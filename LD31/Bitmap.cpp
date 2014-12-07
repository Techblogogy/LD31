//
//  Bitmap.cpp
//  LD31
//
//  Created by Fedor Bobylev on 12/7/14.
//  Copyright (c) 2014 Fedor Bobylev. All rights reserved.
//

#include "Bitmap.h"
#include <SDL2/SDL.h>

Bitmap::Bitmap(Vector2 p, int w, int h)
{
    position = p; //Set Position
    
    width = w; //Set Width
    height = h; //Set Height
    
    //printf("%d\n",w);
    
    pixels = new Uint32[w*h];
    
    for (int i=0; i<w*h; i++)
        pixels[i] = 0;
}

Bitmap::~Bitmap()
{
    delete[] pixels;
}

void Bitmap::GenerateXORTexture(Uint8 r, Uint8 g, Uint8 b)
{
    //printf("%d\n",h);
    
    for (int y=0; y<height; y++)
    {
        for (int x=0; x<width; x++)
        {
            Uint8 c = y^x;
            pixels[(y*width)+x] =   (Uint32)(abs(r-c)) |
                                    (Uint32)(abs(g-c)<<8) |
                                    (Uint32)(abs(b-c)<<16) |
                                    (Uint32)(255<<24);
        }
    }
}

void Bitmap::LoadTexture(std::string path)
{
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    if (!mainBundle) printf("Failed To Get Main Application Bundle \n");
    
    char* cBuf = new char[200];
    
    CFURLRef resourceUrl = CFBundleCopyResourceURL(mainBundle, CFStringCreateWithCString(NULL, path.c_str(), kCFStringEncodingASCII), NULL, NULL);
    if (!resourceUrl) printf("Failed To Get Resource Folder Path \n");
    CFURLGetFileSystemRepresentation(resourceUrl, true, (Uint8*)cBuf, 200);
    
    printf("%s\n",cBuf);
    
    //Actually Read File
    FILE* f = fopen(cBuf, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f);
    
    int size = 3*width*height;
    unsigned char* data = new unsigned char[size];
    fread(data, sizeof(unsigned char), size, f);
    fclose(f);
    
    int b = 0;
    for (int i=0; i<width*height; i++)
    {
        pixels[i] = (Uint32)(data[b]) | (Uint32)(data[b+1]<<8) | (Uint32)(data[b+2]<<16) | (Uint32)(255<<24);
        b+=3;
    }
    
    //printf("Somethibng\n");
}