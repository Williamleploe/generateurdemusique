#include "Instrument.hpp"
using namespace std;
// Destructeur pour lib�rer la m�moire associ�e aux sons
Instrument::~Instrument() {
    for (auto& pair : sounds) {
        if (pair.second) {
            Mix_FreeChunk(pair.second); 
        }
    }
    sounds.clear(); 
}

// Fonction pour jouer une note donn�e
void Instrument::playNote(const string& note) {
    auto it = sounds.find(note); 
    if (it != sounds.end()) {
        Mix_PlayChannel(-1, it->second, 0);
    }
    else {
        cerr << "Note " << note << " non trouv�e !" << endl;
    }
}