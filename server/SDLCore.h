#ifndef _SDL_CORE
#define _SDL_CORE

#include <SDL.h>
#include <vector>
#include "SDL_Image.h"
#include "SDL_ttf.h"
#include <string>
#include <unordered_map>

class resHandler;

extern SDL_Window* mainwin;
extern SDL_Surface* mainsurface;
extern SDL_Renderer* mainren;
extern TTF_Font* mainfont;

SDL_Texture* loadTexture(const std::string& path);

SDL_Texture* loadTexture(const std::string& path); //Prepares a texture. Takes an outside image file path.

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, double x, double y);

void renSpec(SDL_Renderer* ren, SDL_Texture* texs, int w, int h, double x, double y);

void renAngle(SDL_Renderer*, SDL_Texture*, double, double, double, double, double, SDL_Point*, SDL_RendererFlip);

void create_texture_list();

void renSpec(SDL_Renderer* ren, SDL_Texture* texs, int w, int h, double x, double y, SDL_RendererFlip);

bool initSdl();

SDL_Texture* loadText(const std::string, SDL_Color, double, double, int, int);

bool load_textures_from_file();

#endif