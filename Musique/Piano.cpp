#include "Piano.hpp"
#include "SDL_mixer.h"

Piano::Piano() {
    loadSounds();  // Charge les sons au moment de la creation de l'objet
}

Piano::~Piano() {
    // Liberer les ressources allouees si necessaire
    for (auto& pair : sounds) {
        Mix_FreeChunk(pair.second);
    }
    sounds.clear();
}

void Piano::loadSounds() {
    sounds["C"] = Mix_LoadWAV("piano/C.wav");
    sounds["D"] = Mix_LoadWAV("piano/D.wav");
    sounds["E"] = Mix_LoadWAV("piano/E.wav");
    sounds["F"] = Mix_LoadWAV("piano/F.wav");
    sounds["G"] = Mix_LoadWAV("piano/G.wav");
    sounds["A"] = Mix_LoadWAV("piano/A.wav");
    sounds["B"] = Mix_LoadWAV("piano/B.wav");
    sounds["C1"] = Mix_LoadWAV("piano/C1.wav");
    sounds["C7"] = Mix_LoadWAV("piano/C7.wav");
    sounds["D7"] = Mix_LoadWAV("piano/D7.wav");
    sounds["E7"] = Mix_LoadWAV("piano/E7.wav");
    sounds["F7"] = Mix_LoadWAV("piano/F7.wav");
    sounds["G7"] = Mix_LoadWAV("piano/G7.wav");
    sounds["A7"] = Mix_LoadWAV("piano/A7.wav");
    sounds["B6"] = Mix_LoadWAV("piano/B6.wav");
    sounds["A#6"] = Mix_LoadWAV("piano/A#6.wav");
    sounds["E6"] = Mix_LoadWAV("piano/E6.wav");
    sounds["A6"] = Mix_LoadWAV("piano/A6.wav");
    sounds["G6"] = Mix_LoadWAV("piano/G6.wav");
}

void Piano::playNote(const string& note) {
    if (sounds.find(note) != sounds.end()) {
        Mix_PlayChannel(-1, sounds[note], 0);
    }
}