//
//  Camera.h
//  GameEngine
//
//  Created by Fedor Bobylev on 11/19/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __GameEngine__Camera__
#define __GameEngine__Camera__

#include <SDL2/SDL.h>
#include "Vector2.h"

class Camera
{
public:
    static Camera* Instance(); //Camera Instance
    
    int GetX() {return bounds.x;}; //Get Camera X
    int GetY() {return bounds.y;}; //Get Camera Y
    
    void SetX(int x) {bounds.x = x;}; //Set Camera X
    void SetY(int y) {bounds.y = y;}; //Set Camera Y
    
    int GetW() {return bounds.w;}; //Get Camera Width
    int GetH() {return bounds.h;}; //Get Camera Height
    
    void SetW(int w) {bounds.w = w;}; //Set Camera Width
    void SetH(int h) {bounds.h = h;}; //Set Camera Height
    
    void CleanUp();
private:
    Camera(int x, int y, int width, int height); // Private Camera Constructor
    static Camera* g_instance; //Camera Instance
    
    SDL_Rect bounds; //Camera Dimension
};

#endif /* defined(__GameEngine__Camera__) */
