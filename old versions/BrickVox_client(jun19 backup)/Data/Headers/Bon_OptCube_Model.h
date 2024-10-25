/*
===================================================================
= FUNCTION TO DRAW A CUBE THAT'S OPTIMIZED IGNORING COVERED FACES =
===================================================================
*/
void Bon_draw_cube(int map[16][255][16],int _px,int _py,int _pz,int ax, int ay, int az,float s){
       //std::cout<<"data:"<<map[0][0][0]<<std::endl; // just a debug message
       float ltbu = 0.2 +((py/100)*0.5);//+ ((_py+2)/100) * 5;
       float ltbb = 0.2 +((py/100)*0.5);//+ ((_py+2)/100) * 5;
       
       float ltuu = 0.4 +((py/100)*0.5);//+ ((_py+2)/100) * 5;
       float ltub = 0.4 +((py/100)*0.5);//+ ((_py+2)/100) * 5;
       
       float ltxpu = 0.1 +((py/100)*0.5);//+ ((_py+2)/100) * 5;
       float ltxpb = 0.1 +((py/100)*0.5);//+ ((_py-2)/100) * 5;
       
       float ltzpu = 0.2 +((py/100)*0.5);//+ ((_py+2)/100) * 5;
       float ltzpb = 0.2 +((py/100)*0.5);//+ ((_py-2)/100) * 5;
       
       float ltxnu = 0.3 +((py/100)*0.5);//+ ((_py+2)/100) * 5;
       float ltxnb = 0.3 +((py/100)*0.5);//+ ((_py-2)/100) * 5;
       
       float ltznu = 0.4 +((py/100)*0.5);//+ ((_py+2)/100) * 5;
       float ltznb = 0.4 +((py/100)*0.5);//+ ((_py-2)/100) * 5;
       
       glPushMatrix();
       glTranslatef(ax,ay,az);    // move the cube to it's position
	glColor3f(1.0,1.0,1.0);
	if(_py+1<=255){
	if(map[_px][_py+1][_pz] == 0||map[_px][_py+1][_pz] == 6||map[_px][_py+1][_pz] == 5||map[_px][_py+1][_pz] == 4||map[_px][_py+1][_pz] == 7||map[_px][_py+1][_pz] >= base_objects){ // test if the face is not covered
	 glBegin(GL_QUADS);        // begin a cube
  	 glColor3f(ltub,ltuu,ltub);glTexCoord2d(0.0+xoff,0.6666);glVertex3f( s, s,-s);
     	 glColor3f(ltuu,ltuu,ltuu);glTexCoord2d(0.0+xoff,1.0);   glVertex3f(-s, s,-s);     // vertices and texture mapping
     	 glColor3f(ltuu,ltuu,ltuu);glTexCoord2d(1.0+xoff,1.0);   glVertex3f(-s, s, s);
     	 glColor3f(ltub,ltuu,ltub);glTexCoord2d(1.0+xoff,0.6666);glVertex3f( s, s, s);
     	 glEnd();
	}
	}
	glColor3f(0.3,0.3,0.3);
	if(_py-1>=0){
	if(map[_px][_py-1][_pz] == 0||map[_px][_py-1][_pz] == 6||map[_px][_py-1][_pz] == 5||map[_px][_py-1][_pz] == 4||map[_px][_py-1][_pz] == 7||map[_px][_py-1][_pz] >= base_objects){ // test if the face is not covered
	 glBegin(GL_QUADS);        // begin a cube
     	  glColor3f(ltbb,ltbb,ltbb);glTexCoord2d(0.0+xoff,0.0);   glVertex3f( s, -s,  s);
     	  glColor3f(ltbu,ltbu,ltbu);glTexCoord2d(0.0+xoff,0.3333);glVertex3f(-s, -s,  s); // vertices and texture mapping
     	  glColor3f(ltbu,ltbu,ltbu);glTexCoord2d(1.0+xoff,0.3333);glVertex3f(-s, -s, -s);
     	  glColor3f(ltbb,ltbb,ltbb);glTexCoord2d(1.0+xoff,0.0);   glVertex3f( s, -s, -s);
     	 glEnd();
	}
	}
	glColor3f(0.7,0.7,0.7);
	if(_pz+1<15){
        if(map[_px][_py][_pz+1] == 0||_pz+1>=15||map[_px][_py][_pz+1] == 5||map[_px][_py][_pz+1] == 6||map[_px][_py][_pz+1] == 4||map[_px][_py][_pz+1] == 7||map[_px][_py][_pz+1] >= base_objects){ // test if the face is not covered
	 glBegin(GL_QUADS);        // begin a cube
	  glColor3f(ltzpu,ltzpu,ltzpu);glTexCoord2d(0.0+xoff,0.6866);glVertex3f( s,  s, s);
     	  glColor3f(ltzpu,ltzpu,ltzpu);glTexCoord2d(1.0+xoff,0.6866);glVertex3f(-s,  s, s);
     	  glColor3f(ltzpb,ltzpb,ltzpb);glTexCoord2d(1.0+xoff,0.3533);glVertex3f(-s, -s, s); // vertices and texture mapping
     	  glColor3f(ltzpb,ltzpb,ltzpb);glTexCoord2d(0.0+xoff,0.3533);glVertex3f( s, -s, s);
     	 glEnd();
     	 //std::cout<<"for point: "<<_pz<<" generated inside block face"<<std::endl;
        }
        //std::cout<<"for point: "<<_pz<<" generated inside block"<<std::endl;
        }
        if(_pz>=14 && _py <= py+10 && _py >= py-6){
         //if(_py > py-3 && _py < py+3){
         glBegin(GL_QUADS);        // begin a cube
           glColor3f(ltzpu,ltzpu,ltzpu);glTexCoord2d(0.0+xoff,0.6866);glVertex3f( s,  s, s);
     	   glColor3f(ltzpu,ltzpu,ltzpu);glTexCoord2d(1.0+xoff,0.6866);glVertex3f(-s,  s, s);
     	   glColor3f(ltzpb,ltzpb,ltzpb);glTexCoord2d(1.0+xoff,0.3533);glVertex3f(-s, -s, s); // vertices and texture mapping
     	   glColor3f(ltzpb,ltzpb,ltzpb);glTexCoord2d(0.0+xoff,0.3533);glVertex3f( s, -s, s);
     	  glEnd();
         //}
           //std::cout<<"for point: "<<_pz<<" generated outside"<<std::endl;
        }
        if(_pz-1>0){
        glColor3f(0.9,0.9,0.9);
	if(map[_px][_py][_pz-1] == 0||_pz-1<=0||map[_px][_py][_pz-1] == 5||map[_px][_py][_pz-1] == 6||map[_px][_py][_pz-1] == 4||map[_px][_py][_pz-1] == 7||map[_px][_py][_pz-1] >= base_objects){ // test if the face is not covered
	glBegin(GL_QUADS);        // begin a cube
     	 glColor3f(ltznb,ltznb,ltznb);glTexCoord2d(0.0+xoff,0.3533);glVertex3f( s, -s, -s);
     	 glColor3f(ltznb,ltznb,ltznb);glTexCoord2d(1.0+xoff,0.3533);glVertex3f(-s, -s, -s);
     	 glColor3f(ltznu,ltznu,ltznu);glTexCoord2d(1.0+xoff,0.6866);glVertex3f(-s,  s, -s); // vertices and texture mapping
     	 glColor3f(ltznu,ltznu,ltznu);glTexCoord2d(0.0+xoff,0.6866);glVertex3f( s,  s, -s);
     	glEnd();
	}
	}
	if(_pz<=1  && _py <= py+10 && _py >= py-6){
	 glBegin(GL_QUADS);        // begin a cube
           glColor3f(ltznb,ltznb,ltznb);glTexCoord2d(0.0+xoff,0.3533);glVertex3f( s, -s, -s);
     	   glColor3f(ltznb,ltznb,ltznb);glTexCoord2d(1.0+xoff,0.3533);glVertex3f(-s, -s, -s);
     	   glColor3f(ltznu,ltznu,ltznu);glTexCoord2d(1.0+xoff,0.6866);glVertex3f(-s,  s, -s); // vertices and texture mapping
     	   glColor3f(ltznu,ltznu,ltznu);glTexCoord2d(0.0+xoff,0.6866);glVertex3f( s,  s, -s);
     	 glEnd();
         //}
        }
	glColor3f(0.5,0.5,0.5);
	if(_px-1>0){
	if(map[_px-1][_py][_pz] == 0||_px-1<=0||map[_px-1][_py][_pz] == 5||map[_px-1][_py][_pz] == 6||map[_px-1][_py][_pz] == 4||map[_px-1][_py][_pz] == 7||map[_px-1][_py][_pz] >= base_objects){ // test if the face is not covered
	glBegin(GL_QUADS);        // begin a cube
     	 glColor3f(ltxnu,ltxnu,ltxnu);glTexCoord2d(0.0+xoff,0.6866);glVertex3f(-s,  s,  s);
     	 glColor3f(ltxnu,ltxnu,ltxnu);glTexCoord2d(1.0+xoff,0.6866);glVertex3f(-s,  s, -s);
     	 glColor3f(ltxnb,ltxnb,ltxnb);glTexCoord2d(1.0+xoff,0.3533);glVertex3f(-s, -s, -s); // vertices and texture mapping
     	 glColor3f(ltxnb,ltxnb,ltxnb);glTexCoord2d(0.0+xoff,0.3533);glVertex3f(-s, -s,  s);
     	glEnd();
	}
	}
	if(_px<=1  && _py <= py+10 && _py >= py-6){
	glBegin(GL_QUADS);        // begin a cube
           glColor3f(ltxnu,ltxnu,ltxnu);glTexCoord2d(0.0+xoff,0.6866);glVertex3f(-s,  s,  s);
     	   glColor3f(ltxnu,ltxnu,ltxnu);glTexCoord2d(1.0+xoff,0.6866);glVertex3f(-s,  s, -s);
     	   glColor3f(ltxnb,ltxnb,ltxnb);glTexCoord2d(1.0+xoff,0.3533);glVertex3f(-s, -s, -s); // vertices and texture mapping
     	   glColor3f(ltxnb,ltxnb,ltxnb);glTexCoord2d(0.0+xoff,0.3533);glVertex3f(-s, -s,  s);
     	 glEnd();
         //}
        }
	glColor3f(0.3,0.3,0.3);
	if(_px+1<15){
	if(map[_px+1][_py][_pz] == 0||_px+1>=15||map[_px+1][_py][_pz] == 5||map[_px+1][_py][_pz] == 6||map[_px+1][_py][_pz] == 4||map[_px+1][_py][_pz] == 7||map[_px+1][_py][_pz] >= base_objects){ // test if the face is not covered
	glBegin(GL_QUADS);        // begin a cube
     	 glColor3f(ltxpu,ltxpu,ltxpu);glTexCoord2d(0.0+xoff,0.6866);glVertex3f(s,  s, -s);
     	 glColor3f(ltxpu,ltxpu,ltxpu);glTexCoord2d(1.0+xoff,0.6866);glVertex3f(s,  s,  s); // vertices and texture mapping
     	 glColor3f(ltxpb,ltxpb,ltxpb);glTexCoord2d(1.0+xoff,0.3533);glVertex3f(s, -s,  s);
     	 glColor3f(ltxpb,ltxpb,ltxpb);glTexCoord2d(0.0+xoff,0.3533);glVertex3f(s, -s, -s);
     	glEnd();
 	}
 	}
 	if(_px>=14  && _py <= py+10 && _py >= py-6){
         //if(_py > py-3 && _py < py+3){
         glBegin(GL_QUADS);        // begin a cube
           glColor3f(ltxpu,ltxpu,ltxpu);glTexCoord2d(0.0+xoff,0.6866);glVertex3f(s,  s, -s);
     	   glColor3f(ltxpu,ltxpu,ltxpu);glTexCoord2d(1.0+xoff,0.6866);glVertex3f(s,  s,  s); // vertices and texture mapping
     	   glColor3f(ltxpb,ltxpb,ltxpb);glTexCoord2d(1.0+xoff,0.3533);glVertex3f(s, -s,  s);
     	   glColor3f(ltxpb,ltxpb,ltxpb);glTexCoord2d(0.0+xoff,0.3533);glVertex3f(s, -s, -s);
     	 glEnd();
         //}
        }
   //glEnd(); 
   glPopMatrix();                                                 // end of cube
}

void Bon_draw_cross(int map[16][255][16],int _px,int _py,int _pz,int ax, int ay, int az,float s,float air){
     glColor3f(0.7,0.7,0.7);
      glPushMatrix();
       //std::cout<<"data:"<<map[0][0][0]<<std::endl; // just a debug message
       glTranslatef(ax,ay,az);    // move the cube to it's position
      glPushMatrix();
      glRotatef(0,0,0,1);
      glBegin(GL_QUADS);        // begin a cube
     	 glTexCoord2d(0.0+xoff,1.0);glVertex3f(s,   s, -s);
     	 glTexCoord2d(1.0+xoff,1.0);glVertex3f(-s,   s,  s+air); // vertices and texture mapping
     	 glTexCoord2d(1.0+xoff,0.0);glVertex3f(-s,  -s,  s+air);
     	 glTexCoord2d(0.0+xoff,0.0);glVertex3f(s,  -s, -s);
      glEnd();    
      glPopMatrix();
      glPushMatrix(); 
          
      glRotatef(88,0,88,1);
      glBegin(GL_QUADS);        // begin a cube
     	 glTexCoord2d(0.0+xoff,1.0);glVertex3f(s,   s, -s);
     	 glTexCoord2d(1.0+xoff,1.0);glVertex3f(-s,   s,  s+air); // vertices and texture mapping
     	 glTexCoord2d(1.0+xoff,0.0);glVertex3f(-s,  -s,  s+air);
     	 glTexCoord2d(0.0+xoff,0.0);glVertex3f(s,  -s, -s);
      glEnd();     
      glPopMatrix();
      
      glPushMatrix();
      glRotatef(57,0,57,1);
      glBegin(GL_QUADS);        // begin a cube
     	 glTexCoord2d(0.0+xoff,1.0);glVertex3f(s,   s, -s);
     	 glTexCoord2d(1.0+xoff,1.0);glVertex3f(-s,   s,  s+air); // vertices and texture mapping
     	 glTexCoord2d(1.0+xoff,0.0);glVertex3f(-s,  -s,  s+air);
     	 glTexCoord2d(0.0+xoff,0.0);glVertex3f(s,  -s, -s);
      glEnd();     
      glPopMatrix();  
                                              // end of cube
      glPopMatrix();
}
