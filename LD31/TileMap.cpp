//
//  TileMap.cpp
//  GameEngine
//
//  Created by Fedor Bobylev on 11/20/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "GameManager.h"
#include "TileMap.h"


TileMap::TileMap(std::string tP)
{
    tiledPath = tP;
    
    hurtFx = Mix_LoadWAV("Hit_Hurt14.wav");
    coreFx = Mix_LoadWAV("Pickup_Coin13.wav");
}

TileMap::~TileMap()
{
    
}

Json::Value ReadJSONFile(std::string path)
{
#ifdef __APPLE__
    
    /* MAC ONLY */
    /* Get Current Mac Application Directory */
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    if (!mainBundle) printf("Failed To Get Main Application Bundle \n");
    
    char* cBuf = new char[200];
    
    CFURLRef resourceUrl = CFBundleCopyResourceURL(mainBundle, CFStringCreateWithCString(NULL, path.c_str(), kCFStringEncodingASCII), NULL, NULL);
    if (!resourceUrl) printf("Failed To Get Resource Folder Path \n");
    CFURLGetFileSystemRepresentation(resourceUrl, true, (Uint8*)cBuf, 200);
    
    /* Read Tile Map File */
    Json::Value jVal;
    Json::Reader jTxt; //JSON File Parser
    std::ifstream fStr(cBuf, std::ifstream::binary);
    bool loaded = jTxt.parse(fStr, jVal, false);
    if (!loaded) printf("Failed To Load Tiled Map File. Path: %s Reason: %s \n", cBuf, jTxt.getFormatedErrorMessages().c_str());
    
    delete cBuf;
    
    return jVal;
    
#else
    /* Windows Only */
    
    /* Read Tile Map File */
    Json::Value jVal;
    Json::Reader jTxt; //JSON File Parser
    std::ifstream fStr(path, std::ifstream::binary);
    bool loaded = jTxt.parse(fStr, jVal, false);
    if (!loaded) printf("Failed To Load Tiled Map File. Path: %s Reason: %s \n", path.c_str(), jTxt.getFormatedErrorMessages().c_str());
    
    return jVal;
#endif
}

void TileMap::LoadMap()
{
    printf("Loading Tiled Map File At: %s \n", tiledPath.c_str());
    
    jMap = ReadJSONFile(tiledPath);
    
    /* Init Variables */
    
    tilewidth = jMap["tilewidth"].asInt(); //Defines Width of Tile in pixels
    tileheight = jMap["tileheight"].asInt(); //Defines Height of Tile in pixels
    
    width = jMap["width"].asInt(); //Defines Width Of Tilemap in tiles
    height = jMap["height"].asInt(); //Defines Width Of Tilemap in tiles
    
    //dRect.w = tilewidth; //Sets rendering rectange width to width of tile
    //dRect.h = tileheight; //Sets rendering rectange height to height of tile
    
    const Json::Value jLayers = jMap["layers"]; //Get's all tile map layers
    for (int i=0; i<jLayers.size(); i++) //Loops thorught each tile map layer
    {
        mapLayers.push_back(new int[width*height]); //Adds layer map to Layers List
        
        const Json::Value jLayer = jLayers[i]["data"]; //Get's layer data
        for (int a=0; a<jLayer.size(); a++) //Loop to copy data from json layer to array of integers
        {
            mapLayers[i][a] = jLayer[a].asInt();
            
            if (mapLayers[i][a] == 17)
            {
                mapLayers[i][a] = 0;
                
                Enemy* en = new Enemy("PlatformerTiles",32,32);
                en->animS.r = 1;
                en->position = Vector2(a%width*tilewidth,a/width*tileheight);
                
                enemies.push_back(en);
            }
        }
    }
}

void TileMap::LoadResources()
{
    Tile tRect; //Tile Rectangle
    const Json::Value tilesets = jMap["tilesets"]; //Get list of JSON tilesheets
    
    for (int i=0; i<tilesets.size(); i++) //Loop thought JSON tilesheets
    {
        TextureManager::Instance()->LoadTexture(tilesets[i]["image"].asString(),
                                                tilesets[i]["name"].asString()); //Load tilesheet texture using bitmap
        
        tRect.w = tilesets[i]["tilewidth"].asInt(); //Set tilesheet tile width in pixels
        tRect.h = tilesets[i]["tileheight"].asInt(); //Set tilesheet tile height in pixels
        
        tRect.id = tilesets[i]["name"].asString(); //Set tilesheet id
        
        for (int y=0; y<tilesets[i]["imageheight"].asInt()/tRect.h; y++)
        {
            for (int x=0; x<tilesets[i]["imagewidth"].asInt()/tRect.w; x++)
            {
                tRect.r = /*tRect.b.h */ y;
                tRect.c = /*tRect.b.w */ x;
                
                tiles.push_back(tRect);
            }
        }
    }
}

void TileMap::RenderStatic()
{
    for (int x=0; x<width; x++)
    {
        for (int y=0; y<height; y++)
        {
            for (int i=0; i<mapLayers.size(); i++)
            {
                if (mapLayers[i][y*width+x] == 0) continue;
                
                TextureManager::Instance()->Render(tiles[mapLayers[i][y*width+x]-1], //Tile Struct
                                                   Vector2(x*tilewidth, y*tileheight)); //Render Position
            }
        }
    }
    
    for (std::vector<Enemy*>::size_type i=0; i<enemies.size(); i++)
    {
        enemies[i]->Render();
    }
}

void TileMap::RenderDynamic()
{
    
}

void TileMap::isEmpty(int layerId, Vector2 &p, Tile &t, Vector2 &v, float dt, bool &g, bool &d)
{
    Vector2 pp = p;
    
    pp.y += v.y;// * (dt/1000.0f);
    
    Vector2 p1 = Vector2( (int)(pp.x)/(tilewidth), (int)(pp.y)/(tileheight) ); //Top Left
    Vector2 p2 = Vector2( (int)(pp.x-1+t.w)/(tilewidth), (int)(pp.y)/(tileheight) ); //Top Right
    
    Vector2 p3 = Vector2( (int)(pp.x)/(tilewidth), (int)(pp.y+t.h)/(tileheight) ); //Bottom Left
    Vector2 p4 = Vector2( (int)(pp.x-1+t.w)/(tilewidth), (int)(pp.y+t.h)/(tileheight) ); //Bottom Right
    
    
    if (v.y > 0)
    {
        //Bottom Collision
        if (mapLayers[layerId][(int)(p3.y*width+p3.x)] == 0 &&
            mapLayers[layerId][(int)(p4.y*width+p4.x)] == 0)
        {
            p.y += v.y; //* (dt/1000.0f);
            g = false;
        }
        else
        {
            g = true;
            p.y = (p3.y)*tileheight - t.h;
            
            if (mapLayers[layerId][(int)(p3.y*width+p3.x)] == 4)
            {
                Mix_PlayChannel(-1, hurtFx, 0);
                d=true;
            }
            
            if (mapLayers[layerId][(int)(p3.y*width+p3.x)] == 5) //End Level
            {
                Mix_PlayChannel(-1, coreFx, 0);
                
                SDL_RenderSetScale(GameManager::Instance()->rend, 1, 1);
                
                Camera::Instance()->SetX(0);
                Camera::Instance()->SetY(0);
                
                GameManager::Instance()->mn->finnishLast();
                GameManager::Instance()->gScene = GameManager::Instance()->menuScene;
                
                printf("Ending\n");
            }
        }
    }
    else
    {
        //Top Collision
        if (mapLayers[layerId][(int)(p1.y*width+p1.x)] == 0 &&
            mapLayers[layerId][(int)(p2.y*width+p2.x)] == 0)
        {
            p.y += v.y;// * (dt/1000.0f);
            g = false;
        }
        else
        {
            v.y = 32;
            p.y = (p1.y)*tileheight + tileheight;
        }
    }
    
    p.x += v.x * (dt/1000.0f);
    
    pp = p;
    pp.x += v.x * (dt/1000.0f);
    
    p1 = Vector2( (int)(pp.x)/(tilewidth), (int)(pp.y+1)/(tileheight) ); //Top Left
    p2 = Vector2( (int)(pp.x+t.w)/(tilewidth), (int)(pp.y+1)/(tileheight) ); //Top Right
    
    Vector2 p5 = Vector2( (int)(pp.x)/(tilewidth), (int)(pp.y-1+t.h/2)/(tileheight) ); //Middle Left
    Vector2 p6 = Vector2( (int)(pp.x+t.w)/(tilewidth), (int)(pp.y-1+t.h/2)/(tileheight) ); //Middle Right
    
    p3 = Vector2( (int)(pp.x)/(tilewidth), (int)(pp.y-1+t.h)/(tileheight) ); //Bottom Left
    p4 = Vector2( (int)(pp.x+t.w)/(tilewidth), (int)(pp.y-1+t.h)/(tileheight) ); //Bottom Right
    
    if (v.x > 0)
    {
        //if (pp.x > width*tilewidth) pp.x = width-t.w;
        
        //Right Collision
        if (mapLayers[layerId][(int)(p2.y*width+p2.x)] == 0 &&
            mapLayers[layerId][(int)(p4.y*width+p4.x)] == 0 &&
            mapLayers[layerId][(int)(p6.y*width+p6.x)] == 0)
        {
            p.x += v.x * (dt/1000.0f);
        }
        else
        {
            p.x = (p2.x)*tilewidth - t.w;
            
            if (mapLayers[layerId][(int)(p3.y*width+p3.x)] == 5)
            {
                d=true;
            }
        }
    }
    else if (v.x<0)
    {
        //Left Collision
        if (mapLayers[layerId][(int)(p1.y*width+p1.x)] == 0 &&
            mapLayers[layerId][(int)(p3.y*width+p3.x)] == 0 &&
            mapLayers[layerId][(int)(p5.y*width+p5.x)] == 0)
        {
            p.x += v.x * (dt/1000.0f);
        }
        else
        {
            p.x = (p1.x)*tilewidth + tilewidth;
        }
    }
    
    //Enemy Collison
    for (std::vector<Enemy*>::size_type i=0; i<enemies.size(); i++)
    {
        if ( !((int)(p.x+t.w) < (int)(enemies[i]->position.x) ||
               (int)(enemies[i]->position.x+enemies[i]->texture.w) < (int)(p.x) ||
               (int)(p.y+t.h) < (int)(enemies[i]->position.y) ||
               (int)(enemies[i]->position.y+enemies[i]->texture.h) < (int)(p.y) ) )
        {
            Mix_PlayChannel(-1, hurtFx, 0);
            d=true;
        }
    }
    
    int camX = p.x - 640/4;
    
    if (camX < 0) camX = 0;
    if (camX >= width*tilewidth-640/1.5) camX = width*tilewidth-640/1.5;
    
    Camera::Instance()->SetX(camX);
}

void TileMap::isEmptyEnemy(int layerId, Vector2 &p, Tile &t, Vector2 &v, float dt, bool &g, bool &d)
{
    Vector2 pp = p;
    pp.x += v.x * (dt/1000.0f);
    
    Vector2 p1 = Vector2( (int)(pp.x)/(tilewidth), (int)(pp.y+1)/(tileheight) ); //Top Left
    Vector2 p2 = Vector2( (int)(pp.x+t.w)/(tilewidth), (int)(pp.y+1)/(tileheight) ); //Top Right
    
    Vector2 p3 = Vector2( (int)(pp.x)/(tilewidth), (int)(pp.y-1+t.h)/(tileheight) ); //Bottom Left
    Vector2 p4 = Vector2( (int)(pp.x+t.w)/(tilewidth), (int)(pp.y-1+t.h)/(tileheight) ); //Bottom Right
    
    if (v.x > 0)
    {
        //Right Collision
        if (mapLayers[layerId][(int)(p2.y*width+p2.x)] == 0 &&
            mapLayers[layerId][(int)(p4.y*width+p4.x)] == 0)
        {
            if (mapLayers[layerId][(int)((p4.y+1)*width+p4.x)] == 0 ||
                mapLayers[layerId][(int)((p4.y+1)*width+p4.x)] == 4)
            {
                v.x = -v.x;
            }
            
            p.x += v.x * (dt/1000.0f);
        }
        else
        {
            p.x = (p2.x)*tilewidth - t.w;
            v.x = -v.x;
        }
    }
    else if (v.x<0)
    {
        //Left Collision
        if (mapLayers[layerId][(int)(p1.y*width+p1.x)] == 0 &&
            mapLayers[layerId][(int)(p3.y*width+p3.x)] == 0)
        {
            if (mapLayers[layerId][(int)((p3.y+1)*width+p3.x)] == 0 ||
                mapLayers[layerId][(int)((p3.y+1)*width+p3.x)] == 4)
            {
                v.x = -v.x;
            }
            
            p.x += v.x * (dt/1000.0f);
        }
        else
        {
            p.x = (p1.x)*tilewidth + tilewidth;
            v.x = -v.x;
        }
    }
}

void TileMap::Update(float dt)
{
    for (std::vector<Enemy*>::size_type i=0; i<enemies.size(); i++)
    {
        enemies[i]->Update(dt);
    }
}

void TileMap::CleanUp()
{
    for (std::vector<int*>::size_type i=0; i<mapLayers.size(); i++)
    {
        delete mapLayers[i];
    }
    mapLayers.clear();
    
    for (std::vector<Enemy*>::size_type i=0; i<enemies.size(); i++)
    {
        delete enemies[i];
    }
    enemies.clear();
    
    tiles.clear();
}