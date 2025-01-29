#include "Guitare.h"
#include <iostream>

using namespace std;

Guitare::Guitare() {
    chargerNotes();
}

void Guitare::chargerNotes() {
    notes["A"] = loadSound("guitare/A.wav");
    notes["Z"] = loadSound("guitare/B.wav");
    notes["E"] = loadSound("guitare/C.wav");
    notes["R"] = loadSound("guitare/D.wav");
    notes["T"] = loadSound("guitare/E.wav");
    notes["Y"] = loadSound("guitare/F.wav");
    notes["U"] = loadSound("guitare/G.wav");
    notes["I"] = loadSound("guitare/A1.wav");
}

void Guitare::jouerNote(const string& note) {
    if (notes.find(note) != notes.end()) {
        Mix_PlayChannel(-1, notes[note], 0); // Jouer la note
    }
    else {
        cerr << "Note non trouvée: " << note << endl;
    }
}
