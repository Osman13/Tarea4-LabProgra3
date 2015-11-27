#ifndef PERSONAJE_H
#define PERSONAJE_H

#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<vector>
#include<map>

#include "Entidad.h"

using namespace std;

class Personaje : public Entidad
{
    public:
        SDL_Renderer* renderer;
        map<string,vector<SDL_Texture*> >textures;
        string state;
        SDL_Rect rect;
        int current_texture;
        int frames;
        double x, y;
        double velocity;
        int animation_velocity;
        int push_amount;
        string push_orientation;
        Personaje();
        virtual ~Personaje();
        virtual void dibujar();
    protected:
    private:
};

#endif // PERSONAJE_H
