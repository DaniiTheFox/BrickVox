/*
===========================================================
=   FUNCTIONS THAT CONTROLL THE PLAYER MOVEMENTS IN GAME  =
===========================================================
*/
int sensib = 15;
void BON_KEYBOARD_FUNCTION(unsigned char key, int x, int y){
 switch(key){
  case 'i':if(is_texting==false){if(ctx_menu==false){ctx_menu=true;glutAttachMenu(GLUT_RIGHT_BUTTON);}else{ctx_menu=false;glutDetachMenu(GLUT_RIGHT_BUTTON);}if(has_terminal==false){has_terminal=true;}else{has_terminal=false;}}break;
 }
 if(is_texting == false && has_inventory == false){
 float tx, tz;                                               // temporal variables for player position
 switch(key){
  case '.':glutDestroyWindow(1);break;                       // . key quits the game
  case 'w':                                                  // if w is pressed
    up=true;
  break;
  case 's':                                                  // if key S is pressed move behind
   down=true;
  break;
  case 'a':                                                  // if key A pressed move to side
   left=true;
  break;
  case 'd':
   right=true;
  break;
  case ' ':                                                  // if space is pressed move up
  py++;
  break;
  case 'x':                                                  // if X is pressed move down
  py--;
  break;
  
  case 'z':
  h_vnum = b_load_obj_model("MySkin/arm.obj",hand_mdl,hand_uvs,h_vnum);
  break;
  
  case 't':                                                  // if Q is pressed
   is_texting = true; chat_tosend = "<"+tmp_username+">> ";
  break;
  case 'q':if(is_toggled==false){is_toggled=true;}else{is_toggled=false;}break;
  case 'e':
   if(ctx_menu==false){ctx_menu=true;}else{ctx_menu=false;}
   if(has_inventory==false){has_inventory=true;}else{has_inventory=false;}
  break;
  //case '-':lock_query = true;mysql_query(connect, "DELETE FROM Modifications WHERE Chunk_ID >= 0;");lock_query = false;break;
 }
 }else if(has_inventory == true){
   // inventory controls go here lol
   switch(key){
    case 'e':
     if(ctx_menu==false){ctx_menu=true;glutAttachMenu(GLUT_RIGHT_BUTTON);}else{ctx_menu=false;glutDetachMenu(GLUT_RIGHT_BUTTON);}
     if(has_inventory==false){has_inventory=true;}else{has_inventory=false;}
    break;
    case 13:
     snd_beep2 = true;
     if(ctx_menu==false){ctx_menu=true;glutAttachMenu(GLUT_RIGHT_BUTTON);}else{ctx_menu=false;glutDetachMenu(GLUT_RIGHT_BUTTON);}
     if(has_inventory==false){has_inventory=true;}else{has_inventory=false;}
     current_block = pointer_blk;
    break;
    case 's':
     snd_beep1 = true;
     pointer_inv++;pointer_blk++;if(pointer_blk > array_limit){pointer_blk=1;block_selecting = 0;pointer_inv = 1;}
     if(pointer_inv > array_limit){pointer_blk=1;block_selecting = 0;pointer_inv = 1;}
    break;
    case 'w':
     snd_beep1 = true;
     pointer_inv--;pointer_blk--;if(pointer_blk < 0){pointer_blk=1;block_selecting = 0;pointer_inv = 1;}
     if(pointer_inv < 0){pointer_inv=items_n-1;block_selecting-=items_n;}
    break;
   }
 }else{
  if(key == 13){is_texting = false;}
  else{
    if(key != 34 && key != 39 && key!=8){
      chat_tosend = chat_tosend + char(key);
    }
    if(key == 8){
     if(strlen(chat_tosend.c_str())>0){
      for(int i = 0; i < strlen(chat_tosend.c_str())-1; i++){
       msg2cls = msg2cls + chat_tosend[i];
      }
      chat_tosend = msg2cls;
      msg2cls = "";
     }
   }
  }
 }
}

void BON_KEYBOARD_RELEASE(unsigned char key, int x, int y){
 switch(key){
  case 'w':up=false;break;
  case 's':down=false;break;
  case 'd':right=false;break;
  case 'a':left=false;break;
 }
}

void BON_KEYBOARD_ACTIONS(){
 if(ctx_menu==false){
   glutDetachMenu(GLUT_RIGHT_BUTTON);
 }
 if(is_tpv==true){
    // control of the third person camera view
   if(up==true){
      if(up==true&&left==true){
      pa = angle+225;
      if(pa <= 0){
       pe = 360+(pa);
       pa = pe;
      }
      nx = px+cos(((angle+225)*3.14159)/180)*(user_speed/2);
      nz = pz-sin(((angle+225)*3.14159)/180)*(user_speed/2);
      px = nx,pz = nz;
      //player->set_pos_rot(nx,colider_h,nz,pa);
      Wrl_Sys.Chunk_Update();
    }else if(up==true&&right==true){
      pa = angle+135;
      if(pa <= 0){
       pe = 360+(pa);
       pa = pe;
      }
      nx = px+cos(((angle+135)*3.14159)/180)*(user_speed/2);
      nz = pz-sin(((angle+135)*3.14159)/180)*(user_speed/2);
      px = nx,pz = nz;
      //player->set_pos_rot(nx,colider_h,nz,pa);
      Wrl_Sys.Chunk_Update();
    }else{
     pa = angle+180;
     if(pa <= 0){
      pe = 360+(pa);
      pa = pe;
     }
     nx = px+cos(((angle+180)*3.14159)/180)*(user_speed/2);
     nz = pz-sin(((angle+180)*3.14159)/180)*(user_speed/2);
     px = nx,pz = nz;
     //player->set_pos_rot(nx,colider_h+1,nz,pa);
     Wrl_Sys.Chunk_Update();
    }
   }
   if(down==true){
     if(down==true&&left==true){
      pa = angle+315;
      if(pa <= 0){
       pe = 360+(pa);
       pa = pe;
      }
      nx = px+cos(((angle+315)*3.14159)/180)*(user_speed/2);
      nz = pz-sin(((angle+315)*3.14159)/180)*(user_speed/2);
      px = nx,pz = nz;
      //player->set_pos_rot(nx,colider_h,nz,pa);
      Wrl_Sys.Chunk_Update();
    }else if(down==true&&right==true){
      pa = angle+45;
      if(pa <= 0){
       pe = 360+(pa);
       pa = pe;
      }
      nx = px+cos(((angle+45)*3.14159)/180)*(user_speed/2);
      nz = pz-sin(((angle+45)*3.14159)/180)*(user_speed/2);
      px = nx,pz = nz;
      //player->set_pos_rot(nx,colider_h,nz,pa);
      Wrl_Sys.Chunk_Update();
    }else{
      pa = angle;
      if(pa <= 0){
       pe = 360+(pa);
       pa = pe;
      }
      nx = px+cos(((angle)*3.14159)/180)*(user_speed/2);
      nz = pz-sin(((angle)*3.14159)/180)*(user_speed/2);
      px = nx,pz = nz;
      //player->set_pos_rot(nx,colider_h,nz,pa);
      Wrl_Sys.Chunk_Update();
    }
   }
   if(left==true && up==false && down == false){
     pa = angle+270;
     if(pa <= 0){
      pe = 360+(pa);
      pa = pe;
     }
     nx = px+cos(((angle+270)*3.14159)/180)*(user_speed/2);
     nz = pz-sin(((angle+270)*3.14159)/180)*(user_speed/2);
     px = nx,pz = nz;
      //player->set_pos_rot(nx,colider_h,nz,pa);
      Wrl_Sys.Chunk_Update();
   }
   if(right==true && up==false && down == false){
     pa = angle+90;
     if(pa <= 0){
      pe = 360+(pa);
      pa = pe;
     }
     nx = px+cos(((angle+90)*3.14159)/180)*(user_speed/2);
     nz = pz-sin(((angle+90)*3.14159)/180)*(user_speed/2);
     px = nx,pz = nz;
     //player->set_pos_rot(nx,colider_h,nz,pa);
     Wrl_Sys.Chunk_Update();
   }
   if(down==true&&up==true){
    down=false;
   }
   //if(left==true&&right==true){
   // left=false;
   //}
  }else{
    // control of the first person camera view
    if(up==true){
     if(up==true&&left==true){
      tx = px+cos(((angle+45)*3.14159)/180)*(user_speed/2);    // this inverts the angle
      tz = pz-sin(((angle+45)*3.14159)/180)*(user_speed/2);    // of where player is looking at
      px = tx;                                                  // and jumps to those positions
      pz = tz;
      Wrl_Sys.Chunk_Update();
     }else if(up==true&&right==true){
      tx = px+cos(((angle+315)*3.14159)/180)*(user_speed/2);    // this inverts the angle
      tz = pz-sin(((angle+315)*3.14159)/180)*(user_speed/2);    // of where player is looking at
      px = tx;                                                  // and jumps to those positions
      pz = tz;
      Wrl_Sys.Chunk_Update();
     }else{
      px = cx;                                                  // then the player is jumping
      pz = cz;                                                  // to where it's looking at on x and z axis
      Wrl_Sys.Chunk_Update();
     }
    }
    if(down==true){
     if(down==true&&left==true){
      tx = px+cos(((angle+135)*3.14159)/180)*(user_speed/2);    // this inverts the angle
      tz = pz-sin(((angle+135)*3.14159)/180)*(user_speed/2);    // of where player is looking at
      px = tx;                                                  // and jumps to those positions
      pz = tz;
      Wrl_Sys.Chunk_Update();
    }else if(down==true&&right==true){
      tx = px+cos(((angle+225)*3.14159)/180)*(user_speed/2);    // this inverts the angle
      tz = pz-sin(((angle+225)*3.14159)/180)*(user_speed/2);    // of where player is looking at
      px = tx;                                                  // and jumps to those positions
      pz = tz;
      Wrl_Sys.Chunk_Update();
     }else{
      tx = px+cos(((angle+180)*3.14159)/180)*(user_speed/2);    // this inverts the angle
      tz = pz-sin(((angle+180)*3.14159)/180)*(user_speed/2);    // of where player is looking at
      px = tx;                                                  // and jumps to those positions
      pz = tz;
      Wrl_Sys.Chunk_Update();
     }
    }
    if(left==true && up==false && down == false){
     tx = px+cos(((angle+90)*3.14159)/180)*(user_speed/3);     // calculate side position
     tz = pz-sin(((angle+90)*3.14159)/180)*(user_speed/3);
     px = tx;                                                  // and jump to that position
     pz = tz;
     Wrl_Sys.Chunk_Update();
    }
    if(right==true && up==false && down == false){
     tx = px+cos(((angle-90)*3.14159)/180)*(user_speed/3);     // if key D pressed move to other side
     tz = pz-sin(((angle-90)*3.14159)/180)*(user_speed/3);     // calculate the other side position
     px = tx;                                                  // jump to that position
     pz = tz;
     Wrl_Sys.Chunk_Update();
    }
    if(down==true&&up==true){
      down=false;
    }
    //if(left==true&&right==true){
    //  left=false;
    //}
  }
}

/*
void phy_upd(int val){
  if(particles_active==true){
  particle_pointer = test_particle.Dynamics_Update();
  }
  glutTimerFunc(dt*1000, phy_upd, 0); // RECURSIVIDAD PARA VOLVER A ACTUALIZAR EL TIMER
}*/

void BON_MOUSE_BUTTONS(int button, int state, int x, int y){
if(is_tpv==false){
if(ctx_menu == false){
 glutSetCursor(GLUT_CURSOR_NONE);
 if(button == GLUT_RIGHT_BUTTON){
  Wrl_Sys.Chunk_Edit_Add(loc_X,loc_Y,dx,ry,dz,current_block);
  snd_place = true;
 }
 if(button == GLUT_LEFT_BUTTON){
  //if(Wrl_Sys.Chunk_Get_Info(loc_X,loc_Y,dx,ry,dz) != 0){
  Wrl_Sys.Chunk_Edit_Add(loc_X,loc_Y,dx,ry,dz,0);
  //}
  snd_place = true;
 }
 if(button == 3){
  zom++;
 }else if(button == 4){
  zom--;
 }
 if(x < ((BON_SCREEN_W/2)-sensib)){                 // identify if the cursor is not centered to screen
 angle+=1;                                      // if x is less than screen move angle increments 2
 if(angle < 0){
  angle = 359;                                  // avoid angle override the main 360 grades
 }
 if(angle > 359){
  angle = 0;                                    // avoid angle override the main 360 grades
 }
  glutWarpPointer(BON_SCREEN_W/2,BON_SCREEN_H/2);// reset the pointer position
 }else if(x > ((BON_SCREEN_W/2)+sensib)){           //and then we repat the process to the other side
 angle-=1;                                      // the constant 30 represents the sensibility of the mouse 
 if(angle < 0){                                 // avoid angle override the main 360 grades
  angle = 359;
 }
 if(angle > 359){                               // avoid angle override the main 360 grades
  angle = 0;
 }
  glutWarpPointer(BON_SCREEN_W/2,BON_SCREEN_H/2); // reset the pointers position to center to screen
 }
 if(y > (BON_SCREEN_H/2)+sensib){                     // and we repeat the process with X axis but on Y
  angl2+=1;
  glutWarpPointer(BON_SCREEN_W/2,BON_SCREEN_H/2); // we trap the pointer
 }else if(y < (BON_SCREEN_H/2)-sensib){               // and check if it moves towards up or down
  angl2-=1;                                       // and move the camera angle
  glutWarpPointer(BON_SCREEN_W/2,BON_SCREEN_H/2); // and reset the pointer
 }
 glutPostRedisplay();
 }else{
 glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
 }
 }else{
  if (button == 3){
  if(zoom > 3){
   zoom--;
  }
  }else if(button == 4){
   zoom++;
  }
 }
}

void BON_MOUSE_MOTION(int x, int y){
if(is_tpv==true){
if(x < old_mx-10){
 angle-=4;
 if(angle < 0){
  angle = 356;
 }
 if(angle > 356){
  angle = 0;
 }
 //glutWarpPointer(240,240);
 old_mx = x;
 }else if(x > old_mx+10){
 angle+=4;
 if(angle < 0){
  angle = 356;
 }
 if(angle > 356){
  angle = 0;
 }
 //glutWarpPointer(240,240);
 old_mx = x;
 }
 if(y < old_my-10){
  angl2+=4;
  //glutWarpPointer(240,240);
  old_my = y;
 }else if(y > old_my+10){
  angl2-=4;
  //glutWarpPointer(240,240);
  old_my = y;
 }
}
}

void BON_MOUSE_FUNCTION(int x, int y){          // moving camera function
 if(is_tpv==false){
 if(ctx_menu == false){
 glutSetCursor(GLUT_CURSOR_NONE);
 if(x < ((BON_SCREEN_W/2)-sensib)){                 // identify if the cursor is not centered to screen
 angle+=1;                                      // if x is less than screen move angle increments 2
 if(angle < 0){
  angle = 359;                                  // avoid angle override the main 360 grades
 }
 if(angle > 359){
  angle = 0;                                    // avoid angle override the main 360 grades
 }
  glutWarpPointer(BON_SCREEN_W/2,BON_SCREEN_H/2);// reset the pointer position
 }else if(x > ((BON_SCREEN_W/2)+sensib)){           //and then we repat the process to the other side
 angle-=1;                                      // the constant 30 represents the sensibility of the mouse 
 if(angle < 0){                                 // avoid angle override the main 360 grades
  angle = 359;
 }
 if(angle > 359){                               // avoid angle override the main 360 grades
  angle = 0;
 }
  glutWarpPointer(BON_SCREEN_W/2,BON_SCREEN_H/2); // reset the pointers position to center to screen
 }
 if(y > (BON_SCREEN_H/2)+sensib){                     // and we repeat the process with X axis but on Y
  angl2+=1;
  glutWarpPointer(BON_SCREEN_W/2,BON_SCREEN_H/2); // we trap the pointer
 }else if(y < (BON_SCREEN_H/2)-sensib){               // and check if it moves towards up or down
  angl2-=1;                                       // and move the camera angle
  glutWarpPointer(BON_SCREEN_W/2,BON_SCREEN_H/2); // and reset the pointer
 }
 glutPostRedisplay();
 }else{
 glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
 }
 }else{
   glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
 }
}
