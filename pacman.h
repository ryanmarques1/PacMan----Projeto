#ifndef PACMAN_H_INCLUDED
#define PACMAN_H_INCLUDED
#include <allegro5/allegro.h>

///Grupo : Ryan Marques de Castro, Mariana de Deus Castro e Bernardo Teixeira de Miranda INTEGRAL.
class tijolos{
    public:
        tijolos();
        ~tijolos();
        ///Metodos;
       void desenha_tijo(char**);
    private:
        ALLEGRO_BITMAP *til[10];

};

class pilulas{
    public:
        pilulas();
       ~pilulas();
        ///Metodos;
        void desenha_pilu(char**);
    private:
        ALLEGRO_BITMAP *pilu;
};
#endif // PACMAN_H_INCLUDED
