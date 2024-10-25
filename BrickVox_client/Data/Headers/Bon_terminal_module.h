void Bon_draw_terminal(){
 glPushMatrix();
 glColor4f(0.044705882,0.044705882,0.044705882,0.5);
 glBegin(GL_QUADS);
  glVertex2f(128, 64);
  glVertex2f(BON_SCREEN_W-128, 64);
  glVertex2f(BON_SCREEN_W-128, BON_SCREEN_H-164);
  glVertex2f(128, BON_SCREEN_H-164);
 glEnd();
 glPopMatrix();

 out_n = (((BON_SCREEN_H-164)-64)/16);
 for(int i = out_n; i > 0; i--){
  if(i < 100 && i < oun){
   RenderString(143,78+(i*16), Trm_out[i].c_str(), 1.0f, 1.0f, 1.0f);
  }
 }
}

void bon_push_into_cmd(std::string cmd_msg){
 if(tm_ptr < 100){
  if(tm_ptr<out_n){
   Trm_out[tm_ptr] = cmd_msg;
   tm_ptr++;
  }else{
   tm_ptr=0;
   Trm_out[tm_ptr] = cmd_msg;
   tm_ptr++;
  }
  oun = tm_ptr;
 }
}
