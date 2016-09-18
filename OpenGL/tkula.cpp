#include "stdafx.h"

void TKula::kulainitp(float x,float y,float z)
{
	this->px=x;
	this->py=y;
	this->pz=z;
}; 

void TKula::kulainitw(GLint x,GLint y,GLint z)
{
	this->wx=x;
	this->wy=y;
	this->wz=z;
};

void TKula::Kula()
{
	glTranslatef(this->px,this->py,this->pz); 
	GLUquadricObj *fig;
	fig = gluNewQuadric();
	gluQuadricDrawStyle(fig,GLU_FILL);
	gluSphere(fig,this->wx,this->wy,this->wz);
	gluDeleteQuadric(fig);

}


void TKula::Przerysuj()
{
	Kula();
}