#include "stdafx.h"
#include "Opengl.h"
#define _USE_MATH_DEFINES
#include <math.h>

class TKula 
{

public:
	void Przerysuj();
	void Kula();


};
class TWalec
{

public:
	    void Przerysuj();
		void Walec();
		 
};

class TDrzewo 
{
	private:
		TWalec pien;
		TKula korona;
	public:
		void Przerysuj();
};

class Rysujprymityw{
public:
	virtual void Przerysuj();
	void Prostokat(float,float,float);
	void Prostopad(float,float,float);
	void Kwadryk();
	TDrzewo drzewo;

};
