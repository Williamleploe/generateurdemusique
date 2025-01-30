#include "Violon.hpp"
#include <SDL_mixer.h>

void Violon::loadSounds() {
    // Chargement des sons pour chaque note specifique au violon
    sounds["C"] = Mix_LoadWAV("violon/C.wav");
    sounds["D"] = Mix_LoadWAV("violon/D.wav");
    sounds["E"] = Mix_LoadWAV("violon/E.wav");
    sounds["F"] = Mix_LoadWAV("violon/F.wav");
    sounds["G"] = Mix_LoadWAV("violon/G.wav");
    sounds["A"] = Mix_LoadWAV("violon/A.wav");
    sounds["B"] = Mix_LoadWAV("violon/B.wav");
    sounds["C1"] = Mix_LoadWAV("violon/C1.wav");
    sounds["C7"] = Mix_LoadWAV("violon/C7.wav");
    sounds["D7"] = Mix_LoadWAV("violon/D7.wav");
    sounds["E7"] = Mix_LoadWAV("violon/E7.wav");
    sounds["F7"] = Mix_LoadWAV("violon/F7.wav");
    sounds["G7"] = Mix_LoadWAV("violon/G7.wav");
    sounds["A7"] = Mix_LoadWAV("violon/A7.wav");
    sounds["A6"] = Mix_LoadWAV("violon/A6.wav");
    sounds["A#6"] = Mix_LoadWAV("violon/A#6.wav");
    sounds["E6"] = Mix_LoadWAV("violon/E6.wav");
    sounds["B6"] = Mix_LoadWAV("violon/B6.wav");
    sounds["G6"] = Mix_LoadWAV("violon/G6.wav");
}

void Violon::playNote(const string& note) {
    // Verifie si la note est presente dans la map des sons et la joue
    if (sounds.find(note) != sounds.end()) {
        Mix_PlayChannel(-1, sounds[note], 0);
    }
}