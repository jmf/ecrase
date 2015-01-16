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

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <string>
#include "Video.h"

Video::Video(){
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0){ //Initialize everything
		std::cout<<"Initializing SDL failed"<<std::endl;
		exit(1);
	}
}

Video::~Video(){
	SDL_DestroyRenderer(rdr);
	SDL_DestroyWindow(window);
}

void Video::createWindow(std::string projectname, int width, int height){
	Video::window = SDL_CreateWindow(projectname.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN);
	if(!window){
		std::cout<<"Window creation failed."<<std::endl;
		exit(1);
	}
}


void Video::createRenderer(){
	rdr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!rdr){
		std::cout<<"Renderer could not be created."<<std::endl;
		exit(1);
	}
}

SDL_Texture* Video::loadImage(std::string filename){
	SDL_Surface *tmp = IMG_Load(("../data/images/"+filename).c_str());
	if(!tmp){
		std::cout<<"Could not load image: "<<filename<<std::endl;
		exit(1);
	}
	SDL_Texture *ret = SDL_CreateTextureFromSurface(rdr, tmp);
	SDL_FreeSurface(tmp);
	return ret;
}

void Video::renderScreen(){
	SDL_RenderPresent(rdr);
}

