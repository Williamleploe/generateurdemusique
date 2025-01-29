#include "Piano.h"
#include <iostream>

using namespace std;

Piano::Piano() {
    // Chargement des sons pour les notes du piano
    chargerNotes();
}

void Piano::chargerNotes() {
    notes["A"] = loadSound("piano/C.wav");
    notes["Z"] = loadSound("piano/D.wav");
    notes["E"] = loadSound("piano/E.wav");
    notes["R"] = loadSound("piano/F.wav");
    notes["T"] = loadSound("piano/G.wav");
    notes["Y"] = loadSound("piano/A.wav");
    notes["U"] = loadSound("piano/B.wav");
    notes["I"] = loadSound("piano/C1.wav");
}

void Piano::jouerNote(const string& note) {
    if (notes.find(note) != notes.end()) {
        Mix_PlayChannel(-1, notes[note], 0); // Jouer la note
    }
    else {
        cerr << "Note non trouvée: " << note << endl;
    }
}
