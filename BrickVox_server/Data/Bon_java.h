void execute_machine(std::string jvm, std::string _plugin, std::string _mainclass){
 std::string java_execute = jvm + " -cp ./plugins/" + _plugin + ":./Data/BuildTools.jar:./lib/mysql-connector-java-8.0.29.jar " + _mainclass + " > ./logs/" + _plugin + ".log";
 std::cout<<java_execute<<std::endl;
 //exit(0);
 system(java_execute.c_str());
 //while(1){}
}
