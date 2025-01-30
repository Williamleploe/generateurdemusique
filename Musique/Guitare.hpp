#ifndef GUITARE_HPP
#define GUITARE_HPP

using namespace std;
#include "Instrument.hpp"

class Guitare : public Instrument {
public:
    Guitare() = default;

    // Implémentation des méthodes spécifiques à la guitare
    void loadSounds() override;
    void playNote(const string& note) override;

    // Destructeur
    ~Guitare() override;
};

#endif