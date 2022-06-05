
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

    tij[0][0] = 0;
}
/*tijolos::~tijolos(){
    cout << "destrutor\n\n";

}*/


pilulas::pilulas(){
    cout << "\nconstrutor padrao\n\n";

    pil[0][0] = 0;
}
/*pilulas::~pilulas(){
    cout << "\ndestrutor\n\n";
}*/

