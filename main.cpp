//--------------------------------------------------//
//													//	
//    Learning OpenGL: Εισαγωγικά Μαθήματα OpenGL   //
//													//
//    Πλατφόρμα ανάπτυξης παραδειγμάτων				//
//													//
//													//
//		Μάθημα 2ο									//
//--------------------------------------------------//


#include <stdio.h>     // - Just for some ASCII messages
#include "gl/glut.h"   // - An interface and windows 
                       //   management library
#include "visuals.h"   // Header file for our OpenGL functions
#include "clock.h"


////////////////// State Variables ////////////////////////
float pend_angle = -15.0f;
int sec_angle = 0, min_angle = 0, hour_angle = 0;
float alpha = 0.0;


/////////////// Main Program ///////////////////////////

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
  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
 
  
  // Define the main window size and initial position 
  // ( upper left corner, boundaries included )
  glutInitWindowSize(550,550);
  glutInitWindowPosition(50,50);
  
  // Create and label the main window
  glutCreateWindow("Awesome Clock");
  
  // Configure various properties of the OpenGL rendering context
  Setup();
  
  // take current time 
  TakeCurrentTime();

  // Callbacks for the GL and GLUT events:

  // The rendering function 
  glutDisplayFunc(Render);
  glutReshapeFunc(Resize);
  
  //(03)
  glutIdleFunc(Idle);

 
  //Enter main event handling loop
  glutMainLoop();
  return 0;


}  

