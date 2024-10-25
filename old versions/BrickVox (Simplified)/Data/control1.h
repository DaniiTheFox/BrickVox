void control(){
if(up==true){
   pa = angle+180;
   if(pa <= 0){
    pe = 360+(pa);
    pa = pe;
   }
   nx = px+cos(((angle+180)*3.14159)/180);
   nz = pz-sin(((angle+180)*3.14159)/180);
   tmp1 = nx,tmp2 = nz,tmp3 = colider_h;
   player->set_pos_rot(nx,1+1,nz,pa);
 }
 if(down==true){
   pa = angle;
   if(pa <= 0){
    pe = 360+(pa);
    pa = pe;
   }
   nx = px+cos(((angle)*3.14159)/180);
   nz = pz-sin(((angle)*3.14159)/180);
   tmp1 = nx,tmp2 = nz,tmp3 = colider_h;
   player->set_pos_rot(nx,1,nz,pa);
 }
 if(left==true){
   pa = angle+270;
   if(pa <= 0){
    pe = 360+(pa);
    pa = pe;
   }
   nx = px+cos(((angle+270)*3.14159)/180);
   nz = pz-sin(((angle+270)*3.14159)/180);
   tmp1 = nx,tmp2 = nz,tmp3 = colider_h;
    player->set_pos_rot(nx,1,nz,pa);
 }
 if(right==true){
   pa = angle+90;
   if(pa <= 0){
    pe = 360+(pa);
    pa = pe;
   }
   nx = px+cos(((angle+90)*3.14159)/180);
   nz = pz-sin(((angle+90)*3.14159)/180);
   tmp1 = nx,tmp2 = nz,tmp3 = colider_h;
   player->set_pos_rot(nx,1,nz,pa);
 }
 if(down==true&&left==true){
   pa = angle+315;
   if(pa <= 0){
    pe = 360+(pa);
    pa = pe;
   }
   nx = px+cos(((angle+315)*3.14159)/180);
   nz = pz-sin(((angle+315)*3.14159)/180);
   tmp1 = nx,tmp2 = nz,tmp3 = colider_h;
   player->set_pos_rot(nx,1,nz,pa);
 }
 if(down==true&&right==true){
   pa = angle+45;
   if(pa <= 0){
    pe = 360+(pa);
    pa = pe;
   }
   nx = px+cos(((angle+45)*3.14159)/180);
   nz = pz-sin(((angle+45)*3.14159)/180);
   tmp1 = nx,tmp2 = nz,tmp3 = colider_h;
   player->set_pos_rot(nx,1,nz,pa);
 }
 if(up==true&&left==true){
   pa = angle+225;
   if(pa <= 0){
    pe = 360+(pa);
    pa = pe;
   }
   nx = px+cos(((angle+225)*3.14159)/180);
   nz = pz-sin(((angle+225)*3.14159)/180);
   tmp1 = nx,tmp2 = nz,tmp3 = colider_h;
   player->set_pos_rot(nx,1,nz,pa);
 }
 if(up==true&&right==true){
   pa = angle+135;
   if(pa <= 0){
    pe = 360+(pa);
    pa = pe;
   }
   nx = px+cos(((angle+135)*3.14159)/180);
   nz = pz-sin(((angle+135)*3.14159)/180);
   tmp1 = nx,tmp2 = nz,tmp3 = colider_h;
   player->set_pos_rot(nx,1,nz,pa);
 }
 if(down==true&&up==true){
  down=false;
 }
 if(left==true&&right==true){
  left=false;
 }
 px = player->get_pos_rot(1);
 py = player->get_pos_rot(2);
 pz = player->get_pos_rot(3);
 pa = player->get_pos_rot(4);
 cx = px+cos((angle*3.14159)/180)*zoom;
 cz = pz-sin((angle*3.14159)/180)*zoom;
}

void cam(int x, int y){
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
  angle2+=4;
  //glutWarpPointer(240,240);
  old_my = y;
 }else if(y > old_my+10){
  angle2-=4;
  //glutWarpPointer(240,240);
  old_my = y;
 }
}

void keybd(unsigned char key,int x, int y){
//int pe;
 switch(key){
  case 'w':up=true;break;
  case 's':down=true;break;
  case 'd':right=true;break;
  case 'a':left=true;break;
  case ' ':trig=true;break;
 }
}

void ms_r(unsigned char key,int x, int y){
//int pe;
 switch(key){
  case 'w':up=false;break;
  case 's':down=false;break;
  case 'd':right=false;break;
  case 'a':left=false;break;
 }
}

void ms_w(int button, int state, int x, int y){
 if (button == 3){
  if(zoom > 3){
   zoom--;
  }
 }else if(button == 4){
  zoom++;
 }
 //msd = true;
 //_x=x;_y=y;
}

void mixer(int val){
  player->frame_update();
  glutTimerFunc(100, mixer, 0); // RECURSIVIDAD PARA VOLVER A ACTUALIZAR EL TIMER
}

void phy_upd(int val){
  if(trig==1){
  ball->Dynamics_Update();
  }
  glutTimerFunc(dt*1000, phy_upd, 0); // RECURSIVIDAD PARA VOLVER A ACTUALIZAR EL TIMER
}

void create_tex(int bpp, int w, int h, const void *data){
 glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
 gluBuild2DMipmaps(GL_TEXTURE_2D, bpp, w, h, GL_RGBA,  GL_UNSIGNED_BYTE, data);
 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void ld_textures(){
  /*=========================== TEXTURE LOADING =============================*/
  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);
  create_tex(def_tex.bytes_per_pixel,def_tex.width,def_tex.height, def_tex.pixel_data);
  /*=========================================================================*/
  /*=========================== TEXTURE LOADING =============================*/
  glGenTextures(1,&grs);
  glBindTexture(GL_TEXTURE_2D,grs);
  create_tex(floor_tex.bytes_per_pixel,floor_tex.width,floor_tex.height, floor_tex.pixel_data);
  /*=========================================================================*/
  for(int i = 0; i < 6; i++){
  glGenTextures(1,&sky[i]); // ALMACENAR LAS TEXTURAS EN SU RESPECTIVO ESPACIO
  glBindTexture(GL_TEXTURE_2D,sky[i]);
   switch(i){
    case 0:create_tex(nx_c.bytes_per_pixel,nx_c.width,nx_c.height, nx_c.pixel_data);break;
    case 1:create_tex(ny_c.bytes_per_pixel,ny_c.width,ny_c.height, ny_c.pixel_data);break; // FOR EACH FACE OF THE SKY
    case 2:create_tex(nz_c.bytes_per_pixel,nz_c.width,nz_c.height, nz_c.pixel_data);break; // GENERATE DIFFERENT TEXTURES
    case 3:create_tex(px_c.bytes_per_pixel,px_c.width,px_c.height, px_c.pixel_data);break; // FOR MAPPING THE EMPTY SPACE
    case 4:create_tex(py_c.bytes_per_pixel,py_c.width,py_c.height, py_c.pixel_data);break; // CUBEMAP METHOD
    case 5:create_tex(pz_c.bytes_per_pixel,pz_c.width,pz_c.height, pz_c.pixel_data);break; 
   }
  }
  /*=========================================================================*/
}

void bon_draw_floor(int s){
     glBindTexture(GL_TEXTURE_2D,grs);
     glBegin(GL_QUADS);
	glTexCoord2d(0.0,0.0);
	glVertex3f( -s,  0,  -s );
	glTexCoord2d(0.0,s);
	glVertex3f( -s,  0, s );
	glTexCoord2d(s,s);
	glVertex3f(  s,  0, s );
	glTexCoord2d(s,0.0);
	glVertex3f(  s,  0, -s );
    glEnd();
}
