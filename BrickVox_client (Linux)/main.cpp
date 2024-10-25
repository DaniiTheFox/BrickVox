/*
==============================================================================
=  NATIVE C++ FUNCTIONS AND OPENGL ARE INCLUDED IN THIS PART OF THE PROGRAM  =
==============================================================================
*/
#include <GL/glut.h> // linux parameters: -lGL -lGLU -lglut  windows parameters: -lopengl32 -freeglut -lglu32 (if missing use: -lglut32 too)
#include <mysql/mysql.h>  // linux parameters: -L/usr/include/mysql -lmysqlclient -I/usr/include/mysql
#ifdef _AUDIO
#include "SDL2/SDL.h"      // SDL VIDEO LIBRARY: `sdl2-config --cflags --libs`
#include "SDL2/SDL_mixer.h"// SDL AUDIO LIBRARY_ lSDL2_mixer <^-- both used for 
#endif
//creating the audio manager
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <string.h> 
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <thread>
#include <future>
#include <chrono>
#include <iomanip>
#include <time.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <random>
/*
=====================================================================
=        THIS HEADER IS THE ONE USED FOR ALL GLOBAL VARIABLES       =
=====================================================================
*/
#include "Data/Headers/Game_Main_Global_variables.h" // ALL GLOBAL VARIABLES OF THE GAME
#include "Data/Headers/Model_Global_Load.h"          // ALL MODEL LOADING OBJECTS FOR GAME
/*
====================================================
=         ALL GAME ENGINE FUNCTIOS GO HERE         =
====================================================
*/
#define STB_IMAGE_IMPLEMENTATION"
#include "Data/Headers/stb_image.h"
#ifdef _AUDIO
#include "Data/Headers/Bon_Audio_Manager1.h"  // AUDIO MANAGER FOR THE COMPUTER
#include "Data/Headers/Bon_Audio_Manager2.h"  // AUDIO MANAGER FOR THE COMPUTER
#endif
#include "Data/Headers/Bon_Sky_Model.h"       // MODULE THAT INCLUDES THE SKY
#include "Data/Headers/Bon_OptCube_Model.h"   // OPTIMIZED CUBE FUNCTION (RENDERS AN OPTIMIZED CUBE THAT SHOWS ONLY VISIBLE PARTS)
#include "Data/Headers/Bon_Reflection.h"      // MODULE THAT DRAWS THE REFLECTIVE OBJECTS AROUND THE WORLD
#include "Data/Headers/Bon_Aux_Functions.h"   // SET UP FUNCTIONS
#include "Data/Headers/Bon_terminal_module.h" // THIS INCLUDES THE TERMINAL MODULE INTO THE GAME
#include "Data/Headers/Bon_flat_obj.h"        // OPTIMIZED CUSTOM OBJECT MODELS FOR PLAYERS (PLANE THAT ALWAYS LOOK AT USER)
#include "Data/Headers/Bon_perlin_manager.h"  // FUNCTION THAT CREATES PERLIN
#include "Data/Classes/chunks.h"              // CHUNK ENGINE
#include "Data/Headers/Bon_Emitter_1.h"       // PARTICLE EMITTER FOR THE GAME
#include "Data/Headers/Bon_Mply_Module.h"     // ALL FUNCTIONS NEEDED TO LOAD THE 3D MODEL OF PLAYER
#include "Data/Classes/mltply.h"              // PLAYER ENGINE
#include "Data/Headers/obj_loader.h"          // IMPORT OTHER MODELS
#include "Data/Headers/Bon_Inventory_Module.h"// INVENTORY ENGINE
#include "Data/Headers/Bon_loading_screen.h"  // JUST A DETAIL TO AVOID BLACK SCREEN ON START
#include "Data/Headers/Bon_setup_Module.h"    // SETUP FUNCTION
#include "Data/Headers/Bon_keyboard_Module.h" // PLAYER CONTROLLER
#include "Data/Headers/Bon_script_service.h"  // INITIALIZE THE SCRIPTING SERVICE EXECUTION WHILE GAMEPLAY
#include "Data/Headers/Bon_Display_Module.h"  // DISPLAY CONTROLLER
#include "Data/Headers/Bon_Main_Module.h"     // MAIN MODULE
/*
============================================================================================
=    PRINCIPAL FUNCTION FOR THE GAME THIS IS THE MAIN BLOCK THAT EXECUTES ALL STATEMENTS   =
============================================================================================
*/
int main(int argc, char **argv){                             // MAIN FUNCTION FOR PROGRAM FUNCTIONALITY
 connect = mysql_init(NULL);                                 // START THE MYSQL OBJECT
 if(!connect){                                               // IF THE SERVER WAS NOT ABLE TO BE FOUND
  std::cout<<"could not start mysql client...\nERROR: ";     // SHOW THE ERROR MESSAGE WITH THE CRASH
  std::cout<<mysql_errno(connect)<<std::endl;                // crash 
  exit(1);                                                   // EXIT THE GAME
 }

 if(mysql_real_connect(connect, argv[3], argv[4], argv[5], DBCP, 3306, NULL, 0)){// ELSE IT WILL CONNECT TO SERVER AND DATABASE
  std::cout<<"MySQL connected correctly to server :D"<<std::endl;                // SUCCESS MESSAGE ON CONNECTING
  #ifdef linux                                                                   // TEST IF IT'S LINUX
   system("clear");                                                              // clear the screen of all text
  #endif
  //std::cout<<"Session_value: ";
  //std::cin>>current_sesion;
  current_sesion = atoi(argv[1]);
  invalidusr:                                                              // loop for invalid user -- for invalid user
  //std::cout<<"username: ";                                               // show message for player
  //std::cin>>tmp_username;     
  tmp_username = argv[2];                                                  // let user input his/her name
   for(int i = 0; i < strlen(tmp_username.c_str()); i++){                  // loop through all the username
     if(tmp_username[i] == char(34) || tmp_username[i] == char(39)){       // if uses " or ' then reject the username to avoid exploiting
       std::cout<<"Invalid username, please retry"<<std::endl;             // show invalid message
       goto invalidusr;                                                    // jump to input username again
     }
   }
  upload_obj_model("MySkin/char.obj");                  // READ THE 3D MODEL FROM FILE AND UPLOAD IT AS RAW ON DATABASE
  upload_url_ffile("MySkin/self.skn");                  // READ THE URL FOR THE IMAGE AND UPLOAD IT TO THE DATABASE
  mysql_query(connect, "SELECT P_Joined FROM Players_ingame ORDER BY P_Joined DESC LIMIT 1;");
  res_set = mysql_store_result(connect);               // SAVE RESULT INTO RES VARIABLE FROM OLD QUERY OF LAST LOGGED IN
  int pnum = mysql_num_rows(res_set);                  // GET NUMBER OF RESULTS
  if(pnum > 0){                                        // IF NOT EMPTY THERE ARE PLAYERS IN GAME                        
   row = mysql_fetch_row(res_set);                     // SET SAVED STATE TO NEXT QUERY            
   jnt = atoi( row[0] )+1;                             // TO BE ABLE TO DETECT JOINING ON OTHER PLAYER CLIENTS                 
  }else{                                                                                               
   jnt = 1;                                            // ELSE ADD ID 1 AS FIRST PLAYER JOINED
  }
  std::string addu = "INSERT INTO Players_ingame (Username, Pos_X, Pos_Y, Pos_Z, Rot_P, Model, Texture, P_Joined,Sesion) VALUES ('"+tmp_username+"',8,51,8,180,'"+tmp_model+"','"+tmp_linki+"',"+std::to_string(jnt)+","+std::to_string(current_sesion)+");";
  if(mysql_query(connect, addu.c_str())){
   std::cout<<"Could not Join the game D:";                                 // IF YOU COULDN'T CONNECT TO SERVER
   std::cout<<std::endl<<"ERROR: "<<mysql_errno(connect)<<"\n";             // THROW ERROR MESSAGE
   exit(1);
  }
 }else{
  std::cout<<"Could not connect to MySQL server D:";                       // IF YOU COULDN'T CONNECT TO SERVER
  std::cout<<std::endl<<"ERROR: "<<mysql_errno(connect)<<"\n";             // THROW ERROR MESSAGE
 }
 auto ma = std::async(glut_main,argc,argv);
 auto ud = std::async(Position_Update);
 #ifdef _AUDIO
 auto am = std::async(Bon_AudioM_Init);
 #endif
 std::cout<<"\e[1;33m STARTING THREAD OF SCRIPTS \e[0m;"<<std::endl;
 std::thread script_toRun[100];
 for(int i = 0; i < 100; i++){
  std::cout<<"\e[1;33m SERVICE "<<i<<" STARTING......... \e[0m;"<<std::endl;
  script_toRun[i] = std::thread(Bon_code_service,i);
 }
 for(int i = 0; i < 100; i++){
  std::cout<<"\e[1;33m SERVICE "<<i<<" RUNNING.... \e[0m;"<<std::endl;
  script_toRun[i].join();
 }
 return EXIT_SUCCESS;                                          // RETURN STATEMENT SAME AS RETURN 0;
}
