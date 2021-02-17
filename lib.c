#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

/** Questa funzione serve per la stampa dell'intestazione
 *
 */
void intestazione(){
    printf("███╗   ███╗██╗███╗   ██╗██╗██╗      █████╗ ███████╗██╗  ██╗ █████╗\n");
    printf("████╗ ████║██║████╗  ██║██║██║     ██╔══██╗██╔════╝██║ ██╔╝██╔══██╗\n");
    printf("██╔████╔██║██║██╔██╗ ██║██║██║     ███████║███████╗█████╔╝ ███████║\n");
    printf("██║╚██╔╝██║██║██║╚██╗██║██║██║     ██╔══██║╚════██║██╔═██╗ ██╔══██║\n");
    printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████╗██║  ██║███████║██║  ██╗██║  ██║\n");
    printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝\n");
    printf("\n");
}

/** Questa funzione serve per selezionare la modalità di gioco o entrae in impostazioni
 *
 * @param obbligo puntatore che verrà passato alla funzione impostazioni
 * @return ritorna la modalità in cui opera il programma
 */
int menu(int* obbligo) {
    int modalita;
    int valido = 0;
    while (!valido) {

        intestazione();
        printf("Selezionare la modalita' di gioco\n");
        printf("1. Due Player\n");
        printf("2. Player vs CPU\n");
        printf("3. Impostazioni\n");
        printf("\n4. Esci\n");

        scanf("%d", &modalita);
        if (modalita == 3) {
            impostazioni(obbligo);
        } else if (modalita == 2 || modalita == 1 || modalita == 4) {
            valido = modalita;
        } else {
            printf("Selezionare una modalita' valida \n");
            system("clear");
        }
    }
    return valido;
}

/** questa funzione modifica la regola del obbligo di mangiata
 *
 * @param obbligo puntatore che indica se la regola del obbligo di mangiata è attiva o meno
 */

void impostazioni(int * obbligo) {
    int valido = 0,interruttore;
    while(!valido) {
        printf("IMPOSTAZIONI\n");
        if( *obbligo==0) {
            printf("oblligo di mangiata: ON\n"
                   "1. OFF\n"
                   "2. Esci");

        } else {
            printf("Obblligo di mangiata: OFF\n"
                   "1. ON\n"
                   "2. Esci\n");
        }
        scanf("%d", &interruttore);
        if(interruttore==1 &&  *obbligo==0) {
             *obbligo = 1;
            interruttore = 0;
        }
        if(interruttore==1 &&  *obbligo==1) {
             *obbligo=0;
            interruttore=0;
        }
        if(interruttore==2)
            valido=1;
    }

}

/** funzione che crea la matrice 7x7 usando la tecnica degli array di array
 *
 * @param lato grandezza della matrice
 * @return ritorna il puntatore al puntatore della matrice in memoria dinamica
 */

pedina ** matrice(int lato){
    int i;
    pedina **mat;
    mat = (pedina **)malloc(sizeof(pedina *) * 7);

    for(i = 0; i < lato; i++){
        mat[i] = (pedina *)malloc(sizeof(pedina) * 7);
    }
    return mat;
}

/** funzione che fa la destroy della matrice in memoria dinamica
 *
 * @param matrice puntatore al puntatore della matrice in memoria dinamica
 * @param lato grandezza della matrice
 */
void destroy(pedina ** matrice, int lato){
    int i;
    for(i = 0; i < lato; i++){
        free(matrice[i]);
    }
    free(matrice);
}
/** funzione che posiziona le pedine per il giocatore che viene passato
 *
 * @param matrice puntatore al puntatore della matrice in memoria dinamica
 * @param lato grandezza della matrice
 * @param giocatore indica il giocatore
 */

void posiziona(pedina ** matrice, int lato, char giocatore){
    int i, j;
    int limite;

    if(giocatore == 'n'){
        i = 0;
        limite = 3;
    }
    if(giocatore == 'b'){
        i = 3;
        limite = 7;
    }

    for(; i < limite; i++){
        for(j = 0; j < lato; j++){
            if(i == 3){
                matrice[i][j].simbolo = 'v';
                matrice[i][j].promozione = 0;
                matrice[i][j].kill = 0;
            }else if(i%2 == 0 && j%2 == 0){
                matrice[i][j].simbolo = giocatore;
                matrice[i][j].promozione = 0;
                matrice[i][j].kill = 1;
            }else if(i%2 != 0 && j%2 != 0){
                matrice[i][j].simbolo = giocatore;
                matrice[i][j].promozione = 0;
                matrice[i][j].kill = 1;
            }else{
                matrice[i][j].simbolo = 'v';
                matrice[i][j].promozione = 0;
                matrice[i][j].kill = 0;
            }
        }
    }
}

/** funzione che stampa la grafica di gioco costruita sulla matrice in memoria dinamica
 *
 * @param matrice puntatore al puntatore della matrice in memoria dinamica
 * @param lato dimensione della matrice
 */

void stampa_scac(pedina ** matrice, int lato){
    int i, j, z;
    int n = lato;
    intestazione();

    printf("   ");
    for(i = 0; i < 7; i++){
        printf(" %d   ", i);
    }
    printf("\n");

	for(i = 0; i < n; i++){
        printf("  ");
        if(i==0)
            printf("┌");
        else
		    printf("├");

		for(z = 0; z < n-1; z++){
			if(z == n-1 || i==0)
		        printf("────┬");
			else
                printf("────┼");

		}

        if(i==0)
		    printf("────┐\n");
        else
            printf("────┤\n");

        printf("%d ", i);

        if(i%2 == 0)
            printf("│");

		for(j = 0; j < n; j++){

			if((i%2 == 0 && j%2 == 0)||(i%2 != 0 && j%2 != 0)){
                    printf(" ");
                if(matrice[i][j].simbolo != 'v'){
                    if(j==n-1)
                        {
                            printf("%c", matrice[i][j].simbolo);
                            printf("%d |", matrice[i][j].kill);
                    } else {
                            printf("%c", matrice[i][j].simbolo);
                            printf("%d", matrice[i][j].kill);
                        }
                } else if(matrice[i][j].simbolo == 'v' && j==n-1){
                    printf("   |");
                } else {
                    printf("  ");

                }
                printf(" ");
			}else{
				printf("│ ░░ │");
			}
		}
		printf("\n");
	}

	for(i=0;i<n;i++)
    {
        if(i==0)
            printf("  └────┴");
        else if(i==n-1)
            printf("────┘\n");
        else
            printf("────┴");
    }
}

/** funzione che conta il numero di pedine del giocatore passato
 *
 * @param matrice puntatore al puntatore della matrice in memoria dinamica
 * @param lato dimensione della matrice
 * @param giocatore giocatore passato
 * @return ritorna il numero di pedine
 */

int conta(pedina ** matrice, int lato, char giocatore){
    int i, j;
    int tot = 0;

    for(i = 0; i < lato; i++){
        for(j = 0; j < lato; j++){
            if(matrice[i][j].simbolo == giocatore || matrice[i][j].simbolo == giocatore-32)
                tot++;
        }
    }

    return tot;
}

/** funzione che sancisce la vittoria la vittoria
 *
 * @param matrice puntatore al puntatore della matrice in memoria dinamica
 * @param lato dimensione della matrice
 * @return ritorna se il gioco deve finire, in caso di vittoria, oppure continuare in caso non ci siano le condizioni di vittoria
 */

int gioco(pedina ** matrice, int lato){
    int conta_b = conta(matrice, lato, 'b');
    int conta_n = conta(matrice, lato, 'n');
    int game = 1;


    if(conta_n == 0 && conta_b > 0){
        printf("!!! VITTORIA BIANCHI !!! \n");
        game = 0;
    }else if(conta_b == 0 && conta_n > 0){
        printf("!!! VITTORIA NERI !!! \n");
        game = 0;
    }

    return game;
}

int mangiare(pedina ** matrice, int r, int c, int r1, int c1, char giocatore){
    int mangiata /*= 0*/;
    int r2;

    if(matrice[r][c].promozione == 0){
        if(giocatore == 'b'){
            r2 = r1-1;
        }else if(giocatore == 'n'){
            r2 = r1+1;
        }
    }else if(matrice[r][c].promozione == 1){
        if(r - r1 == 1){
            r2 = r1-1;
        }else if(r - r1 == -1){
            r2 = r1+1;
        }
    }

    if(matrice[r1][c1].simbolo == 'v'){
        mangiata = 1;
    } else {
        if(((r - r1 == 1 && c - c1 == 1) || (r - r1 == -1 && c - c1 == 1)) && matrice[r2][c1-1].simbolo == 'v'){
            /*nuova cella direzione 1*/
            matrice[r2][c1-1].simbolo = matrice[r][c].simbolo;
            if(matrice[r][c].kill < 3)
                matrice[r2][c1-1].kill = (matrice[r][c].kill)+ 1;
            else
                matrice[r2][c1-1].kill = matrice[r][c].kill;
            matrice[r2][c1-1].promozione = matrice[r][c].promozione;

        }else if(((r - r1 == -1 && c - c1 == -1) || (r - r1 == 1 && c - c1 == -1)) && matrice[r2][c1+1].simbolo == 'v'){
            /*nuova cella direzione 2*/
            matrice[r2][c1+1].simbolo = matrice[r][c].simbolo;
            if(matrice[r][c].kill < 3)
                matrice[r2][c1+1].kill = (matrice[r][c].kill + 1);
            else
                matrice[r2][c1+1].kill = matrice[r][c].kill ;
            matrice[r2][c1+1].promozione = matrice[r][c].promozione;
        }

        if(matrice[r1][c1].kill -1 == 0){
            /*cella di mezzo, ex cella avversaria*/
            matrice[r1][c1].simbolo = 'v';
            matrice[r1][c1].kill = 0;
            matrice[r1][c1].promozione = 0;
        }else{
            matrice[r1][c1].kill = matrice[r1][c1].kill-1;
        }

        /*cella vecchia*/
        matrice[r][c].simbolo = 'v';
        matrice[r][c].kill = 0;
        matrice[r][c].promozione = 0;

        mangiata = 0;
    }

    return mangiata;
}

/** funzione che controlla se sarà possibile muovere la pedina sia per effetturare un'ipotetica mangiata oppure uno spostamento senza mangiare
 *
 * @param matrice puntatore al puntatore della matrice in memoria dinamica
 * @param lato dimensione della matrice
 * @param r riga di partenza
 * @param c colonna di partenza
 * @param giocatore pedina del giocatore da controllare
 * @return ritorna 0 se non è possibili muovere la pedina, 1 se è possibile muovere la pedina normalmente, 2 se è possibile muoverla effettuando una mangiata
 */
int controllo(pedina ** matrice, int r, int c, char giocatore){
    int chek = 0;
    int r1;
    char av_giocatore;
    int r_start = r;

    if(giocatore == 'n' || giocatore == 'N')
        av_giocatore = 'b';
    if(giocatore == 'b' || giocatore == 'B')
        av_giocatore = 'n';

    if(matrice[r][c].promozione == 0){
        /*controlli senza la promozione, prima*/
        if(giocatore == 'n' || giocatore == 'N'){
            r++;;
            r1 = r+1;
            av_giocatore = 'b';
        }else if(giocatore == 'b' || giocatore == 'B'){
            r--;
            r1 = r-1;
            av_giocatore = 'n';
        }

        if(c+1 >= 7 || c-1 < 0){
            if(c+1 >= 7 && matrice[r][c-1].simbolo == 'v' ){
                chek = 1;
            } else if(c-1 < 0 && matrice[r][c+1].simbolo == 'v' ){
                chek = 1;
            }
            if(c+1 >= 7 && matrice[r1][c-2].simbolo == 'v' && (matrice[r][c-1].simbolo == av_giocatore || matrice[r][c-1].simbolo == av_giocatore-32)){
                chek = 2;
            } else if( c-1 < 0 && matrice[r1][c+2].simbolo == 'v' && (matrice[r][c+1].simbolo == av_giocatore || matrice[r][c+1].simbolo == av_giocatore-32)){
                chek = 2;
            }
        }else{
            if((av_giocatore == 'n' && r_start == 1) || (av_giocatore == 'b' && r_start == 5)){
                if(matrice[r][c+1].simbolo == 'v' || matrice[r][c-1].simbolo == 'v'){
                    chek = 1;
                }
            }
            else{
                if(matrice[r][c+1].simbolo == 'v' || matrice[r][c-1].simbolo == 'v'){
                    chek = 1;
                }
                if(matrice[r1][c+2].simbolo == 'v' && (matrice[r][c+1].simbolo == av_giocatore || matrice[r][c+1].simbolo == av_giocatore-32)){
                    chek = 2;
                }else if(matrice[r1][c-2].simbolo == 'v' && (matrice[r][c-1].simbolo == av_giocatore || matrice[r][c-1].simbolo == av_giocatore-32)){
                    chek = 2;
                }
            }
        }
        if(r_start == 5 && giocatore == 'n' && (matrice[r][c+1].simbolo == 'v' || matrice[r][c-1].simbolo == 'v')){
            chek = 3;/*quando può effettuare la promozione*/
        } 

    }else{
        /*controlli quando e promossa*/
        
        if(r == 0){
            if(c == 0){
                if(matrice[r+1][c+1].simbolo == 'v'){
                    chek = 1;
                } 
                if(matrice[r+2][c+2].simbolo == 'v' && (matrice[r+1][c+1].simbolo == av_giocatore || matrice[r+1][c+1].simbolo == av_giocatore-32))
                    chek = 2; 
            }else if(c == 6){
                if(matrice[r+1][c-1].simbolo == 'v'){
                    chek = 1;
                } 
                if(matrice[r+2][c-2].simbolo == 'v' && (matrice[r+1][c-1].simbolo == av_giocatore || matrice[r+1][c-1].simbolo == av_giocatore-32))
                    chek = 2;  
            }else{
                if(matrice[r+1][c+1].simbolo == 'v' || matrice[r+1][c-1].simbolo == 'v')
                    chek = 1;
                if(matrice[r+2][c+2].simbolo == 'v' && (matrice[r+1][c+1].simbolo == av_giocatore || matrice[r+1][c+1].simbolo == av_giocatore-32))
                    chek = 2;
                if( matrice[r+2][c-2].simbolo == 'v' && (matrice[r+1][c-1].simbolo == av_giocatore || matrice[r+1][c-1].simbolo == av_giocatore-32))
                    chek = 2;   
            } 
        } else if(r == 6){
            if(c == 0){
                if(matrice[r-1][c+1].simbolo == 'v'){
                    chek = 1;
                } 
                if(matrice[r-2][c+2].simbolo == 'v' && (matrice[r-1][c+1].simbolo == av_giocatore || matrice[r-1][c+1].simbolo == av_giocatore-32)){
                    chek = 2;
                }
            } else if(c == 6){
                if(matrice[r-1][c-1].simbolo == 'v'){
                    chek = 1;
                }
                if(matrice[r-2][c-2].simbolo == 'v' && (matrice[r-1][c-1].simbolo == av_giocatore || matrice[r-1][c-1].simbolo == av_giocatore-32)){
                    chek = 2;
                }
            } else {
                if(matrice[r-1][c+1].simbolo == 'v' || matrice[r-1][c-1].simbolo == 'v')
                    chek = 1;
                if(matrice[r-2][c+2].simbolo == 'v' && (matrice[r-1][c+1].simbolo == av_giocatore || matrice[r-1][c+1].simbolo == av_giocatore-32))
                    chek = 2;
                if( matrice[r-2][c-2].simbolo == 'v' && (matrice[r-1][c-1].simbolo == av_giocatore || matrice[r-1][c-1].simbolo == av_giocatore-32))
                    chek = 2;
            } 
        } else if(r == 1){
            if(matrice[r+1][c+1].simbolo == 'v' || matrice[r+1][c-1].simbolo == 'v'){
                chek = 1;
            } else if(matrice[r-1][c+1].simbolo == 'v' || matrice[r-1][c-1].simbolo == 'v'){
                chek = 1;
            }
                if(matrice[r+2][c+2].simbolo == 'v' && (matrice[r+1][c+1].simbolo == av_giocatore || matrice[r+1][c+1].simbolo == av_giocatore-32))
                    chek = 2;
                if( matrice[r+2][c-2].simbolo == 'v' && (matrice[r+1][c-1].simbolo == av_giocatore || matrice[r+1][c-1].simbolo == av_giocatore-32))
                    chek = 2;
            
        } else if(r == 5){
            if(matrice[r-1][c+1].simbolo == 'v' || matrice[r-1][c-1].simbolo == 'v'){
                chek = 1;
            }else if(matrice[r+1][c+1].simbolo == 'v' || matrice[r+1][c-1].simbolo == 'v'){
                chek = 1;
            }
                if(matrice[r-2][c+2].simbolo == 'v' && (matrice[r-1][c+1].simbolo == av_giocatore || matrice[r-1][c+1].simbolo == av_giocatore-32))
                    chek = 2;
                if( matrice[r-2][c-2].simbolo == 'v' && (matrice[r-1][c-1].simbolo == av_giocatore || matrice[r-1][c-1].simbolo == av_giocatore-32))
                    chek = 2;
            
        } else{
            
            if(matrice[r+1][c+1].simbolo == 'v' || matrice[r+1][c-1].simbolo == 'v'){
                chek = 1;
            } else if(matrice[r-1][c+1].simbolo == 'v' || matrice[r-1][c-1].simbolo == 'v'){
                chek = 1;
            }
            if(matrice[r-2][c+2].simbolo == 'v' && matrice[r-1][c+1].simbolo == av_giocatore){
                chek = 2;
            } else if(matrice[r-2][c-2].simbolo == 'v' && matrice[r-1][c-1].simbolo == av_giocatore){
                chek = 2;
            } else if(matrice[r+2][c+2].simbolo == 'v' && matrice[r+1][c+1].simbolo == av_giocatore){
                chek = 2;
            } else if(matrice[r+2][c-2].simbolo == 'v' && matrice[r+1][c-1].simbolo == av_giocatore){
                chek = 2;
            }
            
        }
    }

    return chek;
}

/** funzione che effettua il movimento di una pedina tenedo conto anche del colore avversario oltre alle regole
 *
 * @param matrice matrice puntatore al puntatore della matrice in memoria dinamica
 * @param lato dimensione della matrice in memoria dinamica
 * @param giocatore giocatore che sposta la pedina
 * @param av_giocatore giocatore avversario
 * @param r riga di partenza
 * @param c colonna di partenza
 * @param mod valore che identifica se i valori devono essere inseriti dal utente o dal PC (random)
 * @param obbligo valore che identifica se la regola di obbligo di mangiate è ON o OFF
 */

void movimento(pedina ** matrice,int lato, char giocatore, char av_giocatore, int r, int c, int mod, int obbligo){
    int r1, c1, i;
    int exe = 0, exe_suc;
    int z = 0;

    pos * muovi = (pos *)malloc(sizeof(pos) * 4);
    /*basso sinistra*/
        muovi[0].r = r + 1;
        muovi[0].c = c + 1;
        muovi[0].val = controllo(matrice, r, c, giocatore);

    /*basso destra*/

        muovi[1].r = r + 1;
        muovi[1].c = c - 1;
        muovi[1].val = controllo(matrice, r, c, giocatore);

    /*alto destra*/
    muovi[2].r = r-1;
    muovi[2].c = c+1;
    muovi[2].val = controllo(matrice, r, c, giocatore);
    /*alto sinistra*/
    muovi[3].r = r-1;
    muovi[3].c = c-1;
    muovi[3].val = controllo(matrice, r, c, giocatore);


    while(!exe){
        int vabene = 0;
        if(mod == 1){
            printf("riga successiva: ");
            scanf("%d", &r1);
            printf("colonna successiva: ");
            scanf("%d", &c1);
        }else{
                if (z == 4) {
                    printf("Bot incastrato! Si prega di fare una mossa");
                    printf("riga successiva: ");
                    scanf("%d", &r1);
                    printf("colonna successiva: ");
                    scanf("%d", &c1);
                } else {
                    r1 = muovi[z].r;
                    c1 = muovi[z].c;
                    z++;
                }
        }

        if(obbligo == 2) {
            vabene = obbligomangiata(matrice, lato, r1, c1, giocatore, 2);
            if (vabene == 1)
                printf("e' obbligatorio mangiare!\n");
        }

        if(matrice[r][c].promozione == 0 && vabene==0){
            if(r1 >= 0 && r1 < 7 || c1 >= 0 || c1 < 7){
                if(matrice[r][c].simbolo == 'b' && r1 - r == -1 && (c1 - c == 1 || c1 - c == -1)){
                    if(matrice[r1][c1].simbolo == 'v'){
                        exe = 1;
                        exe_suc = 1;
                    }else if(matrice[r1][c1].simbolo == av_giocatore || matrice[r1][c1].simbolo == av_giocatore-32){
                        if(r-r1 == 1 && c-c1 == 1 && matrice[r1-1][c1-1].simbolo == 'v'){
                            exe_suc = mangiare(matrice, r, c, r1, c1, giocatore);
                            exe = 1;
                            if(exe_suc){
                                printf("mangiata non possibile \n");
                            }
                        }
                        if(r-r1 == 1 && c-c1 == -1 && matrice[r1-1][c1+1].simbolo == 'v'){
                            exe_suc = mangiare(matrice, r, c, r1, c1, giocatore);
                            exe = 1;
                            if(exe_suc){
                                printf("mangiata non possibile \n");
                            }
                        }
                    } else{
                        printf("cella non vuota \n");
                    }
                }else if(matrice[r][c].simbolo == 'n' && r1 - r == 1 && (c1 - c == 1 || c1 - c == -1)){
                    if(matrice[r1][c1].simbolo == 'v' ){
                        exe = 1;
                        exe_suc = 1;
                    } else if(matrice[r1][c1].simbolo == av_giocatore || matrice[r1][c1].simbolo == av_giocatore-32){
                        if(r-r1 == -1 && c-c1 == -1 && matrice[r1+1][c1+1].simbolo == 'v'){
                            exe_suc = mangiare(matrice, r, c, r1, c1, giocatore);

                            if(exe_suc){
                                printf("mangiata non possibile \n");
                            }else{
                                exe = 1;
                            }
                        }else if(r-r1 == -1 && c-c1 == 1 && matrice[r1+1][c1-1].simbolo == 'v'){
                            exe_suc = mangiare(matrice, r, c, r1, c1, giocatore);

                            if(exe_suc){
                                printf("mangiata non possibile \n");
                            }else {
                                exe = 1;
                            }
                        }
                    } else{
                        printf("cella non vuota \n");
                    }
                } else{
                    printf("cella lontana 1\n");
                }
            } else{
                printf("fuori matrice \n");
            }
        } else if (vabene==0) {
            int s = 1;
            if(r1 >= 0 && r1 < 7 || c1 >= 0 || c1 < 7){
                if((r1 - r == 1 || r1 - r == -1) && (c1 - c == 1 || c1 - c == -1)){

                    if((matrice[r1][c1].simbolo == giocatore ||matrice[r1][c1].simbolo == giocatore-32)){
                        printf("mangiata/passo non possibile \n");
                    }else if((r == 1 && r1 == 0 || r == 5 && r1 == 6) && matrice[r1][c1].simbolo != 'v'){
                        exe = 0;
                        printf("cella occupata \n");
                    }else if(matrice[r1][c1].simbolo == 'v' ){
                        exe = 1;
                        exe_suc = 1;
                    }else if(matrice[r1][c1].simbolo == av_giocatore || matrice[r1][c1].simbolo == av_giocatore-32){

                        if(r1-r == 1 && c1-c == -1){
                            if(matrice[r1+1][c1-1].simbolo != 'v' || matrice[r1][c1].simbolo == giocatore || matrice[r1][c1].simbolo == giocatore-32){
                               printf("movimento verso destra per il basso non possibile \n");
                               s = 0;
                            }
                        } else if(r1-r == 1 && c1-c == 1){
                            if(matrice[r1+1][c1+1].simbolo != 'v' || matrice[r1][c1].simbolo == giocatore || matrice[r1][c1].simbolo == giocatore-32){
                               printf("movimento verso sinistra per il basso non possibile \n");
                                s = 0;
                            }
                        } else if(r1-r == -1 && c1-c == -1){
                            if(matrice[r1-1][c1-1].simbolo != 'v' || matrice[r1][c1].simbolo == giocatore || matrice[r1][c1].simbolo == giocatore-32){
                               printf("movimento verso sinistra per l' alto non possibile \n");
                                s = 0;
                            }
                        } else if(r1-r == -1 && c1-c == +1){
                            if(matrice[r1-1][c1-1].simbolo != 'v' || matrice[r1][c1].simbolo == giocatore || matrice[r1][c1].simbolo == giocatore-32){
                                printf("movimento verso destra per l' alto non possibile \n");
                                s = 0;
                            }
                        }
                        if(s == 1){
                            exe = 1;
                            exe_suc = mangiare(matrice, r, c, r1, c1, giocatore);
                        }
                    }
                } else{
                    printf("cella lontana 2\n");
                }
            } else{
                printf("fuori matrice \n");
            }
        }
    }

    if(exe_suc){
        matrice[r1][c1].simbolo = matrice[r][c].simbolo;
        matrice[r1][c1].kill = matrice[r][c].kill;
        matrice[r1][c1].promozione = matrice[r][c].promozione;
        matrice[r][c].simbolo = 'v';
        matrice[r][c].kill = 0;
        matrice[r][c].promozione = 0;
    }
    promozione(matrice, lato, giocatore);
    free(muovi);
}

/** funzione che se chiamata in modalità 1 controlla se ci sono delle mangiate da fare, se chiamata in modalità 2 controlla se viene effettivamente effettuata la mangiata
 *
 * @param matrice matrice puntatore al puntatore della matrice in memoria dinamica
 * @param lato dimensione della matrice
 * @param r riga di partenza
 * @param c colonna di partenza
 * @param giocatore giocatore che deve effettuare la mangiata
 * @param mod modalità di funzionamento della funzione
 * @return in mod 1 ritona 0 se viene selezionata una pedina che deve mangiare, 1 altrienti. In mod 2 ritorna 0 se viene effettuata la mangiata, 1 altrimenti
 */

int obbligomangiata(pedina ** matrice, int lato, int r, int c, char giocatore, int mod){
    int num = conta(matrice, lato, giocatore);
    int visitate = 0;
    int i=0,j;
    int mangiate_possibili=0;

    if(mod==1) {
        while (visitate != num && i <= lato) {
            j = 0;
            while (visitate != num && j <= lato) {
                if (matrice[i][j].simbolo == giocatore || matrice[i][j].simbolo == giocatore - 32) {
                    visitate++;
                    if (controllo(matrice, i, j, giocatore) == 2) {
                        mangiate_possibili++;
                        if (i == r && j == c) {
                            return 0;
                        }
                    }
                }
                j++;
            }
            i++;
        }

    if(mangiate_possibili != 0)
        return 1;
    else
        return 0;
    }

    if(mod==2)
    {
        if(giocatore=='n')
        {
            if(matrice[r][c].simbolo == 'b'  || matrice[r][c].simbolo == 'B')
                return 0;
        }
        if(giocatore=='b')
        {
            if(matrice[r][c].simbolo == 'n'  || matrice[r][c].simbolo == 'N')
                return 0;
        }
    }

    return 1;
}

/** funzione che seleziona la pedina e controlla se può essere selezionata
 *
 * @param matrice matrice puntatore al puntatore della matrice in memoria dinamica
 * @param lato dimensione della matrice
 * @param giocatore giocatore che effettua la selezione
 * @param obbligo parametro che indica se è attivo o meno l'obbligo di mangiata
 */

void seleziona(pedina ** matrice, int lato, char giocatore, int obbligo){
    int r, c;
    int vabene = 0;
    char av_giocatore;
    int valida;

    if(giocatore == 'b'){
        av_giocatore = 'n';
    }else if(giocatore == 'n'){
        av_giocatore = 'b';
    }

    while(!vabene){
        printf("riga:");
        scanf("%d", &r);
        
        printf("colonna:");
        scanf("%d", &c);

        
        if(r < 0 || r >= 7 || c < 0 || c >= 7){
            printf("fuori matrice \n");
        }else{
            
            if(matrice[r][c].simbolo == av_giocatore || matrice[r][c].simbolo == (av_giocatore-32) ) {
                printf("selezione errata \n");
            }else if(matrice[r][c].simbolo == 'v'){
                printf("cella vuota\n");
            }else{
                vabene = controllo(matrice, r, c, giocatore);
                if(!vabene){
                    printf("non spostabile \n");
                }
            }
        }
        if(obbligo == 0) {
            valida = obbligomangiata(matrice, lato, r, c, giocatore,1);
            if (valida == 1) {
                printf("Selezione non valida, e' obbligatorio mangiare!\n");
                vabene = 0;
            }
        }
        
    }
    movimento(matrice, lato, giocatore, av_giocatore, r, c, 1, controllo(matrice, r, c, giocatore));
}

/** funzione che effettua la promozione quando un giocatore raggiunge il lato opposto
 *
 * @param matrice matrice puntatore al puntatore della matrice in memoria dinamica
 * @param lato dimensione della matrice
 * @param giocatore giocatore che deve essere promosso
 */
void promozione(pedina ** matrice, int lato, char giocatore){
    int i, j;

    if(giocatore == 'b'){
        i = 0;
        for(j = 0; j<lato; j++){
            if(matrice[i][j].simbolo == 'b'){
                matrice[i][j].simbolo = 'B';
                matrice[i][j].promozione = 1;
            }
        }
    }else if(giocatore == 'n'){
        i = 6;
        for(j = 0; j<lato; j++){
            if(matrice[i][j].simbolo == 'n'){
                matrice[i][j].simbolo = 'N';
                matrice[i][j].promozione = 1;
            }
        }
    }
}

/** questa funzione effettua lo spostamento automatico di un colore
 *
 * @param matrice matrice puntatore al puntatore della matrice in memoria dinamica
 * @param lato dimensione della matrice
 * @param giocatore colore della pedina che muoverà il bot
 */
void bot(pedina ** matrice, int lato, char giocatore){
    int num = conta(matrice, lato, giocatore);
    int visitate = 0, obbligo=0;
    int i = 0, j, z = 0;
    pos * max = (pos *)malloc(sizeof(pos));
    pos * valide = (pos *)malloc(sizeof(pos)*num);
    int val;

    while(visitate != num && i < lato){
        j = 0;
        while(visitate != num && j < lato){
            if(matrice[i][j].simbolo == giocatore || matrice[i][j].simbolo == giocatore-32){
                visitate++;
                val = controllo(matrice, i, j, giocatore);
                if(val != 0){
                    valide[z].r = i;
                    valide[z].c = j;
                    valide[z].val = val;
                    z++;
                }
            }
            j++;
        }
        i++;
    }
    max -> r = valide[0].r;
    max -> c = valide[0].c;
    max -> val = valide[0].val;

    for(z = 1; z < num; z++){
        if(max->val < valide[z].val){
            max -> r = valide[z].r;
            max -> c = valide[z].c;
            max -> val = valide[z].val;
        }
    }

    printf("pos %d \n", 1);
    printf("r = %d \n", max->r);
    printf("c = %d \n\n", max->c);
    printf("val = %d\n", max->val);

    if(controllo(matrice,max->r, max->c,giocatore)==2)
        obbligo=2;

    movimento(matrice, lato, giocatore, 'b', max->r, max->c, 2,obbligo);

    free(valide);
    free(max);
}
