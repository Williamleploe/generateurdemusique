//#include <iostream>
//#include <vector>
//#include <memory>
//#include <thread>
//#include <chrono>
//#include <fstream>
//#include <map>"
//#include "instruments.h"
//
// using namespace std;
//// Classe de base pour les instruments
//class Instrument {
//public:
//    virtual void afficher() const = 0; // Afficher l'instrument
//    virtual void jouerNote(const std::string& note, int duree) const = 0; // Jouer une note
//    virtual ~Instrument() = default;
//};
//
//// Classe dérivée pour le piano
//class Piano : public Instrument {
//public:
//    void afficher() const override {
//        cout << "Piano" << std::endl;
//    }
//
//    void jouerNote(const std::string& note, int duree) const override {
//        cout << "Piano joue: " << note << std::endl;
//        this_thread::sleep_for(std::chrono::milliseconds(duree));
//    }
//};
//
//// Classe dérivée pour le xylophone
//class Xylophone : public Instrument {
//public:
//    void afficher() const override {
//        std::cout << "Xylophone" << std::endl;
//    }
//
//    void jouerNote(const std::string& note, int duree) const override {
//        cout << "Xylophone joue: " << note << std::endl;
//        this_thread::sleep_for(std::chrono::milliseconds(duree));
//    }
//};
//
//// Classe dérivée pour la guitare
//class Guitare : public Instrument {
//public:
//    void afficher() const override {
//        std::cout << "Guitare" << std::endl;
//    }
//
//    void jouerNote(const std::string& note, int duree) const override {
//        cout << "Guitare joue: " << note << std::endl;
//        std::this_thread::sleep_for(std::chrono::milliseconds(duree));
//    }
//};
//
//// Classe pour gérer les rythmes
//class Rythme {
//public:
//    static int obtenirDuree(const std::string& rythme) {
//        if (rythme == "lent") return 800;
//        if (rythme == "normal") return 400;
//        if (rythme == "rapide") return 200;
//        return 400; // Par défaut "normal"
//    }
//};
//
//// Fonction pour afficher le menu des instruments et permettre le choix
//std::unique_ptr<Instrument> choisirInstrument() {
//    std::vector<std::unique_ptr<Instrument>> instruments;
//    instruments.push_back(std::make_unique<Piano>());
//    instruments.push_back(std::make_unique<Xylophone>());
//    instruments.push_back(std::make_unique<Guitare>());
//
//    std::cout << "Bienvenue chez MusicaLau !\n";
//    std::cout << "Veuillez choisir un instrument :\n";
//
//    for (size_t i = 0; i < instruments.size(); ++i) {
//        std::cout << i + 1 << ". ";
//        instruments[i]->afficher();
//    }
//
//    int choix = 0;
//    std::cout << "Entrez le numero de votre choix : ";
//    std::cin >> choix;
//
//    if (choix >= 1 && static_cast<size_t>(choix) <= instruments.size()) {
//        return std::move(instruments[choix - 1]);
//    }
//    else {
//        std::cout << "\nChoix invalide. Merci de redemarrer le programme." << std::endl;
//        return nullptr;
//    }
//}
//
//// Fonction pour jouer des notes
//void jouerMusique(const Instrument& instrument) {
//    std::string rythme;
//    std::cout << "Choisissez un rythme (lent, normal, rapide) : ";
//    std::cin >> rythme;
//    int duree = Rythme::obtenirDuree(rythme);
//
//    std::cout << "Entrez une sequence de notes (ex: do re mi). Tapez 'fin' pour terminer :\n";
//    std::string note;
//    while (true) {
//        std::cin >> note;
//        if (note == "fin") break;
//        instrument.jouerNote(note, duree);
//    }
//}
//
//// Fonction pour lire une partition depuis un fichier
//void lirePartition(const Instrument& instrument, const std::string& fichier, int duree) {
//    std::ifstream partition(fichier);
//    if (!partition.is_open()) {
//        std::cerr << "Erreur : impossible d'ouvrir le fichier " << fichier << std::endl;
//        return;
//    }
//
//    std::string note;
//    while (partition >> note) {
//        instrument.jouerNote(note, duree);
//    }
//}
//
//int main() {
//    auto instrument = choisirInstrument();
//    if (!instrument) return 1;
//
//    int choix = 0;
//    std::cout << "\nQue voulez-vous faire ?\n";
//    std::cout << "1. Jouer des notes\n";
//    std::cout << "Entrez votre choix : ";
//    std::cin >> choix;
//
//    if (choix == 1) {
//        jouerMusique(*instrument);
//    }
//    else if (choix == 2) {
//        std::string fichier;
//        std::cin >> fichier;
//
//        std::string rythme;
//        std::cout << "Choisissez un rythme pour la lecture (lent, normal, rapide) : ";
//        std::cin >> rythme;
//        int duree = Rythme::obtenirDuree(rythme);
//
//        lirePartition(*instrument, fichier, duree);
//    }
//    else {
//        std::cout << "Choix invalide." << std::endl;
//    }
//
//    return 0;
//}
//
