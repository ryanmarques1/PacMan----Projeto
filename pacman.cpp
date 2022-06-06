
#include "pacman.h"
#include <bits/stdc++.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>


using namespace std;

///Chamando construtores e destrutores.
/*
Map::Map(){ //
    cout << "Criando Construtor Padrao\n\n";
}
Map::Map(ALLEGRO_BITMAP *ptr){

}
pacman::~pacman(){
    cout << "Destruindo\n\n";

}
///Metodos
void Map::setMap(ALLEGRO_BITMAP* ptrS){
    mapa = al_load_bitmap("Sprites/mapa.png");
    mapa = ptrS;
}

ALLEGRO_BITMAP* Map::getMap(){
    return mapa;
}
void Map::imprimeMap(){
    al_draw_bitmap(getMap(),0,1,0);
}*/

tijolos::tijolos(){
    cout << "construtor padrao\n\n";
    til = NULL;
    //tij[0][0] = '\0';
}
/*tijolos::~tijolos(){
    cout << "destrutor\n\n";

}*/


pilulas::pilulas(){
    cout << "\nconstrutor padrao\n\n";
    pilu = NULL;
   // pil[0][0] = '\0';
}
/*pilulas::~pilulas(){
    cout << "\ndestrutor\n\n";
}*/


/*void pilulas::set_pil(){
    char aux[20][20] = {
        "PPPPPPPPPBPPPPPPPPP",
        "PFAEPGAEPCPFAHPFAEP",
        "PPPPPBPPPPPPPBPPPPP",
        "PFAEPBPDPDPDPBPFAEP",
        "PPPPPBPBPBPBPBPPPPP",
        "PFAEPBPCPCPCPBPFAEP",
        "PPPPPBPPPPPPPBPPPPP",
        "PFAAAIPFAAAEPJAAAEP",
        "PPPPPP-------PPPPPP",
        "PGAEPD-GE-FH-DPFAHP",
        "PBPPPB-B---B-BPPPBP",
        "PBPDPB-JAAAI-BPDPBP",
        "PBPBPB-------BPBPBP",
        "PBPBPCPFAAAEPCPBPBP",
        "PBPBPPPPP-PPPPPBPBP",
        "PBPCPFAAAAAAAEPCPBP",
        "PBPPPPPPPPPPPPPPPBP",
        "PCPFAAAAAAAAAAAEPCP",
        "PPPPPPPPPPPPPPPPPPP",
    };
    strcpy(pil[20],aux[20]);
}*/

void pilulas::desenha_pilu(ALLEGRO_BITMAP * ptrP){
    char aux[20][20] = {
        "PPPPPPPPPBPPPPPPPPP",
        "PFAEPGAEPCPFAHPFAEP",
        "PPPPPBPPPPPPPBPPPPP",
        "PFAEPBPDPDPDPBPFAEP",
        "PPPPPBPBPBPBPBPPPPP",
        "PFAEPBPCPCPCPBPFAEP",
        "PPPPPBPPPPPPPBPPPPP",
        "PFAAAIPFAAAEPJAAAEP",
        "PPPPPP-------PPPPPP",
        "PGAEPD-GE-FH-DPFAHP",
        "PBPPPB-B---B-BPPPBP",
        "PBPDPB-JAAAI-BPDPBP",
        "PBPBPB-------BPBPBP",
        "PBPBPCPFAAAEPCPBPBP",
        "PBPBPPPPP-PPPPPBPBP",
        "PBPCPFAAAAAAAEPCPBP",
        "PBPPPPPPPPPPPPPPPBP",
        "PCPFAAAAAAAAAAAEPCP",
        "PPPPPPPPPPPPPPPPPPP",
    };
    int i,j,x=32,y=32;
    for(i = 0 ; i < 20; i++){
        for(j = 0; j < 20; j++){
            if(aux[i][j] == 'P'){
                pilu = al_load_bitmap("Sprites/Candy.png");
                al_draw_bitmap(pilu,x,y,0);
            }
            x+=32;
        }
        x = 32;
        y+=32;
    }
}
/*void tijolos::set_tijo(){
    char aux[20][20] = {
        "PPPPPPPPPBPPPPPPPPP",
        "PFAEPGAEPCPFAHPFAEP",
        "PPPPPBPPPPPPPBPPPPP",
        "PFAEPBPDPDPDPBPFAEP",
        "PPPPPBPBPBPBPBPPPPP",
        "PFAEPBPCPCPCPBPFAEP",
        "PPPPPBPPPPPPPBPPPPP",
        "PFAAAIPFAAAEPJAAAEP",
        "PPPPPP-------PPPPPP",
        "PGAEPD-GE-FH-DPFAHP",
        "PBPPPB-B---B-BPPPBP",
        "PBPDPB-JAAAI-BPDPBP",
        "PBPBPB-------BPBPBP",
        "PBPBPCPFAAAEPCPBPBP",
        "PBPBPPPPP-PPPPPBPBP",
        "PBPCPFAAAAAAAEPCPBP",
        "PBPPPPPPPPPPPPPPPBP",
        "PCPFAAAAAAAAAAAEPCP",
        "PPPPPPPPPPPPPPPPPPP",
    };
    strcpy(tij[20],aux[20]);
}*/
void tijolos::desenha_tijo(ALLEGRO_BITMAP * ptrT){
    char aux[20][20] = {
        "PPPPPPPPPBPPPPPPPPP",
        "PFAEPGAEPCPFAHPFAEP",
        "PPPPPBPPPPPPPBPPPPP",
        "PFAEPBPDPDPDPBPFAEP",
        "PPPPPBPBPBPBPBPPPPP",
        "PFAEPBPCPCPCPBPFAEP",
        "PPPPPBPPPPPPPBPPPPP",
        "PFAAAIPFAAAEPJAAAEP",
        "PPPPPP-------PPPPPP",
        "PGAEPD-GE-FH-DPFAHP",
        "PBPPPB-B---B-BPPPBP",
        "PBPDPB-JAAAI-BPDPBP",
        "PBPBPB-------BPBPBP",
        "PBPBPCPFAAAEPCPBPBP",
        "PBPBPPPPP-PPPPPBPBP",
        "PBPCPFAAAAAAAEPCPBP",
        "PBPPPPPPPPPPPPPPPBP",
        "PCPFAAAAAAAAAAAEPCP",
        "PPPPPPPPPPPPPPPPPPP",
    };
    int i, j , x = 32, y = 32;
    for(i = 0; i < 20; i++){
        for(j = 0; j < 20; j++){
                switch(aux[i][j]){
                case 'A':
                    til = al_load_bitmap("Sprites/B1.png");
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'B':
                    til = al_load_bitmap("Sprites/B2.png");
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'C':
                    til = al_load_bitmap("Sprites/B3.png");
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'D':
                    til = al_load_bitmap("Sprites/B4.png");
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'E':
                    til = al_load_bitmap("Sprites/B5.png");
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'F':
                    til = al_load_bitmap("Sprites/B6.png");
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'G':
                    til = al_load_bitmap("Sprites/B7.png");
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'H':
                    til = al_load_bitmap("Sprites/B8.png");
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'I':
                    til = al_load_bitmap("Sprites/B9.png");
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'J':
                    til = al_load_bitmap("Sprites/B10.png");
                    al_draw_bitmap(til,x,y,0);
                    break;
                default:
                    break;
            }
            x+=32;
        }
        x = 32;
        y+=32;
    }
}
