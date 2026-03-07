#ifndef VELO_H
#define VELO_H
#include <SDL2/SDL.h>

// Classe Velo pour gérer le vélo dans le jeu
class Velo {
public:
    SDL_Rect rect;// Rectangle représentant la position et la taille du vélo
    SDL_Texture* texture; // Texture du vélo
    int speed; // Vitesse de déplacement du vélo
     // Constructeur de la classe Velo
    Velo(int x, int y, int w, int h, SDL_Texture* tex);
    void handleInput(const Uint8* keys);  // Méthode pour gérer les entrées utilisateur
    void render(SDL_Renderer* renderer); // Méthode pour rendre le vélo à l'écran
};
#endif // VELO_H
