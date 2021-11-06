/*
 * File:   main.c
 * Author: LJ
 *
 * Created on November 6, 2021, 10:17 PM
 */


#include <p30fxxxx.h>
#include <stdio.h>
#include <stdlib.h>

_FOSC(CSW_FSCM_OFF & XT_PLL4);//instruction takt je isti kao i kristal
_FWDT(WDT_OFF);
enum state_t {S1, S2, S3, S4, ON, RESTART}; //definisemo da imamo niz stanja
enum state_t stanje = S1; //pocetno stanje je S1

void pinInit(){
    ADPCFG = 0xffff; //definisemo portB kao digitalni port
    TRISB = 0x0000; //definisemo portB kao izlazni port, na njemu ce svetleti diode
    TRISD = 0xffff; //definisemo portD kao ulazni, ovaj port koristi tastere
}

unsigned int broj1,broj2;
void pauza(){
     
        for(broj1=0;broj1<700;broj1++)
        for(broj2=0;broj2<400;broj2++);
}

int main(int argc, char** argv) {
    
    pinInit();
    
    while(1)
    {
        switch(stanje)
                
        {   //sifra su sledeci tasteri: RD0 -> RD1 -> RD2 -> RD3 nakon cega se pali ceo port B
            //ako zelim restart, tj. da se vratim u S1, pritiska se taster RD8 
            
            case S1:
                LATB = 0x0000;
                while(PORTD != 0x0000) //dokle god postoji nekakav unos
                {
                    if(PORTDbits.RD0)
                    {
                        pauza(); //pauzu pravimo radi debouncinga
                        stanje = S2;
                    }
                    else
                        stanje = S1;
                }
                break;
                
            case S2:
                while(PORTD != 0x0000) //dokle god postoji nekakav unos
                {
                    if(PORTDbits.RD1)
                    {
                        pauza();
                        stanje = S3;
                    }
                    else
                        stanje = S1;
                }
                break;
                
            case S3:
                while(PORTD != 0x0000) //dokle god postoji nekakav unos
                {
                    if(PORTDbits.RD2)
                    {
                        pauza();
                        stanje = S4;
                    }
                    else
                        stanje = S1;
                }
                break;
                
            case S4:
                while(PORTD != 0x0000) //dokle god postoji nekakav unos
                {
                    if(PORTDbits.RD3)
                    {
                        pauza();
                        stanje = ON;
                    }
                    else
                        stanje = S1;
                }
                break;
                
            case ON:
                LATB = 0xffff;
                stanje = RESTART;
                
                break;
                
            case RESTART:
                while(PORTD != 0x0000) //dokle god postoji nekakav unos
                {
                    if(PORTDbits.RD8)
                        stanje = S1;
                }
                break;
                
                
        }
    }
    
    
    return 0;
}
