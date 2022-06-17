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
}

/*moviment_pac::~moviment_pac(){
    cout << "\ndestrutor moviment\n";
   //al_destroy_bitmap(movi);
}*/


void moviment_pac::movimenta_personagem(ALLEGRO_EVENT ev){
    int speed = 5;
    const int w = 672;
    const int w2 = 672;
   // float x = 0, y = 0;
    if(ev.type == ALLEGRO_EVENT_TIMER){
        printf("pos_x: %.2f pos_y: %.2f\n", x,y);
        if(tecla[KUP] && y >= 32.0)
            y -= tecla[KUP] + 5.0;
        if(tecla[KDOWN] && y <= w2 - 32.0 - 32.0)
            y+= tecla[KDOWN] + 5.0;
        if(tecla[KLEFT] && x >= 32.0)
            x-= tecla[KLEFT] + 5.0;
        if(tecla[KRIGHT] && x <= w -32.0 - 32.0)
            x+= tecla[KRIGHT] + 5.0;
    }
}
void moviment_pac::movi_cima(ALLEGRO_BITMAP *cima, ALLEGRO_EVENT ev){
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
        "PGAEPD-GE1FH-DPFAHP",
        "PBPPPB-B111B-BPPPBP",
        "PBPDPB-JAAAI-BPDPBP",
        "PBPBPB---0---BPBPBP",
        "PBPBPCPFAAAEPCPBPBP",
        "PBPBPPPPP-PPPPPBPBP",
        "PBPCPFAAAAAAAEPCPBP",
        "PBPPPPPPPPPPPPPPPBP",
        "PCPFAAAAAAAAAAAEPCP",
        "PPPPPPPPPPPPPPPPPPP",
    };
    int a = 32, b = 32;
    //cima = al_load_bitmap("Sprites/Personagens/Voltorb/VoltorbF.png");
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
    switch(ev.keyboard.keycode){
    case ALLEGRO_KEY_UP:
        tecla[KUP] = true;
        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 20; j++){
                if(aux[i][j] == '0'){
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
        "PGAEPD-GE1FH-DPFAHP",
        "PBPPPB-B111B-BPPPBP",
        "PBPDPB-JAAAI-BPDPBP",
        "PBPBPB---0---BPBPBP",
        "PBPBPCPFAAAEPCPBPBP",
        "PBPBPPPPP-PPPPPBPBP",
        "PBPCPFAAAAAAAEPCPBP",
        "PBPPPPPPPPPPPPPPPBP",
        "PCPFAAAAAAAAAAAEPCP",
        "PPPPPPPPPPPPPPPPPPP",
    };
    int a = 32, b = 32;
    //cima = al_load_bitmap("Sprites/Personagens/Voltorb/VoltorbF.png");
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
    switch(ev.keyboard.keycode){
        case ALLEGRO_KEY_DOWN:
            tecla[KDOWN] = true;
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            if(aux[i][j] == '0'){
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
        "PGAEPD-GE1FH-DPFAHP",
        "PBPPPB-B111B-BPPPBP",
        "PBPDPB-JAAAI-BPDPBP",
        "PBPBPB---0---BPBPBP",
        "PBPBPCPFAAAEPCPBPBP",
        "PBPBPPPPP-PPPPPBPBP",
        "PBPCPFAAAAAAAEPCPBP",
        "PBPPPPPPPPPPPPPPPBP",
        "PCPFAAAAAAAAAAAEPCP",
        "PPPPPPPPPPPPPPPPPPP",
    };
    int a = 32, b = 32;
    //cima = al_load_bitmap("Sprites/Personagens/Voltorb/VoltorbF.png");
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
    switch(ev.keyboard.keycode){
    case ALLEGRO_KEY_RIGHT:
        tecla[KRIGHT] = true;
        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 20; j++){
                if(aux[i][j] == '0'){
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
        "PGAEPD-GE1FH-DPFAHP",
        "PBPPPB-B111B-BPPPBP",
        "PBPDPB-JAAAI-BPDPBP",
        "PBPBPB---0---BPBPBP",
        "PBPBPCPFAAAEPCPBPBP",
        "PBPBPPPPP-PPPPPBPBP",
        "PBPCPFAAAAAAAEPCPBP",
        "PBPPPPPPPPPPPPPPPBP",
        "PCPFAAAAAAAAAAAEPCP",
        "PPPPPPPPPPPPPPPPPPP",
    };
    int a = 32, b = 32;
    //cima = al_load_bitmap("Sprites/Personagens/Voltorb/VoltorbF.png");
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
    switch(ev.keyboard.keycode){
        case ALLEGRO_KEY_LEFT:
        tecla[KLEFT] = true;
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            if(aux[i][j] == '0'){
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
}

