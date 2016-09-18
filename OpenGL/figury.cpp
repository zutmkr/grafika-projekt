#include "figury.h"
#include "stdafx.h"
#include "Opengl.h"
#define _USE_MATH_DEFINES
#include <math.h>

void Rysujprymityw::Prostokat(float x,float y,float z)
{
	glBegin(GL_TRIANGLES);
    y = 5 * (sinf(x*0.1f)+sinf(z*0.1f));
	glVertex3f(x,y,z);
	
	y = 5 * (sinf((x+5.0f)*0.1f)+sinf(z*0.1f));
	glVertex3f(x+5,y,z);

    y = 5 * (sinf((x+5.0f)*0.1f)+sinf((z+5.0f)*0.1f));
	glVertex3f(x+5,y,z+5);
	glEnd();

	glBegin(GL_TRIANGLES);
	y = 5 * (sinf(x*0.1f)+sinf(z*0.1f));
	glVertex3f(x,y,z);
	
	y = 5 * (sinf(x*0.1f)+sinf((z+5.0f)*0.1f));
	glVertex3f(x,y,z+5);
	
	y = 5 * (sinf((x+5.0f)*0.1f)+sinf((z+5.0f)*0.1f));
	glVertex3f(x+5,y,z+5);
	glEnd();
}

void Rysujprymityw::Prostopad(float x,float y,float z)
{
	glColor3f(1.0f,0.0f,0.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(x,y,z);
	glVertex3f(x+10,y,z);
	glVertex3f(x+10,y+10,z);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(x,y,z);
	glVertex3f(x,y+10,z);
	glVertex3f(x+10,y+10,z);
	glEnd();
	//////////////////////////////////////////////////////////
	glBegin(GL_TRIANGLES);
	glVertex3f(x,y,z+10);
	glVertex3f(x+10,y,z+10);
	glVertex3f(x+10,y+10,z+10);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(x,y,z+10);
	glVertex3f(x,y+10,z+10);
	glVertex3f(x+10,y+10,z+10);
	glEnd();
	////////////////////////////////////////////////////////////
	glBegin(GL_TRIANGLES);
	glVertex3f(x+10,y,z);
	glVertex3f(x+10,y,z+10);
	glVertex3f(x+10,y+10,z+10);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(x+10,y,z);
	glVertex3f(x+10,y+10,z);
	glVertex3f(x+10,y+10,z+10);
	glEnd();
	////////////////////////////////////////////////////////////
	glBegin(GL_TRIANGLES);
	glVertex3f(x,y,z);
	glVertex3f(x,y,z+10);
	glVertex3f(x,y+10,z+10);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(x,y,z);
	glVertex3f(x,y+10,z);
	glVertex3f(x,y+10,z+10);
	glEnd();
	////////////////////////////////////////////////////////////
	glBegin(GL_TRIANGLES);
	glVertex3f(x,y+10,z);
	glVertex3f(x+10,y+10,z);
	glVertex3f(x+10,y+10,z+10);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(x,y+10,z);
	glVertex3f(x,y+10,z+10);
	glVertex3f(x+10,y+10,z+10);
	glEnd();
	////////////////////////////////////////////////////////////
	glBegin(GL_TRIANGLES);
	glVertex3f(x,y,z);
	glVertex3f(x,y,z+10);
	glVertex3f(x,y+10,z+10);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(x,y,z);
	glVertex3f(x,y+10,z);
	glVertex3f(x,y+10,z+10);
	glEnd();
	////////////////////////////////////////////////////////////
	glBegin(GL_TRIANGLES);
	glVertex3f(x,y,z);
	glVertex3f(x+10,y,z);
	glVertex3f(x+10,y,z+10);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(x,y,z);
	glVertex3f(x,y,z+10);
	glVertex3f(x+10,y,z+10);
	glEnd();
	////////////////////////////////////////////////////////////

}


void TKula::Kula()
{
	
	glColor3f(0.69f,0.4f,0.16f);
	GLUquadricObj *fig;
	fig = gluNewQuadric();
	gluQuadricDrawStyle(fig,GLU_FILL);
	gluSphere(fig,10,30,30);
	gluDeleteQuadric(fig);

}

void TWalec::Walec()
{
	
	glColor3f(1.0f,0.0f,0.0f);
	GLUquadricObj *fig;
	fig = gluNewQuadric();
	gluQuadricDrawStyle(fig,GLU_FILL);
	gluSphere(fig,10,20,20);
	gluDeleteQuadric(fig);

}

void Rysujprymityw::Kwadryk()
{
	
	glColor3f(0.69f,0.4f,0.16f);
	GLUquadricObj *fig;
	fig = gluNewQuadric();
	gluQuadricDrawStyle(fig,GLU_FILL);
	gluSphere(fig,10,30,30);
	gluDeleteQuadric(fig);

}
