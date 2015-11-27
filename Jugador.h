#ifndef JUGADOR_H
#define JUGADOR_H

#include <list>
#include <SDL_ttf.h>
#include "Personaje.h"
#include "Proyectil.h"
#include "Sonido.h"

class Jugador : public Personaje
{
    public:
        Sonido* push;
        int vidas;
        int proyectil_cooldown;
        Jugador(list<Entidad*>* entidades,SDL_Renderer* renderer);
        virtual ~Jugador();
        void logica();
        void logicaPush();
        void dibujar();

        void killsHUD(SDL_Renderer* gRenderer);
        void renderKillsHUD(SDL_Renderer* gRenderer);
        void actualizarHUD(SDL_Renderer* gRenderer);
        SDL_Surface* textSurface;
        SDL_Rect textRect;
        SDL_Texture* text;
        TTF_Font *gFont;
        SDL_Color color;

        const char* labels;

    protected:
    private:
};

#endif // JUGADOR_H
