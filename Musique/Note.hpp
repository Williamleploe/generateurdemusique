#ifndef NOTE_HPP
#define NOTE_HPP

#include <string>
using namespace std;

// Structure repr?sentant une note de musique
struct Note {
    string name;  // Nom de la note (par exemple, "E7", "C5")
    float duration;    // Dur?e de la note (en secondes)
};

#endif