#ifndef ENEMIES_H_INCLUDED
#define ENEMIES_H_INCLUDED

#include <iostream>
#include "moviment.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

class inimigos : public moviment_pac{
    public:
        inimigos();
        ~inimigos();

        void desenha_inimigos(int*,int*,int*);
        void movi_random(int*,int*,int*,char**);
        void movi_inteligente(int*, int*, int*,int*, char**);
        void colidiPac(int, int, int,int);
        
        //void movi_random2(int*, int*, char**);
    private:
        ALLEGRO_BITMAP* inim;
        int dire, sentido;
        double xm, ym;
};
#endif // ENEMIES_H_INCLUDED
