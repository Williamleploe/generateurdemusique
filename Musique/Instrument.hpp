#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

using namespace std;
#include <SDL.h>
#include <SDL_mixer.h>
#include <map>
#include <string>
#include <iostream>

class Instrument {
public:
    Instrument() = default;

    virtual void loadSounds() = 0;

    virtual void playNote(const string& note) = 0;


    virtual ~Instrument();  

    bool isSoundLoaded(const string& note) const {
        return sounds.find(note) != sounds.end(); 
    };

protected:
    std::map<string, Mix_Chunk*> sounds;
};

#endif