
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<iostream>
#include<list>

#include "Jugador.h"
#include "Enemigo.h"
#include "Proyectil.h"
#include "Vida.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character;
SDL_Rect rect_background,rect_character;
Mix_Music* music = NULL;
Mix_Chunk* shot = NULL;
Mix_Chunk* eDeath = NULL;
int*contador;
TTF_Font* font;
SDL_Color color;
SDL_Surface* surfacemessage;
SDL_Texture* message;
SDL_Rect messagerect;

using namespace std;

int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 500/*WIDTH*/, 250/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }
    //Initialize SDL_mixer
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "SDL_Mixer could not initialize! SDL_Mixer Error: " << Mix_GetError();
    }
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        cout << "SDL could not initialize! SDL Error: %s\n" << SDL_GetError();
    }
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        cout << "SDL_ttf could not initialize! SDL_ttf Error: %s\n" << TTF_GetError();
    }
    //Load Music
    music = Mix_LoadMUS("darkmoon.wav");
     shot = Mix_LoadWAV("laser.wav");
     eDeath = Mix_LoadWAV("EnemyDeath.ogg");

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo2.jpg");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = w;
    rect_background.h = h;

    character = IMG_LoadTexture(renderer, "personaje.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 0;
    rect_character.y = 100;
    rect_character.w = w;
    rect_character.h = h;

    SDL_Texture* otro_personaje = IMG_LoadTexture(renderer,"otropersonaje.png");
    SDL_Rect otro_rect;
    otro_rect.x=150;
    otro_rect.y=50;
    otro_rect.w=32;
    otro_rect.h=32;

    Mix_PlayMusic(music, -1);

    list<Entidad*>entidades;
    Jugador *jg = new Jugador(&entidades, renderer);
    entidades.push_back(jg);
    entidades.push_back(new Vida(&entidades,renderer));

    jg->killsHUD(renderer);

    double last_frame=0;
    int frame=0;
    //Main Loop
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                switch(Event.key.keysym.sym)
                    {
                       case SDLK_z:
                        Mix_PlayChannel(-1, shot, 0);
                        break;
                    }
            }
        }

        int spawn_frequency=60-(frame/100);
        if(spawn_frequency<5)
            spawn_frequency=5;
        if(frame%spawn_frequency==0)
            entidades.push_back(new Enemigo(&entidades,renderer));

        //SDL_Delay(17-(SDL_GetTicks()-last_frame));
        double diferencia = SDL_GetTicks()-last_frame;
        double ajuste = 17 - diferencia;
        if(ajuste>0)
            SDL_Delay(ajuste);
        last_frame=SDL_GetTicks();

        for(list<Entidad*>::iterator e = entidades.begin();
            e!=entidades.end();
            e++)
            (*e)->logica();

        for(list<Entidad*>::iterator e = entidades.begin();
            e!=entidades.end();
            e++)
        {
            if((*e)->delete_flag)
            {
                entidades.remove(*e);
                if((*e)->tipo == "Enemigo")
                    jg->kills++;
                jg->actualizarHUD(renderer);
                Mix_PlayChannel(-1, eDeath, 0);
                break;
            }
        }

        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        jg->renderKillsHUD(renderer);

        for(int i=0;i<2;i++)
        {
            for(list<Entidad*>::iterator e = entidades.begin();
                e!=entidades.end();
                e++)
            {
                if((*e)->capa==i)
                    (*e)->dibujar();
            }
        }

        SDL_RenderPresent(renderer);
        frame++;
    }

	return 0;
}
