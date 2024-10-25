void upload_obj_model(char *filename){                        // funcion para subir el modelo y remover codigo de MySQL -- evitar hacks
  std::fstream model_to_convert;
  model_to_convert.open(filename,std::ios::in);               // lectura del modelo desde archivo
  if(model_to_convert.is_open()){
    std::string tmp;
    while(getline(model_to_convert,tmp)){                     // obtener linea por linea del archivo
      int line_length = strlen(tmp.c_str());
      for(int i = 0; i < line_length; i++){                   // revisar la linea obtenida por el archivo
        if(tmp[i] != char(34) && tmp[i] != char(39)){         // evitar que existan comillas para acceder a los exploits en la subida
          tmp_model = tmp_model + tmp[i];
        }
      }
      tmp_model = tmp_model + '\n';                           // marcar en el string un cambio de linea
    }
   model_to_convert.close();
  }else{
   //std::cout<<"no playermodel was found..."<<std::endl;      // caso contrario para cargar un modelo por defecto o cerrar lector
  }
}

/*
===================================================================================
=  SUBIDA DE EL LINK PARA LA IMAGEN A LA BASE DE DATOS PARA SU POSTERIOR DESCARGA =
===================================================================================
*/
/*[ LOAD URL FROM FILE AND UPLOAD IT MYSQL]*/
void upload_url_ffile(char *filename){                           // lectura de url desde el archivo
 std::fstream url_file;                                          // crear variable del archivo
 url_file.open(filename, std::ios::in);                          // abrir archivo
 if(url_file.is_open()){                                         // si se pudo leer
  std::string tmp;
  while(getline(url_file, tmp)){                                 // obtener la linea del url para el skin
   for(int i = 0; i < strlen(tmp.c_str()); i++){                 // buscar comillas dentro de los caracteres para evitar inyeccion de Mysql
     if(tmp[i] != char(34) && tmp[i] != char(39)){
       tmp_linki = tmp_linki + tmp[i];                           // copiar el link al temporal
     }
   }                                                             // fin de la lectura despues se requerira subir el elemento a la base
  }
 }
}

void download_bmp_image(std::string usrnm, std::string img_url){                                      // funcion de descarga de las skins
#ifdef linux
 for(int i = 0; i < 2; i++){
 std::string cmd = "wget --output-document=tmpimg_" + usrnm + ".bmp " + img_url;    
 std::string cmv = "mv tmpimg_" + usrnm + ".bmp ./Temporal/Skins/";
 system(cmd.c_str());                                                                                 // ejecucion de los comandos
 system("clear");
 //std::cout<<"skin downloaded for user: "<<usrnm<<" with name: tmpimg_"<<usrnm<<".bmp"<<std::endl;     // mensaje de exito en descarga
 system(cmv.c_str());
 }
#endif
}

void load_obj_model(std::string _m, double mdl[9][9000], double _uv[6][9000]){// funcion de lectura de modelo desde string
 //std::cout<<"model loading.....\nmodel:\n"<<bridge<<std::endl;
 double vertices[3][9000];                                                    // array temporal de vertices
 double uvMappin[3][9000];                                                    // array temporal de mapa de textura
 char vert1[20], vert2[20], vert3[20];                                        // variables temporales para conversion
 float tmpv1 = 0, tmpv2 = 0, tmpv3 = 0;
 int vcounter = 0, tcounter = 0, bcounter = 0;                                // variables de construccion vertex,texture,build counter
 char v1[15],v2[15],v3[15];int trash;
 int cv1,cv2,cv3,cv4,cv5,cv6;
 _m = bridge;
 std::istringstream m_tmp(_m);                                                // hacer la conversion para leer linea por linea el string
 std::string tmp_line = "";                                                   // donde se almacena la linea actual
 while(std::getline(m_tmp, tmp_line)){                                        // mientras no termine de leer el archivo
  char lh[128];
  char temporal[128];                                                         // usados para el scanf general
  strcpy(temporal, tmp_line.c_str());                                         // pasar la linea a un array char temporal
  sscanf(temporal, "%s", &lh);                                                // la primera lectura para saber que esta leyendo
  if(strcmp(lh, "v") == 0){
   sscanf(temporal,"%s %s %s %s\n",&trash , &vert1, &vert2, &vert3 );         // leer los datos a convertir
   tmpv1 = atof(vert1);
   tmpv2 = atof(vert2);                                                       // conversion de los datos a flotante para almacenar en array
   tmpv3 = atof(vert3);
   vertices[0][vcounter] = tmpv1; vertices[1][vcounter] = tmpv2; vertices[2][vcounter] = tmpv3;
   vcounter++;                                                                // nueva linea en el array de vertices
  }
  if(strcmp(lh, "vt") == 0){
   sscanf(temporal,"%s %s %s\n",&trash , &vert1, &vert2 );                    // escanear los datos del mapeo de la textura por vertice
   tmpv1 = atof(vert1);
   tmpv2 = atof(vert2);                                                       // hacer la conversion a flotantes
   tmpv3 = 0;
   uvMappin[0][tcounter] = tmpv1; uvMappin[1][tcounter] = tmpv2;              // almacenar el dato
   tcounter++;                                                                // cambio de linea del array de uv map
  }
  std::string tmp = "",num1 = "",num2 = "";
  bool isL = true;
  std::string tmp2 = "",num3 = "",num4 = "";                                  // temporales para conversiones y generar el orden de el modelo
  bool isL2 = true;
  std::string tmp3 = "",num5 = "",num6 = "";
  bool isL3 = true;
  bool ns1 = true,ns2 = true,ns3 = true;
  //std::cout<<"if statement\n";
  if(strcmp(lh, "f") == 0){
  //std::cout<<"declaring temporals\n";
   sscanf(temporal, "%s %s %s %s ",&trash, &v1, &v2, &v3);
   tmp = v1;tmp2 = v2; tmp3 = v3;
   tmp = tmp+".";tmp2 = tmp2+"."; tmp3 = tmp3+".";                            // añadir un punto al final para facilitar la lectura
   sscanf(tmp.c_str() , "%i/%i", &cv1, &cv2);
   sscanf(tmp2.c_str(), "%i/%i", &cv3, &cv4);
   sscanf(tmp3.c_str(), "%i/%i", &cv5, &cv6);

   cv1--; cv2--; cv3--;
   cv4--; cv5--; cv6--;
   //std::cout<<"numbers received\n";
   _uv[0][bcounter] = uvMappin[0][cv2]+xoff2; _uv[1][bcounter] = uvMappin[1][cv2];
   mdl[0][bcounter] = vertices[0][cv1]; mdl[1][bcounter] = vertices[1][cv1]; mdl[2][bcounter] = vertices[2][cv1];

   //std::cout<<mdl[0][bcounter]<<" "<<mdl[1][bcounter]<<mdl[2][bcounter]<<std::endl;

   _uv[2][bcounter] = uvMappin[0][cv4]+xoff2; _uv[3][bcounter] = uvMappin[1][cv4];
   mdl[3][bcounter] = vertices[0][cv3]; mdl[4][bcounter] = vertices[1][cv3]; mdl[5][bcounter] = vertices[2][cv3];

   //std::cout<<mdl[3][bcounter]<<" "<<mdl[4][bcounter]<<mdl[5][bcounter]<<std::endl;

   _uv[4][bcounter] = uvMappin[0][cv6]+xoff2; _uv[5][bcounter] = uvMappin[1][cv6];
   mdl[6][bcounter] = vertices[0][cv5]; mdl[7][bcounter] = vertices[1][cv5]; mdl[8][bcounter] = vertices[2][cv5];
   
   //std::cout<<mdl[6][bcounter]<<" "<<mdl[7][bcounter]<<mdl[8][bcounter]<<std::endl;
   
                                                                          // ordenada triangulo por triangulo formando el modelo
   bcounter++;                                                            // eso se guarda en un array para simplemente dibujar al final
  }
 }
   _n = bcounter;                                                          // guardar numero de triangulos por dibujar (evitar la basura)
 // std::cout<<"valor de n: "<<_n<<std::endl;
 // std::cout<<"model loaded is...\n";
}
