#include "stdafx.h"
#pragma once


class TKula 
{
public:
	GLint wx;
	GLint wy;
	GLint wz;
	float px,py,pz;

	void kulainitp(float,float,float);
	void kulainitw(GLint,GLint,GLint);
	void Kula();
	void Przerysuj();

};
