void glut_main(int ar, char **ag){
 glutInit(&ar, ag);                                        // START THE OPENGL LIBRARY FOR THE GAME
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);    // INITIALIZE THE GRAPHICS MODE ON DISPLAY
  glutInitWindowSize(BON_SCREEN_W,BON_SCREEN_H);               // SET THE WINDOW SIZE
  glutInitWindowPosition(300,64);                              // SET THE WINDOW POSITION
  glutCreateWindow(" BrickVox Indev v 0.0.8.1024 ");              // CREATE A GLUT WINDOW FOR THE GAME
 glDepthFunc(GL_LEQUAL);                                       // START THE DEPTH FUNCTION
 glClearDepth(1.0f);                                           // CLEAR THE DEPTH BUFFER
 glIni();                                                      // THE SETUP FUNCTION
  isRunning = true;                                            // DEFINES WHEN THE SECOND THREAD IS RUNNING
  glutIgnoreKeyRepeat(1);                                      // THE FUNCTION FOR MULTIPLE KEY DETECTION
  glutDisplayFunc(BON_GRAPH_FUNCTION);                         // THE FUNCTION TO INITIALIZE AND DRAW THE OBJECTS
  glutKeyboardFunc(BON_KEYBOARD_FUNCTION);                     // THE FUNCTION FOR KEYBOARD INTERACTIONS
  glutKeyboardUpFunc(BON_KEYBOARD_RELEASE);                    // THE FUNCTION TO RESET THE KEYS THAT WHERE PRESSED
  glutMouseFunc(BON_MOUSE_BUTTONS);                            // THE FUNCTION FOR MOUSE BUTTON DETECTION
  glutMotionFunc(BON_MOUSE_MOTION);
  glutPassiveMotionFunc(BON_MOUSE_FUNCTION);                   // THE FUNCTION FOR THE MOUSE INTERACTIONS
  glutIdleFunc(BON_IDLE_FUNCTION);                             // THE FUNCTION WHEN PLAYER IS NOT DOING ANYTHING
  glutReshapeFunc(resz);
  glutTimerFunc(25, game_controller_upd , 0);
  //glutTimerFunc(dt*1000, phy_upd, 0);
  //std::chrono::milliseconds(150);
 glutMainLoop();                                               // MAIN LOOP FOR THE GAME
}
