#pragma once

#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef std::map<std::string, Mix_Chunk*> SoundList;

class Sound {

    SoundList sounds;

public:
    static Sound* getInstance()
    {
        static Sound instance;
        return &instance;
    }

    void load(std::string name, std::string file);

    void play(std::string name, int loop = 0);

    void free(std::string name);

    void freeAll();

private:
    // --- Singleton things
    Sound(); // Don't implement
    ~Sound();
    Sound(Sound const&); // Don't implement
    void operator=(Sound const&); // Don't implement

};
