#include "Spaze_data.h"


PROTAGONISTA::PROTAGONISTA(int x)
{
    // il protagonista nasce sempre alla stessa altezza
    this->x=20;
    this->y=15;
    this->vita=5;
    for(int i=0U; i<SPARIPROT; i++)
    {
        this->a[i].setX('_');
        this->a[i].versoPositivo();
    }
    // ho messo un dato passato per rifermento per gestire la distanza tra gli spari
    deceff=x;
    decadenza=deceff;
}

void PROTAGONISTA::stampa(WINDOW* w,int m[][RIGHE])
{
    mvwaddstr(w,y,x,"<<|\\_");
    mvwaddstr(w,y+1,x,"<<|/ "); // queste due stampano la navicella

    for(unsigned i=x; i<x+5;i++)
        for(unsigned j=y; j<y+2;j++)
            m[i][j]=40;
    // ogni mostro/protagonista ha riflessa la sua posizione e il suo spazio in una matrice

    this->scalaDec(); //ogni volta che il prot viene stampato diminuisce il tempo per tornare a sparare
    stampaVita(w);
    
}

void PROTAGONISTA::muovi(WINDOW* w, int m[][RIGHE],int scelta)
{
    if(this->vita!=0) 
    {
    // ovviamente ti puoi muovere solo se hai la vita xD
    switch(scelta)
    {
        case (KEY_UP):
        this->y--;
        if(this->y<1) //se vai troppo in alto ti ritrovi la navicella in basso
        this->y=RIGHE-2;
        break;

        case (KEY_DOWN):
        this->y++;
        break;
        
        case (KEY_RIGHT):
        this->x++;
        break;

        case (KEY_LEFT):
        this->x--;
        break;

        case (' '):
        if(this->decadenza==0)
        {    
            nuovoSparo();
            this->decadenza=this->deceff;
        }
        else
            stampa(w,m);
        break;

    }

    if(this->y>RIGHE-2)
        this->y=1;
    
    // non puoi andare nella zona dei mostri
    if(this->x>COLONNE/2-6)
        this->x=COLONNE/2-6;
    if(this->x<1)
        this->x=1;

    stampa(w,m);
    
    }    
}



void PROTAGONISTA::setVita(int k)
{
    if(k>=0)
        this->vita=k;
}

void PROTAGONISTA::setX(int a)
{
    if(a>=0)
        this->x=a;
}

void PROTAGONISTA::setY(int a)
{
    if(a>=0)
        this->y=a;
}

void PROTAGONISTA::setDecEff(int k)
{
    if(k>=0)
        this->deceff=k;
}

void PROTAGONISTA::setDecadenza(int a)
{
    if(a>=0)
    this->decadenza=a;
}



int PROTAGONISTA::getX() const
{
    return this->x;
}

int PROTAGONISTA::getY() const
{
    return this->y;
}

int PROTAGONISTA::getVita() const
{
    return this->vita;
}

int PROTAGONISTA::getDecEff() const
{
    return this->deceff;
}

int PROTAGONISTA::getDecadenza() const
{
    return this->decadenza;
}

SPARO& PROTAGONISTA::getSparo(unsigned i)
{
    if(i<SPARIPROT)
        return this->a[i];
}




void PROTAGONISTA::scalaVita()
{
    if(this->vita!=0)
        vita--;
}

void PROTAGONISTA::scalaDec()
{
        if(this->decadenza!=0)
            this->decadenza--;
}




//stampa la sbarra della vita
void PROTAGONISTA::stampaVita(WINDOW*& w)
{
    // stampa la scritta HP bianca
    wattron(w,COLOR_PAIR(4));
    mvwaddstr(w,0,0,"HP ");
    wattroff(w,COLOR_PAIR(4));
    
    // stampa la riga, che e' rossa solo quando hai uno di vita se no e' sempre verde
    if(getVita()!=1)
    {
        wattron(w,COLOR_PAIR(5));
        for(unsigned i=0; i<this->getVita()&&i<COLONNE; i++)
            mvwaddch(w,0,i+3,' ');
         wattroff(w,COLOR_PAIR(5));
    }
    else
    {
        wattron(w,COLOR_PAIR(6));
            mvwaddch(w,0,getVita()+2,' ');
        wattroff(w,COLOR_PAIR(6));
    }
}

//l'effetto rosso quando ti colpiscono
void PROTAGONISTA::hurt(WINDOW*& w,int m[][RIGHE])
{
    wattron(w,COLOR_PAIR(6));
    stampa(w,m);
    wattroff(w,COLOR_PAIR(6));
}



// spara tutti i proiettili/spari
void PROTAGONISTA::spara(WINDOW* w, int m[][RIGHE])
{
    if(this->vita!=0)
    {
        for(unsigned i=0; i<SPARIPROT; i++)
            this->a[i].shoot(m,w);
    }   
}

// il primo sparo che non ha una situazione ottimale viene scelto e modificato per essere il prossimo nuovo sparo
void PROTAGONISTA::nuovoSparo()
{
    for(unsigned i=0; i<SPARIPROT; i++)
    {
        if(this->a[i].getSitua()!=-1)
        {
            this->a[i].versoPositivo();
            this->a[i].setSitua();
            this->a[i].setHx(x+5);
            this->a[i].setHy(y);
            break;
        }
    }
}
