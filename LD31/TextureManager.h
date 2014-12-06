//
//  TextureManager.h
//  GameEngine
//
//  Created by Fedor Bobylev on 11/19/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#ifndef __GameEngine__TextureManager__
#define __GameEngine__TextureManager__

//#include "GameManager.h"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include <string>
#include <map>

#include "Tile.h"
#include "Camera.h"

class TextureManager
{
public:
    static TextureManager* Instance(); //Get or create instance of TextureManager
    
    void LoadTexture(std::string path, std::string name); //Load Texture From File
    SDL_Texture* GetTexture(std::string name); //Get Texture from file
    SDL_Rect GetTextureBounds(std::string name); //Get Texture bounds
    
    void Render(std::string name, Vector2 position); //Render Entire Texture
    
    void Render(Tile t, Vector2 position);
    
    void Render(Tile& t, //Tile Struct
                Vector2& position, //Render Position
                Animation& a,
                SDL_RendererFlip flipped); //Animation Sequence
    
    void CleanUp(); //Destroys SDL Textures
private:
    TextureManager(); //Private texture constructor
    static TextureManager* g_instance; //Texture Manager Instance
    
    std::map<std::string, SDL_Texture*> textureMap; //Stores Game Textures
    
    SDL_Surface* tempSurface; //Temporary surface for texture creation
};

#endif /* defined(__GameEngine__TextureManager__) */
