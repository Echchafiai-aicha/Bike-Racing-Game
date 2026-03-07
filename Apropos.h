#ifndef APROPOS_H
#define APROPOS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
// Classe Apropos pour afficher des informations sur le jeu
class Apropos {
public:
    Apropos();// Constructeur
    ~Apropos();// Destructeur

// Méthodes pour initialiser, gérer les événements, rendre et nettoyer
    bool initialize(SDL_Renderer* renderer, TTF_Font* font);
    void handleEvents(SDL_Event& e);
    void render(SDL_Renderer* renderer);
    void cleanUp();
 // Méthodes pour vérifier et réinitialiser l'état du bouton "Retour"
    bool isBackClicked() const;  // Méthode pour savoir si "Retour" a été cliqué
    void resetBackClicked();      // Réinitialiser l'état du bouton "Retour"

private:
    SDL_Texture* backgroundTexture; // Texture de fond
    SDL_Rect descriptionRect;// Rectangle pour la zone de description
    SDL_Rect backButtonRect; // Rectangle pour le bouton "Retour"
    bool backClicked;// État du clic sur le bouton "Retour"
    std::string descriptionText; // Texte de description

    TTF_Font* font;  // Police utilisée pour le texte
};

#endif // APROPOS_H



