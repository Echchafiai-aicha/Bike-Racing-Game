#include "Mur.h"
#include <cstdlib>  // pour rand()

// Constructeur de la classe Mur
Mur::Mur(int x, int y, int w, int h) {
    rect = { x, y, w, h }; // Initialisation du rectangle avec les coordonnées et dimensions fournies
}
// Méthode pour mettre à jour la position du mur
void Mur::update(int speed) {
    // Déplace le mur vers le bas en fonction de la vitesse
    rect.y += speed;
     // Si le mur sort de l'écran (en bas), le repositionner en haut avec une nouvelle position aléatoire
    if (rect.y > 600) {
        rect.y = -rect.h;// Remettre le mur en haut de l'écran
        rect.x = rand() % (800 - rect.w);// Choisir une nouvelle position x aléatoire
    }
}
// Méthode pour rendre le mur à l'écran
void Mur::render(SDL_Renderer* renderer, SDL_Texture* murTexture) {
    // Copier la texture du mur dans le rectangle défini
    SDL_RenderCopy(renderer, murTexture, nullptr, &rect);
}