void Bon_code_service(int _obj2s){
 bool willrun = true;
 while(isRunning2==false){/*std::cout<<"waiting for program to start...."<<std::endl;*/usleep(150*1000);}//std::chrono::milliseconds(300);}
 //std::cout<<"\e[1;33m SERVICE "<<_obj2s<<" FOR SCRIPTING HAS BEEN ENABLED\e[0m;"<<std::endl;
 if(_obj2s>obj_num){willrun=false;}
 if(willrun==true){
 object_array[_obj2s].Start_code_main();
 object_array[_obj2s].Update_code();
 }
}
