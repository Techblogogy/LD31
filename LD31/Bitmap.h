//
//  Bitmap.h
//  LD31
//
//  Created by Fedor Bobylev on 12/7/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __LD31__Bitmap__
#define __LD31__Bitmap__

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string>

#include <CoreFoundation/CoreFoundation.h>

#include "Vector2.h"

class Bitmap
{
public:
    Bitmap(Vector2 p, int width, int height);
    ~Bitmap();
    
    Vector2 position = Vector2(0,0);
    
    void GenerateXORTexture(Uint8 r, Uint8 g, Uint8 b);
    void LoadTexture(std::string path);
    
    Uint32* pixels;
    int width = 0;
    int height = 0;
private:
    
};

#endif /* defined(__LD31__Bitmap__) */
