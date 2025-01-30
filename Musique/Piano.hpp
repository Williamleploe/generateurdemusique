#ifndef PIANO_HPP
#define PIANO_HPP
using namespace std;
#include "Instrument.hpp"

class Piano : public Instrument {
public:
    Piano();
    // D�claration du destructeur, mais sans corps
    virtual ~Piano();  // Pas de d�finition ici

    void loadSounds() override;
    void playNote(const string& note) override;
};

#endif /