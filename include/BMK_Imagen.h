#ifndef BMK_IMAGEN_H
#define BMK_IMAGEN_H

#include<SDL/SDL.h>

class BMK_Imagen{

    private:
        SDL_Surface *imagen;

    public:
        BMK_Imagen();
        void cargar(const char *path);
        void cargar(const char *path,int rojo,int verde, int azul);
        void borrar();
        SDL_Surface *get_imagen();
        void set_imagen(SDL_Surface *imagen);

};

BMK_Imagen::BMK_Imagen(){
    this->imagen = NULL;
}

void BMK_Imagen::cargar(const char *path){
    this->imagen = SDL_LoadBMP(path);
    if(this->imagen == NULL){
        printf("Hubo un erro al cargar la imagen %s\n",SDL_GetError());
    }
}

void BMK_Imagen::cargar(const char *path,int rojo,int verde, int azul){
    this->imagen = SDL_LoadBMP(path);
    if(this->imagen == NULL){
        printf("Hubo un erro al cargar la imagen %s\n",SDL_GetError());
    }
    else{
        SDL_SetColorKey(this->imagen,SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(this->imagen->format,rojo,verde,azul));
        this->imagen = SDL_DisplayFormat(this->imagen);
    }

}
void BMK_Imagen::set_imagen(SDL_Surface *imagen){
    this->imagen = imagen;
}

void BMK_Imagen::borrar(){
    SDL_FreeSurface(this->imagen);
}

SDL_Surface *BMK_Imagen::get_imagen(){
    return this->imagen;
}

#endif


