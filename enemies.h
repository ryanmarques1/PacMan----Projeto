#ifndef ENEMIES_H_INCLUDED
#define ENEMIES_H_INCLUDED

#include <bits/stdc++.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

class inimigos{
    public:
        inimigos();
        inimigos(ALLEGRO_BITMAP*);
        ~inimigos();

        void desenha_inimigos(ALLEGRO_BITMAP*);
        ALLEGRO_BITMAP* retorna_inimigos();
    private:
        ALLEGRO_BITMAP* inim;
};
#endif // ENEMIES_H_INCLUDED
