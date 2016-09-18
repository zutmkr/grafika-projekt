
#include "stdafx.h"
#pragma once

class TDrzewo 
{
public:
	float x,y,z,h;
	TProstopad pien;
	TKula korona;

	TDrzewo();  //konstruktor bezparametryczny
	void Drzewoinit(float,float,float,float);
	void Drzewo();
	void Przerysuj();
};

