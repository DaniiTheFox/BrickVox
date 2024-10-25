/*
========================================================
=  FUNCTION TO CONVERT THE PROGRAM TO 2D AND DRAW HUD  = Bon_draw_obj_l(hand_mdl,hand_uvs,h_vnum,selft_text);
========================================================
*/
void Bon_2d_Hud(){
  glDisable(GL_LIGHTING);
  glDisable(GL_ALPHA_TEST);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0, BON_SCREEN_W, BON_SCREEN_H, 0.0, -1.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glDisable(GL_CULL_FACE);
  glClear(GL_DEPTH_BUFFER_BIT);
  glColor3f(1.0,1.0,1.0);
   glBindTexture(GL_TEXTURE_2D, EYE_EFFECT_T);
   glBegin(GL_QUADS);
     glTexCoord2d(0,0);
     glVertex2f(0.0,   0.0);
     glTexCoord2d(1,0);
     glVertex2f(BON_SCREEN_W, 0.0);
     glTexCoord2d(1,1);
     glVertex2f(BON_SCREEN_W, BON_SCREEN_H);
     glTexCoord2d(0,1);
     glVertex2f(0.0,   BON_SCREEN_H);
   glEnd();
   glDisable(GL_TEXTURE_2D);
   glColor4f(0.044705882,0.044705882,0.044705882,0.5);
   glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(BON_SCREEN_W,0);
    glVertex2f(BON_SCREEN_W,((BON_SCREEN_H*15)/480));
    glVertex2f(0,((BON_SCREEN_H*15)/480));
   glEnd();
   glColor3f(1,1,1);
   std::string test_str = "BrickVox Indev v0.0.8.1024 by: boni!Soft";
   RenderString(5.0f,15.0f,test_str.c_str(), 1.0f,1.0f,1.0f);
   glEnable(GL_TEXTURE_2D);
   if(has_inventory == true){
    glDisable(GL_TEXTURE_2D);
    Bon_draw_inventory(); 
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
   }
   if(has_terminal==true){
    glDisable(GL_TEXTURE_2D);
    Bon_draw_terminal(); 
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
   }
   if(is_toggled == true){
   glDisable(GL_TEXTURE_2D);
   glColor4f(0.044705882,0.044705882,0.044705882,0.5);
   glBegin(GL_QUADS);
    glVertex2f(128,(BON_SCREEN_H-128));
    glVertex2f(BON_SCREEN_W,(BON_SCREEN_H-128));
    glVertex2f(BON_SCREEN_W,(BON_SCREEN_H));
    glVertex2f(128,(BON_SCREEN_H));
   glEnd();
   glColor3f(1,1,1);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,BVOX_LOGO);
   glBegin(GL_QUADS);
    glTexCoord2d(0,0);
    glVertex2f(0,(BON_SCREEN_H-128));
    glTexCoord2d(1,0);
    glVertex2f(128,(BON_SCREEN_H-128));
    glTexCoord2d(1,1);
    glVertex2f(128,(BON_SCREEN_H));
    glTexCoord2d(0,1);
    glVertex2f(0,(BON_SCREEN_H));
   glEnd();
   RenderString(133.0f,BON_SCREEN_H-15.0f,chat_tosend.c_str(), 1.0f,1.0f,1.0f);
   for(int i = 0; i < 6; i++){
    RenderString(133.0f,(BON_SCREEN_H-((15*i)+30)),chat_messages[i].c_str(), 1.0f,1.0f,1.0f);
   }
   }else{
    glDisable(GL_TEXTURE_2D);
    glColor4f(0.044705882,0.044705882,0.044705882,0.5);
    glBegin(GL_QUADS);
     glVertex2f(0,BON_SCREEN_H-15);
     glVertex2f(BON_SCREEN_W,BON_SCREEN_H-15);
     glVertex2f(BON_SCREEN_W,BON_SCREEN_H);
     glVertex2f(0,BON_SCREEN_H);
    glEnd();
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
   }
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_ALPHA_TEST);
  //glEnable(GL_LIGHTING);
}
/*
=======================================================
=   FUNCTION TO DRAW ALL OBJECTS ON SCENE AND CHUNKS  =
=======================================================
*/
void BON_GRAPH_FUNCTION(){                              // function of drawing stuff in scene
 isRunning2=true;
 //gluPerspective(60,gcd(BON_SCREEN_W,BON_SCREEN_H),0.1,3000);                           // set perspective with a cutwindow of 1000
 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  // clear the buffers on screen for color and depth
 glMatrixMode(GL_MODELVIEW);                            // set the matrix mode to view
 glEnable(GL_CULL_FACE);                                // enable the face culling
 glCullFace(GL_BACK);                                   // for model optimization
 glLoadIdentity();                                      // load all objects in scene
 BON_KEYBOARD_ACTIONS();
 if(is_tpv==true){
  cx = px+cos((angle*3.14159)/180)*zoom;
  cz = pz-sin((angle*3.14159)/180)*zoom;
  cy = py-sin((angl2*3.14159)/180)*zoom;
  gluLookAt(cx,cy,cz, px,py,pz, 0,1,0);
 }else{
  cx = px+cos((angle*3.14159)/180)*user_speed;           // calculate where player is looking on x axis
  cy = py-tan((angl2*3.14159)/180)*user_speed;                      // calculate where player is looking on y axis
  cz = pz-sin((angle*3.14159)/180)*user_speed;           // calculate where player is looking on z axis
  gluLookAt(px, py, pz, cx, cy, cz, 0,1,0);              // move the camera to player position and rotation
 }
 rx = px+cos((angle*3.14159)/180)*zom;                      // calculate where raycast is looking on x axis
 ry = py-tan((angl2*3.14159)/180)*zom;                      // calculate where player is looking on y axis
 rz = pz-sin((angle*3.14159)/180)*zom;                      // calculate where raycast is looking on y axis
 dx = (rx)/15; dz = (rz)/15;
 cox = dx;   coz = dz;
 dx = (dx - cox)*15; dz = (dz - coz)*15;
 if(cx < 0){dx = 15+dx;}
 if(cz < 0){dz = 15+dz;}
 for(int i = 0; i <= 7; i++){
 int lt_c = GL_LIGHT0 + i;
 float ars[3] = {0,0,0};
 glLightfv(lt_c, GL_POSITION, ars);
 }
 //glRotatef(angl2, 1.0, 0.0, 0.0);
 //glRotatef(-angle+180, 0.0, 1.0, 0.0);
 //glTranslatef(-pz,-py,px);

  glDisable(GL_LIGHTING);
  if(cy<=sea_level){
   rho = 0.2;  // density of the water
   if(is_night==false){
     BON_SKY();
     //glFogfv(GL_FOG_COLOR , FogColor);                   // set the fog color
     glClearColor(0.8,0.8,1.0,0.0);                      // set the background color
   }else{
     //glFogfv(GL_FOG_COLOR , NFogColor);                   // set the fog color
     glClearColor(0.0,0.0,0.00005,0.0);                      // set the background color
   }
   glFogfv(GL_FOG_COLOR , WFogColor); 
   glFogf(GL_FOG_START , 1 );                       // set where fog starts 
   glFogf(GL_FOG_END , 6);                           // set where fog ends
  }else{
   rho = 0.5;  // density of the water
   glFogf(GL_FOG_START , 8 );                       // set where fog starts 
   glFogf(GL_FOG_END , 27);                           // set where fog ends
   if(is_night==false){
     BON_SKY();
     glFogfv(GL_FOG_COLOR , FogColor);                   // set the fog color
     glClearColor(0.8,0.8,1.0,0.0);                      // set the background color
   }else{
     glFogfv(GL_FOG_COLOR , NFogColor);                   // set the fog color
     glClearColor(0.0,0.0,0.00005,0.0);                      // set the background color
   }
  }                       // draw the skybox of the game
  //glEnable(GL_LIGHTING);
  glColor3f(0,0,0);
  //glDisable(GL_TEXTURE_2D);
  Wrl_Sys.Chunk_Draw();                                 // draw the chunks (function located in the chunk manager class)
  glColor3f(1,1,1);
  if(is_tpv==true){
   glPushMatrix();
    Bon_draw_self(px,py,pz,pa,self_model,self_uv);
   glPopMatrix();
  }

  Ply_Mng->Player_Drawall();
  if(is_tpv==false){
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
   glPushMatrix();
    glColor3f(1,0,1);
    glTranslatef(roundf(loc_X*15+(dx)),roundf(ry),roundf(loc_Y*15+(dz)));
    glutWireCube(1);
    glColor3f(1,1,1);
   glPopMatrix();
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-100, 100, -100, 100, 0.1, 1000);
   //glDisable(GL_DEPTH_TEST);
   glDisable(GL_FOG);
   glDisable(GL_CULL_FACE);
   Bon_draw_obj_l(hand_mdl,hand_uvs,h_vnum,selft_text);
   glEnable(GL_DEPTH_TEST);
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
    //glViewport(0, 0, xs, ys); // GENERAR UN VIEWPORT DE DIBUJO
    glMatrixMode(GL_PROJECTION); // CAMBIAR EL MODO A PROYECCION
    glLoadIdentity(); // CARGAR LOS OBJETOS
    gluPerspective(60, gcd(BON_SCREEN_W,BON_SCREEN_H), 0.1, 3000);
    //gluPerspective(60,1,0.1,3000);
    glEnable(GL_FOG);
    glEnable(GL_CULL_FACE);
    glMatrixMode(GL_MODELVIEW); // CAMBIAR EL MODO OTRA VEZ A MEMORIA
    glLoadIdentity() ; // MOSTRAR LOS OBJETOS
  glPopMatrix();
  //glEnable(GL_LIGHTING);
  }
  
  Bon_2d_Hud();                                         // draw the GUI on the screen

 glFlush();                                             // make sure everything is drawn correctly
 glutSwapBuffers();                                     // change buffer to the new image in screen
}
