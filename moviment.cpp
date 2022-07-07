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
     KRIGHT,KLEFT,KDOWN,KUP
};
moviment_pac::moviment_pac(){
    cout << "\nconstrutor padrão\n";
    tecla[4] = {false};
    //x = y = 0;
    Map[20][20] = ' ';
}

/*moviment_pac::~moviment_pac(){
    cout << "\ndestrutor moviment\n";
   //al_destroy_bitmap(movi);
}*/

char moviment_pac::startMap(char mapa[][20]){
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


void moviment_pac::teste_pac(ALLEGRO_BITMAP* movi, int *a , int *b){
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
void moviment_pac::desenha(ALLEGRO_BITMAP* movi,int* x, int* y){
    int spr = 0;
    if(tecla[KUP] == true){
        spr = 2;
        al_draw_bitmap_region(movi,0,2*32,32,32,*x,*y,0);
    }
    if(tecla[KDOWN] == true){
        spr = 4 ;
       // al_draw_bitmap_region(movi,0,4*32,32,32,*x,*y,0);
    }
    if(tecla[KRIGHT] == true){
        spr = 3;
      //  al_draw_bitmap_region(movi,0,3*32,32,32,*x,*y,0);
    }
    if(tecla[KLEFT] == true){
        spr = 1;
        //al_draw_bitmap_region(movi,0,1*32,32,32,*x,*y,0);
    }

}
void moviment_pac::direcao_personagem(ALLEGRO_EVENT ev, int *x,int *y){
     if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
        switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_UP:
                tecla[KUP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                tecla[KDOWN] = true;

                break;
            case ALLEGRO_KEY_RIGHT:
                tecla[KRIGHT] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                tecla[KLEFT] = true;
                break;
        }
        //al_draw_bitmap_region(movi,0,sprite*32,32,32,*x,*y,0);
        //al_flip_display();
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
            }
        }
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
void moviment_pac::conta_pilulas(int*x,int*y){
    int pontos = 0;
    if(Map[*x][*y] == 'P'){
            pontos++;
    }

}
bool moviment_pac::colisao(int x,int y,int x2,int y2, int bx,int by,int bx2,int by2){
    if(x > bx2) return false;
    if(x2 < bx) return false;
    if(y > by2) return false;
    if(y2 < by) return false;

    return true;
}
