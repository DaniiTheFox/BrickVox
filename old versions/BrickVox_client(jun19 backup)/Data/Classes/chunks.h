/*
========================================================================
= CHUNK GENERATION LIBRARY ON C++ --> TO GENERATE INFINITE WORLDS!!!!  =
========================================================================
*/
// THE WORLD TYPES INSIDE THE PROYECT
#define   FLAT_WORLD 0 // world mode #1 for flat worlds
#define FLAT_N_TREES 1 // world mode #2 for flar worlds with trees
#define MOUNTAIN_WRL 2 // world mode #3 that uses perlin
int upr_sec_x[3] = {0,1,2}; //   0          1        2
int mid_sec_x[3] = {3,4,5}; // 3 4 5   -- 4 5 3 -- 5 3 4
int lwr_sec_x[3] = {6,7,8}; // array of sectors with their locations used for rebuild and organize the world
bool isDebug = false;       // just a debug variable -- can be ignored
// the node that will be useful to save all chunks
/*
================================================================================================================
=  TODO: STRUCTURE OF THE CHUNK NODE (THIS CONTAINS ALL CHUNK INFO AND IT'S CONTROLLED BY THE CHUNK_GEN CLASS) =
================================================================================================================
*/
struct rchunk{
 int zone_X;                   // The location in X in greater map
 int zone_Y;                   // The location in Y in greater map 
 int chunk_data[16][255][16];  // The cubes located inside the chunk
 int state = 0;                // Numbers between 1-9 to mark it's position
 rchunk *parent;                // pinter which is used to destroy the old chunks
};
/*
======================================================================
=    THIS IS THE CHUNK MANAGER CLASS WHERE ALL THE SYSTEM IS LOCATED =
======================================================================
*/
class Chunk_gen{               // object that contains tree and chunk data
 public:                       // to be able to modify the system from any part of the program
  int seed = 50;               // seed for world generation 50 for default
  int w_type = 0;              // 0-Flat  1-Flat_n_trees 2-Mountain_n_trees
   rchunk *sector[9];           // pointers for each sector (to identify the locations)
   rchunk *aux;
   rchunk *aux3;
   // 0 1 2
   // 3 4 5 -- where 4 it's center chunk -- if player travels to other chunk that chunk will become center chunk
   // 6 7 8  
  // functions
  Chunk_gen(int _s,int w_type);                       // object constructor that generates the first 9 chunks for world and sets up everything
  void Chunk_Create(int p, int zx, int zy);           // function to start generating each chunk (here goes world generation)
  void Chunk_Draw();                                  // function to move through the tree and start generating the terrain on renderer
  void Chunk_Correction();                            // function to fix the broken chunks and avoid holes
  void Chunk_Update();                                // function to generate new chunks as players moves
  int  Chunk_Get_Info(int,int,float,float,float);     // function that will return if a block was found in a position
  void Chunk_Edit_Add(int,int,float,float,float,int); // function that will set a block on a specified location
};
rchunk *aux4q;                    // pointer to avoid flashing on query, must be destroyed at the end of execution
/*
======================================================
= CLASS CONSTRUCTOR -- WHERE SETUP OF CHUNKS IS MADE =
======================================================
*/
Chunk_gen::Chunk_gen(int _s, int w){                 // class constructor that sets up all the world generation
 //std::cout<<"generating chunks"<<std::endl;          // just a debug message to find segmentation parts
 seed = _s;                                          // seed for perlin noise or tree generation
 w = w_type;                                         // world mode
 int positions_x[9] = {-1,0,1,-1,0,1,-1, 0, 1};      // locations of the first 9 chunks
 int positions_y[9] = { 1,1,1, 0,0,0,-1,-1,-1};      // locations of the first 9 chunks
 for(int i = 0; i < 9; i++){                         // loop through all pointers
  Chunk_Create( i, positions_x[i], positions_y[i]);  // to generate all main chunks at first and avoid segmentations
 }
 aux = new rchunk();                                  // create an auxiliary variable for saving the current chunk to read
}
/*
=============================================================================================
= TODO: IMPORTANT: Function to draw all the chunks in screen -- needed to render the world  =
=============================================================================================
*/
void Chunk_gen::Chunk_Draw(){                        // function to start drawing the chunks
 //std::cout<<"drawing chunks"<<std::endl;
 //std::cout<<"chunk with data: "<<aux->zone_X<<std::endl;
 for(int i = 0; i < 9; i++){                         // loop through all pointers in order to draw each chunk
  aux = sector[i];
  glPushMatrix();
  //std::cout<<"testing chunks"<<std::endl;
   for(int z = 0; z < 16;   z++){                    // loop to read Z axis data of the chunk 
    for(int y = (py-10); y < (py+25); y++){           // loop to read Y axis data adjusted to player's positions to optimize generation
     for(int x = 0; x < 16; x++){                    // loop to read X axis data of the chunk
      //if(py-10 < 0){py=0;}
      switch(aux->chunk_data[x][y][z]){              // test the found information about the chunk
       case 0:break;
       case 1:                                       // reading the objects
        //std::cout<<"found 1"<<std::endl;
        glPushMatrix();                              // used to move individually an object
        glBindTexture(GL_TEXTURE_2D, GRASS_TEXTURE); // set the grass texture
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;
       case 2:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, STONE_TEXTURE); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;
       case 3:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, COBBLESTONE_TEXTURE); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;
       case 4:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually RAW_WOOD_TEXTURE
        btri4.draw_model(RAW_WOOD_TEXTURE,x+(aux->zone_X*15),y,z+(aux->zone_Y*15)); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                  // adjusted to chunk location on greater scale
       break;
       case 7:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually RAW_WOOD_TEXTURE
        btri3.draw_model(RAW_WOOD_TEXTURE,x+(aux->zone_X*15),y,z+(aux->zone_Y*15)); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;
       case 8:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, MCOBBLESTONE_TEXTURE); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;
       case 6:break;
       case 5:break;
       case 9:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, PLK_WOOD_TEXTURE); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;

       case 10:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, BOOK_SHELF_TEX); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;

       case 11:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, DMNS_DOOR_TEX); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;

       case 12:break;

       case 13:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, STONE_DOOR_TEX); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;

       case 14:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, BRICKWALL_TEX1); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;

       case 15:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, SAND_TEXTURE_1); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;

       case 16:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, B_COLOR_TEX_RED); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;

       case 17:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, B_COLOR_TEX_ORG); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;

       case 18:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, B_COLOR_TEX_YLW); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;

       case 19:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, B_COLOR_TEX_GRN); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;

       case 20:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, B_COLOR_TEX_BLE); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;

       case 21:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, B_COLOR_TEX_PNK); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;

       case 22:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, B_COLOR_TEX_WHT); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;

       case 23:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, B_COLOR_TEX_BLK); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;

      case 24:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, DIRT_TEXTURE); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;

       
       case 28:break;
       /*============REPLACE REPLACE REPLACE REPLACE REPLACE ==========*/
       default:
        if((aux->chunk_data[x][y][z]) <= array_limit){
         for(int i = 0; i < obj_num; i++){
           if(object_array[i].bs_id == (aux->chunk_data[x][y][z])){
            object_array[i].DrawFlatLookAt(x+(aux->zone_X*15),y,z+(aux->zone_Y*15),px,py,pz);
           }
         }
        }
       break;
      }
     }
    }
   }
 for(int z = 0; z < 16;   z++){                    // loop to read Z axis data of the chunk 
  for(int y = (py-5); y < (py+10); y++){           // loop to read Y axis data adjusted to player's positions to optimize generation
   for(int x = 0; x < 16; x++){                    // loop to read X axis data of the chunk
      //if(py-10 < 0){py=0;}
      switch(aux->chunk_data[x][y][z]){              // test the found information about the chunk
       case 5:
        //std::cout<<"found 2"<<std::endl;
        glDisable(GL_CULL_FACE);
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, LEAVES_TEXTURE); // set stone texture to block
        Bon_draw_cross(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5,0); // calculate and draw optimized cube with it's position
        glPopMatrix(); 
        glEnable(GL_CULL_FACE);                                                                   // adjusted to chunk location on greater scale
       break;
       case 6:
        //std::cout<<"found 2"<<std::endl;
        glDisable(GL_CULL_FACE);                                // enable the face culling
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, PLANT_TEXTURE); // set stone texture to block
        Bon_draw_cross(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5,gmov); // calculate and draw optimized cube with it's position
        glPopMatrix(); 
        glEnable(GL_CULL_FACE);                                                                    // adjusted to chunk location on greater scale
       break;
       case 12:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, GLASS_TEXTURE); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();  
       break;
       case 28: // TODO: INFO
        glPushMatrix();
          Bon_rlfc_water(x+(aux->zone_X*15),y,z+(aux->zone_Y*15),WATER_ENVMAPR,WATER_TEXTURE);
        glPopMatrix();
       break;
      }
     }
    }
   }
   for(int x = 0; x < 15; x++){
    for(int z = 0; z < 15; z++){
     glPushMatrix();
      Bon_rlfc_water(x+(aux->zone_X*15),sea_level,z+(aux->zone_Y*15),WATER_ENVMAPR,WATER_TEXTURE);
     glPopMatrix();
    }
   }
   if(isDebug == true){ // just a tiny boolean for debbugging but avoid losing all the previous information of debug
    //std::cout<<"For Node: "<<i<<" locations: x- "<<aux->zone_X<<" y- "<<aux->zone_Y<<std::endl; // debug message with location of generated chunks
   }
   if(grch == false){if(gmov <= 0.5){gmov+=0.001;}else{grch=true;}}else{if(gmov >= 0){gmov-=0.001;}else{grch=false;}} 
   glPopMatrix();
 }
 if(isDebug == true){   // reset the debugging message to it's original value
  isDebug = false;      // avoid looping the debug messages
 }
}
/*
====================================================================================
= TODO: IMPORTANT FUNCTION TO CREATE A NEW CHUNK NODE AND PUSH IT TO TREE ON CLASS =
====================================================================================
*/
int tmp_x,tmp_y,tmp_z,tmp_b;
void Chunk_gen::Chunk_Create( int p, int zx, int zy ){ // function to create new node of chunk with data
 //std::cout<<"creating chunks"<<std::endl;
 bon_push_into_cmd("<BrickVox Client>> Chunk Created");
 rchunk *newchunk = new rchunk();                        // create the new chunk node (starts empty)
 //std::cout<<"chunk created..."<<std::endl;
 newchunk->zone_X = zx;                                // assign a zone for this chunk on Z axis
 newchunk->zone_Y = zy;                                // assign a zone for this chunk on Y axis
 //std::cout<<"zone assigned"<<std::endl;
 if(w_type == 0){                                      // world generation testing mode
 //std::cout<<"type tested..."<<std::endl;
 bon_push_into_cmd("<BrickVox Client>> adding world data...");
 
 
 if(is_flatw == true){
  bon_push_into_cmd("<BrickVox Client>> Chunktype = flat");
  for(int z = 0; z < 16; z++){                          // this is the world generation
   for(int y = 0; y < 50; y++){                         // as this depends on modes or anything
    for(int x = 0; x < 16; x++){                        // since it's mode 0 generates a flat terrain
     //std::cout<<"generating world data"<<std::endl;     // this part is ment to be the loading chunk data
     if(y < 49){                                        // inside the chunk which means MySQL things go here if world is downloaded
      newchunk->chunk_data[x][y][z] = 2;                // this sets information inside the main array
     }else{
       newchunk->chunk_data[x][y][z] = 1;                // of the chunk data    
     }
    }                                                   // TODO: IMPORTANT: you can use structures and perlin noise in here
   }
  }
  if(has_grass == true){
   bon_push_into_cmd("<BrickVox Client>> Chunk with grass");
   for(int z = 0; z < 16; z++){                          // this is the grass generation
    for(int x = 0; x < 16; x++){                        // since it's mode 0 generates a flat terrain
     newchunk->chunk_data[x][50][z] = 6;               
    }
   }
  }
  }else{
    for(int x = 0; x < 16; x++){
      for(int z = 0; z < 16; z++){
        height_map1 = 50+ValueNoise_2D((float)(zx+x), (float)(zy+z))*100;
        std::string deb = "PX "+std::to_string(loc_Y)+" PZ "+std::to_string(loc_X)+" point = "+std::to_string(height_map1);
        bon_push_into_cmd(deb.c_str());
        for(int y = 0; y < height_map1; y++){
          if(y < height_map1-1){                                  // inside the chunk which means MySQL things go here if world is downloaded
      		newchunk->chunk_data[x][y][z] = 2;                // this sets information inside the main array
     	  }else{
      		newchunk->chunk_data[x][y][z] = 1;                // of the chunk data
      		newchunk->chunk_data[x][y+1][z] = 6;                   
     	  }
        } 
      }
    }
  }
   
  if(has_trees == true && is_flatw==true){
  bon_push_into_cmd("<BrickVox Client>> Flaw world has trees....");
  //std::cout<<"adding debug tree"<<std::endl;            // Just a debugging message
  for(int x = 0; x < 5; x++){                           // the X size of leaves
   for(int y = 0; y < 4; y++){                          // the Y size of leaves
    for(int z = 0; z < 5; z++){                         // the Z size of leaves
     if(newchunk->chunk_data[x][y][z] > 0){             // IF the block is empty
      newchunk->chunk_data[6+x][49+p+y][6+z] = 5;       // add a leaves block on space
     }
    }                                                   // close the leave generation routine
   }
  }
  newchunk->chunk_data[6+0][49+p+3][6+0] = 0;           // these are the upper corners of tree leaves
  newchunk->chunk_data[6+0][49+p+3][6+4] = 0;           // these are creating an empty block
  newchunk->chunk_data[6+4][49+p+3][6+4] = 0;           // on the corners of the tree to give
  newchunk->chunk_data[6+4][49+p+3][6+0] = 0;           // it a roundy effect! and remove cubic tree
  
  newchunk->chunk_data[6+0][49+p+0][6+0] = 0;           // the same happens in the bottom leaves
  newchunk->chunk_data[6+0][49+p+0][6+4] = 0;           // for each corner i add an empty block
  newchunk->chunk_data[6+4][49+p+0][6+4] = 0;           // to remove the blocky style and give
  newchunk->chunk_data[6+4][49+p+0][6+0] = 0;           // life to the trees
  for(int f = 50; f < (50+p); f++){
   if(f != 50){
    newchunk->chunk_data[8][f][8] = 4;                   // this is just a random stick on chunks ignore it
   }else{
    newchunk->chunk_data[8][f][8] = 7;                   // this is just a random stick on chunks ignore it
   }
  }
  }

  //std::cout<<"CHUNK "<<p<<" WAS GENERATED IN LOCATION:"<<" x:"<<newchunk->zone_X<<" y:"<<newchunk->zone_Y<<std::endl;  // debugging trash
 }

 //bon_push_into_cmd("<BrickVox GC>> removing old Chunk");
 //std::cout<<"setting state"<<std::endl;                 // debug message to identify the state of chunk
 newchunk->state = p;                                   // set state of chunk
 //std::cout<<"pushing chunk"<<std::endl;                 // mention when is the chunk being pushed to list
 if(sector[p] != NULL){                                 // if the pointer it's not empty
 rchunk *tmp = new rchunk();                             // create a temporal chunk
  //std::cout<<"destroying the chunk"<<std::endl; 
  aux = sector[p];                                      // assign the actual chunk to delete to the global aux
  aux->parent = tmp;                                    // set the chunk to delete parent look at the temporal chunk that will be deleted
  sector[p] = NULL;                                     // make the main pointer that manages the chunks look at null
  delete tmp;                                           // delete temporal, this will delete the old chunk to avoid memory leaks
 }
 //std::cout<<"chunk was generated and is now pushing...."<<std::endl;
 newchunk->parent = NULL;                               // the parent always looks at null unless it's being deleted
 sector[p] = newchunk;                                  // push the actual chunk to the tree giving the pointer of the class
 //bon_push_into_cmd("<BrickVox GC>> old Chunk has been removed");
 //bon_push_into_cmd("<BrickVox Client>> new chunk linked to render");
 //std::cout<<"new chunk has been created uff"<<std::endl;
}
/*
==========================================================================
= TODO: function to correct the holes in the chunk generator system      =
==========================================================================
*/
void Chunk_gen::Chunk_Correction(){                                              // function to fix the positions of corrupted chunks
 //std::cout<<"correction apply...."<<std::endl;
 //bon_push_into_cmd("<BrickVox Client>> Making Chunk Correction....");
 int locs_X[3] = {-1,0,1};                                                       // correct locations in x
 int locs_Y[3] = {1,0,-1};                                                       // correct locations in y
 for(int i = 0; i < 3; i++ ){                                                    // loop on x axis
  aux = sector[upr_sec_x[i]];                                                    // upper sector fix
   if(aux->zone_X != (loc_X + locs_X[i])||aux->zone_Y != (loc_Y + locs_Y[0])){   // if it finds a missplaced chunk inside generation
    Chunk_Create(upr_sec_x[i],(loc_X + locs_X[i]),(loc_Y + locs_Y[0]));          // create a new chunk on the pointer with correct location
   }
  aux = sector[mid_sec_x[i]];                                                    // middle sector fix
   if(aux->zone_X != (loc_X + locs_X[i])||aux->zone_Y != (loc_Y + locs_Y[1])){   // if it finds a missplaced chunk inside generation
    Chunk_Create(mid_sec_x[i],(loc_X + locs_X[i]),(loc_Y + locs_Y[1]));          // create a new chunk on the pointer with correct location
   }
  aux = sector[lwr_sec_x[i]];                                                    // middle sector fix
   if(aux->zone_X != (loc_X + locs_X[i])||aux->zone_Y != (loc_Y + locs_Y[2])){   // if it finds a missplaced chunk inside generation
    Chunk_Create(lwr_sec_x[i],(loc_X + locs_X[i]),(loc_Y + locs_Y[2]));          // create a new chunk on the pointer with correct location
   }
 }
 //std::cout<<"correction applied"<<std::endl;
 /*for(int i = 0; i < 9; i++){
  aux = sector[i];
  std::cout<<"using MySQL server"<<std::endl;
  std::string rq = "SELECT * FROM Modifications WHERE Chunk_X = "+std::to_string(aux->zone_X)+" AND Chunk_Y = "+std::to_string(aux->zone_Y)+";";
  std::cout<<rq<<std::endl;
  mysql_query(connect, rq.c_str());
  res_set = mysql_store_result(connect);
  std::cout<<"loading stuff"<<std::endl;
  while(( row = mysql_fetch_row(res_set) ) != NULL){
   tmp_x = atoi(row[3]);
   tmp_y = atoi(row[4]);
   tmp_z = atoi(row[5]);
   tmp_b = atoi(row[6]);
   aux->chunk_data[tmp_x][tmp_y][tmp_z] = tmp_b;
  }
 }*/
}
/*
=====================================================================================
= TODO: IMPORTANT: FUNCTION TO UPDATE THE CHUNKS AND GENERATE NEW AS PLAYER WALKS   =
=====================================================================================
*/
int aux1,aux2; int auy1[3], auy2[3];    // auxiliary variables for moving the array and generate new chunks and understand next generation
void Chunk_gen::Chunk_Update(){         // FUNCTION TO GENERATE THE CHUNKS AS PLAYER MOVES ON UPDATES
 bool splitted = false;
 if(px > (opx+8)){          // if player moved on positive x axis
  opx += 15;                                       // update current player position on X of the greater scale
  loc_X++;                                         // update the location of chunk
  Chunk_Create(upr_sec_x[0],loc_X+1,loc_Y+1);      // create 3 new chunks on direction
  Chunk_Create(mid_sec_x[0],loc_X+1,loc_Y);        // these are represening their locations 
  Chunk_Create(lwr_sec_x[0],loc_X+1,loc_Y-1);      // by the use of locs of X and Y
  //std::cout<<"new chunk is generated x pos: "<<std::endl; // debug message
  //std::cout<<"location of new chunks: "<<loc_X+1<<" "<<loc_X+1<<" "<<loc_X+1<<std::endl; // just debug trash
  //std::cout<<"location of new chunks: "<<loc_Y-1<<" "<<loc_Y<<" "<<loc_Y+1<<std::endl;   // ignore these messages of debug
  aux1 = upr_sec_x[2];aux2 = upr_sec_x[1];         // save one of the sectors into auxiliary variables
  upr_sec_x[2] = upr_sec_x[0];                     // move the current variables of x and switch locations 
  upr_sec_x[1] = aux1;                             // set middle current var
  upr_sec_x[0] = aux2;                             // set lower
                                                   // this process is repeated
  aux1 = mid_sec_x[2];aux2 = mid_sec_x[1];         // for each numer on array of sectors
  mid_sec_x[2] = mid_sec_x[0];                     // to assign next chunk location that will be drawn
  mid_sec_x[1] = aux1;                             // this array tells the pointers where to look at
  mid_sec_x[0] = aux2;                             // and how to organize them
  
  aux1 = lwr_sec_x[2];aux2 = lwr_sec_x[1];         // repeat the process of splitting the numbers on lower section of sectors
  lwr_sec_x[2] = lwr_sec_x[0];                     // the splitting it's done to keep the order of the loaded chunks
  lwr_sec_x[1] = aux1;                             // and help to understand which are the next pointers to be used on the generation
  lwr_sec_x[0] = aux2;                             // it's necessary to avoid location corruption
  splitted = true;                                 // just a variable with debug purposes
 }
 if(px < (opx-8)){                                 // repeat the same process for the negative X axis
  opx -= 15;                                       // again move the position on the greater scale
  loc_X--;                                         // move the position on chunk greater scale
  Chunk_Create(upr_sec_x[2],loc_X-1,loc_Y+1);      // generate the new chunks inside the world
  Chunk_Create(mid_sec_x[2],loc_X-1,loc_Y);        // generate the new chunks inside the world
  Chunk_Create(lwr_sec_x[2],loc_X-1,loc_Y-1);      // generate the new chunks inside the world
  //std::cout<<"new chunk is generated x neg: "<<std::endl;                                 // just debug trash messages
  //std::cout<<"location of new chunks: "<<loc_X-1<<" "<<loc_X-1<<" "<<loc_X-1<<std::endl;  // you can ignore these
  //std::cout<<"location of new chunks: "<<loc_Y-1<<" "<<loc_Y<<" "<<loc_Y+1<<std::endl;    // they show greater scale location
  aux1 = upr_sec_x[0];aux2 = upr_sec_x[1];         // save one of the sectors into auxiliary variables
  upr_sec_x[0] = upr_sec_x[2];                     // move the current variables of x and switch locations 
  upr_sec_x[1] = aux1;                             // set middle current var
  upr_sec_x[2] = aux2;                             // set lower
  
  aux1 = mid_sec_x[0];aux2 = mid_sec_x[1];         // the previous moving of the array of pointers is repeated
  mid_sec_x[0] = mid_sec_x[2];                     // in order to understand chich is the next pointer to be moved inside the world
  mid_sec_x[1] = aux1;                             // this array that is being moved is important 
  mid_sec_x[2] = aux2;                             // because it contains the pointers and their actual location
  
  aux1 = lwr_sec_x[0];aux2 = lwr_sec_x[1];         // which helps on the order to understand which are the next chunks being moved
  lwr_sec_x[0] = lwr_sec_x[2];                     // which order they follow
  lwr_sec_x[1] = aux1;                             // how are they organized
  lwr_sec_x[2] = aux2;                             // etc. thanks to this array being moved
  splitted = true;                                 // terrain is able to be generated on it's respective order
 }                                                 // splitted: is just a debug variable
 if(pz > (opy+8)){
  opy += 15;                                              // update the Y position on greater scale that tells when is a new chunk generated
  loc_Y++;                                                // update greater scale of chunk
  Chunk_Create(lwr_sec_x[0],loc_X+1,loc_Y+1);             // create upper chunk
  Chunk_Create(lwr_sec_x[1],loc_X,  loc_Y+1);             // create middle chunk
  Chunk_Create(lwr_sec_x[2],loc_X-1,loc_Y+1);             // create lower chunk
  //std::cout<<"new chunk is generated y pos: "<<std::endl; // debug comment
  //std::cout<<"location of new chunks: "<<loc_X-1<<" "<<loc_X<<" "<<loc_X-1<<std::endl;   // just debug trash comments
  //std::cout<<"location of new chunks: "<<loc_Y+1<<" "<<loc_Y+1<<" "<<loc_Y+1<<std::endl; // that show current location
  auy1[0] = upr_sec_x[0]; auy1[1] = upr_sec_x[1]; auy1[2] = upr_sec_x[2];                // upper section saved on auxiliary 
  auy2[0] = mid_sec_x[0]; auy2[1] = mid_sec_x[1]; auy2[2] = mid_sec_x[2];                // middle section saved on auxiliary
  upr_sec_x[0] = lwr_sec_x[0]; upr_sec_x[1] = lwr_sec_x[1]; upr_sec_x[2] = lwr_sec_x[2]; // replace upper with lower sections
  mid_sec_x[0] = auy1[0]; mid_sec_x[1] = auy1[1]; mid_sec_x[2] = auy1[2];                // replace middle section with upper section
  lwr_sec_x[0] = auy2[0]; lwr_sec_x[1] = auy2[1]; lwr_sec_x[2] = auy2[2];                // replace lower section with middle section
  splitted = true;                                                                       // a debug variable
 }
 if(pz < (opy-8)){
  opy -= 15;                                             // update the Y position on greater scale that tells when is a new chunk generated
  loc_Y--;                                               // update greater scale of chunk
  Chunk_Create(upr_sec_x[0],loc_X+1,loc_Y-1);                                           // create upper chunk
  Chunk_Create(upr_sec_x[1],loc_X,  loc_Y-1);                                           // create middle chunk
  Chunk_Create(upr_sec_x[2],loc_X-1,loc_Y-1);                                           // create lower chunk
  //std::cout<<"new chunk is generated y neg: "<<std::endl;                               // debug comment
  //std::cout<<"location of new chunks: "<<loc_X-1<<" "<<loc_X<<" "<<loc_X+1<<std::endl;  // debug messages (just trash)
  //std::cout<<"location of new chunks: "<<loc_Y-1<<" "<<loc_Y-1<<" "<<loc_Y-1<<std::endl;// ignore the debug messages
  auy1[0] = lwr_sec_x[0]; auy1[1] = lwr_sec_x[1]; auy1[2] = lwr_sec_x[2];  // upper section saved on auxiliary 
  auy2[0] = upr_sec_x[0]; auy2[1] = upr_sec_x[1]; auy2[2] = upr_sec_x[2];  // middle section saved on auxiliary
  upr_sec_x[0] = mid_sec_x[0]; upr_sec_x[1] = mid_sec_x[1]; upr_sec_x[2] = mid_sec_x[2]; // replace upper with lower sections
  mid_sec_x[0] = auy1[0]; mid_sec_x[1] = auy1[1]; mid_sec_x[2] = auy1[2];  // replace middle section with upper section
  lwr_sec_x[0] = auy2[0]; lwr_sec_x[1] = auy2[1]; lwr_sec_x[2] = auy2[2];  // replace lower section with middle section
  splitted = true;                                                         // debug variable not used yet
 } 
 if(splitted == true){                                                     // here is where split is used if a chunk was generated
  //std::cout<<"Terrain generated is: ["<<upr_sec_x[0]<<" "<<upr_sec_x[1]<<" "<<upr_sec_x[2]<<"]"<<std::endl;  // then it will show the data
  //std::cout<<"                      ["<<mid_sec_x[0]<<" "<<mid_sec_x[1]<<" "<<mid_sec_x[2]<<"]"<<std::endl;  // of the pointer array
  //std::cout<<"                      ["<<lwr_sec_x[0]<<" "<<lwr_sec_x[1]<<" "<<lwr_sec_x[2]<<"]"<<std::endl;  // to make sure splitting it's
  //std::cout<<"Location of player and chunks is: LocX: "<<loc_X<<" LocY: "<<loc_Y<<std::endl;                 // correct and also
  //std::cout<<"Location of player current chunk: opx: "<<opx<<" opy:"<<opy<<std::endl;                        // look at greater scales
  splitted = false;                                                                                          // reset the debug variable
 }
 Chunk_Correction(); // TODO: IMPORTANT: to correct world construction and avoid corruption this function is called after generation of chunks
}
/*
===========================================================================
= TODO: IMPORTANT: function to get data on a specific position of the map =
=========================================================================== 
*/
int Chunk_gen::Chunk_Get_Info(int lx,int ly,float rx,float ry,float rz){ // function to get information from a chunk
 int found = 0;                                                          // define what i found
 for(int i = 0; i < 9; i++){                                             // for each chunk
  aux3 = sector[i];                                                       // open the sector to read
  if(aux->zone_X == lx && aux->zone_Y == ly){                            // locate if it is what im looking for
   int read_x = roundf(rx);                                              // get the position in X
   int read_y = roundf(ry);                                              // get the position in Y
   int read_z = roundf(rz);                                              // get the position in Z
   found = aux->chunk_data[read_x][read_y][read_z];                      // tell found what i've found 
   break;                                                                // break the process of looking for data
  }                                                                      // close the if statement
 }                                                                       // end of search
 return found;                                                           // return what i found on the chunk data
}
/*
===============================================================================
= TODO: IMPORTANT: function to set a block on a specified location of the map =
===============================================================================
*/
std::string old_req = "";
void Chunk_gen::Chunk_Edit_Add(int lx,int ly,float rx,float ry,float rz,int block){ // this is the function that adds an specific block to the game data
lock_query = true;                                                                  // lock querys to avoid crashes on mysql
 for(int i = 0; i < 9; i++){                                                        // for each cube
  aux = sector[i];                                                                  // set aux to the chunk i want to read
  if(aux->zone_X == lx && aux->zone_Y == ly){                                       // if it's the same chunk im in
   int read_x = roundf(rx);                                                         // round the X axis
   int read_y = roundf(ry);                                                         // round Y axis
   int read_z = roundf(rz);                                                         // round the Z axis
   std::string req = "INSERT INTO Modifications (Chunk_X, Chunk_Y, Modif_X, Modif_Y, Modif_Z, Block_E,Session) VALUES ("+std::to_string(lx)+","+std::to_string(ly)+","+std::to_string(read_x)+","+std::to_string(read_y)+","+std::to_string(read_z)+","+std::to_string(block)+","+std::to_string(current_sesion)+");";
   if((strcmp(req.c_str(),old_req.c_str()))!=0 ){
    for(int c = 0; c < 100; c++){                      // this sector of the game pushes into a stack
     if(stack_build_cb[c] == 0){                       // what the player is building so when the connection thread
      stack_build_cb[c] = 1;                           // is called the game detects what player made
      stack_build[c] = req;                            // that helps other players to see what you made
      break;                                           // break to make the game faster
     }                                                 // simple method to tell MySQL player Added or Removed a Block
    }
    aux->chunk_data[read_x][read_y][read_z] = block;    // add the change to the current chunk
    break;                                              // break statement to avoid trashy searching
   }
  }
 }
 old_req = req;
 lock_query = false;                                    // allow query's again
}

// CREATE THE OBJECT
Chunk_gen Wrl_Sys(0,0);  // create the object that manages the chunks inside the program (done here because of organization purposes)


/*
======================================================================
= THIS IS A FUNCTION FOR THE CUSTOM OBJECTS NOT INCLUDED IN CHUNKS   =
=____________________________________________________________________=
=  FUNCTION THAT EXECUTES THE BBAL BONI BRICKVOX ASSEMBLER LANGUAGE  =
======================================================================
*/
void Flat_v::runln(std::string script_cmd){ // command to execute a line of code inside program
 //std::cout<<"\e[1;33m RUNNING LINE: ["<<script_cmd<<"] OF CODE\e[0m;"<<std::endl; // just a debug message
 bool fnd_var = false;                                  // boolean to define that variable was found
 std::string decomposed[25];                            // the array that works to decompose the command into mneumonic and parameters
 int var_pos = 0;                                       // just an auxiliary variable for var search
 int zptr = 0;                                          // just an auxiliary variable
 int lnst = strlen(script_cmd.c_str());                 // get the command length
 for(int i = 0; i < lnst; i++){                         // loop through all command
  if(script_cmd[i] == ','||script_cmd[i]==' '){         // split the position once a space or coma was found
   zptr++;                                              // move the auxiliary ptr
  }else{
   decomposed[zptr] = decomposed[zptr] + script_cmd[i]; // put character inside the text
  }
 }
 // this is the execution part compares all mneumonics and tests if exists and acts
 if(strcmp(decomposed[0].c_str(),"endfnc") == 0){ // if the comand is var then assign a variable (always integers)
  if(isRunning2==true){       // if the program is being executed
  is_running=false;           // stop the program execution
  }                           // which will kill the thread
 }
 /*
 [============ VARIABLE MANAGEMENT FUNCTION ===============]
 */
 if(strcmp(decomposed[0].c_str(),"var") == 0){ // if the comand is var then assign a variable (always integers)
  if(var_ptr < 1000){                          // if there's space on memory for a new variable
  for(int i = 0; i < var_ptr; i++){            // loop through all the variables defined
   if(strcmp(decomposed[1].c_str(),var_name[i].c_str())==0){ // look if the variable was already defined
    var_value[i] = atoi(decomposed[2].c_str()); // if it was replace it's value to prevent memory leak
    fnd_var = true;                             // if the variable was found tell var as true
    break;                                      // break the for loop
   }
  }
  if(fnd_var==false){                               // if the variable wasn't found
  var_name[var_ptr] = decomposed[1];                // get the name of the variable
  var_value[var_ptr] = atoi(decomposed[2].c_str()); // set the new value for the variable
  //std::cout<<"variable created with name: "<<var_name[var_ptr]<<" value: "<<var_value[var_ptr]<<" in position: "<<var_ptr<<std::endl;
  var_ptr++;                                        // update the position of the variable
  }
  }
 }
 /*
 =====================================================
 =     ARITMETIC FUNCTIONS GO IN THIS PART           =
 =====================================================
 */
 if(strcmp(decomposed[0].c_str(),"add") == 0){      // addition operation requires 1 variable and new value because the first parameter is where the result will be stored
  var_pos = 0;                                  // position where the variable was located
  for(int i = 0; i < var_ptr; i++){             // loop through all variables
   if(strcmp(decomposed[1].c_str(),var_name[i].c_str())==0){ // if it was found
    var_pos=i;                                               // set position where the new value will be stored
    fnd_var = true;                                          // tell the program that the variable was found
    break;                                                   // stop for loop
   }
  }
  for(int i = 0; i < var_ptr; i++){                          // loop again now for the number to add
   if(strcmp(decomposed[2].c_str(),var_name[i].c_str())==0){ // if variable was found means im adding 2 variables
    if(fnd_var==true){                                       // if variables was found
    var_value[i] = var_value[i] + var_value[var_pos];        // add both values
    }else{
    var_value[i] = var_value[i] + atoi(decomposed[2].c_str()); // else is a number which means im getting the integer value inside parameter
    }
    //std::cout<<"ADD RESULT: "<<var_value[i]<<std::endl; // debug message
    break;
   }
  }
 }
 if(strcmp(decomposed[0].c_str(),"sub") == 0){                 // same applies with the subtraction 
  var_pos = 0;                                                 // the only thing that changes inside this
  for(int i = 0; i < var_ptr; i++){                            // algorithm it's the operation that mus be done
   if(strcmp(decomposed[2].c_str(),var_name[i].c_str())==0){   // and the mneumonic used to apply that function
    var_pos=i;                                                 // the idea of the aritmetics inside the program
    fnd_var = true;                                            // it's that by the use of the system of exploiting the
    break;                                                     // string pieces which helps the system to work by executing the complete string 
   }                                                           // thanks to this idea i managed to get a full assembler language
  }                                                            // ona simple way just reading the mneumonic and parameters
  for(int i = 0; i < var_ptr; i++){                            // to be executed and thanks to this idea the program is capable to 
   if(strcmp(decomposed[1].c_str(),var_name[i].c_str())==0){   // create stuff on a simple way
    if(fnd_var==true){                                         // then when i find an arithmetic operation such as addition, subtraction
    var_value[i] = var_value[i] - var_value[var_pos];          // multiplication division or shifting bits inside the game
    }else{                                                     // I look into the stack to find the possible 
    var_value[i] = var_value[i] - atoi(decomposed[2].c_str()); // and then if the object is variable and i find the 
    }                                                          // 2 variables or 1 variable and number
    //std::cout<<"SUBTRACTION RESULT: "<<var_value[i]<<std::endl;// once this is done the math operation gets a solution
    break;                                                     // and then it's saved on the first parameter which is the variable
   }                                                           //QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
  }                                                            //QQQQQQQQQQQQQQQ@?QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
 }                                                             //QQQQQQQQQQQW"4Q[ mQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
 if(strcmp(decomposed[0].c_str(),"mul") == 0){                 //QQQQQQQQQQQQ  ?  ?QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQF!QF!QQQQQQQQQ
  var_pos = 0;                                                 //QQQQQQQQQQQQ6,    "$QQQQQQQQQQQQQQQQQQQQQQQQQQQQ, Z _QQQQQQQQQ
  for(int i = 0; i < var_ptr; i++){                            //QQQQQQQQQQQQQ      -4QQQQQQQQQQQQQQQQQQQQQQQW!?9( ' jP?QQQQQQQ
   if(strcmp(decomposed[2].c_str(),var_name[i].c_str())==0){   //QQQQQQQQQQQQ#   s,   4QQQQQQQQQQQQQQQQQQQWP'        '  WWQQQQQ
    var_pos=i;                                                 //QQQQQQQQQQQQP  ]QQm,_a"QQQQQQQQQQQQQQQQ@!<w[         _wWQQQQQQ
    fnd_var = true;                                            //QQQQQQQQQQQQf  WWWWQa4m/$QQQQQQQQQQQQP\amQWP"sa,    -QQQQQQQQQ
    break;                                                     //QQQQQQQQQQQQ[ycmWWQQQL]Q/4QQQQQQQQQQ@]WWWP\jQWWWL    WQQQQQQQQ
   }                                                           //QQQQQQQQQQQQ<W[mWWQWWQ6"Qa4QQQQQQQQW\mWD\jWQQQQQQ,   WWQQQQQQQ
  }                                                            //QQQQQQQQQQQW]WfmWWQQQWQ6]Qa4QQQQQQQfjWF<QWQQQQQQQ[   WWQQQQQQQ
  for(int i = 0; i < var_ptr; i++){                            //QQQQQQQQQQQQ]Wm4WWQQQQWQ6]Qr4QQQQQ@]W\jQQQWQWWWWQ[aq,QQQQQQQQQ
   if(strcmp(decomposed[1].c_str(),var_name[i].c_str())==0){   //QQQQQQQQQQQQcWm]WWQQQQQQW6]P-??!""'?\mQQQWWWQWWQQ(WQLQQQQQQQQQ
    if(fnd_var==true){                                         //QQQQQQQQQQQQL4Q)mQQQQQQWV\ajmmmQQQQw"WQWWQQQQQWWQ(QQ)WQQQQQQQQ
    var_value[i] = var_value[i] * var_value[var_pos];          //QQQQQQQQQQQQQ)Q[WQ@WQQD{jWWQQQQQQQQQmc?QQQQQQQWQQ)QQ)QQQQQQQQQ
    }else{                                                     //QQQQQQQQQQQQQ[Q[XQ(]W!smQQQQQQQQQQQQQWw/$QQQQQWWW]WQ]WQQQQQQQQ
    var_value[i] = var_value[i] * atoi(decomposed[2].c_str()); //QQQQQQQQQQQQQm]W]B(c_mWQQQQQQQQQQQQQQQQQc4WQQQWQFjQ#]QQQQQQQQQ
    }                                                          //QQQQQQQQQQQQQQ/Q,suQQQQQQQQQQQQQQQQQQQQWWL/$QQWW[QQPjQQQQQQQQQ
    //std::cout<<"MULTIPLY RESULT: "<<var_value[i]<<std::endl; //QQQQQQQQQQQQQQL$["a/4QQQQQQQQQQQQQQQQQQQQQQc4WQW\WW\WQQQQQQQQQ
    break;                                                     //QQQQQQQQQQQQQQQ/' WQw/4QQQQQQQQQQQQQQQQQQQQWrQW#]WfmWQQQQQQQQQ
   }                                                           //QQQQQQQQQQQQQQQP_rXQQF-$QQQQQQQQQQQQQQQQQQQQm]W[W@]WQQQQQQQQQQ
  }                                                            //QQQQQQQQQQQQQQQ_Qm-?V j]QQQQQQQQQQQQQQQQQQQQQc$\WtmQQQQQQQQQQQ
 }                                                             //QQQQQQQQQQQQQQQ]WtmQ,mQ[$WQQQQQQQQQQQQQQQQQQQm-jFjWQQQQQQQQQQQ
 if(strcmp(decomposed[0].c_str(),"div") == 0){                 //QQQQQQQQQQQQQQQ "]QQfWWfjQQQQQQQQQQQQQQQQQQQQQ[#\WQQQQQQQQQQQQ
  var_pos = 0;                                                 //QQQQQQQQQQQQQQ@]QL4V\,?{QQQQWQWQWQW$UQ@JVQQQQQh mWQQQQQQQQQQQQ
  for(int i = 0; i < var_ptr; i++){                            //QQQQQQQQQQQQQQ[mWQ\wWQ,WWB#mL_?VmmmWQd4Q(]QQQQQ,QQQQQQQQQQQQQQ
   if(strcmp(decomposed[2].c_str(),var_name[i].c_str())==0){   //QQQQQQQQQQQQQQm/QQ)BWW`4B4mQQ]ma/4$QWQQQL_]QQQQL4QQQQQQWQQQQQQ
    var_pos=i;                                                 //QQQQQQQQQQQQQQQm,s_4!swL_s}!"'QWQms"?????-6"WQQQ)QQQQQQQQQQQQQ
    fnd_var = true;                                            //QQQQQQQQQQQQQQQQ[WQ\mWW[WWW`  $QQQW(  ]mmcWma/??'QWQQQQQQQQQQQ
    break;                                                     //QQQQQQQQQQQQQQQQ(WQ]WW,\WQP   ]WQQW   -QQL'jQ#]L4WQQQQQQQQQQQQ
   }                                                           //QQQQQQQQQQQQQQQQ(Q@)WW!)WQf   ]WQQ#    QQ#-4Q#]W]QQQQQQQQQQQWQ
  }                                                            //QQQQQQQQQQQQQQQQ(F<QWmm(QQL   ]WQQQ   _QQfWmQFWB]WQQQQQQQQWQQQ
  for(int i = 0; i < var_ptr; i++){                            //QQQQQQQQQQQQQQQW\jQWQQQL$QQ,  mQQQQc  jQQsWQQ6]fdQQQQQQQQQQQQQ
   if(strcmp(decomposed[1].c_str(),var_name[i].c_str())==0){   //QQQQQQQQQQQQQQQQ""'jQQQQjQQmsaQ@??4majQQQyWQQQg,WQQQQQQQQWQQQQ
    if(fnd_var==true){                                         //QQQQQQW4QQQQQQQW>_QQQQQWmejQWWQ6  jQWWW@&9QQQP4[jQQQQQQQQQQQQQ
    var_value[i] = var_value[i] / var_value[var_pos];          //QQQQQQ6_"Q@4WQQQ(c jQQQQmsQQQQQQQQQQQQQQmdQQQ6_/jQQQQQQQQQQQQQ
    }else{                                                     //QQQE!?H(qc"_]QQQ][4P!4QQQQQQQQQQQQQQQQQQWQQQW,a[QQQQQQQQWQQQQQ
    var_value[i] = var_value[i] / atoi(decomposed[2].c_str()); //QQQQ/mwajWwJL4QQ)Qswmw/4QWQQQQQQQQQQQQQQQQ8??5/'QQQQQQQQQQQQQQ
    }                                                          //QQQQL$WBWWW@Wr$Q)WWWWQQw%?9UBQWQQQQQBP!""\ammwj(QQQQQQQQQQQQQQ
    //std::cout<<"ADD RESULT: "<<var_value[i]<<std::endl;      //QQQQQ)QL-4D\]F-P]QQWQQQQQmmaaa__aa aajmmQQQQQQQ(WQQQQQQQQQQQQQ
    break;                                                     //QQQQ!`?4)wsWr_r]WWQQQQQQQQQQWV"jQQa"HWQQQQQQQQQ(QQQQQQQQWQQQQQ
   }                                                           //QQQQm,{waWWWQQD)WQQQQQQQQQQQfjPQq$DXw]QQQQQQQQQw/QWQQQWQQQQQQQ
  }                                                            //QQQQQQ(QQWQQQWL4WQQQQQQQQQQPjV#mQmQd$L4QQQQQQQQW\WWQQQQQQQQQQQ
 }                                                             //QQQQQQ]WQQQQQQQ-QWQQQQQQQQW\WmmQQQQm$W/QQQQQQQQ(mQQQQQQQQQQQQQ
 if(strcmp(decomposed[0].c_str(),"shl") == 0){                 //QQQQQW)WQWQH$hm(QQQQQQQQQQ(mWmQQQQQQWWm]WQQQQQQfmQQQQQQQQQQQQQ
  var_pos = 0;                                                 //QQQQQPjd@qgQmyW]WQQQQQQQQfjQ[#QQQQQQm]QL4WQQQQQh4QQQQQQQQQQQQQ
  for(int i = 0; i < var_ptr; i++){                            //QQQQW\WQmQQWQQ#]QQQQQQQQ@)QQ(QmQQQQQd)WQc$QQQQQQ]WQQQQQQQQQQQQ
   if(strcmp(decomposed[2].c_str(),var_name[i].c_str())==0){   //QQQQFjQWQQQQQQfjQQQQQQQW\WW@ QmQQQQQW $QQ/QQQQQW)WQQQQQQQWQQQQ
    var_pos=i;                                                 //QQQW)QQQQQQQQW`QQQQQQQQfjQQ[[mdQQQQQX]]QWL]QQQQQ(WQQQQQQQQQQQQ
    fnd_var = true;                                            //QQQ[mQQQQQQQW'jQQQQQQQQ[WWWL,mWQQQQWp_wXQ#]QQQQQ[$QQQQQQQQQQQQ
    break;                                                     //QQQ[WQQQQQQW'jQQQQQQQQQ6]BGmm4mWQQQ#PmWCB[jQQQQQm/QQQQQQQWQQQQ
   }                                                           //QQQ(WQQQQQW'jQQQQQQQQQQQL"QQ#]mQQQQ#fmQQfjQQQQQQQm/QQQQQQQQQQQ
  }                                                            //QQQ[WQQQQQ[]WQQQQQQQQQQQQL4Q#]WWQQQDfmWfjQQQQQQQQQm/QQQQQQQQQQ
  for(int i = 0; i < var_ptr; i++){                            //QQQfmWQQQQ(mWQQQQQQQQQQQQQa4fWmWQQQ##]PjQQQQQQQQQQQm/QQQQQQQQQ
   if(strcmp(decomposed[1].c_str(),var_name[i].c_str())==0){   //QQQfmQQQQQfmQQQQQQQQQQQQQQQc'WmWQQQ##"jWWQQQQQQQQQQQL]QQQQQQQQ
    if(fnd_var==true){                                         //QQQfmQQQQQ[4QQQQQQQQQQQQQQQQ,mmQQQQmQ_QWQQQQQQQQQQQQWjQQQQQQQQ
    var_value[i] = var_value[i] << var_value[var_pos];         //QQQfmWQQQQL]QQQQQQ@^QQQQQQQQ[#QQQQQ#Q]WQQQQQQQQQQQQQfWWQQQQQQQ
    }else{                                                     //QQQL4QQQQQ#]QQQQQW=]WQQQQQQQ(#QQQQQ#Q)WQQQQQQWQQQQQQfmWQQQQQQQ
    var_value[i] = var_value[i] << atoi(decomposed[2].c_str());//QQQ#]QQQQQQ,4QQQQQ-]QQQQQQQQ(QmQQQQQW)WQQQQm-$QQQQQQ[mQQQQQQQQ
    }                                                          //QQQ#]QQQQQQQw-4QD" QWQQQQQQQ{QdP4"QBX]QQQQQQ_/QQQQQW(QQQQQQQQQ
    //std::cout<<"SHIFT RESULT: "<<var_value[i]<<std::endl;    //QQQQ/QQQQQQQWQ,-_aa,?QWQQQQ@]W#m,_Qh#]QQQQQQ[=QQQQP\jQQQQQQQQQ
    break;                                                     //QQQQm/QQQQQQQQQQQQQQa ""!"""]WmQ[]Q$Q]WQQQQWF_/4@\jQQQQQQQQQQQ
   }                                                           //QQQQQm/QQQQQQQQQQQQQQQmmmmm ]QQ$(]@mQ/QQQWF\jQQwsWWWQQQQQQQQQQ
  }                                                            //QQQQQQm/QQQQQQQQQQQQQQQQQQf ]QQd ]&QQ[s_a_wWQQQQWWQQQQQQQQQQQQ
 }                                                             //QQQQQQm/QQQQQQQQQQQQQQQQQQf ]QQd ]&QQ[s_a_wWQQQQWWQQQQQQQQQQQQ
 if(strcmp(decomposed[0].c_str(),"shr") == 0){                 //QQQQQQQm"BQQQQQQQQQQQQQWP\w[]QQD )dQQ(WQQQQQQQQQQQQQQQQQQQQQQQ
  var_pos = 0;                                                 //QQQQQQQQma,?4$QQQQQQWV!<yWWf]QQQ _QQQ[WQQQQQQQQQQQQQQQQQQQQQQQ
  for(int i = 0; i < var_ptr; i++){                            //QQQQQQQQQQQQwa/"{s_aaamQQQQf]QVW(]Q4P[WQQQQQQQQQQQQQQQQQQQQQQQ
   if(strcmp(decomposed[2].c_str(),var_name[i].c_str())==0){   //QQQQQQQQQQQQQWQQQQQQWWQQQQQf]7p$,]2pm,WQQQQQQQQQQQQQQQQQQQQQQQ
    var_pos=i;                                                 //QQQQQQQQQQQQQQQQQQQQQQQQQQQ[jQQQ[]QQQ[WWQQQQQQQQQQQQQQQQQQQQQQ
    fnd_var = true;                                            //QQQQQQQQQQQQQQQQQQQQQQQQQQQ(QQQQ\JQQQfmWQQQQQQQQQQQQQQQQQQQQQQ
    break;                                                     //QQQQQQQQQQQQQQQQQQQQQQQQQQQ(QQQQ)XQQQfmQQQQQQQQQQQQQQQQQQQQQQQ
   }                                                           //QQQQQQQQQQQQQQQQQQQQQQQQQQQ(QQQQ)XQQQfmQQQQQQQQQQQQQQQQQQQQQQQ
  }                                                            //QQQQQQQQQQQQQQQQQQQQQQQQQQQ(QQQQ]SQQQfmWQQQQQQQQQQQQQQQQQQQQQQ
  for(int i = 0; i < var_ptr; i++){                            //QQQQQQQQQQQQQQQQQQQQQQQQQQQ(QQQQ)XQQQ[WWQQQQQQQQQQQQQQQQQQQQQQ
   if(strcmp(decomposed[1].c_str(),var_name[i].c_str())==0){   //QQQQQQQQQQQQQQQQQQQQQQQQQQQ(QQQQ)XQQQfmWQQQQQQQQQQQQQQQQQQQQQQ
    if(fnd_var==true){                                         //QQQQQQQQQQQQQQQQQQQQQQQQQQQ(QQQ@)rQQQ[WWQQQQQQQQQQQQQQQQQQQQQQ
    var_value[i] = var_value[i] >> var_value[var_pos];         //QQQQQQQQQQQQQQQQQQQQQQQQQQQ\WQQ#](QQQL4QQQQQQQQQQQQQQQQQQQQQQQ
    }else{                                                     //QQQQQQQQQQQQQQQQQQQQQQQQQQQ)QQQ#)(QQQ#]QQQQQQQQQQQQQQQQQQQQQQQ
    var_value[i] = var_value[i] >> atoi(decomposed[2].c_str());//QQQQQQQQQQQQQQQQQQQQQQQQQQQ)WQQ#](WQQ#]QQQQQQWQQQWQQQWQQQWQQQQ
    }                                                          //QQQQQQQQQQQQQQQQQQQQQQQQQQQ)PQP&)(@4P#]QQQQQQQQQQQQQQQQQQQQQQQ
    //std::cout<<"SHIFT RESULT: "<<var_value[i]<<std::endl;    //QQQQQQQQQQQQQQQQQQQQQQQQQQQ)fmfX](#]fX]QQQQQQQQQQQQQQQQQQQQQQQ
    break;                                                     //QQQQQQQQQQQQQQQQQQQQQQQQQQQ( "' jc--' WQQQQQQQQQQQQQQQQQQQQQQQ
   }                                                           //QQQQQQQQQQQQQQQQQQQQQQQQQQQQ6aaQWQ6aaQWQQQQQQQQQQQQQQQQQQQQQQQ
  }                                                            //QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
 }
 /*
  =================================
  = SOMETHING HAPPEN INSIDE WORLD =
  =================================
  */
 if(strcmp(decomposed[0].c_str(),"act") == 0){
  //std::cout<<"act has been detected"<<std::endl;
  if(strcmp(decomposed[1].c_str(),"player.touched") == 0){
   //std::cout<<"object is touched by player"<<std::endl;
   if(strcmp(decomposed[2].c_str(),"destroy") == 0){
    //std::cout<<"look for object to destroy"<<std::endl;
    tdx = (px)/15; tdz = (pz)/15;
    tcox = tdx;   tcoz = tdz;
    tdx = (tdx - tcox)*15; tdz = (tdz - tcoz)*15;
    if(px < 0){tdx = 15+tdx;}
    if(pz < 0){tdz = 15+tdz;}
     if(Wrl_Sys.Chunk_Get_Info(loc_X,loc_Y,tdx,py,tdz)==bs_id){
      bon_push_into_cmd("<BrickVox Script Service>> Player touched the object!");
      Wrl_Sys.Chunk_Edit_Add(loc_X,loc_Y,tdx,py,tdz,0);
     }
    }
   }
   //std::cout<<"player touched"<<std::endl;
  }
  /*
  =========================================================
  =  FUNCTION TO TEST IF BLOCK EXISTS ON DEFINED LOCATION =
  =========================================================
  */
  if(strcmp(decomposed[0].c_str(),"tst") == 0){
    int tpx03 = atoi(decomposed[2].c_str());
    int tpy03 = atoi(decomposed[3].c_str());
    int tpz03 = atoi(decomposed[4].c_str());
    if(tpx03 > 15){tpx03=15;}else if(tpx03 < 0){tpx03=0;}
    if(tpy03 > 255){tpy03=255;}else if(tpy03 < 0){tpy03=0;}
    if(tpz03 > 15){tpz03=15;}else if(tpz03 < 0){tpz03=0;}
    if(Wrl_Sys.Chunk_Get_Info(loc_X,loc_Y,tpx03,tpy03,tpz03)!=0){
      for(int i = 0; i < var_ptr; i++){
        if(strcmp(decomposed[1].c_str(),var_name[i].c_str()) == 0){
           var_value[i] = 1;
           break;
        }
      }
    }
  }
  /*
  ======================================================
  =  FUNCTION THAT WILL SET BLOCKS ON CERTAIN POSITION =
  ======================================================
  */
  if(strcmp(decomposed[0].c_str(),"set") == 0){
    float tsx,tsz;
    int tsy = atoi(decomposed[2].c_str());
    int blc = atoi(decomposed[4].c_str());
    int tcosx, tcosz,chtx,chtz;
    tsx = (atoi(decomposed[1].c_str()))/15; tsz = (atoi(decomposed[3].c_str()))/15;
    tcosx = tsx;   tcosz = tsz;
    tsx = (tsx - tcosx)*15; tsz = (tsz - tcosz)*15;
    chtx=tsx; chtz=tsz;
    Wrl_Sys.Chunk_Edit_Add(chtx,chtz,tsx,tsy,tsz,blc);
  }
  /*
  ======================================
  = CALL FUNCTIONS FROM OTHER LANGUAGE =
  ======================================
  */
  if(strcmp(decomposed[0].c_str(),"call") == 0){ // if the game detects a jump then change the game's ptr
   //std::cout<<"system call was detected"<<std::endl; // if detects a call isntruction
   if(strcmp(decomposed[1].c_str(),"printf") == 0){  // test which function of other language is
    int ln = strlen(decomposed[2].c_str());          // in this case C printf function
    std::string tmp_read_string = decomposed[2];     // this will just push a message inside the developer console
    std::string string_composed; bool isComa=false;  // after that all left is to test for other possibilities
    for(int i = 0; i < ln; i++){                     // the idea of this it's an expansion of language functions
     if(tmp_read_string[i]!='$'){                    // the $ is the equivalent for "" to prevent MySQL problems
      string_composed = string_composed + tmp_read_string[i]; //if(isComa==true){isComa=false;}else if(isComa==false){isComa=true;} 
     }
     //if(isComa==true){
      
     //}
    }
    bon_push_into_cmd(string_composed);
    //std::cout<<"message sent>> "<<chat_tosend<<std::endl;
   }
  }
  /*
  =============================
  = COMPARE IF EQUAL TO VALUE =
  =============================
  */
  if(strcmp(decomposed[0].c_str(),"cmp") == 0){ // if the statement for a comparison has appeared into the code
   int val1 = 0; int val2 = 0;                  // create 2 values to compare into the code
   for(int i = 0; i < var_ptr; i++){
    if(strcmp(decomposed[1].c_str(),var_name[i].c_str()) == 0){ // if the value is a variable
     val1 = var_value[i];                                       // save it into the first value
     break;                                                     // and stop looping through all variables
    }else{                                                      // else
      val1 = atoi(decomposed[1].c_str());                       // means that the variable might be a number
    }
  }
  for(int i = 0; i < var_ptr; i++){                             // same idea applies for the second value
    if(strcmp(decomposed[2].c_str(),var_name[i].c_str()) == 0){ // the idea of this function it's to find both 
     val2 = var_value[i];                                       // values and then compare them to test condition
     break;                                                     // similar to an if statement doing:
    }else{                                                      // if(a==b)
      val2 = atoi(decomposed[2].c_str());                       // in case the answer it's true
    }                                                           // then jump to next line
  }
  if(val1 == val2){                                              // if the values are equal                        
  exptr = exptr+1;                                               // jump to the next line
  //std::cout<<"\e[1;31m JUMPED POSITION \e[0m"<<exptr<<std::endl;
  }else{                                                         // else the case is false
  exptr = exptr+2;                                               // skip one line of the code 
  }
  usleep(150*1000);//std::chrono::milliseconds(300);             // sleep to prevent memory leaks
  runln(code[exptr]);                                            // execute the statement
  }
  /*
  ===========================
  = COMPARE IF LARGER  THAN =
  ===========================
  */
  if(strcmp(decomposed[0].c_str(),"upr") == 0){ // if the statement for a comparison has appeared into the code
   int val1 = 0; int val2 = 0;                  // create 2 values to compare into the code
   for(int i = 0; i < var_ptr; i++){
    if(strcmp(decomposed[1].c_str(),var_name[i].c_str()) == 0){ // if the value is a variable
     val1 = var_value[i];                                       // save it into the first value
     break;                                                     // and stop looping through all variables
    }else{                                                      // else
      val1 = atoi(decomposed[1].c_str());                       // means that the variable might be a number
    }
  }
  for(int i = 0; i < var_ptr; i++){                             // same idea applies for the second value
    if(strcmp(decomposed[2].c_str(),var_name[i].c_str()) == 0){ // the idea of this function it's to find both 
     val2 = var_value[i];                                       // values and then compare them to test condition
     break;                                                     // similar to an if statement doing:
    }else{                                                      // if(a>b)
      val2 = atoi(decomposed[2].c_str());                       // in case the answer it's true
    }                                                           // then jump to next line
  }
  if(val1 > val2){                                              // if A is larger than B                        
  exptr = exptr+1;                                               // jump to the next line
  //std::cout<<"\e[1;31m JUMPED POSITION \e[0m"<<exptr<<std::endl;
  }else{                                                         // else the case is false
  exptr = exptr+2;                                               // skip one line of the code 
  }
  usleep(150*1000);//std::chrono::milliseconds(300);             // sleep to prevent memory leaks
  runln(code[exptr]);                                            // execute the statement
  }
  /*
  ===========================
  = COMPARE IF SMALLER THAN =
  ===========================
  */
  if(strcmp(decomposed[0].c_str(),"lwr") == 0){ // if the statement for a comparison has appeared into the code
   int val1 = 0; int val2 = 0;                  // create 2 values to compare into the code
   for(int i = 0; i < var_ptr; i++){
    if(strcmp(decomposed[1].c_str(),var_name[i].c_str()) == 0){ // if the value is a variable
     val1 = var_value[i];                                       // save it into the first value
     break;                                                     // and stop looping through all variables
    }else{                                                      // else
      val1 = atoi(decomposed[1].c_str());                       // means that the variable might be a number
    }
  }
  for(int i = 0; i < var_ptr; i++){                             // same idea applies for the second value
    if(strcmp(decomposed[2].c_str(),var_name[i].c_str()) == 0){ // the idea of this function it's to find both 
     val2 = var_value[i];                                       // values and then compare them to test condition
     break;                                                     // similar to an if statement doing:
    }else{                                                      // if(a<b)
      val2 = atoi(decomposed[2].c_str());                       // in case the answer it's true
    }                                                           // then jump to next line
  }
  if(val1 < val2){                                              // if A is smaller than B                        
  exptr = exptr+1;                                               // jump to the next line
  //std::cout<<"\e[1;31m JUMPED POSITION \e[0m"<<exptr<<std::endl;
  }else{                                                         // else the case is false
  exptr = exptr+2;                                               // skip one line of the code 
  }
  usleep(150*1000);//std::chrono::milliseconds(300);             // sleep to prevent memory leaks
  runln(code[exptr]);                                            // execute the statement
  }
  /*
  ===========================
  = COMPARE IF DIFFERNT TO  =
  ===========================
  */
  if(strcmp(decomposed[0].c_str(),"dif") == 0){ // if the statement for a comparison has appeared into the code
   int val1 = 0; int val2 = 0;                  // create 2 values to compare into the code
   for(int i = 0; i < var_ptr; i++){
    if(strcmp(decomposed[1].c_str(),var_name[i].c_str()) == 0){ // if the value is a variable
     val1 = var_value[i];                                       // save it into the first value
     break;                                                     // and stop looping through all variables
    }else{                                                      // else
      val1 = atoi(decomposed[1].c_str());                       // means that the variable might be a number
    }
  }
  for(int i = 0; i < var_ptr; i++){                             // same idea applies for the second value
    if(strcmp(decomposed[2].c_str(),var_name[i].c_str()) == 0){ // the idea of this function it's to find both 
     val2 = var_value[i];                                       // values and then compare them to test condition
     break;                                                     // similar to an if statement doing:
    }else{                                                      // if(a!=b)
      val2 = atoi(decomposed[2].c_str());                       // in case the answer it's true
    }                                                           // then jump to next line
  }
  if(val1 != val2){                                              // if A is different to B                        
  exptr = exptr+1;                                               // jump to the next line
  //std::cout<<"\e[1;31m JUMPED POSITION \e[0m"<<exptr<<std::endl;
  }else{                                                         // else the case is false
  exptr = exptr+2;                                               // skip one line of the code 
  }
  usleep(150*1000);//std::chrono::milliseconds(300);             // sleep to prevent memory leaks
  runln(code[exptr]);                                            // execute the statement
  }
  /*
  ==================
  = JUMP STATEMENT =
  ==================
  */
  if(strcmp(decomposed[0].c_str(),"jmp") == 0){ // if the game detects a jump then change the game's ptr
  exptr = atoi(decomposed[1].c_str())-1;
  //std::cout<<"\e[1;31m JUMPED POSITION \e[0m"<<exptr<<std::endl;
  //for(int i = 0; i < lenc; i++){
  // std::cout<<"line: "<<i<<"| "<<code[i]<<std::endl;
  //}
  bon_push_into_cmd("<BrickVox Script Service>> Pointer Jumped to line "+std::to_string(exptr));
  usleep(150*1000);//std::chrono::milliseconds(300);
  runln(code[exptr]);
  //}
 }
}
