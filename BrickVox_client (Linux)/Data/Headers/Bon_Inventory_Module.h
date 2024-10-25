/*
=============================================================================
=    FUNCTION THAT GENERATES THE DRAWING OF INVENTORY (CONTROLS SEPARATELY) =
=============================================================================
*/
void Bon_draw_inventory(){
 glPushMatrix();
 glColor4f(0.044705882,0.044705882,0.044705882,0.5);
 glBegin(GL_QUADS);
  glVertex2f(128, 64);
  glVertex2f(BON_SCREEN_W-128, 64);
  glVertex2f(BON_SCREEN_W-128, BON_SCREEN_H-164);
  glVertex2f(128, BON_SCREEN_H-164);
 glEnd();
 glPopMatrix();
 glPushMatrix();
  glColor4f(1.0f,0.0f,0.0f,0.5f);
   glBegin(GL_QUADS);
    glVertex2f(128, 64+(pointer_inv*16));
    glVertex2f(BON_SCREEN_W-128, 66+(pointer_inv*16));
    glVertex2f(BON_SCREEN_W-128, 80+(pointer_inv*16));
    glVertex2f(128, 80+(pointer_inv*16));
   glEnd();
 glPopMatrix();
 items_n = (((BON_SCREEN_H-164)-64)/16);
 for(int i = 0; i < items_n; i++){
  if(i < array_limit){
   RenderString(143,78+(i*16), Objects4List[block_selecting+i].c_str(), 1.0f, 1.0f, 1.0f);
  }else{
   RenderString(143,78+(i*16), "empty slot", 1.0f, 1.0f, 1.0f);  
  }
 }
 if(pointer_inv > items_n-1){
  pointer_inv = 0;
  block_selecting+=items_n;
 }          
 if(pointer_inv < 0){
  pointer_inv = items_n-1;
 }
}