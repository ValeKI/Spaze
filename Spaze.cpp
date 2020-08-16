#include <unistd.h>
#include "Spaze_data.h"

// qua ci sono le funzione che servono al main, sono nel Spaze_data.cpp
void start();
void end(WINDOW*&);
void cambiaSfondo(int,WINDOW*&,int[][RIGHE]);
void livello(int,WINDOW*&,int[][RIGHE],bool&,unsigned&,useconds_t);
void stampaScore(WINDOW*&, int[][RIGHE], unsigned);
void menu(WINDOW*&, int [][RIGHE],bool&);
void svuotaWGetCh(WINDOW*& w);

int main()
{
    int posizioni[COLONNE][RIGHE]={0};
    useconds_t TIME=4e4;
    unsigned score=0U;
    start();
    bool on=0;
    
    WINDOW* sfondo=NULL;
    
    menu(sfondo,posizioni,on); // in questa funzione on cambia valore se il giocatore vuole giocare

    while(on)
    {

        while(on)
        {
                if (TIME>1e4) // a un certo punto il tempo non rallenta piu'
                    TIME-=(1e4/2);
       
                for(unsigned i=1U; i<=3U && on; i++)
                    livello(i,sfondo,posizioni,on,score,TIME);
        }
        stampaScore(sfondo,posizioni,score); 
        score=0U;
        TIME=4e4; // quando muori o decidi di uscire la velocita' ritorna quella iniziale


        svuotaWGetCh(sfondo);
        menu(sfondo,posizioni,on); // on viene passato di indirizzo quindi cambia valore ed ha senso doppio while con la stessa condizione
    }
    
    end(sfondo);
    return 0;
}


