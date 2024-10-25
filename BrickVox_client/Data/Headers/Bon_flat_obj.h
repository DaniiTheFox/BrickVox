class Flat_v{
 private:
  float rh,rv;
  float scala;
 public:
  std::string oname = "default";
  int bs_id = 10;
  std::string excode = "";
  std::string code[1000];
  std::string var_name[1000];
  int var_value[1000];
  int var_ptr = 0;
  bool is_running = true;
  int exptr = 0;
  GLuint tex_cust = 0;
  int lenc = 0;
  void Flat_ini(float _scala, std::string _url, std::string _nme, int _oid, std::string _cod);
  void Update_code();
  void Start_code_main();
  void DrawFlatLookAt(int x, int y, int z,float lx,float ly,float lz);
  void runln(std::string script_cmd);
};

void Flat_v::Flat_ini(float _scala, std::string _url, std::string _nme, int _oid, std::string _cod){
 scala = _scala;
 bs_id = _oid;
 bool is_func = false;
 oname = _nme;
 excode = _cod;
 for(int i = 0; i < strlen(oname.c_str()); i++){
  if(_nme[i]==' '){
   _nme[i]='_';
  }
 }
 #ifdef linux
  for(int i = 0; i < 2; i++){
   std::string cmd2 = "wget --output-document=tmpimg_" + _nme + " " + _url;    
   std::string cmv2 = "mv tmpimg_" + _nme + " ./Temporal/Addons/";
   system(cmd2.c_str());                                                                                 // ejecucion de los comandos
   system("clear");
   //std::cout<<"addon downloaded for object: "<<_nme<<" with name: tmpimg_"<<_nme<<".bmp"<<std::endl;     // mensaje de exito en descarga
   system(cmv2.c_str());
  }
 #endif
 std::string imgtm = "./Temporal/Addons/tmpimg_" + _nme ; // get the downloaded texture from player
 char *lnk = new char[strlen(imgtm.c_str())+1];    // create a tiny temporal pointer with the directory 
 strcpy(lnk, imgtm.c_str());                       // transform into other var type 
 tex_cust = Bon_load_bmp(lnk, 64, 64);           // load the player texture as .bmp into the game
 delete lnk;
 int codesize = strlen(excode.c_str());
 int lptr = 0;
 for(int i = 0; i < codesize; i++){
  if(excode[i]==';'||excode[i]==':'){
  lptr++;
  }else{
    code[lptr] = code[lptr] + excode[i]; 
  }
 }
 lenc = lptr;
 for(int i = 0; i < lptr;i++){
  if(strcmp("fnc setup",code[i].c_str()) == 0){
   exptr = i;
   break;
  }
  if(i == lenc-1){
   exptr=1001;
  }
 }
 for(int i = 0; i < lenc; i++){
  //std::cout<<"line: "<<i<<"| "<<code[i]<<std::endl;
 }
 while((strcmp(code[exptr].c_str(),"endfnc") != 0)&&exptr<1000){
  //std::cout<<"inloop of code"<<std::endl;
  runln(code[exptr]);
  exptr++;
  //std::cout<<"line: "<<exptr<<std::endl;
 }
}

void Flat_v::Start_code_main(){
 for(int i = 0; i < 1000; i++){
   code[i] = "";
 }
 int codesize = strlen(excode.c_str());
 int lptr = 0;
 for(int i = 0; i < codesize; i++){
  if(excode[i]==';'||excode[i]==':'){
  lptr++;
  }else{
    code[lptr] = code[lptr] + excode[i]; 
  }
 }
 lenc = lptr;
 for(int i = 0; i < lptr;i++){
  if(strcmp("fnc main",code[i].c_str()) == 0){
   exptr = i;
   break;
  }
  if(i == lenc-1){
   exptr=1001;
  }
 }
}

void Flat_v::Update_code(){
 //for(int i = 0; i < lenc; i++){
 // std::cout<<"line: "<<i<<"| "<<code[i]<<std::endl;
 //}
 while((strcmp(code[exptr].c_str(),"endfnc") != 0)&&exptr<1000){
  //std::cout<<"inloop of code"<<std::endl;
  runln(code[exptr]);
  exptr++;
  usleep(300*1000);std::chrono::milliseconds(300);
  //std::cout<<"line: "<<exptr<<std::endl;
 }
}

void Flat_v::DrawFlatLookAt(int x, int y, int z,float lx,float ly,float lz){
 float tmpa = ((atan2((lx-x),(lz-z))*180)/3.14159);
 if(tmpa < 0){
  tmpa += 360;
 }
 //std::cout<<tmpa<<"\n";
 float tmya = 0;
 glPushMatrix();
  glTranslatef(x,y,z);
  glRotatef(tmpa,tmya,tmpa,1);
  glBindTexture(GL_TEXTURE_2D, tex_cust);
  glBegin(GL_QUADS);
  glTexCoord2d(0,0);
  glVertex3f(-scala,scala,0);
  glTexCoord2d(0,-1);
  glVertex3f(-scala, -scala,0);
  glTexCoord2d(1,-1);
  glVertex3f( scala, -scala,0);
  glTexCoord2d(1,0);
  glVertex3f( scala,scala,0);
  glEnd();
  /*glDisable(GL_TEXTURE_2D);
   glutWireCube(1);
  glEnable(GL_TEXTURE_2D);*/
 glPopMatrix();
}

Flat_v object_array[100];
int obj_num = 0;

void set_onInv(){
  for(int i = 0; i < obj_num; i++){
   //std::cout<<"\e[1;32m"<<object_array[i].oname<<"\e[0m;"<<std::endl;
   Objects4List[array_limit] = object_array[i].oname;
   array_limit++;
  }
}
