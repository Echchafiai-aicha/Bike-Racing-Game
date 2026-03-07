
#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Classe Menu pour gérer l'affichage et les interactions du menu principal
class Menu {
public:
    Menu();// Constructeur
    ~Menu();// Destructeur
    // Méthode pour initialiser le menu
    bool initialize(SDL_Renderer* renderer);
    void handleEvents(SDL_Event& e);  // Méthode pour gérer les événements de la souris
    void render(SDL_Renderer* renderer); // Méthode pour rendre le menu à l'écran
    void cleanUp();// Méthode pour nettoyer les ressources
 // Méthodes pour vérifier si un bouton a été cliqué
    bool isQuitClicked() const;
    bool isAboutClicked() const;
    bool isPlayClicked() const;
// Méthodes pour réinitialiser l'état des clics
    void resetAboutClicked();
    void resetPlayClicked();

private:
 // Textures pour le fond et les boutons
    SDL_Texture* backgroundTexture;
    SDL_Texture* aboutButtonTexture;
    SDL_Texture* playButtonTexture;
    SDL_Texture* quitButtonTexture;
 // Rectangles pour définir la position et la taille des boutons
    SDL_Rect aboutButtonRect;
    SDL_Rect playButtonRect;
    SDL_Rect quitButtonRect;
 // État des clics sur les boutons
    bool quitClicked;
    bool aboutClicked;
    bool playClicked;
};

#endif // MENU_H

