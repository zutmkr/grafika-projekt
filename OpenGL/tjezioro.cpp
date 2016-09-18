#include "stdafx.h"
#pragma once

void TJezioro::Tafla()
{
	const GLfloat param = 30;
	const GLfloat param2 = 0;
	const float wsp_odbicia1[4] = {1.0,1.0,1.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,wsp_odbicia1);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,&param);
	glTranslatef(this->px,this->py,this->pz); 
	GLUquadricObj *fig;
	fig = gluNewQuadric();
	gluQuadricDrawStyle(fig,GLU_FILL);
	gluCylinder(fig,this->wx,this->wy,this->wz,this->wp,this->wk);
	gluDeleteQuadric(fig);
	const float wsp_odbicia2[4] = {0.0,0.0,0.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,wsp_odbicia2);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,&param2);

}

void TJezioro::jezioroinitw(GLint x,GLint y,GLint z,GLint p,GLint k)
{
	this->wx=x;
	this->wy=y;
	this->wz=z;
	this->wp=p;
	this->wk=k;
};

void TJezioro::jezioroinitp(float x,float y,float z)
{
	this->px=x;
	this->py=y;
	this->pz=z;
}; 

void TJezioro::Przerysuj()
{
	Tafla();
}