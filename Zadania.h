#define sek		250					// SP-AVR: 1 sekunda = 250*4ms (200 przerwañ po 4ms)
#include <ctime>
volatile int tim1 = 0;				// Odmierzanie czasu w przerwaniu int_T0
volatile int tim2 = 0;
volatile int tim3 = 0;
volatile int tim4 = 0;
volatile int tim5 = 0;
volatile int tim6 = 0;
volatile int tim7 = 0;
volatile int tim8 = 0;
volatile float wysokosc = 200;
char stan1 = 1;						// Stan automatu (procesu)
char stan2 = 1;
char stan3 = 1;
char stan4 = 1;
char stan5 = 1;
char stan6 = 1;
int licznikOpuszczen = 0;
int migniecia = 0;

int licznikOpuszczenTemp = 0;

int flaga = 1;


int predkosc = 1;
int liczczasu = 0;
double T_1 = 3 * sek;						// T1=3[s]
int T2 = 0;
int T1 = 0;
float wsp = 0, x = 0, pom;
float wsp_predkosci = 0, pom_predkosc = 0;
float pom_predkosc1 = 0;
void zadanie1(void)
{
    //////////////////////////////////////OPUSZCZANIE//////////////////////////////////////////////////////////////////
    switch (stan1)
    {
        case 1:
            L1 = 0; L2 = 0;
            if (aK1 && !aK2 && wysokosc > 0)
            {
                stan1 = 2;
                wysokosc = wysokosc - 1;
                wsp = ((wysokosc * 500) / 300);
                tim1 = wsp;
                //tim3=2*sek;
            }
            else if (aK1 && aK2)
            {
                stan1 = 5;
            }
            break;


        case 2:
            L1 = 1; L2 = 0;
            if (aK1 && wysokosc > 0)
                wysokosc = wysokosc - 1;

			//cases
			if (wysokosc < 1)
            {
                stan1 = 4;
            }
            else if (!tim1 && aK1)
            {
                stan1 = 3;
                tim1 = sek/10;
            }
            else if (!aK1)
            {
                stan1 = 1;
            }
            else if (aK1 && aK2)
            {
                stan1 = 5;
            }
            break;

        case 3:
            L1 = 0; L2 = 0;
            if (aK1 && wysokosc > 0)
                wysokosc = wysokosc - 1;

			//cases
            if (wysokosc < 1)
            {
                stan1 = 4;
            }
            if (!tim1 && aK1)
            {
                stan1 = 2;
                wsp =   ((wysokosc * 500) / 300);
                tim1 = wsp;
            }
			else if (!aK1)
            {
                stan1 = 1;
            }
            else if (aK1 && aK2)
            {
                stan1 = 5;
            }
            break;

        case 4:
            L1 = 0; L2 = 1;

            if (flaga == 1)
            {
                licznikOpuszczen++;
                flaga = 0;
            }

			//cases
            if (aK2)
            {
                stan1 = 1;
            
            }
            break;

        case 5:
            L2 = 0; L1=0;
			if(!aK2)
				stan1=1;
            break;
    }

    /////////////////////////////////////////////PODNOSZENIE///////////////////////////////////////////////////////////
    switch (stan2)
    {
        case 1:
			//cases
            if (aK2 && !aK1 && wysokosc < 300)
            {
                stan2 = 2;
                wysokosc = wysokosc + 1;
                wsp = 500 - ((wysokosc * 500) / 300);
                tim2 = wsp;
            }
            else if (aK1 && aK2)
            {
                stan2 = 5;
            }

            break;
        case 2:
            L1 = 1;
            if (aK2 && wysokosc < 300)
                wysokosc = wysokosc + 1;

            wsp = (wysokosc / 100);
			//cases
			if(wysokosc>=300)
				stan2=4;
            else if (!tim2 && aK2)
            {
                stan2 = 3;
                tim2 = sek / 10;
            }
            else if (!aK2)
            {
                stan2 = 1;
            }
            else if (aK1 && aK2)
            {
                stan2 = 5;
            }
            break;
        case 3:
            L1 = 0;
            if (aK2 && wysokosc < 300)
                wysokosc = wysokosc + 1;
			//cases
            if (!tim2 && aK2)
            {
                stan2 = 2;
                wsp =  500 - ((wysokosc * 500) / 300);
                tim2 = wsp;
            }
			else if (aK1 && aK2)
            {
                stan2 = 5;
            }
            else if (wysokosc >= 300)
            {
                stan2 = 4;
            }
            else if (!aK2)
            {
                stan2 = 1;
            }
            break;

        case 4:
            L2 = 1;
            if (flaga == 0) 
			{
				flaga = 1; 
			}
			//cases
            if (aK1) 
			{

				stan2 = 1; 
			}
            break;

        case 5: L2 = 0;
			if(!aK1)
				stan2=1;
			break;
    }

    //////////////////////////////////////PREDKOSC//////////////////////////////////////////////////////////////////
    switch (stan3)
    {
        case 1:
            L3 = 0;
            wsp_predkosci = (wysokosc / 300); 
			pom_predkosc = (1 - wsp_predkosci) * 10;
            if ((aK1 && !aK2) && pom_predkosc > 0)
            {
				predkosc=(predkosc*wysokosc*sek)/(predkosc*100);
                tim3 = pom_predkosc * sek;

                stan3 = 2;
            }

            if ((!aK1 && aK2) && pom_predkosc > 0)
            {
				predkosc=(predkosc*wysokosc*sek)/(predkosc*100);
                pom_predkosc = 10 - pom_predkosc;
                tim3 = pom_predkosc * sek;

                stan3 = 5;
            }
            break;
        case 2:
            L3 = 1;
            if (!tim3 && (wysokosc > 0 && wysokosc < 300) && aK1)
            {
                stan3 = 3;
                tim3 = 0.2 * sek;
            }

            else if (wysokosc <= 0 || wysokosc >= 300)
            {
                stan3 = 4;
            }
            if (!aK1 && !aK2)
            {
                stan3 = 1;
            }
            break;
        case 3:
            L3 = 0;
            if (predkosc > 0 && (wysokosc > 0 && wysokosc < 300) && aK1)
            {
                if (!tim3 && (aK1 || !aK2))
                {
                    stan3 = 2; wsp_predkosci = (wysokosc / 300);
                    pom_predkosc = (1 - wsp_predkosci) * 10;
                    tim3 = pom_predkosc * sek;
                }
            }
            else if (wysokosc <= 0 || wysokosc >= 300)
            {
                stan3 = 4;
            }
            else if ((!aK1 && !aK2))
            {
                stan3 = 1;
            }
            break;


        case 4:
            L3 = 0;
            if (wysokosc > 0 && wysokosc < 300)
            {
                stan3 = 1;
            }
            break;

        case 5:
            L3 = 1;
            if (!tim3 && (wysokosc > 0 && wysokosc < 300) && aK2)
            {
                stan3 = 6;
                tim3 = 0.2 * sek;
            }
            else if (wysokosc <= 0 || wysokosc >= 300)
            {
                stan3 = 4;
            }
            if (!aK1 && !aK2)
            {
                stan3 = 1;
            }
            break;

        case 6:
            L3 = 0;
            if (predkosc > 0 && (wysokosc > 0 && wysokosc < 300) && aK2)
            {
                if (!tim3 && (!aK1 && aK2))
                {
                    stan3 = 5; wsp_predkosci = (wysokosc / 300);
                    pom_predkosc = (1 - wsp_predkosci) * 10;
                    pom_predkosc = 10 - pom_predkosc;
                    tim3 = pom_predkosc * sek;
                }
            }
            else if (wysokosc <= 0 || wysokosc >= 300)
            {
                stan3 = 4;
            }
            if (!aK1 && !aK2)
            {
                stan3 = 1;
            }
            break;

    }

    ///////////////////////////////////////LICZNIK OPUSZCZEN/////////////////////////////////////////////////////////////////
    switch (stan4)
    {
        case 1:
            L4 = 0;
            licznikOpuszczenTemp = licznikOpuszczen;
            if (aK3 && licznikOpuszczenTemp > 0)
            {
                stan4 = 2;
                licznikOpuszczenTemp = licznikOpuszczen;
                tim5 = 1 * sek;
            }
            break;

        case 2:
            L4 = 1;
            if (licznikOpuszczenTemp == 0)
            {
                stan4 = 1;
            }
            if (aK3) 
			{
				stan4 = 4;
			}
            else if (!tim5 && !aK3)
            {
                stan4 = 3; 
				tim5 = 0.5 * sek;
                licznikOpuszczenTemp = licznikOpuszczenTemp - 1;
            }
            break;

        case 3:
            L4 = 0;
            if (licznikOpuszczenTemp == 0)
            {
                stan4 = 1;
            }
            else if (!tim5 && !aK3)
            {
                stan4 = 2;
                tim5 = 1 * sek;
            }
            break;

        case 4:
            L4 = 1;
            if (!aK3)
            {
                stan4 = 2;
                tim5 = 1 * sek;
            }
            break;
    }

    //////////////////////////////////////////KIERUNEK OPUSZCZANIA//////////////////////////////////////////////////////////////
    switch (stan5)
    {
        case 1:
            L5 = 0;
            if (wysokosc > 0 && wysokosc < 300)
            {
                if (aK1 && !aK2)
                {
                    stan5 = 2;
                    tim6 = 1 * sek;
                }
                else if (aK2 && !aK1)
                {
                    stan5 = 2; 
					tim7 = 0.5 * sek;
                }
                else if (aK1 && aK2)
                {
                    stan5 = 4;
                }
            }
            break;

        case 2:
            L5 = 1;
            if (wysokosc > 0 && wysokosc < 300)
            {
                if (!tim6 && aK1 && !aK2)
                {
                    stan5 = 3; 
					tim6 = 0.5 * sek;
                }
                else if (!tim7 && !aK1 && aK2)
                {
                    stan5 = 3;
                    tim7 = 1 * sek;
                }
                else if (aK1 && aK2)
                {
                    stan5 = 4;
                }
                else if (!aK2 && !aK1)
                {
                    stan5 = 1;
                }
            }
            else
            {
                stan5 = 1;
            }
            break;

        case 3:
            L5 = 0; 
			if (wysokosc > 0 && wysokosc < 300)
            {
                if (!tim6 && aK1 && !aK2)
                {
                    stan5 = 2;
                    tim6 = 1 * sek;
                }
                else if (!tim7 && aK2 && !aK1)
                {
                    stan5 = 2;
                    tim7 = 0.5 * sek;
                }
                else if (aK1 && aK2)
                {
                    stan5 = 4;
                }
                else if (!aK2 && !aK1)
                {
                    stan5 = 1;
                }
            }
            else
            {
                stan5 = 1;
            }
            break;



        case 4:
            L1 = 0; L2 = 0; L3 = 0; L4 = 0; L5 = 0;
            if (aK1 && !aK2)
            { 
                stan1 = 1;
                stan2 = 1;
                stan3 = 1;
                stan4 = 1;
				stan5 = 1;
            }
            else if (aK2 && !aK1)
            {
                stan1 = 1;
                stan2 = 1;
                stan3 = 1;
                stan4 = 1;
				stan5 = 1;
            }
            break;

    }
    /////////////////////zeruj licznik/////////////////////////////////
    switch (stan6)
    {
        case 1:
            L6 = 0;
            if (aK4 && licznikOpuszczen > 0)
            {
                stan6 = 2;
                licznikOpuszczen = 0;
                tim8 = 1 * sek;
            }
            break;

        case 2:
            L6 = 1; if (!tim8 && migniecia >= 0 && migniecia < 4)
            {
                stan6 = 3;
                migniecia = migniecia + 1;
                tim8 = 1 * sek;
            }
            else if (migniecia > 3)
            {
                stan6 = 1;
				migniecia = 0;
            }
            break;

        case 3:
            L6 = 0;
            if (!tim8)
            {
                stan6 = 4;
                tim8 = 0.5 * sek;
            }
            break;

        case 4:
            L6 = 1;
            if (!tim8 && migniecia >= 0 && migniecia < 4)
            {
                stan6 = 5;
                migniecia = migniecia + 1;
                tim8 = 1 * sek;
            }
            else if (migniecia > 3)
            {
                stan6 = 6;
                migniecia = 0;
            }
            break;

        case 5:
            L6 = 0;
            if (!tim8)
            {
                stan6 = 2;
                tim8 = 1 * sek;
            }
            if (migniecia > 3)
            {
                stan6 = 6;
                migniecia = 0;
            }
            break;

        case 6:
            L6 = 0;
            if (!aK4)
            {
                stan6 = 1;
            }
            break;
    }
}