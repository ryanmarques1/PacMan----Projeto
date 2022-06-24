#ifndef MOVIMENT_H_INCLUDED
#define MOVIMENT_H_INCLUDED
#include <allegro5/allegro.h>
#include "pacman.h"


class moviment_pac{
    public:
        moviment_pac();
        // ~moviment_pac();
        char startMap();
        void TImprimir();
        void movimenta_personagem(ALLEGRO_EVENT,float*,float*);
        void teste_pac(ALLEGRO_BITMAP* , float * , float *);
        void direcao_personagem(ALLEGRO_EVENT,ALLEGRO_BITMAP*,int*,int*);
        bool colisao(int*,int*,int,int);
        int maX(int,int);
        int miN(int,int);
        void movi_cima(ALLEGRO_BITMAP *, ALLEGRO_EVENT);
        void movi_baixo(ALLEGRO_BITMAP *, ALLEGRO_EVENT);
        void movi_direita(ALLEGRO_BITMAP *, ALLEGRO_EVENT);
        void movi_esquerda(ALLEGRO_BITMAP *, ALLEGRO_EVENT);
    private:
        //ALLEGRO_BITMAP *movi;
        bool tecla[5];
        float x,y;
        char Map[20][20];
};
#endif // MOVIMENT_H_INCLUDED
