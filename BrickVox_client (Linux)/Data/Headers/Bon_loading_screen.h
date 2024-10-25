void draw_load_screen(){
  glClearColor(0,0,0,0);
  glDisable(GL_ALPHA_TEST);
   glMatrixMode(GL_PROJECTION);
    glPushMatrix();
     glLoadIdentity();
     glOrtho(0.0, BON_SCREEN_W, BON_SCREEN_H, 0.0, -1.0, 10.0);
     glMatrixMode(GL_MODELVIEW);
     glDisable(GL_CULL_FACE);
     glClear(GL_DEPTH_BUFFER_BIT);
      glPushMatrix();
       glBindTexture(GL_TEXTURE_2D, BON_BS_LOGO);
       glBegin(GL_QUADS);
        glTexCoord2d(0,0);
        glVertex2f(0, 0);
        glTexCoord2d(1,0);
        glVertex2f(BON_SCREEN_W, 0);
        glTexCoord2d(1,1);
        glVertex2f(BON_SCREEN_W, BON_SCREEN_H);
        glTexCoord2d(0,1);
        glVertex2f(0, BON_SCREEN_H);
       glEnd();
      glPopMatrix();
    glPopMatrix();
  glFlush();
  glutSwapBuffers();
}