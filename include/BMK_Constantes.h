#ifndef BMK_CONSTANTES_H
#define BMK_CONSTANTES_H


#define MAX_X 15
#define MAX_Y 23


#define PATH_PARED "sprites/pared_metal.bmp"
#define PATH_PISO "sprites/piso.bmp"
#define PATH_BLOQUE "sprites/bloque.bmp"
#define PATH_AGUA "sprites/agua.bmp"
#define PATH_MATA "sprites/mata.bmp"

#define PATH_IMG_SPRITE_0 "sprites/tank-arriba.bmp"
#define PATH_IMG_SPRITE_1 "sprites/tank-abajo.bmp"
#define PATH_IMG_SPRITE_2 "sprites/tank-de.bmp"
#define PATH_IMG_SPRITE_3 "sprites/tank-iz.bmp"


#define PATH_OBJ_BALA "sprites/bala.bmp"


//Objetos
#define VACIO 0
#define PISO 0
#define PARED 1
#define BLOQUE 2
#define MATA 3
#define AGUA 4


#define MAX_PIXEL 32


#define MAPA_JUEGO 50
#define MAPA_INVENTARIO 51
#define MAPA_PUNTAJE 52

#define ARRIBA 0
#define ABAJO 1
#define DERECHA 2
#define IZQUIERDA 3


#define PASOS 32

//Color de fondo del sprites jugador
#define COLOR_FONDO_JUGADOR 255,0,255

//Definimos las caracteristicas de la ventana
#define ANCHO 800
#define ALTO 600
#define COLORES 32


//Maximos de objetos en el campo
#define MAX_OBJETOS 5


//Constantes del sistema de audio
#define FRECUENCIA 44100
#define NUM_CANALES 2
#define CHUCKSIZE 1024


//maximo de disparos
#define MAX_DISPAROS 100



//Path sonidos
#define PATH_AUDIO_FONDO "/home/danzt/TANKERS/musica/fondo.wav"

//Numero maximo de sprites del jugador
#define MAX_SPRITE_JUGADOR 4


//Estructura de coodenadas
class coordenada{
    public:
        int x,y;
};

typedef struct cor_bala {
    int x,y,direccion;
    bool activa;
}tipo_bala;

#endif
