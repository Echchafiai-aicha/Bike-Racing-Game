#ifndef CHRONOMETRE_H
#define CHRONOMETRE_H
#include <SDL2/SDL.h>

// Classe représentant un chronomètre
class Chronometre {
private:
    Uint32 startTicks;  // Temps au démarrage
    Uint32 duration;    // Durée totale en ms
    bool running; // Indique si le chronomètre est en cours d'exécution

public:
     // Constructeur qui initialise le chronomètre avec une durée spécifiée
    Chronometre(Uint32 duration);
    void start();// Démarre le chronomètre
    void stop();// Arrête le chronomètre
    void reset();// Réinitialise le chronomètre à son état initial
    Uint32 getRemainingTime() const; // Renvoie le temps restant avant que le chronomètre n'expire
    bool isRunning() const;    // Vérifie si le chronomètre est en cours d'exécution
};
#endif // CHRONOMETRE_H