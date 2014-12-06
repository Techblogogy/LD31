//
//  Vector2.h
//  GameEngine
//
//  Created by Fedor Bobylev on 11/19/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __GameEngine__Vector2__
#define __GameEngine__Vector2__

#include <math.h>

class Vector2
{
public:
    Vector2(float xP, float yP); //2D Vector Constructor
    //~Vector2(); //2D Vector Deconstructor
    
    float x,y;
    
    float getLength(); //Calculate length of vector
    void normalize(); //Normalize vector
private:
    //float x,y;
    //int w,h;
};

#endif /* defined(__GameEngine__Vector2__) */
