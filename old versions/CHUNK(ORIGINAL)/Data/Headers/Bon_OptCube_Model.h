/*
===================================================================
= FUNCTION TO DRAW A CUBE THAT'S OPTIMIZED IGNORING COVERED FACES =
===================================================================
*/
void Bon_draw_cube(int map[16][255][16],int _px,int _py,int _pz,int ax, int ay, int az,float s){
       //std::cout<<"data:"<<map[0][0][0]<<std::endl; // just a debug message
       glTranslatef(ax,ay,az);    // move the cube to it's position
	glBegin(GL_QUADS);        // begin a cube
	if((_px)<16  && (_px)>0){ // test if location is inside the chunk data
	if((_py)<255 && (_py)>0){ // test if location is inside chunk data
	if((_pz)<16  && (_pz)>0){ // test if location is inside chunk data
	glColor3f(6.0,6.0,6.0);
	if(map[_px][_py+1][_pz] == 0){ // test if the face is not covered
  	 glTexCoord2d(0.0+xoff,0.6666);glVertex3f( s, s,-s);
     	 glTexCoord2d(0.0+xoff,1.0);glVertex3f(-s, s,-s);     // vertices and texture mapping
     	 glTexCoord2d(1.0+xoff,1.0);glVertex3f(-s, s, s);
     	 glTexCoord2d(1.0+xoff,0.6666);glVertex3f( s, s, s);
	}
	glColor3f(8.0,8.0,8.0);
	if(map[_px][_py-1][_pz] == 0){ // test if the face is not covered
     	 glTexCoord2d(0.0+xoff,0.0);glVertex3f( s, -s,  s);
     	 glTexCoord2d(0.0+xoff,0.3333);glVertex3f(-s, -s,  s); // vertices and texture mapping
     	 glTexCoord2d(1.0+xoff,0.3333);glVertex3f(-s, -s, -s);
     	 glTexCoord2d(1.0+xoff,0.0);glVertex3f( s, -s, -s);
	}
	glColor3f(6.0,7.0,6.0);
        if(map[_px][_py][_pz+1] == 0||_pz+1>=15){ // test if the face is not covered
	 glTexCoord2d(0.0+xoff,0.6866);glVertex3f( s,  s, s);
     	 glTexCoord2d(1.0+xoff,0.6866);glVertex3f(-s,  s, s);
     	 glTexCoord2d(1.0+xoff,0.3533);glVertex3f(-s, -s, s); // vertices and texture mapping
     	 glTexCoord2d(0.0+xoff,0.3533);glVertex3f( s, -s, s);
        }
        glColor3f(8.0,9.0,8.0);
	if(map[_px][_py][_pz-1] == 0||_pz-1<=0){ // test if the face is not covered
     	 glTexCoord2d(0.0+xoff,0.3533);glVertex3f( s, -s, -s);
     	 glTexCoord2d(1.0+xoff,0.3533);glVertex3f(-s, -s, -s);
     	 glTexCoord2d(1.0+xoff,0.6866);glVertex3f(-s,  s, -s); // vertices and texture mapping
     	 glTexCoord2d(0.0+xoff,0.6866);glVertex3f( s,  s, -s);
	}
	glColor3f(6.0,7.0,6.0);
	if(map[_px-1][_py][_pz] == 0||_px-1<=0){ // test if the face is not covered
     	 glTexCoord2d(0.0+xoff,0.6866);glVertex3f(-s,  s,  s);
     	 glTexCoord2d(1.0+xoff,0.6866);glVertex3f(-s,  s, -s);
     	 glTexCoord2d(1.0+xoff,0.3533);glVertex3f(-s, -s, -s); // vertices and texture mapping
     	 glTexCoord2d(0.0+xoff,0.3533);glVertex3f(-s, -s,  s);
	}
	glColor3f(3.0,4.0,3.0);
	if(map[_px+1][_py][_pz] == 0||_px+1>=15){ // test if the face is not covered
     	 glTexCoord2d(0.0+xoff,0.6866);glVertex3f(s,  s, -s);
     	 glTexCoord2d(1.0+xoff,0.6866);glVertex3f(s,  s,  s); // vertices and texture mapping
     	 glTexCoord2d(1.0+xoff,0.3533);glVertex3f(s, -s,  s);
     	 glTexCoord2d(0.0+xoff,0.3533);glVertex3f(s, -s, -s);
 	}
        }}}
   glEnd();                                                  // end of cube
}
