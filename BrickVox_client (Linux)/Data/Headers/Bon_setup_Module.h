/*
==========================================================================
=   TODO: IMPORTANT: FUNCTION TO SET UP ALL THE PROGRAM AND OPENGL STUFF = <---
==========================================================================
*/
#include "Bon_TexLd_Module.h"                                     // LOADED HERE SO ALL FUNCTIONS ARE ENABLED

void game_update(int val){
 //std::cout<<"creating new thread"<<std::endl;
 Ply_Mng->Player_Update(); 
 //std::cout<<"new thread created"<<std::endl;
}

void game_controller_upd(int val){
 game_update(1);
 glutPostRedisplay();
 glutTimerFunc(100, game_controller_upd , 0);
}

void context_menu(int value){
 switch(value){
  case 1:break;
  case 2:break;
  case 3:break;
  case 4:glutDestroyWindow(1);break;
  case 5:
   if(is_night==true){
    is_night=false;
    glMaterialfv(GL_FRONT, GL_AMBIENT, amb_mt);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_md);
    bon_push_into_cmd("<BrickVox Client>> Time has been set to day!");
   }else{
    is_night=true;
    glMaterialfv(GL_FRONT, GL_AMBIENT, n_amb_mt);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, n_amb_md);
    bon_push_into_cmd("<BrickVox Client>> Time has been set to Night!");
   }
  break;
  case 6:if(has_cloud==true){has_cloud=false;bon_push_into_cmd("<BrickVox Client>> Clouds off!");}else{has_cloud=true;bon_push_into_cmd("<BrickVox Client>> Clouds On!");}break;
  case 12:if(is_tpv==false){is_tpv=true;}else{is_tpv=false;}break;
 }
 has_terminal=false;
 ctx_menu=false;
}

void Initialize_custom(){
 std::string query_object_f = "SELECT * FROM custom_object WHERE Sesion = 0 OR Sesion = "+std::to_string(current_sesion)+";";
 //mysql_free_result(res_set);
 mysql_query(connect, query_object_f.c_str());
 res_set = mysql_store_result(connect);
 if(res_set!=NULL){ 
  obj_num = mysql_num_rows(res_set);
  int o_ptr = 0;
  int ot_id=0; std::string ot_code, ot_name, ot_url;
  while((row=mysql_fetch_row(res_set))!=NULL){
   ot_id = atoi(row[0]);
   ot_code = row[2];
   ot_url  = row[4];
   ot_name = row[1];
   object_array[o_ptr].Flat_ini(0.5,ot_url,ot_name,array_limit+ot_id-1,ot_code);
   o_ptr++;
  }
 }
 mysql_free_result(res_set);
}

void Bon_draw_self(float x_,float y_,float z_,float r_,double _s_mdl[9][9000],double _s_uvs[6][9000]){
   glTranslatef(x_,y_,z_); // translate the shape to the player position
   glRotatef(r_,0,r_,1);               // rotate the player to it's position
   // from here begins the rendering of the players
   glBindTexture(GL_TEXTURE_2D, selft_text); // assign their players the 
   glBegin(GL_TRIANGLES);                    // draw the player shape by triangles for each polygon (might help into shading on a future)
   //std::cout<<"vertex number loaded as: "<<s_vnum<<std::endl; // just a debug message
    for(int z = 0; z < s_vnum; z++){ 
     /*if(_s_mdl[1][z] >= 0){
      glColor3f(0.2+(py/100)+abs(_s_mdl[1][z]),0.2+(py/100)+abs(_s_mdl[1][z]),0.2+(py/100)+abs(_s_mdl[1][z]));
     }else{
      glColor3f(0.2+(py/100)+(0),0.2+(py/100)+(0),0.2+(py/100)+(0));
     }*/
     glColor3f(1,1,1);
                             // draw each triangle of the model
     glTexCoord2f(_s_uvs[0][z],  _s_uvs[1][z]);                // -
     glVertex3f(_s_mdl[0][z], _s_mdl[1][z], _s_mdl[2][z]);     //  |
     
     /*if(_s_mdl[4][z] >= 0){
      glColor3f(0.2+(py/100)+abs(_s_mdl[4][z]),0.2+(py/100)+abs(_s_mdl[4][z]),0.2+(py/100)+abs(_s_mdl[4][z]));
     }else{
      glColor3f(0.2+(py/100)+(0),0.2+(py/100)+(0),0.2+(py/100)+(0));
     }*/
                                                               //  |
     glTexCoord2f(_s_uvs[2][z],  _s_uvs[3][z]);                //  | texture mapping
     glVertex3f(_s_mdl[3][z], _s_mdl[4][z], _s_mdl[5][z]);     //  | and vertex
                                                               //  |
     /*if(_s_mdl[7][z] >= 0){
      glColor3f(0.2+(py/100)+abs(_s_mdl[7][z]),0.2+(py/100)+abs(_s_mdl[7][z]),0.2+(py/100)+abs(_s_mdl[7][z]));
     }else{
      glColor3f(0.2+(py/100)+(0),0.2+(py/100)+(0),0.2+(py/100)+(0));
     }*/
                                                               
     glTexCoord2f(_s_uvs[4][z],  _s_uvs[5][z]);                //  |
     glVertex3f(_s_mdl[6][z], _s_mdl[7][z], _s_mdl[8][z]);     // -
    }
   glEnd(); // end of drawing the shape of the player 
}

void Bon_load_Self(){
    download_bmp_image("Self_Skin", tmp_linki);
    selft_text  = Bon_load_bmp("./Temporal/Skins/tmpimg_Self_Skin.bmp",128,64);
    bridge = tmp_model;
    h_vnum = b_load_obj_model("MySkin/arm.obj",hand_mdl,hand_uvs,h_vnum);
    load_obj_model(tmp_model, self_model, self_uv);
    s_vnum = _n;
}

void glIni(){                                                     // function to start the setup
 glClearColor(0,0,0,0);                                           // define a default background color (not used in fact)
 glEnable(GL_TEXTURE_2D);                                         // enable the use of textures
 glEnable(GL_BLEND);                                              // enable blending for textures
 glEnable(GL_DEPTH_TEST);                                         // enable depth for 3d perspective on open GL
 glutSetCursor(GLUT_CURSOR_NONE);
 glutCreateMenu(context_menu);
 glutAddMenuEntry("-- PLAYER OPTIONS --",      0);
 glutAddMenuEntry("change player view"  ,     12);
 glutAddMenuEntry("-- WORLD EDIT TOOLS --",    0);
 glutAddMenuEntry("remove grass zone",        13);
 glutAddMenuEntry("-- OBJECT EDITOR TOOLS --", 0);
 glutAddMenuEntry("-- GAME OPTIONS --",        0);
 glutAddMenuEntry("Change Day/Night Time",     5);
 glutAddMenuEntry("Toggle Clouds",             6);
 glutAddMenuEntry("quit game",                 4);
 glMatrixMode(GL_PROJECTION);                                     // set the matrix mode to projection
 glAlphaFunc(GL_GREATER, 0.5);
 glEnable(GL_ALPHA_TEST);
 glLoadIdentity();                                                // load all objects in scene
 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 //mcFog(13,20,10);                                                 // enable fog parameters
 mcFog(8,27,5);
 Bon_Load_all_textures();                                         // load all textures of the game
 draw_load_screen();
 glDisable(GL_LIGHTING);
 glEnable(GL_NORMALIZE);
  
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,  1);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_md);
  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
  glMaterialfv(GL_FRONT, GL_AMBIENT, amb_mt);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, dif_mt);
  glMaterialfv(GL_FRONT, GL_SPECULAR,spc_mt);
  glMaterialfv(GL_FRONT, GL_EMISSION,ems_mt);
  glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
  glEnable(GL_LIGHTING);

 Bon_load_Self();

 Initialize_custom();
 set_onInv();
 Ply_Mng->Player_Initialize();
 //btri3 = new Tree_base();
}
