#ifndef PIANO_H
#define PIANO_H

#include "Instrument.h"
using namespace std;

class Piano : public Instrument {
public:
    Piano();
    void chargerNotes() override; // Impl�mentation de la m�thode pour charger les notes
    void jouerNote(const string& note) override;  // Impl�mentation pour jouer une note
};

#endif // PIANO_H
