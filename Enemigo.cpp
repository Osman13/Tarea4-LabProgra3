#include "Enemigo.h"

Enemigo::Enemigo(list<Entidad*>* entidades,SDL_Renderer* renderer)
{
    tipo = "Enemigo";
    this->renderer = renderer;
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "Enemigo/down1.png"));
    this->textures["down"].push_back(IMG_LoadTexture(renderer, "Enemigo/down2.png"));
    this->textures["up"].push_back(IMG_LoadTexture(renderer, "Enemigo/up1.png"));
    this->textures["up"].push_back(IMG_LoadTexture(renderer, "Enemigo/up2.png"));
    this->textures["left"].push_back(IMG_LoadTexture(renderer, "Enemigo/left1.png"));
    this->textures["left"].push_back(IMG_LoadTexture(renderer, "Enemigo/left2.png"));
    this->textures["right"].push_back(IMG_LoadTexture(renderer, "Enemigo/right1.png"));
    this->textures["right"].push_back(IMG_LoadTexture(renderer, "Enemigo/right2.png"));

    SDL_QueryTexture(this->textures["down"][0], NULL, NULL, &rect.w, &rect.h);
    x = rand()%100;
    y = rand()%100;
    rect.x=x;
    rect.y=x;

    velocity=0.5;
    animation_velocity=20;

    current_texture=0;

    state="down";

    this->entidades = entidades;

    for(list<Entidad*>::iterator e=entidades->begin();
        e!=entidades->end();
        e++)
    {
        if((*e)->tipo=="Jugador")
        {
            jugador = (Jugador*)*e;
        }
    }
}

Enemigo::~Enemigo()
{
    //dtor
}

void Enemigo::logica()
{
    if(jugador->x>x)
    {
        state="right";
    }
    if(jugador->x<x)
    {
        state="left";
    }
    if(jugador->y<y)
    {
        state="up";
    }
    if(jugador->y>y)
    {
        state="down";
    }

    if(state=="right")
    {
        x+=velocity;
    }
    if(state=="left")
    {
        x-=velocity;
    }
    if(state=="up")
    {
        y-=velocity;
    }
    if(state=="down")
    {
        y+=velocity;
    }

    if(frames%animation_velocity==0)
    {
        current_texture++;
        if(current_texture>=textures[state].size())
            current_texture=0;
    }

    if(colision(rect,jugador->rect))
    {
        //jugador->delete_flag = true;
        if(x<jugador->x)
            jugador->push_orientation="right";
        if(x>jugador->x)
            jugador->push_orientation="left";
        if(y<jugador->y)
            jugador->push_orientation="down";
        if(y>jugador->y)
            jugador->push_orientation="up";

        jugador->push_amount=10;

        jugador->vidas--;

        cout<<"Colision con jugador"<<endl;
    }

    frames++;
}
