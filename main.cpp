#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Menu.h"
#include "Apropos.h"
#include "Jeux.h"
#include "Chronometre.h"
#include "Mur.h"
#include "Velo.h"
#include <iostream>

int main() {
    //SDL_Init:initialise la bibl SDL pour l'utilisation de la vidio 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur d'initialisation SDL: " << SDL_GetError() << std::endl;//si init est echoué un msg d'erreur affiché avec SDL_GetError()
        return -1;//le programme se tirmine
    }
    //IMG_Init: initsialise la bibl SDLimage pour charger les image ou format PNG 
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0) {
        std::cerr << "Erreur d'initialisation SDL_image: " << IMG_GetError() << std::endl;
        SDL_Quit();//SDL quitter
        return -1;
    }
    //TTF_Init: inisialiser la biblio SDLttf pour utiliser des police 
    if (TTF_Init() == -1) {
        std::cerr << "Erreur d'initialisation SDL_ttf: " << TTF_GetError() << std::endl;//si init echoué msg d'erreur affiché
        IMG_Quit();//tout les bibl précédement initialisées sont fermées
        SDL_Quit();
        return -1;
    }
    //SDL_CreateWindow: Crée une fenêtre pour le jeu avec un titre, une position indéfinie(axe X et Y), une taille de 800x600 pixels
    SDL_Window* window = SDL_CreateWindow("BNvélo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Erreur création fenêtre: " << SDL_GetError() << std::endl;//si création échoué 
        TTF_Quit();//féemer tous les biblio
        IMG_Quit();
        SDL_Quit();
        return -1;
    }
   // SDL_CreateRenderer: créer un renderer pour dissiner sur un fenétre , sans renderer ne peux pas visuellement le contenu de ton jeux
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Erreur création renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);// si création echoué férmer la fenétre DL_CreateWindow et les biblio
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    TTF_Font* font = TTF_OpenFont("LiberationSansNarrow-BoldItalic.ttf", 24);//chrgement de police 
    if (!font) {
        std::cerr << "Erreur chargement police: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return -1;
    }
    //initaialisation des objet Menu et apropos
    //initialize(renderer): et une fenction appellent pour configurer l'affichage avec renderer et le police
    Menu menu;//création objet menu
    Apropos apropos;//création objet menu
    if (!menu.initialize(renderer)) {
        std::cerr << "Erreur initialisation menu." << std::endl;//si la fonction initialize, un msg erreur affiché et les ressources sont libérées 
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return -1;//programme terminer 
    }
    //comme objet menu
    if (!apropos.initialize(renderer, font)) {
        std::cerr << "Erreur initialisation apropos." << std::endl;
        menu.cleanUp();
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return -1;
    }
    //Boucle principale de programme
    SDL_Event e;// gérer les événements dans une appSDL, comme les interactions de l'utilisateur avec le système (clavier, souris, etc.)
    bool quit = false;
    bool showApropos = false;
    //cette boucle s'éxecute tant que 'quit' est faux 
    while (!quit) {
        //il récupére tous les évén SDL(clavier,souris,fermeture)
        while (SDL_PollEvent(&e) != 0) {
            //si la fenétre est férmée (SDL_Quit) le jeu s'arréte
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            //si on affiche la fenétre Apropos (showApropos est vrai)
            if (showApropos) {
                apropos.handleEvents(e);//les évenements sont envoyés à l'objet 'apropos'
                //si user clique sur 'Retour' on revient au menu principale
                if (apropos.isBackClicked()) {
                    showApropos = false;
                    apropos.resetBackClicked();
                }
                //sinon on traite les événements du menu 
            } else {
                menu.handleEvents(e);
                //quitter si l'option 'Quitter' est activée
                if (menu.isQuitClicked()) {
                    quit = true;
                //afficher la fenétre 'Apropos' si l'option est activée
                } else if (menu.isAboutClicked()) {
                    showApropos = true;
                    menu.resetAboutClicked();
                //lancer le jeu si 'jouer' est sélectionné 
                } else if (menu.isPlayClicked()) {
                    Jeux jeu(window, renderer);
                    //Le jeu est initialisé puis lancées 
                    if (jeu.initialize()) {
                        jeu.run();
                    //Erreur on affiche un msg 
                    } else {
                        std::cerr << "Erreur initialisation jeu." << std::endl;
                    }
                    menu.resetPlayClicked();
                }
            }
        }
          //affichage à l'écran
          //appelle les fonctions render  pour dessiner sur la fenétre
          //solon var showApropos soit on affiche fenetre Apropos soit le menu
        if (showApropos) {
            apropos.render(renderer);
        } else {
            menu.render(renderer);
        }
    }
  //libération des ressources avant fermeture 
    apropos.cleanUp();
    menu.cleanUp();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}








 