#include "stdafx.h"


TProstopad::TProstopad()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

void TProstopad::prostoinitp(float xp,float yp,float zp,float zh)
{
	this->x=xp;
	this->y=yp;
	this->z=zp;
	this->h=zh;
}; 

void TProstopad::Prostopad()
{
	
	glBegin(GL_TRIANGLES);
	float QA[3] = {x,-y,z};
	float QB[3] = {x,-y,z};
	float QC[3] = {x,y,z};
	
	
	float pointA = QB[0]-QA[0];
	float pointB = QB[1]-QA[1];
	float pointC = QB[2]-QA[2];
	
	float NpointA = QC[0]-QA[0];
	float NpointB = QC[1]-QA[1];
	float NpointC = QC[2]-QA[2];

	float Iloczyn[3] = {NpointB*pointC - NpointC*pointB,NpointC*pointA - NpointA*pointC,NpointA*pointB - NpointB*pointA};
	float IloczynN = (sqrt((Iloczyn[0]*Iloczyn[0])+(Iloczyn[1]*Iloczyn[1])+(Iloczyn[2]*Iloczyn[2])));
	Iloczyn[0] = Iloczyn[0]/IloczynN;
	Iloczyn[1] = Iloczyn[1]/IloczynN;
	Iloczyn[2] = Iloczyn[2]/IloczynN;
	//glNormal3fv(Iloczyn);



	glVertex3f(this->x,this->y,this->z);
	glVertex3f(this->x+this->h,this->y,this->z);
	glVertex3f(this->x+this->h,this->y+this->h,this->z);
	glEnd();

	glBegin(GL_TRIANGLES);
	//glNormal3fv(Iloczyn);
	glVertex3f(this->x,this->y,this->z);
	glVertex3f(this->x,this->y+this->h,this->z);
	glVertex3f(this->x+this->h,this->y+this->h,this->z);
	glEnd();


	//////////////////////////////////////////////////////////
	glBegin(GL_TRIANGLES);

	//	glNormal3fv(Iloczyn);
	glVertex3f(this->x,this->y,this->z+this->h);
	glVertex3f(this->x+this->h,this->y,this->z+this->h);
	glVertex3f(this->x+this->h,this->y+this->h,this->z+this->h);
	glEnd();

	glBegin(GL_TRIANGLES);
	//glNormal3fv(Iloczyn);
	glVertex3f(this->x,this->y,this->z+this->h);
	glVertex3f(this->x,this->y+this->h,this->z+this->h);
	glVertex3f(this->x+this->h,this->y+this->h,this->z+this->h);
	glEnd();
	////////////////////////////////////////////////////////////
	glBegin(GL_TRIANGLES);

    //glNormal3fv(Iloczyn);
	glVertex3f(this->x+this->h,this->y,this->z);
	glVertex3f(this->x+this->h,this->y,this->z+this->h);
	glVertex3f(this->x+this->h,this->y+this->h,this->z+this->h);
	glEnd();

	glBegin(GL_TRIANGLES);
	//glNormal3fv(Iloczyn);
	glVertex3f(this->x+this->h,this->y,this->z);
	glVertex3f(this->x+this->h,this->y+this->h,this->z);
	glVertex3f(this->x+this->h,this->y+this->h,this->z+this->h);
	glEnd();
	////////////////////////////////////////////////////////////
	glBegin(GL_TRIANGLES);
	glVertex3f(this->x,this->y,this->z);
	glVertex3f(this->x,this->y,this->z+this->h);
	glVertex3f(this->x,this->y+this->h,this->z+this->h);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(this->x,this->y,this->z);
	glVertex3f(this->x,this->y+this->h,this->z);
	glVertex3f(this->x,this->y+this->h,this->z+this->h);
	glEnd();
	////////////////////////////////////////////////////////////
	glBegin(GL_TRIANGLES);
	glVertex3f(this->x,this->y+this->h,this->z);
	glVertex3f(this->x+this->h,this->y+this->h,this->z);
	glVertex3f(this->x+this->h,this->y+this->h,this->z+this->h);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(this->x,this->y+this->h,this->z);
	glVertex3f(this->x,this->y+this->h,this->z+this->h);
	glVertex3f(this->x+this->h,this->y+this->h,this->z+this->h);
	glEnd();
	////////////////////////////////////////////////////////////
	glBegin(GL_TRIANGLES);
	glVertex3f(this->x,this->y,this->z);
	glVertex3f(this->x,this->y,this->z+this->h);
	glVertex3f(this->x,this->y+this->h,this->z+this->h);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(this->x,this->y,this->z);
	glVertex3f(this->x,this->y+this->h,this->z);
	glVertex3f(this->x,this->y+this->h,this->z+this->h);
	glEnd();
	////////////////////////////////////////////////////////////
	glBegin(GL_TRIANGLES);
	glVertex3f(this->x,this->y,this->z);
	glVertex3f(this->x+this->h,this->y,this->z);
	glVertex3f(this->x+this->h,this->y,this->z+this->h);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(this->x,this->y,this->z);
	glVertex3f(this->x,this->y,this->z+this->h);
	glVertex3f(this->x+this->h,this->y,this->z+this->h);
	glEnd();
	////////////////////////////////////////////////////////////

}

void TProstopad::Przerysuj()
{
	Prostopad();
}