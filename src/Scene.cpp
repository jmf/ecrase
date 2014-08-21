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
#include <fstream>
#include "Scene.h"
#include "Room.h"
#include "Video.h"

enum def{
  RMEDEF,
  ETYDEF
};

using namespace std;

Room rme;

Scene::Scene()
{
}


Scene::~Scene()
{
}


void Scene::loadRoom(string filename, Video* vid){
  rme.loadRoom(filename, RMEDEF);

  for(int n=0; n<rme.animcount; n++){
    rme.fgd[n]=vid->loadImage(rme.fgdfile[n]);
    rme.bgd[n]=vid->loadImage(rme.bgdfile[n]);
  }

  for(int n=0; ((n<=4)&&(rme.ety[n].exists)); n++){
    for(int imgnr=0; imgnr<rme.ety[n].animcount; imgnr++){
      rme.ety[n].entimg[imgnr] = vid->loadImage(rme.ety[n].imgname[imgnr]);
    }
  }
}


void Scene::placeLayers(Video* vid){
  SDL_Rect dst;
  SDL_RenderCopy(vid->rdr, rme.bgd[0], NULL, NULL);

  for(int n=0; (rme.ety[n].exists==true)&&(n<=4); n++){
    dst.x=rme.ety[n].xpos;//Position x
    dst.y=rme.ety[n].ypos;//Position y
    SDL_QueryTexture(rme.ety[n].entimg[0], NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(vid->rdr, rme.ety[n].entimg[0], NULL, &dst);
  }
  SDL_RenderCopy(vid->rdr, rme.fgd[0], NULL, NULL);
}


void Scene::onClick(int x, int y, Video *vid, string parameter){
  for(int n=0; ((rme.ety[n].exists==true)&&(rme.ety[n].active==true)); n++){
    if((x>=rme.ety[n].xpos)&&(x<=rme.ety[n].xpos+rme.ety[n].xdim)&&(y>=rme.ety[n].ypos)&&(y<=rme.ety[n].ypos+rme.ety[n].ydim)){
      Scene::parseScript(n, parameter, vid);
    }
  }
}

void Scene::parseScript(int n, string action, Video* vid){
  string input="";
  string id="";
  string value="";
  int strpos;

  fstream script;
  script.open(("../data/scene/"+rme.ety[n].scriptname).c_str());
  if(!script.is_open())
  {
    cout<<"ERROR: Could not read script: "<<rme.ety[n].scriptname<<endl;
  }
  while((script.eof()==false)&&(input!=action)){
    getline(script,input);
  }

  while((script.eof()==false)&&(input!="endscr:")){
    getline(script, input);

    strpos=input.find(":");
    id = input.substr(0, strpos);
    value = input.substr(strpos+1, 50);

    if(id=="write"){
      cout<<value<<endl;
    }
    else if(id=="chroom"){
      Scene::loadRoom(value, vid);
    }
    else if(id=="endscr"){
      //End.
    }
    else{
      cout<<"Scene|Script -> Unrecognized Command:" <<id<<endl;
    }
  }
  script.close();
  
}


