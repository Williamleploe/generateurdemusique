//#include <SDL.h>
//#include <SDL_mixer.h>
//#include <iostream>
//#include <map>
//#include <vector>
//#include <string>
//#include <algorithm>
//#include <thread> // Pour le sommeil
//#include <chrono> // Pour la durée
//
//// Structure pour représenter une note musicale et sa durée
//struct Note {
//    std::string key; // La note (par exemple, "C", "D", etc.)
//    double duration; // Durée en secondes
//};
//
//// Fonction pour charger des fichiers audio WAV
//Mix_Chunk* loadSound(const std::string& file) {
//    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
//    if (!chunk) {
//        std::cerr << "Échec du chargement de " << file << ": " << Mix_GetError() << std::endl;
//    }
//    return chunk;
//}
//
//// Fonction pour jouer une note correspondant à une touche pressée
//void playNote(const std::map<std::string, Mix_Chunk*>& notes, const std::string& key) {
//    auto it = notes.find(key);
//    if (it != notes.end()) {
//        int channel = Mix_PlayChannel(-1, it->second, 0);
//        if (channel == -1) {
//            std::cerr << "Erreur lors de la lecture du son: " << Mix_GetError() << std::endl;
//        }
//    }
//    else {
//        std::cerr << "Note pour la touche '" << key << "' non trouvée!" << std::endl;
//    }
//}
//
//// Fonction pour jouer une mélodie
//void playMelody(const std::vector<Note>& melody, const std::map<std::string, Mix_Chunk*>& notes) {
//    for (const auto& note : melody) {
//        if (note.key != "0") { // Ignorer les pauses (0)
//            playNote(notes, note.key);
//        }
//        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(note.duration * 1000)));
//    }
//}
//
//int main(int argc, char* argv[]) {
//    // Initialisation de SDL
//    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
//        std::cerr << "Échec de l'initialisation de SDL: " << SDL_GetError() << std::endl;
//        return -1;
//    }
//
//    // Créer une fenêtre pour capturer les entrées clavier
//    SDL_Window* window = SDL_CreateWindow("SDL Notes Musicales", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
//    if (!window) {
//        std::cerr << "Échec de la création de la fenêtre: " << SDL_GetError() << std::endl;
//        SDL_Quit();
//        return -1;
//    }
//
//    // Initialiser SDL_mixer avec les paramètres audio souhaités
//    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
//        std::cerr << "Échec de l'initialisation de SDL_mixer: " << Mix_GetError() << std::endl;
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return -1;
//    }
//
//    // Charger les fichiers sonores pour les notes
//    std::map<std::string, Mix_Chunk*> notes;
//    notes["A"] = loadSound("C:\\sounds\\C.wav");
//    notes["Z"] = loadSound("C:\\sounds\\D.wav");
//    notes["E"] = loadSound("C:\\sounds\\E.wav");
//    notes["R"] = loadSound("C:\\sounds\\F.wav");
//    notes["T"] = loadSound("C:\\sounds\\G.wav");
//    notes["Y"] = loadSound("C:\\sounds\\A.wav");
//    notes["U"] = loadSound("C:\\sounds\\B.wav");
//    notes["I"] = loadSound("C:\\sounds\\C1.wav");
//
//    // Définir la mélodie
//    std::vector<Note> melody = {
//        {"E7", 0.083}, {"0", 0.083}, {"E7", 0.083}, {"0", 0.083}, {"0", 0.083},
//        {"0", 0.083}, {"E7", 0.083}, {"0", 0.083}, {"0", 0.083}, {"0", 0.083},
//        {"C7", 0.083}, {"0", 0.083}, {"E7", 0.083}, {"0", 0.083}, {"0", 0.083},
//        {"0", 0.083}, {"G7", 0.083}, {"0", 0.083}, {"0", 0.083}, {"0", 0.083},
//        {"0", 0.083}, {"0", 0.099}, {"G6", 0.083}, {"0", 0.500}, {"C7", 0.083},
//        {"0", 0.400}, {"G6", 0.083}, {"0", 0.400}, {"E6", 0.083}, {"0", 0.260},
//        {"A6", 0.099}, {"0", 0.220}, {"B6", 0.111}, {"0", 0.190}, {"A#6", 0.083},
//        {"0", 0.111}, {"A6", 0.083}, {"0", 0.111}, {"G6", 0.083}, {"0", 0.120},
//        {"E7", 0.083}, {"0", 0.120}, {"G7", 0.150}, {"0", 0.083}, {"A7", 0.120},
//        {"0", 0.190}, {"F7", 0.150}, {"0", 0.083}, {"G7", 0.120}, {"0", 0.200},
//        {"E7", 0.111}, {"0", 0.200}, {"C7", 0.083}, {"0", 0.100}, {"D7", 0.083},
//        {"0", 0.100}, {"B6", 0.111}
//    };
//
//    std::map<std::string, Mix_Chunk*> melodyNotes;
//    melodyNotes["E7"] = loadSound("C:\\sounds\\E7.wav");
//    melodyNotes["C7"] = loadSound("C:\\sounds\\C7.wav");
//    melodyNotes["G7"] = loadSound("C:\\sounds\\G7.wav");
//    melodyNotes["G6"] = loadSound("C:\\sounds\\G6.wav");
//    melodyNotes["C7"] = loadSound("C:\\sounds\\C7.wav");
//    melodyNotes["E6"] = loadSound("C:\\sounds\\E6.wav");
//    melodyNotes["A6"] = loadSound("C:\\sounds\\A6.wav");
//    melodyNotes["B6"] = loadSound("C:\\sounds\\B6.wav");
//    melodyNotes["A#6"] = loadSound("C:\\sounds\\A#6.wav");
//    melodyNotes["D7"] = loadSound("C:\\sounds\\D7.wav");
//
//    // Jouer la mélodie au démarrage
//    std::cout << "Lecture de la mélodie...\n";
//    playMelody(melody, notes);
//
//    // Mode interactif : L'utilisateur peut jouer des notes
//    std::cout << "Appuyez sur les touches A, Z, E, R, T, Y, U, I pour jouer des notes. Appuyez sur Q pour quitter.\n";
//    bool running = true;
//    SDL_Event event;
//    while (running) {
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) {
//                running = false;
//            }
//            else if (event.type == SDL_KEYDOWN) {
//                std::string key = SDL_GetKeyName(event.key.keysym.sym);
//                std::transform(key.begin(), key.end(), key.begin(), ::toupper);
//
//                if (key == "Q") {
//                    running = false;
//                }
//                else {
//                    playNote(notes, key);
//                }
//            }
//        }
//    }
//
//    // Libérer les fichiers sonores chargés
//    for (auto& pair : notes) {
//        Mix_FreeChunk(pair.second);
//    }
//
//    // Fermer SDL
//    Mix_CloseAudio();
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}
