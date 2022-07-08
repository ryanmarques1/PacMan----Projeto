#ifndef PACMAN_H_INCLUDED
#define PACMAN_H_INCLUDED
#include <allegro5/allegro.h>
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
///Grupo : Ryan Marques de Castro, Mariana de Deus Castro e Bernardo Teixeira de Miranda INTEGRAL.
class tijolos{
    public:
        tijolos();
        //tijolos(ALLEGRO_BITMAP*);
        //~tijolos();
        ///Metodos;
        //void set_tijo();
       void desenha_tijo(ALLEGRO_BITMAP *);
    private:
        ALLEGRO_BITMAP *til;

};

class pilulas{
    public:
        pilulas();
        //pilulas(ALLEGRO_BITMAP*);
        //~pilulas();
        ///Metodos;
        //void set_pil();
        void desenha_pilu(ALLEGRO_BITMAP *);
    private:
        ALLEGRO_BITMAP *pilu;

};
#endif // PACMAN_H_INCLUDED
