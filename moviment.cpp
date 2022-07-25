#include <iostream>
#include <Windows.h>
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

Movimenta��o
------------
#include <allegro5/allegro5/allegro_primitives.h>

iniciar seu addon -> al_init_primitives_addon();

EVENT_KEY_UP -> EVENT_KEY_DOWN

declarar variaveis -> posi_x, posi_y. atribuindo um valor a cada.


ex: KEY_UP pressionada -<

------------
Movimenta��o

*/
enum keys_board{
     KRIGHT,KLEFT,KDOWN,KUP
};
moviment_pac::moviment_pac(){
    cout << "\nconstrutor padr�o\n";
    for(int i = 0; i < 5; i++){
        tecla[i]=false;
    }
    this->xm = 0;
    this->ym = 0;
    points = 0;
    dire = 0;
    sentido = 0;
    movi = NULL;
    if (!movi) cout << "Certo\n";
}
moviment_pac::~moviment_pac(){
    al_destroy_bitmap(this->movi);
}

void moviment_pac::direcao_personagem(ALLEGRO_EVENT ev, char** m,int x, int y){
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

        if (y - 4 >= 32 && obstaculos(a, b - 1, m) ) {
            dire = 0;
        }
    }else
    if (atualizaval(x) && sentido == 1) {
        a = ceil((double)(x) / (double)32);
        b = ((double)(y) / (double)32);
        a--;
        b--;
        if (y + 4 <= 608 && obstaculos(a, b + 1, m)) {
            dire = 1;
        }
    }else
    if (atualizaval(y) && sentido == 2) {
        a = ((double)(x) / (double)32);
        b = ceil((double)(y) / (double)32);
        a--;
        b--;
        if(x+ 4 <= 608 && obstaculos(a+ 1, b, m)){
            dire = 2;
        }
    }else
    if (atualizaval(y) && sentido == 3) {
        a = ceil((double)(x) / (double)32);
        b = ceil((double)(y) / (double)32);
        a--;
        b--;
        if(x- 4 >= 32 && obstaculos(a - 1, b, m)){
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
        //cout << "A: " << a << " Resto: " << a % 32 << endl;
        return true;
    }
    else {
        //cout << "Resto: *" << endl;
        return false;
    }
}

void moviment_pac::mov_pac(int* x, int* y,int *spr, char** m, int dir=9){
    int bit = 4;
    if (dir != 9) {
        dire = dir;
    }
    if(dire == 0){
        //cout << "T1" << endl;
        *spr = 2;
        if (atualizaval(*x)) {  
            //cout << "Aqui" << endl;
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
        //cout << "T2" << endl;
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
        //cout << "T3" << endl;
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
        //cout << "T4" << endl;
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
double moviment_pac::getxm() {
    return this->xm;
}
double moviment_pac::getym() {
    return this->ym;
}
void moviment_pac::desenha(int* x, int* y, int* spr){
    movi = al_load_bitmap("Sprites/Personagens/Voltorb/Volt.png");
    if(!movi)exit(-1);
    al_draw_bitmap_region(movi,0,*spr*32,32,32,*x,*y,0);
}



void moviment_pac::pontuacao(int y,int x,char **Map, ALLEGRO_FONT* t, ALLEGRO_AUDIO_STREAM* m, ALLEGRO_SAMPLE* p){
    int w = 900, w2 = 672;
    int sons;
    

    if (!t || !m || !p) {
        printf("Erro ao carregar o texto, e sons/audios\n");
        exit(-1);
    }
    
    al_draw_textf(t, al_map_rgb(255, 0, 0), w - 130, w2 - 500, ALLEGRO_ALIGN_CENTER, "SCORE: %d", this->points);
    if(Map[x][y] == 'P'){
    
          al_play_sample(p, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_BIDIR, NULL);
        this->points += 30;
        Map[x][y] = '-';
       
    }
    
    if (this->points == 4900) {
       
        al_draw_textf(t, al_map_rgb(255, 0, 0), w - 135, w2 - 600, ALLEGRO_ALIGN_CENTER,"V I C T O R Y");
        al_attach_audio_stream_to_mixer(m, al_get_default_mixer());
        al_set_audio_stream_playmode(m, ALLEGRO_PLAYMODE_LOOP);//Quando chega ao fim, recome�a desde o in�cio.
       
    }

    
}

