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
#include <leveldb/db.h>
#include "Room.h"

enum def{
  RMEDEF,
  ETYDEF
};

using namespace std;

Room::Room(){
  Room::dbopt.create_if_missing = true;
  leveldb::Status rmestatus = leveldb::DB::Open(dbopt, "../data/scene/rooms", &rmedb);
  leveldb::Status etystatus = leveldb::DB::Open(dbopt, "../data/scene/entities", &etydb);
}


Room::~Room(){
  delete rmedb;
  delete etydb;
}


void Room::loadDef(leveldb::Slice id, int defval)
{


  if(defval==RMEDEF){
    for(int n=0; ety[n].exists!=false; n++){
      Room::ety[n].exists=false;
    }
    Room::etynr=0;
    Room::parseRoom(id);
  }
  else if(defval==ETYDEF){
    Room::parseEntity(id);
    Room::ety[Room::etynr].exists=true;
    Room::etynr++;
  }
  else{
    cout<<"ERROR: Undefined definition ID"<<endl;
  }
}


void Room::parseRoom(leveldb::Slice id){
  std::string value;
  std::string strid = id.ToString();

  leveldb::Status state = rmedb->Get(leveldb::ReadOptions(), id, &value);
  
  state = rmedb->Get(leveldb::ReadOptions(), (strid+"_ac").c_str(), &value);
  Room::animcount = Str2Int(value);

  state = rmedb->Get(leveldb::ReadOptions(), (strid+"_fgd").c_str(), &value);
  Room::fgdfile[0] = value;

  state = rmedb->Get(leveldb::ReadOptions(), (strid+"_bgd").c_str(), &value);
  Room::bgdfile[0] = value;

  state = rmedb->Get(leveldb::ReadOptions(), (strid+"_obj0").c_str(), &value);
  if(value!="NULL"){
    loadDef(value, ETYDEF);
  }
  state = rmedb->Get(leveldb::ReadOptions(), (strid+"_obj1").c_str(), &value);
  if(value!="NULL"){
    loadDef(value, ETYDEF);
  }
  state = rmedb->Get(leveldb::ReadOptions(), (strid+"_obj2").c_str(), &value);
  if(value!="NULL"){
    loadDef(value, ETYDEF);
  }
  state = rmedb->Get(leveldb::ReadOptions(), (strid+"_obj3").c_str(), &value);
  if(value!="NULL"){
    loadDef(value, ETYDEF);
  }  
  state = rmedb->Get(leveldb::ReadOptions(), (strid+"_obj4").c_str(), &value);
  if(value!="NULL"){
    loadDef(value, ETYDEF);
  }
}


void Room::parseEntity(leveldb::Slice id)
{
  std::string value;
  std::string strid = id.ToString();
  Room::ety[Room::etynr].scriptname = strid;

  leveldb::Status state = etydb->Get(leveldb::ReadOptions(), (strid+"_ac").c_str(), &value);
  Room::ety[Room::etynr].animcount = Str2Int(value);

  state = etydb->Get(leveldb::ReadOptions(), (strid+"_img0").c_str(), &value);
  Room::ety[Room::etynr].imgname[0] = value;

  state = etydb->Get(leveldb::ReadOptions(), (strid+"_vis").c_str(), &value);
  if(value=="true"){
    Room::ety[Room::etynr].visible = true;
  }
  else{
    Room::ety[Room::etynr].visible = false;
  }

  state = etydb->Get(leveldb::ReadOptions(), (strid+"_act").c_str(), &value);
  if(value=="true"){
    Room::ety[Room::etynr].active = true;
  }
  else{
    Room::ety[Room::etynr].active = false;
  }

  state = etydb->Get(leveldb::ReadOptions(), (strid+"_xpos").c_str(), &value);
  Room::ety[Room::etynr].xpos = Str2Int(value);

  state = etydb->Get(leveldb::ReadOptions(), (strid+"_ypos").c_str(), &value);
  Room::ety[Room::etynr].ypos = Str2Int(value);

  state = etydb->Get(leveldb::ReadOptions(), (strid+"_xdim").c_str(), &value);
  Room::ety[Room::etynr].xdim = Str2Int(value);

  state = etydb->Get(leveldb::ReadOptions(), (strid+"_ydim").c_str(), &value);
  Room::ety[Room::etynr].ydim = Str2Int(value);
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

