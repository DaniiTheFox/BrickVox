/*
===========================================================
=   FUNCTIONS THAT CONTROLL THE PLAYER MOVEMENTS IN GAME  =
===========================================================
*/

void BON_KEYBOARD_FUNCTION(unsigned char key, int x, int y){
 float tx, tz;                                               // temporal variables for player position
 switch(key){
  case '.':glutDestroyWindow(1);break;                       // . key quits the game
  case 'w':                                                  // if w is pressed
   px = cx;                                                  // then the player is jumping
   pz = cz;                                                  // to where it's looking at on x and z axis
  break;
  case 's':                                                  // if key S is pressed move behind
   tx = px+cos(((angle+180)*3.14159)/180);                   // this inverts the angle
   tz = pz-sin(((angle+180)*3.14159)/180);                   // of where player is looking at
   px = tx;                                                  // and jumps to those positions
   pz = tz;
  break;
  case 'a':                                                  // if key A pressed move to side
   tx = px+cos(((angle+90)*3.14159)/180)*0.5;                // calculate side position
   tz = pz-sin(((angle+90)*3.14159)/180)*0.5;
   px = tx;                                                  // and jump to that position
   pz = tz;
  break;
  case 'd':
   tx = px+cos(((angle-90)*3.14159)/180)*0.5;                // if key D pressed move to other side
   tz = pz-sin(((angle-90)*3.14159)/180)*0.5;                // calculate the other side position
   px = tx;                                                  // jump to that position
   pz = tz;
  break;
  case ' ':                                                  // if space is pressed move up
  py++;
  break;
  case 'x':                                                  // if X is pressed move down
  py--;
  break;
  case 'q':                                                  // if Q is pressed
  std::cout<<"player x: "<<px<<" z:"<<pz<<std::endl;         // turn on debug
  std::cout<<xoff<<std::endl;
  isDebug = true;                                            // to debug the chunk system
  break;
  case '-':mysql_query(connect, "DELETE FROM Modifications WHERE Chunk_ID >= 0;");
 }
 Wrl_Sys.Chunk_Update();
}

void BON_MOUSE_BUTTONS(int button, int state, int x, int y){
 if(button == GLUT_RIGHT_BUTTON){
  Wrl_Sys.Chunk_Edit_Add(loc_X,loc_Y,dx,ry,dz,3);
 }
 if(button == GLUT_LEFT_BUTTON){
  Wrl_Sys.Chunk_Edit_Add(loc_X,loc_Y,dx,ry,dz,0);
 }
 if(button == 3){
  zom++;
 }else if(button == 4){
  zom--;
 }
 if(x < ((BON_SCREEN_W/2)-30)){                 // identify if the cursor is not centered to screen
 angle+=2;                                      // if x is less than screen move angle increments 2
 if(angle < 0){
  angle = 358;                                  // avoid angle override the main 360 grades
 }
 if(angle > 358){
  angle = 0;                                    // avoid angle override the main 360 grades
 }
  glutWarpPointer(BON_SCREEN_W/2,240);          // reset the pointer position
 }else if(x > ((BON_SCREEN_W/2)+30)){           //and then we repat the process to the other side
 angle-=2;                                      // the constant 30 represents the sensibility of the mouse 
 if(angle < 0){                                 // avoid angle override the main 360 grades
  angle = 358;
 }
 if(angle > 358){                               // avoid angle override the main 360 grades
  angle = 0;
 }
  glutWarpPointer(BON_SCREEN_W/2,BON_SCREEN_H/2); // reset the pointers position to center to screen
 }
 if(y > (BON_SCREEN_H/2)+30){                     // and we repeat the process with X axis but on Y
  angl2+=2;
  glutWarpPointer(BON_SCREEN_W/2,BON_SCREEN_H/2); // we trap the pointer
 }else if(y < (BON_SCREEN_H/2)-30){               // and check if it moves towards up or down
  angl2-=2;                                       // and move the camera angle
  glutWarpPointer(BON_SCREEN_W/2,BON_SCREEN_H/2); // and reset the pointer
 }
}

void BON_MOUSE_FUNCTION(int x, int y){          // moving camera function
 if(x < ((BON_SCREEN_W/2)-30)){                 // identify if the cursor is not centered to screen
 angle+=2;                                      // if x is less than screen move angle increments 2
 if(angle < 0){
  angle = 358;                                  // avoid angle override the main 360 grades
 }
 if(angle > 358){
  angle = 0;                                    // avoid angle override the main 360 grades
 }
  glutWarpPointer(BON_SCREEN_W/2,240);          // reset the pointer position
 }else if(x > ((BON_SCREEN_W/2)+30)){           //and then we repat the process to the other side
 angle-=2;                                      // the constant 30 represents the sensibility of the mouse 
 if(angle < 0){                                 // avoid angle override the main 360 grades
  angle = 358;
 }
 if(angle > 358){                               // avoid angle override the main 360 grades
  angle = 0;
 }
  glutWarpPointer(BON_SCREEN_W/2,BON_SCREEN_H/2); // reset the pointers position to center to screen
 }
 if(y > (BON_SCREEN_H/2)+30){                     // and we repeat the process with X axis but on Y
  angl2+=2;
  glutWarpPointer(BON_SCREEN_W/2,BON_SCREEN_H/2); // we trap the pointer
 }else if(y < (BON_SCREEN_H/2)-30){               // and check if it moves towards up or down
  angl2-=2;                                       // and move the camera angle
  glutWarpPointer(BON_SCREEN_W/2,BON_SCREEN_H/2); // and reset the pointer
 }
}
