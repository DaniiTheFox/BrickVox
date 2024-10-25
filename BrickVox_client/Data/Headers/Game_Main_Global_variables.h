// -------------------KEY SCREEN POSITIONS AND SIZE ---------------------
int BON_SCREEN_W = 641;         // SCREEN SIZE VARIABLES ON X AXIS
int BON_SCREEN_H = 480;         // SCREEN SIZE VARIABLES ON Y AXIS
// --------------- HEALTH STATISTICS FOR THE PLAYER ---------------------
int p_health = 100;
// --------------- SELF PLAYER POSITION ON GAME -------------------------
float px = 8, py = 51, pz = 8; // player position
float cx = 0, cy = 0, cz = 0;  // camera rotation
float angle = 180, angl2 = 0;  // player angles
float user_speed = 0.50;       // player speed
int loc_X = 0,loc_Y = 0;       // greater location in player (current chunk where player is)
int opx = 8,opy = 8;           // greater scale of old player position (used for knowing when should a new chunk be generated)
// ---[ THIRD PERSON VARIABLES ]---
bool is_tpv = false;                // variable to define if it's on third person view
double self_model[9][9000];         // model data of self player
double    self_uv[6][9000];         // UV data of self player
double hand_mdl[9][1000];
double hand_uvs[6][1000];
int h_vnum = 0;
int s_vnum = 0;
GLuint selft_text;                  // texture of the player
int pe = 0; int pa = 0;
bool up=false,down=false,left=false,right=false;
float nx,ny,nz,tx,tz;
int zoom = 3;
bool debug = false;
int old_mx,old_my;
// ------------- RAYCASTER PTR DATA VARIABLES FOR BUILDING INGAME -------
float ox=px,oz=pz; float dx,dz; int cox,coz;
float rx,ry,rz;int zom = 6;
// ------------- TEXTURE IDENTIFIERS VARIABLES --------------------------
GLuint GRASS_TEXTURE;        // just some variables and constants
GLuint COBBLESTONE_TEXTURE;  // for the different textures generations 
GLuint MCOBBLESTONE_TEXTURE;  // for the different textures generations 
GLuint DIRT_TEXTURE;         // and also these are needed
GLuint STONE_TEXTURE;        // to identify
GLuint WATER_TEXTURE;        // which texture is enabled
GLuint WATER_ENVMAPR;        // the env mapping for water
GLuint PLANT_TEXTURE;        // which texture is enabled
GLuint SKY_TEXTURE;          // and assigned to each item

GLuint BOOK_SHELF_TEX;       // book shelf texture
GLuint DMNS_DOOR_TEX;        // dimensional door texture
GLuint GLASS_TEXTURE;        // glass texture
GLuint STONE_DOOR_TEX;       // stone door texture
GLuint BRICKWALL_TEX1;       // brickwall texture
GLuint SAND_TEXTURE_1;       // sand texture 1

GLuint B_COLOR_TEX_RED;      // color brick texture
GLuint B_COLOR_TEX_ORG;      // color brick texture
GLuint B_COLOR_TEX_YLW;      // color brick texture
GLuint B_COLOR_TEX_GRN;      // color brick texture
GLuint B_COLOR_TEX_BLE;      // color brick texture
GLuint B_COLOR_TEX_PNK;      // color brick texture
GLuint B_COLOR_TEX_WHT;      // color brick texture
GLuint B_COLOR_TEX_BLK;      // color brick texture

GLuint EYE_EFFECT_T;         // effect of the eye
GLuint RAW_WOOD_TEXTURE;     // wood tree texture
GLuint PLK_WOOD_TEXTURE;     // wood plank texture
GLuint LEAVES_TEXTURE;       // effect of the eye
GLuint BVOX_LOGO;            // effect for showing the logo
GLuint BVOX_FONT;            // brickvox font
GLuint BON_BS_LOGO;          // bonisoft logo on load screen
//-------------- SKY POSITIONS TEXTURES FOR SKYBOX -----------------------
GLuint SKY_TEX[6]; //-- negative x
GLuint NSKY_TEX[6]; //-- negative x
// ------------- TEXTURE OFFSET FOR FIXING THE LOAD ----------------------
float xoff  = 0;  //1.16;           // offset -- used for texture correction (it's a constant fount thats the correction on repeating texture)
float xoff2 = 0;  //0.39;           // offset -- used for texture correction (it's a constant fount thats the correction on repeating texture)
// ------------- VARIABLES TO CONNECT WITH MYSQL SERVER TO LOAD BUILDINGS FROM A BASE --------------------------
#define DBCP   "Voxel_World"                   
// -------------- THE MYSQL POINTER THAT WILL BE USEFUL DURING ALL PROGRAM EXECUTION --------------------------
MYSQL *connect;
MYSQL_RES *res_set;
MYSQL_RES *res_set_players;
MYSQL_ROW row;
MYSQL_ROW row2;
// -------------- MULTIPLAYER SKIN SYSTEM BASES AND VARIABLES --------------------------------------------------
std::string tmp_model = "";                                  // temporal variable of the .obj (same objetive)
std::string tmp_linki = "";                                  // temporal vatiable of the  url (same objetive)
std::string tmp_username = "";                               
int _n = 0, jnt = 0;
std::string bridge;           // UV data
std::string req;
// -------------- DEBUG VARIABLES -------------------------------------
bool isRunning = false;
bool isRunning2= false;
bool lock_query = false;
bool q_locked = false;
bool ctx_menu = false;
/*
==================================================================================
=   LOCAL DATABASE MANAGER TO AVOID MULTIPLE QUERY ON MYSQL AND AVOID CRASHES    =
==================================================================================
*/

// =================== [ PLAYER TABLE IN GAME ] =======================
int players_i[100];         // +----+---+---+---+---+-----+-----+
float players_x[100];       // | ID | X | Y | Z | R | MDL | URL |
float players_y[100];       // +----+---+---+---+---+-----+-----+
float players_z[100];       //      THIS IS THE CREATION OF A
int players_r[100];         //    TEMPORAL DATABASE INSIDE THE GAME
int players_j[100];         //  ---------------------------------------
std::string play_mdl[100];  //   TO AVOID REQUEST ON THE OTHER THREAD
std::string play_url[100];  //  AND PREVENT THE SEGMENTATION ERRORS AND CRASHES
std::string play_usr[100];  // 
int data_number_p = 0;

// ================ [ CHAT TABLE OF PLAYERS ] =======================
std::string chat_messages[7];
std::string chat_tosend;
bool is_toggled = true;
bool has_terminal=false;
bool is_texting = false;
int msg_count = 0;
std::string msg;
std::string msg2cls;
// =============== [ MOTION VARIABLES ] =============================
float gmov = 0; bool grch = false;

//=============== [ PILE FOR CONSTRUCTION ] ========================
std::string stack_build[100]; int stack_build_cb[100];

// ================= [ INVENTORY VARIABLES ] =======================
std::string Objects4List[100] = {"[ MATERIAL INVENTORY ]","GRASS", "STONE", "RED BRICKS", "WOOD FROM TREE", "LEAVES", "PLANTS", "TREE BASE", "MOSSY COBBLESTONE","WOODEN PLANKS","BOOK SHELF","DIMENSIONAL DOOR","GLASS","STONE DOOR","BRICK WALL","SAND","RED BRICK","ORANGE BRICK","YELLOW BRICK","GREEN BRICK","BLUE BRICK","PINK BRICK","WHITE BRICK","BLACK BRICK","DIRT","SIMPLE RED LIGHT","SIMPLE BLUE LIGHT","SIMPLE GREEN LIGHT","WATER PLANE"};
bool has_inventory = false;
int  current_block = 3;
int  block_selecting = 0; // +15
int  array_limit = 29;
int  pointer_inv = 2;
int  pointer_blk = 2;
int  items_n = 0;
int base_objects = 25;
// ================= [ SCRIPTING SERVICE OF THE GAME ] ==============
float tdx,tdz; int tcox,tcoz;
/*
=====================================================================
=     LIGHT ENGINE AND REFLECTION VARIABLES ARE DEFINED HERE        =
=====================================================================
*/
static int SM_SPEC = 1;

bool is_night = false;
bool has_cloud= true;
float nube_rot = 0;

float wof = 0.0;
float wof2= 0.0;
float wof3 = 0;
float maxh= 0.05;
bool incw = false;
static float amb_md[4] = {0.88, 0.88, 0.88, 1.0};  // ambient model values

static float amb_mt[4] = {0.88, 0.88, 0.88, 1.0}; // ambient mat values
static float dif_mt[4] = {0.8, 0.8, 0.8, 1.0}; // diffuse mat values
static float spc_mt[4] = {0.4, 0.4, 0.4, 1.0}; // specular mat values
static float ems_mt[4] = {0.0, 0.0, 0.0, 1.0}; // emission mat values
static float ltc_mt[4] = {0.8, 1.0, 0.8, 1.0}; // green-tinted 

static float n_amb_md[4] = {0.5, 0.5, 0.5, 1.0};  // ambient model values

static float n_amb_mt[4] = {0.5, 0.5, 0.5, 1.0}; // ambient mat values

float FogColor[4] = {0.8,0.8,1.0,1.0};            // color of the fog that's being generated

float NFogColor[4] = {0.1,0.1,0.15,1.0};            // color of the fog that's being generated

float WFogColor[4] = {0.0,0.39,0.49,1.0};            // color of the fog under water
/*
===========================================================================
= CURRENT TERMINAL VARIABLES ARE HERE TO SHOW MESSAGES OF ERROR OR PRINTS = 
===========================================================================
*/
std::string Trm_out[100];
int out_n = 16;
int tm_ptr = 0;
int oun = 0;
/*
=====================================
=  BROWSER FUNCTONS INSIDE THE GAME =
=====================================
*/
std::string rd_line = ""; // this is the content of the line that's being read
/*
=========================================================================================
= GAME MANAGER FOR THE AUDIO VARIABLES -- THESE ARE THE BOOLEANS THAT TRIGGER THE AUDIO =
=========================================================================================
*/
bool snd_beep1 = false;
bool snd_beep2 = false;
bool snd_place = false;
/*
=====================================================================
=  SESSION MANAGER VARIABLES TO PREVENT MULTIPLE SESSIONS COMBINE   =
=====================================================================
*/
int current_sesion = 1;
std::string email = "";
std::string passw = "";
std::string Token = "";
/*
=================================================
= CHUNK APPERIANCE DIMENSION MANAGER VARIABLES  =
=================================================
*/
int  sea_level = 0;
bool is_flatw =  false;
bool has_grass = true;
bool has_trees = true;
std::string descriptor = "default;";

// ------ PERLIN MANAGER VARIABLES -------------
int numX = 512,
    numY = 512,
    numOctaves = 8;
double persistence = 0.5;

#define maxPrimeIndex 10
int primeIndex = 0;

int primes[maxPrimeIndex][3] = {
  { 995615039, 600173719, 701464987 },
  { 831731269, 162318869, 136250887 },
  { 174329291, 946737083, 245679977 },
  { 362489573, 795918041, 350777237 },
  { 457025711, 880830799, 909678923 },
  { 787070341, 177340217, 593320781 },
  { 405493717, 291031019, 391950901 },
  { 458904767, 676625681, 424452397 },
  { 531736441, 939683957, 810651871 },
  { 997169939, 842027887, 423882827 }
};
int height_map1;


/*
================================
* GLOBAL CONSTANTS FOR PHYSICS *
================================
*/
#define PHY_PI 3.14159
#define GRAVITY -9.81
float dt = 0.02;   // delta time - time step
float rho = 0.5;  // density of the air
float C_d = 0.47; // object dragging
/*
==================================================
= STACK OF THE PARTICLE EMITTERS THAT ARE ACTIVE =
==================================================
*/
int particle_pointer;
bool particles_active = false;

