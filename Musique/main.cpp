#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "Piano.hpp"
#include "Guitare.hpp"
#include "Violon.hpp"
#include "Note.hpp"
#include "Melody.hpp"

using namespace std;

// Fonction pour jouer une melodie avec un instrument
void playMelody(Instrument* instrument, double speed) {
    vector<Note> melody = getMelody(instrument);  // Recupere la melodie

    for (const auto& note : melody) {
        if (note.name != "0") {  // Si la note n'est pas une pause
            instrument->playNote(note.name);  // Joue la note
            SDL_Delay(note.duration * 1000 * speed);  // Temps de pause ajuste par la vitesse
        }
    }
}

// Fonction pour jouer de maniere manuelle avec les touches
void playManual(Instrument* instrument) {
    bool quit = false;
    SDL_Event event;

    map<SDL_Keycode, string> keyToNote = {
        {SDLK_a, "C"}, {SDLK_z, "D"}, {SDLK_e, "E"}, {SDLK_r, "F"},
        {SDLK_t, "G"}, {SDLK_y, "A"}, {SDLK_u, "B"}, {SDLK_i, "C1"}
    };

    cout << "Appuyez sur les touches (A, Z, E, R, T, Y, U, I) pour jouer des notes, 'ECHAP' pour revenir au menu." << endl;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    return;  // Retourner au menu de selection du mode
                }
                else {
                    auto it = keyToNote.find(event.key.keysym.sym);
                    if (it != keyToNote.end()) {
                        instrument->playNote(it->second);
                    }
                }
            }
        }
    }
}

// Fonction principale
int main() {
    // Initialisation de SDL pour la video et l'audio
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        cerr << "Erreur SDL_Init: " << SDL_GetError() << endl;
        return -1;
    }

    // Creer une fenetre SDL
    SDL_Window* window = SDL_CreateWindow("Application Musique",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 600, SDL_WINDOW_SHOWN);

    if (!window) {
        cerr << "Erreur SDL_CreateWindow: " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    // Initialisation de SDL_mixer pour la gestion audio
    if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3) {
        cerr << "Erreur Mix_Init: " << Mix_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        cerr << "Erreur Mix_OpenAudio: " << Mix_GetError() << endl;
        Mix_Quit();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    Mix_AllocateChannels(128);
    while (true) {
        // Creer un instrument choisi par l'utilisateur
        int choix;
        cout << "Bonjour, bienvenue a Musicalau quel instrument voulez-vous essayer ? :\n1. Piano\n2. Guitare\n3. Violon\n(0 pour quitter)" << endl;
        cin >> choix;

        if (choix == 0) {
            break;  // Quitter l'application
        }

        unique_ptr<Instrument> instrument;
        switch (choix) {
        case 1: instrument = make_unique<Piano>(); break;
        case 2: instrument = make_unique<Guitare>(); break;
        case 3: instrument = make_unique<Violon>(); break;
        default:
            cout << "Choix invalide." << endl;
            continue;  // Revenir au choix de l'instrument
        }

        instrument->loadSounds();  // Charger les sons

        while (true) {
            // Selectionner le mode de jeu
            int mode;
            cout << "1. Ecouter la melodie\n2. Jouer l'instrument\n(0 pour revenir au choix de l'instrument)" << endl;
            cin >> mode;

            if (mode == 0) {
                break;  // Revenir au choix de l'instrument
            }

            if (mode == 1) {
                double vitesseLecture;
                cout << "Choisissez la vitesse de lecture (1.0 pour normal, > 1 pour plus lent, < 1 pour plus rapide, 0 pour revenir au menu) : ";
                cin >> vitesseLecture;

                if (vitesseLecture == 0) {
                    continue;  // Revenir au choix du mode
                }

                playMelody(instrument.get(), vitesseLecture);
            }
            else if (mode == 2) {
                playManual(instrument.get());  // Permet de revenir au menu via ESC
            }
            else {
                cout << "Choix invalide." << endl;
            }
        }
    }

    // Nettoyage SDL et Mix
    Mix_CloseAudio();
    Mix_Quit();
    SDL_DestroyWindow(window);  // Detruire la fenetre
    SDL_Quit();

    return 0;
}
