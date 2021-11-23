#include <stdio.h>
#include <stdlib.h>
#include<p30fxxxx.h>

_FOSC(CSW_FSCM_OFF & XT_PLL4);//instruction takt je isti kao i kristal
_FWDT(WDT_OFF);

unsigned char tempRX;
unsigned int broj1,broj2;
unsigned int k;
int str[];

void initUART1(void)
{
    U1BRG=0x0040;//ovim odredjujemo baudrate

    U1MODEbits.ALTIO=1;//biramo koje pinove koristimo za komunikaciju osnovne ili alternativne

    IEC0bits.U1RXIE=1;//omogucavamo rx1 interupt

    U1STA&=0xfffc;

    U1MODEbits.UARTEN=1;//ukljucujemo ovaj modul

    U1STAbits.UTXEN=1;//ukljucujemo predaju
}

void __attribute__((__interrupt__)) _U1RXInterrupt(void) 
{
    IFS0bits.U1RXIF = 0;
    tempRX=U1RXREG;
    
    if(tempRX != 0)
    {  
       str[k] = tempRX;
       if(k < 5)
           k++;
       else k=0;
    }
}

void pauza()
{
    for(broj1=0;broj1<3000;broj1++)
    for(broj2=0;broj2<1000;broj2++);
}

void Verification()
{
    if(str[0]=='D' && str[1]=='O'&& str[2]=='R' && str[3]=='O' && str[4]=='S')
    {
    putString("Jelte koleginice, a sta kolega hoce od Vas??");
    }
}

/*********************************************************************
* Ime funkcije      : WriteUART1                                     *
* Opis              : Funkcija upisuje podatak u registar 			 *
* 					  za slanje podataka U1TXREG,   				 *
* Parametri         : unsigned int data-podatak koji treba poslati   *
* Povratna vrednost : Nema                                           *
*********************************************************************/

void WriteUART1(unsigned int data)
{
	  while(!U1STAbits.TRMT);

    if(U1MODEbits.PDSEL == 3)
        U1TXREG = data;
    else
        U1TXREG = data & 0xFF;
}

void putString(register const char *str)
{
    while(*str != 0) //ceka se nekakav upis
    {
        WriteUART1(*str); 
        if(*str == 13) WriteUART1(10);
        if(*str == 10) WriteUART1(13);
        str++;
    }
}

int main(int argc, char** argv) {
    
    
    initUART1();

	while(1)
	{
        pauza();
        Verification();


    }//od whilea

    return (EXIT_SUCCESS);
}
