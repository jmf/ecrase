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

using namespace std;

void Script::openScript(string filename, struct Room *room)
{
	string input;
	fstream script;
	script.open(("../data/script/"+filename).c_str());
	if(!script.is_open())
	{
		cout<<"Could not read script: "<<filename<<endl;
	}
	getline(script, input);
	if(input=="room")   //TODO:FIX THIS
	{
    while(script.eof()==false){
			getline(script, input);
			parseRoom(input, room);
		}
	}
	else
	{
		cout<<"ERROR: Wrong header"<<std::endl;
	}
}

void Script::parseRoom(std::string line, struct Room *room)
{
	int strpos=line.find(":");
	string id=line.substr(0, strpos);
	string value=line.substr(strpos+1, 50);

	if(id=="#"){
		std::cout<<value<<endl; //Display comment
	}
	else if(id=="bgd"){
    room->bgdfile=value;
	}
	else if(id=="fgd"){
    room->fgdfile=value;
  }	
}

/*
TODO:
-Seperate parser for rooms and objects
-Although that, use as much shared code as possible
*/

