void Bon_rlfc_water(int _wx, int _wy, int _wz, GLuint _env_map, GLuint _texture){
 float s = 0.5;
 glPushMatrix();
  glTranslatef(_wx,_wy,_wz);
  //glColor4f(1,1,1,0.5);
  float wof3 = 0;
  if(wof>=0.998){wof=0;}else{wof+=0.002;}
  if(maxh>0){if(wof2<maxh){wof2+=0.0005;}else{maxh*=-1;}}else{if(wof2>maxh){wof2-=0.0005;}else{maxh*=-1;}}
  glBindTexture(GL_TEXTURE_2D, _texture);
  float wmd = _wz % 2;
  if(wmd != 0){
   incw = false;
   wof3 = wof2;
  }else{
   incw = true;
   wof3 = wof2*-1;
  }
  glBegin(GL_QUADS);
     glTexCoord2d(0.0+wof,0.0+wof); glVertex3f( s, s-0.31+(wof3),-s);
 	  glTexCoord2d(0.0+wof,1.0+wof); glVertex3f(-s, s-0.31+(wof3),-s);     // vertices and texture mapping
     glTexCoord2d(1.0+wof,1.0+wof); glVertex3f(-s, s-0.31-(wof3), s);
     glTexCoord2d(1.0+wof,0.0+wof); glVertex3f( s, s-0.31-(wof3), s);
  glEnd();
  glBindTexture(GL_TEXTURE_2D, _env_map);
  glBegin(GL_QUADS);
     glTexCoord2d( ((    _wx*0.0666)+0.0666)+(dx/10),    ((_wz*0.0666))+(dz/10)); glVertex3f( s, s-0.3+(wof3),-s);
 	  glTexCoord2d( (((_wx-1)*0.0666)+0.0666)+(dx/10),    ((_wz*0.0666))+(dz/10)); glVertex3f(-s, s-0.3+(wof3),-s);     // vertices and texture mapping
     glTexCoord2d( (((_wx-1)*0.0666)+0.0666)+(dx/10),(((_wz+1)*0.0666))+(dz/10)); glVertex3f(-s, s-0.3-(wof3), s);
     glTexCoord2d( ((    _wx*0.0666)+0.0666)+(dx/10),(((_wz+1)*0.0666))+(dz/10)); glVertex3f( s, s-0.3-(wof3), s);
  glEnd(); 
 glPopMatrix();
}
