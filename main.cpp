#include <bits/stdc++.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "pacman.h"
//Dimensões
#define W  800
#define W2 800
//Dimensões
using namespace std;


int main(){

   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_BITMAP* MAP = NULL;
   //int mapa[30][30];
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
   MAP = al_load_bitmap("Sprites/borda.png");
   if(!MAP){
        al_show_native_message_box(display,"Erro!","Erro!","A imagem não pode ser carregada",NULL,ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display); //destruindo ptr.
        return -1;
   }

   al_clear_to_color(al_map_rgb(0,0,0)); //Cor de background da tela
   al_draw_bitmap(MAP,0,0,0);
   al_flip_display();

   al_rest(9.0); //Tempo que a tela fica ativa (em segundos)

   al_destroy_display(display); //Destroi a tela
   al_destroy_bitmap(MAP);
   return 0;
}
