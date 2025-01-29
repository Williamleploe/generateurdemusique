#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>

// Définir une structure pour la note et sa durée
struct Note {
    std::string note;
    float duration;  // Durée en secondes
};

// Mapper les noms de notes aux chemins de fichiers WAV
std::string noteToSoundFile(const std::string& note) {
    if (note == "E7") return "piano/E7.wav";
    if (note == "C7") return "piano/C7.wav";
    if (note == "G7") return "piano/G7.wav";
    if (note == "A7") return "piano/A7.wav";
    if (note == "F7") return "piano/F7.wav";
    if (note == "G6") return "piano/G6.wav";
    if (note == "E6") return "piano/E6.wav";
    if (note == "A6") return "piano/A6.wav";
    if (note == "B6") return "piano/B6.wav";
    if (note == "A#6") return "piano/A#6.wav";
    if (note == "D7") return "piano/D7.wav";
    return "";  // Silence (pause)
}

// Initialiser SDL et SDL_mixer pour la lecture audio
bool initSDL() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "L'initialisation de SDL a échoué ! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialiser SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        std::cerr << "L'initialisation de SDL_mixer a échoué ! SDL_mixer Error: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    return true;
}

// Fonction pour jouer une note à partir de son fichier audio
void playNote(const std::string& note) {
    std::string soundFile = noteToSoundFile(note);
    if (!soundFile.empty()) {
        Mix_Chunk* sound = Mix_LoadWAV(soundFile.c_str());
        if (sound) {
            Mix_PlayChannel(-1, sound, 0);  // Jouer la note sur un canal libre
            SDL_Delay(100);  // Attendre un peu pour permettre à la note de se jouer avant de continuer
            Mix_FreeChunk(sound);  // Libérer la mémoire après la lecture
        }
        else {
            std::cerr << "Erreur lors du chargement du fichier " << soundFile << ": " << Mix_GetError() << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (!initSDL()) {
        return 1;
    }

    // Définir la mélodie avec les notes et les durées adaptées au tempo du thème de Mario (120 BPM)
    std::vector<Note> melody = {
        {"E7", 0.083}, {"0", 0.043}, {"E7", 0.083}, {"0", 0.043},
        {"0", 0.043}, {"0", 0.043}, {"E7", 0.083}, {"0", 0.043},
        {"0", 0.043}, {"0", 0.043}, {"C7", 0.083}, {"0", 0.033},
        {"E7", 0.083}, {"0", 0.043}, {"0", 0.043}, {"0", 0.043},
        {"G7", 0.083}, {"0", 0.043}, {"0", 0.043}, {"0", 0.043},
        {"0", 0.043}, {"0", 0.043}, {"0", 0.043}, {"0", 0.043},
        {"G6", 0.083}, {"0", 0.043}, {"0", 0.043}, {"0", 0.043},
        {"0", 0.043}, {"0", 0.043}, {"0", 0.043}, {"0", 0.043},
        {"C7", 0.083}, {"0", 0.043}, {"0", 0.043}, {"0", 0.043},
        {"0", 0.043}, {"0", 0.043}, {"G6", 0.083}, {"0", 0.043},
        {"0", 0.043}, {"0", 0.043}, {"0", 0.043}, {"0", 0.043},
        {"E6", 0.083}, {"0", 0.043}, {"0", 0.043}, {"0", 0.043},
        {"0", 0.043}, {"0", 0.033}, {"A6", 0.083}, {"0", 0.023},
        {"0", 0.023}, {"0", 0.023}, {"B6", 0.083}, {"A#6", 0.083},
        {"A6", 0.083}, {"0", 0.083},
        {"G6", 0.083}, {"0", 0.040}, {"E7", 0.083}, {"0", 0.033},
        {"G7", 0.083}, {"0", 0.033}, {"A7", 0.083}, {"0", 0.033},
        {"0", 0.083}, {"0", 0.033}, {"F7", 0.083}, {"0", 0.023},
        {"G7", 0.083}, {"0", 0.033}, {"0", 0.043}, {"0", 0.023},
        {"E7", 0.083}, {"0", 0.023}, {"0", 0.023}, {"0", 0.023},
        {"C7", 0.083}, {"0", 0.033}, {"D7", 0.083}, {"0", 0.023},
        {"B6", 0.083}, {"0", 0.083}, {"0", 0.083}, {"0", 0.083},
    };

    // Parcours de chaque note dans la mélodie
    for (const auto& note : melody) {
        if (note.note != "0") {  // Ignorer les silences
            playNote(note.note);  // Jouer la note
        }

        // Délai entre les notes (durée de la note en millisecondes)
        SDL_Delay(static_cast<int>(note.duration * 1000));  // Attendre la durée de la note
    }

    Mix_CloseAudio();  // Fermer le périphérique audio
    SDL_Quit();  // Quitter SDL

    return 0;
}
