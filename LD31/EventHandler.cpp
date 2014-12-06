//
//  EventHandler.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/26/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "EventHandler.h"

EventHandler* EventHandler::g_instance = NULL;
EventHandler* EventHandler::Instance()
{
    if (g_instance == NULL)
        g_instance = new EventHandler();
    
    return g_instance;
}

EventHandler::EventHandler()
{
    
}

void EventHandler::GetEvents(bool &runV)
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                runV = false;
            break;
                
            case SDL_KEYDOWN:
               // printf("Key Down Detected\n");
            break;
                
            case SDL_KEYUP:
                //printf("Key Up Detected\n");
            break;
                
            default:
            break;
        }
    }
    
    keyStates = SDL_GetKeyboardState(NULL);
}

bool EventHandler::isKeyDown(SDL_Scancode k)
{
    if (keyStates[k]) return true;
    return false;
}