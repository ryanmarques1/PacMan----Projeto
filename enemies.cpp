#include "enemies.h"
#include "moviment.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
using namespace std;

///Contém herança public -> moviment base
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

void inimigos::movi_random(int *x, int *y, int* spr2, char** m) {// X, Y == 32
	//srand(time(NULL)) para que as sementeste geradas nunca sejam iguais;
	///já que a mesma é gerada desde da primeira compilação do C -> 01/01/1970
	///tera herança com as colisões.
    int ax, ay;
    ax = *x;
    ay = *y;
	srand(time(NULL));
    int r;
    r = rand() % 2;

    ///Cima
    if (moviment_pac::atualizaval(*x) && dire == 0 && (!moviment_pac::obstaculos(xm, ym - 1, m) || (ym - 1) < 0)) {// Eixo x Coluna / Eixo y linha
        xm = ceil((double)(*x) / (double)32);
        ym = ceil((double)(*y) / (double)32);
        xm--;
        ym--;
        if ((ym - 1) > 0 && moviment_pac::obstaculos(xm, ym - 1, m)) {
            cout << "------------------------------------------1Cima\n";
            dire = 0;
        }else //Dir
        this->xm = ((double)(*x) / (double)32);
        this->ym = ceil((double)(*y) / (double)32);
        this->xm--;
        this->ym--;
        if (r == 0 && (xm + 1) < 32 && moviment_pac::obstaculos(xm+1, ym, m)) {
            dire = 2;
            cout << "---------------------------------------Dir\n";
        }else //Esq
        this->xm = ceil((double)(*x) / (double)32);
        this->ym = ceil((double)(*y) / (double)32);
        this->xm--;
        this->ym--;
        if (r == 1 && (xm - 1) > 0 && moviment_pac::obstaculos(xm-1, ym , m)) {
            dire = 3;
            cout << "---------------------------------------Esq\n";
        }
    }

    ///Direita
    if (moviment_pac::atualizaval(*y) && dire == 2 && (!moviment_pac::obstaculos(xm+1, ym, m) || (xm + 1) > 32)) {// Eixo x Coluna / Eixo y linha
        this->xm = ((double)(*x) / (double)32);
        this->ym = ceil((double)(*y) / (double)32);
        this->xm--;
        this->ym--;
        cout << "Obst: " << moviment_pac::obstaculos(xm + 1, ym, m) << " xm+1: " << xm + 1 << " R: " << r << endl;
        if ((xm + 1) < 32 && moviment_pac::obstaculos(xm + 1, ym, m)) {
            dire = 2;
            cout << "----------------------------------------------1Dir\n";
        }
        else // Cima
        xm = ceil((double)(*x) / (double)32);
        ym = ceil((double)(*y) / (double)32);
        xm--;
        ym--;
        if (r == 0 && (ym - 1) > 0 && moviment_pac::obstaculos(xm, ym - 1, m)) {
            cout << "-----------------------------------------Cima\n";
            dire = 0;
        }else//Baixo
        this->xm = ceil((double)(*x) / (double)32);
        this->ym = ((double)(*y) / (double)32);
        this->xm--;
        this->ym--;
        if (r == 1 && (ym + 1) < 32 && moviment_pac::obstaculos(xm, ym+1 , m)) {
            cout << "-----------------------------------------Baixo\n";
            dire = 1;
        }
    }

    ///Baixo
    if (moviment_pac::atualizaval(*x) && dire == 1 && (!moviment_pac::obstaculos(xm, ym + 1, m) || (ym + 1) > 32)) {// Eixo x Coluna / Eixo y linha
        this->xm = ceil((double)(*x) / (double)32);
        this->ym = ((double)(*y) / (double)32);
        this->xm--;
        this->ym--;
        if ((ym + 1) < 32 && moviment_pac::obstaculos(xm, ym + 1, m)) {
            cout << "------------------------------------------1Baixo\n";
            dire = 0;
        }
        else
        this->xm = ((double)(*x) / (double)32);
        this->ym = ceil((double)(*y) / (double)32);
        this->xm--;
        this->ym--;
        //cout << "Obst: " << moviment_pac::obstaculos(xm+1, ym, m) << " xm+1: " << xm+1 << " R: " << r << endl;
        if (r == 1 && (xm + 1) < 32 && moviment_pac::obstaculos(xm + 1, ym, m)) {
            dire = 2;
            cout << "---------------------------------------Dir\n";
        }
        else
        this->xm = ceil((double)(*x) / (double)32);
        this->ym = ceil((double)(*y) / (double)32);
        this->xm--;
        this->ym--;
        if (r == 0 && (xm - 1) > 0 && moviment_pac::obstaculos(xm - 1, ym, m)) {
            dire = 3;
            cout << "---------------------------------------Esq\n";
        }
    }
    ///Esquerda
    if (moviment_pac::atualizaval(*y) && dire == 3 && (!moviment_pac::obstaculos(xm - 1, ym, m) || (xm - 1) < 0)) {// Eixo x Coluna / Eixo y linha
        this->xm = ceil((double)(*x) / (double)32);
        this->ym = ceil((double)(*y) / (double)32);
        this->xm--;
        this->ym--;
        if ((xm - 1) >= 0 && moviment_pac::obstaculos(xm - 1, ym, m)) {
            dire = 3;
            cout << "----------------------------------------------1Dir\n";
        }
        else // Cima
        xm = ceil((double)(*x) / (double)32);
        ym = ceil((double)(*y) / (double)32);
        xm--;
        ym--;
        if (r == 0 && (ym - 1) > 0 && moviment_pac::obstaculos(xm, ym - 1, m)) {
            cout << "-----------------------------------------Cima\n";
            dire = 0;
        }
        else//Baixo
        this->xm = ceil((double)(*x) / (double)32);
        this->ym = ((double)(*y) / (double)32);
        this->xm--;
        this->ym--;
        if (r == 1 && (ym + 1) < 32 && moviment_pac::obstaculos(xm, ym + 1, m)) {
            cout << "-----------------------------------------Baixo\n";
            dire = 1;
        }
    }
    
    
    xm = moviment_pac::getxm();
    ym = moviment_pac::getym();
    moviment_pac::mov_pac(x, y,spr2,m,dire);
    //cout << "Intencao: " << sentido << endl;
}
void inimigos::colidiPac(int x, int y, int x2,int y2) {
	///colisão com o pac = GAME OVER;
	if (x == x2 && y == y2 || x2 == x && y2 == y) {
		cout << "GAME OVER\n";
		exit(0);
		
	}
}
double distancia(int x, int y, int fx, int fy) {
    return abs(sqrt((x - fx) * (x - fx) + (y - fy) * (y - fy)));
}
void inimigos::movi_inteligente(int* x, int* y, int* fx, int* fy, char** m) {

    //Auxiliares
    int xx, yy, ffx, ffy;
    int aux = 10000;
    double d[4];
    d[0] = distancia(*x, *y, *fx, *fy-1); //Cima
    d[1] = distancia(*x, *y, *fx, *fy+1); //Baixo
    d[2] = distancia(*x, *y, *fx+1, *fy); // Direita
    d[3] = distancia(*x, *y, *fx-1, *fy); //Esquerda

    for (int i = 0; i < 4; i++){
        if (d[i] < aux) {
            if (*x != *fx || *y != *fy) {
                aux = d[i];
                dire = i;
            }
        }
    }
    //*fx = *x;
    //*fy = *y;

    if (dire == 0) {
        *fy -= 2.0;
    }
    else if (dire == 1) {
        *fy += 2.0;
    }
    else if (dire == 2) {
        *fx += 2.0;
    }
    else if (dire == 3) {
        *fx -= 2.0;
    }
    //Auxiliares
}