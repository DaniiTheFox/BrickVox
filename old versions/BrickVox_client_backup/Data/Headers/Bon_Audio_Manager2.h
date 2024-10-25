// CREATE THE SOUND FILES
//Audio_manager *audio_test = new Audio_manager("Music/Sounds/Beep2.wav",50);
/*
======================================================================
= MAIN THREAD THAT WILL PLAY THE MUSIC AND AUDIO THIS MUST RUN ASYNC =
======================================================================
*/
SDL_Window *mainwindow;                    // Declare a pointer
int Bon_AudioM_Init(){
 SDL_Init(SDL_INIT_VIDEO);
 
 if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG) < 0) {
  return -1;
 }

 if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
  //std::cout << "Can not initialize mixer!" << std::endl;
  return -1;
 }

 Audio_manager beep2_snd("Data/Music/Sounds/beep2.wav", 100/2);
 Audio_manager beep1_snd("Data/Music/Sounds/beep1.wav", 100 / 2);
 Audio_manager place_snd("Data/Music/Sounds/place.wav", 100 / 2);

 // Amount of channels (Max amount of sounds playing at the same time)
 Mix_AllocateChannels(32);

 //SDL_CreateWindowAndRenderer(2,2,SDL_WINDOW_BORDERLESS, &window, &render);
 mainwindow = SDL_CreateWindow("The Window Name", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              1, 1, SDL_WINDOW_BORDERLESS);
 //SDL_HideWindow(window);

 while(isRunning2==false){/*std::cout<<"waiting for program to start...."<<std::endl;*/usleep(150*1000);}
 //std::cout<<"\e[1;33m AUDIO SERVICE INSIDE PROGRAM HAS STARTED RUNNING.....\e[0m;"<<std::endl;
 while(1){
  if(snd_beep1 == true){
    beep1_snd.splay();
  }
  if(snd_beep2 == true){
    beep2_snd.splay();
  }
  if(snd_place == true){
    place_snd.splay();
  }
  snd_beep1 = false;
  snd_beep2 = false;
  snd_place = false;
  SDL_Delay(10);
  usleep(33);
 }
}

