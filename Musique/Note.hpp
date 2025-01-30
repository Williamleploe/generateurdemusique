#ifndef NOTE_HPP
#define NOTE_HPP

#include <string>
using namespace std;

// Structure représentant une note de musique
struct Note {
    string name;  // Nom de la note (par exemple, "E7", "C5")
    float duration;    // Durée de la note (en secondes)
};

#endif
