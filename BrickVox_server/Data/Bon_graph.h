#ifdef _WIN32
	#include<windows.h>
	#include<stdlib.h>
	#include<conio.h>
#endif
#include<string.h>
#include<math.h>
 // test if class it's running on windows
 // or running on linux, support for linux OS
 // it's not avaliable yet
#ifdef linux

#endif

int maskInt[100][100]; // mask for interactions with screen (used for objects with id system)
int display[100][100]; // pixel array for the bytemap(bitmap) that will be used 
char strings[100][100]; // number of supported texts on screen 
int colors[100];
int textPtr = 0; // keep a track on which text i added for id system 
char key; // we must check for key press 'e' that's the click so we check which thing we interact
class Bs_cmd_graph{
	private:
		int x , y , tex; // x and y are screen size, while tex it's the texture (character that will be used for pixel)
		#ifdef _WIN32
			HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE); // only on windows.h for color pixels
		#endif
	public:
		int vsx,vsy;
		Bs_cmd_graph(int,int,int); // constructor asking for windowsize and texture
		void Bs_put_Pixel(int,int,int); // add a pixel to bytemap
		void Bs_draw_line(int,int,int,int,int); // draw lines on screen function
		void Bs_draw_poly(int arr[][2],int,int); // draw polygon on screen 
		void Bs_draw_imgA(int arr[16][16],int,int); // draw an image from an 8x8 array
		void Bs_draw_text(int,int,std::string,int);
		void Bs_cmd_draw(); // display bytemap on screen 
		void Bs_cmd_clear(); // clean screen (used for refreshing the screen)
};

Bs_cmd_graph::Bs_cmd_graph(int sx,int sy,int tx){
	x = sx; // change range of drawing window x axis
	y = sy; // change range of drawing window y axis
	vsx = x;
	vsy = y;
	tex = tx; // character that is going to be used for drawing
}

void Bs_cmd_graph::Bs_put_Pixel(int _x,int _y, int _c){
	if(_x >= 0 && _y >= 0 && _x <= 100 && _y <= 100){ // test if pixel to draw is inside canvas
	display[_x][_y] = _c; // add a pixel of a color -1 for null (used for text)
	}
}
/*
void Bs_cmd_graph::Bs_draw_line(int _x1,int _y1,int _x2,int _y2,int _col){
	while(_x1 != _x2 || _y1 != _y2){ // weird method to draw lines while are different points
		if(_x1 < _x2){ // test for the position
			_x1++;     // move the pixel to that position
		}else if(_x1 > _x2){ // test again
			_x1--;	    // move again
		}
		if(_y1 < _y2){ // same for y axis
			_y1++;
		}else if(_y1 > _y2){ // do this until both are on the same point
			_y1--;       // the output of this should be a line from point 1 
		}              // to point 2
		Bs_put_Pixel(_x1,_y1,_col); // and to set the pencil to draw line put pixel
	}
}
*****************************
* OLD LINE TRACING ALGORITHM* [ USE ON YOUR OWN RISK --> IT'S FASTER THAN BRESENHAM BUT NOT AS PRECISE ]
*****************************
*/

void Bs_cmd_graph::Bs_draw_line(int x1, int y1,int x2, int y2, int col){ // using bresenham's algorithm
	int incYi = 0; int incYr = 0; // increment R and I for X and Y
	int incXi = 0; int incXr = 0;
	int dx = (x2-x1);
	int dy = (y2-y1); // difference x difference y
	if(dy>=0){ 
	  incYi = 1;
	}else{
	  dy = dy*-1;
	  incYi = -1;
	}
	
	if(dx>=0){
	  incXi = 1;
	}else{
	  dx = dx*-1;
	  incXi = -1;
	}
	
	if(dx >= dy){
	incYr = 0;
	incXr = incXi;
	}else{
	incXr = 0;
	incYr = incYi;
	int k = dx; dx = dy, dy = k; 
	}
	int x = x1; int y = y1;
	int avr = 2*dy;
	int av = avr-dx;
	int avi = av - dx;
	do{
	  Bs_put_Pixel(x,y,col);
	  //std::cout<<"property: "<<x<<" "<<y<<" "<<av<<std::endl;
	  if(av >= 0){
	   x = x + incXi;
	   y = y + incYi;
	   av = av + avi;
	  }else{
	   x = x + incXr;
	   y = y + incYr;
	   av = av + avr;
	  }
	}while(x != x2 || y != y2);
}

void Bs_cmd_graph::Bs_draw_poly(int arr[][2],int _v,int _c){ // draw polygon function
	for(int i = 0; i < _v ; i++){ // seach through all the vertex array
		int pt = i+1; // next vertex
		if(pt >= _v){pt = 0;} // avoid to be larger than array size
		Bs_draw_line(arr[i][0],arr[i][1],arr[pt][0],arr[pt][1],_c); // draw line from vertex to vertex
	}
}

void Bs_cmd_graph::Bs_draw_imgA(int arr[16][16],int _x,int _y){ // draw image function
	for(int yy = 0 ; yy < 16 ; yy++){ // move through all y axis of image
		for(int xx = 0 ; xx < 16 ; xx++){ // on every y axis point test x axis points
			if(arr[xx][yy] != 0){ // image transparency 0 is no pixel on screen
			if(_x >= 0 && _y >= 0 && _x <= 100 && _y <= 100){ // test if pixel to draw is inside canvas
			display[xx+_x][yy+_y] = arr[xx][yy]; // copy pixel from image array to screen array
			}
			} // ...
		} // ...
	} // ...
} // ...

void Bs_cmd_graph::Bs_draw_text(int _x,int _y, std::string _t, int _c){ //since an id system is required to identify text
	if(strlen(_t.c_str())>0){
	int spot = textPtr+257; // spot generates the id for display to know what text to draw
	_t = _t + "\n";
	display[_x][_y] = spot; // this places text on where it has to be drawn
	for(int i = 0; i < strlen(_t.c_str()) ; i++){ // we have to copy our string into the word array
		strings[i][textPtr] = _t[i]; // copy letter to table zone
		colors[textPtr] = _c;
	}
	for(int i = 1; i <= strlen(_t.c_str())-2 ; i++){ // we have to set -1 on other pixels
		display[_x+i][_y] = -1; // since we are drawing many characters we have to delete
	} // the used characters to avoid weird line drawing on display
	textPtr++; // move the word ptr that's pointing to next text to add
	}
}

void Bs_cmd_graph::Bs_cmd_draw(){
	int ptrr = 0;
	for(int yy = 0; yy < y; yy++){ // draw y axis on screen
		for(int xx = 0; xx < x; xx++){ // draw x axis on screen 
			switch(display[xx][yy]){ // test what to draw
				case 0:
					#ifdef linux
					std::cout<<"\e[49m"; 
					#endif
					std::cout<<" ";
				break; // if blank just draw empty space
				case -1:break; // if -1 dont draw (used for text label)
				default: // if it's not a white space 
					if(display[xx][yy] > 256){ // test if it's a text
						ptrr = display[xx][yy] - 257; // clean id to find text on array
						std::cout<<"\e["<<colors[ptrr]<<"m";
						for(int i = 0; i < 100 ; i++){ // im drawing all string but to avoid this to be slow
							if(strings[i][ptrr] == '\n'){ // if im done with drawing and there are no more characters to draw
								break; // stop drawing text
							} 
							std::cout<<strings[i][ptrr];// draw text
						}
					}else{
						#ifdef _WIN32 
						SetConsoleTextAttribute(hndl,display[xx][yy]); // if im on windows then execute color change
						std::cout<<char(tex); // draw character stablished as texture
				 		#endif
						#ifdef linux
						std::cout<<"\e["<<display[xx][yy]<<"m"<<"#";  // draw character stablished as texture
						#endif
						//std::cout<<"#";
					}
				break; // im done searching
			}
		}
		std::cout<<std::endl; // jump once im done drawing x axis to next y axis
	}
}

void Bs_cmd_graph::Bs_cmd_clear(){ // we define here the action to clear screen for refresh
	#ifdef _WIN32
	system("cls"); // we clean the screen with system cls
	#endif
	
	system("clear");

	for(int i = 0; i < y; i++){ // to avoid the thing to be duplicated while animating
		for(int j = 0; j < x; j++){ // we loop deleting the old screen buffer
			Bs_put_Pixel(j,i,0); // setting pixels to 0 they will be drawn again on a new
			maskInt[j][i] = 0; // we need to refresh buttons on screen
		}     // screen buffer making the animations possible 
	} // that can be useful to avoid static images and to avoid the thing to be
} // freezed or duplicating pixels on a glitch

// these are the classes required to create forms inside the cmd shell 
class Bs_object{ // parent class made for identifier array
	protected: 
		int id, x , y , color; // variables required for all form classes
		bool isActive = false; // we must know if it's active to act
	public:
      Bs_object(int _x,int _y,int _i,int _c);	// constructor of main library
};

Bs_object::Bs_object(int _x,int _y,int _i,int _c){ // constructor
	x = _x; y = _y; id = _i; color = _c; // define all variables required
}

class Bs_cmd_button : public Bs_object{ // button child of bs_object
	private:  
		int obj_size;
	public:
		Bs_cmd_button(int _x,int _y,int _i,int _c); // button constructor
		void onClick(void func()); // if button clicked execute a function 
		void Bs_draw_button(Bs_cmd_graph display,std::string); // draw button on display
	  	void Bs_add_id();
	  	void onClick(int,int,void func());
};

Bs_cmd_button::Bs_cmd_button(int _x,int _y,int _i,int _c) : Bs_object(_x,_y,_i,_c){} // constructor for cmd button

void Bs_cmd_button::Bs_draw_button(Bs_cmd_graph display,std::string _text){ // draw class
	int size = strlen(_text.c_str()); // test string size to make button size
	#ifdef _WIN32
	display.Bs_draw_line(x-1,y,x+size+1,y,color); // button it's text surrounded by a square ########
	#endif
	#ifdef linux
	display.Bs_draw_line(x,y,x+size+2,y,color); // button it's text surrounded by a square ########
	#endif
	display.Bs_draw_text(x+1,y+1,_text,0); // draw text in the middle of button                #button# <- example of button
	display.Bs_put_Pixel(x,y+1,color); // put 2 pixels just for detail                       ########
	display.Bs_put_Pixel(x+size+1,y+1,color); // put other pixel
	#ifdef _WIN32
	display.Bs_draw_line(x-1,y+2,x+size+1,y+2,color); // draw below line
	#endif
	#ifdef linux
	display.Bs_draw_line(x,y+2,x+size+2,y+2,color); // button it's text surrounded by a square ########
	#endif
	obj_size = size+2;
}

void Bs_cmd_button::Bs_add_id(){ // add the id for mask map 
	for(int yy = 0; yy < 3; yy++){ // loop for y axis on mask array
		for(int xx = 0; xx < obj_size; xx++){ // loop for x axis on array
			maskInt[x+xx][y+yy] = id; // draw id on mask map
		} // . . . this function is required
	}	 // . . . to add interaction into the map
}  //. . . . . .  if it's not defined you wont be able to use object

void Bs_cmd_button::onClick(int _x,int _y,void func()){ // every class must have onClick function
	int idd = maskInt[_x][_y];                          // NOT DEFINED ON BS_OBJ BECAUSE EACH OBJECT ACTS DIFFERENT
	switch(key){ // we use a switch to test
		case 'e': // e pressed
			if(idd == id){ // test what is the button touching
				func();  // if button touched button then execute this function defined by the user
			}
		break;
		default:break; // if click key wasnt pressed then ignore this object until next mouse touch
	}
}

class Bs_Textbox: public Bs_object{
	std::string text;
	private:
		int size;
	public:
		Bs_Textbox(int,int,int,int,std::string,int);
		void Bs_draw_textbox(Bs_cmd_graph);
		void Bs_add_id();
		void onClick(int,int);	
};

Bs_Textbox::Bs_Textbox(int _x,int _y, int _id, int _s, std::string _txt, int _c) : Bs_object(_x,_y,_id,_c){
	size = _s; text = _txt;
}

void Bs_Textbox::Bs_draw_textbox(Bs_cmd_graph display){
	display.Bs_draw_line(x-1,y,x+size+1,y,color);
	display.Bs_draw_line(x-1,y+2,x+size+1,y+2,color);
	display.Bs_put_Pixel(x,y+1,color);
	display.Bs_put_Pixel(x+size+1,y+1,color);
	if(text == ""){
		display.Bs_draw_text(x+1,y+1," ",0);
	}else{
		display.Bs_draw_text(x+1,y+1,text,0);
	}
}

void Bs_Textbox::Bs_add_id(){
	for(int yy = 0; yy < 3 ; yy++){
		for(int xx = 0; xx < x+size; xx++){
			maskInt[x+xx][y+yy] = id;
		}
	}
}

void Bs_Textbox::onClick(int _x,int _y){
	int idd = maskInt[_x][_y];
	switch(key){
		case 'e':
			if(idd == id){
			std::getline(std::cin,text);
			size = strlen(text.c_str());
			}
		break;
		default:break;
	}
}

// this is the mouse to interact with form classes inside the project
class Bs_mouse_pointer{ // define the object class
	private: // color is private since no object can interact with color
		int color; // define color variable
	public: // while the x and y variables are public
		int x,y; // because we need access on mouse position for object interaction detection 
		Bs_mouse_pointer(int,int,int); // this is the contructor asking for starting x and y and color
		void Bs_mouse_controller(); // this moves the pointer through all the window
		void Bs_mouse_draw(Bs_cmd_graph display); // this draws the pointer on the screen
}; // now that we have the constructors the actual functions:

Bs_mouse_pointer::Bs_mouse_pointer(int _x,int _y,int _c){ // constructor for muse pointer
	x = _x; // we define the parameter _x as the mouse x on screen
	y = _y; // we define the parameter _y to be the y for our mouse
	color = _c; // we define the mouse color this is for whatever you want
} // end constructor function

void Bs_mouse_pointer::Bs_mouse_controller(){ // this is the mouse controller
	switch(key){ // test which key was pressed
		case 'i':if((y-1) >= 0){y--;}break; // if W was pressed move pointer up
		case 'k':y++;break; // if S was pressed we move pointer down
		case 'j':if((x-1) >= 0){x--;}break; // if it's inside the window not touching border and A is pressed move left
		case 'l':x++;break; // if D was pressed we move to the right
		default:break; // none of these keys where pressed we ignore this function used for interactions wit E
	} // if keyboard detects E then we act on the object that we are selecting 
} // else if other key was pressed and it's not W,A,S,D,E then just ignore actions

void Bs_mouse_pointer::Bs_mouse_draw(Bs_cmd_graph display){ // we pass the display object that will draw pointer on screen
	display.Bs_put_Pixel(x,y,color); // we pass the parameters x and y to set location of our pointer and color 
} // with this the mouse should be drawn on screen and with this we should be able to select objects to interact with

// this is the test function to add on the mouse
#ifdef _WIN32
void alertMsg(){ // this is a test function that will be showing a message box
	MessageBox(NULL,"button clicked","",MB_OK); // show message that the button was clicked
} // this is just to test the interaction with buttons take it as a default function
#endif

/*
This part comes for the simple 3d engine made for this library (it might improve)
*/

void draw_wall(Bs_cmd_graph display, float px, float py, float pa, float vx1, float vy1, float vx2, float vy2, int col){
float x1 = 0; float y1a = 0; 
float y1b = 0; float x2 = 0;
float y2a = 0; float y2b = 0;
float tx1 = 0; float ty1 = 0;
float tx2 = 0; float ty2 = 0;
float tz1 = 0; float tz2 = 0;
/*[MOVER EL MAPA ALREDEDOR DEL JUGADOR]*/
 	 tx1 = vx1 - px; ty1 = vy1 - py;
 	 tx2 = vx2 - px; ty2 = vy2 - py;
 	
 	 /*[TRASLADAR EL MAPA ALREDEDOR DEL JUGADOR]*/
 	 tz1 = tx1 * cos((3.14159*pa)/180) + ty1 * sin((3.14159*pa)/180);
 	 tz2 = tx2 * cos((3.14159*pa)/180) + ty2 * sin((3.14159*pa)/180);
 	 tx1 = tx1 * sin((3.14159*pa)/180) - ty1 * cos((3.14159*pa)/180);
 	 tx2 = tx2 * sin((3.14159*pa)/180) - ty2 * cos((3.14159*pa)/180);
 	 /*[__________________________________]*/
 	 //screen->Bs_draw_line(15 - tx1,15 - tz1,15 - tx2,15 - tz2,33);
 	 //screen->Bs_draw_line(35,11,35, 8, 31);
 	 //screen->Bs_put_Pixel(35,11,32);
 	//std::cout<<"linedata: "<<tx1<<" "<<tz1<<" "<<tx2<<" "<<tz2<<std::endl;
 	/*PERSPECTIVE INSIDE PROGRAM*/
 	 
 	  if(tz1 > 0 || tz2 > 0){
 	  if(tz1 > -5 && tz2 > -5){
 	  if(tz1 < 1){
 	   tz1=1;
 	  }
 	  if(tz2 < 1){
 	   tz2=1;
 	  }
 	   if(tz1 == 0){
 	    x1 = (tx1+0.0001*-1) * 16 / tz1+0.0001; y1a = -32 / tz1+0.0001; y1b = 32 / tz1+0.0001;
 	   }else{
 	    x1 = (tx1*-1) * 16 / tz1; y1a = -32 / tz1; y1b = 32 / tz1;
 	   }  
 	 
 	   if(tz2 == 0){
 	    x2 = (tx2+0.0001*-1) * 16 / tz2+0.0001; y2a = -32 / tz2+0.0001; y2b = 32 / tz2+0.0001;
 	   }else{
 	    x2 = (tx2*-1) * 16 / tz2; y2a = -32 / tz2; y2b = 32 / tz2;
 	   }
 	   if(tz1 < 24 && tz2 < 24 && tz1 > -5 && tz2 > -5){
 	    display.Bs_draw_line(roundf(35+x1),roundf(11+y1a),roundf(35+x2),roundf(11+y2a),col);
 	    display.Bs_draw_line(roundf(35+x1),roundf(11+y1b),roundf(35+x2),roundf(11+y2b),col);
 	    display.Bs_draw_line(roundf(35+x1),roundf(11+y1a),roundf(35+x1),roundf(11+y1b),col);
 	    display.Bs_draw_line(roundf(35+x2),roundf(11+y2a),roundf(35+x2),roundf(11+y2b),col);
 	   }
 	  }
 	 }
 	/*[PERSPECTIVE WALL ALGORITHM]*/
}

void display_direction(Bs_cmd_graph display,int x, int y,int pa){
 std::string orient = "East";
 if(pa > 45 && pa < 135){
   orient = "North";
 }
 if(pa > 135 && pa < 225){
   orient = "West";
 }
 if(pa > 225 && pa < 315){
   orient = "South";
 }
 display.Bs_draw_text(x,y,"Facing: "+orient,0);
}

/*
 Engine for vertices inside my other engine thisone DESIGNED FOR REAL 3D OBJECTS IN ROOM
*/

struct vertex3d_type{
	int lx,ly,lz,lt;
	int wx,wy,wz,wt;
	int sx,sy;
};

struct line_type{int start, end;};

struct shapes3d_type{
	int color;
	int vertN;
	int lineN;
	vertex3d_type *points;
	line_type *line;
};

float matrix[4][4];

void Bs_set_projection(shapes3d_type *shape, int dist){
 for(int v = 0; v < (*shape).vertN; v++){
  vertex3d_type *vptr = &(*shape).points[v];
  vptr->sx = dist*vptr->wx/vptr->wz;
  vptr->sy = dist*vptr->wy/vptr->wz;
 }
}

void Bs_initialize_mtrx(){
 //initialize master transformation
 matrix[0][0] = 1; matrix[0][1] = 0; matrix[0][2] = 0; matrix[0][3] = 0;
 matrix[1][0] = 0; matrix[1][1] = 1; matrix[1][2] = 0; matrix[1][3] = 0;
 matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = 1; matrix[2][3] = 0;
 matrix[3][0] = 0; matrix[3][1] = 0; matrix[3][2] = 0; matrix[3][3] = 1;
}

void Bs_multiply_matrices(float resultado[4][4], float matrix1[4][4], float matrix2[4][4]){
	for(int y = 0; y < 4; y++){
	   for(int x = 0; x < 4; x++){
	      resultado[y][x] = 0;
	      for(int i = 0; i < 4; i++){
	      resultado[y][x] += matrix1[y][i] * matrix2[i][x]; 
	      }
	   }
	}
}

void Bs_copy_into_matrix(float matrix1[4][4],float matrix2[4][4]){
	for(int y = 0; y < 4; y++){
		for(int x = 0; x < 4; x++){
			matrix2[y][x] = matrix1[y][x];
		}	
	}
}

void Bs_scalef_shp(float scale){
 float mat[4][4];float smat[4][4];
 smat[0][0] = scale; smat[0][1] = 0; smat[0][2] = 0; smat[0][3] = 0;
 smat[1][0] = 0; smat[1][1] = scale; smat[1][2] = 0; smat[1][3] = 0;
 smat[2][0] = 0; smat[2][1] = 0; smat[2][2] = scale; smat[2][3] = 0;
 smat[3][0] = 0; smat[3][1] = 0; smat[3][2] = 0; smat[3][3] = 1;
 Bs_multiply_matrices(mat,smat,matrix);
 Bs_copy_into_matrix(mat,matrix);
}
void Bs_translatef_shp(int xt,int yt,int zt){
 float mat[4][4];float tmat[4][4];
 tmat[0][0] = 1; tmat[0][1] = 0; tmat[0][2] = 0; tmat[0][3] = 0;
 tmat[1][0] = 0; tmat[1][1] = 1; tmat[1][2] = 0; tmat[1][3] = 0;
 tmat[2][0] = 0; tmat[2][1] = 0; tmat[2][2] = 1; tmat[2][3] = 0;
 tmat[3][0] = xt;tmat[3][1] = yt;tmat[3][2] = zt;tmat[3][3] = 1;
 Bs_multiply_matrices(mat,matrix,tmat);
 Bs_copy_into_matrix(mat,matrix);
}
void Bs_rotatef_shp(float ax,float ay,float az){
 float xmat[4][4]; float ymat[4][4]; float zmat[4][4];
 float mat1[4][4]; float mat2[4][4];
 // x rotation
 xmat[0][0] = 1; xmat[0][1] = 0; xmat[0][2] = 0; xmat[0][3] = 0;
 xmat[1][0] = 0; xmat[1][1] = cos(ax);xmat[1][2] = sin(ax);xmat[1][3] = 0;
 xmat[2][0] = 0; xmat[2][1] = -sin(ax);xmat[2][2] = cos(ax);xmat[2][3] = 0;
 xmat[3][0] = 0; xmat[3][1] = 0; xmat[3][2] = 0; xmat[3][3] = 1;
 Bs_multiply_matrices(mat1,xmat,matrix);
 // y rotation
 ymat[0][0] = cos(ay); ymat[0][1] = 0; ymat[0][2] = -sin(ay); ymat[0][3] = 0;
 ymat[1][0] =       0; ymat[1][1] = 1; ymat[1][2] =        0; ymat[1][3] = 0;
 ymat[2][0] = sin(ay); ymat[2][1] = 0; ymat[2][2] =  cos(ay); ymat[2][3] = 0;
 ymat[3][0] =       0; ymat[3][1] = 0; ymat[3][2] =        0; ymat[3][3] = 1;
 Bs_multiply_matrices(mat2,ymat,mat1);
 // z rotation
 zmat[0][0] = cos(az); zmat[0][1] = sin(az); zmat[0][2] = 0; zmat[0][3] = 0;
 zmat[1][0] =-sin(az); zmat[1][1] = cos(az); zmat[1][2] = 0; zmat[1][3] = 0;
 zmat[2][0] = 0; zmat[2][1] = 0; zmat[2][2] = 1; zmat[2][3] = 0;
 zmat[3][0] = 0; zmat[3][1] = 0; zmat[3][2] = 0; zmat[3][3] = 1;
 Bs_multiply_matrices(matrix,zmat,mat2);
}

void Bs_transform_shp(shapes3d_type *shape){
 for(int v = 0; v < (*shape).vertN ; v++){
  vertex3d_type *vptr = &(*shape).points[v];
  vptr->wx = vptr->lx*matrix[0][0]+vptr->ly*matrix[1][0]+vptr->lz*matrix[2][0]+matrix[3][0];
  vptr->wy = vptr->lx*matrix[0][1]+vptr->ly*matrix[1][1]+vptr->lz*matrix[2][1]+matrix[3][1];
  vptr->wz = vptr->lx*matrix[0][2]+vptr->ly*matrix[1][2]+vptr->lz*matrix[2][2]+matrix[3][2];
 }
}

void Bs_draw_3dshp(shapes3d_type shape,Bs_cmd_graph display,int offsetX, int offsetY){
 for(int i = 0; i < shape.lineN; i++){
  display.Bs_draw_line(shape.points[shape.line[i].start].sx+offsetX,
	   shape.points[shape.line[i].start].sy+offsetY,
	   shape.points[shape.line[i].end].sx+offsetX,
	   shape.points[shape.line[i].end].sy+offsetY,
	   shape.color);
 }
}


void Bs_draw_3dpoly(shapes3d_type fig,Bs_cmd_graph display,int offsetX, int offsetY){
 int p2 = 0;
 for(int i = 0 ; i < fig.vertN ; i++){
  p2=i+1;
  if(p2>=fig.vertN){p2=0;}
  display.Bs_draw_line(fig.points[i].sx+offsetX,
	   fig.points[i].sy+offsetY,
	   fig.points[p2].sx+offsetX,
	   fig.points[p2].sy+offsetY,
	   fig.color);
 }
}
