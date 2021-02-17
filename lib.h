#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char simbolo;
    int promozione;
    int kill;
}pedina;

typedef struct{
    int r;
    int c;
    int val;
}pos;

/*INTESTAZIONE
stampa il titolo ascii*/
void intestazione();

/*MENU
funzione  per decidere la modalita di gioco 
1 -> iterattiva 2 giocatori
2 -> contro computer*/
int menu(int* obbligo);

/*IMPOSTAZIONI
funzione che per mette di disattivare l'obbligo di mangiata*/
void impostazioni(int* obbligo);

/*MATRICE
creo la matrice del tipo pedina che sarà la griglia di gioco
metodologia matrice -> array di array con puntatori NO linearizzata
*/
pedina ** matrice(int lato);

/*DESTROY
distrugge la matrice allocata in memoria dinamica con la malloc
*/
void destroy(pedina ** matrice, int lato);

/*POSIZIONA
viene passato il colore della pedina che deve essere posizionata(giocatore)
e in base al giocatore viene posizionato sopra(neri) o sotto(banchi)
*/
void posiziona(pedina ** matrice, int lato, char giocatore);

/*STAMPA_SCAC
stampa la scacchiera con le cordinate polari[0:6]
la matrice di ** è solo a livello grafico
ogni pedina viene stampata come simbolo + altezza (di base 1) 
*/
void stampa_scac(pedina ** mat, int lato);

/*CONTA
dato un giocatore(che rappresenta il colore) conta le ricorrenze delle pedine di quel giocatore
*/
int conta(pedina ** matrice, int lato, char giocatore);

/*GIOCO
controlla se è stata chiusa la partita
conta il numero di pedine e se per entrembi i colori ci sono almeno 1 pedina allora continua a giocare
*/
int gioco(pedina ** matrice, int lato);

/*MANGIARE
funzione richiamata per effettuare uno spostamento oppure una mangiata. mangiare ritorna:
1 -> se non ha effettuato una mangiata e la funzione sposta si occuperà dello spostamento 
0 -> se ha effettuato la mangiata e non serve che sposta faccia un ulteririore spostamento
*/
int mangiare(pedina ** matrice, int r, int c, int r1, int c1, char giocatore);

/*CONTROLLO
funzione che controlla se sarà possibile lo spostamento sia per lo spostamento normale
che per un ipotetica mangiata
*/
int controllo(pedina ** matrice, int r, int c, char giocatore);

/*MOVIMENTO
effettua il controllo se il movimento/mangiata è possibile e lo effettua 
in caso non avvenga una mangiata allora si occupa di uno spostamento
per effettuare una mangiata bisogna targhettare una cella con una pedina di un altro colore
*/
void movimento(pedina ** matrice,int lato, char giocatore, char av_giocatore, int r, int c, int mod, int obbligo);

/*OBBLIGO MANGIATA
funzione che utilizza la funzione CONTROLLO per verificare se ci sono delle mangiate disponibili
e obbliga il giocatore a mangiare*/
int obbligomangiata(pedina ** matrice, int lato, int r, int c, char giocatore, int mod);

/*SELEZIONA
funzione che si occupa di vedere se le cordinate della pedina selezionata siano valide
se la zona dove si vuole andare è una cella vicina e libera (in caso fosse occupata prende e vede se 
la successiva è libera) 
*/
void seleziona(pedina ** matrice, int lato, char giocatore, int obbligo);

/*PROMOZIONE
funzione che si occupa di controllare se nelle righe finali si trovano delle specifiche pedine
riga 0 -> bianche e riga 6 -> nere e le promuove
queste potranno spostarsi come vogliono*/
void promozione(pedina ** matrice, int lato, char giocatore);

/*BOT
trova tutte le pedine libere e passa alla funzione movimento la pedina col l'utilità massima 
*/
void bot(pedina ** matrice, int lato, char giocatore);