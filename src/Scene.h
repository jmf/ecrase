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
#include <string>
#include "Video.h"

#ifndef _SCENE_H_
#define _SCENE_H_

struct Room{
  std::string fgdfile;
  std::string bgdfile;
  SDL_Texture *fgd;//Foreground image
  SDL_Texture *bgd;//Background image
};

struct Entity{
  std::string scriptname;
  std::string imgname;
  bool exists;//Does actually exist
  bool visible;//Is visible on the screen
  bool active;//Is clickable on the screen
  uint xpos;//x coordinate
  uint ypos;//y coordinate
  uint xdim;//width
  uint ydim;//length
  SDL_Texture *entimg;//TODO: Add animation support
};


class Scene
{
public:
  Scene();
  ~Scene();
  void loadRoom(std::string filename, Video* vid);
  void placeLayers(Video* vid);

};

#endif //_SCENE_H_

