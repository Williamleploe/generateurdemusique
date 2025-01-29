#ifndef GUITARE_H
#define GUITARE_H

#include "Instrument.h"
using namespace std;

class Guitare : public Instrument {
public:
    Guitare();
    void chargerNotes() override;
    void jouerNote(const string& note) override;
};

#endif // GUITARE_H
