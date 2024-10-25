/*
========================================================
=  FUNCTION TO CONVERT THE PROGRAM TO 2D AND DRAW HUD  =
========================================================
*/
void Bon_2d_Hud(){
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
     glVertex2f(640.0, 0.0);
     glTexCoord2d(1,1);
     glVertex2f(640.0, 480.0);
     glTexCoord2d(0,1);
     glVertex2f(0.0,   480.0);
   glEnd();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}
/*
=======================================================
=   FUNCTION TO DRAW ALL OBJECTS ON SCENE AND CHUNKS  =
=======================================================
*/
void BON_GRAPH_FUNCTION(){                              // function of drawing stuff in scene
 gluPerspective(60,1,1,3000);                           // set perspective with a cutwindow of 1000
 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  // clear the buffers on screen for color and depth
 glMatrixMode(GL_MODELVIEW);                            // set the matrix mode to view
 glEnable(GL_CULL_FACE);                                // enable the face culling
 glCullFace(GL_BACK);                                   // for model optimization
 glLoadIdentity();                                      // load all objects in scene
 cx = px+cos((angle*3.14159)/180);                      // calculate where player is looking on x axis
 cy = py-tan((angl2*3.14159)/180);                      // calculate where player is looking on y axis
 cz = pz-sin((angle*3.14159)/180);                      // calculate where player is looking on z axis
 rx = px+cos((angle*3.14159)/180)*zom;                      // calculate where raycast is looking on x axis
 ry = py-tan((angl2*3.14159)/180)*zom;                      // calculate where player is looking on y axis
 rz = pz-sin((angle*3.14159)/180)*zom;                      // calculate where raycast is looking on y axis
 dx = (rx)/15; dz = (rz)/15;
 cox = dx;   coz = dz;
 dx = (dx - cox)*15; dz = (dz - coz)*15;
 if(cx < 0){dx = 15+dx;}
 if(cz < 0){dz = 15+dz;}
 gluLookAt(px, py, pz, cx, cy, cz, 0,1,0);              // move the camera to player position and rotation
 
  BON_SKY();                                            // draw the skybox of the game

  Wrl_Sys.Chunk_Draw();                                 // draw the chunks (function located in the chunk manager class)

  glDisable(GL_TEXTURE_2D);
   glPushMatrix();
    glColor3f(1,0,1);
    glTranslatef(roundf(loc_X*15+(dx)),roundf(ry),roundf(loc_Y*15+(dz)));
    glutWireCube(1);
    glColor3f(1,1,1);
   glPopMatrix();
  glEnable(GL_TEXTURE_2D);

  Bon_2d_Hud();                                         // draw the GUI on the screen

 glFlush();                                             // make sure everything is drawn correctly
 glutSwapBuffers();                                     // change buffer to the new image in screen
}
