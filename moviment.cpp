#include <iostream>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "pacman.h"
#include "moviment.h"
#include <string.h>
#include <math.h>
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
    this->xm = 0;
    this->ym = 0;
    points = 0;
    dire = 2;
    sentido = 2;
    movi = NULL;
    if (!movi) cout << "Certo\n";
}
moviment_pac::~moviment_pac(){
    al_destroy_bitmap(this->movi);
}

void moviment_pac::direcao_personagem(ALLEGRO_EVENT ev, char** m,int x, int y){
    cout << "Sen: " << sentido << endl;
    cout << "X: " << x << " Y: " << y << endl;

    int a, b;
     if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
        switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_UP:
                sentido = 0;
                break;
            case ALLEGRO_KEY_DOWN:
                sentido = 1;
                break;
            case ALLEGRO_KEY_RIGHT:
                sentido = 2;
                break;
            case ALLEGRO_KEY_LEFT:
                sentido = 3;
                break;
        }
        
    }

    if (atualizaval(x) && sentido == 0) {
        a = ceil((double)(x) / (double)32);
        b = ceil((double)(y) / (double)32);
        a--;
        b--;

        if (y - 8 >= 32 && obstaculos(a, b - 1, m) ) {
            dire = 0;
        }
    }else
    if (atualizaval(x) && sentido == 1) {
        a = ceil((double)(x) / (double)32);
        b = ((double)(y) / (double)32);
        a--;
        b--;
        if (y + 8 <= 608 && obstaculos(a, b + 1, m)) {
            dire = 1;
        }
    }else
    if (atualizaval(y) && sentido == 2) {
        a = ((double)(x) / (double)32);
        b = ceil((double)(y) / (double)32);
        a--;
        b--;
        if(x+8 <= 608 && obstaculos(a+ 1, b, m)){
            dire = 2;
        }
    }else
    if (atualizaval(y) && sentido == 3) {
        a = ceil((double)(x) / (double)32);
        b = ceil((double)(y) / (double)32);
        a--;
        b--;
        if(x-8 >= 32 && obstaculos(a - 1, b, m)){
            dire = 3;
        }
    }
}

bool moviment_pac::obstaculos(int x, int y, char** m) {
    if (x >= 0 && y >= 0) {
        if ((m[y][x] == 'P' || m[y][x] == '-' || m[y][x] == '0' || m[y][x] == '1')) {
            return true;
        }
        else {
            return false;

        }
    }
}

bool moviment_pac::atualizaval(int a){
    if (a % 32 == 0) {
        cout << "A: " << a << " Resto: " << a % 32 << endl;
        return true;
    }
    else {
        cout << "Resto: *" << endl;
        return false;
    }
}

void moviment_pac::mov_pac(int* x, int* y,int *spr, char** m){
    int bit = 4;

    if(dire == 0){
        *spr = 2;
        if (atualizaval(*x)) {           
            this->xm = ceil((double)(*x) / (double)32);
            this->ym = ceil((double)(*y) / (double)32);
            this->xm--;
            this->ym--;

            if(*y-bit >= 32 && obstaculos(this->xm, this->ym-1,m)){
                *y-=bit;
            }
        }
    }else
    if(dire == 1){
        *spr = 4;
        if (atualizaval(*x)) {
            this->xm = ceil((double)(*x) / (double)32);
            this->ym = ((double)(*y) / (double)32);
            this->xm--;
            this->ym--;
            if(*y+bit <= 608 && obstaculos(this->xm, this->ym + 1, m)){
                *y+=bit;
            }
        }
    }else
    if(dire == 2){
        *spr = 3;
        if (atualizaval(*y)) {
            this->xm = ((double)(*x) / (double)32);
            this->ym = ceil((double)(*y) / (double)32);
            this->xm--;
            this->ym--;
            if(*x+bit <= 608 && obstaculos(this->xm + 1, this->ym, m)){
                *x+=bit;
            }
        }
    }else
    if(dire == 3){
        *spr = 1;
        if (atualizaval(*y)) {
            this->xm = ceil((double)(*x) / (double)32);
            this->ym = ceil((double)(*y) / (double)32);
            this->xm--;
            this->ym--;
            if(*x-bit >= 32 && obstaculos(this->xm - 1, this->ym, m)){
                *x-=bit;
            }
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

