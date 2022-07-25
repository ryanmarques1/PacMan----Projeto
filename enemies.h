#ifndef ENEMIES_H_INCLUDED
#define ENEMIES_H_INCLUDED

#include <iostream>
#include "moviment.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

class inimigos : public moviment_pac{
    public:
        inimigos();
        ~inimigos();
        void desenha_inimigos(int*,int*,int*);
        void movi_random(int*,int*,int*,char**);
        virtual void mov_pac(int*, int*, int*, char**, int);
        int getdire();
        void colidiPac(int, int, int, int, int, int, ALLEGRO_FONT*);
        void MTop(int*, int*, char**);
        void MDown(int*, int*, char**);
        void MDir(int*, int*, char**);
        void MEsq(int*, int*, char**);
    private:
        ALLEGRO_BITMAP* inim;
        int dire, sentido,iten;
        double xm, ym;
};
#endif // ENEMIES_H_INCLUDED
