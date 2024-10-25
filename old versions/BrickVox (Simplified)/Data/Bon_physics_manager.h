/*
*============================================================
        _                                    _            
       | |                                  (_)           
  _ __ | |__  _   ___  __    ___ _ __   __ _ _ _ __   ___ 
 | '_ \| '_ \| | | \ \/ /   / _ \ '_ \ / _` | | '_ \ / _ \
 | |_) | | | | |_| |>  <   |  __/ | | | (_| | | | | |  __/
 | .__/|_| |_|\__, /_/\_\  \___|_| |_|\__, |_|_| |_|\___|
 | |           __/ |                   __/ |             
 |_|          |___/                   |___/   
                    BY: boniikwdz
*============================================================
*/
#define PHY_PI 3.14159
#define GRAVITY -9.81
/*
================================
* GLOBAL CONSTANTS FOR PHYSICS *
================================
*/
float dt = 0.02;   // delta time - time step
float rho = 0.5;  // density of the air
float C_d = 0.47; // object dragging

class Physics_ball1{
 private:
 public:
  float bpx,bpy,bpz;	           // bon physics position 
  float force_x,force_y,force_z;  // forces that affect the object's position 
  float vvx,vvy,vvz;              // velocity of the object on N axis 
  float fax,fay,faz;              // another force for the weight
  float mass = 0.2;               // the mass of the object that's being moved
  float rads = 0.5;               // radious of the object to get collision
  float bonc = -0.5;              // how much does the object bounce
  float A;                        // calculation of the scale
  float av_min = 10000;           // minimum value of bounce
  float dir_x = 0, dir_z = 0;     // direction of the vector
  Physics_ball1(float _X,float _Y,float _Z,float _rads);// constructor of the object
  void Draw_Sphere();             // function to draw the object
  void Dynamics_Update();         // function to update 
};

Physics_ball1::Physics_ball1(float _X,float _Y,float _Z,float _rads){
  rads = _rads;
  bpx=_X,bpy=_Y,bpz=_Z;
  //A = PHY_PI * rads * rads / 10000;
}

void Physics_ball1::Draw_Sphere(){
 glDisable(GL_TEXTURE_2D);
 glPushMatrix();
  glTranslatef(bpx,bpy,bpz);
  glutSolidSphere(rads, 16, 32);
 glPopMatrix();
 glEnable(GL_TEXTURE_2D);
}

void Physics_ball1::Dynamics_Update(){
   /*
   =======================================
   = DYNAMICS PART OF THE PHYSICS ENGINE =
   =======================================
   */
   force_x += mass * dir_x;
   force_x += -1 * 0.5 * rho * C_d * A * vvx * vvx;//m180mw
 
   force_y += mass * GRAVITY;
   force_y += -1 * 0.5 * rho * C_d * A * vvy * vvy;//m180mw
   
   force_z += mass * dir_z;
   force_z += -1 * 0.5 * rho * C_d * A * vvz * vvz;//m180mw
   
   float dvy, dvx, dvz;
   float new_ay,new_ax,new_az;
   float avg_ax,avg_ay,avg_az;
   
   dvx = vvx * dt + (0.5 * fax * dt * dt);
   bpx += dvx;
   new_ax = force_x / mass;
   avg_ax = 0.5 * (new_ax + fax);
   vvx += avg_ax * dt;
   
   dvy = vvy * dt + (0.5 * fay * dt * dt);
   bpy += dvy;
   new_ay = force_y / mass;
   avg_ay = 0.5 * (new_ay + fay);
   vvy += avg_ay * dt;
   
   dvz = vvz * dt + (0.5 * faz * dt * dt);
   bpz += dvz;
   new_az = force_z / mass;
   avg_az = 0.5 * (new_az + faz);
   vvz += avg_az * dt;
   /*
   ====================
   =  COLISION 1 PART =
   ====================
   */
   if (bpy - rads < 0 && vvy < 0){
        vvy *= bonc;
        if(vvy<9){vvy=0;force_y=0;}
        std::cout<<vvx<<std::endl;
        bpy = 0 + rads;                        
   }
   if((bpx+rads > 500 && vvx > 0)||(bpx-rads < -500 && vvx < 0)){
       dir_x*=-1;
       vvx*=-1;
   }
}


