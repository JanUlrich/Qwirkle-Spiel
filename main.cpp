#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "Farbe.h"

//
//Vincent Musch
//Spielfeld Qwikle (1)
//15.02.2012
#define FarbeBlau    1
#define FarbeRot     2

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

//Arrar
//fï¿½rs spielfeld
S_Feld Spielfeld[iBreite][iHoehe];

//fï¿½r ausgewï¿½hltes feld
S_Feld Ausgewaehlt[iBreite][iHoehe];

//Der Spielsteinbeutel des Spielers:
Spielstein * spielsteinBeutel[spielsteinBeutelGroesse];

//Alle Spielsteine des Spiels:
Spielstein * spielsteine[anzahlSpielsteine];

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
//void darfsetzen(int x, int y, int farbe, int form);

int main(int argc, char *argv[])
{
//alle felder = 0 setzen
      for (int yi=0; yi<iHoehe; yi++)
      {
             for (int xi=0; xi<iBreite; xi++)
             {
                 Spielfeld[xi][yi].Besetzt = false;
             }
      }
      initialisiereSpielsteine();
      fuelleSpielsteinBeutel(spielsteinBeutel);
    //Lokale Variable
    char chauswahl;
  do{   
    printf("Feld Anzeigen(1)\n");
    printf("Feld Besetzten(2)\n");
    printf("Spiel Beenden(3)\n");
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
         
         return 0;
    }
    else
    {
        printf("Falsche Eingabe!\n");
    }
 }while ((chauswahl != 1)||(chauswahl != 2));
 

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
     

     else if (cBewegung == (char) 13){ //115 == 's' 13 == Enter

    	 setzeSpielstein(spielsteinBeutel,spielsteinAuswaehlen(spielsteinBeutel),x,y);
    	 	//break;
           }

     ZeigeSpielfeld();
}while(cBewegung != 13);
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
		printf("Zum AuswÃ¤hlen des Spielsteins seine Nummer eingeben:");
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
	printf("%c",st->form);
	printf(" ");
	//Farbe(15,0);
}

bool checkReihe(int Reihe[][2]){
     for(int i;i<iBreite;i++)
     {
             
             }
     }       

char gibZeichen()
{
	char c = getch();
	//printf("%d",c); //Für Debug-Zwecke
	//getchar();
	return c;
}

/*
bool darfsetzen(int x, int y, int farbe, int form)
{
     if(Spielfeld[x][y].Besetzt == true)return false;
     if(Spielfeld[x+1][y].Besetzt == false && Spielfeld[x-1][y].Besetzt == false && Spielfeld[x][y+1].Besetzt == false && Spielfeld[x][y-1].Besetzt == false)return false;
     
     
     for(int yi=0;yi<iHoehe;yi++){
     for(int xi=0;xi<iBreite;xi++)
     {
             int Reihe[iBreite][2];
             for(int i=0;i<iBreite;i++){
                     Reihe[i][0]=0;
                     Reihe[i][1]=0;
                     }
             int iReihe=0;
             
             if(Spielfeld[xi][yi].Besetzt==true)
             {
             Reihe[iReihe][0] = Spielfeld[xi][yi].spielstein.farbe;
             Reihe[iReihe][1] = Spielfeld[xi][yi].spielstein.form;
             iReihe++;
             }else{
             if(checkReihe(Reihe)==false)return false;
             for(int i=0;i<iBreite;i++){
                     Reihe[i][0]=0;
                     Reihe[i][1]=0;
                     }
             int iReihe=0;
             }
             }
             }
     return true;

}
*/
