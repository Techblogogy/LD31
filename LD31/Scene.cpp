//
//  Scene.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/18/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "Scene.h"

Scene::Scene(std::string tMapPath)
{
    tileMap = new TileMap(tMapPath);
    
    tileMap->LoadMap();
    tileMap->LoadResources();
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
    tileMap->Update(dt);
    
    for (std::vector<GameObject>::size_type i=0; i<objects.size(); i++)
    {
        objects[i]->Update(dt);
    }
}

void Scene::Render()
{
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
    
    tileMap->CleanUp();
    delete tileMap;
}