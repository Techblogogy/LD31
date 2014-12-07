//
//  Scene3d.cpp
//  LD31
//
//  Created by Fedor Bobylev on 12/7/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "GameManager.h"
#include "Scene3d.h"

Scene3d::Scene3d(int** mp)
{
    screenBuffer = new Uint32[GWIDTH*GHEIGHT];
    screenTex = SDL_CreateTexture(GameManager::Instance()->rend,
                                  SDL_PIXELFORMAT_ABGR8888,
                                  SDL_TEXTUREACCESS_STREAMING,
                                  GWIDTH,
                                  GHEIGHT);
    
    zBuffer = new Float32[GWIDTH];
    
    map = mp;
    
    //printf("%d\n", tex[4]->width);
    
    //tex[0]->GenerateXORTexture(255, 0, 0);
    //tex[1]->GenerateXORTexture(0, 255, 0);
    //tex[2]->GenerateXORTexture(0, 0, 255);
    //tex[3]->GenerateXORTexture(255, 255, 0);
    //tex[4]->GenerateXORTexture(0, 255, 255);
    
    tex[0]->LoadTexture("Brick.bmp");
    tex[1]->LoadTexture("core.bmp");
    tex[2]->LoadTexture("Selling.bmp");
    tex[3]->LoadTexture("inst.bmp");
    tex[4]->LoadTexture("hello.bmp");
    tex[5]->LoadTexture("BrickWay.bmp");
    tex[6]->LoadTexture("BrickNo.bmp");
    tex[7]->LoadTexture("BrickLost.bmp");
    
    doneFx = Mix_LoadWAV("Pickup_Coin13.wav");
}
Scene3d::~Scene3d()
{
    
}

/*void Scene3d::Add(GameObject* obj)
{
    objects.push_back(obj);
    obj->Init();
}*/

void Scene3d::Update(float dt)
{
    float rT = 4.0f * (dt/1000.0f);
    float moveV = 3.0f * (dt/1000.0f);
    
    if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_W))
    {
        if (map[(int)(player.y)][(int)(player.x+direction.x*moveV)] == false) player.x += direction.x * moveV;
        if (map[(int)(player.y+direction.y*moveV)][(int)(player.x)] == false) player.y += direction.y * moveV;
        
        if (map[(int)(player.y)][(int)(player.x+direction.x*moveV)] == 2 ||
            map[(int)(player.y+direction.y*moveV)][(int)(player.x)] == 2)
        {
            Mix_PlayChannel(-1, doneFx, 0);
            
            GameManager::Instance()->gScene = GameManager::Instance()->menuScene;
            GameManager::Instance()->mn->finnishLast();
        }
    }
    if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_S))
    {
        if (map[(int)(player.y)][(int)(player.x-direction.x*moveV)] == false) player.x -= direction.x * moveV;
        if (map[(int)(player.y-direction.y*moveV)][(int)(player.x)] == false) player.y -= direction.y * moveV;
    }
    
    if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
    {
        float oDirX = direction.x;
        direction.x = direction.x * cosf(rT) - direction.y * sinf(rT);
        direction.y = oDirX * sinf(rT) + direction.y * cosf(rT);
        
        float op = plane.x;
        plane.x = plane.x * cosf(rT) - plane.y * sinf(rT);
        plane.y = op * sinf(rT) + plane.y * cosf(rT);
    }
    
    if (EventHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
    {
        float oDirX = direction.x;
        direction.x = direction.x * cosf(-rT) - direction.y * sinf(-rT);
        direction.y = oDirX * sinf(-rT) + direction.y * cosf(-rT);
        
        float op = plane.x;
        plane.x = plane.x * cosf(-rT) - plane.y * sinf(-rT);
        plane.y = op * sinf(-rT) + plane.y * cosf(-rT);
    }
    
    
    //printf("Scene3d Updating\n");
}

void Scene3d::Render()
{
    for (int i=0; i<GWIDTH*GHEIGHT; i++)
        screenBuffer[i] = 0;
    
    for (int x=0; x<GWIDTH; x++)
    {
        float camX = 2 * x/float(GWIDTH) - 1; //Get Point In Camera
        
        Vector2 rayP = player; //Start Ray Position
        Vector2 rayD = Vector2 (direction.x + plane.x * camX,
                                direction.y + plane.y * camX); //Ray Direction
        // Do DDA
        int mapX = (int)rayP.x;
        int mapY = (int)rayP.y;
        
        Vector2 rayDistance = Vector2(0,0);
        Vector2 dRayDistance = Vector2 ( sqrtf(1 + (rayD.y*rayD.y) / (rayD.x*rayD.x)),
                                         sqrtf(1 + (rayD.x*rayD.x) / (rayD.y*rayD.y)));
        
        float wDist;
        
        int stepX;
        int stepY;
        
        bool hit = false;
        int side = 0;
        if (rayD.x < 0)
        {
            stepX = -1;
            rayDistance.x = (rayP.x-mapX)*dRayDistance.x;
        }
        else
        {
            stepX = 1;
            rayDistance.x = (mapX + 1.0f - rayP.x)*dRayDistance.x;
        }
        if (rayD.y < 0)
        {
            stepY = -1;
            rayDistance.y = (rayP.y-mapY)*dRayDistance.y;
        }
        else
        {
            stepY = 1;
            rayDistance.y = (mapY + 1.0f - rayP.y)*dRayDistance.y;
        }
        while (!hit)
        {
            if (rayDistance.x < rayDistance.y)
            {
                rayDistance.x += dRayDistance.x;
                mapX += stepX;
                side = 0;
            }
            else
            {
                rayDistance.y += dRayDistance.y;
                mapY += stepY;
                side = 1;
            }
            
            if (map[mapY][mapX] > 0) hit = true;
        }
        
        if (side == 0)
        {
            wDist = fabs( (mapX-rayP.x+(1-stepX)/2)/rayD.x );
        }
        else
        {
            wDist = fabs( (mapY-rayP.y+(1-stepY)/2)/rayD.y );
        }
        
        int lineH = abs( (int)(GHEIGHT/wDist) );
        
        int drawStart = -lineH/2 + GHEIGHT/2;
        if (drawStart < 0) drawStart = 0;
        
        int drawEnd = lineH/2 + GHEIGHT/2;
        if (drawEnd >= GHEIGHT) drawEnd = GHEIGHT-1;
        
        float wallX;
        if (side==1)
            wallX = rayP.x + ( (mapY-rayP.y+(1-stepY)/2)/rayD.y )*rayD.x;
        else
            wallX = rayP.y + ( (mapX-rayP.x+(1-stepX)/2)/rayD.x )*rayD.y;
        
        wallX -= floorf(wallX);
        
        int texId = map[mapY][mapX];
        
        int texX = (int)(wallX*float(32));
        if (side==0&&rayD.x>0) texX = 32-texX-1;
        if (side==1&&rayD.y<0) texX = 32-texX-1;
        
        //Render Texture
        for (int y=drawStart; y<drawEnd; y++)
        {
            int d = y*256-GHEIGHT*128+lineH*128;
            int texY = ((d*32)/lineH)/256;
            
            Uint32 color = tex[texId-1]->pixels[32*texY+texX];
            if (side==1) color = (color>>1)&0x7f7f7f;
            
            screenBuffer[y*GWIDTH+x] = color;
        }
        
        //Set ZBuffer
        zBuffer[x] = wDist;
        
        //Floor Casting
        double floorXWall, floorYWall;
        
        if (side==0&&rayD.x > 0)
        {
            floorXWall = mapX;
            floorYWall = mapY+wallX;
        }
        else if (side==0&&rayD.x < 0)
        {
            floorXWall = mapX + 1.0f;
            floorYWall = mapY + wallX;
        }
        else if (side==1&&rayD.y > 0)
        {
            floorXWall = mapX+wallX;
            floorYWall = mapY;
        }
        else //if (side==1&&rayD.y < 0)
        {
            floorXWall = mapX + wallX;
            floorYWall = mapY + 1.0f;
        }
        
        double distWall, distPlayer, currentDist;
        
        distWall = wDist;
        distPlayer = 0.0;
        
        if (drawEnd < 0) drawEnd = GHEIGHT;
        
        for (int y=drawEnd; y<GHEIGHT; y++)
        {
            currentDist = GHEIGHT / (2.0f * y - GHEIGHT);
            
            float weight = (currentDist-distPlayer)/(distWall-distPlayer);
            
            float currentFloorX = weight*floorXWall+(1.0f-weight) * player.x;
            float currentFloorY = weight*floorYWall+(1.0f-weight) * player.y;
            
            int floorTexX, floorTexY;
            floorTexX = (int)(currentFloorX*32) % 32;
            floorTexY = (int)(currentFloorY*32) % 32;
            
            screenBuffer[y*GWIDTH+x] = (tex[2]->pixels[32*floorTexY+floorTexX] >> 1)&0x7f7f7f;
            screenBuffer[(GHEIGHT-y)*GWIDTH+x] = (tex[2]->pixels[32*floorTexY+floorTexX]);
        }
    }
    
    //int td = 4;
    
    //Render Sprite
    /*Vector2 sprite = Vector2(tex[td]->position.x,
                             tex[td]->position.y);
    
    float invDet = 1.0f / (plane.x * direction.y - direction.x * plane.y);
    
    Vector2 transform = Vector2( invDet * (direction.y*sprite.x-direction.x*sprite.y),
                                 invDet * (-plane.y*sprite.x+plane.x*sprite.y) );
    
    int spriteScreenX = int( (GWIDTH/2)*(1+transform.x/transform.y) );*/
    
    SDL_UpdateTexture(screenTex, NULL, screenBuffer, GWIDTH*sizeof(Uint32));
    SDL_RenderCopy(GameManager::Instance()->rend, screenTex, NULL, NULL);
    
    //printf("Scene3d Rendering\n");
}

void Scene3d::CleanUp()
{
    /*for (std::vector<GameObject>::size_type i=0; i<objects.size(); i++)
    {
        objects[i]->CleanUp();
        delete objects[i];
    }
    objects.clear();
    
    if (tileMap != NULL)
    tileMap->CleanUp();
    
    delete tileMap;*/
}