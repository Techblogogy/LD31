//
//  Particle.h
//  GameEngine
//
//  Created by Fedor Bobylev on 11/27/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __GameEngine__Particle__
#define __GameEngine__Particle__

#include <stdio.h>

#include "Tile.h"
#include "Vector2.h"

#include "TextureManager.h"

class Particle
{
public:
    Particle(Tile t, Vector2 pos, Vector2 grav, int l, int d, float s);
    ~Particle();
    
    void Update(float dt);
    void Render();
    
    float life = 0;
    
    //bool gravity = true;
    Vector2 gravityA = Vector2(0,0);
    
private:
    Tile texture;
    
    Vector2 position = Vector2(0,0);
    Vector2 velocity = Vector2(0,0);
    
    float angle = 0;
    float speed = 0;
};

#endif /* defined(__GameEngine__Particle__) */
