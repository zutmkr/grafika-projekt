#include "stdafx.h"
#pragma once

class TLampa
{
public:
	float x,y,z,h;
	TProstopad noga;
	TKula klosz;

	TLampa();  //konstruktor bezparametryczny
	void lampainit(float,float,float,float);	
	void Lampa();
	void Przerysuj();
};
