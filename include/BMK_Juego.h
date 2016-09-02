#ifndef BMK_JUEGO_H
#define BMK_JUEGO_H

#include "BMK_Librerias.h"

class BMK_Juego: public BMK_ModuloSDL {
    private:
        SDL_Surface *pantalla_principal;
        SDL_Event evento;
        BMK_Mapa *mapa;
        BMK_Sprites *materiales;
        BMK_Jugador *jugador;
        BMK_Sonido *musica_fondo;
        bool juego_terminado;
        Uint8 *tecla;

    public:
        BMK_Juego();
        ~BMK_Juego();


        void cargar_imagenes();
        void cargar_sonidos();
        void cargar_musicas();

        void cargar_pantalla();
        void cargar_mapas();
        void cargar_sprites();

        void cargar_objetos();

        void eventos();
        void iniciar_juego();
        void finalizar_juego();

        void renderizar();

        void mover_abeja();

};

BMK_Juego::BMK_Juego(){

    this->materiales = new BMK_Sprites(MAX_OBJETOS);
    this->mapa = new BMK_Mapa;
    this->jugador = new BMK_Jugador(12,12);
    this->musica_fondo = new BMK_Sonido();
    this->juego_terminado = false;

    this->iniciar_sistema(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO);
    this->iniciar_sistema_audio();
    this->set_titulo_ventana("Tankers Ver.0.1 (BMKeros)",NULL);

}

BMK_Juego::~BMK_Juego(){
    this->materiales->liberar_recurso();
    this->detener_sistema();
    this->musica_fondo->liberar_musica();
    delete this->jugador;
}

void BMK_Juego::cargar_imagenes(){

    this->materiales->cargar_frame(PATH_PISO);//0
    this->materiales->cargar_frame(PATH_PARED);//1
    this->materiales->cargar_frame(PATH_BLOQUE);//2
    this->materiales->cargar_frame(PATH_MATA);//3
    this->materiales->cargar_frame(PATH_AGUA);//4


    ///Cargamos las imagenes del jugador
    jugador->cargar_sprite(PATH_IMG_SPRITE_0);
    jugador->cargar_sprite(PATH_IMG_SPRITE_1);
    jugador->cargar_sprite(PATH_IMG_SPRITE_2);
    jugador->cargar_sprite(PATH_IMG_SPRITE_3);

    this->jugador->set_imagen_bala(PATH_OBJ_BALA);

}

void BMK_Juego::cargar_sonidos(){
}

void BMK_Juego::cargar_musicas(){
    this->musica_fondo->cargar_musica(PATH_AUDIO_FONDO);
    this->musica_fondo->set_volumen_musica(30);
}
void BMK_Juego::cargar_pantalla(){
    this->pantalla_principal = this->iniciar_modo_grafico(ANCHO,ALTO,COLORES,SDL_HWSURFACE);
}

void BMK_Juego::cargar_mapas(){
    this->mapa->crear_mapa();
}

void BMK_Juego::cargar_objetos(){

}

void BMK_Juego::cargar_sprites(){
    this->mapa->dibujar_mapa(this->materiales,this->pantalla_principal);
    this->jugador->dibujar(this->pantalla_principal);

    for(int i=3;i<10;i++){
        this->mapa->set_objeto_mapa(i+1*2,i+1,BLOQUE,MAPA_JUEGO);
        this->mapa->set_objeto_mapa(6,i+1,AGUA,MAPA_JUEGO);
        this->mapa->set_objeto_mapa(6,i*i,AGUA,MAPA_JUEGO);
        this->mapa->set_objeto_mapa(i+1,9,BLOQUE,MAPA_JUEGO);
        this->mapa->set_objeto_mapa(i+3,i*3,BLOQUE,MAPA_JUEGO);

    }
    this->mapa->set_objeto_mapa(6,9,AGUA,MAPA_JUEGO);


}

void BMK_Juego::renderizar(){
    this->mapa->dibujar_mapa(this->materiales,this->pantalla_principal);
    this->jugador->dibujar(this->pantalla_principal);
    this->jugador->dibujar_balas(this->pantalla_principal);
    this->jugador->mover_balas(this->mapa);
    SDL_Flip(this->pantalla_principal);
    SDL_Delay(40); //retardo en la renderizacion
}



void BMK_Juego::iniciar_juego(){
    this->musica_fondo->reproducir_musica(-1);
    this->renderizar();



    while(!this->juego_terminado){

        if(this->jugador->get_estado() && (this->jugador->get_vidas() == 0) ){
            this->juego_terminado = true;
        }

        this->renderizar();


        this->tecla=SDL_GetKeyState(NULL);


        if( tecla[SDLK_UP] || tecla[SDLK_w]){
            this->jugador->mover_jugador(ARRIBA,this->mapa);

        }
        if(tecla[SDLK_DOWN]|| tecla[SDLK_s]){
            this->jugador->mover_jugador(ABAJO,this->mapa);

        }
        if(tecla[SDLK_LEFT] || tecla[SDLK_a]){
            this->jugador->mover_jugador(IZQUIERDA,this->mapa);

        }
        if(tecla[SDLK_RIGHT] || tecla[SDLK_d]){
            this->jugador->mover_jugador(DERECHA,this->mapa);

        }
        if(tecla[SDLK_SPACE]){
            this->jugador->disparar();
        }


        while(SDL_PollEvent(&this->evento)){
            if(this->evento.type == SDL_KEYDOWN){
                if(this->evento.key.keysym.sym == SDLK_ESCAPE){
                    this->juego_terminado = true;
                }
            }
            else if(this->evento.type == SDL_QUIT){
                this->juego_terminado = true;

            }
        }
    }
    this->finalizar_juego();
}

void BMK_Juego::finalizar_juego(){
    this->musica_fondo->parar_musica();
    exit(1);
}


#endif

