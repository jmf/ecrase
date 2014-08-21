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
#include "Room.h"

enum def{
  RMEDEF,
  ETYDEF
};

using namespace std;


void Room::loadRoom(string filename, int defval)
{
  string input;
  string id;
  string value;
  int strpos;
  bool stopread=false;

  fstream script;
  script.open(("../data/scene/"+filename).c_str());

  if(!script.is_open())
  {
    cout<<"ERROR: Could not read def: "<<filename<<endl;
  }

  if(defval==RMEDEF){
    Room::etynr=0;
    for(int n=0; n<=4; n++){//Delete previous objects
      Room::ety[n].exists = false;
    }
  }

  while(script.eof()==false && stopread==false){
    getline(script, input);

    strpos = input.find(":");
    id = input.substr(0, strpos);
    value = input.substr(strpos+1, 50);

    if(defval==RMEDEF){
      Room::parseRoom(id, value);
    }
    else if (defval==ETYDEF){
      if((id=="on_look")||(id=="on_interact")){
        stopread=true;
      }
      else{
        Room::parseEntity(id, value);
      }
    }
    else{
      cout<<"ERROR: Def called with wrong args"<<endl;
    }
  }

  if (defval==ETYDEF){
    Room::etynr++;
  }

  script.close();
}


void Room::parseRoom(string id, string value){
  if(id=="animcount"){
    Room::animcount = Str2Int(value);
  }
  else if(id=="fgd"){
    Room::fgdfile[0] = value;
  }
  else if(id=="bgd"){
    Room::bgdfile[0] = value;
  }
  else if(id=="object"){
    Room::ety[Room::etynr].scriptname = value;
    Room::ety[Room::etynr].exists = true;
    Room::loadRoom(value, ETYDEF);
    //TODO: Handle overflow
  }
  else if(id==""||id=="#"){
    //Comment or empty line
  }
  else{
    cout<<"Room -> Unrecognized Command:" <<id<<endl;
  }
}


void Room::parseEntity(string id, string value)
{
  if(id=="animcount"){
    Room::ety[Room::etynr].animcount = Str2Int(value);
  }
  else if(id=="image"){
    Room::ety[Room::etynr].imgname[0] = value;
  }
  else if(id=="visible"){
    if(value=="true"){
      Room::ety[Room::etynr].visible = true;
    }
    else{
      Room::ety[Room::etynr].visible = false;
    }
  }
  else if(id=="active"){
    if(value=="true"){
      Room::ety[Room::etynr].active = true;
    }
    else{
      Room::ety[Room::etynr].active = false;
    }
  }
  else if(id=="xpos"){
    Room::ety[Room::etynr].xpos = Str2Int(value);
  }
  else if(id=="ypos"){
    Room::ety[Room::etynr].ypos = Str2Int(value);
  }
  else if(id=="xdim"){
    Room::ety[Room::etynr].xdim = Str2Int(value);
  }
  else if(id=="ydim"){
    Room::ety[Room::etynr].ydim = Str2Int(value);
  }
  else if(id==""||id=="#"){
    //Comment or empty line
  }
  else{
    cout<<"Ety -> Unrecognized Command:" <<id<<endl;
  }
}


int Room::Str2Int(string input){//TODO: Maybe make it less hacky
  int multiplicator = 1;
  int output = 0;
  for(int n =input.size()-1; n>=0; n--){
    output=output+(input[n]-48)*multiplicator;
    multiplicator=multiplicator*10;
  }
  return output;
}


/*
TODO:
-Exception handling!!!
*/

