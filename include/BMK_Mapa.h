#ifndef BMK_MAPA_H
#define BMK_MAPA_H

#include "BMK_Sprites.h"
#include <SDL/SDL.h>
#include "BMK_Constantes.h"

class BMK_Mapa {

    public:
        int mapa[MAX_X][MAX_Y];
        //int mapa_inventario[MAX_IN_X][MAX_IN_Y];
        //int mapa_puntaje[MAX_MAP_PUNTAJE_X][MAX_MAP_PUNTAJE_Y];

        BMK_Mapa();
        ~BMK_Mapa();
        void iniciar_mapa();
        void crear_mapa();
        void crear_mapa_puntaje();
        void crear_mapa_inventario();
        void dibujar_mapa(BMK_Sprites *materiales,SDL_Surface *pantalla);
        void dibujar_mapa_inventario(BMK_Sprites *materiales,SDL_Surface *pantalla);
        void dibujar_mapa_puntaje(BMK_Sprites *materiales,SDL_Surface *pantalla);
        void set_objeto_mapa(int x , int y, int objeto, int num_objeto);
        int get_objeto_mapa(int x, int y);
        void set_pantalla(SDL_Surface *pantalla);

};


BMK_Mapa::BMK_Mapa(){
    this->iniciar_mapa();
}

BMK_Mapa::~BMK_Mapa(){

}

void BMK_Mapa::iniciar_mapa(){
    for(int i=0; i<MAX_X; i++){
        for(int j=0; j<MAX_Y; j++){
            this->mapa[i][j] = 0;
        }
    }

//    for(int i=0; i<MAX_IN_X; i++){
//        for(int j=0; j<MAX_IN_Y; j++){
//            this->mapa_inventario[i][j] = 0;
//        }
//    }
//
//    for(int i=0; i<MAX_MAP_PUNTAJE_X; i++){
//        for(int j=0; j<MAX_MAP_PUNTAJE_Y; j++){
//            this->mapa_puntaje[i][j] = 0;
//        }
//    }
}

void BMK_Mapa::crear_mapa(){

    for(int i=0 ; i<MAX_X ; i++) {
        for (int j=0 ; j<MAX_Y ; j++) {
            //Creamos paredes
            if(i<MAX_Y && j==0) this->mapa[i][j] = PARED;
            else if(i==MAX_X-1 && j<MAX_Y) this->mapa[i][j] =PARED;
            else if(i==0 && j<MAX_Y) this->mapa[i][j] =PARED;
            else if(i<MAX_Y && j==MAX_Y-1) this->mapa[i][j] =PARED;
        }
    }

}

void BMK_Mapa::crear_mapa_inventario(){
//
//    for(int i=0 ; i<MAX_IN_X ; i++) {
//        for (int j=0 ; j<MAX_IN_Y ; j++) {
//            //Creamos paredes
//            if(i<MAX_IN_X && j==0) this->mapa_inventario[i][j] = PARED_INVENTARIO;
//            else if(i==MAX_IN_X-1 && j<MAX_Y) this->mapa_inventario[i][j] = PARED_INVENTARIO;
//            else if(i==0 && j<MAX_IN_Y) this->mapa_inventario[i][j] = PARED_INVENTARIO;
//            else if(i<MAX_IN_X && j==MAX_IN_Y-1) this->mapa_inventario[i][j] = PARED_INVENTARIO;
//            else if(i<=MAX_IN_Y) this->mapa_inventario[i][j] = VACIO_INVENTARIO;
//        }
//    }

}

void BMK_Mapa::crear_mapa_puntaje(){
//
//    for(int i=0 ; i<MAX_MAP_PUNTAJE_X ; i++) {
//        for (int j=0 ; j<MAX_MAP_PUNTAJE_Y ; j++) {
//            //Creamos paredes
//            if(i<MAX_MAP_PUNTAJE_X && j==0) this->mapa_puntaje[i][j] = PARED_INVENTARIO;
//            else if(i==MAX_MAP_PUNTAJE_X-1 && j<MAX_Y) this->mapa_puntaje[i][j] =PARED_INVENTARIO;
//            else if(i==0 && j<MAX_MAP_PUNTAJE_Y) this->mapa_puntaje[i][j] =PARED_INVENTARIO;
//            else if(i<MAX_MAP_PUNTAJE_X && j==MAX_MAP_PUNTAJE_Y-1) this->mapa_puntaje[i][j] =PARED_INVENTARIO;
//            else if(i==4) this->mapa_puntaje[i][j] = PARED_INVENTARIO;
//
//        }
//    }

}

void BMK_Mapa::dibujar_mapa(BMK_Sprites *materiales,SDL_Surface *pantalla){
    SDL_Rect r;
    for(int i=0 ; i<MAX_X ; i++){
        for(int j=0 ; j<MAX_Y ; j++){

            materiales->set_frame_actual(this->mapa[i][j]);

            //printf("[%d]",this->mapa[i][j]);
            r.x=(j+1)*MAX_PIXEL;
            r.y=(i+1)*MAX_PIXEL;
            r.h = materiales->get_alto();
            r.w = materiales->get_ancho();
            SDL_BlitSurface(materiales->get_sprite_actual(), NULL, pantalla, &r);
        }
        //printf("\n");
    }
}

void BMK_Mapa::dibujar_mapa_inventario(BMK_Sprites *materiales,SDL_Surface *pantalla){
//    SDL_Rect r;
//    for(int i=0 ; i<MAX_IN_X ; i++){
//        for(int j=0 ; j<MAX_IN_Y ; j++){
//            materiales->set_frame_actual(this->mapa_inventario[i][j]);
//            //printf("[%d]",tmp);
//            r.x=(j+21)*MAX_PIXEL;
//            r.y=(i+7)*MAX_PIXEL;
//            r.h = materiales->get_alto();
//            r.w = materiales->get_ancho();
//
//            SDL_BlitSurface(materiales->get_sprite_actual(), NULL, pantalla, &r);
//        }
//        //printf("\n");
//    }
}

void BMK_Mapa::dibujar_mapa_puntaje(BMK_Sprites *materiales,SDL_Surface *pantalla){
//    SDL_Rect r;
//    for(int i=0 ; i<MAX_MAP_PUNTAJE_X; i++){
//        for(int j=0 ; j<MAX_MAP_PUNTAJE_Y ; j++){
//
//            materiales->set_frame_actual(this->mapa_puntaje[i][j]);
//            //printf("[%d]",tmp);
//
//            r.x=(j+21)*MAX_PIXEL;
//            r.y=(i+1)*MAX_PIXEL;
//            r.h = materiales->get_alto();
//            r.w = materiales->get_ancho();
//
//            SDL_BlitSurface(materiales->get_sprite_actual(), NULL, pantalla, &r);
//        }
//        //printf("\n");
//    }
}
void BMK_Mapa::set_objeto_mapa(int x, int y, int objeto,int num_mapa){

    switch(num_mapa){
        case MAPA_JUEGO:
            this->mapa[x][y] = objeto;
        break;
//        case MAPA_INVENTARIO:
//            this->mapa_inventario[x][y] = objeto;
//        break;
//        case MAPA_PUNTAJE:
//            this->mapa_puntaje[x][y] = objeto;
//        break;
    }

}

int BMK_Mapa::get_objeto_mapa(int x, int y){
    return this->mapa[x][y];
}
#endif // BMK_MAPA_H
