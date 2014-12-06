//
//  Enemy.h
//  LD31
//
//  Created by Fedor Bobylev on 12/6/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __LD31__Enemy__
#define __LD31__Enemy__

#include <string> //Inlcude STD String
#include <math.h>

#include "Vector2.h" //Include Vector 2d library
#include "Camera.h" //Camera Class
#include "TextureManager.h" //Include texture manager
#include "Tile.h"

class Enemy
{
public:
    Enemy(std::string tId, int w, int h); //GameObjet Constructor
    ~Enemy(); //GameObject Destructor
    
    Vector2 position = Vector2(0,0); //Stores GameObject's Position
    
    virtual void Init(); //GameObject Initiation
    virtual void Render(); //GameObject Render
    virtual void Update(float dt); //GameObject Update
    virtual void CleanUp(); //
    
    Tile texture;
    Animation animS;
private:
    Vector2 vel = Vector2(-64,0);
    bool dead = false;
    bool grounded = false;
    SDL_RendererFlip rf = SDL_FLIP_NONE;
};

#endif /* defined(__LD31__Enemy__) */
