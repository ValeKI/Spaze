#include <stdlib.h>
#include <ctime>
#include "Spaze_data.h"

MOSTRO::MOSTRO(int t, int n)
{
    this->vita=20;
    this->id=(t*10)+n;

    // da qui in poi questa funzione si occupa di generare casualmente la posizione dei mostri e con che decadenza casuale sparano
    srand(time(0)*id);
    this->decadenza=(rand()%7)+7;
    int* dove=new int(rand()%2);
    if(n%2)
        this->verso=-1;
    else
        this->verso=1;
    delete dove;
    switch (t)
    {
        case (1): // AQUILA 2
            this->dimX=15;
            this->dimY=6;
            
            break;
        
        case (2): // AEREO 4
            this->dimX=12;
            this->dimY=5;
            
            break;
        
        case (3): // UFO 6
            this->dimX=6;
            this->dimY=4;
            
            break;
    }
    
    this->x=COLONNE/2+(this->dimX*(n-1))+1;
    if(t==2&&n==2)
        this->x+=1;
    if(t==2&&n==3)
        this->x+=2;

    if(t==1 && n==2)
        this->x+=5;
    this->y=rand()%(RIGHE-this->dimY-2)+2;

    this->incr=0;
    this->tipo=t;
    setSparoY();
    for(unsigned i=0; i<SPARIMOSTRO; i++)
            {
                this->s[i].versoNegativo();
            }
}



// ogni mostro a secondo il tipo spara da un'altezza diversa
void MOSTRO::setSparoY()
{
    switch (this->tipo)
    {
        case 1:
            this->sparoY=this->y + 2;
        case 2:
            this->sparoY=this->y + 3;
        case 3:
            this->sparoY=this->y + 2;
    }
}

void MOSTRO::setSparoY(int a)
{
    this->sparoY=a;
}

void MOSTRO::setX(int a)
{
    this->x=a;
}

void MOSTRO::setY(int a)
{
    this->y=a;
}

void MOSTRO::setDimX(int a)
{
    this->dimX=a;
}

void MOSTRO::setDimY(int a)
{
    this->dimY=a;
}

void MOSTRO::setVita(int a)
{
    this->vita=a;
}

void MOSTRO::setDecadenza(int a)
{
    this->decadenza=a;
}

void MOSTRO::setIncr(unsigned a)
{
    this->incr=a;
}

void MOSTRO::setTipo(short a)
{
    this->tipo=a;
}

void MOSTRO::setVerso(short a)
{
    this->verso=a;
}

void MOSTRO::setId(short a)
{
    this->id=a;
}


int MOSTRO::getX() const
{
    return this->x;
}

int MOSTRO::getY() const
{
    return this->y;
}

short MOSTRO::getId() const
{
    return this->id;
}

int MOSTRO::getSparoY() const
{
    return this->sparoY;
}

int MOSTRO::getVita() const
{
    return this->vita;
}

int MOSTRO::getDimX() const
{
    return this->dimX;
}

int MOSTRO::getDimY() const
{
    return this->dimY;
}

int MOSTRO::getDecadenza() const
{
    return this->decadenza;
}

unsigned MOSTRO::getIncr() const
{
    return this->incr;
}

short MOSTRO::getTipo() const
{
    return this->tipo;
}

short MOSTRO::getVerso() const
{
    return this->tipo;
}

SPARO& MOSTRO::getSparo(unsigned i)
{
    return this->s[i];
}




void MOSTRO::scalaVita(int i)
{
    if(this->vita>0)
        (this->vita)--;
}



// si occupa di sparare i proiettili e muovere il mostro
void MOSTRO::sparaEmuovi(int m[][RIGHE],WINDOW* sfondo)
{
    bool k=1;
    if(getVita()!=0) // se il mostro e' morto non fa nulla giustamente
    {
    for(unsigned i=0; i<SPARIMOSTRO; i++)
            {
                // genera con una frequenza con almeno 3 di ampiezza un nuovo sparo
                if( this->s[i].getSitua()!=-1  &&  getSparoY()== ( ( (this->decadenza%4)+this->decadenza%3+3) * i ) )
                {
                    this->s[i].setHy(getSparoY());
                    this->s[i].setHx(getX());
                    this->s[i].setSitua();
                }

                // ci sono dei punti alla fine e all'inizio dove il mostro spara di meno a causa della sua altezza sparo SparoY
                if ( this->s[i].getSitua()!=-1 && ( (this->y+this->dimY==RIGHE && this->decadenza%2==1) || (this->y==1 && this->decadenza%2==0) ) && k)
                {
                    unsigned a=this->decadenza%this->dimY;
                    if (this->y==1 && this->decadenza%4==0 && a!=0)
                        a--;
                    this->s[i].setHy(y + a);
                    this->s[i].setHx(getX());
                    this->s[i].setSitua();
                    k=0;
                }

                // qui sparo singolarmente i colpi
                this->s[i].shoot(m,sfondo);
            } 
        muovi(sfondo,m);
    }
    else // in caso il mostro muore gli spari continuano ad esistere per un po'
        spara(m,sfondo);
}

// si occupa di stampare e settare di nuovo l'altezza sparo (sparoY)
void MOSTRO::stampa(WINDOW* w, int m[][RIGHE])
{
    unsigned i=0;
    switch (this->tipo)
    {
        case (1):
            mvwaddstr(w,y+i++,x,"    _     _    ");
            mvwaddstr(w,y+i++,x," .-'/  _  \\'-. ");
            mvwaddstr(w,y+i++,x,"/  (  < )  )  \\");
            mvwaddstr(w,y+i++,x,"\\   '_' '_'   /");
            mvwaddstr(w,y+i++,x," '-..__ __..-' ");
            mvwaddstr(w,y+i++,x,"      /_\\      ");
        break;
        
        case (2):
            mvwaddstr(w,y+i++,x,"      _     ");
            mvwaddstr(w,y+i++,x,"  ___/ |___ ");
            mvwaddstr(w,y+i++,x," /          ");
            mvwaddstr(w,y+i++,x,"(____.-.__u=");
            mvwaddstr(w,y+i++,x,"    \\_/     ");
        break;

        case (3):
            mvwaddstr(w,y+i++,x,"  __  ");
            mvwaddstr(w,y+i++,x," /__\\ ");
            mvwaddstr(w,y+i++,x,"(____)");
            mvwaddstr(w,y+i++,x," /||\\ ");
        break;
    }

    // ogni mostro ha un proprio id, in modo tale che ogni proiettile che li colpisce puo' essere riconosciuto
    // questo id viene memorizzato nelle posizioni corrispondenti al mostro in una matrice
    if(this->tipo!=0)
    {
        for(i=this->x; i<this->x+this->dimX; i++)
            for(unsigned j=this->y; j<this->y+this->dimY; j++)
                m[i][j]=this->id;
        
    }
    // ogni volta che il mostro e' stampato ha una nuova posizione quindi anche una nuova altezza sparo
    setSparoY();
}

void MOSTRO::muovi(WINDOW* w,int m[][RIGHE])
{
    srand(time(0)*id*(incr++));
    // va avanti verso le y del suo verso
    this->y=this->y+this->verso;
    
    // ogni volta che arriva alla fine o all'inizio cambia il verso e resetta la casualita' dei proiettili
    if((this->y+this->dimY)>=RIGHE || this->y<=0)
    {
        this->decadenza=((rand()*this->incr++)%9 + 5);
        this->verso*=-1;

        if(this->incr<0)
            this->incr=0;

        if((this->y+this->dimY)>=RIGHE)
            this->y=RIGHE-this->dimY;

        if(this->y<=0)
            this-> y=0;
    }
    stampa(w,m);
    
}

// fa colorare il mostro rosso quando colpito
void MOSTRO::hurt(WINDOW*& w,int m[][RIGHE])
{
    wattron(w,COLOR_PAIR(8));
    stampa(w,m);
    wattroff(w,COLOR_PAIR(8));
}

// spara tutti i proiettili
void MOSTRO::spara(int m[][RIGHE], WINDOW* w)
{
    for(unsigned i=0; i<SPARIMOSTRO; i++)
        this->s[i].shoot(m,w);
}