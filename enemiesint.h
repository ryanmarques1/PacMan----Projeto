#ifndef ENEMIESINT_H_INCLUDED
#define ENIMIESINT_H_INCLUDED

#include <iostream>
#include "moviment.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>


class inimigos_int : public moviment_pac {
	public:
		inimigos_int();
		~inimigos_int();

		void desenha_inimigoInt(int*, int*, int*);
		void movi_inteligente(int*,int*,int*,int*, char**);
		double distancia(int, int, int, int);
		virtual void mov_pac(int*, int*, int*, char**, int);
		int getdire();

		//void colidiPac_int();
	private:
		ALLEGRO_BITMAP* inim_int;
		int dire, sentido,auxsen;
		double xm, ym;
};
#endif