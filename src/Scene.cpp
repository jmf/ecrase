/*
* Copyright (C) 2014 jmf
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
* and associated documentation files (the "Software"), to deal in the Software without restriction, 
* including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
* and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT 
* NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Scene.h"
#include "Script.h"
#include "Video.h"

enum def{
  RMEDEF,
  ETYDEF,
  SCRDEF
};

Room rme;
Entity ety[5];
Script* scr;

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::loadRoom(std::string filename, Video* vid)
{

  scr->openScript(filename, &rme, ety, RMEDEF);
  for(int n=0; n<rme.animcount; n++){
    rme.fgd[n]=vid->loadImage(rme.fgdfile[n]);
    rme.bgd[n]=vid->loadImage(rme.bgdfile[n]);
  }

  for(int n=0; (ety[n].exists==true)&&(n<=4); n++){
    scr->openScript(ety[n].scriptname, &rme, ety, ETYDEF);
    for(int imgnr=0; imgnr<ety[n].animcount; imgnr++){
      ety[n].entimg[imgnr]=vid->loadImage(ety[n].imgname[imgnr]);
    }
  }
}


void Scene::placeLayers(Video* vid)
{
  SDL_Rect dst;

  SDL_RenderCopy(vid->rdr, rme.bgd[0], NULL, NULL);

  for(int n=0; (ety[n].exists==true)&&(n<=4); n++){
    dst.x=ety[n].xpos;//Position
    dst.y=ety[n].ypos;//Position
    SDL_QueryTexture(ety[n].entimg[0], NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(vid->rdr, ety[n].entimg[0], NULL, &dst);
  }

  SDL_RenderCopy(vid->rdr, rme.fgd[0], NULL, NULL);
}

/*
TODO: Add objects
*/

