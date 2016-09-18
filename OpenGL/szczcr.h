#include "Szescian.h"
#include "OpenGL.h"
#include <math.h>

// #define RYSUJWEKTORY

void Szescian::Przerysuj()
{
	float wsp_odbicia[4] = {0.0f,0.0f,0.0f,1.0f};
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,wsp_odbicia);
	glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,30);
	glBegin(GL_QUADS);
		glColor3f(this->kolor_r,this->kolor_g,this->kolor_b);
       // Tylna œciana        
		float QA[3] = {-x,-y,z};
		float QB[3] = {x,-y,z};
		float QC[3] = {x,y,z};
		float QD[3] = {-x,y,z};
		
		float pointA = QB[0]-QA[0];
		float pointB = QB[1]-QA[1];
		float pointC = QB[2]-QA[2];
		
		float NpointA = QC[0]-QA[0];
		float NpointB = QC[1]-QA[1];
		float NpointC = QC[2]-QA[2];

		float Iloczyn[3] = {NpointB*pointC - NpointC*pointB,NpointC*pointA - NpointA*pointC,NpointA*pointB - NpointB*pointA};
		float IloczynN = (sqrt((Iloczyn[0]*Iloczyn[0])+(Iloczyn[1]*Iloczyn[1])+(Iloczyn[2]*Iloczyn[2])));
		Iloczyn[0] = Iloczyn[0]/IloczynN;
		Iloczyn[1] = Iloczyn[1]/IloczynN;
		Iloczyn[2] = Iloczyn[2]/IloczynN;
		glNormal3fv(Iloczyn);

		glVertex3fv(QA);
        glVertex3fv(QB);
        glVertex3fv(QC); 
        glVertex3fv(QD);
	glEnd();
	#ifdef RYSUJWEKTORY
		wektor.RysujWektoryNormalne(QA,Iloczyn);
		wektor.RysujWektoryNormalne(QB,Iloczyn);
		wektor.RysujWektoryNormalne(QC,Iloczyn);
		wektor.RysujWektoryNormalne(QD,Iloczyn);
	#endif
	glBegin(GL_QUADS);
		glColor3f(this->kolor_r,this->kolor_g,this->kolor_b);
		// Przednia œciana        
		QA[0] = -x;		QB[0] = -x;		QC[0] = x;		QD[0] = x;
		QA[1] = -y;		QB[1] = y;		QC[1] = y;		QD[1] = -y;
		QA[2] = z+y;	QB[2] = z+y;	QC[2] = z+y;	QD[2] = z+y;

		pointA = QB[0]-QA[0];
		pointB = QB[1]-QA[1];
		pointC = QB[2]-QA[2];
		
		NpointA = QC[0]-QA[0];
		NpointB = QC[1]-QA[1];
		NpointC = QC[2]-QA[2];

		Iloczyn[0] = NpointB*pointC - NpointC*pointB;
		Iloczyn[1] = NpointC*pointA - NpointA*pointC;
		Iloczyn[2] = NpointA*pointB - NpointB*pointA;

	    IloczynN = (sqrt((Iloczyn[0]*Iloczyn[0])+(Iloczyn[1]*Iloczyn[1])+(Iloczyn[2]*Iloczyn[2])));
		Iloczyn[0] = Iloczyn[0]/IloczynN;
		Iloczyn[1] = Iloczyn[1]/IloczynN;
		Iloczyn[2] = Iloczyn[2]/IloczynN;
		glNormal3fv(Iloczyn);

        glVertex3fv(QA);        
        glVertex3fv(QB);         
        glVertex3fv(QC);         
        glVertex3fv(QD);
	glEnd();
	
	#ifdef RYSUJWEKTORY
		wektor.RysujWektoryNormalne(QA,Iloczyn);
		wektor.RysujWektoryNormalne(QB,Iloczyn);
		wektor.RysujWektoryNormalne(QC,Iloczyn);
		wektor.RysujWektoryNormalne(QD,Iloczyn);
	#endif

	glBegin(GL_QUADS);
		glColor3f(this->kolor_r,this->kolor_g,this->kolor_b);
		// Górna œciana       
		QA[0] = -x;		QB[0] = -x;		QC[0] = x;		QD[0] = x;
		QA[1] = y;		QB[1] = y;		QC[1] = y;		QD[1] = y;
		QA[2] = z;		QB[2] = z+y;	QC[2] = z+y;	QD[2] = z;

		pointA = QD[0]-QB[0];
		pointB = QD[1]-QB[1];
		pointC = QD[2]-QB[2];
		
		NpointA = QC[0]-QB[0];
		NpointB = QC[1]-QB[1];
		NpointC = QC[2]-QB[2];

		Iloczyn[0] = NpointB*pointC - NpointC*pointB;
		Iloczyn[1] = NpointC*pointA - NpointA*pointC;
		Iloczyn[2] = NpointA*pointB - NpointB*pointA;

	    IloczynN = (sqrt((Iloczyn[0]*Iloczyn[0])+(Iloczyn[1]*Iloczyn[1])+(Iloczyn[2]*Iloczyn[2])));
		Iloczyn[0] = Iloczyn[0]/IloczynN;
		Iloczyn[1] = Iloczyn[1]/IloczynN;
		Iloczyn[2] = Iloczyn[2]/IloczynN;
		glNormal3fv(Iloczyn);

        glVertex3fv(QA);        
        glVertex3fv(QB);         
        glVertex3fv(QC);         
        glVertex3fv(QD);
	glEnd();

	#ifdef RYSUJWEKTORY
		wektor.RysujWektoryNormalne(QA,Iloczyn);
		wektor.RysujWektoryNormalne(QB,Iloczyn);
		wektor.RysujWektoryNormalne(QC,Iloczyn);
		wektor.RysujWektoryNormalne(QD,Iloczyn);
	#endif

	glBegin(GL_QUADS);
		glColor3f(this->kolor_r,this->kolor_g,this->kolor_b);
        // Lewa œciana
		QA[0] = -x;		QB[0] = -x;		QC[0] = -x;		QD[0] = -x;
		QA[1] = -y;		QB[1] = y;		QC[1] = y;		QD[1] = -y;
		QA[2] = z;		QB[2] = z;		QC[2] = z+y;	QD[2] = z+y;

		pointA = QB[0]-QA[0];
		pointB = QB[1]-QA[1];
		pointC = QB[2]-QA[2];
		
		NpointA = QC[0]-QA[0];
		NpointB = QC[1]-QA[1];
		NpointC = QC[2]-QA[2];

		Iloczyn[0] = NpointB*pointC - NpointC*pointB;
		Iloczyn[1] = NpointC*pointA - NpointA*pointC;
		Iloczyn[2] = NpointA*pointB - NpointB*pointA;

	    IloczynN = (sqrt((Iloczyn[0]*Iloczyn[0])+(Iloczyn[1]*Iloczyn[1])+(Iloczyn[2]*Iloczyn[2])));
		Iloczyn[0] = Iloczyn[0]/IloczynN;
		Iloczyn[1] = Iloczyn[1]/IloczynN;
		Iloczyn[2] = Iloczyn[2]/IloczynN;
		glNormal3fv(Iloczyn);

        glVertex3fv(QA);        
        glVertex3fv(QB);         
        glVertex3fv(QC);         
        glVertex3fv(QD);
	glEnd();
	
	#ifdef RYSUJWEKTORY
		wektor.RysujWektoryNormalne(QA,Iloczyn);
		wektor.RysujWektoryNormalne(QB,Iloczyn);
		wektor.RysujWektoryNormalne(QC,Iloczyn);
		wektor.RysujWektoryNormalne(QD,Iloczyn);
	#endif

	glBegin(GL_QUADS);
		glColor3f(this->kolor_r,this->kolor_g,this->kolor_b);
        // Prawa œciana           
		QA[0] = x;		QB[0] = x;		QC[0] = x;		QD[0] = x;
		QA[1] = -y;		QB[1] = y;		QC[1] = y;		QD[1] = -y;
		QA[2] = z;		QB[2] = z;		QC[2] = z+y;	QD[2] = z+y;

		pointA = QD[0]-QB[0];
		pointB = QD[1]-QB[1];
		pointC = QD[2]-QB[2];
		
		NpointA = QC[0]-QB[0];
		NpointB = QC[1]-QB[1];
		NpointC = QC[2]-QB[2];

		Iloczyn[0] = NpointB*pointC - NpointC*pointB;
		Iloczyn[1] = NpointC*pointA - NpointA*pointC;
		Iloczyn[2] = NpointA*pointB - NpointB*pointA;

	    IloczynN = (sqrt((Iloczyn[0]*Iloczyn[0])+(Iloczyn[1]*Iloczyn[1])+(Iloczyn[2]*Iloczyn[2])));
		Iloczyn[0] = Iloczyn[0]/IloczynN;
		Iloczyn[1] = Iloczyn[1]/IloczynN;
		Iloczyn[2] = Iloczyn[2]/IloczynN;
		glNormal3fv(Iloczyn);

        glVertex3fv(QA);        
        glVertex3fv(QB);         
        glVertex3fv(QC);         
        glVertex3fv(QD);
	glEnd();
	
	#ifdef RYSUJWEKTORY
		wektor.RysujWektoryNormalne(QA,Iloczyn);
		wektor.RysujWektoryNormalne(QB,Iloczyn);
		wektor.RysujWektoryNormalne(QC,Iloczyn);
		wektor.RysujWektoryNormalne(QD,Iloczyn);
	#endif
}

