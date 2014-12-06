//
//  Scene.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/18/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "Scene.h"

Scene::Scene()
{
    tileMap = NULL;
    menu = NULL;
}
Scene::Scene(std::string tMapPath)
{
    tileMap = new TileMap(tMapPath);
    
    tileMap->LoadMap();
    tileMap->LoadResources();
    
    menu = NULL;
}
Scene::~Scene()
{
    
}

void Scene::Add(GameObject* obj)
{
    objects.push_back(obj);
    obj->Init();
}

void Scene::Update(float dt)
{
    if (menu != NULL)
        menu->Update();
    
    if (tileMap != NULL)
        tileMap->Update(dt);
    
    for (std::vector<GameObject>::size_type i=0; i<objects.size(); i++)
    {
        objects[i]->Update(dt);
    }
}

void Scene::Render()
{
    if (menu != NULL)
        menu->Render();
    
    if (tileMap != NULL)
        tileMap->RenderStatic();
    
    for (std::vector<GameObject>::size_type i=0; i<objects.size(); i++)
    {
        objects[i]->Render();
    }
}

void Scene::CleanUp()
{
    for (std::vector<GameObject>::size_type i=0; i<objects.size(); i++)
    {
        objects[i]->CleanUp();
        delete objects[i];
    }
    objects.clear();
    
    if (tileMap != NULL)
        tileMap->CleanUp();
    
    delete tileMap;
}