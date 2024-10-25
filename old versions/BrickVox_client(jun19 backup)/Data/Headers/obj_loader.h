int aux_vnum = 0;

int b_load_obj_model(char *filename, double mdl[9][1000], double _uv[6][1000], int _n){// funcion de lectura de modelo desde string
 //std::cout<<"model loading.....\nmodel:\n"<<bridge<<std::endl;
 std::string _m = "";
 std::ifstream file(filename);
 std::string file_content;
 while(std::getline(file, file_content)){
  _m = _m + file_content + "\n";
 }
 //std::cout<<_m<<"\nloaded"<<std::endl;
 double vertices[3][9000];                                                    // array temporal de vertices
 double uvMappin[3][9000];                                                    // array temporal de mapa de textura
 char vert1[20], vert2[20], vert3[20];                                        // variables temporales para conversion
 float tmpv1 = 0, tmpv2 = 0, tmpv3 = 0;
 int vcounter = 0, tcounter = 0, bcounter = 0;                                // variables de construccion vertex,texture,build counter
 char v1[15],v2[15],v3[15];int trash;
 int cv1,cv2,cv3,cv4,cv5,cv6;
 //_m = bridge;
 //std::cout<<_m<<std::endl;
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
   
   //std::cout<<"string readed\n";
   ns1 = true;ns2 = true;ns3 = true;
   isL = true; isL2 = true; isL3 = true;                                   //cuando la conversion finaliza se procede a crear numeros enteros
   /*
   cv1 = atoi(num1.c_str())-1; cv2 = atoi(num2.c_str())-1; cv3 = atoi(num3.c_str())-1;
   cv4 = atoi(num4.c_str())-1; cv5 = atoi(num5.c_str())-1; cv6 = atoi(num6.c_str())-1;*/
   sscanf(tmp.c_str() , "%i/%i", &cv1, &cv2);
   sscanf(tmp2.c_str(), "%i/%i", &cv3, &cv4);
   sscanf(tmp3.c_str(), "%i/%i", &cv5, &cv6);

   cv1--; cv2--; cv3--;
   cv4--; cv5--; cv6--;
  // exit(1);
   //std::cout<<"numbers received\n";
   _uv[0][bcounter] = uvMappin[0][cv2]; _uv[1][bcounter] = uvMappin[1][cv2];
   mdl[0][bcounter] = vertices[0][cv1]; mdl[1][bcounter] = vertices[1][cv1]; mdl[2][bcounter] = vertices[2][cv1];

   //std::cout<<mdl[0][bcounter]<<" "<<mdl[1][bcounter]<<mdl[2][bcounter]<<std::endl;

   _uv[2][bcounter] = uvMappin[0][cv4]; _uv[3][bcounter] = uvMappin[1][cv4];
   mdl[3][bcounter] = vertices[0][cv3]; mdl[4][bcounter] = vertices[1][cv3]; mdl[5][bcounter] = vertices[2][cv3];

   //std::cout<<mdl[3][bcounter]<<" "<<mdl[4][bcounter]<<mdl[5][bcounter]<<std::endl;

   _uv[4][bcounter] = uvMappin[0][cv6]; _uv[5][bcounter] = uvMappin[1][cv6];
   mdl[6][bcounter] = vertices[0][cv5]; mdl[7][bcounter] = vertices[1][cv5]; mdl[8][bcounter] = vertices[2][cv5];
   
   //std::cout<<mdl[6][bcounter]<<" "<<mdl[7][bcounter]<<mdl[8][bcounter]<<std::endl;
   
                                                                          // ordenada triangulo por triangulo formando el modelo
   bcounter++;                                                            // eso se guarda en un array para simplemente dibujar al final
  }
 }
  return bcounter;                                                          // guardar numero de triangulos por dibujar (evitar la basura)
  //std::cout<<"valor de n: "<<_n<<std::endl;
  //std::cout<<"model loaded is...\n";
}

void Bon_draw_obj_l( double vert_map[9][1000], double uv_map[6][1000],int vert_num, GLuint Texture){
  glPushMatrix();
   //glTranslatef(lx, ly, lz);
   glBindTexture(GL_TEXTURE_2D, Texture);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_TRIANGLES);
    for(int i = 0; i < vert_num; i++){
     glTexCoord2f(uv_map[0][i]+xoff2, uv_map[1][i]);                         // -
     glVertex3f(vert_map[0][i], vert_map[1][i], vert_map[2][i]);       //  |
                                                                       //  |
     glTexCoord2f(uv_map[2][i]+xoff2, uv_map[3][i]);                         //  | texture mapping
     glVertex3f(vert_map[3][i], vert_map[4][i], vert_map[5][i]);       //  | and vertex
                                                                       //  |
     glTexCoord2f(uv_map[4][i]+xoff2, uv_map[5][i]);                         //  |
     glVertex3f(vert_map[6][i], vert_map[7][i], vert_map[8][i]);       // -
    }
   glEnd();
  glPopMatrix();
}
