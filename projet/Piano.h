#ifndef PIANO_H
#define PIANO_H

#include "Instrument.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>

class Piano : public Instrument {
private:
    std::map<std::string, Mix_Chunk*> notes; // Mapping des touches aux fichiers audio

    // Méthode pour charger les sons
    Mix_Chunk* loadSound(const std::string& file) {
        Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
        if (!chunk) {
            std::cerr << "Erreur de chargement : " << file << " - " << Mix_GetError() << std::endl;
        }
        return chunk;
    }

public:
    Piano() : Instrument("Piano") {
        // Initialiser SDL_Mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            std::cerr << "Erreur SDL_mixer : " << Mix_GetError() << std::endl;
        }

        // Charger les fichiers audio pour chaque note
        notes["A"] = loadSound("C:\\sounds\\C.wav");
        notes["Z"] = loadSound("C:\\sounds\\D.wav");
        notes["E"] = loadSound("C:\\sounds\\E.wav");
        notes["R"] = loadSound("C:\\sounds\\F.wav");
        notes["T"] = loadSound("C:\\sounds\\G.wav");
        notes["Y"] = loadSound("C:\\sounds\\A.wav");
        notes["U"] = loadSound("C:\\sounds\\B.wav");
        notes["I"] = loadSound("C:\\sounds\\C1.wav");
    }

    ~Piano() {
        // Libérer les ressources
        for (auto& pair : notes) {
            Mix_FreeChunk(pair.second);
        }
        Mix_CloseAudio();
    }

    // Jouer une note avec SDL
    void playNote(const std::string& note, const std::string& rhythm) const override {
        auto it = notes.find(note);
        if (it != notes.end()) {
            int channel = Mix_PlayChannel(-1, it->second, 0);
            if (channel == -1) {
                std::cerr << "Erreur de lecture du son : " << Mix_GetError() << std::endl;
            }
        }
        else {
            std::cerr << "Note '" << note << "' introuvable pour le piano !" << std::endl;
        }

        // Ajouter un délai en fonction du rythme
        if (rhythm == "lent") {
            SDL_Delay(600);
        }
        else if (rhythm == "normal") {
            SDL_Delay(300);
        }
        else if (rhythm == "rapide") {
            SDL_Delay(150);
        }
    }
};

#endif
