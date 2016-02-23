#ifndef BMK_JUGADOR_H
#define BMK_JUGADOR_H

#include "BMK_Librerias.h"

class BMK_Jugador {
    private:
        char *nombre;
        float puntaje;
        //BMK_Inventario *inventario;
        BMK_Sprites *cuerpo;
        coordenada posicion;
        SDL_Rect contenedor;
        int num_vidas;
        bool salio;

        //Atributos para saber cuando cambiar el sprite de direccion
        int sprite_actual;
        bool cambia_sprite;

        //Atributos para el disparo
        tipo_bala *disparos = (tipo_bala *)(malloc(sizeof(tipo_bala)*MAX_DISPAROS));
        BMK_Sprites *bala;
        int num_balas;


    public:
        BMK_Jugador(int x, int y);
        ~BMK_Jugador();
        void set_nombre(char *nombre);
        char *get_nombre();
        void set_puntaje(float puntaje);
        float get_puntaje();
        coordenada get_posicion();
        void set_posicion(coordenada posicion);
        //BMK_Inventario *get_inventario();
        void set_num_vidas(int num_vidas);
        int get_vidas();

        //Metodos manejo de sprites
        void cargar_sprite(const char *path);

        //Metodos dibujar
        void dibujar(SDL_Surface *pantalla);
        void cambiar_direccion_sprite(int direccion);

        //Metodos para el movimiento del jugador
        int colision(int x, int y, int w, int h);
        coordenada alterar_coordenada(int direccion);
        bool cambiar_posicion(coordenada destino, BMK_Mapa *mapa);
        bool mover_jugador(int direccion,BMK_Mapa *mapa);

        bool get_estado();

        //metodos para el disparo
        bool disparar();
        void mover_balas(BMK_Mapa *mapa);
        void dibujar_balas(SDL_Surface *pantalla);
        void set_imagen_bala(const char *path);

};


BMK_Jugador::BMK_Jugador(int x, int y){
    this->cuerpo = new BMK_Sprites(MAX_SPRITE_JUGADOR);
    //this->inventario = new BMK_Inventario;
    this->posicion.x = x;
    this->posicion.y = y;
    this->sprite_actual = 0;
    this->cambia_sprite = false;
    this->num_vidas = 4;
    this->salio = false;
    this->bala = new BMK_Sprites(1);
    for(int i=0 ; i<MAX_DISPAROS;i++){
        this->disparos[i].x = this->disparos[i].y = 0;
        this->disparos[i].activa = false;
        this->disparos[i].direccion = ARRIBA;
    }
}

BMK_Jugador::~BMK_Jugador(){
    delete this->nombre;
    //delete this->inventario;
    this->cuerpo->liberar_recurso();
    this->bala->liberar_recurso();
}

void BMK_Jugador::set_nombre(char *nombre){
    this->nombre = nombre;
}

char *BMK_Jugador::get_nombre(){
    return this->nombre;
}

void BMK_Jugador::set_puntaje(float puntaje){
    this->puntaje = puntaje;
}

float BMK_Jugador::get_puntaje(){
    return this->puntaje;
}

coordenada BMK_Jugador::get_posicion(){
    return this->posicion;
}

void BMK_Jugador::set_posicion(coordenada _posicion){
    this->posicion = _posicion;
}

//BMK_Inventario *BMK_Jugador::get_inventario(){
//    return this->inventario;
//}

//Manejo de los sprite cuerpo
void BMK_Jugador::cargar_sprite(const char *path){
    this->cuerpo->cargar_frame(path);
}

//Dibujar
void BMK_Jugador::dibujar(SDL_Surface *pantalla){

    this->contenedor.y = (this->posicion.x+1)*PASOS;
    this->contenedor.x = (this->posicion.y+1)*PASOS;
    this->contenedor.w = this->cuerpo->get_ancho();
    this->contenedor.h = this->cuerpo->get_alto();

    SDL_SetColorKey(this->cuerpo->get_sprite_actual(),SDL_SRCCOLORKEY,SDL_MapRGB(this->cuerpo->get_sprite_actual()->format,COLOR_FONDO_JUGADOR));

    SDL_BlitSurface(this->cuerpo->get_sprite_actual(),NULL,pantalla,&this->contenedor);

}

//Cambiamos la direccion del sprite
void BMK_Jugador::cambiar_direccion_sprite(int direccion){

    switch(direccion){
        case ARRIBA:
                this->cuerpo->set_frame_actual(ARRIBA);
        break;

        case ABAJO:
                this->cuerpo->set_frame_actual(ABAJO);
        break;

        case IZQUIERDA:
                this->cuerpo->set_frame_actual(IZQUIERDA);
        break;

        case DERECHA:
                this->cuerpo->set_frame_actual(DERECHA);
        break;
    }
}

//Movimientos
coordenada BMK_Jugador::alterar_coordenada(int direccion){
    coordenada temporal = this->posicion;

    switch(direccion){
        case ARRIBA:
            temporal.x--;
        break;

        case ABAJO:
            temporal.x++ ;
        break;

        case IZQUIERDA:
            temporal.y--;
        break;

        case DERECHA:
            temporal.y++;
        break;
    }
    return temporal;
}

//Cambia de posicion y dibuja el personaje
bool BMK_Jugador::cambiar_posicion(coordenada destino, BMK_Mapa *mapa){

    switch(mapa->mapa[destino.x][destino.y]){
        case VACIO:
            this->set_posicion(destino);
            return true;
        break;
    }

    return false;
}


bool BMK_Jugador::mover_jugador(int direccion,BMK_Mapa *mapa){
    bool retorno = false;
    switch(direccion){
        case ARRIBA:
            this->cambiar_direccion_sprite(ARRIBA);
            retorno = this->cambiar_posicion(this->alterar_coordenada(ARRIBA),mapa);
        break;
        case ABAJO:
            this->cambiar_direccion_sprite(ABAJO);
            retorno = this->cambiar_posicion(this->alterar_coordenada(ABAJO),mapa);
        break;
        case IZQUIERDA:
            this->cambiar_direccion_sprite(IZQUIERDA);
            retorno = this->cambiar_posicion(this->alterar_coordenada(IZQUIERDA),mapa);
        break;
        case DERECHA:
            this->cambiar_direccion_sprite(DERECHA);
            retorno = this->cambiar_posicion(this->alterar_coordenada(DERECHA),mapa);
        break;
    }
    return retorno;
}

void BMK_Jugador::set_num_vidas(int _num_vidas){
    if(_num_vidas <= 0){
        this->num_vidas = 0;
    }
    else{
        this->num_vidas = _num_vidas;
    }
}

int BMK_Jugador::get_vidas(){
    return this->num_vidas;
}

int BMK_Jugador::colision(int x, int y, int w, int h){
    SDL_Rect rec;
    rec.x = x;
    rec.y = y;
    rec.w = w;
    rec.h = h;

    if((this->contenedor.x + this->contenedor.w)> rec.x && (this->contenedor.y + this->contenedor.h) > rec.y && (rec.x + rec.w)>this->contenedor.x && (rec.y + rec.h) > this->contenedor.y){
        return true ;
    }
    else{
        return false ;
    }
}

bool BMK_Jugador::get_estado(){
    return this->salio;
}


//balas

void BMK_Jugador::set_imagen_bala(const char *path){
    this->bala->cargar_frame(path);
}

bool BMK_Jugador::disparar(){
    bool retorno =false;



    switch(this->cuerpo->get_posicion_frame_actual()){
        case ARRIBA:
            this->disparos[this->num_balas].x = this->posicion.y+1;
            this->disparos[this->num_balas].y = (this->posicion.x);
            this->disparos[this->num_balas].activa = true;
            this->disparos[this->num_balas].direccion = ARRIBA;
            retorno = true;
        break;

        case ABAJO:
            this->disparos[this->num_balas].x = this->posicion.y+1;
            this->disparos[this->num_balas].y = (this->posicion.x+2);
            this->disparos[this->num_balas].activa = true;
            this->disparos[this->num_balas].direccion = ABAJO;
            retorno = true;
        break;

        case IZQUIERDA:
            this->disparos[this->num_balas].x = this->posicion.y;
            this->disparos[this->num_balas].y = (this->posicion.x+1);
            this->disparos[this->num_balas].activa = true;
            this->disparos[this->num_balas].direccion = IZQUIERDA;
            retorno = true;
        break;

        case DERECHA:
            this->disparos[this->num_balas].x = this->posicion.y+2;
            this->disparos[this->num_balas].y = (this->posicion.x+1);
            this->disparos[this->num_balas].activa = true;
            this->disparos[this->num_balas].direccion = DERECHA;
            retorno = true;
        break;
    }
    this->num_balas++;
    /*if(this->num_balas < MAX_DISPAROS){
            if(!this->disparos[this->num_balas].activa){


                printf("numero de balas %d\n",this->num_balas);
            }
    }*/

    return retorno;

}

void BMK_Jugador::mover_balas(BMK_Mapa *mapa){
    for (int i=0 ; i<MAX_DISPAROS ; i++) {
        if(this->disparos[i].activa) {
            //printf("Moviendo bala %d,%d\n",this->disparos[i].x,this->disparos[i].y);

            switch(this->disparos[i].direccion){
                case ARRIBA:
                    this->disparos[i].y--;
                        SDL_Delay(30);
                        if (this->disparos[i].y < 1) {
                            this->disparos[i].activa = false;
                            this->disparos[i].x = this->disparos[i].y = 0;
                        }
                break;

                case ABAJO:
                    this->disparos[i].y++;
                        SDL_Delay(30);
                        if (this->disparos[i].y > MAX_X-1) {
                            this->disparos[i].activa = false;
                            this->disparos[i].x = this->disparos[i].y = 0;

                        }
                break;

                case IZQUIERDA:
                    this->disparos[i].x--;
                        SDL_Delay(30);
                        if (this->disparos[i].x < 2) {

                            this->disparos[i].activa = false;
                            this->disparos[i].x = this->disparos[i].y = 0;
                        }

                break;

                case DERECHA:
                    this->disparos[i].x++;
                        SDL_Delay(30);
                        if (this->disparos[i].x > MAX_Y-1) {
                            this->disparos[i].activa = false;
                            this->disparos[i].x = this->disparos[i].y = 0;
                        }
                break;
            }
        }
    }
}

void BMK_Jugador::dibujar_balas(SDL_Surface *pantalla){
    for (int i=0 ; i<MAX_DISPAROS ; i++) {
            if (this->disparos[i].activa) {
                this->bala->set_x(this->disparos[i].x * MAX_PIXEL);
                this->bala->set_y(this->disparos[i].y * MAX_PIXEL);
                this->bala->dibujar(pantalla);
            }
    }
}








#endif
