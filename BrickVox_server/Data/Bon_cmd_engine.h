std::string splitted[10];
void bsplit(std::string cmd2s, char div){
  int p = 0;
  for(int i = 0; i < 10; i++){splitted[i] = "";} // clean the comand split 
  for(int i = 0; i < strlen(cmd2s.c_str());i++){ // for each character on command
   //std::cout<<"reading: "<<cmd2s[i]<<std::endl;
      if(cmd2s[i] != div){                       // test if is splitting
          splitted[p] += cmd2s[i];               // if it's not then add the character into pos
      }else{                                     // otherwise
          p++;                                   // change pos
      }
  }
  //for(int i = 0; i < 10; i++){std::cout<<splitted[i]<<std::endl;}
  //exit(2);
}

void bon_push_into_cmd(std::string cmd_msg, int ig){
 //for(int i =0;i< ig;i++){cmd_msg+=".";}
 std::string tmp_s = "";
 if(strlen(cmd_msg.c_str())>23){
   for(int i = 0; i < 23; i++){
    tmp_s = tmp_s + cmd_msg[i];
   }
   cmd_msg = tmp_s;
 }
 if(tm_ptr < 100){
  if(tm_ptr<20){
   Trm_out[tm_ptr] = cmd_msg;
   tm_ptr++;
  }else{
   tm_ptr=0;
   for(int i = 0;i <  100;i++){Trm_out[i]="";}
   Trm_out[tm_ptr] = cmd_msg;
   tm_ptr++;
  }
  //oun = tm_ptr;
 }
}

void bon_push_into_java(std::string cmd_msg, int ig){
 //for(int i =0;i< ig;i++){cmd_msg+=".";}
 std::string tmp_s = "";
 if(strlen(cmd_msg.c_str())>30){
   for(int i = 0; i < 30; i++){
    tmp_s = tmp_s + cmd_msg[i];
   }
   cmd_msg = tmp_s;
 }
 if(tm_ptr < 100){
  if(tm_ptr<11){
   Jvm_out[tm_ptr] = cmd_msg;
   tm_ptr++;
  }else{
   tm_ptr=0;
   for(int i = 0;i <  100;i++){Jvm_out[i]="";}
   Jvm_out[tm_ptr] = cmd_msg;
   tm_ptr++;
  }
  //oun = tm_ptr;
 }
}

void test_cmd(std::string cmd2rd){
    bsplit(cmd2rd, ' ');
    if(strcmp(splitted[0].c_str(), "die")==0){
        std::cout<<"Program server ended!"<<std::endl;
        mysql_close(connect);
        exit(0);
    }
    // COMMAND SET SYNTAX:  set X Y Z World BlockID
    if(strcmp(splitted[0].c_str(), "set")==0){
        bon_push_into_cmd("added block in:",4);
        //bon_push_into_cmd(" > "+splitted[1]+" "+splitted[2]+" "+splitted[3]+"|",6);
        int tm_x = atof(splitted[1].c_str());
        int tm_y = atof(splitted[2].c_str());
        int tm_z = atof(splitted[3].c_str());
        int dimns= atoi(splitted[4].c_str());
        int block= atoi(splitted[5].c_str());
        get_x = (float)tm_x/15.0f;
        get_z = (float)tm_z/15.0f;
        //std::cout<<"x: "<<get_x<<" z: "<<get_z<<std::endl;exit(0);
        int chunk_x = get_x;
        int chunk_z = get_z;
        float conv_get_x = 0;
        float conv_get_z = 0;
        if(get_x<0){conv_get_x=get_x*-1;}else{conv_get_x=get_x;}
        if(get_z<0){conv_get_z=get_z*-1;}else{conv_get_z=get_z;}
        int pos_x = (conv_get_x-chunk_x)*15;
        int pos_z = (conv_get_z-chunk_z)*15;
        bon_push_into_cmd(">> cx: "+std::to_string(chunk_x)+" cz: "+std::to_string(chunk_z),0);
        bon_push_into_cmd(">> x:"+std::to_string(pos_x)+" y:"+std::to_string(tm_y)+
        " z:"+std::to_string(pos_z)+" |",0);
        std::string qry = "INSERT INTO Modifications (Chunk_X,Chunk_Y,Modif_X,Modif_Y,Modif_Z,session,Block_E)"
        " VALUES ("+std::to_string(chunk_x)+","+std::to_string(chunk_z)+","+
        std::to_string(pos_x)+","+std::to_string(tm_y)+","+std::to_string(pos_z)+","+
        std::to_string(dimns)+","+std::to_string(block)+");";
        //std::cout<<qry<<std::endl;exit(0);
        if(mysql_query(connect,qry.c_str())){
            std::cout<<mysql_errno(connect)<<std::endl;
        }
        //
    }
}
