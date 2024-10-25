#include<GL/glut.h>
#include<iostream>
#include<unistd.h>
#include<math.h>

GLuint texture,grs;
GLuint sky[6];

#include "Data/Models/Object.h"
#include "Data/Models/skymodel.h"
#include "Data/Bon_physics_manager.h"

#include "Data/Textures/default.c"
#include "Data/Textures/floor.c"

#include "Data/Textures/skybox/nx.c"
#include "Data/Textures/skybox/ny.c"
#include "Data/Textures/skybox/nz.c"

#include "Data/Textures/skybox/px.c"
#include "Data/Textures/skybox/py.c"
#include "Data/Textures/skybox/pz.c"
/*
===========================================
=   OLD VARIABLES JUST IGNORE THIS STUFF  =
===========================================
*/
int pe;
int tmp1,tmp2,tmp3; bool isJmp = false; int gravity = -1;
int colider_h = 1, tx, ty;
int old_x = 0, old_y = 0,angle = 180,angle2 = -25,zoom = 6;
float px = 0,py = 6,pz = 0,nx = 0,nz = 0,pa = 0,jump = 6;
int iax = 0, iaz = 0;float cx, cz;
bool msd = false;
int old_mx,old_my;
bool up=false,down=false,left=false,right=false;
/*------------------------------------------------*/

void display();
void standf();
void glIni();
bool trig = false;
Bonii *player = new Bonii("bonnie",5,1,5,0,true);
Physics_ball1 *ball = new Physics_ball1(0,6,0,1);

#include "Data/control1.h"

float light_diffuse[] = {70.0, 70.0, 70.0, 70.0}; 
float light_position[] = {-100.0, 0.0, 1.0, 0.0};
static float amb[] =  {0.6, 0.6, 0.6, 0.0};
static float dif[] =  {1.0, 1.0, 1.0, 0.0};

int main(int argc, char **argv){
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
 glutInitWindowSize(480,480);
 glutCreateWindow("BrickVox Simplified");
 glClearDepth(1.0f);
 glDepthFunc(GL_LEQUAL);
 glIni();
 glutIgnoreKeyRepeat(1);
 glutDisplayFunc(display);
 glutKeyboardFunc(keybd);
 glutMotionFunc(cam);
 glutMouseFunc(ms_w);
 glutKeyboardUpFunc(ms_r);
 glutIdleFunc(standf);
 glutTimerFunc(25, mixer, 0);
 glutTimerFunc(dt*1000, phy_upd, 0);
 glutMainLoop();
 return 0;
}


void standf(){usleep(33);glutPostRedisplay();}

void glIni(){
 glClearColor(0.5,0.5,0.7,0.0);
 glEnable(GL_DEPTH_TEST);
 glEnable(GL_TEXTURE_2D);
 glEnable(GL_BLEND);
 glEnable(GL_LIGHTING);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(60, 1,1,2000);
 ld_textures();
 
 glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,  1);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
  glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
  //glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
  glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
}

void display(){
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 control();
 float ars[3] = {0,0,0};
 glLightfv(GL_LIGHT0, GL_POSITION, ars);
 gluLookAt(cx,py-sin((angle2*3.14159)/180)*zoom,cz, px,py,pz, 0,1,0);

 bon_draw_floor(500);
 ball->Draw_Sphere();
 glDisable(GL_LIGHTING);
 player->draw_model(texture);
 draw_sky(sky[0],sky[1],sky[2], sky[3],sky[4],sky[5]);
 glEnable(GL_LIGHTING);

 glFlush();
 glutSwapBuffers();
}
  
