#include <bits/stdc++.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro.h>
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
     KRIGHT,KLEFT,KDOWN,KUP,KEY_ENTER
};
moviment_pac::moviment_pac(){
    cout << "\nconstrutor padrão\n";
    //movi = NULL;
    tecla[5] = {false};
    x = y = 0;
    Map[20][20] = ' ';
}

/*moviment_pac::~moviment_pac(){
    cout << "\ndestrutor moviment\n";
   //al_destroy_bitmap(movi);
}*/

char moviment_pac::startMap(){
    char Aux[20][20] ={
        "PPPPPPPPPBPPPPPPPPP",
        "PFAEPGAEPCPFAHPFAEP",
        "PPPPPBPPPPPPPBPPPPP",
        "PFAEPBPDPDPDPBPFAEP",
        "PPPPPBPBPBPBPBPPPPP",
        "PFAEPBPCPCPCPBPFAEP",
        "PPPPPBPPPPPPPBPPPPP",
        "PFAAAIPFAAAEPJAAAEP",
        "PPPPPP-------PPPPPP",
        "PGAEPD-GE1FH-DPFAHP",
        "PBPPPB-B111B-BPPPBP",
        "PBPDPB-JAAAI-BPDPBP",
        "PBPBPB-------BPBPBP",
        "PBPBPCPFAAAEPCPBPBP",
        "PBPBPPPPP0PPPPPBPBP",
        "PBPCPFAAAAAAAEPCPBP",
        "PBPPPPPPPPPPPPPPPBP",
        "PCPFAAAAAAAAAAAEPCP",
        "PPPPPPPPPPPPPPPPPPP",
    };
    int i,j;
    for(i = 0 ; i < 20; i++){
        for(j = 0; j < 20; j++){
            Map[i][j] = Aux [i][j];
        }
    }
    return Map[20][20];
}

////Teste para Imprimir
//void moviment_pac::TImprimir(){
//    int i,j;
//    for(i = 0 ; i < 20; i++){
//        for(j = 0; j < 20; j++){
//            printf("%c ",Map[i][j]);
//        }
//        printf("\n");
//    }
//}

/*void moviment_pac::movimenta_personagem(ALLEGRO_EVENT ev, float *x, float *y){
//    int speed = 5;
    const int w = 672;
    const int w2 = 672;
   // float x = 0, y = 0;
    if(ev.type == ALLEGRO_EVENT_TIMER){
//        printf("pos_x: %.2f pos_y: %.2f\n", x,y);
        if(tecla[KUP] && *y >= 64.0)
            *y -=5.0;
        if(tecla[KDOWN] && *y <= 672 - 64.0 )
            *y+= 5.0;
        if(tecla[KLEFT] && *x>= 64.0)
            *x-= 5.0;
        if(tecla[KRIGHT] && *x <= 672 - 64.0)
            *x+= 5.0;
    }
}*/
void moviment_pac::teste_pac(ALLEGRO_BITMAP* movi, float *a , float *b){
    int i , j;
    for(i = 0; i < 20; i++){
        for(j = 0; j < 20; j++){
            if(Map[i][j] == '0'){
                if(!movi)
                    exit(-1);
                al_draw_bitmap_region(movi,0,0,32,32,*a,*b,0);
            }
            *a+=32;
        }
        *a = 32;
        *b+=32;
    }
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
void moviment_pac::direcao_personagem(ALLEGRO_EVENT ev,ALLEGRO_BITMAP* movi,int* x,int* y){
    int i = 0, j = 0;
    int tempo, sprite = 0, fator = 1;
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
//            sprite+=1;
        switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_UP:
                tecla[KUP] = true;
                //(*y >= 0.0) ? *y-=10.0 : 0;
                    if(*y <= 32.0 && !colisao(x,y,32,32))
                        *y+=32;
                    else
                        *y-=32;
                sprite=2;
                //al_draw_bitmap_region(movi,0,2*32,32,32,*x,*y,0);
                break;
            case ALLEGRO_KEY_DOWN:
                tecla[KDOWN] = true;
                //(*y <= 672 - 32.0) ? *y+=10.0 : 0;
                    if(*y >= 672 - 32 - 32 )
                        *y-=32;
                    else
                        *y+=32;
                sprite = 4;
                //al_draw_bitmap_region(movi,0,4*32,32,32,*x,*y,0);
                break;
            case ALLEGRO_KEY_RIGHT:
                tecla[KRIGHT] = true;
                //*x+=10.0;
                    if(*x >= 672 - 32 - 32)
                        *x-=32;
                    else
                        *x+=32;
                sprite = 3;
               //al_draw_bitmap_region(movi,0,3*32,32,32,*x,*y,0);
                break;
            case ALLEGRO_KEY_LEFT:
                tecla[KLEFT] = true;
                //(*x >= 0.0) ? *x-=10.0 : 0
                    if(*x <= 32)
                        *x+=32;
                    else
                        *x-=32;
                sprite = 1;
                //al_draw_bitmap_region(movi,0,1*32,32,32,*x,*y,0);
                break;
            default:
                break;
        }
        al_draw_bitmap_region(movi,0,sprite*32,32,32,*x,*y,0);
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_UP){
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_RIGHT:
                    tecla[KRIGHT] = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    tecla[KLEFT] = false;
                    break;
                case ALLEGRO_KEY_UP:
                    tecla[KUP] = false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    tecla[KDOWN] = false;
                    break;
                default:
                    break;
            }
        }

}
int moviment_pac::maX(int x, int y){
    if(x >= y){
        return x;
    }
    else return y;
}
int moviment_pac::miN(int x, int y){
    if(x <= y){
        return x;
    }
    else return y;
}
bool moviment_pac::colisao(int *x,int *y,int x2,int y2){
    int i = 0, j = 0;
    const int w = 32, h = 32;
    int up,down,dir,esq;
    bool colidiu = false;
    if(!(*x > x2 + w)|| (*y > y2 + h) || (x2 > *x + w) || (y2 > *y + h)){
        up = maX(*y,y2);
        down = miN(*y + h,y2+h);
        esq = maX(*x,x2);
        dir = miN(*x + w, x2 + w);
    }
    for(i = up; i < down && !colidiu;i++){
        for(j = esq; j < dir && !colidiu; j++){
            colidiu = true;
        }
    }
    return colidiu;
}
/*
void moviment_pac::movi_cima(ALLEGRO_BITMAP *cima, ALLEGRO_EVENT ev){
    int a = 32, b = 32;
    //cima = al_load_bitmap("Sprites/Personagens/Voltorb/VoltorbF.png");
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
    switch(ev.keyboard.keycode){
    case ALLEGRO_KEY_UP:
        tecla[KUP] = true;
        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 20; j++){
                if(Map[i][j] == '0'){
                    if(!cima)
                        exit(-1);
                    al_draw_bitmap(cima,a,b,0);
                }
                a+=32;
            }
            a = 32;
            b+=32;
        }
        break;
    }
    }else if(ev.type == ALLEGRO_EVENT_KEY_UP){
        switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_UP:
                tecla[KUP] = false;
                break;
        }
    }
}
void moviment_pac::movi_baixo(ALLEGRO_BITMAP *baixo, ALLEGRO_EVENT ev){
    int a = 32, b = 32;
    //cima = al_load_bitmap("Sprites/Personagens/Voltorb/VoltorbF.png");
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
    switch(ev.keyboard.keycode){
        case ALLEGRO_KEY_DOWN:
            tecla[KDOWN] = true;
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            if(Map[i][j] == '0'){
                if(!baixo)
                    exit(-1);
                al_draw_bitmap(baixo,a,b,0);
            }
            a+=32;
        }
        a = 32;
        b+=32;
    }
    break;
    }
    }else if(ev.type == ALLEGRO_EVENT_KEY_UP){
        switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_DOWN:
                tecla[KDOWN] = false;
                break;
        }
    }
}
void moviment_pac::movi_direita(ALLEGRO_BITMAP *direita, ALLEGRO_EVENT ev){
    int a = 32, b = 32;
    //cima = al_load_bitmap("Sprites/Personagens/Voltorb/VoltorbF.png");
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
    switch(ev.keyboard.keycode){
    case ALLEGRO_KEY_RIGHT:
        tecla[KRIGHT] = true;
        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 20; j++){
                if(Map[i][j] == '0'){
                    if(!direita)
                        exit(-1);
                    al_draw_bitmap(direita,a,b,0);
                }
                a+=32;
            }
            a = 32;
            b+=32;
        }
        break;
    }
    }else if(ev.type == ALLEGRO_EVENT_KEY_UP){
        switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_RIGHT:
                tecla[KRIGHT] = false;
                break;
        }
    }
}
void moviment_pac::movi_esquerda(ALLEGRO_BITMAP *esquerda, ALLEGRO_EVENT ev){
    int a = 32, b = 32;
    //cima = al_load_bitmap("Sprites/Personagens/Voltorb/VoltorbF.png");
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
    switch(ev.keyboard.keycode){
        case ALLEGRO_KEY_LEFT:
        tecla[KLEFT] = true;
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            if(Map[i][j] == '0'){
                if(!esquerda)
                    exit(-1);
                al_draw_bitmap(esquerda,a,b,0);
            }
            a+=32;
        }
        a = 32;
        b+=32;
    }
    break;
    }
    }else if(ev.type == ALLEGRO_EVENT_KEY_UP){
        switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_LEFT:
                tecla[KLEFT] = false;
                break;
        }
    }
}*/
