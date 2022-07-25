#include "pacman.h"
#include "moviment.h"
#include "enemies.h"
#include "enemiesint.h"
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

///Grupo : Ryan Marques de Castro, Mariana de Deus Castro e Bernardo Teixeira de Miranda INTEGRAL.

//Dimensões
#define W  900
#define W2 672
//-----------//
//Dimensoes da matriz
#define lines 20
#define columns 20

const float fps = 60.0; ///60 frames por segundo.
//Dimensões
using namespace std;



struct MapaFixo {
    char MPF[lines][columns] = {
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
        "PBPBPPPPP0PPPPPBPBP",
        "PBPCPFAAAAAAAEPCPBP",
        "PBPPPPPPPPPPPPPPPBP",
        "PCPFAAAAAAAAAAAEPCP",
        "PPPPPPPPPPPPPPPPPPP",
    };
};


int main() {

    ALLEGRO_DISPLAY* display = NULL; //ptr display
    ALLEGRO_BITMAP* borda, * fundo; ///bitmap da borda e fundo
    borda = fundo = NULL;
    ALLEGRO_EVENT_QUEUE* fila_events = NULL; ///ponteiro para fila de eventos
    ALLEGRO_TIMER* FPS = NULL; ///ptr timer 
    ALLEGRO_AUDIO_STREAM* msc = NULL;
    ALLEGRO_SAMPLE* pills = NULL;
    ALLEGRO_FONT* txt, *txt2 = NULL;
    ALLEGRO_SAMPLE_INSTANCE* ins = NULL;
    /// Variaveis Padrões ---------------------------------------------------------------------------------------------
    bool fim_loop = false; ///para o loop de eventos

    //Posições x e y do pac e spr para troca
    int posi_x = 320, posi_y = 480, spr = 4;
    //Posições x e y do pac e spr para troca
    
    //Posições x e y dos fantasmas e sprites para troca.
    int posi_xf[5], posi_yf[5], spr2[4], spr3;
    spr2[0] = 1; spr2[1] = 1; spr2[2] = 1; spr2[3] = 1; spr3 = 1;

    int ant_px = 0;
    int ant_py = 0;
    posi_xf[0] = 32; posi_xf[1] = 608; posi_xf[2] = 608; posi_xf[3] = 32;
    posi_yf[0] = 32; posi_yf[1] = 608; posi_yf[2] = 32; posi_yf[3] = 608;
    posi_xf[4] = 288; posi_yf[4] = 288;
    //Posições x e y dos fantasmas e sprites para troca.
    
    char** MapaMain;
    MapaMain = (char**)malloc(20 * sizeof(char*));
    for (int i = 0; i < 20; i++) {
        MapaMain[i] = (char*)malloc(20 * sizeof(char)); ///Alocando a matriz de char.
    }

    /// ---------------------------------------------------------------------------------------------------------------
    pilulas p;
    tijolos t;
    moviment_pac movi, *movifm[5]; //classe base
    inimigos i[4]; //classe inimigo random
    inimigos_int iN; ///classe inimigo inteligente
    //Ponteiro da classe basica, polimorfismo.
    movifm[0] = &i[0]; 
    movifm[1] = &i[1];
    movifm[2] = &i[2]; 
    movifm[3] = &i[3];
    movifm[4] = &iN;
    //Ponteiro da classe basica, polimorfismo.
    if (!al_init()) {
        fprintf(stderr, "Falha ao iniciar o allegro!\n"); ///iniciando allegro.
        return -1;
    }
    MapaFixo MPF;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            MapaMain[i][j] = MPF.MPF[i][j]; ///Atribuindo a matriz.
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

    FPS = al_create_timer(1.0 / fps); //definido a contagem do fps

    ///addons
    display = al_create_display(W, W2); //Cria uma tela com essas dimensoes
    if (!display) {
        fprintf(stderr, "Falha na criação do display!\n");
        return -1;
    }
    al_clear_to_color(al_map_rgb(0, 0, 0)); //Cor de background da tela

    ///Fundo e Borda
    fundo = al_load_bitmap("Sprites/Fundo.jpg");
    if (!fundo) {
        al_show_native_message_box(display, "Erro!", "Erro!", "A imagem não pode ser carregada", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display); //destruindo ptrdisplay.
        return -1;
    }

    borda = al_load_bitmap("Sprites/Borda.png");
    if (!borda) {
        al_show_native_message_box(display, "Erro!", "Erro!", "A imagem não pode ser carregada", NULL, ALLEGRO_MESSAGEBOX_ERROR);
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
    
    bool test = false; //redesenha
    ALLEGRO_EVENT event;  //variavel que receberá o evento atual.
    msc = al_load_audio_stream("audios/theme_victory.ogg", 4, 1024);
    pills = al_load_sample("audios/pills.ogg");
    txt = al_load_font("Fonts/Vermin_Vibes_1989.ttf", 25, 0);
    txt2 = al_load_font("Fonts/Vermin_Vibes_1989.ttf", 30, 0);
    ins = al_create_sample_instance(pills);
    al_attach_sample_instance_to_mixer(ins, al_get_default_mixer());
    //Inicio Game-----------------------------------------------------------------------------------------------------------------------
    while (!fim_loop) {
        test = true;
        al_wait_for_event(fila_events, &event);
        ant_px = posi_x;
        ant_py = posi_y;
        //qual evento
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            fim_loop = true; ///clicando com no X;
        }
        else {

            movi.direcao_personagem(event, MapaMain, posi_x, posi_y);
            if ((test && al_is_event_queue_empty(fila_events))) {// Redesenha
                ///destruidores
                p.~pilulas();
                t.~tijolos();
                movi.~moviment_pac();
                for (int j = 0; j < 4; j++) {
                    i[j].~inimigos();
                }
                //-------------------
                al_clear_to_color(al_map_rgb(0, 0, 0)); //clear no mapa
                al_draw_bitmap(fundo, 0, 0, 0); //desenha fundo
                al_draw_bitmap(borda, 0, 0, 0); //desenha borda
                p.desenha_pilu(MapaMain); //desenha pilulas
                t.desenha_tijo(MapaMain); //desenha tijolos
                movi.mov_pac(&posi_x, &posi_y, &spr, MapaMain,9); //mov pac
                movi.desenha(&posi_x, &posi_y, &spr); //desenha pac

                for (int j = 0; j < 4; j++) {
                    i[j].movi_random(&posi_xf[j], &posi_yf[j], &spr2[j], MapaMain);
                    movifm[j]->mov_pac(&posi_xf[j], &posi_yf[j], &spr2[j], MapaMain,i[j].getdire());
                    
                    i[j].desenha_inimigos(&posi_xf[j], &posi_yf[j], &spr2[j]);
                    i[j].colidiPac(posi_x, posi_y, posi_xf[j], posi_yf[j], ant_px,ant_py,txt2);
                }
               iN.movi_inteligente(&posi_x, &posi_y, &posi_xf[4], &posi_yf[4], MapaMain);
               movifm[4]->mov_pac(&posi_xf[4], &posi_yf[4],&spr3, MapaMain, iN.getdire());
               iN.desenha_inimigoInt(&posi_xf[4], &posi_yf[4], &spr3);
               iN.colidiPac(posi_x, posi_y, posi_xf[4], posi_yf[4], ant_px, ant_py,txt2);

               movi.pontuacao((posi_x - 32) / 32, (posi_y - 32) / 32, MapaMain,txt,msc,pills);
                
            }
        }
        al_flip_display();
    }
    al_destroy_display(display);
    al_destroy_bitmap(borda);
    al_destroy_bitmap(fundo);
    p.~pilulas();
    t.~tijolos();
    movi.~moviment_pac();
    for (int j = 0; j < 4; j++) {
        i[j].~inimigos();
    }
    iN.~inimigos_int();
    al_destroy_event_queue(fila_events);
    al_destroy_timer(FPS);
    al_destroy_audio_stream(msc);
    al_destroy_font(txt);
    al_destroy_font(txt2);
    ///destroyers
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

