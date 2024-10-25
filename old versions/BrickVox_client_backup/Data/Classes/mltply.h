/*
==============================================================================================
=   PLAYER MANACEMENT CLASS BASED ON CHUNK SYSTEM TO ALLOW PLAYERS GET THEIR OWN AVATARS OWO =
==============================================================================================
*/
struct Player{
 int User_Id;                               // user ID
 std::string p_usernm;                      // user name
 float o_px=0, o_py=0, o_pz=0, o_pa=0;      // user location and rotation
 int v_num = 0;                             // vertex number
 double model[9][9000];                     // model data
 double uv[6][9000];                        // UV data
 GLuint Tex;                                // Texture
 Player *parent;                            // pointer to delete players
};
/* ============ { PLAYER MANAGEMENT CLASS TO ALLOW MULTIPLAYER } ================= */
class Player_manager{
 public: 
  int p_ptr = 0;                       // counter to test the number of players inside the game
  Player *users_online[100];           // pointer array with all the players inside the game
  Player *auxiliar;                    // auxiliar pointer to manage the players ingame and read them
  Player_manager();                    // constructor for our player class
  std::string _modl;                   // temporal model bridge
  void Player_Joined( int _id, std::string _usr, std::string _url , int _pushed,float _x,float _y, float _z, int _r);
  // ^^^ THIS FUNCTION RUNS WHEN THE PLAYER IS ADDED INTO THE GAME AND PUSHES THE PLAYER INTO THE TREE
  void Player_Drawall();               // function to draw all the players inside the game
  void Player_Initialize();            // when game starts this will ask all players for their data
  void Player_Update();                // get the new information of players to syncronize games
};
/*
==================================================================================================
=     ALL THE REQUIRED CLASS FUNCTIONS FOR MULTIPLAYER TO WORK CORRECTLY START IN HERE  OWO      = 
==================================================================================================
*/
/*######################### PLAYER MANAGER CONTRUCTOR ######################*/
Player_manager::Player_manager(){                      // this is the player manager function
 //std::cout<<"initializing players...."<<std::endl;     // just a debug message to know if its working
 for(int i = 0; i < 100; i++){users_online[i] = NULL;} // start the player array and set all players to NULL
}
/* ---------------- THIS MUST BE CALLED WHEN THE GAME START TO GET ALL PLAYER DATA ---------------*/
void Player_manager::Player_Initialize(){                                  
 std::string rq_f = "SELECT * FROM Players_ingame WHERE Username <> '"+tmp_username+"' AND Sesion = "+std::to_string(current_sesion)+";"; // query to get everyone's data except for self
 lock_query = true;                             // prevent multiple querys to happen at the same time
 mysql_query(connect,rq_f.c_str());             // ask mysql to get the information of players
 res_set = mysql_store_result(connect);         // save the result on the pointer
 while((row=mysql_fetch_row(res_set))!=NULL){   // while i'm still receiving information of players
 std::string tus = row[2];                      // convert username into string
 std::string _modl = row[7];                    // convert model into string
 std::string tul = row[8];                      // convert URL of skin into string
   //std::cout<<"recv:\n"<<_modl<<std::endl;      // debug message to test if model could be loaded
   bridge = _modl;                              // just a bridge variable to call the model
  Player_Joined(atoi(row[0]),tus,tul, p_ptr,atof(row[3]),atof(row[4]),atof(row[5]),atoi(row[6]));
  // ^^^ THIS FUNCTION TELLS THE GAME TO ADD A NEW PLAYERS AS A CHUNK INTO THE TREE THAT CONTROLS PLAYER INFO
  //std::cout<<"pushed object\n"; // debug message to know if the game was called
  p_ptr++;                      // move the current player pointer
  jnt = atoi(row[1]);           // get last moment when player joined into the game
 }
 mysql_free_result(res_set);    // clean the memory to prevent leaks
 lock_query = false;            // allow the game to do other Querys to mysql
}
/*
######################################################################################################
# ================================================================================================== #
# =     TODO: THIS IS ONE OF THE MOST IMPORTANT FUNCTIONS!!! THIS UPDATES AND RECEIVES PLAYERS!!!  = #
# ================================================================================================== #
######################################################################################################
*/
void Player_manager::Player_Update(){
 lock_query = true;                   // prevent other query's to happen at the same time than this
 glutPostRedisplay();                 // show new buffer to prevent loosing framerate
 float txp = 0, typ = 0, tzp = 0; int trt = 0, tid = 0,tptr = 1,itmp = 0; // some temporal variables
 //std::cout<<"running update"<<std::endl;     // debug message that the function is Running
 while(players_i[itmp] >= 0 && itmp < 100){  // while the player is inside the ranking of nodes that can be supported by the game
  tid = players_i[itmp];                     // convert player id into integer
  txp = players_x[itmp];                     // convert player X into integer
  typ = players_y[itmp];                     // convert player Y into integer
  tzp = players_z[itmp];                     // convert player Z into integer
  trt = players_r[itmp];                     // convert player Rotation into integer
  tptr = players_j[itmp];                    // get the moment when player joined
  //std::cout<<"tptr: "<<tptr<<" jnt: "<<jnt<<std::endl; // display the moment as a debug message
  if(tptr <= jnt){                           // if the player joined before than last fetched player
  //std::cout<<"update player positions\n";    // show debug message for it's positions
  for(int i = 0; i < p_ptr; i++){            // loop through all players to find him/her
    //std::cout<<"infor"<<std::endl;           // debug message
    auxiliar = users_online[i];              // save the player into a pointer to edit data
   if(auxiliar != NULL){                     // if the pointer is not NULL (prevent memory leaks aswell)
    //std::cout<<"ponter assigned"<<std::endl; // show a debug message
    if(auxiliar->User_Id == tid){            // if player id is similar to data found
     //std::cout<<"inif"<<std::endl;           // another debug stuff
     auxiliar->o_px = txp;                   // update the X position
     auxiliar->o_py = typ;                   // update the Y position 
     auxiliar->o_pz = tzp;                   // update the Z position
     auxiliar->o_pa = trt;                   // update the Rotation of player
    }
   }                                         // close all the brackets that where open before
  }
   //std::cout<<"success"<<std::endl;          // success message updating all players
  }else{                                     // if the player joined later than last fetched player
  //std::cout<<"update players download"<<std::endl;  // show an important debug message
   // JOIN NEW PLAYER
   std::string tus = play_usr[itmp];         // get that player username
   std::string _modl = play_mdl[itmp];       // get that player model
   std::string tul = play_url[itmp];         // get that player URL
   //std::cout<<"recv:\n"<<_modl<<std::endl;   // debug message again to know if .obj was received correctly
   bridge = _modl;                           // do again a bridge to fetch the information
   Player_Joined(players_i[itmp],tus,tul, p_ptr,players_x[itmp],players_y[itmp],players_z[itmp],players_r[itmp]);
   // ^^^ PUSH INTO THE TREE THE NEW PLAYER TO BE ABLE TO MODIFY AND SEE THE PLAYER DATA
   //std::cout<<"pushed object\n"; // debug message to tell me it was successful
   p_ptr++;                      // move the current player pointer
   jnt = players_j[itmp];        // tell the game this player was the lastone to join
  } 
  itmp++;                        // increment the temporal ptr 
 }
 lock_query = false;             // ALLOW THE GAME TO DO OTHER QUERYS AGAIN
 /* "UPDATE Players_ingame SET Pos_X = " + std::to_string(px) + ",Pos_Y = " + std::to_string(py) + ",Pos_Z = " +  std::to_string(pz) + ",Rot_P = " + std::to_string(angle) + "    WHERE Username = '" + tmp_username + "';";*/
}
/*
########################################################################################
#      IMPORTANT FUNCTION AGAIN THIS PUSHES A NEW PLAYER INTO THE STACK  OF PCHUNKS    #
########################################################################################
*/
void Player_manager::Player_Joined( int _id, std::string _usr, std::string _url , int _pushed,float _x,float _y, float _z, int _r){
 //std::cout<<"model:\n"<<bridge<<std::endl; // FIRST OF ALL show a message to notice if data was gotten correctly
 Player *newplayer = new Player();    // create a new player chunk node
 newplayer->User_Id = _id;            // set the ID of the player
 newplayer->p_usernm = _usr;          // set the username of the player
 newplayer->o_px = _x;                // set the spawn point of player on X axis
 newplayer->o_py = _y;                // set the spawn point of player on Y axis
 newplayer->o_pz = _z;                // set the spawn point of player on Z axis
 newplayer->o_pa = _r;                // set the player rotation as a default value
 download_bmp_image(_usr, _url);      // tell the game to download the texture from the player
 load_obj_model(bridge, newplayer->model, newplayer->uv); // get toghether the .obj model file to a readable format for the game
 newplayer->v_num = _n;                                   // get the vertex number of the player
 //std::cout<<"valor de n: "<<_n<<std::endl;                // just another debug message
 //std::cout<<"model loaded is: "<<t_model[0][0]<<" "<<t_model[0][1]<<" "<<t_model[0][2]<<"\n";
 //std::string a;
 //std::cin>>a;
 std::string tex_image = "./Temporal/Skins/tmpimg_" + _usr + ".bmp"; // get the downloaded texture from player
 char *lnk = new char[strlen(tex_image.c_str())+1];    // create a tiny temporal pointer with the directory 
 strcpy(lnk, tex_image.c_str());                       // transform into other var type 
 newplayer->Tex = Bon_load_bmp(lnk, 128, 64);          // load the player texture as .bmp into the game
 delete lnk;                                           // destroy the pointer to prevent memory leaks
 newplayer->parent = NULL;                             // pointer to destroy a player this is the parent chunk
 if(users_online[_pushed] != NULL){                    //if user couln't be pushed
  Player *p_tmp = new Player();                        // create a temporal chunk
  auxiliar = users_online[_pushed];                    // assign the actual chunk to delete to the global aux
  auxiliar->parent = p_tmp;                            // set the chunk to delete parent look at the temporal chunk that will be deleted
  users_online[_pushed] = NULL;                        // make the main pointer that manages the chunks look at null
  delete p_tmp;                                        // delete temporal, this will delete the old chunk to avoid memory leaks
 }
 users_online[_pushed] = newplayer;                    // add new player information into the stack
}
/*
=============================================
=    DRAW ALL THE PLAYERS INSIDE THE GAME   =
=============================================
*/
void Player_manager::Player_Drawall(){
  //std::cout<<"drawf"<<std::endl;        // debug message for drawing the players
 //glDisable(GL_TEXTURE_2D);
 for(int i = 0; i < p_ptr; i++){        // loop through all players in game
  auxiliar = users_online[i];           // set the pointer to current player -- allow edit and read
  //std::cout<<"testing for draw"<<std::endl;
    //  std::cout<<"drawing...."<<std::endl;
   glPushMatrix();                      // a matrix per player to prevent moving all them at the same time
   //std::cout<<"rotation loaded as: "<<auxiliar->o_pa<<std::endl;
   if(auxiliar->o_px > (px-100) && auxiliar->o_px < (px+100)){ // if it's inside a rendering distance
   if(auxiliar->o_py > (py-100) && auxiliar->o_py < (py+100)){ // if it's inside a rendering distance
   if(auxiliar->o_pz > (pz-100) && auxiliar->o_pz < (pz+100)){ // if it's inside a rendering distance
   glTranslatef(auxiliar->o_px,auxiliar->o_py,auxiliar->o_pz); // translate the shape to the player position
   glRotatef(auxiliar->o_pa,0,auxiliar->o_pa,1);               // rotate the player to it's position
   // from here begins the rendering of the players
   glBindTexture(GL_TEXTURE_2D, auxiliar->Tex); // assign their players the 
   glBegin(GL_TRIANGLES);             // draw the player shape by triangles for each polygon (might help into shading on a future)
   //std::cout<<"vertex number loaded as: "<<auxiliar->v_num<<std::endl; // just a debug message
    for(int z = 0; z < auxiliar->v_num; z++){  
     if(auxiliar->model[1][z] >= 0){
      glColor3f(0.2+(py/100)+abs(auxiliar->model[1][z]),0.2+(py/100)+abs(auxiliar->model[1][z]),0.2+(py/100)+abs(auxiliar->model[1][z]));
     }else{
      glColor3f(0.2+(py/100)+(0),0.2+(py/100)+(0),0.2+(py/100)+(0));
     }
                                           // draw each triangle of the model
     glTexCoord2f(auxiliar->uv[0][z],  auxiliar->uv[1][z]);                               // -
     glVertex3f(auxiliar->model[0][z], auxiliar->model[1][z], auxiliar->model[2][z]);     //  |
                                                                                          //  |
     if(auxiliar->model[4][z] >= 0){
      glColor3f(0.2+(py/100)+abs(auxiliar->model[4][z]),0.2+(py/100)+abs(auxiliar->model[4][z]),0.2+(py/100)+abs(auxiliar->model[4][z]));
     }else{
      glColor3f(0.2+(py/100)+(0),0.2+(py/100)+(0),0.2+(py/100)+(0));
     }
     
     glTexCoord2f(auxiliar->uv[2][z],  auxiliar->uv[3][z]);                               //  | texture mapping
     glVertex3f(auxiliar->model[3][z], auxiliar->model[4][z], auxiliar->model[5][z]);     //  | and vertex
                                                                                          //  |
     if(auxiliar->model[7][z] >= 0){
      glColor3f(0.2+(py/100)+abs(auxiliar->model[7][z]),0.2+(py/100)+abs(auxiliar->model[7][z]),0.2+(py/100)+abs(auxiliar->model[7][z]));
     }else{
      glColor3f(0.2+(py/100)+(0),0.2+(py/100)+(0),0.2+(py/100)+(0));
     }
     
     glTexCoord2f(auxiliar->uv[4][z],  auxiliar->uv[5][z]);                               //  |
     glVertex3f(auxiliar->model[6][z], auxiliar->model[7][z], auxiliar->model[8][z]);     // -
    }
   glEnd(); // end of drawing the shape of the player 
  }
  } // close all brackets that were opened during the drawing of each polygon of the player
  }
  glPopMatrix(); // pop the matrix to allow drawing and translating other plkayer shapes
 }
 //glEnable(GL_TEXTURE_2D);
}
/*
===============================================================
=  SECONDARY THREAD OF THE GAME THAT UPDATES ALL MYSQL STUFF  =
===============================================================
*/
void Position_Update(){
std::string u_tmp_v;                         // string for temporal Query that helps to update player position
 while(1){                                   // main secondary thread while looping that activates once the other thread tells it to do it
  //std::cout<<"requesting upd"<<std::endl;    // debug message that tells when is the program going through another requesting process
  if(isRunning == true){                     // If update is enabled
   if(lock_query == false){                  // and nothing it's preventing the game to do Querys to MySQL
    q_locked = true;                         // enable locking to other thread the requests
    /*
    ======================================================================================
    =     PLAYER UPDATE SELF POSITION ON THE SERVER DATABASE SO REALTIME MOVENT EXISTS   =
    ======================================================================================
    */
   //std::cout<<"updating players...."<<std::endl;
    if(is_tpv==false){
    u_tmp_v = "UPDATE Players_ingame SET Pos_X = " + std::to_string(px) + ",Pos_Y = " + std::to_string(py) + ",Pos_Z = " +  std::to_string(pz) + ",Rot_P = " + std::to_string(angle) + "    WHERE Username = '" + tmp_username + "';";
    }else{
    u_tmp_v = "UPDATE Players_ingame SET Pos_X = " + std::to_string(px) + ",Pos_Y = " + std::to_string(py) + ",Pos_Z = " +  std::to_string(pz) + ",Rot_P = " + std::to_string(pa) + "    WHERE Username = '" + tmp_username + "';";
    }
    mysql_query(connect, u_tmp_v.c_str());                                                   //  THE QUERY THAT STORES THE NEW PLAYER POSITION INTO THE SERVER 
    //std::cout<<"ERROR REQUESTING NEW POSITIONS: "<<mysql_errno(connect)<<std::endl;          //  DEBUG MESSAGE THAT TELLS ME IF SOMETHING WENT WRONG DURING UPLOADING POSITION
    /*
    =================================================================
    =  SELECT ALL PLAYER OBJECTS IN GAME AND SAVE THEM TO DATABASE  =
    =================================================================
    */
    std::string rq_f = "SELECT * FROM Players_ingame WHERE Username <> '"+tmp_username+"' AND Sesion = "+std::to_string(current_sesion)+";"; // get all players that are not self to update their positions
    mysql_query(connect,rq_f.c_str());                                                       // do the query to MySQL server
    //std::cout<<"ERROR2 REQUESTING NEW POSITIONS: "<<mysql_errno(connect)<<std::endl;         // debug message to understand if something went wrong
    res_set = mysql_store_result(connect);            // store player data into result pointer
    while((row = mysql_fetch_row(res_set))!=NULL){    // while im receiving information 
      players_i[data_number_p] = atoi(row[0]);        // call the inside database system of the game done with arrays
      players_x[data_number_p] = atof(row[3]);        // which might help saving all player information inside the game
      players_y[data_number_p] = atof(row[4]);        // and then use all that info for the update function
      players_z[data_number_p] = atof(row[5]);        // that inserts new player into the game aswell as update their positions
      players_r[data_number_p] = atoi(row[6]);        // here i convert each data to it's respective dataformat and then
      players_j[data_number_p] = atoi(row[1]);        // store it into an array to use later outside this thread
      play_mdl[data_number_p]  = row[7];              // this system will prevent multiple query's to
      play_url[data_number_p]  = row[8];              // happen at the same thime which causes crashes inside the game
      play_usr[data_number_p]  = row[2];              // and also prevent the performance to be affected by networking
      data_number_p++;                                // since everything runs inside a secondary thread
    }                                                 // which makes the game playable in offline mode
    //std::cout<<"post player"<<std::endl;              // and also there must be an array system to store all database info
    players_i[data_number_p+1] = -1;                  // this is done to prevent memory leaks
    data_number_p = 0;                                // reset this variable
    mysql_free_result(res_set);                       // clean the result pointer to prevent more memory leaks
    std::string chat_fix_query = "SELECT * FROM chat_data WHERE Session = "+std::to_string(current_sesion)+" ORDER BY Message_ID DESC LIMIT 6;";
    mysql_query(connect, chat_fix_query.c_str()); // query to receive all player messages
    res_set = mysql_store_result(connect);         // store messages inside the 
    while((row=mysql_fetch_row(res_set))!=NULL){   // while it's fetching messages
     chat_messages[msg_count] = row[2];            // save messages inside an array
     msg_count++;                                  // just for array movement
    }
    msg_count = 0;                                 // reset the pointer
    mysql_free_result(res_set);                    // free the result of all messages to prevent leaks
    if((is_texting == false) && (strlen(chat_tosend.c_str())) > 0 ){  // if player is not testing anymore and there is a message into the stack
     msg = "INSERT INTO chat_data (Msg_Data,User_Sent,Session) VALUES ('"+chat_tosend+"','"+tmp_username+"',"+std::to_string(current_sesion)+");"; // send to mysql the message
     mysql_query(connect,msg.c_str()); // send to MySQL the message with the username who sent the message
     chat_tosend = "";                 // and then clear again the message buffer to send new messages and prevent spam
    }
    //std::cout<<"updating pos..."<<std::endl; // just another debug message lol
    /*
    ==========================================
    =  LOAD THE CHUNK DATA WHERE I'M LOCATED =
    ==========================================
    */
    //std::cout<<"UPDATING BUILD IN WORLD"<<std::endl; // debug message that tells me when is the world being updated 
    std::string mql = "SELECT * FROM Modifications WHERE ((Chunk_X = "+std::to_string(loc_X)+" AND Chunk_Y = "+std::to_string(loc_Y)+") OR (Chunk_X = "+std::to_string(loc_X-1)+" AND Chunk_Y = "+std::to_string(loc_Y+1)+") OR (Chunk_X = "+std::to_string(loc_X)+" AND Chunk_Y = "+std::to_string(loc_Y+1)+") OR (Chunk_X = "+std::to_string(loc_X+1)+" AND Chunk_Y = "+std::to_string(loc_Y+1)+") OR (Chunk_X = "+std::to_string(loc_X-1)+" AND Chunk_Y = "+std::to_string(loc_Y)+") OR (Chunk_X = "+std::to_string(loc_X+1)+" AND Chunk_Y = "+std::to_string(loc_Y)+") OR (Chunk_X = "+std::to_string(loc_X-1)+" AND Chunk_Y = "+std::to_string(loc_Y-1)+")  OR (Chunk_X = "+std::to_string(loc_X)+" AND Chunk_Y = "+std::to_string(loc_Y-1)+") OR (Chunk_X = "+std::to_string(loc_X+1)+" AND Chunk_Y = "+std::to_string(loc_Y-1)+")) AND Session = "+std::to_string(current_sesion)+";";
    // ^^ Query to ask for all the modifications inside the chunk so all players can see the buildings
    int bfx = 0, bfy = 0, bfz = 0, bfm = 0;   // just some temporal variables
    mysql_query(connect, mql.c_str());        // save the changes into the result pointer
    res_set = mysql_store_result(connect);    // this is done here to prevent multiple querys in parallel 
    //std::cout<<"datos obtenidos"<<std::endl;  // which causes segmentation errors
    while((row = mysql_fetch_row(res_set))!=NULL){ // while game is receveing information
      //std::cout<<"inwhile"<<std::endl;             // show a debug message on the game
      for(int i = 0; i < 9; i++){                  // loop through all the chunk pointers
        aux4q = Wrl_Sys.sector[i];                 // save the information into a second pointer
        if(aux4q != NULL){                         // if the pointer is not null
        if(aux4q->zone_X == atoi(row[1]) && aux4q->zone_Y == atoi(row[2])){ // test if the location is valid
           bfx = atoi(row[3]);    // chunk location converted and set into a variable
           bfy = atoi(row[4]);    // chunk location in Y axis
           bfz = atoi(row[5]);    // this array conversions are made to prevent memory leaks and save memory
           bfm = atoi(row[6]);    // also for an easier game management 
           aux4q->chunk_data[bfx][bfy][bfz] = bfm; // set the modification inside the chunking system
        }
       } // close all brackets into the program to prevent problems
      }
    }
    //std::cout<<"done loading"<<std::endl; // another debug message just ignore these
    mysql_free_result(res_set);           // free the result from pointer to prevent memory leaks
    for(int i = 0; i < 100; i++){         // loop through all the stack of building
     if(stack_build_cb[i] != 0){          // then test if the modification is not null
      stack_build_cb[i] = 0;              // set to null
      mysql_query(connect, stack_build[i].c_str()); // do the query to mysql to push the new message
      stack_build[i] = "";                          // clean the stack
     }
    }
   }
   //std::cout<<"updated pos..."<<std::endl;    // debug message to tell that all processes have been completed on this thread
   q_locked = false;                          // allow multiple query's again
   }
   usleep(10*1000);                      // prevent leaks because of quick querys and stuff just a loop for the while 1
   //std::chrono::milliseconds(100);        // another method to do the delay of the function
   //std::cout<<"after chrono"<<std::endl;  // message to say that loop has finished correctly
  }
}

Player_manager *Ply_Mng = new Player_manager(); // create the object for player management 
