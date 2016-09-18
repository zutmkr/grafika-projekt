#include "stdafx.h"
#pragma once


class TJezioro 
{
public:
	GLint wx,wy,wz,wp,wk;
	float px,py,pz;

	void Tafla();
	void jezioroinitw(GLint,GLint,GLint,GLint,GLint);
	void jezioroinitp(float,float,float);
	void Przerysuj();
};