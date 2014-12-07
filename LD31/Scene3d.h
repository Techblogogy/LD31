//
//  Scene3d.h
//  LD31
//
//  Created by Fedor Bobylev on 12/7/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __LD31__Scene3d__
#define __LD31__Scene3d__

#include <SDL2_mixer/SDL_mixer.h>

#include <stdio.h>
#include "Scene.h"
#include "Bitmap.h"

#define GWIDTH 640
#define GHEIGHT 480

class Scene3d : public Scene
{
public:
    Scene3d(int** mp);
    ~Scene3d(); //Scene's Destructor
    
    //TileMap* tileMap; //Stores Tile Map
    //Menu* menu;
    
    //void Add(GameObject* obj); //Add Object to scene
    
    //Fake Player
    Vector2 player = Vector2(2.5,1.5);
    Vector2 plane = Vector2(0,0.66);
    Vector2 direction = Vector2(-1,0);
    
    Float32* zBuffer;
    Uint32* screenBuffer;
    SDL_Texture* screenTex;
    
    /*int map[24][24] =
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };*/
    
    /*int map[5][5]=
    {
        {1,1,1,1,1},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,0,2,0,1},
        {1,4,1,4,1}
    };*/
    
    int** map;
    
    Bitmap* tex[8]={new Bitmap(Vector2(0,0), 32, 32),
                    new Bitmap(Vector2(0,0), 32, 32),
                    new Bitmap(Vector2(0,0), 32, 32),
                    new Bitmap(Vector2(0,0), 32, 32),
                    new Bitmap(Vector2(0,0), 32, 32),
                    new Bitmap(Vector2(0,0), 32, 32),
                    new Bitmap(Vector2(0,0), 32, 32),
                    new Bitmap(Vector2(0,0), 32, 32)};
    
    virtual void Render(); //Render All Objects to scenes
    virtual void Update(float dt); //Update All Objects on scene
    
    void CleanUp();
    
    Mix_Chunk* doneFx;
    
    //std::vector<GameObject*> objects; //Scene Objects
};

#endif /* defined(__LD31__Scene3d__) */
