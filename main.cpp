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



using namespace std;

//Variablen Deklarieren
 int x = 0;
 int y = 0;

char cBewegung;
int Punkte;



//Unverï¿½nderbare variablen
const int iBreite = 15;
const int iHoehe = 15;
const int spielsteinBeutelGroesse = 6;
const int anzahlSpielsteine = 75;
const int anzahlFarben=2;
const int anzahlFormen=4;
const char* speicherDateiNamen = "QwirkleSpeicherstand.dat";

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
	int zuletztGesetzterSpielsteinPos[2]; // [0] = X-Wert, [1] = Y-Wert
	};

//Arrar
//fï¿½rs spielfeld
S_Feld Spielfeld[iBreite][iHoehe];

//fï¿½r ausgewï¿½hltes feld
//S_Feld Ausgewaehlt[iBreite][iHoehe];



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
void neuerSpieler(bool bComputerGegner);
void naechsterSpieler();

void spielStarten()
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
      neuerSpieler(true); // einen Spieler erstellen
      neuerSpieler(false);


while(true){ //endlosschleife! Hier findet das eigentliche Spielen statt
    naechsterSpieler();
    do{
    	if(aktiverSpieler->istComputerGegner)
    	{
    		spielzugKI();
    	}else{
    		spielzugMenschlicherSpieler();
    	}
 }while (aktiverSpieler->zugBeendet == false);//(chauswahl != 1)||(chauswahl != 2));
}

}

int main(int argc, char *argv[])
{
    // Variablen deklarieren
    char ceingabe;
    int istatus;
    int iflag;
    int iausgang;


   istatus=1;
   iflag=0;
   iausgang=0;

   do
   {
      do
      {
         //Ausgabe des Menüs
         switch(istatus)
         {
              case 1 :
                   printf(" \n \n \n ");
                   printf("            QQQQQ    Q     Q  Q  QQQQQQ  QQQQQQQ  QQQQQQQ  Q       \n ");
                   printf("           Q     Q   Q     Q  Q  Q    Q  Q     Q  Q        Q       \n ");
                   printf("           Q     Q   Q     Q  Q  Q    Q  Q     Q  Q        Q       \n ");
                   printf("           Q     Q   Q     Q  Q  QQQQQ   Q        QQQQQQQ  Q       \n ");
                   printf("           Q     Q   Q     Q  Q  Q  Q    Q   QQQ  Q        Q       \n ");
                   printf("           Q    QQ   Q     Q  Q  Q   Q   Q     Q  Q        Q       \n ");
                   printf("            QQQQQQQ   QQQQQ   Q  Q    Q  QQQQQQQ  QQQQQQQ  QQQQQQQ \n ");
                   printf("\n\n\n\n\n");
                   printf("                           \32\32\32 *Spiel starten* \33\33\33");
                   printf("\n\n\n\n");
                   printf("                                *Spiel laden*");
                   printf("\n\n\n\n");
                   printf("                                 *Anleitung*");
                   printf("\n\n\n\n");
                   printf("                              *Spiel verlassen*");
                   break;

                   case 2 :
                   printf(" \n \n \n ");
                   printf("            QQQQQ    Q     Q  Q  QQQQQQ  QQQQQQQ  QQQQQQQ  Q       \n ");
                   printf("           Q     Q   Q     Q  Q  Q    Q  Q     Q  Q        Q       \n ");
                   printf("           Q     Q   Q     Q  Q  Q    Q  Q     Q  Q        Q       \n ");
                   printf("           Q     Q   Q     Q  Q  QQQQQ   Q        QQQQQQQ  Q       \n ");
                   printf("           Q     Q   Q     Q  Q  Q  Q    Q   QQQ  Q        Q       \n ");
                   printf("           Q    QQ   Q     Q  Q  Q   Q   Q     Q  Q        Q       \n ");
                   printf("            QQQQQQQ   QQQQQ   Q  Q    Q  QQQQQQQ  QQQQQQQ  QQQQQQQ \n ");
                   printf("\n\n\n\n\n");
                   printf("                               *Spiel starten*");
                   printf("\n\n\n\n");
                   printf("                            \32\32\32 *Spiel laden* \33\33\33");
                   printf("\n\n\n\n");
                   printf("                                 *Anleitung*");
                   printf("\n\n\n\n");
                   printf("                              *Spiel verlassen*");
                   break;

                   case 3 :
                   printf(" \n \n \n ");
                   printf("            QQQQQ    Q     Q  Q  QQQQQQ  QQQQQQQ  QQQQQQQ  Q       \n ");
                   printf("           Q     Q   Q     Q  Q  Q    Q  Q     Q  Q        Q       \n ");
                   printf("           Q     Q   Q     Q  Q  Q    Q  Q     Q  Q        Q       \n ");
                   printf("           Q     Q   Q     Q  Q  QQQQQ   Q        QQQQQQQ  Q       \n ");
                   printf("           Q     Q   Q     Q  Q  Q  Q    Q   QQQ  Q        Q       \n ");
                   printf("           Q    QQ   Q     Q  Q  Q   Q   Q     Q  Q        Q       \n ");
                   printf("            QQQQQQQ   QQQQQ   Q  Q    Q  QQQQQQQ  QQQQQQQ  QQQQQQQ \n ");
                   printf("\n\n\n\n\n");
                   printf("                               *Spiel starten* ");
                   printf("\n\n\n\n");
                   printf("                                *Spiel laden*");
                   printf("\n\n\n\n");
                   printf("                             \32\32\32 *Anleitung* \33\33\33");
                   printf("\n\n\n\n");
                   printf("                              *Spiel verlassen*");
                   break;

                   case 4 :
                   printf(" \n \n \n ");
                   printf("            QQQQQ    Q     Q  Q  QQQQQQ  QQQQQQQ  QQQQQQQ  Q       \n ");
                   printf("           Q     Q   Q     Q  Q  Q    Q  Q     Q  Q        Q       \n ");
                   printf("           Q     Q   Q     Q  Q  Q    Q  Q     Q  Q        Q       \n ");
                   printf("           Q     Q   Q     Q  Q  QQQQQ   Q        QQQQQQQ  Q       \n ");
                   printf("           Q     Q   Q     Q  Q  Q  Q    Q   QQQ  Q        Q       \n ");
                   printf("           Q    QQ   Q     Q  Q  Q   Q   Q     Q  Q        Q       \n ");
                   printf("            QQQQQQQ   QQQQQ   Q  Q    Q  QQQQQQQ  QQQQQQQ  QQQQQQQ \n ");
                   printf("\n\n\n\n\n");
                   printf("                               *Spiel starten* ");
                   printf("\n\n\n\n");
                   printf("                                *Spiel laden*");
                   printf("\n\n\n\n");
                   printf("                                 *Anleitung*");
                   printf("\n\n\n\n");
                   printf("                          \32\32\32 *Spiel verlassen* \33\33\33");
                   break;
         }

         // Einlesen und Auswerten der Eingabe
         do
         {
               ceingabe=getch();
         }while(ceingabe<0);

         switch(ceingabe)
         {
              case 72:
                    istatus=istatus-1;

                    if(istatus==0)
                    {
                           istatus=4;
                    }
                    break;

              case 80:
                    istatus=istatus+1;

                    if(istatus==5)
                    {
                           istatus=1;
                    }
                    break;

              case 13:
                   iflag=1;
                   break;

         }
         system("cls");
   }while(iflag==0);

   // Spielanleitung
   switch(istatus)
   {
   	   	   	   	   case 1:
   	   	   	   		   spielStarten();
                  case 3:
                       printf("Jeder Spieler bekommt fuenf Steine, die er aus einem Beutel zieht.\n");
                       printf("Der Spieler beginnt und legt eine Kette aus vielen moeglichst vielen\n");
                       printf("gleichen Symbolen oder Steinen in der selben Farbe und beendet den Zug.\n");
                       printf("Alle folgenden Spielzuege folgen diesem Prinzip. Man legt eine Reihe aus \n");
                       printf("oder verlaengert eine Reihe, bekommt Punkte für Steine in den Reihen. \n");
                       printf("Im Gegensatz zur allerersten Reihe koennen bei den folgenden Spielzuegen\n");
                       printf("mehrere Reihen auf einmal entstehen. Dann wird jede Reihe fuer sich\n");
                       printf("gewertet, wobei auch hier jede Reihe so viele Punkte bringt, wie sie\n");
                       printf("Steine enthaelt. \n");
                       printf("Waehrend des ganzen Spiels gilt fuer die Punktwertung aber eine \n");
                       printf("Sonderregel: Eine Reihe mit fuenf Steinen, ein sogenannter Qwirkle,\n");
                       printf("bringt nicht fuenf, sondern zehn Punkte. Wer keine Steine auslegen \n");
                       printf("moechte, darf alternativ auch Steine tauschen. Dazu legt er die \n");
                       printf("abzugebenden Steine beiseite, zieht entsprechend viele neue aus \n");
                       printf("dem Beutel und wirft die unerwuenschten Steine anschließend in den \n");
                       printf("Beutel hinein.\n");
                       printf("Sobald der Beutel leer ist, koennen keine Steine mehr nachgezogen \n");
                       printf("werden. Nun wird solange gespielt, bis ein Spieler seinen letzten \n");
                       printf("Stein gelegt hat. Er beendet das Spiel. Wer nun die meisten Punkte hat,\n");
                       printf("ist Sieger.\n\n\n");
                       printf("Zurueck mit beliebiger Taste");
                       getch();
                       break;

                  case 4:
                       system("exit");
                       iausgang=1;
                       break;
   }
   }while(iausgang==0);

   spielStarten();
}


void spielSpeichern(){
	FILE * datei = fopen(speicherDateiNamen,"w+");
	if (datei == NULL)
	{
	printf("Fehler beim oeffnen der Datei.");
	beenden();
	}
	//SpielfeldSpeichern:
	for(int xi = 0; xi<iBreite;xi++)for(int yi = 0; yi<iHoehe;yi++)
	{
		fwrite(&Spielfeld[xi][yi], sizeof(S_Feld),1,datei);
	}

	//fprintf(datei, "");

	fclose(datei);
}

void neuerSpieler(bool bComputerGegner)
{
	Spieler ** newMitSpieler = new Spieler*[anzahlSpieler+1];
	for(int i=0; i< anzahlSpieler;i++)newMitSpieler[i]=mitSpieler[i];//mitSpieler kopieren
	if(mitSpieler != 0){
		free(mitSpieler); // Speicher clearen
	}
	// Spieler anfügen ....
	newMitSpieler[anzahlSpieler]=new Spieler;
	newMitSpieler[anzahlSpieler]->istComputerGegner = bComputerGegner;
	for(int i=0;i<spielsteinBeutelGroesse;i++)newMitSpieler[anzahlSpieler]->spielsteinBeutel[i]=0;
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
	printf("Spieler %d ist an der Reihe!\n\n",aktiverSpieler->spielerNummer);
}

void beenden()
{
	exit(0);
}

void spielzugKI()
{
	ZeigeSpielfeld();
	//return;
	for(int i = 0; i<anzahlSpielsteine;i++)for(int xi = 0; xi<iBreite;xi++)for(int yi = 0; yi<iHoehe;yi++)
		{
			if(spielsteine[i]!=0)
			{
				if(darfsetzen(xi,yi,spielsteine[i])==true)
				{
					//ZeigeSpielfeld();
					//printf("\n\n");
//gibZeichen();
					setzeSpielstein(spielsteine, i,xi,yi);
					break;
				}
			}
		}
	aktiverSpieler->zugBeendet=true;
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
    	//aktiverSpieler->punktestand += punkteRechnen(aktiverSpieler->zuletztGesetzterSpielsteinPos[0],aktiverSpieler->zuletztGesetzterSpielsteinPos[1]);
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
     //printf("%d\n",x);
    // printf("%d\n",y);
    //printf("%d\n",Punkte);
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
    	 	//break;
    	 }else{
    		 printf("Nicht möglich!");
    	 }
           }
     printf("Punktestand Spieler %d: %d\n",aktiverSpieler->spielerNummer , aktiverSpieler->punktestand);
     ZeigeSpielfeld();
}while(cBewegung != 115 && cBewegung != 27); //27 == ESC
}

void setzeSpielstein(Spielstein * ausBeutel[], int spielsteinNr, int x, int y)
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
	if(st!=0){
	Farbe(st->farbe,0);
	printf(" ");
	printf("%d%c",st->farbe,st->form);
	printf(" ");
	Farbe(15,0);
	}
}

bool checkReihe(Spielstein * Reihe[iBreite]){
int lFarbe=0;
char lForm = (char)0;
bool gleicheFarbe=false;
bool gleicheForm=false;
if(Reihe[1]!=0){//Vergleich nur möglich, wenn Spielstein an nächste Position
		gleicheFarbe=Reihe[0]->farbe == Reihe[1]->farbe;
		gleicheForm=Reihe[0]->form == Reihe[1]->form;
		if(gleicheFarbe && gleicheForm)return false;
		if(!gleicheFarbe && !gleicheForm)return false;
		if(gleicheFarbe){
			lFarbe = Reihe[0]->farbe;
		}else{
			lForm = Reihe[0]->form;
		}

		for(int i=0;i<iBreite;i++)
     {
		if(Reihe[i]!=0 && gleicheFarbe && lFarbe != Reihe[i]->farbe){return false;}else if(gleicheFarbe){
			for(int i2 = 0; i2<iBreite; i2++){
				if(i2!=i && Reihe[i2]!=0 && Reihe[i]!=0 && Reihe[i]->form == Reihe[i2]->form)return false;
			}
		}
		if(Reihe[i]!=0 && gleicheForm && lForm != Reihe[i]->form){return false;}else if(gleicheForm){
			for(int i2 = 0; i2<iBreite; i2++){
				if(i2!=i && Reihe[i2]!=0 && Reihe[i]!=0 && Reihe[i]->farbe == Reihe[i2]->farbe)return false;
			}
		}

     }
}
	return true;
     }       

char gibZeichen()
{
	char c = getch();
	//printf("%d",c); //Für Debug-Zwecke
	//getchar();
	return c;
}


bool darfsetzen(int x, int y, Spielstein * st)
{
     if(Spielfeld[x][y].Besetzt == true)return false;
     int anzahlGesetzterSteine=0;
     for(int xi=0; xi<iBreite;xi++)for(int yi=0;yi<iHoehe;yi++){
    	 if(Spielfeld[xi][yi].Besetzt)anzahlGesetzterSteine++;
     }
     if((x>iBreite-2 || Spielfeld[x+1][y].Besetzt == false) && (x<1 || Spielfeld[x-1][y].Besetzt == false) && (y>iHoehe-2 || Spielfeld[x][y+1].Besetzt == false) && (y<1 || Spielfeld[x][y-1].Besetzt == false) && anzahlGesetzterSteine>0)return false;
     
     bool gueltig=true;

     //Spielstein probeweise setzen:
     Spielfeld[x][y].Besetzt = true;
     Spielfeld[x][y].spielstein = st;

     Spielstein * Reihe[iBreite];
                  for(int i=0;i<iBreite;i++){
                          Reihe[i]=0;
                          }
                  int iReihe=0;

                  for(int yi=0;yi<iHoehe;yi++){

                	  for(int i=0;i<iBreite;i++){
                	                                    Reihe[i]=0;
                	                                    }
                	                            iReihe=0;

                  for(int xi=0;xi<iBreite;xi++)
                  {
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

                  for(int xi=0;xi<iHoehe;xi++){
                	  for(int i=0;i<iBreite;i++){
                	                                    Reihe[i]=0;
                	                                    }
                	                            iReihe=0;

                  for(int yi=0;yi<iBreite;yi++)
                  {
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
	if(punkteReihe==anzahlFarben)punkteReihe*=2; //Qwirkle!
	endpunktzahl +=punkteReihe;

	return endpunktzahl;
}

void spielsteinSetzenDurchKI(){

}
