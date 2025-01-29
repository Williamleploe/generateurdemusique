#include "Instrument.h"
#include <iostream>

using namespace std;

Mix_Chunk* loadSound(const std::string& path) {
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if (!chunk) {
        cerr << "Erreur de chargement du son " << path << " : " << Mix_GetError() << endl;
    }
    return chunk;
}
