#include "enemies.h"
#include "pacman.h"
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
using namespace std;

///Cont�m heran�a public -> moviment base
///Construtores e Destrutores

inimigos::inimigos() {
	this->inim = NULL;
    this->dire = 0;
    this->sentido = 0;
	this->xm = this->ym = 0;

}

inimigos::~inimigos() {
	al_destroy_bitmap(this->inim);
}

void inimigos::desenha_inimigos(int* x, int *y, int* spr) {
	inim = al_load_bitmap("Sprites/Personagens/Psyduck/Psy1.png");
	if (!inim) {
		exit(-1);
		cout << "Erro ao carregar\n";
	}
    al_draw_bitmap_region(inim, 0, *spr * 32, 32, 32, *x, *y, 0);
}
/// -----------------------------------------------------------------------------------------------------------------------------------------------
void inimigos::MTop(int* x, int* y, char** m) {
    this->xm = ((double)(*x) / (double)32);
    this->ym = ((double)(*y) / (double)32);
    this->xm--;
    this->ym--;
    if ((this->ym - 1) > 0 && moviment_pac::obstaculos(this->xm, this->ym - 1, m)) {
       
        this->dire = 0;
    }
}
void inimigos::MDown(int* x, int* y, char** m) {
    this->xm = ((double)(*x) / (double)32);
    this->ym = ((double)(*y) / (double)32);
    this->xm--;
    this->ym--;
    if ((this->ym + 1) < 18 && moviment_pac::obstaculos(this->xm, this->ym + 1, m)) {
        
        this->dire = 1;
    }
}
void inimigos::MDir(int* x, int* y, char** m) {
    this->xm = ((double)(*x) / (double)32);
    this->ym = ((double)(*y) / (double)32);
    this->xm--;
    this->ym--;
    if ((this->xm + 1) < 18 && moviment_pac::obstaculos(this->xm + 1, this->ym, m)) {
        this->dire = 2;
        
    }
}
void inimigos::MEsq(int* x, int* y, char** m) {
    this->xm = ((double)(*x) / (double)32);
    this->ym = ((double)(*y) / (double)32);
    this->xm--;
    this->ym--;
    if ((this->xm - 1) > 0 && moviment_pac::obstaculos(this->xm - 1, this->ym, m)) {
        this->dire = 3;
        
    }
}
/// ----------------------------------------------------------------------------------------------------------------------------------------------
void inimigos::movi_random(int *x, int *y, int* spr2, char** m) {// X, Y == 32
	//srand(time(NULL)) para que as sementeste geradas nunca sejam iguais;
	///j� que a mesma � gerada desde da primeira compila��o do C -> 01/01/1970
	///tera heran�a com as colis�es.

    srand(time(NULL));

    this->xm = ((double)(*x) / (double)32);
    this->ym = ((double)(*y) / (double)32);
    this->xm--;
    this->ym--;



    if (moviment_pac::atualizaval(*x) && dire == 0) {// Eixo x Coluna / Eixo y linha        
        int aux = *y / 32;
        double aux2 = (double)*y / 32;
        if ((!moviment_pac::obstaculos(xm, ceil(ym) - 1, m) || (ceil(ym) - 1) < 0)) {
            while (true){
                if ((rand() % 6) % 2 == 0) { ///Direita
                    MDir(x, y, m);
                    break;
                }
                else
                if ((rand() % 6) % 2 == 1) { ///Esquerda
                    MEsq(x, y, m);
                    break;
                }
            }
        }else
        if(moviment_pac::obstaculos(xm-1, ym, m) || moviment_pac::obstaculos(xm + 1, ym, m)){
           
            int random1 = rand() % 6;
            if (random1 <= 2) {
                MTop(x, y, m);
            }
            else{
                while (true) {
                    
                    if (aux == aux2) {
                        while (true) {
                            int random2 = rand() % 2;
                            if (moviment_pac::obstaculos(xm - 1, ym, m) || moviment_pac::obstaculos(xm + 1, ym, m)) {
                                if (xm > 0) {
                                   
                                    if (random2 == 0) {
                                        cout << "Esq" << endl;
                                        MEsq(x, y, m);
                                        break;
                                    }
                                }
                                else
                                if (xm < 608) {
                                    
                                    if (random2 == 1) {
                                        cout << "Dir" << endl;
                                        MDir(x, y, m);
                                        break;
                                    }
                                }
                            }else{
                                break;
                            }
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }else
    
    if (moviment_pac::atualizaval(*y) && dire == 2) {// Eixo x Coluna / Eixo y linha
    
        int aux3 = *x / 32;
        double aux4 = (double)*x / 32;
        if (!moviment_pac::obstaculos(xm + 1, ym, m) || (xm + 1) > 18) {
            while(true) {
                if ((rand() % 6) % 2 == 0) {///Cima
                    MTop(x, y, m); 
                    break;
                }else
                if ((rand() % 6) % 2 == 1) {///Baixo
                    MDown(x, y, m);
                    break;
                }
            }
        }else
        if(moviment_pac::obstaculos(xm, ym-1, m) || moviment_pac::obstaculos(xm, ym+1, m)){
            int random1 = rand() % 6;
            if (random1 <= 2) {
                MDir(x, y, m);
                
            }
            else {
                while (true) {
                    if (aux3 == aux4) {
                        while (true) {
                            int random2 = rand() % 2;
                            if (moviment_pac::obstaculos(xm, ym - 1, m) || moviment_pac::obstaculos(xm, ym + 1, m)) {
                                if (xm > 0) {
                                    
                                    if (random2 == 0) {
                                        MTop(x, y, m);
                                        
                                        break;
                                    }
                                }
                                else
                                if (xm < 608) {
                                   
                                    if (random2 == 1) {
                                        MDown(x, y, m);
                                        
                                        break;
                                    }
                                }
                            }else{
                                break;
                            }
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }else   

    if (moviment_pac::atualizaval(*x) && dire == 1) {// Eixo x Coluna / Eixo y linha
        //MDown(x, y, m);///Baixo
        int aux = *y / 32;
        double aux2 = (double)*y / 32;
        if (!moviment_pac::obstaculos(xm, ym + 1, m) || (ym + 1) > 18) {
            while (true) {
                if ((rand() % 6) % 2 == 1){///Direita
                    MDir(x, y, m);
                    break;
                }
                else
                if ((rand() % 6) % 2 == 0){///Esquerda
                    MEsq(x, y, m);
                    break;
                }
            }
        }else
        if(moviment_pac::obstaculos(xm-1, ym, m) || moviment_pac::obstaculos(xm + 1, ym, m)){
            int random1 = rand() % 6;
            if (random1 <= 2) {
                MDown(x, y, m);
            }
            else{
                while (true) {
                    if (aux == aux2) {
                        while (true) {
                            int random2 = rand() % 2;
                            if (moviment_pac::obstaculos(xm - 1, ym, m) || moviment_pac::obstaculos(xm + 1, ym, m)) {
                                if (xm > 0) {
                                   
                                    if (random2 == 1) {
                                        
                                        MEsq(x, y, m);
                                        break;
                                    }
                                }
                                else
                                if (xm < 608) {
                                    
                                    if (random2 == 0) {
                                       
                                        MDir(x, y, m);
                                        break;
                                    }
                                }
                            }else{
                                break;
                            }
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }else    

    if (moviment_pac::atualizaval(*y) && dire == 3) {// Eixo x Coluna / Eixo y linha
        
        int a = ceil((double)(*x) / (double)32);
        int b = ceil((double)(*y) / (double)32);
        a--;
        b--;
        int aux3 = *x / 32;
        double aux4 = (double)*x / 32;
        if ((!moviment_pac::obstaculos(a - 1, b, m) || (a - 1) < 0)) {
            while (true) {
                if ((rand() % 6)%2 == 1) {///Cima
                    MTop(x, y, m);
                    break;
                }
                else 
                if ((rand() % 6) % 2 == 0) {///Baixo
                    
                    MDown(x, y, m);
                    break;
                }
            }
        }else
        if(moviment_pac::obstaculos(xm, ym-1, m) || moviment_pac::obstaculos(xm, ym+1, m)){
            int random1 = rand() % 6;
            if (random1 <= 2) {
                MEsq(x, y, m);
            }
            else {
                while (true) {
                    if (aux3 == aux4) {
                        while (true) {
                            int random2 = rand() % 2;
                            if (moviment_pac::obstaculos(xm, ym - 1, m) || moviment_pac::obstaculos(xm, ym + 1, m)) {
                                if (xm > 0) {
                                    if (random2 == 1) {
                                        MTop(x, y, m);
                                        break;
                                    }
                                }
                                else
                                if (xm < 608) {
                                    if (random2 == 0) {
                                        MDown(x, y, m);
                                        break;
                                    }
                                }
                            }else{
                                break;
                            }
                        }
                        break;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
    //cout << "Intencao: " << sentido << endl;
}
void inimigos::mov_pac(int* x, int* y, int* spr2, char** m, int dir) {

    moviment_pac::mov_pac(x, y, spr2, m, dire);

}
int inimigos::getdire() {

    return this->dire;
}
bool inimigos::colidiPac(int x, int y, int x2,int y2, int ant_pacx, int ant_pacy) {
	///colis�o com o pac = GAME OVER
    if (x == x2 && y == y2 || ant_pacx == x2 && ant_pacy == y2) {
        return true;
    }
    return false;
}

/// -----------------------------------------------------------------------------------------------------------------------------------------------
