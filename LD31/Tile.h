//
//  Tile.h
//  GameEngine
//
//  Created by Fedor Bobylev on 11/26/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef GameEngine_Tile_h
#define GameEngine_Tile_h

#include <string>

struct Tile
{
    std::string id; //Tile Id in data map
    
    int c; //Tile Coloum (X)
    int r; //Tile Row (Y)
    
    int w; //Width Of Tile In Pixels
    int h; //Height Of Tile In Pixels
};

struct Animation
{
    int r; //Animation Row (Y)
    
    int sF; //Animation Start Frame
    int l; //Length of animation in frames
    
    int d; //Frame Duration
};

#endif