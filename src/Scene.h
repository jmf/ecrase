/*
* Copyright (C) 2014, 2015 jmf
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
#include <string>
#include <time.h>
#include <vector>
#include "Entity.h"
#include "Room.h"
#include "Video.h"

#ifndef _SCENE_H_
#define _SCENE_H_

struct Currentety{
	int counter;
	EntityDef edf;
	std::vector<SDL_Texture*> anim;
};

class Scene
{
public:
	Scene();
	~Scene();
	void loadRoom(int id, Video* vid);
	void placeLayers(Video* vid);
	void onClick(int x, int y, Video* vid, int action);
	void parseEtyScript(std::string filename, int section);
private:
	Room rme;
	Entity ety;
	std::vector<Currentety> rmety;
	SDL_Texture* fgd;
	SDL_Texture* bgd;
	timespec timer;
	timespec old;
	int rmenr;
	bool clock_reset;
	bool showInventory;
};

#endif //_SCENE_H_

