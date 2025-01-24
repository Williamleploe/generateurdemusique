#include <SDL2.dll>
#include <iostream>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Hello SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Delay(3000); // attend 3 secondes

    SDL_DestroyWindow(window);
    SDL_Quit();
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
