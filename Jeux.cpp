#include "Jeux.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

// Constructeur de la classe Jeux
Jeux::Jeux(SDL_Window* win, SDL_Renderer* ren)
    : window(win), renderer(ren), backgroundTexture(nullptr), bikeTexture(nullptr), murTexture(nullptr),
      font(nullptr), gameOverTexture(nullptr), running(false), gameOver(false),
      bike(nullptr), chronometre(60000) // 60 secondes
{
    srand(static_cast<unsigned int>(time(nullptr))); // Initialisation de la graine pour rand()
}
// Destructeur de la classe Jeux
Jeux::~Jeux() {
    cleanUp(); // Nettoyage des ressources
}
// Méthode pour initialiser le jeu
bool Jeux::initialize() {
    // Chargement de la police de caractères
    font = TTF_OpenFont("LiberationSansNarrow-BoldItalic.ttf", 50);
    if (!font) {
        std::cerr << "Erreur chargement police: " << TTF_GetError() << std::endl;
        return false;
    }
     // Chargement de l'image de fond
    SDL_Surface* bgSurface = IMG_Load("BGJ.png");
    if (!bgSurface) {
        std::cerr << "Erreur chargement image fond: " << IMG_GetError() << std::endl;
        return false;
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    if (!backgroundTexture) {
        std::cerr << "Erreur création texture fond: " << SDL_GetError() << std::endl;
        return false;
    }
     // Chargement de l'image du vélo
    SDL_Surface* bikeSurface = IMG_Load("vélo.png");
    if (!bikeSurface) {
        std::cerr << "Erreur chargement image vélo: " << IMG_GetError() << std::endl;
        return false;
    }
    bikeTexture = SDL_CreateTextureFromSurface(renderer, bikeSurface);
    SDL_FreeSurface(bikeSurface);
    if (!bikeTexture) {
        std::cerr << "Erreur création texture vélo: " << SDL_GetError() << std::endl;
        return false;
    }
      // Chargement de l'image des murs
    SDL_Surface* murSurface = IMG_Load("banane_final.png");
    if (!murSurface) {
        std::cerr << "Erreur chargement image mur: " << IMG_GetError() << std::endl;
        return false;
    }
    murTexture = SDL_CreateTextureFromSurface(renderer, murSurface);
    SDL_FreeSurface(murSurface);
    if (!murTexture) {
        std::cerr << "Erreur création texture mur: " << SDL_GetError() << std::endl;
        return false;
    }
    // Création de l'objet vélo à la position donnée avec la texture chargée
    bike = new Velo(375, 520, 80, 80, bikeTexture);
        // Initialisation des murs avec position en x aléatoire et position y échelonnée vers le haut

    murs.clear();
    for (int i = 0; i < 5; i++) {
        int x = rand() % (800 - 50);// Position x aléatoire
        int y = -i * 150; // Position y pour échelonner les murs vers le haut hors écran
        murs.emplace_back(x, y, 50, 50);
    }

    running = true;// Démarrage du jeu
    gameOver = false;// Jeu non terminé

    chronometre.start();// Démarrage du chronomètre

    updateGameOverTexture("Game Over");// Préparation du message Game Over

    return true;
}
// Gestion des évènements SDL
void Jeux::handleEvents(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
        running = false;
    }
     // Gestion de l'entrée clavier pour déplacer le vélo si le jeu n'est pas fini
    if (!gameOver) {
        const Uint8* keys = SDL_GetKeyboardState(nullptr);
        if (bike) {
            bike->handleInput(keys);
        }
    }
}
// Mise à jour de l'état du jeu
void Jeux::update() {
    if (gameOver) return;

    int speed = 5;// Vitesse de déplacement des murs

    for (auto& mur : murs) {
        mur.update(speed);  // Mise à jour position du mur
         // Vérification collision entre le vélo et un mur
        if (bike && checkCollision(bike->rect, mur.rect)) {
            gameOver = true;// Fin du jeu si collision détectée
            chronometre.stop(); // Arrêt du chronomètre
            updateGameOverTexture("Dommage, vous avez perdu ");
        }
    }
    // Vérification fin du temps de jeu
    if (chronometre.getRemainingTime() == 0) {
        gameOver = true;
        chronometre.stop();
        updateGameOverTexture(" Fin du jeu, bravo !");
    }
}
// Rendu visuel du jeu
void Jeux::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);// Couleur de fond noire
    SDL_RenderClear(renderer);// Nettoyer l'écran
    // Affichage du fond
    if (backgroundTexture) SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
    // Affichage des murs
    for (auto& mur : murs) {
        mur.render(renderer, murTexture);
    }
    // Affichage du vélo
    if (bike) bike->render(renderer);

    // Affichage du temps restant (en haut droite)
    if (font && !gameOver) {
        Uint32 remainingMs = chronometre.getRemainingTime();
        int seconds = remainingMs / 1000;
        std::string timeText = "Temps: " + std::to_string(seconds) + "s";

        SDL_Color white = {255, 255, 255, 255};
        SDL_Surface* surface = TTF_RenderText_Solid(font, timeText.c_str(), white);
        SDL_Texture* timeTexture = SDL_CreateTextureFromSurface(renderer, surface);

        int w, h;
        SDL_QueryTexture(timeTexture, nullptr, nullptr, &w, &h);
        SDL_Rect textRect = {800 - w - 10, 10, w, h};
        SDL_RenderCopy(renderer, timeTexture, nullptr, &textRect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(timeTexture);
    }

     // Affichage du message Game Over au centre
    if (gameOver && gameOverTexture) {
        int w, h;
        SDL_QueryTexture(gameOverTexture, nullptr, nullptr, &w, &h);
        SDL_Rect rect = {(800 - w) / 2, (600 - h) / 2, w, h};
        SDL_RenderCopy(renderer, gameOverTexture, nullptr, &rect);
    }

    SDL_RenderPresent(renderer);
}
// Nettoyage des ressources allouées
void Jeux::cleanUp() {
    if (bike) {
        delete bike;
        bike = nullptr;
    }
    murs.clear();

    if (bikeTexture) {
        SDL_DestroyTexture(bikeTexture);
        bikeTexture = nullptr;
    }
    if (murTexture) {
        SDL_DestroyTexture(murTexture);
        murTexture = nullptr;
    }
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = nullptr;
    }
    if (gameOverTexture) {
        SDL_DestroyTexture(gameOverTexture);
        gameOverTexture = nullptr;
    }
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}
// Vérifie la collision entre deux rectangles SDL
bool Jeux::checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return SDL_HasIntersection(&a, &b);
}
// Boucle principale du jeu
void Jeux::run() {
    SDL_Event event;
    while (running) {
         // Gestion des événements SDL
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            handleEvents(event);
        }
        update();// Mise à jour du jeu
        render();// Affichage du jeu
        SDL_Delay(16);   // Pause pour approx. 60 images par seconde
    }
}
// Met à jour la texture du message Game Over affiché au centre
void Jeux::updateGameOverTexture(const std::string& msg) {
    if (gameOverTexture) { // Déstruction de l'ancienne texture si existante
        SDL_DestroyTexture(gameOverTexture);
        gameOverTexture = nullptr;
    }

    SDL_Color red = {255, 255, 0, 255}; // Couleur rouge pour le message
    SDL_Surface* surface = TTF_RenderText_Solid(font, msg.c_str(), red);
    gameOverTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

 