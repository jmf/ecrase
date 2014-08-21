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
#include "Video.h"

#ifndef _SCRIPT_H_
#define _SCRIPT_H_

struct Entity{
  int animcount;
  std::string scriptname;
  bool exists;//Does actually exist
  bool visible;//Is visible on the screen
  bool active;//Is clickable on the screen
  int xpos;//x coordinate
  int ypos;//y coordinate
  int xdim;//width
  int ydim;//length
  SDL_Texture *entimg[5];//Images
  std::string imgname[5];
};

class Room{

 public:
  int animcount;
  std::string fgdfile[5];
  std::string bgdfile[5];
  SDL_Texture *fgd[5];//Foreground image
  SDL_Texture *bgd[5];//Background image
  Entity ety[5];
  int etynr;

  void loadRoom(std::string scriptname, int defval);
  void parseRoom(std::string id, std::string value);
  void parseEntity(std::string id, std::string value);
  SDL_Texture* loadImage(std::string filename);
 private:
  int Str2Int(std::string input);
};

#endif //_SCRIPT_H_
