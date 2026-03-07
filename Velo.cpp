#include "Velo.h"
#include <SDL2/SDL.h>

// Constructeur de la classe Velo
Velo::Velo(int x, int y, int w, int h, SDL_Texture* tex)
    : speed(5), texture(tex)// Initialisation de la vitesse et de la texture
{
    rect = { x, y, w, h };// Initialisation du rectangle avec les coordonnées et dimensions fournies
}
// Méthode pour gérer les entrées utilisateur
void Velo::handleInput(const Uint8* keys) {
     // Déplacement vers le haut
    if (keys[SDL_SCANCODE_UP]) {
        rect.y -= speed;// Déplace le vélo vers le haut
        if (rect.y < 0) rect.y = 0;// Empêche le vélo de sortir de l'écran par le haut
    }
    // Déplacement vers le bas
    if (keys[SDL_SCANCODE_DOWN]) {
        rect.y += speed; // Déplace le vélo vers le bas
        if (rect.y + rect.h > 600) rect.y = 600 - rect.h;// Empêche le vélo de sortir de l'écran par le bas
    }
    // Déplacement vers la gauche
    if (keys[SDL_SCANCODE_LEFT]) {
        rect.x -= speed;// Déplace le vélo vers la gauche
        if (rect.x < 0) rect.x = 0;// Empêche le vélo de sortir de l'écran par la gauche
    }
     // Déplacement vers la droite
    if (keys[SDL_SCANCODE_RIGHT]) {
        rect.x += speed; // Déplace le vélo vers la droite
        if (rect.x + rect.w > 800) rect.x = 800 - rect.w;// Empêche le vélo de sortir de l'écran par la droite
    }
}
// Méthode pour rendre le vélo à l'écran
void Velo::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);// Rendre la texture du vélo à la position spécifiée par rect
}

