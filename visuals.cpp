#include <stdio.h>     // - Just for some ASCII messages
#include "gl/glut.h"   // - An interface and windows
                       //   management library
#include "visuals.h"   // Header file for our OpenGL functions
#include "clock.h"


int r = 1;
int l = 0;
int cuckoo = 0;

void Render()
{    
  
  glClear(GL_COLOR_BUFFER_BIT );  // Clean up the colour of the window
								  // and the depth buffer

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // draw the clock body
  
  
  DrawPendulum();
  DrawClockBody();  
  DrawClock();
  DrawCuckoo();

  glutSwapBuffers();             // All drawing commands applied to the 
                                 // hidden buffer, so now, bring forward
                                 // the hidden buffer and hide the visible one           

}

//-----------------------------------------------------------


void Resize(int w, int h)
{ 
  // define the visible area of the window ( in pixels )
  if (h==0) h=1;
  glViewport(0,0,700,700); 

  // Setup viewing volume

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
 
  //         L	    R 	    B 	   T	   N	   F
  glOrtho (-100.0, 100.0, -100.0, 200.0, 100.0,-100.0);
	
}

void Idle()
{
	if (pend_angle<15.0 && r==1)	pend_angle+=0.5f;	//rotate right pendulum
	else if (pend_angle>-15.0 && l==1)	pend_angle-=0.5f;	// rotate left pendulum
	else if ( pend_angle>=15.0 && r==1)   // 1 second passed
	{
		r=0;l=1;
		pend_angle-=0.5f;					// rotate left pendulum

		sec_angle += 6;						// rotate seconds pointer		
		if (sec_angle%360==0)		// 1 minute passed
		{
			min_angle+=6;			// rotate minutes pointer
			if (min_angle%360==0)	hour_angle+=6;	// 1 hour passed - rotate hours pointer 
		}
		
		ControlCuckoo();					// define if cuckoo has to be shown or not	
	}
	else if (pend_angle<=-15.0 && l==1)     // another second passed
	{
		l=0;
		r=1;
		pend_angle+=0.5f;
		sec_angle += 6;

		if (sec_angle%360==0) 
		{
			min_angle+=6;
			if (min_angle%360==0) hour_angle+=6;
		}
		
		ControlCuckoo();
	}


	glutPostRedisplay();

}

//-----------------------------------------------------------

void Setup()  // DON'T TOUCH IT 
{ 
	//Parameter handling
	//glShadeModel (GL_SMOOTH);
	glShadeModel (GL_FLAT);

 
	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
  
	//Set up light source
	GLfloat light_position[] = { -50.0, 20.0, 150.0, 1.0 };
	GLfloat ambientLight[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	   
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
	glLightfv( GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_POINT_SMOOTH);

	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);

}





