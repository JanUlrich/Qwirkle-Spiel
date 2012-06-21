#include <cstdlib>
#include <iostream>
//#include <conio.h>
#include <stdio.h>
//#include <windows.h>
#include <time.h>
#include "Farbe.h"

//
//Vincent Musch
//Spielfeld Qwikle (1)
//15.02.2012
#define FarbeBlau    1
#define FarbeRot     2



using namespace std;

//Variablen Deklarieren
 int x = 0;
 int y = 0;

char cBewegung;
int Punkte;



//Unverï¿½nderbare variablen
const int iBreite = 15;
const int iHoehe = 15;
const int spielsteinBeutelGroesse = 7; //spielsteinBeutelGroesse muss kleiner als 10 sein!
const int anzahlSpielsteine = 100;
const int anzahlFarben=2;
const int anzahlFormen=4;

struct Spielstein
{
       int farbe;
       char form;
};

//Variablen mit "Eigenschaften"
struct S_Feld
{
       bool Besetzt;
       bool Ausgeweahlt;
       bool punkterechnung;
       
       Spielstein * spielstein;
       
};

struct Spieler
{
	int spielerNummer;
	bool istComputerGegner;
	//Der Spielsteinbeutel des Spielers:
	Spielstein * spielsteinBeutel[spielsteinBeutelGroesse];
	bool zugBeendet;
	bool darfSteineTauschen;
	int punktestand;
	};

//Arrar
//fï¿½rs spielfeld
S_Feld Spielfeld[iBreite][iHoehe];

//fï¿½r ausgewï¿½hltes feld
S_Feld Ausgewaehlt[iBreite][iHoehe];



//Alle Spielsteine des Spiels:
Spielstein * spielsteine[anzahlSpielsteine];

int anzahlSpieler = 0;
Spieler ** mitSpieler = 0;

//Der Spieler, welcher an der Reihe ist:
Spieler * aktiverSpieler = 0;

//prototyp
void ZeigeSpielfeld();
void Feldauswahl();
Spielstein * gibSpielstein();
void zeigeSpielsteine(Spielstein * beutel[spielsteinBeutelGroesse]);
int spielsteinAuswaehlen(Spielstein * beutel[spielsteinBeutelGroesse]);
void spielsteinAnzeigen(Spielstein * st);
void fuelleSpielsteinBeutel(Spielstein * beutel[spielsteinBeutelGroesse]);
void initialisiereSpielsteine();
char gibZeichen();
void setzeSpielstein(Spielstein * ausBeutel[spielsteinBeutelGroesse], int spielsteinNr, int x, int y);
bool darfsetzen(int x, int y, Spielstein * st);
void beenden();
void spielzugKI();
void spielzugMenschlicherSpieler();
int punkteRechnen(int x, int y);

void neuerSpieler(bool computerGegner){
	Spieler ** newMitSpieler = new Spieler*[anzahlSpieler+1];
	for(int i=0; i< anzahlSpieler;i++)newMitSpieler[i]=mitSpieler[i];//mitSpieler kopieren
	if(mitSpieler != 0){
		free(mitSpieler); // Speicher clearen
	}
	// Spieler anfügen ....
	newMitSpieler[anzahlSpieler]=new Spieler;
	newMitSpieler[anzahlSpieler]->istComputerGegner = computerGegner;
	fuelleSpielsteinBeutel(newMitSpieler[anzahlSpieler]->spielsteinBeutel);
	newMitSpieler[anzahlSpieler]->spielerNummer = anzahlSpieler;
	newMitSpieler[anzahlSpieler]->punktestand = 0;
	// ....................
	mitSpieler = newMitSpieler;
	anzahlSpieler++;
}

void naechsterSpieler() // setzt den naechsten Spieler als aktiven Spieler
{
	if(aktiverSpieler!=0){
	aktiverSpieler = mitSpieler[(aktiverSpieler->spielerNummer+1)%anzahlSpieler];
	}else{
		aktiverSpieler = mitSpieler[0];
	}
	aktiverSpieler->zugBeendet = false;
	aktiverSpieler->darfSteineTauschen = true;
}

int main(int argc, char *argv[])
{
//Initialisierung:===============
//alle felder = 0 setzen
      for (int yi=0; yi<iHoehe; yi++)
      {
             for (int xi=0; xi<iBreite; xi++)
             {
                 Spielfeld[xi][yi].Besetzt = false;
             }
      }
      initialisiereSpielsteine();
//==============================
      neuerSpieler(false); // einen Spieler erstellen

while(true){ //endlosschleife! Hier findet das eigentliche Spielen statt
    naechsterSpieler();
    do{
    	if(aktiverSpieler->istComputerGegner)
    	{
    		spielzugKI();
    	}else{
    		spielzugMenschlicherSpieler();
    	}
 }while (aktiverSpieler->zugBeendet);//(chauswahl != 1)||(chauswahl != 2));
}

}

void beenden()
{
	exit(0);
}

void spielzugKI()
{

}

void spielzugMenschlicherSpieler()
{
	//Lokale Variable
	char chauswahl;

    printf("Feld Anzeigen(1)\n");
    printf("Feld Besetzten(2)\n");
    printf("Steine tauschen(3)\n");
    printf("Zug beenden(4)\n");
    printf("Spiel Beenden(5)\n");
    chauswahl = gibZeichen();

    if(chauswahl == '1')
    {
          ZeigeSpielfeld();
    }
    else if(chauswahl == '2')
    {    
          ZeigeSpielfeld();
          Feldauswahl();
          //darfsetzen();
    }
    
    else if(chauswahl == '3')
    {
         printf("Programm wird Beendet!\n");
         
         beenden();
    }
    else if(chauswahl == '4'){
    	aktiverSpieler->zugBeendet = true;
    }
    else
    {
        printf("Falsche Eingabe!\n");
    }
}

void initialisiereSpielsteine()
{
 char form = 'A';
	int farben[anzahlFarben]={FarbeRot, FarbeBlau};
	int formNr=0;
	int farbenNr=0;
	for(int i=0;i<anzahlSpielsteine;i++)
	{
		formNr++;
		formNr=formNr%anzahlFormen;
		if(formNr==0)
		{
		farbenNr++;
		farbenNr=farbenNr%anzahlFarben;
		}
		Spielstein *st = new Spielstein;
		st->farbe=farben[farbenNr];
		st->form=(char)(form+formNr);
		spielsteine[i]=st;
	}
}

Spielstein * gibSpielstein(){
	for(int i=0;i<anzahlSpielsteine;i++)
	{
		if(spielsteine[i]!=0){
			Spielstein * st = spielsteine[i];
			spielsteine[i]=0; //Spielstein aus dem Pool entfernen
			return st;
		}
	}
	printf("Alle Spielsteine aufgebraucht! Spielende!");
	return 0;//TODO Spiel beenden
}

void fuelleSpielsteinBeutel(Spielstein * beutel[spielsteinBeutelGroesse])
{
	for(int i=0;i<spielsteinBeutelGroesse;i++)
	{
		if(beutel[i]==0)beutel[i]=gibSpielstein();
	}
}

void ZeigeSpielfeld()
{
      //system("cls");
     printf("%d\n",x);
     printf("%d\n",y);
     printf("%d\n",Punkte);
     //printf(cansetr1<<endl;
     //printf(cansetr2<<endl;

     for (int yi=0; yi<iHoehe; yi++)
         {
             for (int xi=0; xi<iBreite; xi++)
             {         
                                
                     //besetzt von curser
                     if(Spielfeld[xi][yi].Besetzt == false && xi == x && yi == y )
                     {   
                         printf("() ");
                     }

                     else if(Spielfeld[xi][yi].Besetzt == true)
                     {    
                    	 spielsteinAnzeigen(Spielfeld[xi][yi].spielstein);
                     }
                    
                     else
                     {
                          printf("[] ");
                     }
             }
             
             printf("\n");
        
         }
}

void zugBeenden(){

}

void Feldauswahl()
{
     
      do{
      
     
     do{
     cBewegung = gibZeichen();
     }while(cBewegung<0); //behebt Bug bei drï¿½cken von Pfeiltasten
     
     if((cBewegung == 72))
     {
          //Nach oben Bewegen
          y = y-1;
          //Curser 
         //Spielfeld[x][y].Besetzt = true;
     }
     
     else if((cBewegung == 80))
     {
          //Nach unten Bewegen
          y = y+1;
          //Curser 
         //Spielfeld[x][y].Besetzt = true;
     }
     
     else if((cBewegung == 77)||(cBewegung == 'a'))
     {
          //Nach Rechts
          x = x+1;
          //Curser 
         //Spielfeld[x][y].Besetzt = true;
     }
     
     else if((cBewegung == 75))
     {
          //Nach Links
          x = x-1;
         //Curser 
         //Spielfeld[x][y].Besetzt = true;

     }
     

     else if (cBewegung == (char) 115){ //115 == 's' 13 == Enter
    	 int gewahlterSpielstein = spielsteinAuswaehlen(aktiverSpieler->spielsteinBeutel);
    	 //hier noch eine Abrfrage, welche abfrägt, dass Spielsteine nur in Reihen gelegt werden dürfen.
    	 if(darfsetzen(x,y,aktiverSpieler->spielsteinBeutel[gewahlterSpielstein])){
    	 setzeSpielstein(aktiverSpieler->spielsteinBeutel, gewahlterSpielstein,x,y);
    	 aktiverSpieler->punktestand += punkteRechnen(x,y);
    	 	//break;
    	 }else{
    		 printf("Nicht möglich!");
    	 }
           }
     printf("Punktestand Spieler %d: %d\n",aktiverSpieler->spielerNummer , aktiverSpieler->punktestand);
     ZeigeSpielfeld();
}while(cBewegung != 115 || cBewegung != 27); //27 == ESC
}

void setzeSpielstein(Spielstein * ausBeutel[spielsteinBeutelGroesse], int spielsteinNr, int x, int y)
{
	Spielfeld[x][y].spielstein = ausBeutel[spielsteinNr];
	Spielfeld[x][y].Besetzt = true;
	ausBeutel[spielsteinNr]=0;//Spielstein aus Beutel entfernen
}

int spielsteinAuswaehlen(Spielstein * beutel[spielsteinBeutelGroesse])
{
	zeigeSpielsteine(beutel);
	int spielsteinNr;
	do{ //funktioniert nur fÃ¼r spielsteinBeutelGroesse<10
		printf("Zum AuswÃ¤hlen des Spielsteins seine Nummer eingeben:\n");
		spielsteinNr = (int) gibZeichen()-49;
	}while(spielsteinNr<0 || spielsteinNr>spielsteinBeutelGroesse || beutel[spielsteinNr]==0);
	return spielsteinNr;
}

void zeigeSpielsteine(Spielstein * beutel[spielsteinBeutelGroesse])
{
	for(int i=0;i<spielsteinBeutelGroesse;i++)
	{
		printf("\n%d : ",i+1);
		if(beutel[i]!=0)
		{
			spielsteinAnzeigen(beutel[i]);
		}else{
			//kein Spielstein an diesem Platz im Beutel!
		}
	}
}

void spielsteinAnzeigen(Spielstein * st)
{
	//Farbe(Spielfeld[xi][yi].spielstein.farbe,0);
	printf(" ");
	printf("%d %c",st->farbe,st->form);
	printf(" ");
	//Farbe(15,0);
}

bool checkReihe(Spielstein * Reihe[iBreite]){
	for(int i=0;i<iBreite-1;i++)
     {
		if(Reihe[i+1]!=0){//Vergleich nur möglich, wenn Spielstein an nächste Position
		bool gleicheFarbe=Reihe[i]->farbe == Reihe[i+1]->farbe;
		bool gleicheForm=Reihe[i]->form == Reihe[i+1]->form;
		if(!gleicheFarbe && !gleicheForm)return false;
		}

     }
	return true;
     }       

char gibZeichen()
{
	char c = getchar();
	//printf("%d",c); //Für Debug-Zwecke
	getchar();
	return c;
}


bool darfsetzen(int x, int y, Spielstein * st)
{
     if(Spielfeld[x][y].Besetzt == true)return false;
     int anzahlGesetzterSteine=0;
     for(int xi; xi<iBreite;xi++)for(int yi;yi<iHoehe;yi++){
    	 if(Spielfeld[xi][yi].Besetzt)anzahlGesetzterSteine++;
     }
     if(Spielfeld[x+1][y].Besetzt == false && Spielfeld[x-1][y].Besetzt == false && Spielfeld[x][y+1].Besetzt == false && Spielfeld[x][y-1].Besetzt == false && anzahlGesetzterSteine>0)return false;
     
     bool gueltig=true;

     //Spielstein probeweise setzen:
     Spielfeld[x][y].Besetzt = true;
     Spielfeld[x][y].spielstein = st;

     Spielstein * Reihe[iBreite];
                  for(int i=0;i<iBreite;i++){
                          Reihe[i]=0;
                          }
                  int iReihe=0;

     for(bool diagonal = true; diagonal;diagonal=false)
     for(int yi=0;yi<iHoehe;yi++){
     for(int xi=0;xi<iBreite;xi++)
     {
    	 if(diagonal==false){
    		 int xitemp=xi;
    		 xi=yi;
    		 yi=xitemp;
    	 }
             if(Spielfeld[xi][yi].Besetzt==true)
             {
             Reihe[iReihe] = Spielfeld[xi][yi].spielstein;
             iReihe++;
             }else{
             if(checkReihe(Reihe)==false)gueltig = false;
             for(int i=0;i<iBreite;i++){
                     Reihe[i]=0;
                     }
             iReihe=0;
             }
             }
     }
     //Spielstein wieder entfernen:
	  Spielfeld[x][y].Besetzt = false;
	  Spielfeld[x][y].spielstein = 0;

     return gueltig;

}

//Rechnet die Punkte aus, welcher ein neu gelegter Spielstein an Position x,y einbringt.
int punkteRechnen(int x, int y)
{
	if(!Spielfeld[x][y].Besetzt)return 0; // Ist das Spielfeld nicht besetzt, gibt es auch keine Punkte!
	int endpunktzahl = 1; //Ein Punkt für den Ausgangsspielstein

	int punkteReihe = 0;
	for(int off = -1; off==-1 || off==1;off += 2){
		int xi=0;
		do{
			xi+=off;
			if(xi<0 || xi>iBreite)break;
			if(Spielfeld[xi][y].Besetzt)punkteReihe++;
		}while(Spielfeld[xi][y].Besetzt); //Ein unbesetzter Spielfeldplatz unterbricht die Reihe!
	}
	if(punkteReihe==6)punkteReihe=12; //Qwirkle!
	endpunktzahl +=punkteReihe;

	punkteReihe = 0;
		for(int off = -1; off==-1 || off==1;off += 2){
			int yi=0;
			do{
				yi+=off;
				if(yi<0 || yi>iHoehe)break;
				if(Spielfeld[x][yi].Besetzt)punkteReihe++;
			}while(Spielfeld[x][yi].Besetzt); //Ein unbesetzter Spielfeldplatz unterbricht die Reihe!
		}
	if(punkteReihe==6)punkteReihe=12; //Qwirkle!
	endpunktzahl +=punkteReihe;

	return endpunktzahl;
}

void spielsteinSetzenDurchKI(){

}
