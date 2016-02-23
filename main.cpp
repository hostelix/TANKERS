#include "include/BMK_Juego.h"


int main ( int argc, char** argv )
{

    BMK_Juego *tankers = new BMK_Juego;

    atexit(SDL_Quit);

    tankers->cargar_imagenes();
    tankers->cargar_pantalla();
    tankers->cargar_sonidos();
    tankers->cargar_musicas();

    tankers->cargar_mapas();

    tankers->cargar_objetos();
    tankers->cargar_sprites();

    tankers->iniciar_juego();
    SDL_Delay(SDL_GetTicks()*10);
}
