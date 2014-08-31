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

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <leveldb/db.h>
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


void Scene::loadRoom(leveldb::Slice id, Video* vid){
  rme.loadDef(id, RMEDEF);

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


void Scene::onClick(int x, int y, Video *vid, int action){
  for(int n=0; ((rme.ety[n].exists==true)&&(rme.ety[n].active==true)); n++){
    if((x>=rme.ety[n].xpos)&&(x<=rme.ety[n].xpos+rme.ety[n].xdim)&&(y>=rme.ety[n].ypos)&&(y<=rme.ety[n].ypos+rme.ety[n].ydim)){
      Scene::parseScript(n, action, vid);
    }
  }
}

void Scene::parseScript(int n, int action, Video* vid){

  string scrname = rme.ety[n].scriptname;
  string value="";
  string scrline="";
  string id="";
  string command="";
  int strpos=0;

  leveldb::Status state;
  if(action==1){
    state = rme.etydb->Get(leveldb::ReadOptions(), (scrname+"_script1").c_str(), &value);
  }
  else if(action==2){
    state = rme.etydb->Get(leveldb::ReadOptions(), (scrname+"_script2").c_str(), &value);
  }
  else{
    cout<<"ERROR: No valid action"<<endl;
  }

  for(n=0; (value!="NULL:NULL")&&(value!=""); n++){

    strpos=value.find("|");
    scrline = value.substr(0, strpos);
    value = value.substr(strpos+1, 255);

    strpos=scrline.find(":");
    id = scrline.substr(0, strpos);
    command = scrline.substr(strpos+1, 50);

    if(id=="write"){
      cout<<command<<endl;
    }
    else if(id=="chroom"){
      Scene::loadRoom(command, vid);
    }
    else{
      cout<<"ERROR: No valid script"<<endl;
      cout<<value;
    }
  }
}


