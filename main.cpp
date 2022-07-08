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
Pena, com os destrutores o allegro est� retornando um erro.

C:\temp\gcc\build\x86_64-w64-mingw32\libgcc\..\..\..\src\libgcc\unwind-seh.c|347|multiple definition of `_Unwind_Resume';
C:\allegro\lib\liballegro_monolith-debug.dll.a(d001015.o):(.text+0x0): first defined here|

Dei uma olhada no forum da allegro: https://www.allegro.cc/forums/thread/617487 , mesmo assim
retorna o mesmo erro. tentei usar essa vers�o da allegro
Allegro524_mingw-w64-gcc81_posix_dwarf e essa do mingw i686-8.1.0-release-posix-dwarf-rt_v6-rev0
e mesmo assim retorna o mesmo erro.
e nesse aqui tamb�m, https://www.allegro.cc/forums/thread/220924/220927

*/
///Grupo : Ryan Marques de Castro, Mariana de Deus Castro e Bernardo Teixeira de Miranda INTEGRAL.

//Dimens�es
#define W  900
#define W2 672
#define lines 20
#define columns 20

const float fps = 60.0; ///60 frames por segundo.
//Dimens�es
using namespace std;

enum keys_board{
     KEY_ENTER, KEY_ESCAPE
};

struct MapaFixo{
    char MPF[lines][columns]={
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
    al_set_audio_stream_playmode(m,ALLEGRO_PLAYMODE_LOOP);//Quando chega ao fim, recome�a desde o in�cio.
}
int main(){

   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_BITMAP* borda, *fundo;
   borda = fundo = NULL;
   ALLEGRO_EVENT_QUEUE *fila_events = NULL; ///ponteiro para fila de eventos
   ALLEGRO_TIMER *FPS = NULL; ///ptr timer;
   ALLEGRO_FONT *texto = NULL; ///ptr para texto;
   ///ponteiros de audio e som
   ALLEGRO_AUDIO_STREAM *music = NULL;
   ///ponteiros de audio e som

   /// Variaveis Padr�es ---------------------------------------------------------------------------------------------
    bool fim_loop = false; ///para o loop de eventos
    bool teclas[2] = {false,false}; ///teclas;
    int posi_x = 320, posi_y = 480, sprite = 0,spr = 4;
    int frame;

    char **MapaMain;
    MapaMain = (char**) malloc(20*sizeof(char*));
    for(int i = 0; i < 20; i++){
        MapaMain[i] =(char*) malloc(20*sizeof(char));
    }

   /// ---------------------------------------------------------------------------------------------------------------

   pilulas p;
   tijolos t;
   moviment_pac movi;
   if(!al_init()) {
      fprintf(stderr, "Falha ao iniciar o allegro!\n");
      return -1;
   }

    MapaFixo MPF;
    /// Setar Mapa do Arquivo na variavel
    for(int i = 0 ; i < 20; i++){
        for(int j = 0; j < 20; j++){
            MapaMain[i][j] = MPF.MPF[i][j];
        }
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
      fprintf(stderr, "Falha na cria��o do display!\n");
      return -1;
   }
   al_clear_to_color(al_map_rgb(0,0,0)); //Cor de background da tela

   ///Fundo e Borda
   fundo = al_load_bitmap("Sprites/Fundo.jpg");
   if(!fundo){
        al_show_native_message_box(display,"Erro!","Erro!","A imagem n�o pode ser carregada",NULL,ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display); //destruindo ptrdisplay.
        return -1;
   }

    borda = al_load_bitmap("Sprites/Borda.png");
    if(!borda){
        al_show_native_message_box(display,"Erro!","Erro!","A imagem n�o pode ser carregada",NULL,ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display); //destruindo ptrdisplay.
        return -1;
    }
    ///Fundo e Borda

    ///fila de eventos para a movimenta��o
    fila_events = al_create_event_queue();
    ///registrando quais tipos de eventos ter�
    al_register_event_source(fila_events, al_get_keyboard_event_source()); ///pegando eventos dos teclados ->
    al_register_event_source(fila_events, al_get_display_event_source(display)); ///pegandoe eventos do display.
    al_register_event_source(fila_events, al_get_timer_event_source(FPS)); ///registrando o temporizador na fila de eventos
    al_flip_display();
    al_start_timer(FPS);
    texto = al_load_font("Fonts/04B_30__.ttf", 30, 0);
    //   menu(texto);
    //music = al_load_audio_stream("audios/samba_amigo.ogg",4,1030);
    //music_menu(music);
    bool test = false;
    ALLEGRO_EVENT event;  //variavel que receber� o evento atual.
    //al_set_target_bitmap(pacm);
    //al_set_target_bitmap(al_get_backbuffer(display));
    //Inicio Game-----------------------------------------------------------------------------------------------------------------------
    while(!fim_loop){
        test = true;
        frame = al_get_timer_count(FPS);
        al_wait_for_event(fila_events, &event);
        //qual evento
        if(event.type == ALLEGRO_EVENT_TIMER){
            if(frame == (fps*1000)/200)
                al_set_timer_count(FPS,0);
        }
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
            fim_loop = true; ///clicando com no X;
        }else{
            movi.direcao_personagem(event);
            if(test && al_is_event_queue_empty(fila_events)){ // Redesenha
                p.destroi_pilu();
                t.destroi_tijo();
                movi.destroi_pac();
                ///destruidores
                al_clear_to_color(al_map_rgb(0,0,0));
                al_draw_bitmap(fundo,0,0,0);
                al_draw_bitmap(borda,0,0,0);
                p.desenha_pilu(MapaMain);
                t.desenha_tijo(MapaMain);
                movi.mov_pac(&posi_x,&posi_y,&spr);
                movi.desenha(&posi_x,&posi_y,&spr);
                ///redesenha
//              cout << "Pos x = " << posi_x << endl;
//              cout << "Pos y = " << posi_y << endl;
                movi.pontuacao((posi_x-32)/32,(posi_y-32)/32,MapaMain);
        //      menu_pontos(texto);

            }
        }
//        cout << "Pos x = " << posi_x << endl;
//        cout << "Pos y = " << posi_y << endl;
//        cout << "Spr = " << spr << endl;
        al_flip_display();


    }
    al_destroy_display(display);
    al_destroy_bitmap(borda);
    al_destroy_bitmap(fundo);
    al_destroy_event_queue(fila_events);
    al_destroy_timer(FPS);
    al_destroy_font(texto);
    ///destroyers;

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

