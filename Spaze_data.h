#ifndef SPAZE_DATA_H
#define SPAZE_DATA_H
#include <ncurses.h>

const unsigned RIGHE=30U, COLONNE=80U, SPARIPROT=50U, SPARIMOSTRO=20U;

class SPARO
{
    public:
    SPARO();
    int shoot(int[][RIGHE], WINDOW*);

    void setHy(int);
    void setHx(int);

    void setSitua(int a=-1)
    {
        // puoi solo settare -1 oppure 0
        if(a==-1||a==0)
            this->situa=a;
    }
    
    void azzeraSitua();
    void setX(char s);

    void versoNegativo();
    void versoPositivo();
    
    int getSitua()const;
    int getHx()const;
    int getHy()const;
    char getX()const;
    

    private:
    int situa; // serve per conservare in che "situazione" si trova il proiettile (per esempio se ha colpito qualcosa)
    int hx, hy; // indicano le coordinate dello sparo
    char x; // e' il carattere del proiettile
    int verso; // se il proiettile va da sinistra verso destra o viceversa

};



class PROTAGONISTA
{
    public:
    PROTAGONISTA(int);
    void stampa(WINDOW*,int[][RIGHE]);
    void muovi(WINDOW*,int[][RIGHE],int);

    void setVita(int);
    void setX(int);
    void setY(int);
    void setDecEff(int);
    void setDecadenza(int);
    
    int getX() const;
    int getY() const;
    int getVita() const;
    int getDecEff() const;
    int getDecadenza() const;
    SPARO& getSparo(unsigned);

    void scalaVita();
    void scalaDec();

    void stampaVita(WINDOW*&);
    void hurt(WINDOW*&, int m[][RIGHE]);

    void spara(WINDOW*,int [][RIGHE]);
    void nuovoSparo();

    private:
    SPARO a[SPARIPROT]; // i proiettili a dispozione del protagonista
    int deceff; // ogni quanto puo' sparare
    int decadenza; // quanto manca per sparare
    int vita; // la sua vita
    int x, y; // memorizzano la sua posizione
};



class MOSTRO
{
    public:
        MOSTRO(int, int);
         
        void setSparoY();
        void setSparoY(int);
        void setX(int);
        void setY(int);
        void setDimX(int);
        void setDimY(int);
        void setVita(int);
        void setDecadenza(int);
        void setIncr(unsigned);
        void setTipo(short);
        void setVerso(short);
        void setId(short);

        int getX() const;
        int getY() const;
        short getId() const;
        int getSparoY() const;
        int getVita() const;
        int getDimX() const;
        int getDimY() const;
        int getDecadenza() const;
        unsigned getIncr() const;
        short getTipo() const;
        short getVerso() const;

        SPARO& getSparo(unsigned);

        void scalaVita(int);
        
        void sparaEmuovi(int [][RIGHE],WINDOW*);
        void stampa(WINDOW*,int[][RIGHE]);
        void muovi(WINDOW*,int[][RIGHE]);
        void hurt(WINDOW*&, int m[][RIGHE]);
        void spara(int m[][RIGHE],WINDOW*);

    private:
        int x, y; // le coordinate della posizione
        int dimX, dimY; // quanto e' grande come larghezza e altezza
        int vita; // la vita del mostro easy
        int sparoY; // ogni mostro ha una sua altezza sparo, perche' se no sparano all'inizio da dove sono stampati
        int decadenza; // valore casuale che serve per determinare ogni quando possono sparare
        unsigned incr; // serve per rendere un po' piu' casuale la decadenza
        SPARO s[SPARIMOSTRO]; // e' un array degli spari a disposizione del mostro
        short tipo, verso; // ogni mostro ha un suo tipo (aquila, aereoplano, ufo) e un verso (alto -, basso +)
        short id; //ogni mostro ha un suo id univoco che serve per essere identificato dai proiettili
};


#endif
