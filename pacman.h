#ifndef PACMAN_H_INCLUDED
#define PACMAN_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "base.h"


class moviment_pac{
public:
    moviment_pac();
    ~moviment_pac();

    bool obstaculos(int, int, char**);
    virtual void mov_pac(int*, int*, int*, char**, int);
    void desenha(int*, int*, int*);
    void direcao_personagem(ALLEGRO_EVENT, char**, int, int);
    bool atualizaval(int);
    double getxm();
    double getym();
    int getpoints();
    bool pontuacao(int, int, char**);
    bool victory();
   
private:
    double xm, ym;
    bool tecla[5];
    int points, dire, sentido;
    ALLEGRO_BITMAP* movi;
};
#endif // PACMAN_H_INCLUDED
