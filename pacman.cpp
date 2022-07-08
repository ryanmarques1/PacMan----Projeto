#include "pacman.h"
#include <bits/stdc++.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
using namespace std;

///Chamando construtores e destrutores.
///Grupo : Ryan Marques de Castro, Mariana de Deus Castro e Bernardo Teixeira de Miranda INTEGRAL.


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

tijolos::tijolos(){
    cout << "construtor padrao\n";
    til = NULL;
}


pilulas::pilulas(){
    cout << "\nconstrutor padrao\n";
    pilu = NULL;

}

/*tijolos::~tijolos(){
    exit(0);
}
*/
/*pilulas::~pilulas(){
    al_destroy_bitmap(pilu);
}*/
void pilulas::desenha_pilu(char **aux){ ///196 Doces
    int i,j;
    float x=32,y=32;
    for(i = 0 ; i < 20; i++){
        for(j = 0; j < 20; j++){
            if(aux[i][j] == 'P'){
                pilu = al_load_bitmap("Sprites/Candy.png");
                 if(!pilu){
                    al_show_native_message_box(al_get_current_display(),"Erro!","Erro!","A imagem não pode ser carregada",NULL,ALLEGRO_MESSAGEBOX_ERROR);
                    exit(-1);
                }
                al_draw_bitmap(pilu,x,y,0);

            }
            x+=32;
        }
        x = 32;
        y+=32;
    }
}
void pilulas::destroi_pilu(){
    al_destroy_bitmap(this->pilu);
}
void tijolos::desenha_tijo(char **aux){
    int i, j;
    float x = 32, y = 32;
    for(i = 0; i < 20; i++){
        for(j = 0; j < 20; j++){
                switch(aux[i][j]){

                case 'A':
                    til = al_load_bitmap("Sprites/B1.png");
                    if(!til) exit(-1);
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'B':
                    til = al_load_bitmap("Sprites/B2.png");
                    if(!til) exit(-1);
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'C':
                    til = al_load_bitmap("Sprites/B3.png");
                    if(!til) exit(-1);
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'D':
                    til = al_load_bitmap("Sprites/B4.png");
                    if(!til) exit(-1);
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'E':
                    til = al_load_bitmap("Sprites/B5.png");
                    if(!til) exit(-1);
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'F':
                    til = al_load_bitmap("Sprites/B6.png");
                    if(!til) exit(-1);
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'G':
                    til = al_load_bitmap("Sprites/B7.png");
                    if(!til) exit(-1);
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'H':
                    til = al_load_bitmap("Sprites/B8.png");
                    if(!til) exit(-1);
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'I':
                    til = al_load_bitmap("Sprites/B9.png");
                    if(!til) exit(-1);
                    al_draw_bitmap(til,x,y,0);
                    break;
                case 'J':
                    til = al_load_bitmap("Sprites/B10.png");
                    if(!til) exit(-1);
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

void tijolos::destroi_tijo(){
    al_destroy_bitmap(this->til);
}
