#ifndef SONIDO_H
#define SONIDO_H

#include <SDL_mixer.h>
#include <iostream>

using namespace std;

class Sonido
{
    public:
        Mix_Chunk* sound;
        Sonido();
        Sonido(string file);
        virtual ~Sonido();
        void play();
    protected:
    private:
};

#endif // SOUND_H
