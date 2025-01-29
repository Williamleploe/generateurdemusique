//#define SDL_MAIN_HANDLED
//#include <SDL.h>
//#include <SDL_mixer.h>
//#include <iostream>
//#include <map>
//#include <memory>
//#include <limits>
//
//using namespace std;
//
//// Fonction pour charger un son et le retourner sous forme de Mix_Chunk*
//Mix_Chunk* loadSound(const string& file) {
//    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
//    if (!chunk) {
//        cerr << "Erreur de chargement du son " << file << " : " << Mix_GetError() << endl;
//    }
//    return chunk;
//}
//
//int main() {
//    // Initialisation de SDL
//    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
//        cerr << "Erreur SDL_Init: " << SDL_GetError() << endl;
//        return -1;
//    }
//
//    // Création de la fenêtre SDL
//    SDL_Window* window = SDL_CreateWindow("Générateur de Musique",
//        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
//        800, 600, SDL_WINDOW_SHOWN);
//    if (!window) {
//        cerr << "Erreur de création de fenêtre: " << SDL_GetError() << endl;
//        SDL_Quit();
//        return -1;
//    }
//
//    // Création du renderer pour la fenêtre
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    if (!renderer) {
//        cerr << "Erreur de création du renderer: " << SDL_GetError() << endl;
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return -1;
//    }
//
//    // Initialisation de SDL_mixer
//    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
//        cerr << "Erreur Mix_OpenAudio: " << Mix_GetError() << endl;
//        SDL_DestroyRenderer(renderer);
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return -1;
//    }
//
//    Mix_AllocateChannels(128);
//    // Carte pour stocker les sons de chaque instrument
//    map<string, Mix_Chunk*> pianoNotes;
//    map<string, Mix_Chunk*> guitareNotes;
//    map<string, Mix_Chunk*> violonNotes;
//
//    // Chargement des sons pour chaque instrument (Piano, Guitare, Violon)
//    pianoNotes["a"] = loadSound("piano/C.wav");
//    pianoNotes["z"] = loadSound("piano/D.wav");
//    pianoNotes["e"] = loadSound("piano/E.wav");
//    pianoNotes["r"] = loadSound("piano/F.wav");
//    pianoNotes["t"] = loadSound("piano/G.wav");
//    pianoNotes["y"] = loadSound("piano/A.wav");
//    pianoNotes["u"] = loadSound("piano/B.wav");
//    pianoNotes["i"] = loadSound("piano/C1.wav");
//
//    guitareNotes["a"] = loadSound("guitare/C.wav");
//    guitareNotes["z"] = loadSound("guitare/D.wav");
//    guitareNotes["e"] = loadSound("guitare/E.wav");
//    guitareNotes["r"] = loadSound("guitare/F.wav");
//    guitareNotes["t"] = loadSound("guitare/G.wav");
//    guitareNotes["y"] = loadSound("guitare/A.wav");
//    guitareNotes["u"] = loadSound("guitare/B.wav");
//    guitareNotes["i"] = loadSound("guitare/C1.wav");
//
//    violonNotes["a"] = loadSound("violon/C.wav");
//    violonNotes["z"] = loadSound("violon/D.wav");
//    violonNotes["e"] = loadSound("violon/E.wav");
//    violonNotes["r"] = loadSound("violon/F.wav");
//    violonNotes["t"] = loadSound("violon/G.wav");
//    violonNotes["y"] = loadSound("violon/A.wav");
//    violonNotes["u"] = loadSound("violon/B.wav");
//    violonNotes["i"] = loadSound("violon/C1.wav");
//
//    // Boucle principale pour choisir un instrument
//    int choix = 0;
//    bool instrumentChoisi = false;
//    map<string, Mix_Chunk*>* currentNotes = nullptr;
//
//    while (true) {
//        // Boucle pour choisir un instrument
//        while (!instrumentChoisi) {
//            cout << "Choisissez un instrument: 1. Piano 2. Guitare 3. Violon" << endl;
//            cin >> choix;
//
//            // Vérification si l'entrée est correcte
//            if (cin.fail()) {
//                cin.clear(); // Efface l'état d'erreur
//                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore les caractères incorrects
//                cerr << "Entrée invalide! Veuillez entrer un nombre valide (1, 2 ou 3)." << endl;
//                continue;
//            }
//
//            switch (choix) {
//            case 1:
//                currentNotes = &pianoNotes;
//                instrumentChoisi = true;
//                break;
//            case 2:
//                currentNotes = &guitareNotes;
//                instrumentChoisi = true;
//                break;
//            case 3:
//                currentNotes = &violonNotes;
//                instrumentChoisi = true;
//                break;
//            default:
//                cerr << "Choix invalide! Essayez encore." << endl;
//                break;
//            }
//        }
//
//        // Message de contrôle
//        cout << "Appuyez sur une touche (a, z, e, r, t, y, u, i) pour jouer une note." << endl;
//        cout << "Appuyez sur 'q' pour changer d'instrument." << endl;
//
//        // Gestion des entrées clavier
//        bool running = true;
//        SDL_Event e;
//
//        while (running) {
//            while (SDL_PollEvent(&e)) {
//                if (e.type == SDL_QUIT) {
//                    running = false;
//                }
//                if (e.type == SDL_KEYDOWN) {
//                    // Convertir le code de la touche en caractère
//                    string keyStr;
//                    switch (e.key.keysym.sym) {
//                    case SDLK_a: keyStr = "a"; break;
//                    case SDLK_z: keyStr = "z"; break;
//                    case SDLK_e: keyStr = "e"; break;
//                    case SDLK_r: keyStr = "r"; break;
//                    case SDLK_t: keyStr = "t"; break;
//                    case SDLK_y: keyStr = "y"; break;
//                    case SDLK_u: keyStr = "u"; break;
//                    case SDLK_i: keyStr = "i"; break;
//                    case SDLK_q: // Changer d'instrument avec 'q'
//                        instrumentChoisi = false;  // Permet de revenir au choix d'instrument
//                        running = false; // Quitter la boucle de lecture des notes
//                        break;
//                    default: keyStr = ""; break;
//                    }
//
//                    if (keyStr == "q") {
//                        instrumentChoisi = false;  // Permet de revenir au choix d'instrument
//                        break; // Quitter cette boucle pour recommencer le choix d'instrument
//                    }
//
//                    if (!keyStr.empty() && currentNotes->find(keyStr) != currentNotes->end()) {
//                        // Jouer la note correspondante
//                        if (Mix_PlayChannel(-1, (*currentNotes)[keyStr], 0) == -1) {
//                            cerr << "Erreur lors de la lecture de la note: " << Mix_GetError() << endl;
//                        }
//                    }
//                    else if (!keyStr.empty()) {
//                        cerr << "Note invalide: " << keyStr << endl;
//                    }
//                }
//            }
//
//            // Effacer l'écran et dessiner quelque chose (facultatif, mais ça montre qu'on a la fenêtre SDL)
//            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir
//            SDL_RenderClear(renderer);
//            SDL_RenderPresent(renderer);
//        }
//    }
//
//    // Libération des ressources et nettoyage
//    Mix_CloseAudio();
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//    return 0;
//}
