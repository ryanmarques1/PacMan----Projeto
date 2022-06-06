#ifndef PACMAN_H_INCLUDED
#define PACMAN_H_INCLUDED
#include <bits/stdc++.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "pacman.h"
class tijolos{
    public:
        tijolos();
        //tijolos(int*);
        //~tijolos();
        ///Metodos;
       // int* create_tij();
       void set_tijo();
       void desenha_tijo(ALLEGRO_BITMAP *);
    private:
        ALLEGRO_BITMAP *til;
        //char tij[20][20];
};

class pilulas{
    public:
        pilulas();
        //pilulas(int*);
        //~pilulas();
        ///Metodos;
        //int* create_pil();
        void set_pil();
        //char** get_pil();
        void desenha_pilu(ALLEGRO_BITMAP *);
    private:
        ALLEGRO_BITMAP *pilu;
        //char pil[20][20];
};
#endif // PACMAN_H_INCLUDED
