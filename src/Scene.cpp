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

#include <fstream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <time.h>
#include <vector>
#include "Entity.h"
#include "Scene.h"
#include "Video.h"

using namespace std;

Scene::Scene(){
	clock_reset=true;
	rme.parseRmeDef();
	ety.parseEtyDef();
}

Scene::~Scene(){
}


void Scene::loadRoom(int id, Video* vid){
	rmety.resize(0);//Delete previous room information
	rmenr=id;
	fgd=vid->loadImage(rme.getFgd(id));
	bgd=vid->loadImage(rme.getBgd(id));
	for(int n=0; n<rme.getEntids(rmenr).size(); n++){
		Currentety tmpety;
		int i=rme.getEntids(rmenr)[n];
		tmpety.edf = ety.getEty(i);//Get entities that are in the room
		for(int img=0; img<tmpety.edf.frame.size(); img++){
			tmpety.anim.push_back(vid->loadImage(tmpety.edf.frame[img]));
		}
		rmety.push_back(tmpety);
	}
}


void Scene::placeLayers(Video* vid){
	int animnr;
	SDL_Rect dst;
	SDL_RenderCopy(vid->rdr, bgd, NULL, NULL);
	
	clock_gettime(CLOCK_MONOTONIC, &timer);//Time animations
	if((timer.tv_nsec>=(old.tv_nsec+200000000))||(timer.tv_sec>=(old.tv_sec+1))){//200ms per frame
		clock_reset=true;
		for(int n=0; n<rmety.size(); n++){
			rmety[n].counter++;
		}
	}

	if(clock_reset==true){
		clock_gettime(CLOCK_MONOTONIC, &old);
		clock_reset=false;
	}

	for(int n=0; n<rmety.size(); n++){
		if(rmety[n].counter>=rmety[n].anim.size()){
			rmety[n].counter=0;
		}
		animnr=rmety[n].counter;
		dst.x=rmety[n].edf.xpos;//Position x
	 	dst.y=rmety[n].edf.ypos;//Position y
	 	SDL_QueryTexture(rmety[n].anim[animnr], NULL, NULL, &dst.w, &dst.h);
	 	SDL_RenderCopy(vid->rdr, rmety[n].anim[animnr], NULL, &dst);
	}
	SDL_RenderCopy(vid->rdr, fgd, NULL, NULL);

}

void Scene::parseEtyScript(string filename, int section){
	//Sections: 1-on_look ; 2-on_interact; coming soon
	//TODO: Add in real function; add script to ety
}


void Scene::onClick(int x, int y, Video *vid, int action){
	//TODO: Add real function with parseEtyScript here.
	for(int n=0; n<rmety.size(); n++){
		if((x>=rmety[n].edf.xpos)&&(x<=rmety[n].edf.xpos+rmety[n].edf.xdim)&&(y>=rmety[n].edf.ypos)&&(y<=rmety[n].edf.ypos+rmety[n].edf.ydim)){
		loadRoom(1-rmenr, vid);
		}
	}
}

