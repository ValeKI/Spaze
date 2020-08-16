#include <unistd.h>
#include "Spaze_data.h"


// SFONDO

//inizializza lo sfondo
void start()
{
    initscr();
	cbreak();
	noecho();
	start_color();
    keypad(stdscr, TRUE);
    curs_set(0);
    init_pair(1,COLOR_BLUE,COLOR_BLACK);
    init_pair(2,COLOR_CYAN,COLOR_BLACK);
    init_pair(3,COLOR_YELLOW,COLOR_BLACK);
    init_pair(4,COLOR_WHITE,COLOR_BLACK);
    init_pair(5,COLOR_RED,COLOR_GREEN);
    init_pair(6,COLOR_RED,COLOR_RED);
    init_pair(7,COLOR_WHITE,COLOR_BLACK);
    init_pair(8,COLOR_RED,COLOR_BLACK);
    init_pair(9,COLOR_MAGENTA,COLOR_BLACK);
}

// distrugge la win 
void end(WINDOW*& s)
{
    wrefresh(s);
    wgetch(s);
    delwin(s);
	endwin();
}

// cambia le scritte e i colori della win e si occupa pure di azzerare la matrice
void cambiaSfondo(int c,WINDOW*& w, int m[][RIGHE])
{
    delwin(w);
    w=newwin(RIGHE,COLONNE,0,0);
    for(unsigned i=0U; i<COLONNE; i++)
        for(unsigned j=0U; j<RIGHE; j++)
            m[i][j]=0;
    wbkgd(w,COLOR_PAIR(c));
    keypad(w, TRUE);
    refresh();
}

// e' la schermata di pausa
bool pausa(WINDOW*& w,int m[][RIGHE])
{
    char s='0';
    cambiaSfondo(7,w,m);
    unsigned i=0;
    wattron(w,COLOR_PAIR(9));
    mvwaddstr(w,3+(i++),0,"          ___           ___           ___           ___           ___     ");
    mvwaddstr(w,3+(i++),0,"         /\\  \\         /\\  \\         /\\__\\         /\\  \\         /\\  \\    ");
    mvwaddstr(w,3+(i++),0,"        /::\\  \\       /::\\  \\       /:/  /        /::\\  \\       /::\\  \\   ");
    mvwaddstr(w,3+(i++),0,"       /:/\\:\\  \\     /:/\\:\\  \\     /:/  /        /:/\\ \\  \\     /:/\\:\\  \\  ");
    mvwaddstr(w,3+(i++),0,"      /::\\~\\:\\  \\   /::\\~\\:\\  \\   /:/  /  ___   _\\:\\~\\ \\  \\   /::\\~\\:\\  \\ ");
    mvwaddstr(w,3+(i++),0,"     /:/\\:\\ \\:\\__\\ /:/\\:\\ \\:\\__\\ /:/__/  /\\__\\ /\\ \\:\\ \\ \\__\\ /:/\\:\\ \\:\\__\\");
    mvwaddstr(w,3+(i++),0,"     \\/__\\:\\/:/  / \\/__\\:\\/:/  / \\:\\  \\ /:/  / \\:\\ \\:\\ \\/__/ \\/__\\:\\/:/  /");
    mvwaddstr(w,3+(i++),0,"          \\::/  /       \\::/  /   \\:\\  /:/  /   \\:\\ \\:\\__\\        \\::/  / ");
    mvwaddstr(w,3+(i++),0,"           \\/__/        /:/  /     \\:\\/:/  /     \\:\\/:/  /        /:/  /  ");
    mvwaddstr(w,3+(i++),0,"                       /:/  /       \\::/  /       \\::/  /        /:/  /   ");
    mvwaddstr(w,3+(i++),0,"                       \\/__/         \\/__/         \\/__/         \\/__/    ");
    wattroff(w,COLOR_PAIR(9));
    i=18;
    mvwaddstr(w,3+(i++),22,"Premi 'p' per tornare al gioco");
    mvwaddstr(w,3+(++i),22,"Premi 'e' per tornare al menu' principale");

    while(s!='e'&&s!='p') // finche' non si inserisce qualcosa la schermata e' ferma
        s=wgetch(w);

    if (s=='e')
    {
        cambiaSfondo(1,w,m);
        delwin(w);
        return 0; // indica che si deve chiudere
    }
    else
        return 1; // ritorna al gioco
}

// la schermata che indica che hai perso e sei morto al giocatore
void gameover(WINDOW*& w,int m[][RIGHE])
{
    cambiaSfondo(8,w,m);
    unsigned i=1U,j=11U;

    mvwaddstr(w,3+(i++),j,"      ___           ___           ___           ___     ");
    mvwaddstr(w,3+(i++),j,"     /\\__\\         /\\  \\         /\\  \\         /\\__\\    ");
    mvwaddstr(w,3+(i++),j,"    /:/ _/_       /::\\  \\       |::\\  \\       /:/ _/_   ");
    mvwaddstr(w,3+(i++),j,"   /:/ /\\  \\     /:/\\:\\  \\      |:|:\\  \\     /:/ /\\__\\  ");
    mvwaddstr(w,3+(i++),j,"  /:/ /::\\  \\   /:/ /::\\  \\   __|:|\\:\\  \\   /:/ /:/ _/_ ");
    mvwaddstr(w,3+(i++),j," /:/__\\/\\:\\__\\ /:/_/:/\\:\\__\\ /::::|_\\:\\__\\ /:/_/:/ /\\__\\");
    mvwaddstr(w,3+(i++),j," \\:\\  \\ /:/  / \\:\\/:/  \\/__/ \\:\\~~\\  \\/__/ \\:\\/:/ /:/  /");
    mvwaddstr(w,3+(i++),j,"  \\:\\  /:/  /   \\::/__/       \\:\\  \\        \\::/_/:/  / ");
    mvwaddstr(w,3+(i++),j,"   \\:\\/:/  /     \\:\\  \\        \\:\\  \\        \\:\\/:/  /  ");
    mvwaddstr(w,3+(i++),j,"    \\::/  /       \\:\\__\\        \\:\\__\\        \\::/  /   ");
    mvwaddstr(w,3+(i++),j,"     \\/__/         \\/__/         \\/__/         \\/__/    ");
    mvwaddstr(w,3+(i++),j,"      ___                         ___           ___     ");
    mvwaddstr(w,3+(i++),j,"     /\\  \\          ___          /\\__\\         /\\  \\    ");
    mvwaddstr(w,3+(i++),j,"    /::\\  \\        /\\  \\        /:/ _/_       /::\\  \\   ");
    mvwaddstr(w,3+(i++),j,"   /:/\\:\\  \\       \\:\\  \\      /:/ /\\__\\     /:/\\:\\__\\  ");
    mvwaddstr(w,3+(i++),j,"  /:/  \\:\\  \\       \\:\\  \\    /:/ /:/ _/_   /:/ /:/  /  ");
    mvwaddstr(w,3+(i++),j," /:/__/ \\:\\__\\  ___  \\:\\__\\  /:/_/:/ /\\__\\ /:/_/:/__/___");
    mvwaddstr(w,3+(i++),j," \\:\\  \\ /:/  / /\\  \\ |:|  |  \\:\\/:/ /:/  / \\:\\/:::::/  /");
    mvwaddstr(w,3+(i++),j,"  \\:\\  /:/  /  \\:\\  \\|:|  |   \\::/_/:/  /   \\::/~~/~~~~ ");
    mvwaddstr(w,3+(i++),j,"   \\:\\/:/  /    \\:\\__|:|__|    \\:\\/:/  /     \\:\\~~\\     ");
    mvwaddstr(w,3+(i++),j,"    \\::/  /      \\::::/__/      \\::/  /       \\:\\__\\    ");
    mvwaddstr(w,3+(i++),j,"     \\/__/        ~~~~           \\/__/         \\/__/    ");


    wtimeout(w,6e2);
    wgetch(w);
    usleep(1e6);
    delwin(w);
}

// prima di iniziare un livello appare questa schermata
void animazioneLivello(int n, WINDOW*& w, int m[][RIGHE])
{
    unsigned i=5U, j=8U;
    mvwaddstr(w,i++,j,"      ___       ___           ___           ___           ___ ");
    mvwaddstr(w,i++,j,"     /\\__\\     /\\  \\         /\\__\\         /\\  \\         /\\__\\");
    mvwaddstr(w,i++,j,"    /:/  /    /::\\  \\       /:/  /        /::\\  \\       /:/  /");
    mvwaddstr(w,i++,j,"   /:/  /    /:/\\:\\  \\     /:/  /        /:/\\:\\  \\     /:/  / ");
    mvwaddstr(w,i++,j,"  /:/  /    /::\\~\\:\\  \\   /:/__/  ___   /::\\~\\:\\  \\   /:/  /  ");
    mvwaddstr(w,i++,j," /:/__/    /:/\\:\\ \\:\\__\\  |:|  | /\\__\\ /:/\\:\\ \\:\\__\\ /:/__/   ");
    mvwaddstr(w,i++,j," \\:\\  \\    \\:\\~\\:\\ \\/__/  |:|  |/:/  / \\:\\~\\:\\ \\/__/ \\:\\  \\   ");
    mvwaddstr(w,i++,j,"  \\:\\  \\    \\:\\ \\:\\__\\    |:|__/:/  /   \\:\\ \\:\\__\\    \\:\\  \\  ");
    mvwaddstr(w,i++,j,"   \\:\\  \\    \\:\\ \\/__/     \\::::/__/     \\:\\ \\/__/     \\:\\  \\ ");
    mvwaddstr(w,i++,j,"    \\:\\__\\    \\:\\__\\        ~~~~          \\:\\__\\        \\:\\__\\");
    mvwaddstr(w,i++,j,"     \\/__/     \\/__/                       \\/__/         \\/__/");
    j=3;
    switch (n)
    {
        case 1:
        mvwaddstr(w,i++,j,"                                    ___                                             ");
        mvwaddstr(w,i++,j,"                                   /\\  \\                                            ");
        mvwaddstr(w,i++,j,"                                   \\:\\  \\                                           ");
        mvwaddstr(w,i++,j,"                                   /::\\__\\                                          ");
        mvwaddstr(w,i++,j,"                                __/:/\\/__/                                          ");
        mvwaddstr(w,i++,j,"                               /\\/:/  /                                             ");
        mvwaddstr(w,i++,j,"                               \\::/__/                                              ");
        mvwaddstr(w,i++,j,"                                \\:\\__\\                                              ");
        mvwaddstr(w,i++,j,"                                 \\/__/                                              ");
        mvwaddstr(w,i++,j,"                                                                                    ");
        break;

        case 2:
        j+=2;
        mvwaddstr(w,i++,j,"                        ___         ___                                             ");
        mvwaddstr(w,i++,j,"                       /\\  \\       /\\  \\                                            ");
        mvwaddstr(w,i++,j,"                       \\:\\  \\      \\:\\  \\                                           ");
        mvwaddstr(w,i++,j,"                       /::\\__\\     /::\\__\\                                          ");
        mvwaddstr(w,i++,j,"                    __/:/\\/__/  __/:/\\/__/                                          ");
        mvwaddstr(w,i++,j,"                   /\\/:/  /    /\\/:/  /                                             ");
        mvwaddstr(w,i++,j,"                   \\::/__/     \\::/__/                                              ");
        mvwaddstr(w,i++,j,"                    \\:\\__\\      \\:\\__\\                                              ");
        mvwaddstr(w,i++,j,"                     \\/__/       \\/__/                                              ");
        mvwaddstr(w,i++,j,"                                                                                    ");
        break;

        case 3:
        mvwaddstr(w,i++,j,"                        ___         ___         ___                                 ");
        mvwaddstr(w,i++,j,"                       /\\  \\       /\\  \\       /\\  \\                                ");
        mvwaddstr(w,i++,j,"                       \\:\\  \\      \\:\\  \\      \\:\\  \\                               ");
        mvwaddstr(w,i++,j,"                       /::\\__\\     /::\\__\\     /::\\__\\                              ");
        mvwaddstr(w,i++,j,"                    __/:/\\/__/  __/:/\\/__/  __/:/\\/__/                              ");
        mvwaddstr(w,i++,j,"                   /\\/:/  /    /\\/:/  /    /\\/:/  /                                 ");
        mvwaddstr(w,i++,j,"                   \\::/__/     \\::/__/     \\::/__/                                  ");
        mvwaddstr(w,i++,j,"                    \\:\\__\\      \\:\\__\\      \\:\\__\\                                  ");
        mvwaddstr(w,i++,j,"                     \\/__/       \\/__/       \\/__/                                  ");
        mvwaddstr(w,i++,j,"                                                                                    ");
        break;

    }

    wtimeout(w,5e2);
    wgetch(w);
    usleep(8e5);
}

// quando muore il protagonista o viene decidiso di uscire dal gioco e' mostrato il tuo score
void stampaScore(WINDOW*& w, int m[][RIGHE], unsigned score)
{
    unsigned i=3U,j=5U;
        cambiaSfondo(9,w,m);
        
    	mvwaddstr(w,i++,j,"      ___           ___           ___           ___           ___     ");
	    mvwaddstr(w,i++,j,"     /  /\\         /  /\\         /  /\\         /  /\\         /  /\\    ");
	    mvwaddstr(w,i++,j,"    /  /:/_       /  /:/        /  /::\\       /  /::\\       /  /:/_   ");
	    mvwaddstr(w,i++,j,"   /  /:/ /\\     /  /:/        /  /:/\\:\\     /  /:/\\:\\     /  /:/ /\\  ");
    	mvwaddstr(w,i++,j,"  /  /:/ /::\\   /  /:/  ___   /  /:/  \\:\\   /  /:/~/:/    /  /:/ /:/_ ");
	    mvwaddstr(w,i++,j," /__/:/ /:/\\:\\ /__/:/  /  /\\ /__/:/ \\__\\:\\ /__/:/ /:/___ /__/:/ /:/ /\\");
    	mvwaddstr(w,i++,j," \\  \\:\\/:/~/:/ \\  \\:\\ /  /:/ \\  \\:\\ /  /:/ \\  \\:\\/:::::/ \\  \\:\\/:/ /:/");
	    mvwaddstr(w,i++,j,"  \\  \\::/ /:/   \\  \\:\\  /:/   \\  \\:\\  /:/   \\  \\::/~~~~   \\  \\::/ /:/ ");
    	mvwaddstr(w,i++,j,"   \\__\\/ /:/     \\  \\:\\/:/     \\  \\:\\/:/     \\  \\:\\        \\  \\:\\/:/  ");
	    mvwaddstr(w,i++,j,"     /__/:/       \\  \\::/       \\  \\::/       \\  \\:\\        \\  \\::/   ");
	    mvwaddstr(w,i++,j,"     \\__\\/         \\__\\/         \\__\\/         \\__\\/         \\__\\/    ");
        
        wattron(w,COLOR_PAIR(7));
        mvwprintw(w,i+6,37,"%d",score);
        wattroff(w,COLOR_PAIR(7));
        
        wtimeout(w,6e2);
        wgetch(w);
        usleep(9e5);
}

// menu iniziale
void menu(WINDOW*& w, int m[][RIGHE],bool& on)
{
    bool s=1;
    
    while(1)
    {
        unsigned i=3U, j=6U;
        cambiaSfondo(9,w,m);

        mvwaddstr(w,i++,j,"             ,-.----.                             ,----,            ");
	    mvwaddstr(w,i++,j,"  .--.--.    \\    /  \\      ,---,               .'   .`|     ,---,. ");
    	mvwaddstr(w,i++,j," /  /    '.  |   :    \\    '  .' \\           .'   .'   ;   ,'  .' | ");
    	mvwaddstr(w,i++,j,"|  :  /`. /  |   |  .\\ :  /  ;    '.       ,---, '    .' ,---.'   | ");
    	mvwaddstr(w,i++,j,";  |  |--`   .   :  |: | :  :       \\      |   :     ./  |   |   .' ");
    	mvwaddstr(w,i++,j,"|  :  ;_     |   |   \\ : :  |   /\\   \\     ;   | .'  /   :   :  |-, ");
    	mvwaddstr(w,i++,j," \\  \\    `.  |   : .   / |  :  ' ;.   :    `---' /  ;    :   |  ;/| ");
    	mvwaddstr(w,i++,j,"  `----.   \\ ;   | |`-'  |  |  ;/  \\   \\     /  ;  /     |   :   .' ");
    	mvwaddstr(w,i++,j,"  __ \\  \\  | |   | ;     '  :  | \\  \\ ,'    ;  /  /--,   |   |  |-, ");
    	mvwaddstr(w,i++,j," /  /`--'  / :   ' |     |  |  '  '--'     /  /  / .`|   '   :  ;/| ");
    	mvwaddstr(w,i++,j,"'--'.     /  :   : :     |  :  :         ./__;       :   |   |    \\ ");
    	mvwaddstr(w,i++,j,"  `--'---'   |   | :     |  | ,'         |   :     .'    |   :   .' ");
    	mvwaddstr(w,i++,j,"             `---'.|     `--''           ;   |  .'       |   | ,'   ");
	    mvwaddstr(w,i++,j,"               `---`                     `---'           `----'     ");

        i=19; j=35;
        wattron(w,COLOR_PAIR(7));

        if(s)
            wattron(w,WA_REVERSE);
        mvwaddstr(w,i++,j,"NUOVA PARTITA");
        if (s)
            wattroff(w,WA_REVERSE);

        if(!s)
            wattron(w,WA_REVERSE);
        mvwaddstr(w,i++,j+4,"ESCI");
        if(!s)
            wattroff(w,WA_REVERSE);

        wattroff(w,COLOR_PAIR(7));
    
        i++; j=1;

        mvwaddstr(w,i++,j,"COMANDI MENU'");
        mvwaddstr(w,i++,j,"Muoviti su e giu' con le frecce direzionali e seleziona con invio");
        i++;
        mvwaddstr(w,i++,j,"COMANDI GIOCO");
        mvwaddstr(w,i++,j,"Muoviti verso tutte le direzioni possibili con le frecce direzionali");
        mvwaddstr(w,i++,j,"Spara con spazio e uccidi tutti i nemici per passare di livello");
        mvwaddstr(w,i++,j,"Dopo il terzo livello il gioco ricominciera' con una velocita' maggiore!");
        mvwaddstr(w,i++,j,"Metti in pausa cliccando 'p'. Buon Divertimento! cit");

        int t=0;
        wtimeout(w,1);
        while(t!=KEY_UP && t!=KEY_DOWN && t!='\n')
            t=wgetch(w);   
        usleep(3e4);

        // se premi SU o GIU' cambia la s che rappresenta s=1->NUOVA PARTITA s=0->ESCI
        if(t==KEY_UP||t==KEY_DOWN)
            if(s)
                s=0;
            else
                s=1;
    
        if(t=='\n') 
        {
            if(s)
                on=1;  // se la tua scelta e' nuova partita il gioco e' attivo
            else
                on=0; // se no e' off
            usleep(2e4);
            refresh();
            wrefresh(w);
            break; // si esce solo se si e' fatta una scelta
        }
    
    
    }
}

// FINE SFONDO



// proiettili

// gestisce chi viene colpito
void colpi(PROTAGONISTA & io, MOSTRO & lui, unsigned& score, WINDOW*& w, int m[][RIGHE])
{
    for(unsigned i=0U; i<SPARIPROT; i++)
    {    
        if(io.getSparo(i).getSitua()==lui.getId()) // se c'e' un proiettile del protagonista con l'id di quel mostro la vita del mostro scala e viene reso possibile il riutilizzo dello sparo con 0 come situa
        {
            lui.scalaVita(1);
            lui.hurt(w,m);
            score+=lui.getId();
            io.getSparo(i).azzeraSitua();
        }
        if(i<SPARIMOSTRO && lui.getSparo(i).getSitua()==40) // uguale ma 40 rappresenta il protagonista
        {
            io.scalaVita();
            io.hurt(w,m);
            lui.getSparo(i).azzeraSitua();
        }
    }
    
}

// fine proiettili

// anche questa funzione stampa lo score, ma quello in alto vicino la vita mentre e' in corso il gioco
void stampaScore(WINDOW*& w,unsigned score)
{
    wattron(w,COLOR_PAIR(7));
    mvwprintw(w,0,9,"SCORE %d",score);
    wattroff(w,COLOR_PAIR(7));
}

//svuota il wgetch
void svuotaWGetCh(WINDOW*& w)
{
    int t;
    while(1)
    {
        wtimeout(w,1);
        t=wgetch(w);
        if(!(t==KEY_UP || t==KEY_DOWN || t==KEY_LEFT || t==KEY_RIGHT || t=='\n' || t==' ' ) )
            break;
    }
}

// LIVELLO
void livello(int n, WINDOW*& sfondo,int m[][RIGHE], bool& on,unsigned& score, useconds_t TIME)
{
    svuotaWGetCh(sfondo);
    cambiaSfondo(n,sfondo,m); // cambia lo sfondo secondo il livello
    unsigned NumNemici=0;

    switch (n) // a seconda il livello ci sono diversi numeri di mostri
    {
        case 1:
        NumNemici=2;
        break;

        case 2:
        NumNemici=3;
        break;

        case 3:
        NumNemici=6;
        break;
    }

    MOSTRO **C=new MOSTRO*[NumNemici];

    for(unsigned i=0U; i<NumNemici; i++)
        C[i]=new MOSTRO(n,i+1);  // un nuovo mostro per quanti sono il numero
    
    PROTAGONISTA* hit=new PROTAGONISTA(2);

    animazioneLivello(n,sfondo,m); // schermata del livello

    for(unsigned i=0U; i<NumNemici; i++)
        C[i]->stampa(sfondo,m); //stampa i mostri

    int scelta='i';
    bool VitaMostri=0;
    unsigned VMconta=0U;
    while(!(hit->getVita()==0||VitaMostri) )
    {
        int conta=0;
        for(unsigned i=0U; i<NumNemici; i++)
        {
            if(C[i]->getVita()==0)
                conta++; // si conta quanti mostri sono morti
        }
        if(conta==NumNemici)
            VMconta++;
        if(VMconta>=20) // ma dopo un po' che sono morti finisce il livello
            VitaMostri=1;

        wtimeout(sfondo,1);
        scelta=wgetch(sfondo);
        
        if(scelta=='p')
        {
            on=pausa(sfondo,m);
            if(!on)
                break;
        }

        /*
        if(scelta=='l')
            break;
        */

        usleep(TIME); 
        cambiaSfondo(n,sfondo,m);

        hit->muovi(sfondo,m,scelta); // muove e in caso crea nuovi spari
        for(unsigned i=0U; i<NumNemici; i++)
            C[i]->sparaEmuovi(m,sfondo); // spara, crea nuovi spari, muove i mostri

        hit->spara(sfondo,m); // spara i proiettili del protagonista

        for(unsigned i=0U; i<NumNemici; i++) // gestisce se i proiettili hanno toccato qualcuno e scala la vita di esso in caso
            colpi(*hit,*C[i],score,sfondo,m); 
        
        if(hit->getVita()==0) // se la vita del protagonista finisce, finisce il livello e anche on=0 quindi si ritorna al menu'
            {
                gameover(sfondo,m);
                on=0; // il gioco va in off e ritorna al menu
                
                break;
            }

        stampaScore(sfondo,score);

        refresh();
    }

    // qui si distruggono i mostri e il protagonista
    for(unsigned i=0; i<NumNemici; i++)
        delete C[i];
    delete[] C;
    delete hit;

}

// FINE LIVELLO
