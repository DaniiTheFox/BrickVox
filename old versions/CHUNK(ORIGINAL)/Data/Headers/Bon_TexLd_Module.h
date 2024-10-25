#include "../Textures/skybox/nx.c"
#include "../Textures/skybox/ny.c"
#include "../Textures/skybox/nz.c"
#include "../Textures/skybox/px.c"
#include "../Textures/skybox/py.c"
#include "../Textures/skybox/pz.c"

void Bon_Load_all_textures(){
 GRASS_TEXTURE = Bon_load_bmp( "Data/Textures/grass.bmp",16,48);  // using the .bmp loader
 STONE_TEXTURE = Bon_load_bmp( "Data/Textures/stone.bmp",16,48);  // load all textures to the game
 RAW_WOOD_TEXTURE = Bon_load_bmp( "Data/Textures/wood.bmp",16,48);  // using the .bmp loader
 LEAVES_TEXTURE = Bon_load_bmp( "Data/Textures/leaves.bmp",16,48);  // load all textures to the game
 SKY_TEX[0] = Bon_create_texture(nx_c.bytes_per_pixel,nx_c.width,nx_c.height, nx_c.pixel_data); // FOR EACH FACE OF SKY
 SKY_TEX[1] = Bon_create_texture(ny_c.bytes_per_pixel,ny_c.width,ny_c.height, ny_c.pixel_data); // GENERATE A TEXTURE
 SKY_TEX[2] = Bon_create_texture(nz_c.bytes_per_pixel,nz_c.width,nz_c.height, nz_c.pixel_data); // THIS IS MADE FOR THE CUBEMAP
 SKY_TEX[3] = Bon_create_texture(px_c.bytes_per_pixel,px_c.width,px_c.height, px_c.pixel_data); // NOW THAT ALL TEXTURES ARE LOADED
 SKY_TEX[4] = Bon_create_texture(py_c.bytes_per_pixel,py_c.width,py_c.height, py_c.pixel_data); // THEY MUST BE STORED INTO ARRAY
 SKY_TEX[5] = Bon_create_texture(pz_c.bytes_per_pixel,pz_c.width,pz_c.height, pz_c.pixel_data); // TO MAKE THEM POSSIBLE TO READ
 COBBLESTONE_TEXTURE = Bon_load_bmp("Data/Textures/cobblestone.bmp",16,48); // mossy cobblestone texture
 EYE_EFFECT_T = Bon_create_texture(effect1_eye.bytes_per_pixel, effect1_eye.width, effect1_eye.height, effect1_eye.pixel_data);
}
