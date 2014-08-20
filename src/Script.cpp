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

#include <string>
#include <fstream>
#include <iostream>
#include "Script.h"
#include "Scene.h"

enum def{
  RMEDEF,
  ETYDEF,
  SCRDEF
};

using namespace std;

int Script::entnr=0;


void Script::openScript(string filename, struct Room *room, struct Entity *ety, int mode)
{
  Script::entnr=0;
  string input;
  string id;
  string value;
  int strpos;

  fstream script;
  script.open(("../data/scene/"+filename).c_str());
  if(!script.is_open())
  {
    cout<<"ERROR: Could not read script: "<<filename<<endl;
  }
  while(script.eof()==false){
    getline(script, input);

    strpos=input.find(":");
    id = input.substr(0, strpos);
    value = input.substr(strpos+1, 50);

    if(mode==RMEDEF){
      parseRoom(id, value, room, ety);
    }
    else if (mode==ETYDEF){
      parseEntity(id, value, ety);
    }
  }
  script.close();
}


void Script::parseRoom(string id, string value, struct Room *rme, struct Entity *ety)
{
  if(id=="animcount"){
    rme->animcount=Str2Int(value);
  }
  else if(id=="fgd"){
    rme->fgdfile[0]=value;
  }
  else if(id=="bgd"){
    rme->bgdfile[0]=value;
  }
  else if(id=="object"){
    ety[Script::entnr].scriptname=value;
    ety[Script::entnr].exists=true;
    Script::entnr++;
    //TODO: Handle overflow
  }
  else if(id==""||id=="#"){
    //Comment or empty line
  }
  else{
    cout<<"Room -> Unrecognized Command:" <<id<<endl;
  }
}


void Script::parseEntity(string id, string value, struct Entity *ety)
{
  if(id=="animcount"){
    ety->animcount=Str2Int(value);
  }
  else if(id=="image"){
    ety->imgname[0]=value;
  }
  else if(id=="visible"){
    if(value=="true"){
      ety->visible=true;
    }
    else{
      ety->visible=false;
    }
  }
  else if(id=="active"){
    if(value=="true"){
      ety->active=true;
    }
    else{
      ety->active=false;
    }
  }
  else if(id=="xpos"){
    ety->xpos=Str2Int(value);
  }
  else if(id=="ypos"){
    ety->ypos=Str2Int(value);
  }
  else if(id=="xdim"){
    ety->xdim=Str2Int(value);
  }
  else if(id=="ydim"){
    ety->ydim=Str2Int(value);
  }
  else if(id==""||id=="#"){
    //Comment or empty line
  }
  else{
    cout<<"Ety -> Unrecognized Command:" <<id<<endl;
  }
}


int Script::Str2Int(string input){//TODO: Maybe make it less hacky
  uint multiplicator=1;
  int output=0;
  for(int n=input.size()-1; n>=0; n--){
    output=output+(input[n]-48)*multiplicator;
    multiplicator=multiplicator*10;
  }
  return output;
}


/*
TODO:
-Add script parser for entity scripts
-Exception handling!!!
*/

