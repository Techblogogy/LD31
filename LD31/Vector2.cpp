//
//  Vector2.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/19/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "Vector2.h"

Vector2::Vector2(float xP, float yP)
{
    x = xP;
    y = yP;
}

/*float Vector2::getX()
{
    return x;
}
float Vector2::getY()
{
    return y;
}

void Vector2::setX(float xP)
{
    x = xP;
}
void Vector2::setY(float yP)
{
    y = yP;
}*/

float Vector2::getLength()
{
    return sqrtf(x*x + y*y);
}

void Vector2::normalize()
{
    float l = getLength();
    if (l>0)
    {
        x *= 1/l;
        y *= 1/l;
    }
}