#include <SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>  // Pour M_PI

// D�finir une structure pour la note et sa dur�e
struct Note {
    std::string note;
    float duration;  // Dur�e en secondes
};

// Mapper les noms de notes aux fr�quences
int noteToFrequency(const std::string& note) {
    if (note == "E7") return 2637;
    if (note == "C7") return 2093;
    if (note == "G7") return 3136;
    if (note == "A7") return 3520;
    if (note == "F7") return 2794;
    if (note == "G6") return 1568;
    if (note == "E6") return 1318;
    if (note == "A6") return 1760;
    if (note == "B6") return 1976;
    if (note == "A#6") return 1865;
    if (note == "D7") return 2349;
    return 0;  // Silence (pause)
}

// G�n�rer un buffer de sinuso�de pour la fr�quence donn�e
void generateTone(Uint8* buffer, int length, int frequency, int sampleRate = 44100) {
    if (frequency == 0) {  // Pour une pause
        std::fill(buffer, buffer + length, 128);  // Silence
    }
    else {
        for (int i = 0; i < length; i++) {
            buffer[i] = 127 * sin(2 * M_PI * frequency * i / sampleRate) + 128;
        }
    }
}

// Fonction pour initialiser SDL pour l'audio
bool initSDL() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "L'initialisation de SDL a �chou� ! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Sp�cification du format audio voulu
    SDL_AudioSpec wanted_spec;
    SDL_zero(wanted_spec);
    wanted_spec.freq = 44100;  // Fr�quence d'�chantillonnage
    wanted_spec.format = AUDIO_U8;  // Format de donn�es audio (8 bits non sign�)
    wanted_spec.channels = 1;  // Mono
    wanted_spec.samples = 4096;  // 1024 �chantillons par callback

    // Ouvrir le p�riph�rique audio avec les sp�cifications souhait�es
    if (SDL_OpenAudio(&wanted_spec, nullptr) < 0) {
        std::cerr << "SDL_OpenAudio a �chou� ! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // D�marrer imm�diatement la lecture audio
    SDL_PauseAudio(0);
    return true;
}
//
int main(int argc, char* argv[]) {
    if (!initSDL()) {
        return 1;
    }

    // D�finir la m�lodie avec les notes et les dur�es adapt�es au tempo du th�me de Mario (120 BPM)
    std::vector<Note> melody = {
        {"E7", 0.083}, {"0", 0.083}, {"E7", 0.083}, {"0", 0.083}, {"0", 0.083},
        {"0", 0.083}, {"E7", 0.083}, {"0", 0.083}, {"0", 0.083}, {"0", 0.083},
        {"C7", 0.083}, {"0", 0.083}, {"E7", 0.083}, {"0", 0.083}, {"0", 0.083},
        {"0", 0.083}, {"G7", 0.083}, {"0", 0.083}, {"0", 0.083}, {"0", 0.083},
        {"0", 0.083}, {"0", 0.099}, {"G6", 0.083}, {"0", 0.500}, {"C7", 0.083},
        {"0", 0.400}, {"G6", 0.083}, {"0", 0.400}, {"E6", 0.083}, {"0", 0.260},
        {"A6", 0.099}, {"0", 0.220}, {"B6", 0.111}, {"0", 0.190}, {"A#6", 0.083},
        {"0", 0.111}, {"A6", 0.083}, {"0", 0.111}, {"G6", 0.083}, {"0", 0.120},
        {"E7", 0.083}, {"0", 0.120}, {"G7", 0.150}, {"0", 0.083}, {"A7", 0.120},
        {"0", 0.190}, {"F7", 0.150}, {"0", 0.083}, {"G7", 0.120}, {"0", 0.200},
        {"E7", 0.111}, {"0", 0.200}, {"C7", 0.083}, {"0", 0.100}, {"D7", 0.083},
        {"0", 0.100}, {"B6", 0.111}
    };

    // Parcours de chaque note dans la m�lodie
    for (const auto& note : melody) {
        int frequency = noteToFrequency(note.note);  // Obtenir la fr�quence de la note
        int toneLength = static_cast<int>(note.duration * 44100);  // Dur�e en �chantillons

        Uint8* buffer = new Uint8[toneLength];  // Allouer un buffer pour les donn�es audio
        generateTone(buffer, toneLength, frequency);  // G�n�rer la tonalit�

        // Mettre en file d'attente les donn�es audio pour la lecture
        SDL_QueueAudio(1, buffer, toneLength);

        // D�lai entre les notes (dur�e de la note en millisecondes)
        SDL_Delay(static_cast<int>(note.duration * 1000));  // Attendre la dur�e de la note

        delete[] buffer;  // Lib�rer le buffer apr�s utilisation
    }

    SDL_Delay(5000);  // Attendre avant de fermer (laisser le temps � la derni�re note de se jouer)

    SDL_CloseAudio();  // Fermer le p�riph�rique audio
    SDL_Quit();  // Quitter SDL

    return 0;
}
