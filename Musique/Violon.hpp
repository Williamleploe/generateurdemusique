#ifndef VIOLON_HPP
#define VIOLON_HPP

using namespace std;
#include "Instrument.hpp"

class Violon : public Instrument {
public:
    void loadSounds() override;
    void playNote(const string& note) override;
};

#endif