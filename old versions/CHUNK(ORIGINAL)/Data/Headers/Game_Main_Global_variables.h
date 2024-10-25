// -------------------KEY SCREEN POSITIONS AND SIZE ---------------------
int BON_SCREEN_W = 640;         // SCREEN SIZE VARIABLES ON X AXIS
int BON_SCREEN_H = 480;         // SCREEN SIZE VARIABLES ON Y AXIS

// --------------- SELF PLAYER POSITION ON GAME -------------------------
float px = 8, py = 51, pz = 8; // player position
float cx = 0, cy = 0, cz = 0;  // camera rotation
float angle = 180, angl2 = 0;  // player angles
int loc_X = 0,loc_Y = 0;       // greater location in player (current chunk where player is)
int opx = 8,opy = 8;           // greater scale of old player position (used for knowing when should a new chunk be generated)
// ------------- RAYCASTER PTR DATA VARIABLES FOR BUILDING INGAME -------
float ox=px,oz=pz; float dx,dz; int cox,coz;
float rx,ry,rz;int zom = 2;
// ------------- TEXTURE IDENTIFIERS VARIABLES --------------------------
GLuint GRASS_TEXTURE;        // just some variables and constants
GLuint COBBLESTONE_TEXTURE;  // for the different textures generations 
GLuint DIRT_TEXTURE;         // and also these are needed
GLuint STONE_TEXTURE;        // to identify
GLuint WATER_TEXTURE;        // which texture is enabled
GLuint SKY_TEXTURE;          // and assigned to each item
GLuint EYE_EFFECT_T;         // effect of the eye
GLuint RAW_WOOD_TEXTURE;     // wood tree texture
GLuint LEAVES_TEXTURE;         // effect of the eye
//-------------- SKY POSITIONS TEXTURES FOR SKYBOX -----------------------
GLuint SKY_TEX[6]; //-- negative x
// ------------- TEXTURE OFFSET FOR FIXING THE LOAD ----------------------
float xoff = 1.16;           // offset -- used for texture correction (it's a constant fount thats the correction on repeating texture)
float xoff2 = 0.39;           // offset -- used for texture correction (it's a constant fount thats the correction on repeating texture)
// ------------- VARIABLES TO CONNECT WITH MYSQL SERVER TO LOAD BUILDINGS FROM A BASE --------------------------
#define SERVER "localhost" 
#define USER   "bonii_vw"                      //
#define PASS   "Bonii462432+!"                 // REPLACE WITH YOUR OWN USER AND PASSWORD
#define DBCP   "Voxel_World"                   // 
// -------------- THE MYSQL POINTER THAT WILL BE USEFUL DURING ALL PROGRAM EXECUTION --------------------------
MYSQL *connect;
MYSQL_RES *res_set;
MYSQL_ROW row;
