#include "../Textures/skybox/nx.c"
#include "../Textures/skybox/ny.c"
#include "../Textures/skybox/nz.c"
#include "../Textures/skybox/px.c"
#include "../Textures/skybox/py.c"
#include "../Textures/skybox/pz.c"
#include "../Textures/skybox_nc/nx.c"
#include "../Textures/skybox_nc/ny.c"
#include "../Textures/skybox_nc/nz.c"
#include "../Textures/skybox_nc/px.c"
#include "../Textures/skybox_nc/py.c"
#include "../Textures/skybox_nc/pz.c"
#include "../Textures/Logo.c"
#include "../Textures/font.c"
#include "../bs_logo.c"

void Bon_Load_all_textures(){
 GRASS_TEXTURE = Bon_load_bmp( "Data/Textures/grass.bmp",64,192);  // using the .bmp loader
 DIRT_TEXTURE = Bon_load_bmp( "Data/Textures/dirt.bmp",64,192);  // using the .bmp loader
 BOOK_SHELF_TEX = Bon_load_bmp( "Data/Textures/book_shelf.bmp",64,192);       // book shelf texture
 DMNS_DOOR_TEX = Bon_load_bmp( "Data/Textures/purple_stone.bmp",64,192);        // dimensional door texture
 GLASS_TEXTURE = Bon_load_bmp( "Data/Textures/glass1.bmp",64,192);        // glass texture
 STONE_DOOR_TEX = Bon_load_bmp( "Data/Textures/stone_wall.bmp",64,192);       // stone door texture
 BRICKWALL_TEX1 = Bon_load_bmp( "Data/Textures/stone_wall2.bmp",64,192);       // brickwall texture
 SAND_TEXTURE_1 = Bon_load_bmp( "Data/Textures/sand.bmp",64,192);       // sand texture 1

 B_COLOR_TEX_RED = Bon_load_bmp( "Data/Textures/red_brick.bmp",64,192);        // color brick texture
 B_COLOR_TEX_ORG = Bon_load_bmp( "Data/Textures/orange_brick.bmp",64,192);     // color brick texture
 B_COLOR_TEX_YLW = Bon_load_bmp( "Data/Textures/yellow_brick.bmp",64,192);     // color brick texture
 B_COLOR_TEX_GRN = Bon_load_bmp( "Data/Textures/green_brick.bmp",64,192);      // color brick texture
 B_COLOR_TEX_BLE = Bon_load_bmp( "Data/Textures/blue_brick.bmp",64,192);       // color brick texture
 B_COLOR_TEX_PNK = Bon_load_bmp( "Data/Textures/pink_brick.bmp",64,192);       // color brick texture
 B_COLOR_TEX_WHT = Bon_load_bmp( "Data/Textures/white_brick.bmp",64,192);      // color brick texture
 B_COLOR_TEX_BLK = Bon_load_bmp( "Data/Textures/black_brick.bmp",64,192);      // color brick texture

 STONE_TEXTURE = Bon_load_bmp( "Data/Textures/stone.bmp",64,192);  // load all textures to the game
 PLANT_TEXTURE = Bon_load_bmp( "Data/Textures/plant.bmp",128,128);  // load all textures to the game
 WATER_ENVMAPR = Bon_load_bmp( "Data/Textures/envMaps/water.bmp", 256,256); // load the envmap for water
 WATER_TEXTURE = Bon_load_bmp( "Data/Textures/water.bmp", 64,64);    // water texture importing
 RAW_WOOD_TEXTURE = Bon_load_bmp( "Data/Textures/wood.bmp",64,192);  // using the .bmp loader
 PLK_WOOD_TEXTURE = Bon_load_bmp( "Data/Textures/wplanks.bmp",64,192);  // using the .bmp loader
 LEAVES_TEXTURE = Bon_load_bmp( "Data/Textures/leaves.bmp",128,128);  // load all textures to the game
 SKY_TEX[0] = Bon_create_texture(nx_c.bytes_per_pixel,nx_c.width,nx_c.height, nx_c.pixel_data); // FOR EACH FACE OF SKY
 SKY_TEX[1] = Bon_create_texture(ny_c.bytes_per_pixel,ny_c.width,ny_c.height, ny_c.pixel_data); // GENERATE A TEXTURE
 SKY_TEX[2] = Bon_create_texture(nz_c.bytes_per_pixel,nz_c.width,nz_c.height, nz_c.pixel_data); // THIS IS MADE FOR THE CUBEMAP
 SKY_TEX[3] = Bon_create_texture(px_c.bytes_per_pixel,px_c.width,px_c.height, px_c.pixel_data); // NOW THAT ALL TEXTURES ARE LOADED
 SKY_TEX[4] = Bon_create_texture(py_c.bytes_per_pixel,py_c.width,py_c.height, py_c.pixel_data); // THEY MUST BE STORED INTO ARRAY
 SKY_TEX[5] = Bon_create_texture(pz_c.bytes_per_pixel,pz_c.width,pz_c.height, pz_c.pixel_data); // TO MAKE THEM POSSIBLE TO READ
 NSKY_TEX[0] = Bon_create_texture(nx_nc.bytes_per_pixel,nx_nc.width,nx_nc.height, nx_nc.pixel_data); // FOR EACH FACE OF SKY WITHOUT CLOUDS
 NSKY_TEX[1] = Bon_create_texture(ny_nc.bytes_per_pixel,ny_nc.width,ny_nc.height, ny_nc.pixel_data); // GENERATE A TEXTURE
 NSKY_TEX[2] = Bon_create_texture(nz_nc.bytes_per_pixel,nz_nc.width,nz_nc.height, nz_nc.pixel_data); // THIS IS MADE FOR THE CUBEMAP
 NSKY_TEX[3] = Bon_create_texture(px_nc.bytes_per_pixel,px_nc.width,px_nc.height, px_nc.pixel_data); // NOW THAT ALL TEXTURES ARE LOADED
 NSKY_TEX[4] = Bon_create_texture(py_nc.bytes_per_pixel,py_nc.width,py_nc.height, py_nc.pixel_data); // THEY MUST BE STORED INTO ARRAY
 NSKY_TEX[5] = Bon_create_texture(pz_nc.bytes_per_pixel,pz_nc.width,pz_nc.height, pz_nc.pixel_data); // TO MAKE THEM POSSIBLE TO READ
 BVOX_LOGO =  Bon_create_texture(bvox_logo.bytes_per_pixel,bvox_logo.width,bvox_logo.height, bvox_logo.pixel_data); // JUST MY LOGO
 BVOX_FONT =  Bon_create_texture(font_tex.bytes_per_pixel,font_tex.width,font_tex.height, font_tex.pixel_data); // THE INGAME FONT
 COBBLESTONE_TEXTURE = Bon_load_bmp("Data/Textures/cobblestone.bmp",64,192); // mossy cobblestone texture
 MCOBBLESTONE_TEXTURE = Bon_load_bmp("Data/Textures/cobblestone2.bmp",64,192); // mossy cobblestone texture
 EYE_EFFECT_T = Bon_create_texture(effect1_eye.bytes_per_pixel, effect1_eye.width, effect1_eye.height, effect1_eye.pixel_data);
 BON_BS_LOGO = Bon_create_texture(bs_logo.bytes_per_pixel,bs_logo.width,bs_logo.height, bs_logo.pixel_data); // LOAD BONI LOGO
}
