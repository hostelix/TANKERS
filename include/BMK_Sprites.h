#ifndef BMK_SPRITES_H
#define BMK_SPRITES_H

#include "BMK_Imagen.h"

class BMK_Sprites {
	private:
		int x, y;
		int actual;
		int num_frames;
		int indice;
		BMK_Imagen *sprites;

	public:

		BMK_Sprites();
		BMK_Sprites(int num_frames);
		void liberar_recurso();
		void agregar_frame(BMK_Imagen frame);
		void set_frame_actual(int nf);
		int get_num_frames();
		void set_x(int x);
		void set_y(int y);
		int get_x();
		int get_y();
		int get_ancho();
		int get_alto();
		void dibujar(SDL_Surface *pantalla);
		SDL_Surface *get_sprite_actual();
		void cargar_frame(const char* path);
		void cargar_frame(const char* path,int rojo, int verde, int azul);
		int get_posicion_frame_actual();

};

BMK_Sprites::BMK_Sprites(){
    this->sprites = new BMK_Imagen[2];
    this->num_frames = 2;
    this->indice= 0;
    this->actual=0;

}

BMK_Sprites::BMK_Sprites(int _num_frames){
    this->sprites = new BMK_Imagen[_num_frames];
    this->num_frames = _num_frames;
    this->indice= 0;
    this->actual=0;

}

void BMK_Sprites::liberar_recurso(){
	for(int i=0; i<num_frames-1; i++){
		sprites[i].borrar();
	}
}

void BMK_Sprites::agregar_frame(BMK_Imagen frame){
	if(indice < num_frames){
		sprites[indice] = frame;
		indice++;
	}
	else{
        printf("Ya no hay espacio para almacenar este frame");
	}
}
void BMK_Sprites::cargar_frame(const char* path){
    if(indice < num_frames){
		sprites[indice].cargar(path);
		indice++;
	}
	else{
        printf("Ya no hay espacio para almacenar este frame");
	}
}

void BMK_Sprites::cargar_frame(const char* path,int rojo, int verde, int azul){
    if(indice < num_frames){
		sprites[indice].cargar(path);
		SDL_SetColorKey(this->sprites[this->indice].get_imagen(), SDL_SRCCOLORKEY, SDL_MapRGB(this->sprites[this->indice].get_imagen()->format,rojo,verde,azul));
		indice++;

	}
	else{
        printf("Ya no hay espacio para almacenar este frame");
	}
}

void BMK_Sprites::set_frame_actual(int posi_frame){
	if(posi_frame<=num_frames){
		actual = posi_frame;
	}
}

int BMK_Sprites::get_num_frames(){
	return indice;
}

void BMK_Sprites::set_x(int x){
	this->x = x;
}

void BMK_Sprites::set_y(int y){
	this->y = y;
}

int BMK_Sprites::get_x(){
	return this->x;
}

int BMK_Sprites::get_y(){
	return this->y;
}

int BMK_Sprites::get_ancho(){
	return sprites[this->actual].get_imagen()->w;
}

int BMK_Sprites::get_alto(){
	return sprites[this->actual].get_imagen()->h;
}

void BMK_Sprites::dibujar(SDL_Surface *pantalla){
	SDL_Rect dest;

	dest.x = this->x;
	dest.y = this->y;
	SDL_BlitSurface(sprites[this->actual].get_imagen(), NULL, pantalla, &dest);
}

SDL_Surface *BMK_Sprites::get_sprite_actual(){
    return this->sprites[this->actual].get_imagen();
}

int BMK_Sprites::get_posicion_frame_actual(){
    return this->actual;
}


#endif
