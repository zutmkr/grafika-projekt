#include "stdafx.h"

TLampa::TLampa()
{
	this->x=0; 
	this->y=0; 
	this->z=0;
}   

void TLampa::lampainit(float xp,float yp,float zp,float zh)
{
	this->x=xp;
	this->y=yp;
	this->z=zp;
	this->h=zh;
}

void TLampa::Lampa()
{
	glColor3f(0.1f,0.1f,0.1f);
	noga.prostoinitp(this->x-h/2,this->y,this->z-h/2,this->h);
	noga.Przerysuj();		 
	noga.prostoinitp(this->x-h/2,this->y-h,this->z-h/2,this->h);
	noga.Przerysuj();		 					 
	noga.prostoinitp(this->x-h/2,this->y-2*h,this->z-h/2,this->h);
	noga.Przerysuj();		 					 
	noga.prostoinitp(this->x-h/2,this->y-3*h,this->z-h/2,this->h);
	noga.Przerysuj();


	glColor3f(1.0f,1.0f,0.9f);
	klosz.kulainitp(this->x,this->y+3*h,this->z);
	klosz.kulainitw((GLint)this->h*2,100,100);
	klosz.Przerysuj();
	
}

void TLampa::Przerysuj()
{
	Lampa();
}