#include "base.h"
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
using namespace std;

///BASE DE TODAS CARREGA PILULAS E TIJOLOS
///Grupo : Ryan Marques de Castro, Mariana de Deus Castro e Bernardo Teixeira de Miranda INTEGRAL.
///Chamando construtores e destrutores.

tijolos::tijolos(){
    cout << "construtor padrao\n";
    for(int i = 0; i < 10; i++)
        til[i] = NULL;
    if (!til) cout << "Certo2\n";
}

pilulas::pilulas(){
    cout << "\nconstrutor padrao\n";
    pilu = NULL;
    if (!pilu) cout << "Certo3\n";

}

tijolos::~tijolos(){
   // int i, j;
    for (int i = 0; i < 10; i++) {
        al_destroy_bitmap(this->til[i]);
    }
}

pilulas::~pilulas(){
    al_destroy_bitmap(this->pilu);
}
void pilulas::desenha_pilu(char **aux){ ///196 Doces
    int i,j;
    float x=32,y=32;
    pilu = al_load_bitmap("Sprites/Candy.png");
    if (!pilu) {
        al_show_native_message_box(al_get_current_display(), "Erro!", "Erro!", "A imagem não pode ser carregada", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        exit(-1);
    }
    for(i = 0 ; i < 20; i++){
        for(j = 0; j < 20; j++){
            if(aux[i][j] == 'P'){
                al_draw_bitmap(pilu,x,y,0);
            }
            x+=32;
        }
        x = 32;
        y+=32;
    }
}

void tijolos::desenha_tijo(char **aux){
    til[0] = al_load_bitmap("Sprites/B1.png");
    til[1] = al_load_bitmap("Sprites/B2.png");
    til[2] = al_load_bitmap("Sprites/B3.png");
    til[3] = al_load_bitmap("Sprites/B4.png");
    til[4] = al_load_bitmap("Sprites/B5.png");
    til[5] = al_load_bitmap("Sprites/B6.png");
    til[6] = al_load_bitmap("Sprites/B7.png");
    til[7] = al_load_bitmap("Sprites/B8.png");
    til[8] = al_load_bitmap("Sprites/B9.png");
    til[9] = al_load_bitmap("Sprites/B10.png");


    int i, j;
    int ac = 0;
    float x = 32, y = 32;
    for(i = 0; i < 20; i++){
        for(j = 0; j < 20; j++){
            
                switch(aux[i][j]){
                case 'A':
                    if(!til[0]) exit(-1);
                    al_draw_bitmap(til[0], x, y, 0);
                 
                    break;
                case 'B':
                    if(!til[1]) exit(-1);
                    al_draw_bitmap(til[1], x, y, 0);
          
                    break;
                case 'C':
                    if(!til[2]) exit(-1);
                    al_draw_bitmap(til[2], x, y, 0);
             
                    break;
                case 'D':
                    if(!til[3]) exit(-1);
                    al_draw_bitmap(til[3], x, y, 0);
   
                    break;
                case 'E':
                    if(!til[4]) exit(-1);
                    al_draw_bitmap(til[4], x, y, 0);
 
                    break;
                case 'F':
                    if(!til[5]) exit(-1);
                    al_draw_bitmap(til[5], x, y, 0);

                    break;
                case 'G':
                    if(!til[6]) exit(-1);
                    al_draw_bitmap(til[6], x, y, 0);

                    break;
                case 'H':
                    if(!til[7]) exit(-1);
                    al_draw_bitmap(til[7], x, y, 0);

                    break;
                case 'I':
                    if(!til[8]) exit(-1);
                    al_draw_bitmap(til[8], x, y, 0);
 
                    break;
                case 'J':
                    if(!til[9]) exit(-1);
                    al_draw_bitmap(til[9], x, y, 0);

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
