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

#define RMEDEF 0
#define ETYDEF 1
#define SCRIPT 2

using namespace std;

int Script::entnr=0;

void Script::openScript(string filename, struct Room *room, struct Entity *ety, int mode)
{
  string input;
  string type;
  fstream script;

  if(mode==RMEDEF){
    type="rooms";
  }

  else{
    type="entities";
  }

  script.open(("../data/"+type+"/"+filename).c_str());
  if(!script.is_open())
  {
    cout<<"ERROR: Could not read script: "<<filename<<endl;
  }
  getline(script, input);
  if(mode==RMEDEF){
    while(script.eof()==false){
      getline(script, input);
      parseRoom(input, room, ety);
    }
  }

  else if(mode==ETYDEF){
    Script::entnr=0;
    for(int n; n<=4; n++){
      ety[n].exists=0;
    }
    while(script.eof()==false){
      getline(script, input);
      parseEntity(input, ety);
    }
  }

  else if(mode==SCRIPT){
    while(script.eof()==false){
      getline(script, input);
      parseEntity(input, ety);
    }
  }

  else
  {
    cout<<"ERROR: Bad Read Code"<<std::endl;
  }
  script.close();

}



void Script::parseRoom(std::string line, struct Room *room, struct Entity *ety)
{
  int strpos=line.find(":");
  string id=line.substr(0, strpos);
  string value=line.substr(strpos+1, 50);

  if(id=="bgd"){ //Load room background
    room->bgdfile=value;
  }

  else if(id=="fgd"){ //Load room foreground
    room->fgdfile=value;
  }

  else if(id=="object"){ //Load object filename
    ety[Script::entnr].scriptname=value;
    ety[Script::entnr].exists=true;
    cout<<"Script added: "<<ety[Script::entnr].scriptname<<endl;
    Script::entnr++;
    //TODO: Make it abort!
    if(Script::entnr>4){
      cout<<"CRITICAL ERROR: ENTITIY ARRAY OUT OF BOUNDS (Script::parseRoom)"<<endl;
      Script::entnr=0;//Quick fix. Not permanent.
    }
  }

  else if((id=="#")||(id=="")){ //Ignore comment or empty
  }
   
  else{ //Wrong formatting
    cout<<"ERROR: Bad formatting @ "<<line<<endl;
  }
}


void Script::parseEntity(std::string line, struct Entity *ety)
{
  int strpos=line.find(":");
  string id=line.substr(0, strpos);
  string value=line.substr(strpos+1, 50);

  if(id=="image"){ //Load object image
    ety[Script::entnr].imgname=value;
  }

  else if(id=="visible"){ //Visible?
    if(value=="true"){
      ety[Script::entnr].visible=true;
    }
    else{
      ety[Script::entnr].visible=false;
    }
  }

  else if(id=="active"){ //Active?
    ety[Script::entnr].exists=true;
    if(value=="true"){
      ety[Script::entnr].active=true;
    }
    else{
      ety[Script::entnr].active=false;
    }
  }

  else if(id=="xpos"){ //x position
    ety[Script::entnr].xpos=Str2Uint(value);
  }

  else if(id=="ypos"){ //x position
    ety[Script::entnr].ypos=Str2Uint(value);
  }

  else if(id=="xdim"){ //x position
    ety[Script::entnr].xdim=Str2Uint(value);
  }

  else if(id=="ydim"){ //x position
    ety[Script::entnr].ydim=Str2Uint(value);
  }

  else if((id=="#")||(id=="")){ //Ignore comment or empty
  }
   
  else{ //Wrong formatting
    cout<<"ERROR: Bad formatting @ "<<line<<endl;
  }
}

uint Script::Str2Uint(string input){//TODO: Maybe make it less hacky
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

