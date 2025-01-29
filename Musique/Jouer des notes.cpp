#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Piano.h"
#include "Guitare.h"
#include "Violon.h"

using namespace std;

int main() {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        cerr << "Erreur SDL_Init: " << SDL_GetError() << endl;
        return -1;
    }

    // Initialisation de SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        cerr << "Erreur Mix_OpenAudio: " << Mix_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    // Choisir un instrument avec boucle pour valider l'entrée
    Instrument* instrument = nullptr;
    int choix;
    do {
        cout << "Choisissez un instrument: 1. Piano 2. Guitare 3. Violon" << endl;
        cin >> choix;

        switch (choix) {
        case 1: instrument = new Piano(); break;
        case 2: instrument = new Guitare(); break;
        case 3: instrument = new Violon(); break;
        default:
            cerr << "Choix invalide! Veuillez entrer 1, 2 ou 3." << endl;
            break;
        }
    } while (instrument == nullptr);

    // Jouer une note (par exemple "A")
    cout << "Appuyez sur une touche pour jouer une note (A, Z, E, R...)" << endl;
    char note;
    cin >> note;

    instrument->jouerNote(string(1, note));

    // Libération des ressources et nettoyage
    delete instrument;
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}

