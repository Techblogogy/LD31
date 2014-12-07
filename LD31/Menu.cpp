//
//  Menu.cpp
//  LD31
//
//  Created by Fedor Bobylev on 12/6/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "GameManager.h"
#include "Menu.h"

Menu::Menu()
{
    //Frames
    TextureManager::Instance()->LoadTexture("selector.png", "sel");
    TextureManager::Instance()->LoadTexture("SelectorDone.png", "selD");
    
    TextureManager::Instance()->LoadTexture("Splash.png", "splash");
    
    TextureManager::Instance()->LoadTexture("menuNav.png", "nav");
    
    for (int i=0; i<LEVELS; i++)
    {
        TextureManager::Instance()->LoadTexture(levels[i].thumbNail, levels[i].thumbNail);
        
        levels[i].lvTh = Mix_LoadMUS(levels[i].themePath.c_str());
        
        levels[i].x = x;
        levels[i].y = y;
        
        y += 120;
        if (y == 4*120)
        {
            x+=160;
            y=0;
        }
        
        //if (i==0) levels[i].enabled = false;
    }
    
    x=0;
    y=0;
    
    //Init 3D Levels
    //int** m1 = new int*[5];
    
    //Level 1
    for (int i=0; i<5; i++)
        m1[i] = new int[5];
    for (int y=0; y<5; y++)
        for (int x=0; x<5; x++)
            m1[y][x] = map1[y][x];
    
    //Level 2
    for (int i=0; i<12; i++)
        m2[i] = new int[12];
    for (int y=0; y<12; y++)
        for (int x=0; x<12; x++)
            m2[y][x] = map2[y][x];
    
    //Level 3
    for (int i=0; i<18; i++)
        m3[i] = new int[18];
    for (int y=0; y<18; y++)
        for (int x=0; x<18; x++)
            m3[y][x] = map3[y][x];
    
    //Level 4
    for (int i=0; i<19; i++)
        m4[i] = new int[19];
    for (int y=0; y<19; y++)
        for (int x=0; x<19; x++)
            m4[y][x] = map4[y][x];
    
    //Level 5
    for (int i=0; i<24; i++)
        m5[i] = new int[24];
    for (int y=0; y<24; y++)
        for (int x=0; x<24; x++)
            m5[y][x] = map5[y][x];
    
    //Level 6
    for (int i=0; i<24; i++)
        m6[i] = new int[24];
    for (int y=0; y<24; y++)
        for (int x=0; x<24; x++)
            m6[y][x] = map6[y][x];
    
    //Level 7
    for (int i=0; i<12; i++)
        m7[i] = new int[12];
    for (int y=0; y<12; y++)
        for (int x=0; x<12; x++)
            m7[y][x] = map7[y][x];
    
    
    clkFx = Mix_LoadWAV("Blip_Select4.wav");
    theme = Mix_LoadMUS("menuTheme.wav");
}

Menu::~Menu()
{
    
}

bool startTheme = false;

void Menu::Update()
{
    Camera::Instance()->SetX(0);
    Camera::Instance()->SetY(0);
    
    if (!startTheme)
    {
        //Mix_PlayChannel(-1, theme, 0);
        Mix_PlayMusic(theme, -1);
        startTheme = true;
    }
    
    if (splash)
    {
        if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
        {
            Mix_PlayChannel(-1, clkFx, 0);
            splash = false;
        }
    }
    
    if (!splash)
    {
        if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
        {
            if (lv+1 < LEVELS)
            {
                lv++;
                x = levels[lv].x;
                y = levels[lv].y;
            }
            
            Mix_PlayChannel(-1, clkFx, 0);
            
            SDL_Delay(100);
        }
        else if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
        {
            if (lv-1 >= 0)
            {
                lv--;
                x = levels[lv].x;
                y = levels[lv].y;
            }
            
            Mix_PlayChannel(-1, clkFx, 0);
            
            SDL_Delay(100);
        }
        else if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
        {
            if (lv-4 >= 0)
            {
                lv-=4;
                x = levels[lv].x;
                y = levels[lv].y;
            }
            
            Mix_PlayChannel(-1, clkFx, 0);
            
            SDL_Delay(100);
        }
        else if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
        {
            if (lv+4 < LEVELS)
            {
                lv+=4;
                x = levels[lv].x;
                y = levels[lv].y;
            }
            
            Mix_PlayChannel(-1, clkFx, 0);
            
            SDL_Delay(100);
        }
        else if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
        {
            if (!levels[lv].is3d)
            {
                GameManager::Instance()->gScene = new Scene(levels[lv].tileMap);
                GameObject* player = new GameObject("playerTex", 14, 58);
                
                GameManager::Instance()->gScene->Add(player);
                
                SDL_RenderSetScale(GameManager::Instance()->rend, 1.5, 1.5);
            }
            else
            {
                GameManager::Instance()->gScene = new Scene3d(levels[lv].map);
            }
            
            Mix_PlayChannel(-1, clkFx, 0);
            Mix_HaltMusic();
            
            if (levels[lv].lvTh != NULL)
                Mix_PlayMusic(levels[lv].lvTh, -1);
            
            SDL_Delay(100);
        }
    }
}

void Menu::Render()
{
    for (int i=0; i<LEVELS; i++)
    {
        TextureManager::Instance()->Render(levels[i].thumbNail, Vector2(levels[i].x,levels[i].y));
        
        if (levels[i].enabled==false)
        {
            TextureManager::Instance()->Render("selD", Vector2(levels[i].x,levels[i].y));
        }
    }
    
    TextureManager::Instance()->Render("sel", Vector2(x,y));
    TextureManager::Instance()->Render("nav", Vector2(160*3,120*2));
    
    if (splash)
        TextureManager::Instance()->Render("splash", Vector2(0,0));
}

void Menu::finnishLast()
{
    Mix_HaltMusic();
    Mix_PlayMusic(theme, -1);
    levels[lv].enabled = false;
}