#ifndef VIOLON_H
#define VIOLON_H

#include "Instrument.h"

using namespace std;

class Violon : public Instrument {
public:
    Violon();
    void chargerNotes() override;
    void jouerNote(const string& note) override;
};

#endif // VIOLON_H
