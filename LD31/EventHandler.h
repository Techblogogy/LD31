//
//  EventHandler.h
//  GameEngine
//
//  Created by Fedor Bobylev on 11/26/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __GameEngine__EventHandler__
#define __GameEngine__EventHandler__

#include <SDL2/SDL.h>

#include <stdio.h>

class EventHandler
{
public:
    static EventHandler* Instance();
    
    void GetEvents(bool &runV);
    
    bool isKeyDown(SDL_Scancode k);
    bool isKeyUp(SDL_Scancode k);
private:
    EventHandler();
    static EventHandler* g_instance;
    
    SDL_Event event;
    
    const Uint8 *keyStates;
};

#endif /* defined(__GameEngine__EventHandler__) */
