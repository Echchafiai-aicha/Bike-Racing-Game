#ifndef JEUX_H
#define JEUX_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include "Mur.h"
#include "Velo.h"
#include "Chronometre.h"

// Classe représentant le jeu
class Jeux {
public:

    // Constructeur qui initialise le jeu avec une fenêtre et un renderer
    Jeux(SDL_Window* window, SDL_Renderer* renderer);
    ~Jeux();// Destructeur pour nettoyer les ressources

    bool initialize(); // Méthode pour initialiser le jeu
    void handleEvents(SDL_Event& e);// Méthode pour gérer les événements SDL
    void update(); // Méthode pour mettre à jour l'état du jeu
    void render();  // Méthode pour rendre le jeu à l'écran
    void cleanUp(); // Méthode pour nettoyer les ressources
    void run();// Méthode principale pour exécuter le jeu

private:
    SDL_Window* window; // Pointeur vers la fenêtre SDL
    SDL_Renderer* renderer; // Pointeur vers le renderer SDL
    TTF_Font* font;// Pointeur vers la police de caractères

    SDL_Texture* backgroundTexture; // Texture de fond
    SDL_Texture* bikeTexture; // Texture du vélo
    SDL_Texture* murTexture;  // Texture des murs
    SDL_Texture* gameOverTexture; // Texture du message "Game Over"

    bool running;    // Indique si le jeu est en cours d'exécution
    bool gameOver;// Indique si le jeu est terminé

    Velo* bike; // Pointeur vers l'objet vélo
    std::vector<Mur> murs;// Vecteur contenant les murs

    Chronometre chronometre;  // Chronomètre pour le jeu
    // Méthode pour mettre à jour le message "Game Over"
    void updateGameOverTexture(const std::string& msg);
    // Méthode pour vérifier les collisions entre deux rectangles
    bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
};

#endif


 



 