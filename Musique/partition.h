//class Partition {
//private:
//    std::vector<std::pair<std::string, std::string>> notes; // (note, rythme)
//
//public:
//    // Charger une partition depuis un fichier
//    bool loadFromFile(const std::string& filename) {
//        std::ifstream file(filename);
//        if (!file.is_open()) {
//            std::cerr << "Impossible d'ouvrir le fichier : " << filename << std::endl;
//            return false;
//        }
//
//        notes.clear();
//        std::string note, rhythm;
//        while (file >> note >> rhythm) {
//            notes.emplace_back(note, rhythm);
//        }
//
//        file.close();
//        return true;
//    }
//
//    // Lire la partition
//    const std::vector<std::pair<std::string, std::string>>& getNotes() const {
//        return notes;
//    }
//};
//
//#endif
