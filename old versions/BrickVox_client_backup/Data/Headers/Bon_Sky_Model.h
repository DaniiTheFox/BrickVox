void draw_sky(GLuint _nx,GLuint _ny,GLuint _nz,GLuint _px,GLuint _py,GLuint _pz,int irt){
int s = 1000;
glTranslatef(px,py,pz);
if(irt==1){glRotatef(nube_rot, 0, nube_rot, 1);}
glPushMatrix();
glColor3f(1.0,1.0,1.0);
// LADO TRASERO: lado blanco
glBindTexture(GL_TEXTURE_2D,_pz);
glBegin(GL_QUADS);
glTexCoord2d(0.0,0.0);
glVertex3f( -s, s, s );
glTexCoord2d(0.0,1.0);
glVertex3f( -s, -s, s );
glTexCoord2d(1.0,1.0);
glVertex3f( s, -s, s );
glTexCoord2d(1.0,0.0);
glVertex3f( s, s, s );
glEnd();
// LADO FRONTAL: lado blanco
glBindTexture(GL_TEXTURE_2D,_nz);
glBegin(GL_QUADS);
glTexCoord2d(0.0,0.0);
glVertex3f( s, s, -s );
glTexCoord2d(0.0,1.0);
glVertex3f( s,  -s, -s );
glTexCoord2d(1.0,1.0);
glVertex3f( -s,  -s, -s );
glTexCoord2d(1.0,0.0);
glVertex3f( -s, s, -s );
glEnd();
// LADO DERECHO: lado morado
glBindTexture(GL_TEXTURE_2D,_px);
glBegin(GL_QUADS);
glTexCoord2d(0.0,0.0);
glVertex3f( s, s, s );
glTexCoord2d(0.0,1.0);
glVertex3f( s,  -s,s );
glTexCoord2d(1.0,1.0);
glVertex3f( s,  -s,-s);
glTexCoord2d(1.0,0.0);
glVertex3f( s, s, -s );
glEnd();
// LADO IZQUIERDO: lado verde
glBindTexture(GL_TEXTURE_2D,_nx);
glBegin(GL_QUADS);
glTexCoord2d(0.0,0.0);
glVertex3f( -s, s,  -s);
glTexCoord2d(0.0,1.0);
glVertex3f( -s,  -s,-s );
glTexCoord2d(1.0,1.0);
glVertex3f( -s,  -s, s );
glTexCoord2d(1.0,0.0);
glVertex3f( -s, s, s );
glEnd();
// LADO SUPERIOR: lado azul
glBindTexture(GL_TEXTURE_2D,_py);
glBegin(GL_QUADS);
glTexCoord2d(0.0,0.0);
glVertex3f( -s,  s,  -s );
glTexCoord2d(0.0,1.0);
glVertex3f( -s,  s, s );
glTexCoord2d(1.0,1.0);
glVertex3f(  s,  s, s );
glTexCoord2d(1.0,0.0);
glVertex3f(  s,  s, -s );
glEnd();
// LADO INFERIOR: lado rojo
glBindTexture(GL_TEXTURE_2D,_ny);
glBegin(GL_QUADS);
glTexCoord2d(0.0,0.0);
glVertex3f( -s, -s, s );
glTexCoord2d(0.0,1.0);
glVertex3f( -s, -s,-s );
glTexCoord2d(1.0,1.0);
glVertex3f( s, -s,-s );
glTexCoord2d(1.0,0.0);
glVertex3f( s, -s, s );
glEnd();

glPopMatrix();
}

