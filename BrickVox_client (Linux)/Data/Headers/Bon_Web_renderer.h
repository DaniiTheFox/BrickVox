/*
======================================================
= CLASS THAT WILL DO THE WEB RENDERING FOR WEB PAGES =
======================================================
*/
class Web_Renderer{
 public:
 std::string web_site = "";
 std::string world_site = "";
 Web_Renderer();
 void wsearch(std::string _wurl);
};

/*
==================================
= WEB RENDERER CLASS CONSTRUCTOR =
==================================
*/
Web_Renderer::Web_Renderer(){
 
}

void Web_Renderer::wsearch(std::string _wurl){
  #ifdef linux
  std::string wurl = "lynx -dump -accept_all_cookies "+_wurl+" > ./Temporal/browsing/search";
  system(wurl.c_str());
  #endif
  std::ifstream file("./Temporal/browsing/search");
  while (std::getline(file, rd_line)){
    
  }
}
