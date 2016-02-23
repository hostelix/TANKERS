#ifndef BMK_MODULOSDL_H
#define BMK_MODULOSDL_H

#include "BMK_Mensajes.h"
#include "BMK_Constantes.h"
#include <SDL/SDL_mixer.h>
//#include <SDL/SDL_ttf.h>

class BMK_ModuloSDL
{

    private:

    public:
        BMK_ModuloSDL();
        virtual ~BMK_ModuloSDL();
        bool iniciar_sistema(Uint32 sistema);
        bool iniciar_subSistema(Uint32 subsistema);
        SDL_Surface *iniciar_modo_grafico(int ancho, int alto, int num_colores,Uint32 modo);
        void set_titulo_ventana(const char *titulo, char *icono);
        void set_icono_ventana(SDL_Surface *icono, Uint8 *mascara);
        void detener_sistema();
        void detener_subSistema(Uint32 subsistema);
        bool iniciar_sistema_audio();
        void cerrar_sistema_audio();
        bool iniciar_modo_texto();

};


BMK_ModuloSDL::BMK_ModuloSDL()
{
    //ctor
}

BMK_ModuloSDL::~BMK_ModuloSDL()
{
    //dtor
}

bool BMK_ModuloSDL::iniciar_sistema(Uint32 sistema){
    if(SDL_Init(sistema) < 0){
        printf(ERROR_INICIAR_SISTEMA,SDL_GetError());
        exit(1);
        return false;
    }
    return true;
}

bool BMK_ModuloSDL::iniciar_subSistema(Uint32 subsistema){
    if(SDL_InitSubSystem(subsistema) < 0){
        printf(ERROR_INICIAR_SUBSISTEMA,SDL_GetError());
        exit(1);
        return false;
    }
    return true;
}

SDL_Surface *BMK_ModuloSDL::iniciar_modo_grafico(int ancho, int alto, int num_colores,Uint32 modo){
    SDL_Surface *tmp;
    tmp = SDL_SetVideoMode(ancho,alto,num_colores,modo);

    if(tmp){
        return tmp;
    }
    exit(1);
    return NULL;
}

void BMK_ModuloSDL::set_titulo_ventana(const char *titulo, char *icono){
    SDL_WM_SetCaption(titulo, icono);
}


void BMK_ModuloSDL::set_icono_ventana(SDL_Surface *icono, Uint8 *mascara){
    SDL_WM_SetIcon(icono, mascara);
}

void BMK_ModuloSDL::detener_sistema(){
    SDL_Quit();
}

void BMK_ModuloSDL::detener_subSistema(Uint32 subsistema){
    SDL_QuitSubSystem(subsistema);
}

bool BMK_ModuloSDL::iniciar_sistema_audio(){
    if(Mix_OpenAudio(FRECUENCIA,MIX_DEFAULT_FORMAT,NUM_CANALES,CHUCKSIZE) == -1){
        printf("Hubo un error al cargar el sistema de audio, %s",SDL_GetError());
        exit(1);
        return false;
    }
    return true;
}

void BMK_ModuloSDL::cerrar_sistema_audio(){
    Mix_CloseAudio();
}

//bool BMK_ModuloSDL::iniciar_modo_texto(){
//
//    if (TTF_Init() == 0) {
//        atexit(TTF_Quit);
//    }
//    else{
//        printf("Error al iniciar el sistema de texto \n");
//        exit(1);
//    }
//}



#endif // BMK_MODULOSDL_H
