#include "Apropos.h"
#include <iostream>
#include <sstream>

// Constructeur de la classe Apropos
Apropos::Apropos() : backgroundTexture(nullptr), backClicked(false), font(nullptr) {
    // Initialisation du texte de description
    descriptionText = 
        "                                                 \n"
        " Un jeu ou le joueur controle un cycliste devant eviter   \n"
        " des obstacles dans un temps limite,Utilise les fleches pour\n"
        "  se deplacer et SDL2 pour les graphismes.Le jeu comprend\n"
        "  un chronometre, des collisions et un menu principal.\n"
        "Perdez si vous touchez un mur ou si le temps s ecoule.";
// Initialisation des rectangles pour la description et le bouton "Retour"
    descriptionRect = { 100,200, 600, 200 };
    backButtonRect = { 300, 500, 200, 50 };
}
// Destructeur de la classe Apropos
Apropos::~Apropos() {
    cleanUp();
}
// Méthode pour initialiser le menu "À propos"
bool Apropos::initialize(SDL_Renderer* renderer, TTF_Font* f) {
    font = f;// Assignation de la police
    // Chargement de l'image de fond
    SDL_Surface* backgroundSurface = IMG_Load("BGM.png");
    if (!backgroundSurface) {
        std::cerr << "Erreur chargement image fond: " << IMG_GetError() << std::endl;
        return false;
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    if (!backgroundTexture) {
        std::cerr << "Erreur création texture fond: " << SDL_GetError() << std::endl;
        return false;
    }
    // Chargement de la police
    font = TTF_OpenFont("LiberationSansNarrow-BoldItalic.ttf", 24);
    if (!font) {
        std::cerr << "Erreur chargement police: " << TTF_GetError() << std::endl;
        return false;
    }
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);

    return true;
}
// Gestion des événements liés à la souris
void Apropos::handleEvents(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = e.button.x;
        int mouseY = e.button.y;
        // Vérification du clic sur le bouton "Retour"
        if (mouseX >= backButtonRect.x && mouseX <= backButtonRect.x + backButtonRect.w &&
            mouseY >= backButtonRect.y && mouseY <= backButtonRect.y + backButtonRect.h) {
            backClicked = true;
        }
    }
}
// Méthode pour afficher la fenêtre "À propos"
void Apropos::render(SDL_Renderer* renderer) {
      // Afficher la texture de fond
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
      // Dessiner un rectangle jaune pour la zone de description
    SDL_SetRenderDrawColor(renderer, 255, 210 ,0, 255);
    SDL_RenderFillRect(renderer, &descriptionRect);
 // Découper le texte en lignes et les dessiner une à une
    std::istringstream iss(descriptionText);
    std::string line;
    int lineHeight = 30;
    int yOffset = descriptionRect.y;

    while (std::getline(iss, line)) {
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, line.c_str(), {255, 255, 255, 255});
        if (textSurface) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);

            int textWidth, textHeight;
            SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

            SDL_Rect textRect;
            textRect.w = textWidth;
            textRect.h = textHeight;
            textRect.x = descriptionRect.x + (descriptionRect.w - textWidth) / 2;
            textRect.y = yOffset;

            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
            SDL_DestroyTexture(textTexture);

            yOffset += lineHeight;
        } else {
            std::cerr << "Erreur création surface texte: " << TTF_GetError() << std::endl;
        }
    }
    // Dessiner un rectangle rouge pour le bouton "Retour"
    SDL_SetRenderDrawColor(renderer, 230, 0, 0, 255);
    SDL_RenderFillRect(renderer, &backButtonRect);
     // Afficher le texte "Fermer" centré dans le bouton
    if (font) {
        SDL_Surface* closeTextSurface = TTF_RenderText_Blended(font, "Fermer", {255, 255, 255, 255});
        if (closeTextSurface) {
            SDL_Texture* closeTextTexture = SDL_CreateTextureFromSurface(renderer, closeTextSurface);

            SDL_Rect textRect;
            textRect.w = closeTextSurface->w;
            textRect.h = closeTextSurface->h;
            textRect.x = backButtonRect.x + (backButtonRect.w - textRect.w) / 2;
            textRect.y = backButtonRect.y + (backButtonRect.h - textRect.h) / 2;

            SDL_FreeSurface(closeTextSurface);

            if (closeTextTexture) {
                SDL_RenderCopy(renderer, closeTextTexture, nullptr, &textRect);
                SDL_DestroyTexture(closeTextTexture);
            } else {
                std::cerr << "Erreur création texture texte 'Fermer': " << SDL_GetError() << std::endl;
            }
        } else {
            std::cerr << "Erreur création surface texte 'Fermer': " << TTF_GetError() << std::endl;
        }
    }

    SDL_RenderPresent(renderer);
}
// Nettoyage des ressources
void Apropos::cleanUp() {
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = nullptr;
    }
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}
// Indique si le bouton "Retour" a été cliqué
bool Apropos::isBackClicked() const {
    return backClicked;
}
// Réinitialiser l'état du bouton "Retour"
void Apropos::resetBackClicked() {
    backClicked = false;
}
