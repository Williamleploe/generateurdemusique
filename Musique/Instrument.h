#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <map>
#include <string>
#include <SDL_mixer.h>

using namespace std;

// Déclaration de la fonction loadSound
Mix_Chunk* loadSound(const string& path);

class Instrument {
public:
    virtual void chargerNotes() = 0;
    virtual void jouerNote(const std::string& note) = 0;
    virtual ~Instrument() = default;

protected:
    map<std::string, Mix_Chunk*> notes;
};

#endif // INSTRUMENT_H
