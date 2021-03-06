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
#include <stdlib.h>
#include <string>
#include <vector>
#include "Room.h"

using namespace std;

Room::Room(){
}

Room::~Room(){
}

vector<int> Room::getEntids(int roomid){
	return rmdf[roomid].entid;
}

string Room::getFgd(int roomid){
	if(roomid>rmdf.size()){
		cout<<"Room does not exist"<<endl;
		exit(1);
	}
	return rmdf[roomid].fgd;
}

string Room::getBgd(int roomid){
	if(roomid>rmdf.size()){
		cout<<"Room does not exist"<<endl;
		exit(1);
	}
	return rmdf[roomid].bgd;
}

void Room::parseRmeDef(){
	
	RoomDef tmprd;
	ifstream roomfile;
	int strpos=0;
	bool end=false;
	string line;
	roomfile.open("../data/scene/rmedef");
	
	if(!roomfile.is_open()){
		cout<<"Could not open room definition."<<endl;
		exit(1);
	}

	rmdf.reserve(10); //Allocate some memory. Adjust up to prevent high delays caused by many allocations.
	
	while(getline(roomfile, line)){
		end=false;
		tmprd.entid.resize(0);
		
		//Human readable information:
		
		strpos = line.find("|");
		//The ID is never used, it only makes it easier for humans to find the out the item numbers
		line = line.substr(strpos+1, 255);

		strpos = line.find("|");
		string name = line.substr(0, strpos);
		line = line.substr(strpos+1, 255);

		//Images:		
		strpos = line.find("|");
		string bgd = line.substr(0, strpos);
		line = line.substr(strpos+1, 255);
		
		strpos = line.find("|");
		string fgd = line.substr(0, strpos);
		line = line.substr(strpos+1, 255);
		
		//Objects:
		while(end==false){
			strpos = line.find("|");
			if(line.substr(0, strpos)!=";"){
				int objid = stoi(line.substr(0, strpos), NULL, 10);
				line = line.substr(strpos+1, 255);
				tmprd.entid.push_back(objid);
			}
			else{
				end=true;
			}
		}
		tmprd.name = name;
		tmprd.bgd=bgd;
		tmprd.fgd=fgd;
		rmdf.push_back(tmprd);
		tmprd.fgd.resize(0);
		tmprd.bgd.resize(0);
	}
	cout<<"Loaded "<<rmdf.size()<<" rooms."<<endl;
	roomfile.close();
}

