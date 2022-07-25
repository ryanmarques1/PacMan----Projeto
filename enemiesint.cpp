#include "enemiesint.h"
#include "moviment.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
using namespace std;


inimigos_int::inimigos_int() {

	this->inim_int = NULL;
	this->xm = this->ym = 0;
	this->dire = this->sentido = this->auxsen = 0;
}

inimigos_int::~inimigos_int() {
	al_destroy_bitmap(this->inim_int);
}

void inimigos_int::desenha_inimigoInt(int* x, int* y, int* spr2) {
	inim_int = al_load_bitmap("Sprites/Personagens/Psyduck/Psy3.png");
	if (!inim_int) {
		exit(-1);
		cout << "\nErro ao carregar a imagem\n";
	}
	al_draw_bitmap_region(inim_int, 0, *spr2 * 32, 32, 32, *x, *y, 0);
}

double inimigos_int::distancia(int x, int y, int fx, int fy) {
	return abs(sqrt(pow(fx - x, 2) + pow(fy - y, 2)));
}

/// -----------------------------------------------------------------------------
void inimigos_int::movi_inteligente(int* x, int* y, int* fx, int* fy, char** m) {
	srand(time(NULL));
    int a , b ;
	a = ((double)(*fx) / (double)32);
	b = ((double)(*fy) / (double)32);
	a--;
	b--;
    if (*fx < *x && dire != 3 && moviment_pac::obstaculos(a+1, b, m) && moviment_pac::atualizaval(*fy))dire = 2;
    else 
	a = ((double)(*fx) / (double)32);
	b = ((double)(*fy) / (double)32);
	a--;
	b--;
	if (*fx > *x && dire != 2 && moviment_pac::obstaculos(a-1 ,b, m) && moviment_pac::atualizaval(*fy)) dire = 3;
    else 
	a = ((double)(*fx) / (double)32);
	b = ((double)(*fy) / (double)32);
	a--;
	b--;
	if (*fy < *y && dire != 0 && moviment_pac::obstaculos(a, b + 1, m) && moviment_pac::atualizaval(*fx)) dire = 1;
    else 
	a = ((double)(*fx) / (double)32);
	b = ceil((double)(*fy) / (double)32);
	a--;
	b--;
	if (*fy > *y && dire != 1 && moviment_pac::obstaculos(a, b - 1, m) && moviment_pac::atualizaval(*fx)) dire = 0;

	/// Estou a Enlouquecer ja

	a = ceil((double)(*fx) / (double)32);
	b = ceil((double)(*fy) / (double)32);
	a--;
	b--;
	if (moviment_pac::atualizaval(*x) && !moviment_pac::obstaculos(a, b - 1, m) && b - 1 > 0 && dire == 0) {
		int aux = *fy / 32;
		double aux2 = (double)*fy / 32;
		if (moviment_pac::obstaculos(a - 1, b, m) && moviment_pac::obstaculos(a + 1, b, m) && aux == aux2) {			
			if (*fx > *x) {
				dire = 3;
			}
			else {
				dire = 2;
			}
		}else{
			(moviment_pac::obstaculos(a - 1, b, m)) ? (dire = 3) : (dire = 2);
		}
	}

	a = ((double)(*fx) / (double)32);
	b = ((double)(*fy) / (double)32);
	a--;
	b--;
	if (moviment_pac::atualizaval(*fx) && !moviment_pac::obstaculos(a, b + 1, m) && b + 1 < 18 && dire == 1) {
		int aux = *fy / 32;
		double aux2 = (double)*fy / 32;
		if (moviment_pac::obstaculos(a - 1, b, m) && moviment_pac::obstaculos(a + 1, b, m) && aux == aux2) {
			if (*fx > *x) {
				dire = 3;
			}
			else {
				dire = 2;
			}
		}
		else {
			(moviment_pac::obstaculos(a - 1, b, m)) ? (dire = 3) : (dire = 2);
		}
	}

	a = ((double)(*fx) / (double)32);
	b = ((double)(*fy) / (double)32);
	a--;
	b--;
	if (moviment_pac::atualizaval(*fy) && !moviment_pac::obstaculos(a + 1, b, m) && a + 1 < 18 && dire == 2) {
		int aux3 = *x / 32;
		double aux4 = (double)*x / 32;
		if (moviment_pac::obstaculos(a, b-1, m) && moviment_pac::obstaculos(a , b + 1, m) && aux3 == aux4) {
			if (*fy < *y) {
				dire = 1;
			}
			else {
				dire = 0;
			}
		}else{
			(moviment_pac::obstaculos(a, b-1, m)) ? (dire = 0) : (dire = 1);
		}
	}

	a = ceil((double)(*fx) / (double)32);
	b = ceil((double)(*fy) / (double)32);
	a--;
	b--;
	if (moviment_pac::atualizaval(*fy) && !moviment_pac::obstaculos(a - 1, b, m) && a-1 > 0 && dire == 3) {
		int aux3 = *x / 32;
		double aux4 = (double)*x / 32;
		if (moviment_pac::obstaculos(a, b - 1, m) && moviment_pac::obstaculos(a, b + 1, m) && aux3 == aux4 ) {
			if (*fy < *y) {
				dire = 1;
			}
			else {
				dire = 0;
			}
		}
		else {
			(moviment_pac::obstaculos(a, b - 1, m)) ? (dire = 0) : (dire = 1);
		}
	}
	
}
void inimigos_int::mov_pac(int* fx, int* fy, int* spr2, char** m, int dir) {
	moviment_pac::mov_pac(fx, fy, spr2, m, dire);
}
int inimigos_int::getdire() {
	return dire;
}
void inimigos_int::colidiPac(int x, int y, int x2, int y2, int ant_pacx, int ant_pacy, ALLEGRO_FONT* t) {
	///colisão com o pac = GAME OVER
	if (!t) {
		printf("Erro em carregar a fonte !\n");
		exit(-1);
	}
	if (x == x2 && y == y2 || ant_pacx == x2 && ant_pacy == y2) {
		al_draw_textf(t, al_map_rgb(255, 0, 0), 900 - 135, 672 - 600, ALLEGRO_ALIGN_CENTER, "GAME OVER RUIM");

	}
}


