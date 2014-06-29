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

Room rme;
Script* scr;

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::loadRoom(std::string filename, Video* vid)
{

	scr->openScript(filename, &rme);

  rme.fgd=vid->loadImage(rme.fgdfile);
  rme.bgd=vid->loadImage(rme.bgdfile);

}


void Scene::placeLayers(Video* vid)
{
		SDL_RenderCopy(vid->rdr, rme.bgd, NULL, NULL);
    //TODO: Load also objects here
    SDL_RenderCopy(vid->rdr, rme.fgd, NULL, NULL);
}

/*
TODO: Add objects
*/
