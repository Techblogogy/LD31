//
//  TileMap.h
//  GameEngine
//
//  Created by Fedor Bobylev on 11/20/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __GameEngine__TileMap__
#define __GameEngine__TileMap__

#include <CoreFoundation/CFBundle.h>

#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>

#include <string>
#include <fstream>
#include <vector>

#include <stdio.h>

#include "json/json.h"

#include "TextureManager.h"
#include "Camera.h"
#include "Vector2.h"
#include "Tile.h"
#include "Enemy.h"

class TileMap
{
public:
    TileMap(std::string tPath/*, SDL_Renderer* r*/); //Tiled Map Constructor
    ~TileMap(); //Tiled Map Deconstuctor
    
    void LoadMap(); //Load Tiled Map
    void LoadResources(); //Load Tiled Map Resources
    
    void RenderStatic(); //Render Static Layers
    void RenderDynamic(); //Render Dynamic Layers
    
    void Update(float dt);
    
    void isEmpty(int layerId, Vector2 &p, Tile &t, Vector2 &v, float dt, bool &g, bool &d);
    void isEmptyEnemy(int layerId, Vector2 &p, Tile &t, Vector2 &v, float dt, bool &g, bool &d);
    
    void CleanUp();
private:
    std::string tiledPath; //Tile Map Path
    
    Json::Value jMap; //JSON Tiled File
    
    std::vector<int*> mapLayers; //Stores Layers Data
    std::vector<Tile> tiles; //Stores Tilesets Positions
    
    std::vector<Enemy*> enemies;
    
    int tilewidth; //Width of Tile In Pixels
    int tileheight; //Height of tile in pixels
    
    int width; //TileMap width in tiles
    int height; //TileMap height in tiles
    
    Mix_Chunk* hurtFx;
    Mix_Chunk* coreFx;
};

#endif /* defined(__GameEngine__TileMap__) */
