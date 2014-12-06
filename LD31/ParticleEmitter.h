//
//  ParticleEmitter.h
//  GameEngine
//
//  Created by Fedor Bobylev on 11/27/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __GameEngine__ParticleEmitter__
#define __GameEngine__ParticleEmitter__

#include <stdio.h>
#include <vector>

#include "Particle.h"

class ParticleEmitter
{
public:
    ParticleEmitter(Tile t, Vector2 p, float l, float a, float s);
    ParticleEmitter(Tile t, Vector2 p, bool grav, Vector2 g, float l, float a, float s);
    ~ParticleEmitter();
    
    void Render();
    void Update(float dt);
    
    bool gravity = false;
    void setTime(float time) { timerD = time; };
    void setN(int n) { partN = n; };
    
    void setGravity(Vector2 g) { gravityA = g; };
    
private:
    std::vector<Particle*> particles;
    
    Tile t;
    
    Vector2 position = Vector2(0,0);
    Vector2 velocity = Vector2(0,0);
    
    Vector2 gravityA = Vector2(0,0);
    
    float life = 0;
    float angle = 0;
    float speed = 0;
    
    float timerC = 0;
    float timerD = 1000;
    
    int partN = 1;
};

#endif /* defined(__GameEngine__ParticleEmitter__) */
