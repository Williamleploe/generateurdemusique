#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <thread> // For sleep
#include <chrono> // For duration

// Structure to represent a musical note and its duration
struct Note {
    std::string key;
    double duration; // Duration in seconds
};

// Function to load WAV sound files
Mix_Chunk* loadSound(const std::string& file) {
    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
    if (!chunk) {
        std::cerr << "Failed to load " << file << ": " << Mix_GetError() << std::endl;
    }
    return chunk;
}

// Function to play a note corresponding to a key press
void playNote(const std::map<std::string, Mix_Chunk*>& notes, const std::string& key) {
    auto it = notes.find(key);
    if (it != notes.end()) {
        int channel = Mix_PlayChannel(-1, it->second, 0);
        if (channel == -1) {
            std::cerr << "Error playing sound: " << Mix_GetError() << std::endl;
        }
    }
    else {
        std::cerr << "Note for key '" << key << "' not found!" << std::endl;
    }
}

// Function to play a melody
void playMelody(const std::vector<Note>& melody, const std::map<std::string, Mix_Chunk*>& notes) {
    for (const auto& note : melody) {
        if (note.key != "0") { // Skip rests
            playNote(notes, note.key);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(note.duration * 1000)));
    }
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create a window to capture keyboard input
    SDL_Window* window = SDL_CreateWindow("SDL Music Notes", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Initialize SDL_mixer with desired audio settings
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    Mix_AllocateChannels(128);
    // Load sound files for notes
    std::map<std::string, Mix_Chunk*> notes;
    notes["A"] = loadSound("C:\\piano\\C.wav");
    notes["Z"] = loadSound("C:\\piano\\D.wav");
    notes["E"] = loadSound("C:\\piano\\E.wav");
    notes["R"] = loadSound("C:\\piano\\F.wav");
    notes["T"] = loadSound("C:\\piano\\G.wav");
    notes["Y"] = loadSound("C:\\piano\\A.wav");
    notes["U"] = loadSound("C:\\piano\\B.wav");
    notes["I"] = loadSound("C:\\piano\\C1.wav");

    // Define the melody
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

    std::map<std::string, Mix_Chunk*> melodyNotes;
    melodyNotes["E7"] = loadSound("C:\\piano\\E7.wav");
    melodyNotes["C7"] = loadSound("C:\\piano\\C7.wav");
    melodyNotes["G7"] = loadSound("C:\\piano\\G7.wav");
    melodyNotes["G6"] = loadSound("C:\\piano\\G6.wav");
    melodyNotes["C7"] = loadSound("C:\\piano\\C7.wav");
    melodyNotes["E6"] = loadSound("C:\\piano\\E6.wav");
    melodyNotes["A6"] = loadSound("C:\\piano\\A6.wav");
    melodyNotes["B6"] = loadSound("C:\\piano\\B6.wav");
    melodyNotes["A#6"] = loadSound("C:\\piano\\A#6.wav");
    melodyNotes["D7"] = loadSound("C:\\piano\\D7.wav");

    // Play the melody at the start
    std::cout << "Playing the melody...\n";
    playMelody(melody, notes);

    // Interactive mode: User can play notes
    std::cout << "Press keys A, Z, E, R, T, Y, U, I to play notes. Press Q to quit.\n";
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                std::string key = SDL_GetKeyName(event.key.keysym.sym);
                std::transform(key.begin(), key.end(), key.begin(), ::toupper);

                if (key == "Q") {
                    running = false;
                }
                else {
                    playNote(notes, key);
                }
            }
        }
    }

    // Free the loaded sound files
    for (auto& pair : notes) {
        Mix_FreeChunk(pair.second);
    }

    // Close SDL
    Mix_CloseAudio();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}













