// stdafx.h: do³¹cz plik do standardowych systemowych plików do³¹czanych,
// lub specyficzne dla projektu pliki do³¹czane, które s¹ czêsto wykorzystywane, ale
// s¹ rzadko zmieniane
//

// Pliki nag³ówkowe œrodowiska uruchomieniowego C
#include <windows.h>
#include <windowsx.h>

#define IDS_APP_TITLE			103
#define IDD_ABOUTBOX			103
#define IDM_ABOUT				104
#define IDM_EXIT				105
#define IDI_OPENGL			107
#define IDI_SMALL				108
#define IDC_OPENGL			109


#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <gl/gl.h>
#include <gl/glu.h>

#include <crtdbg.h>


#define MAX_LOADSTRING 100
#define MAX_ILOSC_ZEGAROW 10
#define ILE_CZCIONEK 10


class TRysuj
{
private:
	GLfloat xpop, ypop, zpop;
	GLfloat myszX, myszY, myszZ;
	GLfloat myszX_koniec, myszY_koniec, myszZ_koniec;
	GLfloat SzerokoscEkranu, WysokoscEkranu;
	HWND hwnd_ap;
	GLfloat katX, katY;
	bool ObrotScenyTN;

protected:

	unsigned long* WczytajTeksture(LPCWSTR nazwaPliku, int& teksturaSzer, int& teksturaWys, bool zZasobow, unsigned char alfa);
	void Kolor(GLfloat r, GLfloat g, GLfloat b);
	void Punkt(GLfloat x, GLfloat y, GLfloat z);
	void Punkt(GLfloat x, GLfloat y);
	void Linia(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat x1, GLfloat y1, GLfloat z1);
	void Linia(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1);
	void PrzesunDo(GLfloat x, GLfloat y, GLfloat z);
	void PrzesunDo(GLfloat x, GLfloat y);
	void LiniaDo(GLfloat x, GLfloat y, GLfloat z);
	void LiniaDo(GLfloat x, GLfloat y);
	void Trojkat(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2);
	void Trojkat(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	void Pisz(GLfloat x, GLfloat y, int RozmiarCzcionki, const char *fmt, ...);

	GLfloat PodajXMyszy();
	GLfloat PodajYMyszy();
	GLfloat PodajZMyszy();
	GLfloat PodajXMyszyKoniec();
	GLfloat PodajYMyszyKoniec();
	GLfloat PodajZMyszyKoniec();

	GLfloat PodajSzerokoscEkranu();
	GLfloat PodajWysokoscEkranu();

	void ObrotOsX(GLfloat kat);
	void ObrotOsY(GLfloat kat);
	void ObrotOsZ(GLfloat kat);

public:
	void UstawWspolrzedneMyszy(GLfloat x, GLfloat y);
	void UstawWspolrzedneMyszy(GLfloat x, GLfloat y, GLfloat z);
	void UstawWspolrzedneMyszyKoniec(GLfloat x, GLfloat y, GLfloat z);
	void UstawRozmiaryEkranu(GLfloat szer, GLfloat wys);
	void ObrotSceny(bool TN);

	virtual void UstawieniaSceny();
	virtual void Poczatek();
	virtual void Koniec();
	void Przerysowywanie();
	virtual void Przerysuj() = 0;
	virtual void RuchMyszy(GLfloat x, GLfloat y);
	virtual void RuchMyszy(GLfloat x, GLfloat y, GLfloat z);
	virtual void RuchMyszy(GLfloat x_poczatek, GLfloat y_poczatek, GLfloat z_poczatek, GLfloat x_koniec, GLfloat y_koniec, GLfloat z_koniec);
	virtual void PrawyPrzyciskMyszyWcisniety();
	virtual void PrawyPrzyciskMyszyPuszczony();
	virtual void LewyPrzyciskMyszyWcisniety();
	virtual void LewyPrzyciskMyszyPuszczony();
	virtual void LewyPrzyciskPodwojneKlikniencie();
	virtual void Zegar(int numer);
	virtual void KlawiszWcisniety(int klawisz);
	virtual void ZmianaRozmiaruEkranu();


	void Odswiez();
	void UstawUchwytOkienka(HWND hwnd);

	TRysuj();
};

class TAplikacja
{
private:
	TCHAR szTitle[MAX_LOADSTRING];					// Tekst paska tytu³u
	TCHAR szWindowClass[MAX_LOADSTRING];			// nazwa klasy okna g³ównego
	static _In_ HINSTANCE hInstance;
	int nCmdShow;
	BOOL InicjalizacjaPoprawna;
	HACCEL hAccelTable;
	static BOOL poczatek;
	static HDC hDC;
	static HGLRC hRC;
	static TRysuj *rysuj;
	static HWND hwnd_ap;
	static bool zegar[MAX_ILOSC_ZEGAROW];

	static int SzerokoscObszaruUzytkownika;
	static int WysokoscObszaruUzytkownika;

	static void UstawienieSceny();
	static void WylaczOpenGL(HWND hWnd);
	static void WlaczOpenGL(HWND hWnd);
	
	static void KasujZegary();

	static GLvoid BuildFont(GLvoid);
	static GLvoid KillFont(GLvoid);

	BOOL InitInstance();
	static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	ATOM MyRegisterClass();

public:
	static GLuint base[ILE_CZCIONEK];


	bool UstawZegar(int numer, int czas_ms);
	bool WylaczZegar(int numer);
	void UstawParametryEkranu();

	WPARAM PetlaWiadomosci();

	TAplikacja(_In_ HINSTANCE hInstance, int _nCmdShow,TRysuj *rys);
	~TAplikacja();
public:
};