#include <iostream>
#include <conio.h>   
#include <windows.h> 
#include <map>       
#include <string>    

int main() {
    // Map des touches vers les fichiers de notes
    std::map<char, std::wstring> keyToNote = {
        {'a', L"C.wav"},  // 'a' -> note C
        {'s', L"D.wav"},  // 's' -> note D
        {'d', L"E.wav"},  // 'd' -> note E
        {'f', L"F.wav"},  // 'f' -> note F
        {'g', L"G.wav"},  // 'g' -> note G
        {'h', L"A.wav"},  // 'h' -> note A
        {'j', L"B.wav"}   // 'j' -> note B
    };

    std::cout << "Appuyez sur les touches (a, s, d, f, g, h, j) pour jouer des notes. Appuyez sur 'q' pour quitter.\n";

    while (true) {
        char key = _getch(); // Attend qu'une touche soit pressée
        if (key == 'q') {
            std::cout << "Fermeture du programme.\n";
            break; // Quitte la boucle si 'q' est pressé
        }

        if (keyToNote.find(key) != keyToNote.end()) {
            // Joue le son associé à la touche
            std::wstring soundFile = keyToNote[key];
            PlaySound(soundFile.c_str(), NULL, SND_FILENAME | SND_ASYNC);
            std::cout << "Note jouée : " << key << "\n";
        }
        else {
            std::cout << "Touche invalide. Appuyez sur une touche valide (a, s, d, f, g, h, j).\n";
        }
    }

    return 0;
}

// Classe de base pour un instrument
class Instrument {
protected:
    std::string name;

public:
    Instrument(const std::string& name) : name(name) {}
    virtual ~Instrument() {}

    virtual void playNote(const std::string& note) const {
        std::cout << "Playing note " << note << " on " << name << ".\n";
    }

    std::string getName() const { return name; }
};
