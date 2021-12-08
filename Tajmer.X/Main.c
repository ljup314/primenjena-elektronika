#include <p30fxxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include "tajmeri.h"
#define PWM LATDbits.LATD0

_FOSC(CSW_FSCM_OFF & XT_PLL4);
_FWDT(WDT_OFF);


//---------------------------------
unsigned int brojac_ms,stoperica,ms,sekund;

/*******************************************************************
//funkcija za kasnjenje u milisekundama
*********************************************************************/
void Delay_ms (int vreme)//funkcija za kasnjenje u milisekundama
	{
		stoperica = 0;
		while(stoperica < vreme);
	}

void funcPWM0()
{
    PWM = 0; //sigurica da je na D0 0V
    PWM = 1; // dovodi se 5V na D0
    Delay_ms(9.5); //pauza 0.9ms
    PWM = 0; //D0 = 0V
    Delay_ms(190.5);
}

void funcPWM1()
{
    PWM = 0; //sigurica da je na D0 0V
    PWM = 1; // dovodi se 5V na D0
    Delay_ms(19.5); //pauza 2ms
    PWM = 0; //D0 = 0V
    Delay_ms(180.5);
}

void funcPWM2()
{
    PWM = 0; //sigurica da je na D0 0V
    PWM = 1; // dovodi se 5V na D0
    Delay_ms(1); //pauza 0.1ms
    PWM = 0; //D0 = 0V
    Delay_ms(199);
}



void __attribute__ ((__interrupt__)) _T2Interrupt(void) // svakih 1ms
{

		TMR2 =0;
     ms=1;//fleg za milisekundu ili prekid;potrebno ga je samo resetovati u funkciji

	brojac_ms++;//brojac milisekundi
    stoperica++;//brojac za funkciju Delay_ms

    if (brojac_ms==1000)//sek
        {
          brojac_ms=0;
          sekund=1;//fleg za sekundu
		 } 
	IFS0bits.T2IF = 0; 
       
}

	


void main (void)
{
    ADPCFGbits.PCFG4=1;//defini?emo da pin B4 nije analogni vec digitalni
	TRISBbits.TRISB4=0;//konfigurisemo kao izlaz
    TRISDbits.TRISD0 = 0; //konfigurisemo kao izlaz
    
    TRISDbits.TRISD1 = 1; //ulaz, taster
    TRISDbits.TRISD2 = 1; //ulaz, taster
    TRISDbits.TRISD3 = 1; //ulaz, taster

Init_T2();
//	Init_T1();
//	Init();


	while(1)
	{
        if(PORTDbits.RD1) //da li je pritisnut taster
            funcPWM0();
        else if(PORTDbits.RD2)
            funcPWM1();
        else if(PORTDbits.RD3)
            funcPWM2();
			
	}//while(1)



}//main


