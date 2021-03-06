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
#include "Scene.h"
#include "Video.h"

const int width = 800; //Set your custom window width here
const int height= 600; //Set your custom window height here
std::string projectname = "Ecrase engine"; //Name of your game


using namespace std;

int main(void)
{
	cout<<"ecrase version 0.0.1"<<endl;
	cout<<"  (c) 2014/15 jmf   "<<endl;

	SDL_Event event;
	bool quit=false;

	Video vid; //Video-Object handles SDL
	Scene scn;

	vid.createWindow(projectname,width, height);
	vid.createRenderer();
	scn.loadRoom(0, &vid);//Load first room for starting

	while(quit==false){//Query events
		while(SDL_PollEvent(&event)){
			if(event.type==SDL_QUIT){
				quit=true;
			}
			else if (event.type==SDL_MOUSEBUTTONDOWN){
				if(event.button.button==SDL_BUTTON_LEFT){
					scn.onClick(event.motion.x, event.motion.y, &vid, 1);
				}
				else if(event.button.button==SDL_BUTTON_RIGHT){
					scn.onClick(event.motion.x, event.motion.y, &vid, 2);
				}
			}
		}
		SDL_RenderClear(vid.rdr);
		scn.placeLayers(&vid);
		vid.renderScreen();
		SDL_Delay(40);
	}
	SDL_Quit();
}

