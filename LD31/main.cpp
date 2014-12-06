//
//  main.cpp
//  LD31
//
//  Created by Fedor Bobylev on 12/6/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include <iostream>
#include "GameManager.h"

int main(int argc, char** argv)
{
    GameManager::Instance()->Init("LD31", 640, 480, "Level1.json");
    
    TextureManager::Instance()->LoadTexture("PlayerSheetThin.png", "playerTex");
    
    GameObject* go = new GameObject("playerTex", 14, 58);
    
    GameManager::Instance()->gScene->Add(go);
    
    GameManager::Instance()->Tick();
    GameManager::Instance()->Clean();
    
    return 0;
}
