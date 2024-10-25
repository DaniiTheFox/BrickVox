#include "../broken_texture.c" // include the default texture on a C format
#include "../effect1.c"        // include the eye effect
/*
================================================================================================================================
= JUST A FUNCTION TO LOAD THE CUBE TEXTURES FROM A BITMAP AND IMPLEMENT THEM INSIDE THE PROGRAM TO BE ABLE TO DO TEXTUREPACKS  =
================================================================================================================================
*/
/*GLuint Bon_load_bmp(char *filename, int w, int h){
 //std::cout<<"loading texture"<<std::endl;                                       // debug message
 GLuint tmp_txt;                                                                // texture identifier
 unsigned char *data2;                                                          // where the .bmp data is saved
 //std::cout<<"var created"<<std::endl;
 FILE *file = fopen(filename,"rb");                                             // open the file of the bitmap
 //std::cout<<"loaded file"<<std::endl;
 //rewind(file);
 //std::cout<<"archivo abierto..."<<std::endl;
 if(file == NULL){                                                             // if file couldn't be loaded then
  //std::cout<<"fallo en la lectura..."<<std::endl;
  glGenTextures(1, &tmp_txt);                                                  // generate the error texture
  glBindTexture(GL_TEXTURE_2D, tmp_txt);                                       // that is set by default to avoid segmentation 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);                 // set the texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  gluBuild2DMipmaps(GL_TEXTURE_2D, brk_tex.bytes_per_pixel, brk_tex.width, brk_tex.height, GL_RGBA, GL_UNSIGNED_BYTE, brk_tex.pixel_data);
  return tmp_txt;                                                              // return the default texture
 }
 //std::cout<<"reescalando data..."<<std::endl;
 data2 = (unsigned char *)malloc(w*h*4);                                        // resize the variable to the bitmap size to avoid errors
 //std::cout<<"leyendo archivo..."<<std::endl;
 if(fread(data2, w*h*4, 1, file)){                                                  // read the bitmap data inside the char variable
 fclose(file);                                                                      // file is not needed anymore so it can be closed now
 int index = 0;                                                                     // auxiliary variable for color correction
 //std::cout<<"aplicando la correccion"<<std::endl;
 for(int i = 0; i < w * h; i++){                                               // apply the color correction to the format
  index = i * 4;
  unsigned char R,G,B,A;                                                       // by using RGBA VARIABLES
  A = data2[index];
  R = data2[index+1];                                                          // some get moved to find the correct colors of pixels
  G = data2[index+2];
  B = data2[index+3];                                                           // RED AND BLUE ARE THE ONES THAT ARE INVERTED 

  data2[index] = A;
  data2[index+1] = B;
  data2[index+2] = G;
  data2[index+3] = R;                                                          // so this is needed to fix the colors
 }
 //std::cout<<"correccion aplicada generando..."<<std::endl;
 glGenTextures(1, &tmp_txt);                                                   // generate the current texture based on the bitmap
 glBindTexture(GL_TEXTURE_2D, tmp_txt);
 glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  
 glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);                
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);                 // these are the texture parameters
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 gluBuild2DMipmaps(GL_TEXTURE_2D, 4, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data2);
 free(data2);
 }else{                                                                        // free the unused data
  //load_bmp_texture(filename);
  //std::cout<<"fallo en la lectura..."<<std::endl;
  glGenTextures(1, &tmp_txt);                                                  // if texture couldn't be loaded because it might be corrupted
  glBindTexture(GL_TEXTURE_2D, tmp_txt);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);                 // generate the default texture once again
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  gluBuild2DMipmaps(GL_TEXTURE_2D, brk_tex.bytes_per_pixel, brk_tex.width, brk_tex.height, GL_RGBA, GL_UNSIGNED_BYTE, brk_tex.pixel_data);
 }
 return tmp_txt;
}*/
GLuint Bon_load_bmp(char *filename, int w, int h){
 std::cout<<"loading texture"<<std::endl;                                       // debug message
 GLuint tmp_txt;
  int comp = 4;
  unsigned char* image = stbi_load(filename, &w, &h, &comp, STBI_rgb_alpha);

  if(image == nullptr){
    glGenTextures(1, &tmp_txt);
    glBindTexture(GL_TEXTURE_2D, tmp_txt);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);                
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);                 // these are the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, brk_tex.bytes_per_pixel, brk_tex.width, brk_tex.height, GL_RGBA, GL_UNSIGNED_BYTE, brk_tex.pixel_data);
  }
  glGenTextures(1, &tmp_txt);
  glBindTexture(GL_TEXTURE_2D, tmp_txt);

 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

 stbi_image_free(image);
 return tmp_txt;
}
/*
=================================================
=  FUNCTION TO CREATE A TEXTURE FROM .C FORMAT  =
=================================================
*/
GLuint Bon_create_texture(int bpp, int w, int h, const void *data){
 GLuint tmp_txt;
 glGenTextures(1, &tmp_txt);                                                  // CREATION OF A NEW TEXTURE
 glBindTexture(GL_TEXTURE_2D, tmp_txt);
 glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);                 // generate the default texture once again
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 gluBuild2DMipmaps(GL_TEXTURE_2D, bpp, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
 return tmp_txt;
}
/*
===========================================
=  JUST THE IDLE FUNCTION NOTHING SPECIAL =
===========================================
*/
void BON_IDLE_FUNCTION(){                            // just the function for when player is idle refresh frame
  usleep(33);                                        // sleep 33 miliseconds
  glutPostRedisplay();                               // repost buffer on screen
}
/*
========================================================================
=  THE FUNCTION THAT GENERATES THE FOG AND GIVES THE PROPERTIES TO IT  =
========================================================================
*/
void mcFog(float strt , float end ,float dens){      // fog function to hide that the world is being generated
 GLuint filter;                                      // just a variable
 glClearColor(0.8,0.8,1.0,0.0);                      // set the background color
 glFogi(GL_FOG_MODE , GL_LINEAR);                    // enable the fog mode on linear
 glFogfv(GL_FOG_COLOR , FogColor);                   // set the fog color
 glFogf(GL_FOG_DENSITY , dens );                     // set the fog density
 glHint(GL_FOG_HINT , GL_DONT_CARE);                 // start a hint
 glFogf(GL_FOG_START , strt );                       // set where fog starts 
 glFogf(GL_FOG_END , end);                           // set where fog ends
 //glEnable(GL_FOG);                                 // i disabled the fog here to tell OpenGL which objects are being afected by the fog
}
/*
================================================
= JUST A SKYBOX FUNCTION NOT IMPORTANT IN FACT =
================================================
*/
void BON_SKY(){                                                      // TODO: not important really just a skybox
 glDisable(GL_CULL_FACE);
 glDisable(GL_FOG);
 glPushMatrix();
  if(has_cloud == true){
  draw_sky(SKY_TEX[0],SKY_TEX[1],SKY_TEX[2],SKY_TEX[3],SKY_TEX[4],SKY_TEX[5],1); // create the sky model from module
  nube_rot += 0.1;
  }else{
  draw_sky(NSKY_TEX[0],NSKY_TEX[1],NSKY_TEX[2],NSKY_TEX[3],NSKY_TEX[4],NSKY_TEX[5],0); // create the sky model from module
  }
 glPopMatrix();
 glEnable(GL_FOG);                                                  // enable the fog (this makes the skybox not being affected by fog)
 glEnable(GL_CULL_FACE); 
}
/*
=========================================
=   FUNCTION TO RENDER A STRING IN GAME =
=========================================
*/
void RenderString(float x, float y,const char *str,float r, float g, float b){  
 glColor3f(r, g, b); 
 glEnable(GL_TEXTURE_2D);
 glBindTexture(GL_TEXTURE_2D,BVOX_FONT);
 std::string mesg_tmp = std::string(str);
 for(int i = 0; i < strlen(mesg_tmp.c_str()); i++){
 glBegin(GL_QUADS);
     int ascii_r = mesg_tmp[i];
     double tmp_cal = (((16+(16*(ascii_r-1)))-512));
     double calcx = tmp_cal/1504;
     glTexCoord2d(calcx-0.010638298,0); // 0  0
     glVertex2f(x+(i*10),y-16);
     glTexCoord2d(calcx,0);  // 1 0
     glVertex2f(x+16+(i*10) , y-16);
     glTexCoord2d(calcx,1);  // 1 1
     glVertex2f(x+16+(i*10) , y );
     glTexCoord2d(calcx-0.010638298,1); // 0 1
     glVertex2f(x+(i*10), y);
 glEnd();
 }
 //std::cout<<std::endl;
  glColor3f(1.0f, 1.0f, 1.0f); 
}

int gcd (int a, int b) {
    return (b == 0) ? a : gcd (b, a%b);
}

void resz(int xs, int ys){ // FUNCION DE REESCALAMIENTO
    const float ar = (float) xs / (float) ys; // TAMAÑO DEL PIXEL ( ASPECT RATIO )
    BON_SCREEN_W = xs; // DEFINIR EL TAMAÑO NUEVO DE LA PANTALLA
    BON_SCREEN_H = ys; // DEFINIR EL TAMAÑO NUEVO DE LA PANTALLA
    glViewport(0, 0, xs, ys); // GENERAR UN VIEWPORT DE DIBUJO
    glMatrixMode(GL_PROJECTION); // CAMBIAR EL MODO A PROYECCION
    glLoadIdentity(); // CARGAR LOS OBJETOS
    gluPerspective(60, gcd(xs,ys), 0.1, 3000);
    //gluPerspective(60,1,0.1,3000);
    glMatrixMode(GL_MODELVIEW); // CAMBIAR EL MODO OTRA VEZ A MEMORIA
    glLoadIdentity() ; // MOSTRAR LOS OBJETOS
    current_block = 3;
    block_selecting = 0;
    pointer_inv = 1;
    pointer_blk = 1;
}
/*
==============================================
=  GENERATE A RANDOM INTEGER NUMBER IN RANGE =
==============================================
*/
int get_rnd_num(double a1, double a2){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(a1, a2);
    float rnd = dist(mt);
    unsigned int flt = rnd;
    return flt;
}
