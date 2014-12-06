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
    TextureManager::Instance()->LoadTexture(Thumb1, "thumb1");
    TextureManager::Instance()->LoadTexture(Thumb2, "thumb2");
    TextureManager::Instance()->LoadTexture(Thumb3, "thumb3");
    TextureManager::Instance()->LoadTexture(Thumb4, "thumb4");
    TextureManager::Instance()->LoadTexture(Thumb5, "thumb5");
    TextureManager::Instance()->LoadTexture(Thumb6, "thumb6");
    TextureManager::Instance()->LoadTexture(Thumb7, "thumb7");
    
    //Frames
    TextureManager::Instance()->LoadTexture("selector.png", "sel");
}

Menu::~Menu()
{
    
}

void Menu::Update()
{
    if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
    {
        y += 120;
        SDL_Delay(100);
    }
    else if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
    {
        y -= 120;
        SDL_Delay(100);
    }
    else if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
    {
        x -= 160;
        SDL_Delay(100);
    }
    else if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
    {
        x += 160;
        SDL_Delay(100);
    }
    else if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
    {
        if (x==0&&y==0)
        {
            GameManager::Instance()->gScene = new Scene("Level1.json");
            GameObject* player = new GameObject("playerTex", 14, 58);
            
            GameManager::Instance()->gScene->Add(player);
            
            SDL_RenderSetScale(GameManager::Instance()->rend, 1.5, 1.5);
        }
        else if (x==0&&y==120)
        {
            GameManager::Instance()->gScene = new Scene("Level2.json");
            GameObject* player = new GameObject("playerTex", 14, 58);
            
            GameManager::Instance()->gScene->Add(player);
            
            SDL_RenderSetScale(GameManager::Instance()->rend, 1.5, 1.5);
        }
        else if (x==0&&y==240)
        {
            GameManager::Instance()->gScene = new Scene("Level3.json");
            GameObject* player = new GameObject("playerTex", 14, 58);
            
            GameManager::Instance()->gScene->Add(player);
            
            SDL_RenderSetScale(GameManager::Instance()->rend, 1.5, 1.5);
        }
        else if (x==0&&y==360)
        {
            GameManager::Instance()->gScene = new Scene("Level4.json");
            GameObject* player = new GameObject("playerTex", 14, 58);
            
            GameManager::Instance()->gScene->Add(player);
            
            SDL_RenderSetScale(GameManager::Instance()->rend, 1.5, 1.5);
        }
        else if (x==160&&y==0)
        {
            GameManager::Instance()->gScene = new Scene("Level5.json");
            GameObject* player = new GameObject("playerTex", 14, 58);
            
            GameManager::Instance()->gScene->Add(player);
            
            SDL_RenderSetScale(GameManager::Instance()->rend, 1.5, 1.5);
        }
        else if (x==160&&y==120)
        {
            GameManager::Instance()->gScene = new Scene("Level6.json");
            GameObject* player = new GameObject("playerTex", 14, 58);
            
            GameManager::Instance()->gScene->Add(player);
            
            SDL_RenderSetScale(GameManager::Instance()->rend, 1.5, 1.5);
        }
        else if (x==160&&y==240)
        {
            GameManager::Instance()->gScene = new Scene("Level7.json");
            GameObject* player = new GameObject("playerTex", 14, 58);
            
            GameManager::Instance()->gScene->Add(player);
            
            SDL_RenderSetScale(GameManager::Instance()->rend, 1.5, 1.5);
        }
        
        SDL_Delay(100);
    }
}

void Menu::Render()
{
    TextureManager::Instance()->Render("thumb1", Vector2(0,0));
    TextureManager::Instance()->Render("thumb2", Vector2(0,120));
    TextureManager::Instance()->Render("thumb3", Vector2(0,240));
    TextureManager::Instance()->Render("thumb4", Vector2(0,360));
    TextureManager::Instance()->Render("thumb5", Vector2(160,0));
    TextureManager::Instance()->Render("thumb6", Vector2(160,120));
    TextureManager::Instance()->Render("thumb7", Vector2(160,240));
    
    TextureManager::Instance()->Render("sel", Vector2(x,y));
}