#ifndef MUR_H
#define MUR_H
#include <SDL2/SDL.h>

// Classe représentant un mur dans le jeu
class Mur {
public:
    SDL_Rect rect;// Rectangle qui définit la position et la taille du mur
    Mur(int x, int y, int w, int h);// Constructeur qui initialise le mur avec des coordonnées et des dimensions
    void update(int speed);// Méthode pour mettre à jour la position du mur
    void render(SDL_Renderer* renderer, SDL_Texture* murTexture);// Méthode pour rendre le mur à l'écran
};
#endif // MUR_H