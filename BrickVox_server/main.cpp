/*
=========================================
= BRICKVOX SERVER PROGRAM BY: BONIIKWDZ =
=========================================
*/
// --- [ THE MAIN LIBRARIES NEEDED ] ------
#include <mysql/mysql.h>
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <string.h> 
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <thread>
#include <future>
#include <chrono>
#include <iomanip>
#include <time.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <random>
// --- [ OTHER RESOURCES REQUIRED ]  ------
#include "Data/Bon_graph.h"
// --- [ MAIN VARIABLE DEFINITION ] -------
Bs_cmd_graph *screen = new Bs_cmd_graph(60,22,35);
std::string cmd = "";
MYSQL *connect;
 
std::string Trm_out[100];
std::string Jvm_out[100];

std::thread plugin_execute[200];

int p_ptr = 0;

int tm_ptr;
double get_x, get_z;
// ---------------------------------
#include "Data/Bon_cmd_engine.h"
#include "Data/Bon_java.h"
/*
---------------------------------------
- MAIN FUNCTION OF THE SERVER PROGRAM -
---------------------------------------
*/
int main(int argc, char** argv){
 connect = mysql_init(NULL);                                 // START THE MYSQL OBJECT
 if(!connect){                                               // IF THE SERVER WAS NOT ABLE TO BE FOUND
  std::cout<<"could not start mysql client...\nERROR: ";     // SHOW THE ERROR MESSAGE WITH THE CRASH
  std::cout<<mysql_errno(connect)<<std::endl;                // crash 
  exit(1);                                                   // EXIT THE GAME
 }
 std::string SERVER = "";
 std::string USER = "";
 std::string PASS = "";
 std::string DBCP = "";
 
 std::string _auth = "";
 
 char *filename = "loginCredentials.auth";
 std::ifstream file(filename);
 
 std::string file_content;
 while(std::getline(file, file_content)){
  _auth = _auth + file_content + "\n";
 }
 
 std::istringstream m_tmp(_auth);  
 std::string tmp_line = "";          
                                                                               // donde se almacena la linea actual
 while(std::getline(m_tmp, tmp_line)){                                        // mientras no termine de leer el archivo
  char temporal[128];     
  char credential[128];
  char data[128];
  strcpy(temporal, tmp_line.c_str()); 
  sscanf(temporal, "%s %s", &credential, &data);
  // -------------------------------------------- 
  if(strcmp(credential, "h") == 0){SERVER= data;}
  if(strcmp(credential, "u") == 0){USER  = data;}
  if(strcmp(credential, "p") == 0){PASS  = data;}
  if(strcmp(credential, "d") == 0){DBCP  = data;}
  // --------------------------------------------
 }
 if(!mysql_real_connect(connect, SERVER.c_str(), USER.c_str(), PASS.c_str(), DBCP.c_str(), 3306, NULL,0)){
  std::cout<<"Could not connect to server\nERROR: ";          // SHOW THE ERROR MESSAGE WITH THE CRASH
  std::cout<<mysql_errno(connect)<<std::endl;                 // crash 
  exit(1);                                                    // EXIT THE SERVER
 }else{
     std::cout<<"connected"<<std::endl;
 }
 
 bon_push_into_cmd("started connection....",7);
 
 // ----------------------------------------------------
 //        INITIALIZE ALL THE PLUGINS FOR THE GAME
 // ----------------------------------------------------
  std::string jvm_path = "java";
 
  char *pluginfile = "plugin.cfg";
  std::ifstream pfile(pluginfile);
 
  std::string _plugins = "";
  
  std::string pfile_content;
  while(std::getline(pfile, pfile_content)){
   _plugins = _plugins + pfile_content + "\n";
  }
 
 // std::cout<<_plugins<<std::endl; exit(1);
 
  bon_push_into_java("Plugin system is enabled.",4);
 
  std::istringstream p_tmp(_plugins);  
  std::string tmp_linep = "";          
                                                                               // donde se almacena la linea actual
  while(std::getline(p_tmp, tmp_linep)){                                        // mientras no termine de leer el archivo
   char ctemporal[128];   
   char plugin_instr[128];  
   char plugin_jname[128];
   char plugin_jmain_class[128];
   strcpy(ctemporal, tmp_linep.c_str()); 
   sscanf(ctemporal, "%s %s %s", &plugin_instr, &plugin_jname, &plugin_jmain_class);
   // -------------------------------------------- 
   if(strcmp(plugin_instr, "connect") == 0){
    std::string Java_class = plugin_jmain_class;
    std::string Java_plugin= plugin_jname;
    plugin_execute[p_ptr] = std::thread(execute_machine,jvm_path, Java_plugin, Java_class);
    bon_push_into_java("Enabled: " + Java_plugin,7);
    bon_push_into_java("Class: " + Java_class,7);
    p_ptr++;
   }
   
   if(strcmp(plugin_instr, "jvm") == 0){
    jvm_path = plugin_jname;
    bon_push_into_java("java virtual machine path:",7);
    bon_push_into_java("set:" + jvm_path,7);
   }
   
   // --------------------------------------------
  }
  
  bon_push_into_java("java plugins enabled. ",7);
 // ----------------------------------------------------
 
 screen->Bs_cmd_clear();
 while(1){
  screen->Bs_draw_line(0 ,0 ,25,0   ,32);
  screen->Bs_draw_line(0 ,21,26,21  ,32);
  screen->Bs_draw_line(0 ,0 ,0 ,21  ,32);
  screen->Bs_draw_line(25,0 ,25,21  ,32);

  screen->Bs_draw_line(26,0 ,59,0  ,36);
  screen->Bs_draw_line(26,12,60,12 ,36);
  screen->Bs_draw_line(26,0 ,26,12 ,36);
  screen->Bs_draw_line(59,0 ,59,12 ,36);
  for (int i = 0; i < 19; i++){
      screen->Bs_draw_text(1,1+i,Trm_out[i],0);
  }
  for (int i = 0; i < 10; i++){
      screen->Bs_draw_text(28,0+i,Jvm_out[i],0);
  }
  screen->Bs_cmd_draw();
  std::cout<<"\e[1;33m>> \e[0m";std::getline(std::cin, cmd);
  //std::cin>>cmd;
  test_cmd(cmd);
  usleep(33);
  screen->Bs_cmd_clear();
 }
 return 0;
}
/*
□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
□□□■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□■■□□□□□■□
□□■■■■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□■■■□□■□□□□■■□□□■■■□□■■□□□□■□□□□■■□□□□□□■■■□□□■□□
□□□■■■■□□□□□□□□□□□□□□□□□□□□□□■□□□□□■□□■□■□■■□□□□□■□□□■□■■□□■□■□□□□■■□□□□□□□□■■□□■□□
□□□■■■■■■□□□□□□□□□□□□□□□□■■■■■□□□□□■□□■□■■□□□■■□□■□□□■□■■□■□□□■□□■■□□□■■■□□□□■■■□□□
□□□■■■□□□■□□□□□□□□□□■■■■■■■■■■■□□□□■■■□□■□□□□■■□■□□□□□□■■□■□□□■□□■■□□■□□□■□□□□■■□□□
□□□■■□□□□□■□□□□□□□□■■□□□■■■■■■■□□□□■□□■□■□□□□■■□■□□□□□□■■■□□□□■□■■□□□■□□□■□□□■■■■□□
□□□■□□■■□□□■■□□□□□■□□□■□□□■■■■■□□□□■□□■□■□□□□■■□□■□□□■□■■□■□□□■□■■□□□■□□□■□□□■□■■□□
□■■□□□■□□□□□□■□□■■□□■■□□■■■□□■■□□□□■□□■□■□□□□■■□□■□□□■□■■□■□□□□■■□□□□■□□□■□□■□□□■■□
□■■□□□□■□□□□□□■□□□□■■□□□□□■□□■■□□□□■■■□□■□□□□■■□□□■■■□□■■□□■□□□■■□□□□□■■■□□□□□□□□□□
□□■■□□■□□□□□□■■■■■■□□□□□□■■□□□■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
□□■□□□■■□□□■■■■■■■■■□□□□□□■□□□■□□□□■■■■□■■■■■□■■■□□■□□□□□■■□■■■■■□■■■□□□□□□□□□□□□□□
□□■■■□□□□■■■■■■■■■■■■■□□■■■□□□■□□□□■□□■□■□□□□□■□□■□■□□□□□■■□■□□□□□■□□■□□□□□□□□□□□□□
□□□□■□■■■■■■■■■■■■■■■■■□□□□□□■■□□□□■□□■□■□□□□□■□□■□□■□□□■■□□■□□□□□■□□■□□□□□□□□□□□□□
□□□□■□□□■■■■■■■■■■■■■■■■■□□□■□□□□□□■□□□□■■■■□□■□□■□□■□□□■■□□■■■■□□■□□■□□□□□□□□□□□□□
□□□□■■□□□■■■■■■■■■■■■■■■■□□□■□□□□□□■■■■□■□□□□□■■■□□□□■□□■□□□■□□□□□■■■□□□□□□□□□□□□□□
□□□■□□■■■■■■■■■■■■■■■■■■■□□■□□□□□□□□□□■□■□□□□□■□□■□□□■□■■□□□■□□□□□■□□■□□□□□□□□□□□□□
□□□■□■□□■□■■■■■■■■■■■■■■■■□■□□□□□□□■□□■□■□□□□□■□□■□□□■□■□□□□■□□□□□■□□■□□□□□□□□□□□□□
□□□■□■□□■□■■■■■■■■■■■■■■■■■□□□□□□□□■□□■□■□□□□□■□□□■□□□■■□□□□■□□□□□■□□□■□□□□□□□□□□□□
□□□■■□■■□■□■■■■■■■■■■■■■■■■□□□□□□□□■■■■□■■■■■□■□□□■□□□■□□□□□■■■■■□■□□□■□□□□□□□□□□□□
□□□□■□□■□■□□■■■□□□■■■■■■■■■■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
□□□□□■■■■■□□■■■□□□■■■□■□■■■■□□□□□□□■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■□□
□□□□□■■■■■□□■■■□□□■■■□■□□■■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
□□□□□■■□□■□□■■■□□□■■■□■■□□■□□□□□□□□■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■□□□□
□□□□□■■■□■□□□□□■■■□□□□■□□■■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
□□□□□■□□□□□□□□□□□□□□□□□□■■□□□□□□□□□□□□□□□□□□□■□□□□□□□□□□■□■□■□■□■□□□■□■■□□■■□□□□□□□
□□□□□■■■□□□□□□□□■□□□□□□□□□■□□□□□□□□■□□■□■□■□□■■□□■■□□■■□□□■□■■□□■□■□■□■□■□□■□□□□□□□
□□□□□■■■■□□□□□□□□□□□□□□■■■■□□□□□□□□■■□■■■□□□□■□■□■■□■□■□■□□□■□■□■□■□■□■□■□■□□□□□□□□
□□□□□■■■■■■■■■■■■■■■■■■■■■■□□□□□□□□■□■□□■□■□□■■□□■■□■□■□■□■□■□■□□■□■□□■■□□■■□□□□□□□
□□□□□■■■■■■■■■■□□□■■■■■■■■■□□□□□□□□■■□■■■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
□□□□■■■■■■■■■□□□■□□□■■■■■■■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
□□□□■■■■■■■■■□□■□□■□□■■■■■■□□□□□□□□■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■□□□□□□□
□□□■■■■■■■■■□□■□□□■□□■■■■■■■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
*/
