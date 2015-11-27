#ifndef VIDA_H
#define VIDA_H

#include<SDL.h>
#include<SDL_image.h>

#include "Entidad.h"
#include "Jugador.h"

using namespace std;

class Vida : public Entidad
{
    public:
        SDL_Rect rect;
        SDL_Texture* texture;
        SDL_Renderer* renderer;
        Jugador* jugador;
        Vida(list<Entidad*>* entidades,SDL_Renderer* renderer);
        void logica();
        void dibujar();
        virtual ~Vida();
    protected:
    private:
};

#endif // VIDA_H
