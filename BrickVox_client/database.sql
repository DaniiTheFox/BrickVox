-- ======================================================================================
-- =     CHUNK SYSTEM ON MULTIPLAYER GAME PROTOTYPE SQL SCRIPT TO CREATE DATABASE       =
-- ======================================================================================
CREATE USER 'bonii_vw'@'localhost' IDENTIFIED BY 'bonibase!';


CREATE DATABASE Voxel_World;

USE Voxel_World;

CREATE TABLE Modifications(                        -- chunk modifications
 Chunk_ID INT NOT NULL PRIMARY KEY AUTO_INCREMENT, -- chunk id
 Chunk_X  INT NOT NULL,                            -- chunk position on z axis
 Chunk_Y  INT NOT NULL,                            -- chunk position on y axis
 Modif_X  INT NOT NULL,                            -- x coordinate of modification
 Modif_Y  INT NOT NULL,                            -- y coordinate of modification
 Modif_Z  INT NOT NULL,                            -- z coordinate of modification
 Block_E  INT NOT NULL,                             -- the modification for the chunk
 Session  INT NOT NULL
);

CREATE TABLE Players_ingame(
 Player_ID INT NOT NULL PRIMARY KEY AUTO_INCREMENT, 
 P_Joined  INT NOT NULL,
 Username  Varchar(50) NOT NULL,
 Pos_X     INT NOT NULL,
 Pos_Y     INT NOT NULL,
 Pos_Z     INT NOT NULL,
 Rot_P     INT NOT NULL,
 Model     MEDIUMTEXT NOT NULL,   -- must have model as string
 Texture   varchar(300),    -- must have an url saved NO COMAS
 Sesion    INT NOT NULL
);

CREATE TABLE chat_data(
 Message_ID INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
 User_Sent  Varchar(50) NOT NULL, 
 Msg_Data   Varchar(1000) NOT NULL,
 Session    INT NOT NULL
);

CREATE TABLE custom_object(
 Obj_ID INT NOT NULL PRIMARY KEY AUTO_INCREMENT, -- current object
 Nameob Varchar(500) NOT NULL,                   -- name of the object 
 obCode MEDIUMTEXT NOT NULL,                     -- the behaviour of the object
 Sesion INT NOT NULL,                            -- in what sesion is the object generated
 img_ul Varchar(1000) NOT NULL                   -- how does the object look like?
);

CREATE TABLE Session_data(
 Sesion_Id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, -- id of session that was created
 Sesion_linker INT NOT NULL,                        -- this is the id that is linked to the objects players and bricks inside the game
 Sesion_name   VARCHAR(300) NOT NULL,               -- name of the session
 Sesion_desc   MEDIUMTEXT NOT NULL,                 -- the description of the session
 Sesion_owner  VARCHAR(100) NOT NULL,               -- who is the owner of the session
 Permission_l  INT NOT NULL                         -- what permissions the non owner have
);

GRANT SELECT,INSERT,DELETE,UPDATE ON Session_data   TO 'bonii_vw'@'localhost';
GRANT SELECT,INSERT,DELETE,UPDATE ON custom_object  TO 'bonii_vw'@'localhost';
GRANT SELECT,INSERT,DELETE,UPDATE ON Modifications  TO 'bonii_vw'@'localhost';
GRANT SELECT,INSERT,DELETE,UPDATE ON Players_ingame TO 'bonii_vw'@'localhost';
GRANT SELECT,INSERT,DELETE,UPDATE ON chat_data TO 'bonii_vw'@'localhost';
-- THE DATABASE TO SAVE THE CHUNK MODIFICATIONS
-- FILE MODIFICATIONS AND DONE SO OTHER PLAYERS CAN SEE MODIFICATIONS
-- WE SAVE THE CHUNK LOCATION
-- AND THE EDIT LOCATION
-- ALSO WHAT BLOCK IS LOCATED
