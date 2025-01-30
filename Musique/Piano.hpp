#ifndef PIANO_HPP
#define PIANO_HPP
using namespace std;
#include "Instrument.hpp"

class Piano : public Instrument {
public:
    Piano();
    // Déclaration du destructeur, mais sans corps
    virtual ~Piano();  // Pas de définition ici

    void loadSounds() override;
    void playNote(const string& note) override;
};

#endif /