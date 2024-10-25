-- ======================================================================================
-- =     CHUNK SYSTEM ON MULTIPLAYER GAME PROTOTYPE SQL SCRIPT TO CREATE DATABASE       =
-- ======================================================================================
CREATE USER 'bonii_vw'@'localhost' IDENTIFIED BY 'Bonii462432+!';

CREATE DATABASE Voxel_World;

USE Voxel_World;

CREATE TABLE Modifications(                        -- chunk modifications
 Chunk_ID INT NOT NULL PRIMARY KEY AUTO_INCREMENT, -- chunk id
 Chunk_X  INT NOT NULL,                            -- chunk position on z axis
 Chunk_Y  INT NOT NULL,                            -- chunk position on y axis
 Modif_X  INT NOT NULL,                            -- x coordinate of modification
 Modif_Y  INT NOT NULL,                            -- y coordinate of modification
 Modif_Z  INT NOT NULL,                            -- z coordinate of modification
 Block_E  INT NOT NULL                             -- the modification for the chunk
);

GRANT SELECT,INSERT,DELETE,UPDATE ON Modifications TO 'bonii_vw'@'localhost';

-- THE DATABASE TO SAVE THE CHUNK MODIFICATIONS
-- FILE MODIFICATIONS AND DONE SO OTHER PLAYERS CAN SEE MODIFICATIONS
-- WE SAVE THE CHUNK LOCATION
-- AND THE EDIT LOCATION
-- ALSO WHAT BLOCK IS LOCATED
