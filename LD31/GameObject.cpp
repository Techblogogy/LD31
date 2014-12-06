//
//  GameObject.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/17/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "GameManager.h"
#include "GameObject.h"

GameObject::GameObject(std::string tId, int w, int h)
{
    /* Texture Wibly Wolby */
    
    texture.id = tId; //Set Texture Tile Id
    
    texture.r = 0; //
    texture.c = 0; //
    
    texture.w = w; //Set Texture Tile Width in pixels
    texture.h = h; //Set Texture Tile Height in pixels
    
    /* Animation Wibly Wobly */
    
    animS.r = 0; //Set Animation Row (Y)
    
    animS.sF = 0; //Set Animation Start Frame
    animS.l = 1; //Set Animation Length
    
    animS.d = 500; //Set Animation Duration
    
    position.x = 32*1; //31; //18 //26
}
GameObject::~GameObject()
{
}

void GameObject::Init()
{
    
}

Vector2 vel = Vector2(0,0);

bool dead = false;

bool grounded = false;
SDL_RendererFlip rf = SDL_FLIP_NONE;

int timerS = 1000;
int timerC = 0;

void GameObject::Update(float dt)
{
    if (!dead)
    {
        if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
        {
            vel.x = -64;
            
            animS.sF = 1;
            animS.l = 2;
            
            rf = SDL_FLIP_HORIZONTAL;
        }
        else if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
        {
            vel.x = 64;
            
            animS.sF = 1;
            animS.l = 2;
            
            rf = SDL_FLIP_NONE;
        }
        else
        {
            vel.x = 0;
            
            animS.sF = 0;
            animS.l = 1;
        }
        
        if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && grounded)
        {
            vel.y = -4;
        }
        
        if (!grounded)
            vel.y += 5 * (dt/1000.0f);
        
        GameManager::Instance()->gScene->tileMap->isEmpty(1, position, texture, vel, dt, grounded, dead);
    }
    else
    {
        timerC += dt;
        
        if (timerC < timerS)
        {
            rf = SDL_FLIP_VERTICAL;
            vel.y += 5 * (dt/1000.0f);
            position.y += vel.y;
        }
        else
        {
            position.x = 32;
            position.y = 0;
            
            vel.x = 0;
            vel.y = 0;
            
            dead = false;
            
            timerC = 0;
            
            rf = SDL_FLIP_NONE;
        }
    }
}

void GameObject::Render()
{
    TextureManager::Instance()->Render(texture, position, animS, rf);
}

void GameObject::CleanUp()
{
    
}