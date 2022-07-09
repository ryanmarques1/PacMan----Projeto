#include <iostream>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "pacman.h"
#include "moviment.h"
using namespace std;

/*

Movimentação
------------
#include <allegro5/allegro5/allegro_primitives.h>

iniciar seu addon -> al_init_primitives_addon();

EVENT_KEY_UP -> EVENT_KEY_DOWN

declarar variaveis -> posi_x, posi_y. atribuindo um valor a cada.


ex: KEY_UP pressionada -<

------------
Movimentação

*/
enum keys_board{
     KRIGHT,KLEFT,KDOWN,KUP
};
moviment_pac::moviment_pac(){
    cout << "\nconstrutor padrão\n";
    for(int i = 0; i < 5; i++){
        tecla[i]=false;
    }
    points = 0;
    movi = NULL;
    if (!movi) cout << "Certo\n";
}
moviment_pac::~moviment_pac(){
    al_destroy_bitmap(this->movi);
}
/*
colisão ->
ter funções de max e min;

max ->
if(a >= b) return a;
else return b;

min ->
if(a <= b) return a;
else return b;

-----------------

colisão->
ter os bitmaps;
for i,j;
float x1,y1,x2,y2;
bool colisão = FALSE;
if(!(x1>x2 + largura bitmap) || (y1>y2 + altura bitmap) || (x2 > x1 + largura) || (y2 + y1 + altura))

cima = max entre y1 y2

*/
void moviment_pac::direcao_personagem(ALLEGRO_EVENT ev){
     if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
        switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_UP:
                tecla[KUP] = true;
                tecla[KLEFT] = false;
                tecla[KDOWN] = false;
                tecla[KRIGHT] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                tecla[KDOWN] = true;
                tecla[KLEFT] = false;
                tecla[KUP] = false;
                tecla[KRIGHT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                tecla[KRIGHT] = true;
                tecla[KLEFT] = false;
                tecla[KUP] = false;
                tecla[KDOWN] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                tecla[KLEFT] = true;
                tecla[KRIGHT] = false;
                tecla[KUP] = false;
                tecla[KDOWN] = false;
                break;
        }
    }
}
void moviment_pac::mov_pac(int* x, int* y,int *spr){
    if(tecla[KUP] == true){
        *spr = 2;
        if(*y-32 >= 32){
            *y-=32;
        }
    }else
    if(tecla[KDOWN] == true){
        *spr = 4 ;
        if(*y+32 <= 608){
            *y+=32;
        }
    }else
    if(tecla[KRIGHT] == true){
        *spr = 3;
        if(*x+32 <= 608){
            *x+=32;
        }
    }else
    if(tecla[KLEFT] == true){
        *spr = 1;
        if(*x-32 >= 32){
            *x-=32;
        }
    }
}
void moviment_pac::desenha(int* x, int* y, int* spr){
    movi = al_load_bitmap("Sprites/Personagens/Voltorb/Volt.png");
    if(!movi)exit(-1);
    al_draw_bitmap_region(movi,0,*spr*32,32,32,*x,*y,0);
}

void moviment_pac::movimenta_personagem(ALLEGRO_EVENT ev, int *x, int *y){
    if(ev.type == ALLEGRO_EVENT_TIMER){
        if(tecla[KUP] == true && *y >= 50)
            *y-=32;
        if(*y <= 672 - 50 - 32)
            *y+=32;
        if(*x <= 672 - 50 - 32)
            *x+=32;
        if(*x >= 50)
            *x-=32;
    }
}

void moviment_pac::pontuacao(int y,int x,char **Map){
    int w = 900, w2 = 672;
    ALLEGRO_FONT* txt = al_load_font("Fonts/04B_30__.ttf", 21, 0);
    al_draw_textf(txt, al_map_rgb(255, 0, 0), w - 128, w2 - 500, ALLEGRO_ALIGN_CENTER, "SCORE: %d", this->points);
    if(Map[x][y] == 'P'){
        this->points += 25;
//        cout << "Letra = " << Map[x][y] << endl;
//        cout << "Pos x = " << x << endl;
//        cout << "Pos y = " << y << endl;
//        for(int i = 0 ; i < 20; i++){
//            for(int j = 0; j < 20; j++){
//                cout << Map[i][j];
//            }
//            cout << endl;
//        }
        Map[x][y] = '-';
    }
    al_destroy_font(txt);
//    cout << this->points << endl;
}
bool moviment_pac::colisao(int x,int y,int x2,int y2, int bx,int by,int bx2,int by2){
    if(x > bx2) return false;
    if(x2 < bx) return false;
    if(y > by2) return false;
    if(y2 < by) return false;
    return true;
}
