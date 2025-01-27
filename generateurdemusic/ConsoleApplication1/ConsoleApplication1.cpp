#include <SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>  // For M_PI

// Define a structure for note and its duration
struct Note {
    std::string note;
    float duration;  // Duration in seconds
};

// Map note names to frequencies
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
    return 0;  // Silence (rest)
}

// Generate a sine wave buffer for the given frequency
void generateTone(Uint8* buffer, int length, int frequency, int sampleRate = 44100) {
    if (frequency == 0) {  // For rest
        std::fill(buffer, buffer + length, 128);  // Silence
    }
    else {
        for (int i = 0; i < length; i++) {
            buffer[i] = 127 * sin(2 * M_PI * frequency * i / sampleRate) + 128;
        }
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_AudioSpec wanted_spec;
    SDL_zero(wanted_spec);
    wanted_spec.freq = 44100;
    wanted_spec.format = AUDIO_U8;
    wanted_spec.channels = 1;  // Mono
    wanted_spec.samples = 4096;  // 1024 samples per callback

    if (SDL_OpenAudio(&wanted_spec, nullptr) < 0) {
        std::cerr << "SDL_OpenAudio failed! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_PauseAudio(0);  // Start playing audio immediately

    // Define melody with notes and durations adjusted to fit the Mario theme tempo (120 BPM)





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














    for (const auto& note : melody) {
        int frequency = noteToFrequency(note.note);  // Get frequency for the note
        int toneLength = static_cast<int>(note.duration * 44100);  // Duration in samples

        Uint8* buffer = new Uint8[toneLength];  // Allocate buffer for the audio data
        generateTone(buffer, toneLength, frequency);  // Generate tone

        SDL_QueueAudio(1, buffer, toneLength);  // Queue the audio data for playback

        // Delay between notes (note duration in milliseconds)
        SDL_Delay(static_cast<int>(note.duration * 1000));  // Wait for note duration

        delete[] buffer;  // Free buffer after use
    }

    SDL_Delay(5000);  // Wait before closing

    SDL_CloseAudio();
    SDL_Quit();

    return 0;
}
