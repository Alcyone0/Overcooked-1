//
// Created by ACER on 07/04/2024.
//

#include "musique.h"
#include <allegro.h>

void musique(){
    // Initialisation du son
    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
        allegro_message("Erreur lors de l'initialisation du son.");
        return;
    }


    SAMPLE *musique = load_sample("C:\\Users\\ACER\\Documents\\info\\overcook\\test2\\son\\tarantella-napoletana-164475.wav");
    if (!musique) {
        allegro_message("Erreur lors du chargement de la musique.");
        return;
    }

    // Jouer la musique en boucle
    play_sample(musique, 255, 128, 1000, TRUE);
}