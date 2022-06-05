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
        void set_tij(int* ,int*);
        int get_tij();
    private:
        ALLEGRO_BITMAP *tijo;
        int tij[15][15];
};

class pilulas{
    public:
        pilulas();
        //pilulas(int*);
        //~pilulas();
        ///Metodos;
        //int* create_pil();
        void set_pil(int*, int*);
        int get_pil();
    private:
        ALLEGRO_BITMAP *pilu;
        int pil[15][15];
};
#endif // PACMAN_H_INCLUDED
