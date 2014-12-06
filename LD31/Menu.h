//
//  Menu.h
//  LD31
//
//  Created by Fedor Bobylev on 12/6/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __LD31__Menu__
#define __LD31__Menu__

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

#include "TextureManager.h"
#include "EventHandler.h"

class Menu
{
public:
    Menu();
    ~Menu();
    
    void Update();
    void Render();
    
private:
    int x,y = 0;
    
    std::string Thumb1 = "Thumb1.png";
    std::string Thumb2 = "Thumb2.png";
    std::string Thumb3 = "Thumb3.png";
    std::string Thumb4 = "Thumb4.png";
    std::string Thumb5 = "Thumb5.png";
    std::string Thumb6 = "Thumb6.png";
    std::string Thumb7 = "Thumb7.png";
};

#endif /* defined(__LD31__Menu__) */
