#include "SDLCore.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <fstream>
#include "SDL_image.h"
#include <string>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
SDL_Renderer* mainren;
SDL_Surface* mainsurface;
TTF_Font* mainfont;
SDL_Window* mainwin;
std::vector<SDL_Texture*> textures;


SDL_Texture* loadTexture(const std::string& path) //Prepares a texture. Takes an outside image file path.
{
    SDL_Texture* newtex = NULL;

    SDL_Surface* loadedimg = IMG_Load(path.c_str());
    if (loadedimg != NULL) {
        newtex = SDL_CreateTextureFromSurface(mainren, loadedimg);
        SDL_FreeSurface(loadedimg);
        if (newtex == NULL) {
            printf("Failed to create texture from surface");
        }
    }
    else {
        printf("Failed to loadBMP");
    }
    return newtex;
}


void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, double x, double y) {
    //Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    //Query the texture to get its width and height to use
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(mainren, tex, NULL, &dst);
}

void renAngle(SDL_Renderer* ren, SDL_Texture* tex, double x, double y, double w, double h, double angle, SDL_Point* ang_pnt = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopyEx(ren, tex, NULL, &dst, angle, ang_pnt, flip);
}

void renSpec(SDL_Renderer* ren, SDL_Texture* texs, int w, int h, double x, double y) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopy(ren, texs, NULL, &rect);
}

void renSpec(SDL_Renderer* ren, SDL_Texture* texs, int w, int h, double x, double y, SDL_RendererFlip flip) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopyEx(ren, texs, NULL, &rect, NULL, NULL, flip);
}

void create_texture_list() {
    textures.resize(3);
    textures[0] = loadTexture("resources/player.png");
    textures[1] = loadTexture("resources/sword.png");
    textures[2] = loadTexture("resources/grassBackground.png");
    //textures[2] = loadTexture("player_model.png");
    //textures[3] = loadTexture("sword_model2.png");
}

bool initSdl() //Starts up the SDL library and makes sure everything is working.
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Failed to init");
        success = false;
    }
    else {
        mainwin = SDL_CreateWindow("Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640,
            480, SDL_WINDOW_SHOWN);
        if (mainwin == NULL) {
            success = false;
        }
        else {
            mainsurface = SDL_GetWindowSurface(mainwin);
        }

        mainren = SDL_CreateRenderer(mainwin, -1, SDL_RENDERER_PRESENTVSYNC);
        int imgflags = IMG_INIT_PNG;
        if (!(IMG_Init(imgflags) & imgflags)) {
            printf("Fail to init img");
            success = false;
        }
        //		if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048 ) < 0)
        //		{
        //			success = false;
        //		}
        if (mainren == NULL) {
            success = false;
        }
    }
     TTF_Init();
     mainfont = TTF_OpenFont("font.ttf", 28);
     if (!mainfont) {
         printf("Text");
         success = false;
     }
    create_texture_list();
    return success;
}

bool load_textures_from_file() {
    std::ifstream file;
    file.open("file.txt");
    if (!file.is_open()) {
        std::cout << "No file.txt detected. Please include this. Closing soon.";
        SDL_Delay(5000);
        return false;
    }
    std::string text;
    while (getline(file, text)) {
        textures.push_back(loadTexture(text.c_str()));
    }
    return true;
}

SDL_Texture* loadText(const std::string str, SDL_Color col, double x, double y, int w, int h) {
    SDL_Texture* newtex = NULL;
    SDL_Surface* loadedimg = TTF_RenderText_Solid(mainfont, str.c_str(), col);
    if (loadedimg != NULL) {
        newtex = SDL_CreateTextureFromSurface(mainren, loadedimg);
        SDL_FreeSurface(loadedimg);
        if (newtex == NULL) {
            //printf("Failed to create texture from surface");
            return NULL;
        }
    }
    else {
        printf("Failed to loadBMP");
    }
    renSpec(mainren, newtex, w, h, x, y);
    return newtex;
}
