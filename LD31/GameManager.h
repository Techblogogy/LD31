//
//  GameManager.h
//  GameEngine
//
//  Created by Fedor Bobylev on 11/23/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __GameEngine__GameManager__
#define __GameEngine__GameManager__

#include <SDL2/SDL.h> //Main SDL Header
#include <stdio.h> //STD IO Library

#include "TextureManager.h" //Game Texture Manager
#include "EventHandler.h" //Game Event Manager
#include "Camera.h" //Game Camera
#include "Scene.h" //Game Scene
#include "TileMap.h" //Game Tile Map

#define FPS_MS 16

struct Time
{
    Uint32 t = 0; //Current Time
    Uint32 d = 0; //Delta Time
    Uint32 l = 0; //Last Frame Time
};

class GameManager
{
public:
    static GameManager* Instance(); //GameManager Singleton Instance
    
    SDL_Window* window; //SDL Game Window
    SDL_Renderer* rend; //SDL Game Renderer
    
    Scene* gScene; //Main Game Scene
    
    Time time;
    
    void Init(std::string wName, int w, int h, std::string path); //Init Game Manager
    
    void Tick(); //Main Game Loop
    void Clean(); //CleanUp Game Variables
    
private:
    GameManager(); //GameManager Constructor
    static GameManager* g_instance; //Game Manager private instance
    
    bool running = true;
    
    void CreateWindow(std::string name, int w, int h); //Creating SDL Window
    void CreateRenderer(); //Create SDL Renderer
    
    void SetUpCamera(int w, int h); //Setup Camera
    void SetUpTextureManager(); //Setup TextureManager
    void SetUpScene(std::string path); //Setup Scene
    
    void Update(); //Handle Game Physics
    void Render(); //Render Game
};

#endif /* defined(__GameEngine__GameManager__) */
