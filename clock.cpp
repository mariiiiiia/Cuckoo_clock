#include <stdio.h>     // - Just for some ASCII messages
#include "gl/glut.h"   // - An interface and windows
                       //   management library
#include "clock.h"
#include "visuals.h"   // Header file for our OpenGL functions
#include "time.h"

int cuckoo_counter=0;

void DrawCuckoo()
{
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glRotatef( -30, 0.0, 1.0, 0.0);
	glColor4f( 1.5, 1.6, 1.0, alpha );

	glTranslatef( 23, 125, 0);	
	glutSolidSphere( 7, 50, 50);	 // cuckoo's body
	
	glTranslatef( -5, 10, 0);	
	glutSolidCone( 5, 10, 50, 50);		//cuckoo's head
	

}


void DrawClock()
{
	glLoadIdentity();

	glTranslatef( 20.0, 50.0, 0.0);

	glColor3f( 1.8, 1, 0.8);
	glPointSize(4);
	glBegin( GL_QUADS);
	glVertex2f( 20.0, 20.0);
	glVertex2f( 20.0, -20.0);
	glVertex2f( -20.0, -20.0);
	glVertex2f( -20.0, 20.0);
	glEnd();

	glColor3f( 0.6, 0.0, 0);
	glPointSize(4);
	glBegin( GL_POLYGON);
	glVertex2f( -2.0, 2.0);
	glVertex2f( 2.0, 2.0);
	glVertex2f( 2.0, -2.0);
	glVertex2f( -2.0, -2.0);
	glEnd();


	// draw seconds 
	glRotatef( sec_angle, 0.0, 0.0, -1.0);

	glColor3f( 0.0, 0.0, 0.0);
	glPointSize(6);
	glBegin(GL_POLYGON);
	glVertex2f( -0.5, 0.0);
	glVertex2f( -0.5, 16.0);
	glVertex2f( 0.0, 19.0);
	glVertex2f( 0.5, 16.0);
	glVertex2f( 0.5, 0.0);
	glVertex2f( -0.5, 0.0);
	glEnd();

	// draw minutes
	glLoadIdentity();

	glTranslatef( 20.0, 50.0, 100.0);
	glRotatef( min_angle, 0.0, 0.0, -1.0);

	glColor3f( 0.0, 0.0, 0.0);
	glPointSize(6);
	glBegin(GL_POLYGON);
	glVertex2f( -0.7, 0.0);
	glVertex2f( -0.7, 14.0);
	glVertex2f( 0.0, 17.0);
	glVertex2f( 0.7, 14.0);
	glVertex2f( 0.7, 0.0);
	glVertex2f( -0.7, 0.0);
	glEnd();

	// draw hours
	glLoadIdentity();

	glTranslatef( 20.0, 50.0, 100.0);
	glRotatef( hour_angle, 0.0, 0.0, -1.0);

	glColor3f( 0.0, 0.0, 0.0);
	glPointSize(6);
	glBegin(GL_POLYGON);
	glVertex2f( -0.9, 0.0);
	glVertex2f( -0.9, 10.0);
	glVertex2f( 0.0, 13.0);
	glVertex2f( 0.9, 10.0);
	glVertex2f( 0.9, 0.0);
	glVertex2f( -0.9, 0.0);
	glEnd();
}


void DrawClockBody()
{
	glLoadIdentity();

	glScalef(2,2,0);
    glTranslatef( 0, 10, 0);

    glColor3f(2.8, 1.8, 1.3);						   
    glRectf(-10.0, -10.0, 30.0, 40.0);       // house         

    glColor3f(3.0, 0.1, 0.1);			// roof
    glPointSize(3);
    glBegin(GL_TRIANGLES);
    glVertex2f( -20, 40);
    glVertex2f( 10, 80);
    glVertex2f( 40, 40);  
    glEnd();
  
    glLoadIdentity();
  
}

void DrawPendulum()
{
	glLoadIdentity();

	glTranslatef( 21.5, 0, 0);					// rotation of the pendulum
	glRotatef( pend_angle, 0.0, 0.0, 1.0);		
	glTranslatef( -21.5, 0, 0);

	glColor3f(0.6,0.0,0.0);					// draw pendulum
	glPointSize(5);
	glBegin(GL_POLYGON);
	glVertex2f( 20, 0);
	glVertex2f( 20, -50);
	glVertex2f( 23, 0);
	glVertex2f( 23, -50);
	glVertex2f( 20, -50);
	glEnd();

	glTranslatef( 21.5,-50,0);
	glutSolidSphere( 3, 10, 10);
}

void ControlCuckoo()
{
	if ( alpha==1) 
	{
		cuckoo_counter+=1;
//		if (cuckoo_counter==3)		// time cuckoo is on (in seconds)
		if (cuckoo_counter==15)
		{
			alpha=0.0;
			cuckoo_counter=0;
		}
	}
	else if (alpha==0)
	{
		cuckoo_counter+=1;
		if (cuckoo_counter==1)     // time cuckoo waits (in seconds)
//		if (cuckoo_counter==3600
		{
			alpha=1.0;
			cuckoo_counter=0;
		}
	}
}


void TakeCurrentTime()
{
	int hours=0,minutes=0,secs=0;
	
	time_t time_now = time(0);			// take current time
	struct tm * tstruct;
	tstruct = localtime(&time_now);
    hours = tstruct->tm_hour;
    minutes = tstruct->tm_min;
    secs = tstruct->tm_sec;

	sec_angle = secs*6;				// show current time
	min_angle = minutes*6;
	if (hours>11) hours = hours-12;
	hour_angle = hours*30;

    printf("time now is %d:%d:%d", hours, minutes, secs);
}
