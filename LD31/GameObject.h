//
//  GameObject.h
//  GameEngine
//
//  Created by Fedor Bobylev on 11/17/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __GameEngine__GameObject__
#define __GameEngine__GameObject__

#include <string> //Inlcude STD String
#include <math.h>

#include "Vector2.h" //Include Vector 2d library
#include "Camera.h" //Camera Class
#include "TextureManager.h" //Include texture manager
#include "Tile.h"

class GameObject
{
public:
    GameObject(std::string tId, int w, int h); //GameObjet Constructor
    ~GameObject(); //GameObject Destructor
    
    Vector2 position = Vector2(0,0); //Stores GameObject's Position
    
    virtual void Init(); //GameObject Initiation
    virtual void Render(); //GameObject Render
    virtual void Update(float dt); //GameObject Update
    virtual void CleanUp(); //
private:
    Tile texture;
    Animation animS;
};

#endif /* defined(__GameEngine__GameObject__) */
