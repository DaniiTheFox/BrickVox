/*
=========================================================
= INCLUDE THE REQUIRED LIBRARIES FOR THE AUDIO MANAGER =
=========================================================
*/
#include <memory>
//#include "SDL/SDL_mixer.h"
/*
=========================================================
= CREATE THE REQUIRED VARIABLES FOR THE MANAGER TO WORK =
=========================================================
*/
SDL_Window *window;
SDL_Renderer *render;
/*
================================================================
= AUDIO MANAGER CLASS THAT WILL PLAY THE SOUNDS WITH THE MIXER = 
================================================================
*/
class Audio_manager{
 private:
  Mix_Chunk *msic;
 public:
  Audio_manager(std::string pth, int vol);
  void splay();
  void play(int times);
  void set_volume(int vol);
};

Audio_manager::Audio_manager(std::string pth, int vol) {
    const char *path = pth.c_str();
    msic = Mix_LoadWAV(path);
    if (!msic) {
        //std::cout<<"ERROR LOADING THE AUDIO FILE PLEASE CHECK IF THE PROGRAM IS COMPLETE "<<Mix_GetError()<<std::endl;
    }

    Mix_VolumeChunk(msic, vol);
}

void Audio_manager::splay() {
    Mix_PlayChannel(-1, msic, 0);
}

void Audio_manager::play(int times) {
    Mix_PlayChannel(-1, msic, times - 1);
}

void Audio_manager::set_volume(int vol) {
    Mix_VolumeChunk(msic, vol);
}
