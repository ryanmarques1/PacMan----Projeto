#include "pacman.h"
#include "moviment.h"
#include "enemies.h"
#include <bits/stdc++.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
Pena, com os destrutores o allegro está retornando um erro.

C:\temp\gcc\build\x86_64-w64-mingw32\libgcc\..\..\..\src\libgcc\unwind-seh.c|347|multiple definition of `_Unwind_Resume';
C:\allegro\lib\liballegro_monolith-debug.dll.a(d001015.o):(.text+0x0): first defined here|

Dei uma olhada no forum da allegro: https://www.allegro.cc/forums/thread/617487 , mesmo assim
retorna o mesmo erro. tentei usar essa versão da allegro
Allegro524_mingw-w64-gcc81_posix_dwarf e essa do mingw i686-8.1.0-release-posix-dwarf-rt_v6-rev0
e mesmo assim retorna o mesmo erro.
e nesse aqui também, https://www.allegro.cc/forums/thread/220924/220927

*/
///Grupo : Ryan Marques de Castro, Mariana de Deus Castro e Bernardo Teixeira de Miranda INTEGRAL.

//Dimensões
#define W  672
#define W2 900
#define lines 20
#define columns 20

const float fps = 60.0; ///60 frames por segundo.
//Dimensões
using namespace std;

enum keys_board{
     KEY_ENTER, KEY_ESCAPE
};
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
void menu(ALLEGRO_FONT *text){
    //text = al_load_font("Fonts/04B_30__.ttf", 45, NULL);
    if(!text){
        al_show_native_message_box(al_get_current_display(), "Erro load font", "Erro text", "Erro ao carregar a fonte...", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(al_get_current_display());
        exit(-1);
    }
    al_draw_textf(text,al_map_rgb(255,0,0), W/2,W2/2.5,ALLEGRO_ALIGN_CENTER,"Press ENTER for Start");
    al_draw_textf(text,al_map_rgb(255,0,255), W/2,W2/2,ALLEGRO_ALIGN_CENTER, "Press ESC for Exit");
    al_flip_display();
}
void menu_pontos(ALLEGRO_FONT *text){
    if(!text){
        al_show_native_message_box(al_get_current_display(), "Erro load font", "Erro text", "Erro ao carregar a fonte...", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(al_get_current_display());
        exit(-1);
    }
    al_draw_textf(text,al_map_rgb(255,0,255), W/2,W2-200,ALLEGRO_ALIGN_CENTER,"Menu de Pontos e Mortes");
}
void music_menu(ALLEGRO_AUDIO_STREAM *m){
    //m = al_load_audio_stream("audios/samba_amigo.ogg", 4, 1024);
    if(!m){
         al_show_native_message_box(al_get_current_display(),"Erro music","Erro critico","Erro ao carregar a musica...",NULL,ALLEGRO_MESSAGEBOX_ERROR);
         al_destroy_display(al_get_current_display());
         exit(-1);
    }
    al_attach_audio_stream_to_mixer(m,al_get_default_mixer());
    al_set_audio_stream_playmode(m,ALLEGRO_PLAYMODE_LOOP);//Quando chega ao fim, recomeça desde o início.
}
int main(){

   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_BITMAP* borda, *fundo, *pilu, *tijo, *pacm, *pacm2;
   borda = fundo = pilu = tijo = pacm = pacm2 =NULL;
   ALLEGRO_EVENT_QUEUE *fila_events = NULL; ///ponteiro para fila de eventos
   ALLEGRO_TIMER *FPS = NULL; ///ptr timer;
   ALLEGRO_FONT *texto = NULL; ///ptr para texto;
   ///ponteiros de audio e som
   ALLEGRO_AUDIO_STREAM *music = NULL;
   ///ponteiros de audio e som
   bool fim_loop = false; ///para o loop de eventos
   bool teclas[2] = {false,false}; ///teclas;
   int posi_x = 0, posi_y = 0, sprite = 0;
   int x = 0, y = 0;
   int frame;
   pilulas p;
   tijolos t;
   personagem pp;
   moviment_pac movi;
   if(!al_init()) {
      fprintf(stderr, "Falha ao iniciar o allegro!\n");
      return -1;
   }
   ///addons
   al_init_image_addon();
   al_install_keyboard();
   al_install_audio();
   al_init_acodec_addon();
   al_reserve_samples(1);
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();

   FPS = al_create_timer(1.0/fps);

   ///addons
   display = al_create_display(W, W2); //Cria uma tela com essas dimensoes
   if(!display) {
      fprintf(stderr, "Falha na criação do display!\n");
      return -1;
   }
   al_clear_to_color(al_map_rgb(0,0,0)); //Cor de background da tela

   ///Fundo e Borda
   pacm = al_load_bitmap("Sprites/Personagens/Voltorb/Volt.png");
   fundo = al_load_bitmap("Sprites/Fundo.jpg");
   if(!fundo){
        al_show_native_message_box(display,"Erro!","Erro!","A imagem não pode ser carregada",NULL,ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display); //destruindo ptrdisplay.
        return -1;
   }

   borda = al_load_bitmap("Sprites/Borda.png");
   if(!borda){
        al_show_native_message_box(display,"Erro!","Erro!","A imagem não pode ser carregada",NULL,ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display); //destruindo ptrdisplay.
        return -1;
   }
   ///Fundo e Borda

   ///fila de eventos para a movimentação
   fila_events = al_create_event_queue();
   ///registrando quais tipos de eventos terá
   al_register_event_source(fila_events, al_get_keyboard_event_source()); ///pegando eventos dos teclados ->
   al_register_event_source(fila_events, al_get_display_event_source(display)); ///pegandoe eventos do display.
   al_register_event_source(fila_events, al_get_timer_event_source(FPS)); ///registrando o temporizador na fila de eventos
   al_flip_display();
   al_start_timer(FPS);
   texto = al_load_font("Fonts/04B_30__.ttf", 30, NULL);
   menu(texto);
   //music = al_load_audio_stream("audios/samba_amigo.ogg",4,1030);
   //music_menu(music);
   bool test = false;
   bool re = false;
   ALLEGRO_EVENT event;  //variavel que receberá o evento atual.
   //al_set_target_bitmap(pacm);
   //al_set_target_bitmap(al_get_backbuffer(display));
   //Inicio Game-----------------------------------------------------------------------------------------------------------------------
   while(!fim_loop){

        //printf("pos_x: %.2f pos_y: %.2f\n", posi_x,posi_y);
         frame = al_get_timer_count(FPS);
         al_wait_for_event(fila_events, &event);
        //qual evento
        if(event.type == ALLEGRO_EVENT_TIMER){
            //movi.movimenta_personagem(&posi_x,&posi_y)
             movi.movimenta_personagem(event,&posi_x,&posi_y);

        }
       else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            //movi.conta_pilulas(&x,&y);
            movi.direcao_personagem(event,&posi_x,&posi_y);
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_ENTER:
                    teclas[KEY_ENTER] = true; ///quando apertado, vira true.
                    test = true;
                    movi.startMap(mapa);
                    if(music != NULL){
                        al_destroy_audio_stream(music); ///musica do menu para.
                        music = NULL;
                    }
                    al_clear_to_color(al_map_rgb(0,0,0));
                    al_draw_bitmap(fundo,0,0,0);
                    al_draw_bitmap(borda,0,0,0);
                    p.desenha_pilu(pilu);
                    t.desenha_tijo(tijo);

                    menu_pontos(texto);
                    break;
                default:
                    break;
            } //se o evento é algo relacionado a alguma tecla apertada
        }else if(event.type == ALLEGRO_EVENT_KEY_UP){
            if(teclas[KEY_ENTER]== true)
                teclas[KEY_ENTER] = false;
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
            fim_loop = true; ///clicando com no X;

        }
         if(test && al_is_event_queue_empty(fila_events)){
          test = false;
          al_clear_to_color(al_map_rgb(0,0,0));
        }
        al_draw_bitmap(fundo,0,0,0);
        al_draw_bitmap(borda,0,0,0);
        p.desenha_pilu(pilu);
        t.desenha_tijo(tijo);
       movi.desenha(pacm,&posi_x,&posi_y);
        menu_pontos(texto);
        al_flip_display();

   }
   ///destroyers;
   al_destroy_display(display);
   al_destroy_bitmap(borda);
   al_destroy_bitmap(fundo);
   al_destroy_bitmap(pilu);
   al_destroy_bitmap(tijo);
   al_destroy_bitmap(pacm);
   al_destroy_event_queue(fila_events);
   al_destroy_timer(FPS);
   al_destroy_font(texto);
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
