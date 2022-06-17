#ifndef TIJOLOS_H_INCLUDED
#define TIJOLOS_H_INCLUDED
#include <allegro5/allegro.h>
class tijolos{
    public:
        tijolos();
        //tijolos(ALLEGRO_BITMAP*);
        ~tijolos();
        ///Metodos;
        //void set_tijo();
       void desenha_tijo(ALLEGRO_BITMAP *);
    private:
        ALLEGRO_BITMAP *til;

};


#endif // TIJOLOS_H_INCLUDED
