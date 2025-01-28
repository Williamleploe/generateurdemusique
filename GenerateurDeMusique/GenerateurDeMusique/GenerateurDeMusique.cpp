#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include <fstream>
#include <map>

using namespace std;

// Classe de base pour les instruments
class Instrument {
public:
    virtual void afficher() const = 0; // Afficher l'instrument
    virtual void jouerNote(const std::string& note, int duree) const = 0; // Jouer une note
    virtual ~Instrument() = default;
};

// Classe dérivée pour le piano
class Piano : public Instrument {
public:
    void afficher() const override {
        cout << "Piano" << std::endl;
    }

    void jouerNote(const std::string& note, int duree) const override {
        cout << "Piano joue: " << note << std::endl;
        this_thread::sleep_for(std::chrono::milliseconds(duree));
    }
};

// Classe dérivée pour le xylophone
class Xylophone : public Instrument {
public:
    void afficher() const override {
        std::cout << "Xylophone" << std::endl;
    }

    void jouerNote(const std::string& note, int duree) const override {
        cout << "Xylophone joue: " << note << std::endl;
        this_thread::sleep_for(std::chrono::milliseconds(duree));
    }
};

// Classe dérivée pour la guitare
class Guitare : public Instrument {
public:
    void afficher() const override {
        cout << "Guitare" << std::endl;
    }

    void jouerNote(const std::string& note, int duree) const override {
        cout << "Guitare joue: " << note << std::endl;
        this_thread::sleep_for(std::chrono::milliseconds(duree));
    }
};

// Classe pour gérer les rythmes
class Rythme {
public:
    static int obtenirDuree(const std::string& rythme) {
        if (rythme == "lent") return 800;
        if (rythme == "normal") return 400;
        if (rythme == "rapide") return 200;
        return 400; // Par défaut "normal"
    }
};

// Fonction pour afficher le menu des instruments et permettre le choix
unique_ptr<Instrument> choisirInstrument() {
    vector<std::unique_ptr<Instrument>> instruments;
    instruments.push_back(std::make_unique<Piano>());
    instruments.push_back(std::make_unique<Xylophone>());
    instruments.push_back(std::make_unique<Guitare>());

    cout << "Bienvenue chez MusicaLau !\n";
    cout << "Veuillez choisir un instrument :\n";

    for (size_t i = 0; i < instruments.size(); ++i) {
        cout << i + 1 << ". ";
        instruments[i]->afficher();
    }

    int choix = 0;
    cout << "Entrez le numero de votre choix : ";
    cin >> choix;

    if (choix >= 1 && static_cast<size_t>(choix) <= instruments.size()) {
        return move(instruments[choix - 1]);
    }
    else {
        cout << "\nChoix invalide. Merci de redemarrer le programme." << std::endl;
        return nullptr;
    }
}

// Fonction pour jouer des notes
void jouerMusique(const Instrument& instrument) {
    string rythme;
    cout << "Choisissez un rythme (lent, normal, rapide) : ";
    cin >> rythme;
    int duree = Rythme::obtenirDuree(rythme);

    cout << "Entrez une sequence de notes (ex: do re mi). Tapez 'fin' pour terminer :\n";
    string note;
    while (true) {
        cin >> note;
        if (note == "fin") break;
        instrument.jouerNote(note, duree);
    }
}

// Fonction pour lire une partition depuis un fichier
void lirePartition(const Instrument& instrument, const std::string& fichier, int duree) {
    ifstream partition(fichier);
    if (!partition.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier " << fichier << std::endl;
        return;
    }

    string note;
    while (partition >> note) {
        instrument.jouerNote(note, duree);
    }
}

int main() {
    auto instrument = choisirInstrument();
    if (!instrument) return 1;

    int choix = 0;
    cout << "\nQue voulez-vous faire ?\n";
    cout << "1. Jouer des notes\n";
    cout << "2. Lire une partition depuis un fichier\n";
    cout << "Entrez votre choix : ";
    cin >> choix;

    if (choix == 1) {
        jouerMusique(*instrument);
    }
    else if (choix == 2) {
        string fichier;
        cout << "Entrez le nom du fichier de partition : ";
        cin >> fichier;

        string rythme;
        cout << "Choisissez un rythme pour la lecture (lent, normal, rapide) : ";
        cin >> rythme;
        int duree = Rythme::obtenirDuree(rythme);

        lirePartition(*instrument, fichier, duree);
    }
    else {
        cout << "Choix invalide." << std::endl;
    }

    return 0;
}
