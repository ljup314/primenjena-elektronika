/*
 * File:   main.c
 * Author: LJ
 *
 * Created on October 28, 2021, 2:49 AM
 */


#include <stdio.h>
#include <stdlib.h>
#include<p30fxxxx.h>

_FOSC(CSW_FSCM_OFF & XT_PLL4);//instruction takt je isti kao i kristal
_FWDT(WDT_OFF); // watchdog timer je iskljucen

void pinInit(){
    
    ADPCFG = 0xffff;//definisemo da port B nije analogni vec digitalni
   
	TRISB = 0x0000;//konfigurisemo kao izlaz
    TRISC = 0x0000;//konfigurisemo kao izlaz
	TRISD = 0x0000;//konfigurisemo kao izlaz
    TRISF = 0x0000;//konfigurisemo kao izlaz 
    TRISA = 0x0000;//konfigurisemo kao izlaz
}

unsigned int broj1,broj2;
void pauza(){
     
        for(broj1=0;broj1<700;broj1++)
        for(broj2=0;broj2<400;broj2++);
}

void portbOn(){
	LATBbits.LATB0 = 1;
    pauza();
    LATBbits.LATB1 = 1;
    pauza();
    LATBbits.LATB2 = 1;
    pauza();
    LATBbits.LATB3 = 1;
    pauza();
    LATBbits.LATB4 = 1;
    pauza();
    LATBbits.LATB5 = 1;
    pauza();
    LATBbits.LATB6 = 1;
    pauza();
    LATBbits.LATB7 = 1;
    pauza();
    LATBbits.LATB8 = 1;
    pauza();
    LATBbits.LATB9 = 1;
    pauza();
    LATBbits.LATB10 = 1;
    pauza();
    LATBbits.LATB11 = 1;
    pauza();
    LATBbits.LATB12 = 1;
    pauza();
}

void portbOff(){
    LATBbits.LATB0 = 0;
    pauza();
    LATBbits.LATB1 = 0;
    pauza();
    LATBbits.LATB2 = 0;
    pauza();
    LATBbits.LATB3 = 0;
    pauza();
    LATBbits.LATB4 = 0;
    pauza();
    LATBbits.LATB5 = 0;
    pauza();
    LATBbits.LATB6 = 0;
    pauza();
    LATBbits.LATB7 = 0;
    pauza();
    LATBbits.LATB8 = 0;
    pauza();
    LATBbits.LATB9 = 0;
    pauza();
    LATBbits.LATB10 = 0;
    pauza();
    LATBbits.LATB11 = 0;
    pauza();
    LATBbits.LATB12 = 0;
    pauza();
}

void portcOn(){
    LATCbits.LATC13 = 1;
    pauza();
    LATCbits.LATC14 = 1;
    pauza();
}

void portcOff(){
    LATCbits.LATC13 = 0;
    pauza();
    LATCbits.LATC14 = 0;
    pauza();
    
}

void portdOn(){
    LATDbits.LATD0 = 1;
    pauza();
    LATDbits.LATD1 = 1;
    pauza();
    LATDbits.LATD2 = 1;
    pauza();
    LATDbits.LATD3 = 1;
    pauza();
    LATDbits.LATD8 = 1;
    pauza();
    LATDbits.LATD9 = 1;
    pauza();
}

void portdOff(){
    LATDbits.LATD0 = 0;
    pauza();
    LATDbits.LATD1 = 0;
    pauza();
    LATDbits.LATD2 = 0;
    pauza();
    LATDbits.LATD3 = 0;
    pauza();
    LATDbits.LATD8 = 0;
    pauza();
    LATDbits.LATD9 = 0;
    pauza();
}

void portaOn(){
    LATAbits.LATA11 = 1;
    pauza();
}

void portaOff(){
    LATAbits.LATA11 = 0;
    pauza();
}


void portfOn(){
    LATFbits.LATF0 = 1;
    pauza();
    LATFbits.LATF1 = 1;
    pauza();
    LATFbits.LATF2 = 1;
    pauza();
    LATFbits.LATF3 = 1;
    pauza();
    LATFbits.LATF4 = 1;
    pauza();
    LATFbits.LATF5 = 1;
    pauza();
    LATFbits.LATF6 = 1;
    pauza();
}

void portfOff(){
    LATFbits.LATF0 = 0;
    pauza();
    LATFbits.LATF1 = 0;
    pauza();
    LATFbits.LATF2 = 0;
    pauza();
    LATFbits.LATF3 = 0;
    pauza();
    LATFbits.LATF4 = 0;
    pauza();
    LATFbits.LATF5 = 0;
    pauza();
    LATFbits.LATF6 = 0;
    pauza();
}

int main(int argc, char** argv) {
  //setup inicijalizacija 
  
  
	pinInit();
  
	while(1)
	{
        portbOn();
        portcOn();
        portdOn();
        portaOn();
        portfOn();
        
        portbOff();
        portcOff();
        portdOff();
        portaOff();
        portfOff();

	}// while    
    return (EXIT_SUCCESS);
}//main
