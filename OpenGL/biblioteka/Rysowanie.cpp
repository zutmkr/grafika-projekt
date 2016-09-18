// stdafx.cpp: plik Ÿród³owy , który zawiera tylko standardowe zawarcia
// Opengl.pch bêdzie wstêpnie skompilowanym nag³ówkiem
// stdafx.obj bêdzie zawieraæ informacje typu wstêpnie skompilowanego

#include "Rysowanie.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

// TODO: odwo³aj siê do dowolnych dodatkowych nag³ówków, których potrzebujesz w pliku STDAFX.H
// a nie w tym pliku

_In_ HINSTANCE TAplikacja::hInstance;
HDC TAplikacja::hDC;
HGLRC TAplikacja::hRC;
int TAplikacja::SzerokoscObszaruUzytkownika;
int TAplikacja::WysokoscObszaruUzytkownika;
TRysuj *TAplikacja::rysuj = NULL;
HWND TAplikacja::hwnd_ap;
bool TAplikacja::zegar[MAX_ILOSC_ZEGAROW];
BOOL TAplikacja::poczatek = true;
GLuint TAplikacja::base[ILE_CZCIONEK];
int RozmiaryCzcnionek[] = {-50,-40,-30,-25,-20,-16,-14,-12,-10,-8};

#define ID_TIMER 1000
#define SKOK_KATA 1

//----------------------------------------------------------
//Jacek Matulewski, Tomasz Dziubak, Marcin Sylwestrzak, Rados³aw P³oszajczak
//Grafika.Fizyka.Metody numeryczne.Symulacje fizyczne z wizualizacj¹ 3D
unsigned long* TRysuj::WczytajTeksture(LPCWSTR nazwaPliku, int& teksturaSzer, int& teksturaWys, bool zZasobow, unsigned char alfa)
{
	//niezbyt elegancko jest tworzyc new w funkcji (zapomina sie o delete)
	//ale dzieki temu nie trzeba rozbijac na dwie czesci (pobieranie obrazu i czytanie)
	//nie trzeba zwracac informacji o obrazie, bo zawsze zwracamy tablice RGBA
	//czytanie bitmapy z pliku lub z zasobow

	HBITMAP uchwytObrazu = (HBITMAP)LoadImage(GetModuleHandle(NULL), nazwaPliku, IMAGE_BITMAP, 0, 0, (zZasobow ? 0 : LR_LOADFROMFILE) | LR_CREATEDIBSECTION);

	if (uchwytObrazu == NULL)
		return NULL;

	//informacje o bitmapie
	BITMAP obraz;
	GetObject(uchwytObrazu, sizeof(BITMAP), &obraz);
	teksturaSzer = obraz.bmWidth;
	teksturaWys = obraz.bmHeight;

	//informacja o ilosci bitow na piksel
	//char bufor[256];
	//ShowMessage(_gcvt(obraz.bmBitsPixel,10,bufor));		

	unsigned long* tekstura = new unsigned long[teksturaSzer*teksturaWys];
	switch (obraz.bmBitsPixel)
	{
	case 24:
	{
		unsigned char* tekstura24bppBRG = new unsigned char[obraz.bmWidthBytes*teksturaWys];
		memcpy(tekstura24bppBRG, obraz.bmBits, teksturaSzer*teksturaWys * 3);
		//gdybym zwrocil tekstura24bppBRG zrzutowane na unsigned long*, to powinienem uzywac do wyswietlania GL_BGR_EXT

		//konwersja na RGBA
		for (int ih = 0; ih<teksturaWys; ih++)	//kolejnosc i tak dowolna, bo tablica jednowymiarowa	
			for (int iw = 0; iw<teksturaSzer; iw++)
			{
				int i = 3 * iw + (ih*obraz.bmWidthBytes); //uwzglednia uzupelnianie do WORD
				unsigned char A = alfa;
				unsigned char B = tekstura24bppBRG[i];
				unsigned char G = tekstura24bppBRG[i + 1];
				unsigned char R = tekstura24bppBRG[i + 2];

				/*
				//jezeli konwersja na BW
				unsigned char jasnosc=(R+G+B)/3;
				R=jasnosc;
				B=jasnosc;
				G=jasnosc;
				*/

				tekstura[iw + (ih*teksturaSzer)] = (A << 24) + (B << 16) + (G << 8) + (R);
			}
		delete[] tekstura24bppBRG;
	}
		break;

	case 1:	//monochromatyczne
	{
		unsigned char* tekstura1bppMono = new unsigned char[obraz.bmWidthBytes*teksturaWys];
		memcpy(tekstura1bppMono, obraz.bmBits, obraz.bmWidthBytes*teksturaWys);

		//konwersja na RGBA				
		for (int ih = 0; ih<teksturaWys; ih++)
			for (int iw = 0; iw<teksturaSzer; iw++)
			{
				int i = iw / 8 + (ih*obraz.bmWidthBytes); //uwzglednia uzupelnianie do WORD
				int numerBitu = iw % 8;
				unsigned char A = alfa;
				bool bitZapalony = ((tekstura1bppMono[i] << numerBitu) & 128) == 128;
				//ignorujemy palete i tworzymy obraz czarno-bialy
				unsigned char B = bitZapalony ? 255 : 0;
				unsigned char G = bitZapalony ? 255 : 0;
				unsigned char R = bitZapalony ? 255 : 0;
				tekstura[iw + (ih*teksturaSzer)] = (A << 24) + (B << 16) + (G << 8) + (R);
			}
		delete[] tekstura1bppMono;
	}
		break;

	case 8: //256 kolorow, wymaga palety barw (tabeli kolorow)
	{
		unsigned char* tekstura8bppPalette = new unsigned char[obraz.bmWidthBytes*teksturaWys];
		memcpy(tekstura8bppPalette, obraz.bmBits, obraz.bmWidthBytes*teksturaWys);
		//memcpy(tekstura,tekstura8bppPalette,obraz.bmWidthBytes*teksturaWys);				

		//pobranie tabeli kolorow (pomijamy czytanie BITMAPINFO)
		HDC uchwyt = CreateCompatibleDC(GetDC(hwnd_ap));
		SelectObject(uchwyt, uchwytObrazu);
		RGBQUAD tabelaKolorow[256];
		GetDIBColorTable(uchwyt, 0, 256, tabelaKolorow);

		/*
		//standardowa paleta kolorow z systemu
		//HPALETTE uchwytPalety=(HPALETTE)GetStockObject(DEFAULT_PALETTE);
		PALETTEENTRY tabelaKolorow[256];
		GetSystemPaletteEntries(GetDC(uchwytOkna),0,256,tabelaKolorow);
		*/

		for (int ih = 0; ih<teksturaWys; ih++)	//kolejnosc i tak dowolna, bo tablica jednowymiarowa	
			for (int iw = 0; iw<teksturaSzer; iw++)
			{
				int i = iw + (ih*obraz.bmWidthBytes); //uwzglednia uzupelnianie do WORD
				unsigned char A = alfa;
				unsigned char R = tabelaKolorow[tekstura8bppPalette[i]].rgbRed;
				unsigned char G = tabelaKolorow[tekstura8bppPalette[i]].rgbGreen;
				unsigned char B = tabelaKolorow[tekstura8bppPalette[i]].rgbBlue;
				tekstura[iw + (ih*teksturaSzer)] = (A << 24) + (B << 16) + (G << 8) + (R);
			}
		delete[] tekstura8bppPalette;
	}
		break;

	case 4: //16 kolorow (paleta barw jak w Paint)
	{
		unsigned char* tekstura4bppPalette = new unsigned char[obraz.bmWidthBytes*teksturaWys];
		memcpy(tekstura4bppPalette, obraz.bmBits, obraz.bmWidthBytes*teksturaWys);

		//pobranie tabeli kolorow (pomijamy czytanie BITMAPINFO)
		HDC uchwyt = CreateCompatibleDC(GetDC(hwnd_ap));
		SelectObject(uchwyt, uchwytObrazu);
		RGBQUAD tabelaKolorow[16];
		GetDIBColorTable(uchwyt, 0, 16, tabelaKolorow);

		for (int ih = 0; ih<teksturaWys; ih++)	//kolejnosc i tak dowolna, bo tablica jednowymiarowa	
			for (int iw = 0; iw<teksturaSzer; iw++)
			{
				int i = iw / 2 + (ih*obraz.bmWidthBytes); //uwzglednia uzupelnianie do WORD
				bool pierwszaPolowaBajtu = !(iw % 2);
				unsigned char A = alfa;
				int numerKoloruZPalety = (pierwszaPolowaBajtu) ? ((tekstura4bppPalette[i] & 0xF0) >> 4) : (tekstura4bppPalette[i] & 0x0F);
				unsigned char R = tabelaKolorow[numerKoloruZPalety].rgbRed;
				unsigned char G = tabelaKolorow[numerKoloruZPalety].rgbGreen;
				unsigned char B = tabelaKolorow[numerKoloruZPalety].rgbBlue;
				tekstura[iw + (ih*teksturaSzer)] = (A << 24) + (B << 16) + (G << 8) + (R);
			}
		delete[] tekstura4bppPalette;
	}
		break;

	default: ; break;
	}

	DeleteObject(uchwytObrazu);

	return tekstura;
}
//-------------------------------------------


void TRysuj::UstawieniaSceny()
{

}

void TRysuj::Poczatek()
{

}

void TRysuj::Koniec()
{

}

void TRysuj::Kolor(GLfloat r, GLfloat g, GLfloat b)
{
	glColor3f(r, g, b);
}

void TRysuj::Punkt(GLfloat x, GLfloat y, GLfloat z)
{
	glBegin(GL_POINTS);
	glVertex3f(x, y, z);
	glEnd(); 
}

void TRysuj::Punkt(GLfloat x, GLfloat y)
{
	Punkt(x, y, 0);
}

void TRysuj::Linia(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat x1, GLfloat y1, GLfloat z1)
{
	glBegin(GL_LINES);
	glVertex3f(x0, y0, z0);
	glVertex3f(x1, y1, z1);
	glEnd();

}

void TRysuj::Linia(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1)
{
	Linia(x0, y0, 0, x1, y1, 0);
}

void TRysuj::PrzesunDo(GLfloat x, GLfloat y, GLfloat z)
{
	xpop = x;
	ypop = y;
	zpop = z;
}

void TRysuj::PrzesunDo(GLfloat x, GLfloat y)
{
	PrzesunDo(x, y, 0);
}

void TRysuj::LiniaDo(GLfloat x, GLfloat y, GLfloat z)
{
	glBegin(GL_LINES);
	glVertex3f(xpop, ypop, zpop);
	glVertex3f(xpop + x, ypop + y, zpop + z);
	glEnd();
	xpop += x;
	ypop += y;
	zpop += z;

}

void TRysuj::LiniaDo(GLfloat x, GLfloat y)
{
	LiniaDo(x, y, 0);
}

void TRysuj::Trojkat(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2)
{
	glBegin(GL_TRIANGLES);
	glVertex3f(x0, y0, z0);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}

void TRysuj::Trojkat(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	Trojkat(x0, y0, 0, x1, y1, 0, x2, y2, 0);
}

void TRysuj::UstawWspolrzedneMyszy(GLfloat x, GLfloat y)
{
	myszX = x;
	myszY = y;
}

void TRysuj::UstawWspolrzedneMyszy(GLfloat x, GLfloat y, GLfloat z)
{
	myszX = x;
	myszY = y;
	myszZ = z;
}

void TRysuj::UstawWspolrzedneMyszyKoniec(GLfloat x, GLfloat y, GLfloat z)
{
	myszX_koniec = x;
	myszY_koniec = y;
	myszZ_koniec = z;
}


GLfloat TRysuj::PodajXMyszy()
{
	return myszX;
}

GLfloat TRysuj::PodajYMyszy()
{
	return myszY;
}

GLfloat TRysuj::PodajZMyszy()
{
	return myszZ;
}

GLfloat TRysuj::PodajXMyszyKoniec()
{
	return myszX_koniec;
}

GLfloat TRysuj::PodajYMyszyKoniec()
{
	return myszY_koniec;
}

GLfloat TRysuj::PodajZMyszyKoniec()
{
	return myszZ_koniec;
}

void TRysuj::Przerysowywanie()
{
	if (ObrotScenyTN)
	{
		glTranslatef(0, 0.0, -100.0f);
		ObrotOsX(katX);
		ObrotOsY(katY);
	}
	Przerysuj();
}

void TRysuj::RuchMyszy(GLfloat x, GLfloat y)
{
//	UstawWspolrzedneMyszy(x, y);
//	Odswiez();
}

void TRysuj::RuchMyszy(GLfloat x, GLfloat y, GLfloat z)
{
	UstawWspolrzedneMyszy(x, y, z);
//	Odswiez();
}

void TRysuj::RuchMyszy(GLfloat x_poczatek, GLfloat y_poczatek, GLfloat z_poczatek, GLfloat x_koniec, GLfloat y_koniec, GLfloat z_koniec)
{
	UstawWspolrzedneMyszy(x_poczatek, y_poczatek, z_poczatek);
	UstawWspolrzedneMyszyKoniec(x_koniec, y_koniec, z_koniec);
//	Odswiez();
}


void TRysuj::UstawRozmiaryEkranu(GLfloat szer, GLfloat wys)
{
	SzerokoscEkranu = szer;
	WysokoscEkranu = wys;
}

void TRysuj::ObrotSceny(bool TN)
{
	ObrotScenyTN = TN;
}

GLfloat TRysuj::PodajSzerokoscEkranu()
{
	return SzerokoscEkranu;
}

GLfloat TRysuj::PodajWysokoscEkranu()
{
	return WysokoscEkranu;
}

void TRysuj::ObrotOsX(GLfloat kat)
{
	glRotatef(kat, 1, 0, 0);
}

void TRysuj::ObrotOsY(GLfloat kat)
{
	glRotatef(kat, 0, 1, 0);
}

void TRysuj::ObrotOsZ(GLfloat kat)
{
	glRotatef(kat, 0, 0, 1);
}

GLvoid TRysuj::Pisz(GLfloat x, GLfloat y, int RozmiarCzcionki, const char *fmt, ...)
{
	char        text[256];        
	va_list        ap;

	if (RozmiarCzcionki < 0)
		RozmiarCzcionki = 0;
	if (RozmiarCzcionki >= ILE_CZCIONEK)
		RozmiarCzcionki = ILE_CZCIONEK - 1;

	if (fmt == NULL)        
		return;

	glRasterPos2f(x, y);

	va_start(ap, fmt);
	vsnprintf_s(text,256, fmt, ap);         
	va_end(ap);

	glPushAttrib(GL_LIST_BIT);      
	glListBase(TAplikacja::base[RozmiarCzcionki] - 32);

	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);        
	glPopAttrib();       

}

void TRysuj::Odswiez()
{
	if (hwnd_ap)
		InvalidateRect(hwnd_ap, NULL, TRUE);
}

void TRysuj::UstawUchwytOkienka(HWND hwnd)
{
	hwnd_ap = hwnd;
}



TRysuj::TRysuj()
{
	ObrotScenyTN = true;

	xpop = 0;
	ypop = 0;
	zpop = 0;

	myszX = -1;
	myszY = -1;
	myszZ = -1;
	myszX_koniec = -1;
	myszY_koniec = -1;
	myszZ_koniec = -1;

	hwnd_ap = 0;

	SzerokoscEkranu = 0;
	WysokoscEkranu = 0;

	katX = 0;
	katY = 0;

}


void TRysuj::PrawyPrzyciskMyszyWcisniety()
{

}

void TRysuj::PrawyPrzyciskMyszyPuszczony()
{

}

void TRysuj::LewyPrzyciskMyszyWcisniety()
{

}
void TRysuj::LewyPrzyciskMyszyPuszczony()
{

}

void TRysuj::LewyPrzyciskPodwojneKlikniencie()
{

}

void TRysuj::Zegar(int numer)
{

}

void TRysuj::KlawiszWcisniety(int klawisz)
{
	if (ObrotScenyTN)
	{
		switch (klawisz)
		{
		case VK_LEFT:
			katY += SKOK_KATA;
			Odswiez();
			break;
		case VK_RIGHT:
			katY -= SKOK_KATA;
			Odswiez();
			break;
		case VK_UP:
			katX += SKOK_KATA;
			Odswiez();
			break;
		case VK_DOWN:
			katX -= SKOK_KATA;
			Odswiez();
			break;
		case VK_ESCAPE:
			katX = 0;
			katY = 0;
			Odswiez();
			break;
		}
	}
}

void TRysuj::ZmianaRozmiaruEkranu()
{

}


void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fW, fH;

	//fH = tan( (fovY / 2) / 180 * pi ) * zNear;
	fH = tan(fovY / 360 * pi) * zNear;
	fW = fH * aspect;

	glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

void TAplikacja::UstawienieSceny()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glViewport(0, 0, SzerokoscObszaruUzytkownika, WysokoscObszaruUzytkownika);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	float wsp = SzerokoscObszaruUzytkownika / float(WysokoscObszaruUzytkownika);
//	glOrtho(-SzerokoscObszaruUzytkownika / 2, SzerokoscObszaruUzytkownika / 2, -WysokoscObszaruUzytkownika / 2, WysokoscObszaruUzytkownika / 2, 0, 10000);
//	glMatrixMode(GL_MODELVIEW);
//	glFrustum(-2.0 * SzerokoscObszaruUzytkownika / WysokoscObszaruUzytkownika, 2.0 * SzerokoscObszaruUzytkownika / WysokoscObszaruUzytkownika, -10.0, 10.0, -50.0, 4000.0);
	perspectiveGL(45, wsp, 1, 400.0f);
	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	
//	glDisable(GL_SCISSOR_TEST);
	if (rysuj != NULL)
		rysuj->UstawieniaSceny();
	BuildFont();
}


void TAplikacja::WylaczOpenGL(HWND hWnd)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hWnd, hDC);
}


void TAplikacja::WlaczOpenGL(HWND hWnd)//, HDC *hDC, HGLRC *hRC)
{
	PIXELFORMATDESCRIPTOR pfd;
	int iFormat;

	/* get the device context (DC) */
	hDC = GetDC(hWnd);
	
	/* set the pixel format for the DC */
	ZeroMemory(&pfd, sizeof (pfd));
	pfd.nSize = sizeof (pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
//	pfd.cColorBits = 24;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	iFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, iFormat, &pfd);

	/* create and enable the render context (RC) */
	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);

}

bool TAplikacja::UstawZegar(int numer, int czas_ms)
{
	if (numer < 0 || numer > MAX_ILOSC_ZEGAROW)
		return false;
	if (czas_ms <= 0)
		return false;
	if (!hwnd_ap)
		return false;

	if (SetTimer(hwnd_ap, ID_TIMER + numer, czas_ms, NULL) == 0)
		return false;
	else
		return true;
}

bool TAplikacja::WylaczZegar(int numer)
{
	if (numer < 0 || numer > MAX_ILOSC_ZEGAROW)
		return false;
	if (!hwnd_ap)
		return false;

	KillTimer(hwnd_ap, ID_TIMER + numer);

	return true;
}


void TAplikacja::KasujZegary()
{
	int i;

	for (i = 0; i < MAX_ILOSC_ZEGAROW; i++)
		if (zegar[i] && hwnd_ap)
			KillTimer(hwnd_ap, ID_TIMER + i);
}

GLvoid TAplikacja::BuildFont(GLvoid)
{
	HFONT    font;        
	HFONT    oldfont; 
	int i;
	for (i = 0; i < ILE_CZCIONEK; i++)
	{
		base[i] = glGenLists(255);
		font = CreateFont(RozmiaryCzcnionek[i], 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, L"Courier New");

		oldfont = (HFONT)SelectObject(hDC, font);
		wglUseFontBitmaps(hDC, 32, 255, base[i]);
		SelectObject(hDC, oldfont);
		DeleteObject(font);
	}
}

GLvoid TAplikacja::KillFont(GLvoid)
{
	int i;

	for (i = 0; i < ILE_CZCIONEK; i++)
	{
		glDeleteLists(base[i], 96);
	}
}

BOOL TAplikacja::InitInstance()
{


	hwnd_ap = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hwnd_ap)
	{
		return FALSE;
	}

	ShowWindow(hwnd_ap, nCmdShow);
	UpdateWindow(hwnd_ap);

	return TRUE;
}

INT_PTR CALLBACK TAplikacja::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


LRESULT CALLBACK TAplikacja::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	RECT rect;

	switch (message)
	{
	case WM_CREATE:
		WlaczOpenGL(hWnd);
		if (rysuj != NULL)
		{
			rysuj->Poczatek();
		}
		UstawienieSceny();
		SetTimer(hWnd, ID_TIMER, 1000, NULL);

		GetClientRect(hWnd, &rect);
		SzerokoscObszaruUzytkownika = rect.right - rect.left;
		WysokoscObszaruUzytkownika = rect.bottom - rect.top;
		if (rysuj != NULL)
		{
			rysuj->UstawRozmiaryEkranu(GLfloat(SzerokoscObszaruUzytkownika), GLfloat(WysokoscObszaruUzytkownika));
		}


		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Analizuj zaznaczenia menu:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, &TAplikacja::About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_MOUSEMOVE:
		if (rysuj != NULL)
		{

			double matModelView[16], matProjection[16];
			GLdouble X, Y, Z, X2, Y2, Z2;
			int viewport[4];
			glGetDoublev(GL_MODELVIEW_MATRIX, matModelView);
			glGetDoublev(GL_PROJECTION_MATRIX, matProjection);
			glGetIntegerv(GL_VIEWPORT, viewport);
			double winX = (double)GET_X_LPARAM(lParam);
			double winY = viewport[3] - (double)GET_Y_LPARAM(lParam);
			rysuj->RuchMyszy((GLfloat)winX, (GLfloat)winY);
			gluUnProject(winX, winY, 0.0, matModelView, matProjection,
				viewport, &X, &Y, &Z);
			gluUnProject(winX, winY, 1.0, matModelView, matProjection,
				viewport, &X2, &Y2, &Z2);

			rysuj->RuchMyszy((GLfloat)X, (GLfloat)Y, (GLfloat)Z, (GLfloat)X2, (GLfloat)Y2, (GLfloat)Z2);

		}
		break;
	case WM_LBUTTONDOWN:
		if (rysuj != NULL)
			rysuj->LewyPrzyciskMyszyWcisniety();
		break;
	case WM_LBUTTONUP:
		if (rysuj != NULL)
			rysuj->LewyPrzyciskMyszyPuszczony();
		break;
	case WM_LBUTTONDBLCLK:
		if (rysuj != NULL)
			rysuj->LewyPrzyciskPodwojneKlikniencie();
		break;
	case WM_RBUTTONDOWN:
		if (rysuj != NULL)
			rysuj->PrawyPrzyciskMyszyWcisniety();
		break;
	case WM_RBUTTONUP:
		if (rysuj != NULL)
			rysuj->PrawyPrzyciskMyszyPuszczony();
		break;
	case WM_TIMER:
		if (rysuj != NULL)
			rysuj->Zegar(wParam - ID_TIMER);
		break;
	case WM_KEYDOWN:
		if (rysuj != NULL)
			rysuj->KlawiszWcisniety(wParam);
		break;
	case WM_PAINT:


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glTranslatef(0.0, 0.0, -1.0);


		if (rysuj != NULL)
		{
			rysuj->Przerysowywanie();
			if (poczatek)
			{
				poczatek = false;
				rysuj->ZmianaRozmiaruEkranu();
			}
		}

		glFlush();

		glPopMatrix();
		SwapBuffers(hDC);


		ValidateRect(hWnd, NULL);
		break;
	case WM_SIZE:
		GetClientRect(hWnd, &rect);
		SzerokoscObszaruUzytkownika = rect.right - rect.left;
		WysokoscObszaruUzytkownika = rect.bottom - rect.top;
		UstawienieSceny();
		if (rysuj != NULL)
		{
			rysuj->UstawRozmiaryEkranu(GLfloat(SzerokoscObszaruUzytkownika), GLfloat(WysokoscObszaruUzytkownika));
			rysuj->ZmianaRozmiaruEkranu();
		}
		break;
	case WM_DESTROY:
		KasujZegary();
		if (rysuj != NULL)
		{
			rysuj->Koniec();
		}
		KillTimer(hWnd, ID_TIMER);
		WylaczOpenGL(hWnd);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

ATOM TAplikacja::MyRegisterClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = TAplikacja::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OPENGL));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = NULL;//(HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_OPENGL);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

void TAplikacja::UstawParametryEkranu()
{
//	rysuj = rysuj_;
	if (rysuj != NULL && hwnd_ap)
	{
		rysuj->UstawUchwytOkienka(hwnd_ap);
		rysuj->UstawRozmiaryEkranu(GLfloat(SzerokoscObszaruUzytkownika), GLfloat(WysokoscObszaruUzytkownika));
		rysuj->UstawieniaSceny();
	}
	if (hwnd_ap)
		InvalidateRect(hwnd_ap, NULL, TRUE);
}

WPARAM TAplikacja::PetlaWiadomosci()
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

TAplikacja::TAplikacja(_In_ HINSTANCE _hInstance, int _nCmdShow, TRysuj *rys)
{
	int i;

	rysuj = rys;

	hInstance = _hInstance;
	nCmdShow = _nCmdShow;

	for (i = 0; i < MAX_ILOSC_ZEGAROW; i++)
		zegar[i] = false;

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_OPENGL, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass();

	if (InitInstance())
	{
		InicjalizacjaPoprawna = true;
		hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OPENGL));
	}
	else
		InicjalizacjaPoprawna = false;
}

TAplikacja::~TAplikacja()
{
	_CrtDumpMemoryLeaks();

}

