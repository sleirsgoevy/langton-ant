#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cstdlib>
#include <SDL/SDL.h>

using namespace std;

class GUI
{
    SDL_Surface* surf;
    int width;
    int height;
    int currKey;
    SDL_Event event;
public:
    GUI(const char* options)
    {
        if(options != NULL)
        {
            istringstream sin(string(options));
            int w = -1;
            char x = -1;
            int h = -1;
            sin >> w >> x >> h;
            if(w <= 0 || h <= 0 || x != 'x')
            {
                cerr << "Cannot parse resolution: " << options << endl;
                exit(1);
            }
            width = w;
            height = h;
        }
        else
        {
            width = 1024;
            height = 768;
        }
        SDL_Init(SDL_INIT_EVERYTHING);
        surf = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    }
    void getSize(int&, int&);
    void putpixel(int, int, int);
    void flip();
    void wait();
    int getKey();
    void getMouse(int&, int&, int&);
};

void GUI::getSize(int& w, int& h)
{
    w = width;
    h = height;
}

void GUI::putpixel(int x, int y, int value)
{
    int* surf = (int*)surf->pixels;
    surf[y * width + x] = value;
}

void GUI::flip()
{
    SDL_Flip(surf);
}

void GUI::wait()
{
    SDL_PollEvent(&event);
    if(event.type == SDL_KEYDOWN)
        currKey = event.key.keysym.sym;
    if(event.type == SDL_KEYUP)
        currKey = -1;
}

int GUI::getKey()
{
    return currKey;
}

void GUI::getMouse(int& x, int& y, int& btn)
{
    x = 0;
    y = 0;
    btn = 0;
}
}

GUI* new_gui(const char* options)
{
    return new GUI(options);
}
