/*
==============================================================================
=  NATIVE C++ FUNCTIONS AND OPENGL ARE INCLUDED IN THIS PART OF THE PROGRAM  =
==============================================================================
*/
#include <GL/glut.h> // linux parameters: -lGL -lGLU -lglut  windows parameters: -lopengl32 -freeglut -lglu32 (if missing use: -lglut32 too)
#include <mysql/mysql.h>  // linux parameters: -L/usr/include/mysql -lmysqlclient -I/usr/include/mysql
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <string.h> 
#include <sstream>
#include <fstream>
#include <stdlib.h>
/*
=====================================================================
=        THIS HEADER IS THE ONE USED FOR ALL GLOBAL VARIABLES       =
=====================================================================
*/
#include "Data/Headers/Game_Main_Global_variables.h" // AL GLOBAL VARIABLES OF THE GAME
/*
====================================================
=         ALL GAME ENGINE FUNCTIOS GO HERE         =
====================================================
*/
#include "Data/Headers/Bon_Sky_Model.h"       // MODULE THAT INCLUDES THE SKY
#include "Data/Headers/Bon_OptCube_Model.h"   // OPTIMIZED CUBE FUNCTION (RENDERS AN OPTIMIZED CUBE THAT SHOWS ONLY VISIBLE PARTS)
#include "Data/Headers/Bon_Aux_Functions.h"   // SET UP FUNCTIONS
#include "Data/Classes/chunks.h"              // CHUNK ENGINE
#include "Data/Headers/Bon_keyboard_Module.h" // PLAYER CONTROLLER
#include "Data/Headers/Bon_Display_Module.h"  // DISPLAY CONTROLLER
/*
============================================================================================
=    PRINCIPAL FUNCTION FOR THE GAME THIS IS THE MAIN BLOCK THAT EXECUTES ALL STATEMENTS   =
============================================================================================
*/
int main(int argc, char **argv){                             // MAIN FUNCTION FOR PROGRAM FUNCTIONALITY
 connect = mysql_init(NULL);                                 // START THE MYSQL OBJECT
 if(!connect){                                               // IF THE SERVER WAS NOT ABLE TO BE FOUND
  std::cout<<"could not start mysql client...\nERROR: ";     // SHOW THE ERROR MESSAGE WITH THE CRASH
  std::cout<<mysql_errno(connect)<<std::endl; // crash 
  exit(1);                                                   // EXIT THE GAME
 }
 if(mysql_real_connect(connect, SERVER, USER, PASS, DBCP, 3306, NULL, 0)){ // ELSE IT WILL CONNECT TO SERVER AND DATABASE
  std::cout<<"MySQL connected correctly to server :D"<<std::endl;          // SUCCESS MESSAGE ON CONNECTING
 }else{
  std::cout<<"Could not connect to MySQL server D:";                       // IF YOU COULDN'T CONNECT TO SERVER
  std::cout<<std::endl<<"ERROR: "<<mysql_errno(connect)<<"\n";             // THROW ERROR MESSAGE
 }
 glutInit(&argc, argv);                                        // START THE OPENGL LIBRARY FOR THE GAME
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);    // INITIALIZE THE GRAPHICS MODE ON DISPLAY
  glutInitWindowSize(BON_SCREEN_W,BON_SCREEN_H);               // SET THE WINDOW SIZE
  glutInitWindowPosition(300,64);                              // SET THE WINDOW POSITION
  glutCreateWindow("= CLIENT: Block Universe =");              // CREATE A GLUT WINDOW FOR THE GAME
 glDepthFunc(GL_LEQUAL);                                       // START THE DEPTH FUNCTION
 glClearDepth(1.0f);                                           // CLEAR THE DEPTH BUFFER
 glIni();                                                      // THE SETUP FUNCTION
  glutDisplayFunc(BON_GRAPH_FUNCTION);                         // THE FUNCTION TO INITIALIZE AND DRAW THE OBJECTS
  glutKeyboardFunc(BON_KEYBOARD_FUNCTION);                     // THE FUNCTION FOR KEYBOARD INTERACTIONS
  glutMouseFunc(BON_MOUSE_BUTTONS);                            // THE FUNCTION FOR MOUSE BUTTON DETECTION
  glutPassiveMotionFunc(BON_MOUSE_FUNCTION);                   // THE FUNCTION FOR THE MOUSE INTERACTIONS
  glutIdleFunc(BON_IDLE_FUNCTION);                             // THE FUNCTION WHEN PLAYER IS NOT DOING ANYTHING
 glutMainLoop();                                               // MAIN LOOP FOR THE GAME
 return EXIT_SUCCESS;                                          // RETURN STATEMENT SAME AS RETURN 0;
}
