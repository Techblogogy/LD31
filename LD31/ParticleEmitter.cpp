//
//  ParticleEmitter.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/27/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(Tile tt, Vector2 p, float l, float a, float s)
{
    t = tt;
    
    position = p;
    
    life = l;
    angle = a;
    speed = s;
}

ParticleEmitter::~ParticleEmitter()
{
    
}

void ParticleEmitter::Update(float dt)
{
    //Spawn Particles
    timerC += dt;
    
    if (timerC >= timerD*5)
    {
        for (int i=0; i<partN; i++)
        {
            angle = rand() % 360 + 1;
            particles.push_back(new Particle(t,position,gravityA,life*5,angle,speed));
            timerC = 0;
        }
    }
    
    for (std::vector<Particle*>::size_type i=0; i<particles.size();)
    {
        particles[i]->Update(dt);
        
        if (particles[i]->life < 0)
        {
            delete particles[i];
            particles.erase(particles.begin()+i);
        }
        else
        {
            ++i;
        }
    }
}

void ParticleEmitter::Render()
{
    for (std::vector<Particle*>::size_type i=0; i<particles.size(); i++)
    {
        particles[i]->Render();
    }
}