#include "pacman.h"
#include "moviment.h"
#include "enemies.h"
#include "enemiesint.h"
#include <Windows.h>
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
#define lines 20
#define columns 20

const float fps = 60.0; ///60 frames por segundo.
//Dimensões
using namespace std;

enum keys_board {
    KEY_ENTER, KEY_ESCAPE
};

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
        "PGAEPD-GEEFH-DPFAHP",
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

void menu(ALLEGRO_FONT* text) {
    //text = al_load_font("Fonts/04B_30__.ttf", 45, NULL);
    if (!text) {
        al_show_native_message_box(al_get_current_display(), "Erro load font", "Erro text", "Erro ao carregar a fonte...", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(al_get_current_display());
        exit(-1);
    }
    al_draw_textf(text, al_map_rgb(255, 0, 0), W / 2, W2 / 2.5, ALLEGRO_ALIGN_CENTER, "Press ENTER for Start");
    al_draw_textf(text, al_map_rgb(255, 0, 255), W / 2, W2 / 2, ALLEGRO_ALIGN_CENTER, "Press ESC for Exit");
    al_flip_display();
}
void music_menu(ALLEGRO_AUDIO_STREAM* m) {
    //m = al_load_audio_stream("audios/samba_amigo.ogg", 4, 1024);
    if (!m) {
        al_show_native_message_box(al_get_current_display(), "Erro music", "Erro critico", "Erro ao carregar a musica...", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(al_get_current_display());
        exit(-1);
    }
    al_attach_audio_stream_to_mixer(m, al_get_default_mixer());
    al_set_audio_stream_playmode(m, ALLEGRO_PLAYMODE_LOOP);//Quando chega ao fim, recomeça desde o início.
}
int main() {

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_BITMAP* borda, * fundo;
    borda = fundo = NULL;
    ALLEGRO_EVENT_QUEUE* fila_events = NULL; ///ponteiro para fila de eventos
    ALLEGRO_TIMER* FPS = NULL; ///ptr timer;
    ALLEGRO_FONT* texto = NULL; ///ptr para texto;
    ///ponteiros de audio e som
    ALLEGRO_AUDIO_STREAM* music = NULL;
    ///ponteiros de audio e som

    /// Variaveis Padrões ---------------------------------------------------------------------------------------------
    bool fim_loop = false; ///para o loop de eventos
    bool teclas[2] = { false,false }; ///teclas;
    int posi_x = 320, posi_y = 480, spr = 4, spr2[4], frame;
    int posi_xf[5], posi_yf[5];
    spr2[0] = 1; spr2[1] = 1 ; spr2[2] = 1 ; spr2[3] = 1 ;
    posi_xf[0] = 32; posi_xf[1] = 608; posi_xf[2] = 608; posi_xf[3] = 32;
    posi_yf[0] = 32; posi_yf[1] = 608; posi_yf[2] = 32; posi_yf[3] = 608;
    posi_xf[4] = 288; posi_yf[4] = 288;

    //------------//
    char** MapaMain;
    MapaMain = (char**)malloc(20 * sizeof(char*));
    for (int i = 0; i < 20; i++) {
        MapaMain[i] = (char*)malloc(20 * sizeof(char));
    }

    /// ---------------------------------------------------------------------------------------------------------------
    pilulas p;
    tijolos t;
    moviment_pac movi, *movifm[5];
    inimigos i[4];
    inimigos_int iN;
    movifm[0] = &i[0]; 
    movifm[1] = &i[1];
    movifm[2] = &i[2]; 
    movifm[3] = &i[3];
    movifm[4] = &iN;
    if (!al_init()) {
        fprintf(stderr, "Falha ao iniciar o allegro!\n");
        return -1;
    }
    MapaFixo MPF;
    /// Setar Mapa do Arquivo na variavel
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
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

    FPS = al_create_timer(1.0 / fps);

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
    texto = al_load_font("Fonts/04B_30__.ttf", 30, 0);
    //   menu(texto);
    //music = al_load_audio_stream("audios/samba_amigo.ogg",4,1030);
    //music_menu(music);
    bool test = false;
    ALLEGRO_EVENT event;  //variavel que receberá o evento atual.
    //al_set_target_bitmap(pacm);
    //al_set_target_bitmap(al_get_backbuffer(display));
    //Inicio Game-----------------------------------------------------------------------------------------------------------------------
    while (!fim_loop) {
        test = true;
        al_wait_for_event(fila_events, &event);
        frame = al_get_timer_count(FPS);
        //qual evento
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            fim_loop = true; ///clicando com no X;
        }
        else {

            movi.direcao_personagem(event, MapaMain, posi_x, posi_y);
            //i.direcao_fantasma(MapaMain, posi_xf[0], posi_yf[0]);
            if ((test && al_is_event_queue_empty(fila_events))) {// Redesenha
                ///destruidores
                p.~pilulas();
                t.~tijolos();
                movi.~moviment_pac();
                for (int j = 0; j < 2; j++) {
                    i[j].~inimigos();
                }
                //-------------------
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_bitmap(fundo, 0, 0, 0);
                al_draw_bitmap(borda, 0, 0, 0);
                p.desenha_pilu(MapaMain);
                t.desenha_tijo(MapaMain);
                movi.mov_pac(&posi_x, &posi_y, &spr, MapaMain,9);
                movi.desenha(&posi_x, &posi_y, &spr);

                for (int j = 0; j < 4; j++) {
                    i[j].movi_random(&posi_xf[j], &posi_yf[j], &spr2[j], MapaMain);
                    movifm[j]->mov_pac(&posi_xf[j], &posi_yf[j], &spr2[j], MapaMain,i[j].getdire());
                    
                    
                    i[j].desenha_inimigos(&posi_xf[j], &posi_yf[j], &spr2[j]);
                    i[j].colidiPac(posi_xf[j], posi_yf[j], posi_x, posi_y);
                }
               int spr3 = 3;
               iN.movi_inteligente(&posi_x, &posi_y, &posi_xf[4], &posi_yf[4], MapaMain);
               movifm[4]->mov_pac(&posi_xf[4], &posi_yf[4],&spr3, MapaMain, iN.getdire());
               iN.desenha_inimigoInt(&posi_xf[4], &posi_yf[4], &spr3);
                /*i[0].movi_random(&posi_xf[0], &posi_yf[0], &spr2[0], MapaMain);
                i[0].desenha_inimigos(&posi_xf[0], &posi_yf[0], &spr2[0]);
                i[0].colidiPac(posi_xf[0], posi_yf[0], posi_x, posi_y);*/

                /*i[1].movi_random(&posi_xf[1], &posi_yf[1], &spr2[1], MapaMain);
                i[1].desenha_inimigos(&posi_xf[1], &posi_yf[1], &spr2[1]);
                i[1].colidiPac(posi_xf[1], posi_yf[1], posi_x, posi_y);*/

                /*i[2].movi_random(&posi_xf[2], &posi_yf[2], &spr2[2], MapaMain);
                i[2].desenha_inimigos(&posi_xf[2], &posi_yf[2], &spr2[2]);
                i[2].colidiPac(posi_xf[2], posi_yf[2], posi_x, posi_y);
                */
                /*i[3].movi_random(&posi_xf[3], &posi_yf[3], &spr2[3], MapaMain);
                i[3].desenha_inimigos(&posi_xf[3], &posi_yf[3], &spr2[3]);
                i[3].colidiPac(posi_xf[3], posi_yf[3], posi_x, posi_y);*/
                
                
                ///redesenha
//              cout << "Pos x = " << posi_x << endl;
//              cout << "Pos y = " << posi_y << endl;

        //      menu_pontos(texto);
                movi.pontuacao_victory((posi_x - 32) / 32, (posi_y - 32) / 32, MapaMain);
                
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
    al_destroy_font(texto);
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

