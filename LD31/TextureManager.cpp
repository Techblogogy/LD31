//
//  TextureManager.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/19/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "GameManager.h"
#include "TextureManager.h"

TextureManager* TextureManager::g_instance = NULL;
TextureManager* TextureManager::Instance()
{
    if (!g_instance) {
        g_instance = new TextureManager();
    }
    
    return g_instance;
}

TextureManager::TextureManager()
{
    
}

void TextureManager::LoadTexture(std::string path, std::string name)
{
    printf("Loading Image. Id: %s, Path: %s \n", name.c_str(), path.c_str());
    
    if (textureMap[name] != NULL) printf("Image with");
    
    SDL_Texture* tex;
    
    tempSurface = IMG_Load(path.c_str());
    tex = SDL_CreateTextureFromSurface(GameManager::Instance()->rend, tempSurface);
    
    if (tex == NULL) printf("Image Loading Failed.");
    
    SDL_FreeSurface(tempSurface);
    
    textureMap[name] = tex;
}

SDL_Texture* TextureManager::GetTexture(std::string name)
{
    return textureMap[name];
}

SDL_Rect TextureManager::GetTextureBounds(std::string name)
{
    SDL_Rect bounds;
    SDL_QueryTexture(textureMap[name], NULL, NULL, &bounds.w, &bounds.h);
    
    bounds.x = 0;
    bounds.y = 0;
    
    return bounds;
}

void TextureManager::Render(std::string name, Vector2 position)
{
    SDL_Rect destR; //Stores Texture Draw Position
    SDL_Rect bounds; //Stores Texture crop position
    SDL_QueryTexture(textureMap[name], NULL, NULL, &bounds.w, &bounds.h); //Get Texture Width And Height
    
    bounds.x = 0;
    bounds.y = 0;
    
    destR.x = (int)position.x - Camera::Instance()->GetX();
    destR.y = (int)position.y - Camera::Instance()->GetY();
    
    destR.w = bounds.w;
    destR.h = bounds.h;
    
    SDL_RenderCopy(GameManager::Instance()->rend, textureMap[name], &bounds, &destR);
}

void TextureManager::Render(Tile t, Vector2 position)
{
    SDL_Rect destR; //Stores Texture Draw Position
    SDL_Rect bounds; //Stores Texture crop position
    
    bounds.x = t.c * t.w;
    bounds.y = t.r * t.h;
    
    destR.x = (int)roundf(position.x) - Camera::Instance()->GetX();
    destR.y = (int)roundf(position.y) - Camera::Instance()->GetY();
    
    destR.w = bounds.w = t.w;
    destR.h = bounds.h = t.h;
    
    SDL_RenderCopy(GameManager::Instance()->rend, textureMap[t.id], &bounds, &destR);
}

void TextureManager::Render(Tile& t, Vector2& position, Animation& a, SDL_RendererFlip fliped)
{
    SDL_Rect destR; //Stores Texture Draw Position
    SDL_Rect bounds; //Stores Texture crop position
    
    t.r = a.r;
    t.c = a.sF + (SDL_GetTicks()/a.d % a.l);
    
    bounds.x = t.c * t.w;
    bounds.y = t.r * t.h;
    
    destR.x = position.x - Camera::Instance()->GetX();
    destR.y = position.y - Camera::Instance()->GetY();
    
    destR.w = bounds.w = t.w;
    destR.h = bounds.h = t.h;
    
    //SDL_RenderCopy(GameManager::Instance()->rend, textureMap[t.id], &bounds, &destR);
    
    SDL_RenderCopyEx(GameManager::Instance()->rend, textureMap[t.id], &bounds, &destR, 0, NULL, fliped);
}

void TextureManager::CleanUp()
{
    printf("Cleaning Texture Manager");
    
    std::map<std::string, SDL_Texture*>::iterator it;
    for (it = textureMap.begin(); it!=textureMap.end(); it++)
    {
        SDL_DestroyTexture(it->second);
    }
    textureMap.clear();
    
    delete g_instance;
}