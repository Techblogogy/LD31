//
//  Particle.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/27/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "GameManager.h"
#include "Particle.h"

Particle::Particle(Tile t, Vector2 pos, Vector2 grav, int l, int d, float s)
{
    texture = t;
    
    position = pos;
    
    life = (float)l;
    angle = d * M_PI / 180;
    
    gravityA = grav;
    
    velocity.x = s * cosf(angle);
    velocity.y = s * sinf(angle);
}
Particle::~Particle()
{
    
}

void Particle::Update(float dt)
{
    life -= dt;
    
    if (life > 0)
    {
        Vector2 fP = Vector2(position.x + velocity.x * (dt/1000.0f),
                             position.y + velocity.y * (dt/1000.0f));
        
        /*if (GameManager::Instance()->gScene->tileMap->isEmpty(1, fP, texture, fP, dt))
        {
            position.x += velocity.x * (dt/1000.0f);
            position.y += velocity.y * (dt/1000.0f);
        }
        else
        {
            if (velocity.x > 0)
            {
                position.x = (int)(fP.x/32) * 32 + texture.w;
            }
        }*/
        
        /*fP = Vector2(position.x,
                     position.y + velocity.y * (dt/1000.0f));
        
        if (GameManager::Instance()->gScene->tileMap->isEmpty(1, fP, texture, fP))
        {
            position.y += velocity.y * (dt/1000.0f);
        }*/
        
        //position.x += velocity.x * (dt/1000.0f);
        //position.y += velocity.y * (dt/1000.0f);
        
        /* Simulate Gravity */
        velocity.y += 1.8f*gravityA.y;
        velocity.x += 1.8f*gravityA.x;
    }
}

void Particle::Render()
{
    TextureManager::Instance()->Render(texture, position);
}