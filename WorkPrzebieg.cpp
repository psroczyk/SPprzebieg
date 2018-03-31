/**********************************************************************************/
/*     Program symulatora SP-841/AVR w wersji do zadañ z przebiegów czasowych     */
/**********************************************************************************/
#include "WorkPrzebieg.h"			// Definicje zmiennych i prototypy funkcji SP
#include "Zadania.h"				// Zadania u¿ytkownika

void inicjuj(void)					// Inicjowanie programu (jednorazowo przy starcie)
{
}

void oblicz(void)					// Kod u¿ytkownika - wykonywany co wCykl [ms]
{ 
	zadanie1();						// Funkcja z pliku "Zadania.h"

	sprintf(buf,"K1=%dK2=%dK3=%dK4=%d ",(int)aK1,(int)aK2,(int)aK3,(int)aK4);
	LCD_xy(1,1); LCD_puts(buf);
	sprintf(buf,"L1=%dL2=%dL3=%dL4=%d ",(int)L1,(int)L2,(int)L3,(int)L4);
	LCD_xy(1,2); LCD_puts(buf);
}

void int_T0(void)					// Przerwanie od T0/T1/T2 wywo³ywane tIntr [ms]
{
	if(tim1) --tim1;
	if(tim2) --tim2;
	if(tim3) --tim3;
	if(tim4) --tim4;
	if(tim5) --tim5;
	if(tim6) --tim6;
	if(tim7) --tim7;
	if(tim8) --tim8;
}

void WykresyPC()					// Opisy/wartoœci wykresów i zmiennych pomocniczych
{ 
	iNazwa[0]="stan2"; iZmienna[0]= stan2;
	iNazwa[2]="tim2";  iZmienna[2]= tim2;
	iNazwa[6]="tim5"; iZmienna[6]= tim5;
	iNazwa[7]="stan6"; iZmienna[7]= stan6;
	iNazwa[5]="wysokosc"; iZmienna[5]= wysokosc;

	bNazwa[0]="opusc";  bWykres[0]= aK1;
	bNazwa[1]="podnos";  bWykres[1]= aK2;
	bNazwa[2]="l. opuszczen";  bWykres[2]= aK3;
	bNazwa[3]="zeruj";  bWykres[3]= aK4;
	//bNazwa[4]="";  bWykres[4]= aK5;

	bNazwa[5]="wysokosc";  
	bWykres[5]= L1;

	bNazwa[6]="czuj zblizeniowy";  
	bWykres[6]= L2;

	bNazwa[7]="predkosc";  
	bWykres[7]= L3;

	bNazwa[8]="ilosc opuszczen";  
	bWykres[8]= L4;

	bNazwa[9]="kierunek";  
	bWykres[9]= L5;

	bNazwa[10]="zerowanie";  
	bWykres[10]=L6;
}
