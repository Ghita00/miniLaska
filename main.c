#include <stdio.h>
#include <stdlib.h>
#include "lib.c"
#include <time.h>

const int lato = 7;

int main(){
    srand(time(NULL));
    pedina **mat = matrice(lato);
    int game=0, obbligo=0;
    while(!game) {
	    int modalita = menu(&obbligo);
	   
	    system("clear");
	
	    /*ciclo vita gioco*/
	    if (modalita == 0){
	        /*inzializzazione gioco*/
	        posiziona(mat, lato, 'b');
	        posiziona(mat, lato, 'n');
	        stampa_scac(mat, lato);
	
	    } else if (modalita == 1) {
	        /*inzializzazione gioco*/
	        posiziona(mat, lato, 'b');
	        posiziona(mat, lato, 'n');
	        stampa_scac(mat, lato);
	
	        do {
	            printf("bianchi rimanenti: %d\n", conta(mat, lato, 'b'));
	            printf("neri rimanenti: %d\n", conta(mat, lato, 'n'));
	            printf("MUOVE BIANCHI! \n");
	            seleziona(mat, lato, 'b', obbligo);
	            system("clear");
	                
	            stampa_scac(mat, lato);
	
	            if (conta(mat, lato, 'n') ) {
	                printf("bianchi rimanenti: %d\n", conta(mat, lato, 'b'));
	                printf("neri rimanenti: %d\n", conta(mat, lato, 'n'));
	                printf("MUOVE NERI! \n");
	                seleziona(mat, lato, 'n', obbligo);
	                system("clear");    
	                
	                stampa_scac(mat, lato);
	            }
	        } while (gioco(mat, lato) );
	    } else if (modalita == 2) {
	
	        /*inzializzazione gioco*/
	        posiziona(mat, lato, 'b');
	        posiziona(mat, lato, 'n');
	        stampa_scac(mat, lato);
	        do {
	            printf("bianchi rimanenti: %d\n", conta(mat, lato, 'b'));
	            printf("neri rimanenti: %d\n", conta(mat, lato, 'n'));
	            printf("MUOVE BIANCHI! \n");
	            seleziona(mat, lato, 'b', obbligo);
	            system("clear");
	                
	            stampa_scac(mat, lato);
	
	            if (conta(mat, lato, 'n') ) {
	                bot(mat, lato, 'n');
	                system("clear");
	                    
	                stampa_scac(mat, lato);
	            }
	        } while (gioco(mat, lato));
	    } else if (modalita == 4)
	    game=1;
	}
    /*fine gioco*/
    destroy(mat, lato);
    return 0;
}
