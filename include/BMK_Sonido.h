#ifndef BMK_Sonido_H
#define BMK_Sonido_H


#include <SDL/SDL_mixer.h>

class BMK_Sonido {
        Mix_Chunk *audio;
        Mix_Music *musica;
        int canal;
        int volumen;
        bool activo,pausado;

    public:
        BMK_Sonido();
        BMK_Sonido(int canal);
        //Sonidos
        void cargar_audio(const char* path);
        bool reproducir_audio(int num_repeticiones);
        bool reproducir_audio(int num_repeticiones, int ms);
        void pausar_audio();
        void resumir_audio();
        void parar_audio();
        void liberar_audio();
        void set_volumen_audio(int volumen);

        //Musica
        void cargar_musica(const char* path);
        void set_volumen_musica(int volumen);
        void liberar_musica();
        bool reproducir_musica(int num_repeticiones);
        bool reproducir_musica(int num_repeticiones, int ms);
        void pausar_musica();
        void reanudar_musica();
        int parar_musica();

};

BMK_Sonido::BMK_Sonido(int canal){
    this->canal = canal;
    this->activo = false;
    this->pausado = false;
}

BMK_Sonido::BMK_Sonido(){
    this->activo = false;
    this->pausado = false;
}

void BMK_Sonido::cargar_audio(const char *path){
    this->audio = Mix_LoadWAV(path);
    if(this->audio == NULL){
        printf("Hubo un error al cargar el audio, %s", SDL_GetError());
        exit(1);
    }
}

void BMK_Sonido::set_volumen_audio(int volumen){
    this->volumen = volumen;
    Mix_VolumeChunk(this->audio,this->volumen);
}


void BMK_Sonido::liberar_audio(){
    Mix_FreeChunk(this->audio);
}

bool BMK_Sonido::reproducir_audio(int num_repeticiones){
    if(Mix_PlayChannel(this->canal,this->audio,num_repeticiones) == -1){
        printf("Error al reproducir el sonido %s \n",Mix_GetError());
        return false;
    }
    this->activo = true;
    return true;
}

bool BMK_Sonido::reproducir_audio(int num_repeticiones, int ms){
    if(Mix_PlayChannelTimed(this->canal,this->audio,num_repeticiones,ms) == -1){
        printf("Error al reproducir el sonido %s\n",Mix_GetError());
        return false;
    }
    this->activo = true;
    return true;
}

void BMK_Sonido::pausar_audio(){
    if(!this->pausado && this->activo){
        Mix_Pause(this->canal);
        this->pausado = true;
    }
    else{
        printf("El audio ya esta pausado\n");
    }
}

void BMK_Sonido::resumir_audio(){
    if(this->pausado && this->activo){
        Mix_Resume(this->canal);
        this->pausado = false;
    }
    else{
        printf("El audio no esta pausado\n");
    }
}

void BMK_Sonido::parar_audio(){
    Mix_HaltChannel(this->canal);
    this->activo = false;
}



//Musicas

void BMK_Sonido::cargar_musica(const char *path){
    this->musica = Mix_LoadMUS(path);
    if(this->musica == NULL){
        printf("Hubo un error al cargar el audio, %s", SDL_GetError());
        exit(1);
    }
}

bool BMK_Sonido::reproducir_musica(int num_repeticiones){
    if(Mix_PlayMusic(this->musica,num_repeticiones) == -1){
        printf("Error al reproducir la musica %s \n",Mix_GetError());
        return false;
    }
    this->activo = true;
    return true;
}

bool BMK_Sonido::reproducir_musica(int num_repeticiones,int ms){
    if(Mix_FadeInMusic(this->musica,num_repeticiones,ms) == -1){
        printf("Error al reproducir la musica %s \n",Mix_GetError());
        return false;
    }
    this->activo = true;
    return true;
}

void BMK_Sonido::liberar_musica(){
    Mix_FreeMusic(this->musica);
}

void BMK_Sonido::set_volumen_musica(int volumen){
    this->volumen = volumen;
    Mix_VolumeMusic(this->volumen);
}

void BMK_Sonido::pausar_musica(){
    Mix_PauseMusic();
}

void BMK_Sonido::reanudar_musica(){
    Mix_ResumeMusic();
}

int BMK_Sonido::parar_musica(){
    return Mix_HaltMusic();
}



#endif // BMK_AUDIO_H
