
#include "stdafx.h"
#pragma once


TDrzewo::TDrzewo()
{
	this->x=0;
	this->y=0;
	this->z=0;
}

void TDrzewo::Drzewoinit(float xp,float yp,float zp,float zh)
{
	this->x=xp;
	this->y=yp;
	this->z=zp;
	this->h=zh;
}

void TDrzewo::Drzewo()
{


	glColor3f(0.32f,0.00f,0.0f);
	pien.prostoinitp(this->x-h/2,this->y,this->z-h/2,this->h);
	pien.Przerysuj();		 
	pien.prostoinitp(this->x-h/2,this->y-h,this->z-h/2,this->h);
	pien.Przerysuj();		 					 
	pien.prostoinitp(this->x-h/2,this->y-2*h,this->z-h/2,this->h);
	pien.Przerysuj();		 					 
	pien.prostoinitp(this->x-h/2,this->y-3*h,this->z-h/2,this->h);
	pien.Przerysuj();


	glColor3f(0.0f,0.4f,0.0f);
	korona.kulainitp(this->x,this->y+3*h,this->z);
	korona.kulainitw((GLint)this->h*2,100,100);
	korona.Przerysuj();

}

void TDrzewo::Przerysuj()
{
	Drzewo();
}