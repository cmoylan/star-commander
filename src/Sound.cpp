#include "Sound.h"


// no constructor
Sound::Sound() { }

void
Sound::free(std::string name)
{
    SoundList::iterator sound;

    sound = sounds.find(name);
    if (sound != sounds.end()) {
        Mix_FreeChunk(sound->second);
    }
}


void
Sound::freeAll()
{
    SoundList::iterator sound;

    for (sound = sounds.begin(); sound != sounds.end(); ++sound) {
        Mix_FreeChunk(sound->second);
        sounds.erase(sound);
    }

    //it->first it->second
}


void
Sound::play(std::string name, int loop)
{
    SoundList::iterator sound;

    sound = sounds.find(name);
    if (sound != sounds.end()) {
        Mix_PlayChannel(-1, sound->second, loop);
    }
}


void
Sound::load(std::string name, std::string file)
{
    Mix_Chunk *chunk;

    // TODO: make sure it loaded
    chunk = Mix_LoadWAV(file.c_str());

    sounds[name] = chunk;
}
