#define _CRT_SECURE_NO_DEPRECATE 
int  wCykl=100;							// Czas cyklu dla funkcji oblicz(), np. 100[ms]
char tIntr=4;							// Interwa� czasu pomi�dzy przerwaniami od T0 [ms]
char typPanelu=1;						// Typ palenu: 0=>SP-841, 1=>SP-AVR
char fTekstury=0;						// Czy rysowa� tekstury? (1=Tak, 0=Nie)
char fTablWart=1;						// Czy rysowa� tablic� wart.? (1=Tak, 0=Nie)
char fWykresy=1;						// Czy rysowa� wykresy? (1=Tak, 0=Nie)
char buf[64];							// Bufor komunikat�w wy�wietlacza LCD

#include <stdio.h>

typedef unsigned char bit;

extern bit K1,K2,K3,K4,L1,L2,L3,L4,BUZ;	// Klawisze, diody LED, piszczyk BUZ

extern char cb[18];						// CheckBox-y (analogowe,binarne), 0=wy��czony, 1=w��czony
extern float aWykres[6];				// Wy�wietlane warto�ci wielko�ci analogowych
extern char  bWykres[12];				// Wy�wietlane warto�ci wielko�ci binarnych
extern int   iZmienna[8];				// Wy�wietlane warto�ci zmiennych pomocniczych
extern char  *bNazwa[12];				// Tablica nazw wielko�ci analogowych
extern char  *aNazwa[6];				// Tablica nazw wielko�ci binarnych
extern char  *iNazwa[8];				// Tablica nazw zmiennych pomocniczych
extern void LCD_xy(char x, char y);		// Ustawienie kursora na wy�wietlaczu LCD
extern void LCD_putch(char znak);		// Wy�wietlenie znaku na wy�wietlaczu LCD
extern void LCD_puts(char *tablica_LCD);// Wy�wietlenie �a�cucha znak�w na wy�wietlaczu LCD
extern int  get_KBD();					// Odczyt stanu klawiszy K1..K4
extern void set_LED(int val);			// Wy�wietlenie stanu diod LED
extern void SYM_send(void);				// Odczyt komunikatu z symulatora obiekt�w
extern char SYM_read(void);				// Wys�anie komunikatu do symulatora obiekt�w
extern void oblicz(void);				// Funkcja z programem u�ytkownika
extern bit K1,K2,K3,K4,K5,K6,K7,K8;		// Klawisze K1..K8
extern bit L1,L2,L3,L4,L5,L6,L7,L8;		// Diody L1..L8
char aK1,aK2,aK3,aK4,aK5,aK6,aK7,aK8;	// Aktualny stan klawisza K1..K8
char pK1,pK2,pK3,pK4,pK5,pK6,pK7,pK8=0;	// Poprzedni stan klawisza K1..K8

char ile_aWe = 0;						// Ile zmiennych analogowych w SNET_read()
char ile_aWy = 0;						// Ile zmiennych analogowych w SNET_send()

void KEY_read(void)
{
	aK1=!K1; aK2=!K2; aK3=!K3; aK4=!K4;	// Aktualny stan klawiszy K1..K4
	aK5=!K5; aK6=!K6; aK7=!K7; aK8=!K8;	// Aktualny stan klawiszy K5..K8
}
void KEY_mem(void)						// Zapami�tanie stanu klawiszy
{
	pK1=aK1; pK2=aK2; pK3=aK3; pK4=aK4;
	pK5=aK5; pK6=aK6; pK7=aK7; pK8=aK8;
}
void LED_set(void)
{}

void work(void)
{
	KEY_read();
	oblicz();
	LED_set();
	KEY_mem();
}
