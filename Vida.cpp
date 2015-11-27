#include "Vida.h"

Vida::Vida(list<Entidad*>* entidades,SDL_Renderer* renderer)
{
    this->entidades = entidades;
    this->renderer = renderer;
    texture = IMG_LoadTexture(renderer,"corazon.png");
    rect.x=0;
    rect.y=0;
    SDL_QueryTexture(texture,NULL,NULL,&rect.w,&rect.h);

    for(list<Entidad*>::iterator e=entidades->begin();
        e!=entidades->end();
        e++)
    {
        if((*e)->tipo=="Jugador")
        {
            jugador = (Jugador*)*e;
        }
    }
    capa=1;
}

Vida::~Vida()
{
    //dtor
}

void Vida::dibujar()
{
    SDL_Rect rect_aux = rect;
    for(int i=0;i<jugador->vidas;i++)
    {
        rect_aux.x+=rect_aux.w;
        SDL_RenderCopy(renderer,texture,NULL,&rect_aux);
    }
    cout<<"dibujando"<<endl;
}

void Vida::logica()
{

}
