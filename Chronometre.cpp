#include "Chronometre.h"

// Constructeur de la classe Chronometre
Chronometre::Chronometre(Uint32 _duration)
    : duration(_duration), running(false), startTicks(0) {}

// Démarre le chronomètre en enregistrant le temps actuel
void Chronometre::start() {
    startTicks = SDL_GetTicks();// Enregistre le temps de démarrage
    running = true;// Met à jour l'état du chronomètre à "en cours"
}
// Arrête le chronomètre
void Chronometre::stop() {
    running = false;// Met à jour l'état du chronomètre à "arrêté"
}

// Réinitialise le chronomètre en enregistrant le temps actuel
void Chronometre::reset() {
    startTicks = SDL_GetTicks();// Réinitialise le temps de démarrage
}
// Renvoie le temps restant avant que le chronomètre n'expire
Uint32 Chronometre::getRemainingTime() const {
    if (!running) {
        return duration;// Si le chronomètre n'est pas en cours, renvoie la durée totale
    }
    Uint32 elapsed = SDL_GetTicks() - startTicks;// Calcule le temps écoulé
    if (elapsed >= duration) {
        return 0; // Si le temps écoulé dépasse la durée, renvoie 0
    }
    return duration - elapsed;// Renvoie le temps restant
}
// Vérifie si le chronomètre est en cours d'exécution
bool Chronometre::isRunning() const {
    return running;// Renvoie l'état du chronomètre
}