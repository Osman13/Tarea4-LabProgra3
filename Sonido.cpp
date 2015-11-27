#include "Sonido.h"

Sonido::Sonido(string file)
{
    this->sound = Mix_LoadWAV(file.c_str());

    if(sound == NULL)
        cout << "Failed to load scratch sound effect! SDL_mixer Error: %s\n" << Mix_GetError();
}

Sonido::~Sonido()
{
    //dtor
}

void Sonido::play()
{
    Mix_PlayChannel(-1, sound, 0);
}
