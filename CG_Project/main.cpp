#include <stdio.h>     // - Just for some ASCII messages
#include "GL/glut.h"   // - An interface and windows 
#include "visuals.h"

int main(int argc, char* argv[])
{ 
  // initialize GLUT library state
  glutInit(&argc, argv);
	
  // Set up the display using the GLUT functions to 
  // get rid of the window setup details:
  // - Use true RGB colour mode ( and transparency )
  // - Enable double buffering for faster window update
  // - Allocate a Depth-Buffer in the system memory or 
  //   in the video memory if 3D acceleration available	
                      //RGBA//DEPTH BUFFER//DOUBLE BUFFER//
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
 
  
  // Define the main window size and initial position 
  // ( upper left corner, boundaries included )
  glutInitWindowSize(800,600);
  glutInitWindowPosition(50,50);
  
  // Create and label the main window
  glutCreateWindow("Papakia kai Mpalakia");
  
  Setup();
  
  glutDisplayFunc(Render);
  glutReshapeFunc(Resize);
  glutIdleFunc(Idle);
  glutKeyboardFunc(Keyboard);
  glutSpecialFunc(SpecialKeyboard);
  
  glutMainLoop();
  return 0;	
}  
