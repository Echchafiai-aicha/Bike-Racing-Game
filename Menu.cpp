#include "Menu.h"
#include <iostream>
// Constructeur de la classe Menu
Menu::Menu() : backgroundTexture(nullptr), aboutButtonTexture(nullptr), playButtonTexture(nullptr), quitButtonTexture(nullptr), quitClicked(false), aboutClicked(false), playClicked(false) {
     // Initialisation des rectangles pour les boutons
    aboutButtonRect = { 300, 400, 200, 50 };// Position et taille du bouton "À propos"
    playButtonRect = { 300, 475, 200, 50 }; // Position et taille du bouton "Jouer"
    quitButtonRect = { 300, 550, 200, 50 };// Position et taille du bouton "Quitter"
}
// Destructeur de la classe Menu
Menu::~Menu() {
    cleanUp(); // Nettoyage des ressources
}
// Méthode pour initialiser le menu
bool Menu::initialize(SDL_Renderer* renderer) {
    SDL_Surface* backgroundSurface = IMG_Load("BGM.png");
    if (!backgroundSurface) {
        std::cerr << "Erreur chargement image fond: " << IMG_GetError() << std::endl;
        return false;
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);// Libération de la surface après création de la texture
    if (!backgroundTexture) {
        std::cerr << "Erreur création texture fond: " << SDL_GetError() << std::endl;
        return false;
    }
 // Chargement des images des boutons
    SDL_Surface* aboutSurface = IMG_Load("Apropos.png");
    SDL_Surface* playSurface = IMG_Load("jouer.png");
    SDL_Surface* quitSurface = IMG_Load("quiter.png");
// Vérification du chargement des surfaces
    if (!aboutSurface || !playSurface || !quitSurface) {
        std::cerr << "Erreur chargement images boutons: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(aboutSurface);
        SDL_FreeSurface(playSurface);
        SDL_FreeSurface(quitSurface);
        return false;// Retourne faux si une des images n'a pas pu être chargée
    }
 // Création des textures à partir des surfaces
    aboutButtonTexture = SDL_CreateTextureFromSurface(renderer, aboutSurface);
    playButtonTexture = SDL_CreateTextureFromSurface(renderer, playSurface);
    quitButtonTexture = SDL_CreateTextureFromSurface(renderer, quitSurface);
 // Libération des surfaces après création des textures
    SDL_FreeSurface(aboutSurface);
    SDL_FreeSurface(playSurface);
    SDL_FreeSurface(quitSurface);
 // Vérification de la création des textures
    if (!aboutButtonTexture || !playButtonTexture || !quitButtonTexture) {
        std::cerr << "Erreur création textures boutons: " << SDL_GetError() << std::endl;
        return false;// Retourne faux si une texture n'a pas pu être créée
    }

    return true; // Initialisation réussie
}
// Gestion des événements liés à la souris
void Menu::handleEvents(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x;
        int y = e.button.y;
          // Vérification si le clic est dans la zone du bouton Quitter
        if (x >= quitButtonRect.x && x <= quitButtonRect.x + quitButtonRect.w &&
            y >= quitButtonRect.y && y <= quitButtonRect.y + quitButtonRect.h) {
            quitClicked = true;
            // Vérification si le clic est dans la zone du bouton À propos
        } else if (x >= aboutButtonRect.x && x <= aboutButtonRect.x + aboutButtonRect.w &&
                   y >= aboutButtonRect.y && y <= aboutButtonRect.y + aboutButtonRect.h) {
            aboutClicked = true;
          // Vérification si le clic est dans la zone du bouton Jouer    
        } else if (x >= playButtonRect.x && x <= playButtonRect.x + playButtonRect.w &&
                   y >= playButtonRect.y && y <= playButtonRect.y + playButtonRect.h) {
            playClicked = true;
        }
    }
}
// Affichage du menu à l'écran
void Menu::render(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);// Efface l'écran
      // Affiche la texture de fond si chargée
    if (backgroundTexture)
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
     // Affiche les boutons si les textures sont chargées
    if (aboutButtonTexture)
        SDL_RenderCopy(renderer, aboutButtonTexture, NULL, &aboutButtonRect);

    if (playButtonTexture)
        SDL_RenderCopy(renderer, playButtonTexture, NULL, &playButtonRect);

    if (quitButtonTexture)
        SDL_RenderCopy(renderer, quitButtonTexture, NULL, &quitButtonRect);

    SDL_RenderPresent(renderer);// Met à jour l'écran avec tout ce qui a été dessiné
}
// Libération des ressources allouées
void Menu::cleanUp() {
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = nullptr;
    }
    if (aboutButtonTexture) {
        SDL_DestroyTexture(aboutButtonTexture);
        aboutButtonTexture = nullptr;
    }
    if (playButtonTexture) {
        SDL_DestroyTexture(playButtonTexture);
        playButtonTexture = nullptr;
    }
    if (quitButtonTexture) {
        SDL_DestroyTexture(quitButtonTexture);
        quitButtonTexture = nullptr;
    }
}
// Accesseurs pour savoir si un bouton a été cliqué
bool Menu::isQuitClicked() const {
    return quitClicked;
}

bool Menu::isAboutClicked() const {
    return aboutClicked;
}

bool Menu::isPlayClicked() const {
    return playClicked;
}
// Réinitialise l'état du clic sur le bouton À propos
void Menu::resetAboutClicked() {
    aboutClicked = false;
}
//Réinitialise l'état du clic sur le bouton Jouer
void Menu::resetPlayClicked() {
    playClicked = false;
}




