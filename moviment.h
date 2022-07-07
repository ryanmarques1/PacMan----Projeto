#ifndef MOVIMENT_H_INCLUDED
#define MOVIMENT_H_INCLUDED
#include <allegro5/allegro.h>
#include "pacman.h"


class moviment_pac{
    public:
        moviment_pac();
        // ~moviment_pac();
        char startMap(char [][20]);
        void TImprimir();
        void movimenta_personagem(ALLEGRO_EVENT, int*,int*);
        bool colisao(int,int,int,int,int,int,int,int);
        void desenha(ALLEGRO_BITMAP*,int*, int*);void teste_pac(ALLEGRO_BITMAP* , int * , int *);
        void direcao_personagem(ALLEGRO_EVENT,int*,int*);
        void conta_pilulas(int*,int*);
    private:
        bool tecla[5];
        char Map[20][20];
};
#endif // MOVIMENT_H_INCLUDED
