//
//  Scene.h
//  GameEngine
//
//  Created by Fedor Bobylev on 11/18/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __GameEngine__Scene__
#define __GameEngine__Scene__

#include <vector>

#include "GameObject.h"
#include "TileMap.h"

class Scene
{
public:
    Scene(std::string tMapPath); //Scene's Constructor
    ~Scene(); //Scene's Destructor
    
    TileMap* tileMap; //Stores Tile Map
    
    void Add(GameObject* obj); //Add Object to scene
    
    void Render(); //Render All Objects to scenes
    void Update(float dt); //Update All Objects on scene
    
    void CleanUp();
    
    std::vector<GameObject*> objects; //Scene Objects
};

#endif /* defined(__GameEngine__Scene__) */
