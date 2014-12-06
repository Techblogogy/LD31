//
//  Camera.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/19/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "Camera.h"

Camera* Camera::g_instance = NULL;
Camera* Camera::Instance()
{
    if (!g_instance)
    {
        g_instance = new Camera(0,0,800,600);
    }
    
    return g_instance;
}

Camera::Camera(int x, int y, int width, int height)
{
    bounds.x = x;
    bounds.y = y;
    
    bounds.w = width;
    bounds.h = height;
}

void Camera::CleanUp()
{
    delete g_instance;
}