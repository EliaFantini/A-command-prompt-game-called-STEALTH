#include <stdio.h>//NON SI VINCE NE PERDE MAI, RIVEDI CONDIZIONE DI USCITA DAL CICLO GIOCA E PROGRAMMA AUMENTO DI LIVELLO
#include <dos.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <sys\timeb.h>
#include <string.h>
#include <conio.h>

#define DIM 15
#define S 1
#define E 2
#define N 3
#define O 4
typedef int MQ[DIM][DIM];
typedef struct Nd{
	int c;
	int r;
	struct Nd * prox;
}Nodo;
typedef Nodo * Lista;

int gioca(MQ,int,int);
int modificamq(MQ,char,Lista,int);
void stampa(MQ,int,int);
void stampafine(MQ,int,int);
int * avanzaeroe(MQ,int *);
int tr(MQ);
int tc(MQ);
int trn(MQ);
int tcn(MQ);
void haiperso(MQ);
Lista inizializzacampo(MQ , int);
void avanzanemici(MQ,Lista,int);

Lista Inizializza(void);
Lista InsInTesta ( Lista , int , int  );

int main(){
	MQ mq={};
	int vintooperso;
	char c;
	int nem=5;
	int livello=1;
	printf("\n*********************\n*********************\n   |||STEALTH|||\n*********************\n*********************\n");
	printf("Benvenuto in STEALTH soldato.\nIl tuo compito sara\' trasportare il carico fino al prossimo punto d\'estrazione situato\nnel punto piu\' a sud est della mappa evitando tutti i nemici, indicati dal [+]. ");
	printf("\n\nPer controllare la direzione utilizza i tasti W,A,S,D e muoviti di una casella con SPACE.\n\nSopravvivi a più livelli possibili.");
	printf("\n\nPremi SPACE per iniziare.");
	do{
		c=getch();
		fflush(stdin);
	}while(c!=' ');
	do{
		vintooperso=gioca(mq,nem,livello);
		nem=nem+2;
		livello++;
	}while(vintooperso==-1);
	stampafine(mq,livello,nem);
	printf("\n\n\n %s LAVORO, RAGGIUNTO LIVELLO %d\n\n PREMI SPACE PER FINIRE",livello>3?"OTTIMO":"PESSIMO",livello-1);
	do{
		c=getch();
	}while(c!=' ');
	return 0;
}

int gioca(MQ mq,int nem,int liv){
	char c;
	Lista lista=inizializzacampo(mq,nem);
	int status;
	do{
		stampa(mq,liv,nem);
		c=getch();
		fflush(stdin);
		status=modificamq(mq,c,lista,nem);		
	}while(status==0);
	return status;
}

int modificamq(MQ mq,char c,Lista lista,int nem){
	int fine=0;
	int * finep=&fine;
	switch(c){
		case 'a':mq[tc(mq)][tr(mq)]=O;break;
		case 's':mq[tc(mq)][tr(mq)]=S;break;
		case 'd':mq[tc(mq)][tr(mq)]=E;break;
		case 'w':mq[tc(mq)][tr(mq)]=N;break;
		case ' ':avanzanemici(mq,lista,nem);avanzaeroe(mq,finep);break;
		default: return fine;	
	}
	return fine;
}



void stampa(MQ mq,int liv,int nem){//testata
	system("cls");
	printf("\n\n______________________\n   LIVELLO %d: %d nemici\n----------------------\n\n\n\n        ",liv,nem);
	int col;
	int riga;
	for(riga=0;riga<DIM;riga++){
		for(col=0;col<DIM;col++){
			if(mq[col][riga]==0)printf("[ ]");
			if(mq[col][riga]==S)printf("[v]");
			if(mq[col][riga]==E)printf("[>]");
			if(mq[col][riga]==N)printf("[^]");
			if(mq[col][riga]==O)printf("[<]");
			if(mq[col][riga]==-1)printf("[X]");
			if(mq[col][riga]!=0&&mq[col][riga]!=S&&mq[col][riga]!=E&&mq[col][riga]!=O&&mq[col][riga]!=N&&mq[col][riga]!=-1){
				printf("Errore nella funzione stampa in posizione col-riga:%d-%d",col,riga);
				return ;
			}
			
		}
		printf("\n        ");
	}
	return ;
}

void stampafine(MQ mq,int liv,int nem){
	int i=0;
	int col;
	int riga;
	for(i=0;i<50;i++){
		if(i%10<=5){
				system("cls");
	printf("\n\n______________________\n   LIVELLO %d: %d nemici\n----------------------\n\n\n\n        ",liv,nem);
	for(riga=0;riga<DIM;riga++){
		for(col=0;col<DIM;col++){
			if(mq[col][riga]==0)printf("[ ]");
			if(mq[col][riga]==S)printf("[+]");
			if(mq[col][riga]==E)printf("[+]");
			if(mq[col][riga]==N)printf("[+]");
			if(mq[col][riga]==O)printf("[+]");
			if(mq[col][riga]==-1)printf("[X]");
			if(mq[col][riga]!=0&&mq[col][riga]!=S&&mq[col][riga]!=E&&mq[col][riga]!=O&&mq[col][riga]!=N&&mq[col][riga]!=-1){
				printf("Errore nella funzione stampa in posizione col-riga:%d-%d",col,riga);
				return ;
			}
			
		}
		printf("\n        ");
	}
	}
	if(i%10>5){
				system("cls");
	printf("\n\n______________________\n   LIVELLO %d: %d nemici\n----------------------\n\n\n\n        ",liv,nem);
	for(riga=0;riga<DIM;riga++){
		for(col=0;col<DIM;col++){
			if(mq[col][riga]==0)printf("[ ]");
			if(mq[col][riga]==S)printf("[X]");
			if(mq[col][riga]==E)printf("[X]");
			if(mq[col][riga]==N)printf("[X]");
			if(mq[col][riga]==O)printf("[X]");
			if(mq[col][riga]==-1)printf("[X]");
			if(mq[col][riga]!=0&&mq[col][riga]!=S&&mq[col][riga]!=E&&mq[col][riga]!=O&&mq[col][riga]!=N&&mq[col][riga]!=-1){
				printf("Errore nella funzione stampa in posizione col-riga:%d-%d",col,riga);
				return ;
			}
			
		}
		printf("\n        ");
	}
	}
	if(i==49){
				system("cls");
	printf("\n\n______________________\n   LIVELLO %d: %d nemici\n----------------------\n\n\n\n        ",liv,nem);
	for(riga=0;riga<DIM;riga++){
		for(col=0;col<DIM;col++){
			if(mq[col][riga]==0)printf("[ ]");
			if(mq[col][riga]==S)printf("[O]");
			if(mq[col][riga]==E)printf("[O]");
			if(mq[col][riga]==N)printf("[O]");
			if(mq[col][riga]==O)printf("[O]");
			if(mq[col][riga]==-1)printf("[X]");
			if(mq[col][riga]!=0&&mq[col][riga]!=S&&mq[col][riga]!=E&&mq[col][riga]!=O&&mq[col][riga]!=N&&mq[col][riga]!=-1){
				printf("Errore nella funzione stampa in posizione col-riga:%d-%d",col,riga);
				return ;
			}
			
		}
		printf("\n        ");
	}
	}
}
return;	
}


int tc(MQ mq){//testata(trova colonna in cui si trova eroe)
	int col;
	int riga;
	for(riga=0;riga<DIM;riga++){
		for(col=0;col<DIM;col++){
			if(mq[col][riga]==S||mq[col][riga]==E||mq[col][riga]==O||mq[col][riga]==N){
				return col;
			}
			
		}
	}
	printf("Errore tc");      
	return -1;
}
	
int tr(MQ mq){//testata(trova riga in cui si trova eroe)
	int col;
	int riga;
	for(riga=0;riga<DIM;riga++){
		for(col=0;col<DIM;col++){//in realtà la prima coordinata è la colonna e la seconda è la riga.
			if(mq[col][riga]==S||mq[col][riga]==E||mq[col][riga]==O||mq[col][riga]==N){
				return riga;
			}
			
		}
	}
	printf("Errore tr");
	return ;
}
	
	
int tcn(MQ mq){
	int col;
	int riga;
	for(riga=0;riga<DIM;riga++){
		for(col=0;col<DIM;col++){
			if(mq[col][riga]==-1){
				return col;
			}
			
		}
	}
	printf("Errore tcn");
	return -1;
}
	
int trn(MQ mq){
	int col;
	int riga;
	for(riga=0;riga<DIM;riga++){
		for(col=0;col<DIM;col++){
			if(mq[col][riga]==-1){
				return riga;
			}
			
		}
	}
	printf("Errore trn");
	return -1;
		
}

int * avanzaeroe(MQ mq,int * finep){//testato tutto tranne se incontra il nemico
	int c=tc(mq);
	int r=tr(mq);
	int statoeroe=mq[c][r];
	if(statoeroe==N){
		if(r!=0){
			if(mq[c][r-1]==-1){
				(*finep)++;
				return finep;
			}
			mq[c][r]=0;
			mq[c][r-1]=statoeroe;
		}
	}
	if(statoeroe==O){
		if(c!=0){
			if(mq[c-1][r]==-1){
				(*finep)++;
				return finep;
			}
			mq[c][r]=0;
			mq[c-1][r]=statoeroe;
		}
	}
	if(statoeroe==S){
		if(r!=DIM-1){
			if(mq[c][r+1]==-1){
				(*finep)++;
				return finep;
			}
			mq[c][r]=0;
			mq[c][r+1]=statoeroe;
		}
	}
	if(statoeroe==E){
		if(c!=DIM-1){
			if(mq[c+1][r]==-1){
				(*finep)++;
				return finep;
			}
			mq[c][r]=0;
			mq[c+1][r]=statoeroe;
		}
	}
	if((DIM-1==tc(mq))&&(DIM-1==tr(mq))){
				(*finep)--;
				return finep;
			}
	return finep;
}

void haiperso(MQ mq){
	return;
}

Lista inizializzacampo(MQ mq, int nem){//testato
	
	int i,i2;
	for(i=0;i<DIM;i++){
		for(i2=0;i2<DIM;i2++){
			mq[i2][i]=0;
		}
	}
	mq[0][0]=E;
	int col;
	int riga;
	Lista lista=Inizializza();
	srand(time(NULL));
	for(i=0;i<nem;i++){
		do{
			col=(rand() % ( (DIM-1)-2+1)) +2;
			riga=(rand() % ( (DIM-1)-2+1)) +2;
		} while(mq[col][riga]==-1);
		mq[col][riga]=-1;
		lista=InsInTesta(lista,col,riga);
	}
	return lista;
}

void avanzanemici(MQ mq,Lista lista, int nem){//testata
	MQ mqnem={0};
	int i,cn,rn;//cn=colonna nemico rn=riga nemico
	int randomc,randomr;
	Lista copia=lista;
	for(i=0;i<nem;i++){
		mqnem[copia->c][copia->r]=-1;
		copia=copia->prox;
	}
	copia=lista;
	srand(time(NULL));
	for(i=0;i<nem;i++){
		cn=tcn(mqnem);
		rn=trn(mqnem);
		mqnem[cn][rn]=0;
		do{
			randomc=(rand() % ( (1)+1+1)) -1 ;
			randomr=(rand() % ( (1)+1+1)) -1 ;
			} 	while((mq[cn+randomc][rn+randomr]!=0)||(cn+randomc<0)||(cn+randomc>=DIM)||(rn+randomr<0)||(rn+randomr>=DIM));
		copia->c=cn+randomc;
		copia->r=rn+randomr;
		copia=copia->prox;
		mq[cn][rn]=0;
		mq[cn+randomc][rn+randomr]=-1;
	}
	return;
}

Lista Inizializza(void){
	return NULL;
}

Lista InsInTesta ( Lista lista, int c, int r ) {
Lista punt;
punt = (Lista) malloc(sizeof(Nodo));
punt->c = c;
punt->r = r;
punt->prox = lista;
return punt;
}

