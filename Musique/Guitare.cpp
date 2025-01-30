#include "Guitare.hpp"
#include <SDL_mixer.h>

Guitare::~Guitare() {
    // Libérer les sons spécifiques à la guitare
    for (auto& pair : sounds) {
        if (pair.second) {
            Mix_FreeChunk(pair.second);  // Libère chaque son chargé
        }
    }
    sounds.clear();  // Vide la map des sons
}


void Guitare::loadSounds() {
    // Chargement des sons pour chaque note spécifique à la guitare
    sounds["C"] = Mix_LoadWAV("guitare/C.wav");
    sounds["D"] = Mix_LoadWAV("guitare/D.wav");
    sounds["E"] = Mix_LoadWAV("guitare/E.wav");
    sounds["F"] = Mix_LoadWAV("guitare/F.wav");
    sounds["G"] = Mix_LoadWAV("guitare/G.wav");
    sounds["A"] = Mix_LoadWAV("guitare/A.wav");
    sounds["B"] = Mix_LoadWAV("guitare/B.wav");
    sounds["C1"] = Mix_LoadWAV("guitare/C1.wav");
    sounds["C7"] = Mix_LoadWAV("guitare/C7.wav");
    sounds["D7"] = Mix_LoadWAV("guitare/D7.wav");
    sounds["E7"] = Mix_LoadWAV("guitare/E7.wav");
    sounds["F7"] = Mix_LoadWAV("guitare/F7.wav");
    sounds["G7"] = Mix_LoadWAV("guitare/G7.wav");
    sounds["A7"] = Mix_LoadWAV("guitare/A7.wav");
    sounds["A6"] = Mix_LoadWAV("guitare/A6.wav");
    sounds["A#6"] = Mix_LoadWAV("guitare/A#6.wav");
    sounds["E6"] = Mix_LoadWAV("guitare/E6.wav");
    sounds["B6"] = Mix_LoadWAV("guitare/B6.wav");
    sounds["G6"] = Mix_LoadWAV("guitare/G6.wav");
}

void Guitare::playNote(const string& note) {
    // Vérifier si la note existe dans la map et la jouer
    if (sounds.find(note) != sounds.end()) {
        Mix_PlayChannel(-1, sounds[note], 0);
    }
}
