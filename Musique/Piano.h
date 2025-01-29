#ifndef PIANO_H
#define PIANO_H

#include "Instrument.h"
using namespace std;

class Piano : public Instrument {
public:
    Piano();
    void chargerNotes() override; // Implémentation de la méthode pour charger les notes
    void jouerNote(const string& note) override;  // Implémentation pour jouer une note
};

#endif // PIANO_H
