//
//  Enemy.cpp
//  LD31
//
//  Created by Fedor Bobylev on 12/6/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "GameManager.h"
#include "Enemy.h"

Enemy::Enemy(std::string tId, int w, int h)
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
    
    position.x = 32;
}
Enemy::~Enemy()
{
}

void Enemy::Init()
{
    
}

void Enemy::Update(float dt)
{
    /*if (!dead)
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
        position.x = 32;
        position.y = 0;
        
        dead = false;
    }*/
    
    //vel.x = -64;
    
    animS.sF = 1;
    animS.l = 2;
    
    if (vel.x > 0)
        rf = SDL_FLIP_HORIZONTAL;
    else
        rf = SDL_FLIP_NONE;
    
    GameManager::Instance()->gScene->tileMap->isEmptyEnemy(1, position, texture, vel, dt, grounded, dead);
}

void Enemy::Render()
{
    TextureManager::Instance()->Render(texture, position, animS, rf);
}

void Enemy::CleanUp()
{
    
}