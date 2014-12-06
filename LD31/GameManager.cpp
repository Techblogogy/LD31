//
//  GameManager.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/23/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "GameManager.h"

GameManager* GameManager::g_instance = NULL;
GameManager* GameManager::Instance()
{
    if (!g_instance)
    {
        g_instance = new GameManager();
    }
    
    return g_instance;
}

GameManager::GameManager()
{
    
}

/* Initialize GameManager */
void GameManager::Init(std::string wName, int w, int h, std::string path)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    
    CreateWindow(wName, w, h);
    CreateRenderer();
    
    SetUpCamera(w, h);
    SetUpScene(path);
    //SetUpTextureManager();
}

void GameManager::CreateWindow(std::string name, int w, int h)
{
    printf("Creating SDL Window. Name: %s, Width: %d, Height: %d \n", name.c_str(), w, h);
    
    window = SDL_CreateWindow(name.c_str(), //Game Window Name
                              SDL_WINDOWPOS_CENTERED, //Game Window Position X
                              SDL_WINDOWPOS_CENTERED, //Game Window Position Y
                              w, //Game Window Width
                              h, //Game Window Height
                              SDL_WINDOW_SHOWN); //Uint32 SDL Window Flags
    
    if (window == NULL)
    {
        printf("Failed To Create Window: %s\n", SDL_GetError());
    }
    else
    {
        printf("Window Creation Succeeded \n");
    }
}

void GameManager::CreateRenderer()
{
    printf("Creating SDL Renderer. \n");
    
    rend = SDL_CreateRenderer(window, //SDL Window
                              -1, //Renderer Id
                              SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //Renderer Uint32 Flags
    
    if (rend == NULL)
    {
        printf("Failed To Create Renderer: %s\n", SDL_GetError());
    }
    else
    {
        printf("Renderer Creation Succeeded \n");
    }
}

void GameManager::SetUpCamera(int w, int h)
{
    printf("Setting Camera X: %d, Y: %d, Width: %d, Height: %d \n",0,0,w,h);
    
    Camera::Instance()->SetX(0);
    Camera::Instance()->SetY(0);
    
    Camera::Instance()->SetW(w);
    Camera::Instance()->SetH(h);
}

void GameManager::SetUpScene(std::string path)
{
    printf("Creating Scene \n");
    
    gScene = new Scene(path);
    
    if (gScene == NULL)
    {
        printf("Failed To Create Scene \n");
    }
}

void GameManager::SetUpTextureManager()
{
    printf("Creating TextureManager Instance \n");
    
    TextureManager::Instance(); //Init TextureManager Instance
}

/* Game Manager Logic */

#include "Particle.h"
#include "ParticleEmitter.h"
ParticleEmitter* p;

void GameManager::Tick()
{
    /*TextureManager::Instance()->LoadTexture("t1.png", "spSheet");
    
    Tile t;
    t.id = "spSheet";
    t.c = 0;
    t.r = 0;
    t.w = 16;
    t.h = 16;
    p = new ParticleEmitter(t, Vector2(225,215), 500, 30, -128);
    p->setN(10);
    p->setTime(500);
    
    p->setGravity(Vector2(0,2));*/
    
    //int x = 0;
    
    SDL_RenderSetScale(rend, 1.5, 1.5);
    
    while (running)
    {
        time.t = SDL_GetTicks();
        time.d = time.t - time.l;
        time.l = time.t;
        
        //x += 1;
        //Camera::Instance()->SetX(x);
        
        Update();
        
        //p->Update(time.d);
        
        Render();
    }
}

void GameManager::Update()
{
    EventHandler::Instance()->GetEvents(running);
    
    /* Main Logic */
    gScene->Update(time.d);
}

void GameManager::Render()
{
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 1);
    
    SDL_RenderClear(rend);
    
    gScene->Render();
    
    //p->Render();
    
    SDL_RenderPresent(rend);
}

/* Clean Up Game Manager */

void GameManager::Clean()
{
    TextureManager::Instance()->CleanUp();
    Camera::Instance()->CleanUp();
    
    gScene->CleanUp();
    delete gScene;
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend);
    
    SDL_Quit(); //Quit SDL
    
    delete g_instance;
}