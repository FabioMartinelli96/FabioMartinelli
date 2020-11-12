#include <stdio.h>
#include <stdlib.h> // includo questa libreria per utilizzare rand() e srand()
#include <time.h> // includo questa libreira per utilizzare time()
#include <string.h>

char m[128], k[128], c[128], m2[128], scelta;
int lunghezza_m, lunghezza_k;
time_t t;
char ch;
/* Definisco le funzioni */
void plaintextM();
void richiesta();
void chiaveManuale();
void chiaveCasuale();

int main()
{
    /* Inizializzo il generatore di numeri casuali utilizzando il tempo attuale  */
    srand((unsigned) time(&t)); // Funzione da chiamare una sola volta

    plaintextM();

    richiesta();
}

/* Chiedo all'utente di inserire una stringa di testo da cifrare */
void plaintextM()
{
    printf("Inserisco una stringa M:\n");
    fgets(m, 128, stdin); // utilizzo la funzione fgets per controllare che la stringa letta non superi 128 caratteri
    lunghezza_m = strlen(m)-1;
    printf("\n");
    printf("La stringa inserita è: %s", m);
    printf("La lunghezza della stringa M è di: %d caratteri\n", lunghezza_m);
}

/* Dopo aver inserito il nostro plaintext M, chiedere all'utente come procedere attrverso uno switch */
void richiesta()
{
    while((ch= getchar())!= '\n' && ch != EOF);
    int verifica = 0;
    do{
        printf("\n");
        printf("Scegliere un numero per procedere.\n");
        printf("1. Inserire la chiave manualmente per cifrare il plaintext M.\n");
        printf("2. Generare in modo casuale la chiave per cifrare il plaintext M.\n");
        printf("3. Uscire dal programma.\n");
        printf("\n");
        printf("Inserisci il numero desiderato:\n");
        scanf("%c", &scelta);
        switch (scelta) {
            case '1':
            chiaveManuale();
            verifica = 1;
            break;
            case '2':
            chiaveCasuale();
            verifica = 1;
            break;
            case '3':
            return;
            verifica = 1;
            break;
            default:
            printf("\n******\n");
            printf("\nPrego inserire un numero valido\n");
            printf("\n******\n");
        }
    }while(!verifica);
}

/* Dopo che l'utente ha scelto il caso 1, si richiede di inserire manualmente la chiave k che si utilizzerà per cifreare il plaintext M */
void chiaveManuale()
{
    while((ch= getchar())!= '\n' && ch != EOF); // utilizzo questo ciclo per pulire il buffer da caratteri indesiderati
    do{
        printf("Inserire la chiave k manualmente (deve avere lunghezza maggiore o ugale alla lunghezza di M):\n");
        fgets(k, 128, stdin);
        lunghezza_k = strlen(k)-1;
            if(lunghezza_k < lunghezza_m){
              printf("\nErrore: la chiave deve avere lunghezza compresa tra %d e 128 caratteri\n", lunghezza_m);
            }
    }while(lunghezza_k < lunghezza_m);
    printf("La chiave k è: %s", k);
    printf("La lunghezza della chiave k è di: %d caratteri\n", lunghezza_k);
    printf("\n");

    /* Ciclo for che serve per cifrare la stringa M con la chiave K */
    for(int i = 0; i < strlen(m); i++){
        c[i] = m[i] ^ k[i]; // Utilizzo l'operazione XOR per cifrare
        c[i] += 32; // Aggiungo 32 caratteri per escludere quelli "speciali"
    }
    printf("\nIl risultato della cifratura (c) è: ");
    printf("%s", c);
    printf("\n");

    /* Ciclo for per decifrare la stringa C per resituire la stringa originale M */
    for(int i = 0; i < strlen(m); i++){
        c[i] -= 32; // Tolgo 32 caratteri per resituire correttamente la stringa originale
        m2[i] = c[i] ^ k[i];
    }
    printf("Il risultato della decifratura (m) è: ");
    printf("%s", m2);
    printf("\n");
}

/* Dopo che l'utente ha scelto il caso 2, genero una chiave k randomica */
void chiaveCasuale()
{
    while((ch= getchar())!= '\n' && ch != EOF);
    for(int i=0; i < (strlen(m)-1); i++){
        k[i] = 32 + rand() % 96; // ritorna un numero tra 32 e 128 (escludendo i numeri tra 0 e 31 della tabella ASCII che sono "speciali")
    }
    printf("La chiave randomica k è:");
    printf("%s", k);

    for(int i = 0; i < strlen(m); i++){
        c[i] = m[i] ^ k[i];
        c[i] += 32;
    }
    printf("\nIl risultato della cifratura (c) è: ");
    printf("%s", c);
    printf("\n");

    for(int i = 0; i < strlen(m); i++){
        c[i] -= 32;
        m2[i] = c[i] ^ k[i];
    }
    printf("Il risultato della decifratura (m) è: ");
    printf("%s", m2);
    printf("\n");

}
