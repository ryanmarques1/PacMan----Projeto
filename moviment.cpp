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
    for(int i = 0; i < 5; i++){
        tecla[i]=false;
    }
    //x = y = 0;
    Map[20][20] = ' ';
    points = 0;
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


//void moviment_pac::teste_pac(ALLEGRO_BITMAP* movi, int a , int b){
//    if(!movi){
//        exit(-1);
//    }
//    al_draw_bitmap_region(movi,0,0,32,32,a,b,0);
//    cout << a << endl << b << endl << "-" << endl;
//    desenha(movi,&a,&b);
//    break;
//
//}

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
//    else if(ev.type == ALLEGRO_EVENT_KEY_UP){
//        switch(ev.keyboard.keycode){
//            case ALLEGRO_KEY_RIGHT:
//                tecla[KRIGHT] = false;
//                break;
//            case ALLEGRO_KEY_LEFT:
//                tecla[KLEFT] = false;
//                break;
//            case ALLEGRO_KEY_UP:
//                tecla[KUP] = false;
//                break;
//            case ALLEGRO_KEY_DOWN:
//                tecla[KDOWN] = false;
//                break;
//        }
//    }
}
void moviment_pac::mov_pac(ALLEGRO_BITMAP* movi,int* x, int* y,int *spr){
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
//        al_draw_bitmap_region(movi,0,4*32,32,32,*x,*y,0);
    }else
    if(tecla[KRIGHT] == true){
        *spr = 3;
        if(*x+32 <= 608){
            *x+=32;
        }
//        al_draw_bitmap_region(movi,0,3*32,32,32,*x,*y,0);
    }else
    if(tecla[KLEFT] == true){
        *spr = 1;
        if(*x-32 >= 32){
            *x-=32;
        }
//        al_draw_bitmap_region(movi,0,1*32,32,32,*x,*y,0);
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
void moviment_pac::pontuacao(int*x,int*y){
    if(this->Map[*x][*y] == 'P'){
        this->points+=25;
        this->Map[*x][*y] = '-';
    }

}
bool moviment_pac::colisao(int x,int y,int x2,int y2, int bx,int by,int bx2,int by2){
    if(x > bx2) return false;
    if(x2 < bx) return false;
    if(y > by2) return false;
    if(y2 < by) return false;

    return true;
}
