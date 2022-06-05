#include <bits/stdc++.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "pacman.h"
//Dimensões
#define W  672
#define W2 672
#define lines 20
#define columns 20
//Dimensões
using namespace std;
char mapa[lines][columns] = {
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

void desenha_tijpil(ALLEGRO_BITMAP *pil, ALLEGRO_BITMAP *til){
    int i,j, x = 32, y=32;
    pil = til = NULL;
    for(i = 0; i < lines; i++){
        for(j = 0; j < columns; j++){
            printf("%c ", mapa[i][j]);
            if(mapa[i][j] == 'P'){
                pil = al_load_bitmap("Sprites/Candy.png");
                al_draw_bitmap(pil,x,y,0);
            }
            switch(mapa[i][j]){
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
        y +=32;
        cout << endl;
    }
}
int main(){

   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_BITMAP* borda, *fundo, *pilu, *tijo;
   borda = fundo = pilu = tijo = NULL;
   pilulas p;
   tijolos t;
   /*
   ALLEGRO_SAMPLE* audio = NULL;
   ALLEGRO_SAMPLE_INSTANCE* mix = NULL;
   ALLEGRO_EVENT_QUEUE *events = NULL;
   bool key_board[255] = {false};

   */
   if(!al_init()) {
      fprintf(stderr, "Falha ao iniciar o allegro!\n");
      return -1;
   }
   ///addons
   al_init_image_addon();
   al_install_keyboard();

   display = al_create_display(W, W2); //Cria uma tela com essas dimensoes
   if(!display) {
      fprintf(stderr, "Falha na criação do display!\n");
      return -1;
   }
   al_clear_to_color(al_map_rgb(0,0,0)); //Cor de background da tela

   ///Fundo e Borda
   fundo = al_load_bitmap("Sprites/Fundo.jpg");
   if(!fundo){
        al_show_native_message_box(display,"Erro!","Erro!","A imagem não pode ser carregada",NULL,ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display); //destruindo ptr.
        return -1;
   }
   al_draw_bitmap(fundo,0,0,0);
   borda = al_load_bitmap("Sprites/Borda.png");
   if(!borda){
        al_show_native_message_box(display,"Erro!","Erro!","A imagem não pode ser carregada",NULL,ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display); //destruindo ptr.
        return -1;
   }
   al_draw_bitmap(borda,0,0,0);
   ///Fundo e Borda

   desenha_tijpil(pilu,tijo); ///coloca sprites das pilulas e tijolos na tela.
   al_flip_display();
   al_rest(150.0); //Tempo que a tela fica ativa (em segundos)
   ///destroyers;
   al_destroy_display(display);
   al_destroy_bitmap(borda);
   al_destroy_bitmap(fundo);
   al_destroy_bitmap(pilu);
   al_destroy_bitmap(tijo);
   return 0;
}





///- = vazio, P = pilula.
/*
Muro
A -> B1
B -> B2
C -> B3
D -> B4
E -> B5
F -> B6
G -> B7
H -> B8
I -> B9
J -> B10
*/

/*int mapa[lines][columns] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};*/
