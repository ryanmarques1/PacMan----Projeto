#ifndef MOVIMENT_H_INCLUDED
#define MOVIMENT_H_INCLUDED
#include <allegro5/allegro.h>
#include "pacman.h"


class moviment_pac{
    public:
        moviment_pac();
       ~moviment_pac();

        char startMap(char [][20]);
        void TImprimir();
        void movimenta_personagem(ALLEGRO_EVENT, int*,int*);
        bool obstaculos(int,int,char**);
        void mov_pac(int*, int*,int*, char**);
        void desenha(int*,int*,int*);
        void direcao_personagem(ALLEGRO_EVENT, char**,int,int);
        void pontuacao(int,int,char**);
        bool atualizaval(int);

    private:
        double xm, ym,x32,y32;
        bool tecla[5];
        int points,dire,sentido;
        ALLEGRO_BITMAP *movi;
};
#endif // MOVIMENT_H_INCLUDED
