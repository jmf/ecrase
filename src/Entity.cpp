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
#include "Entity.h"

using namespace std;

Entity::Entity(){
}

Entity::~Entity(){
}

EntityDef Entity::getEty(int id){
	return etydf[id];
}

void Entity::parseEtyDef(){

	ifstream entityfile;
	int strpos=0;
	string line;
	entityfile.open("../data/scene/etydef");
	
	if(!entityfile.is_open()){
		cout<<"Could not open entity definition."<<endl;
		exit(1);
	}

	etydf.reserve(10); //Allocate some memory. Adjust up to prevent high delays caused by many allocations.

	while(getline(entityfile, line)){
		EntityDef tmped;
		bool end=false;
		strpos = line.find("|");
		string id = line.substr(0, strpos);
		line = line.substr(strpos+1, 255);

		strpos = line.find("|");
		string name = line.substr(0, strpos);
		line = line.substr(strpos+1, 255);

		//Position:		
		strpos = line.find("|");
		int xpos = stoi(line.substr(0, strpos), NULL, 10);
		line = line.substr(strpos+1, 255);
		
		strpos = line.find("|");
		int ypos = stoi(line.substr(0, strpos), NULL, 10);
		line = line.substr(strpos+1, 255);

		//Size:
		strpos = line.find("|");
		int xdim = stoi(line.substr(0, strpos), NULL, 10);
		line = line.substr(strpos+1, 255);
		
		strpos = line.find("|");
		int ydim = stoi(line.substr(0, strpos), NULL, 10);
		line = line.substr(strpos+1, 255);

		//Animation:

		while(end==false){
			strpos = line.find("|");
			if(line.substr(0, strpos)!=";"){
				string frame = line.substr(0, strpos);
				line = line.substr(strpos+1, 255);
				tmped.frame.push_back(frame);
			}
			else{
				end=true;
			}
		}
		
		tmped.name = name;
		tmped.xpos=xpos;
		tmped.ypos=ypos;
		tmped.xdim=xdim;
		tmped.ydim=ydim;
		
		etydf.push_back(tmped);
	}
	cout<<"Loaded "<<etydf.size()<<" entities."<<endl;
	entityfile.close();
}

