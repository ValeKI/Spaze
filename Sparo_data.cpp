#include "Spaze_data.h"

SPARO::SPARO()
{ 
    this->verso=0;
    this->x='*'; 
    this->situa=0;
    this->hy=0;
    this->hx=0;
}

// si occupa di far continuare a muovere sulla win il proiettile
int SPARO::shoot(int m[][RIGHE], WINDOW *w)
{
    if( this->situa == -1 ) // -1 e' un indice che lo sparo e' in una situazione ottimale per continuare ad essere sparato
    {
        this->hx+=this->verso; // lo sparo si muove lungo le x a secondo il suo verso
        if( this->hx < 0  ||  this->hx >= COLONNE ) // quando esce dallo schermo non siamo piu' in una situazione ottimale
            this->situa=-2;
        
        else if( ( this->verso == -1  &&  m[ this->hx ][ this->hy ] == 40 )  ||  ( this->verso == 1  &&  m[ this->hx ][ this->hy ] != 40  &&  m[ this->hx ][ this->hy ] != 0 ) )
            // se e' un mostro (quindi ha il verso negativo) lo sparo perde la sua situazione ottimale se tocca il prtotagonista (40)
            // il contrario per il verso positivo, che ha il protagonista. Pero' il controllo e' solo se non e' nel vuoto o non tocca lo stesso protagonista
            this->situa=m[this->hx][this->hy];
            // lo sparo perde la sua situazioine ottimale e la nuova situa e' uguale a uno dei vari id dei mostri o 40 che rappresenta il protagonista
        else
        {
            // se non ci sono problemi stampa
            mvwaddch(w,this->hy,this->hx,this->x);
            this->situa=-1;
        }
    }
}


//Vari set
void SPARO::setHy(int a)
{
    this->hy=a;
}

void SPARO::setHx(int a)
{
    this->hx=a;
}

// setSitua e' descritto nel header

void SPARO::azzeraSitua()
{
    // per una questione di leggibilita' ho deciso di implementare anche questa funzione
    this->situa=0;
}

void SPARO::setX(char s)
{
    this->x=s;
}

void SPARO::versoNegativo()
{
    this->verso=-1;
}

void SPARO::versoPositivo()
{
    this->verso=1;
}
   
int SPARO::getSitua()const
{
    return this->situa;
}

int SPARO::getHx()const
{
    return this->hx;
}

int SPARO::getHy()const
{
    return this->hy;
}

char SPARO::getX()const
{
    return this->x;
}