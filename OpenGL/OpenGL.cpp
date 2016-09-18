// Opengl.cpp: Okreœla punkt wejœcia dla aplikacji.

#include "stdafx.h"


#define _USE_MATH_DEFINES
#define MAX_LOADSTRING 100

// Zmienne globalne:
HINSTANCE hInst;								// bie¿¹ce wyst¹pienie
TCHAR szTitle[MAX_LOADSTRING];					// Tekst paska tytu³u
TCHAR szWindowClass[MAX_LOADSTRING];			// nazwa klasy okna g³ównego

// Przeka¿ dalej deklaracje funkcji do³¹czonych w tym module kodu:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);



class Rysujprymityw :public TRysuj
{
public:
	virtual void Przerysuj();
	void Prostokat(float,float,float);

	TDrzewo drzewo;
	TProstopad dom;
	TJezioro jezioro;
	TLampa lampa;
	void UstawieniaSceny();
	void KlawiszWcisniety(int);


};

void Rysujprymityw::UstawieniaSceny()
{
	glEnable(GL_LIGHTING);
	const float kolor_tla[] = {0.1f,0.1f,0.1f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,kolor_tla);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	////////////////////SWIATLO NR 5 Z ROZBLYSKIEM////////////////
	const float pozycja5[4] = {45.0f,12.0f,66.0f,1.0f};
	const float kolor5[4] = {0.9f,0.9f,0.9f,1.0f};
	glLightfv(GL_LIGHT5,GL_POSITION,pozycja5);
	glLightfv(GL_LIGHT5,GL_DIFFUSE,kolor5);
	glEnable(GL_LIGHT5);




	/*
	glLightfv(GL_LIGHT5,GL_POSITION,pozycja5);
	glLightfv(GL_LIGHT5,GL_DIFFUSE,kolor5);
	glLightfv(GL_LIGHT5,GL_SPECULAR,kolor_rozblysk);
	glLightfv(GL_LIGHT5,GL_SPOT_DIRECTION,kierunek);
	glLightfv(GL_LIGHT5,GL_SPOT_CUTOFF,&szerokosc_wiazki);
	glEnable(GL_LIGHT5);
	*/
	////////////////////SWIATLO NR 4 BEZ ROZBLYSKU////////////////

	const float pozycja4[4] = {0.0f,0.0f,-120.0f,1.0f};
	const float kolor4[4] = {0.9f,0.9f,0.9f,1.0f};
	glLightfv(GL_LIGHT4,GL_POSITION,pozycja4);
	glLightfv(GL_LIGHT4,GL_DIFFUSE,kolor4);
	glEnable(GL_LIGHT4);

	const float kolor_rozblysk[4] = {0.9f,0.9f,0.9f,1.0f};
	const float kierunek[3] = {0.0f,0.0f,0.0f};
	const GLfloat szerokosc_wiazki = 150;


	glLightfv(GL_LIGHT4,GL_POSITION,pozycja4);
	glLightfv(GL_LIGHT4,GL_DIFFUSE,kolor4);
	glLightfv(GL_LIGHT4,GL_SPECULAR,kolor_rozblysk);
	glLightfv(GL_LIGHT4,GL_SPOT_DIRECTION,kierunek);
	glLightfv(GL_LIGHT4,GL_SPOT_CUTOFF,&szerokosc_wiazki);
	glEnable(GL_LIGHT4);





}

void Rysujprymityw::Prostokat(float x,float y,float z)
{
	glBegin(GL_TRIANGLES);
	y = 3 * (sinf(x*0.1f)+sinf(z*0.1f));
	glVertex3f(x,y,z);

	y = 3 * (sinf((x+5.0f)*0.1f)+sinf(z*0.1f));
	glVertex3f(x+5,y,z);

	y = 3 * (sinf((x+5.0f)*0.1f)+sinf((z+5.0f)*0.1f));
	glVertex3f(x+5,y,z+5);
	glEnd();

	glBegin(GL_TRIANGLES);
	y = 3 * (sinf(x*0.1f)+sinf(z*0.1f));
	glVertex3f(x,y,z);

	y = 3 * (sinf(x*0.1f)+sinf((z+5.0f)*0.1f));
	glVertex3f(x,y,z+5);

	y = 3 * (sinf((x+5.0f)*0.1f)+sinf((z+5.0f)*0.1f));
	glVertex3f(x+5,y,z+5);
	glEnd();
}

void Rysujprymityw::KlawiszWcisniety(int klawisz)
{
	TRysuj::KlawiszWcisniety(klawisz);


	const float pozycja5[4] = {45.0f,12.0f,66.0f,1.0f};
	const float kierunek[3] = {1.0f,0.0f,-1.0f};

	switch (klawisz)
	{
	case VK_LEFT:
		glLightfv(GL_LIGHT5,GL_POSITION,pozycja5);
		glLightfv(GL_LIGHT5,GL_SPOT_DIRECTION,kierunek);
		break;
	case VK_RIGHT:
		glLightfv(GL_LIGHT5,GL_POSITION,pozycja5);
		glLightfv(GL_LIGHT5,GL_SPOT_DIRECTION,kierunek);
		break;
	case VK_UP:
		glLightfv(GL_LIGHT5,GL_POSITION,pozycja5);
		glLightfv(GL_LIGHT5,GL_SPOT_DIRECTION,kierunek);
		break;
	case VK_DOWN:
		glLightfv(GL_LIGHT5,GL_POSITION,pozycja5);
		glLightfv(GL_LIGHT5,GL_SPOT_DIRECTION,kierunek);
		break;
	}

}


void Rysujprymityw::Przerysuj()
{
	void UstawieniaSceny();

	/////////////////////////////////POWIERZCHNIA/////////////////////////////
	glTranslatef(-30.0f,-30.0f,-60.0f);
	float i=0,j=0;

	glColor3f(0.0f,1.0f,0.0f);
	for (i=0;i<101;i=i+5)
	{  
		Prostokat(i,0,0);
		for (j=0;j<101;j=j+5)
		{
			Prostokat(i,0,j);
		}
	};

	/////////////////////////////////DRZEWA/////////////////////////////
	glPushMatrix();
	drzewo.Drzewoinit(20,10,8,3);
	drzewo.Przerysuj();
	glPopMatrix();

	glPushMatrix();
	drzewo.Drzewoinit(35,10,18,3);
	drzewo.Przerysuj();
	glPopMatrix();

	glPushMatrix();
	drzewo.Drzewoinit(44,5,8,3);
	drzewo.Przerysuj();
	glPopMatrix();

	glPushMatrix();
	drzewo.Drzewoinit(40,10,33,3);
	drzewo.Przerysuj();
	glPopMatrix();

	/////////////////////////////////DOMEK 1/////////////////////////////
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.5f);
	dom.prostoinitp(60,0,40,15);
	dom.Przerysuj();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f,0.0f,0.0f);
	dom.prostoinitp(65,6,54,3);
	dom.Przerysuj();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f,0.0f,0.0f);
	dom.prostoinitp(70,6,54,3);
	dom.Przerysuj();
	glPopMatrix();

	/////////////////////////////////DOMEK 2/////////////////////////////
	glPushMatrix();
	glColor3f(0.4f,0.3f,0.2f);
	dom.prostoinitp(60,0,70,15);
	dom.Przerysuj();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f,0.0f,0.0f);
	dom.prostoinitp(65,6,68,3);
	dom.Przerysuj();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f,0.0f,0.0f);
	dom.prostoinitp(70,6,68,3);
	dom.Przerysuj();
	glPopMatrix();
	/////////////////////////////////JEZIORO/////////////////////////////
	glPushMatrix();
	glColor3f(0.0f,0.3f,0.9f);
	glRotatef(90.0f,1.0f,0.0f,0.0f);
	jezioro.jezioroinitp(14,48,-1);
	jezioro.jezioroinitw(9,0,0,30,4);
	jezioro.Przerysuj();
	glPopMatrix();
	/////////////////////////////////LAMPY/////////////////////////////
	
	glPushMatrix();
	glScalef(0.4f,0.4f,0.2f);
	lampa.lampainit(20,12,66,3);
	lampa.Przerysuj();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.4f,0.4f,0.2f);
	lampa.lampainit(20,12,120,3);
	lampa.Przerysuj();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.4f,0.4f,0.2f);
	lampa.lampainit(100,12,400,3);
	lampa.Przerysuj();
	glPopMatrix();
	
}


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPTSTR    lpCmdLine,
					   _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	Rysujprymityw rysowanie;


	TAplikacja aplikacja(hInstance, nCmdShow, &rysowanie);

	aplikacja.UstawParametryEkranu();


	return (int) aplikacja.PetlaWiadomosci();
}
