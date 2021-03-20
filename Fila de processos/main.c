/* Mateus Pereira Damasceno */

/*
3) Existem partes dos sistemas operacionais que cuidam da ordem em que os programas devem ser
executados. Por exemplo, em um sistema de computação de tempo-compartilhado ("time-shared") existe a
necessidade de manter um conjunto de processos em uma fila, esperando para serem executados. Escreva
um programa que seja capaz de ler uma série de solicitações para:
a) Incluir novos processos na fila de processo;
b) Retirar da fila o processo com o maior tempo de espera;
c) Imprimir o conteúdo da fila de processos em determinado momento. 
Assuma que cada processo é representado por um número identificador.
*/

#include <stdio.h>
#include <stdlib.h>
#define TAM_VET_INFO 20 // Tamanho máximo do vetor que guarda o campo info da struct que guarda os dados do elemento da fila

/* Lista */
typedef struct lista{
	char info[TAM_VET_INFO];// Informação
    int id;                 // Identificador
	struct lista *prox;     // Próximo elemento
}Lista;

/* Fila */
typedef struct fila{
	Lista *ini;
	Lista *fim;
}Fila;

void menu();
Fila *fila_cria();
void fila_insere(Fila *f, char info[], int id);
char *fila_retira(Fila *f);
void fila_imprime(Fila *f);
int fila_conta_elementos(Fila *f);
int fila_vazia(Fila *f);
void libera_fila(Fila *f);

int main(){

    Fila *f = fila_cria();
    char nome[TAM_VET_INFO];
    int id, opcao = -1;

    fila_insere(f, "Processo 1", 8905);
    fila_insere(f, "Processo 2", 2357);
    fila_insere(f, "Google Chrome", 9999);
    fila_insere(f, "Candy Crush", 4643);
    fila_insere(f, "VS Code", 1234);

    do{      
        menu();
        scanf("%d", &opcao);
        fflush(stdin);
        switch (opcao){
            case 0:
                printf("\nEncerrando...\n");
                break;
            case 1:
                printf("\nDigite o nome do processo: ");
                gets(nome);
                printf("\nDigite o identificador do processo: ");
                scanf("%d", &id);
                fflush(stdin);
                fila_insere(f, nome, id);
                printf("\nProcesso na fila.\n");
                break;
            case 2:   
                if(fila_retira(f) != NULL){
                    printf("\nProcesso removido!\n");
                }
                break;
            case 3:
                fila_imprime(f);
                break;     
            default:
                printf("Opcao invalida\n");
                break;
        }
    }while(opcao != 0);
    
    libera_fila(f);
    return 0;
}

void menu(){

    printf("\n============== TASK QUEUE ==============\n\n");
    printf("[1] Incluir um novo processo na fila de processos\n");
    printf("[2] Retirar da fila o processo com o maior tempo de espera\n");
    printf("[3] Imprimir o conteudo da fila de processos\n");
    printf("[0] Sair\n\n");
    printf("Opcao: ");

}

/* Cria uma fila */
Fila *fila_cria(){
	Fila *f = (Fila *) malloc(sizeof(Fila));
	f->ini = f->fim = NULL;
	return f;
}

/* Insere um elemento no final da fila */
void fila_insere(Fila *f, char info[], int id){
    Lista *novo = (Lista *) malloc(sizeof(Lista));
    for(int i = 0; i < TAM_VET_INFO; i++){
        novo->info[i] = info[i];
    }
    novo->id = id;
	
    novo->prox = NULL; // o novo elemento é o último da fila, não tem nada depois dele

	if(f->fim != NULL){
        f->fim->prox = novo; // Se existe alguém no fim, então o novo passa a ser o final
    }
	else{
        f->ini = novo;// Se for o primeiro elemento, ele é o primeiro e o último
    }

	f->fim = novo; // registra que o novo elemento é o último da fila 
}

/* Retira o primeiro elemento da fila */
char *fila_retira(Fila *f){
	Lista *t;
	char *v;
	if(fila_vazia(f)){
		printf("\nNenhuma nave!\n");
		return NULL;
	}
	t = f->ini;
	v = t->info;
	f->ini = t->prox;
	if(f->ini==NULL){
        f->fim = NULL;
    }
	free(t);
	return v;
}

/* Mostra os elementos na fila */
void fila_imprime(Fila *f){
	Lista *aux;
    int i = 1;
	
    printf("\n========= Lista de processos =========\n\n");
    if(fila_vazia(f)){
		printf("Nenhum processo!\n");
	}
    
    for(aux = f->ini; aux != NULL; aux = aux->prox){
        printf("\t%d: %s - ID: %d\n", i, aux->info, aux->id);
        i++;
    }
    printf("\n\tTotal: %d processos", i-1);
    printf("\n=====================================\n\n");
}

/* Conta quantos elementos uma fila possui */
int fila_conta_elementos(Fila *f){
    Lista *aux;
    int qtd = 0;
	
    if(fila_vazia(f)){
		return 0;
	}

    for(aux = f->ini; aux != NULL; aux = aux->prox){
        qtd++;
    }
    return qtd;
}

/* Retorna 1 se a fila estiver vazia, caso contrário retorna 0 */
int fila_vazia(Fila *f){
	return (f->ini == NULL);
}

/* Libera os ponteiros de uma fila */
void libera_fila(Fila *f){
	Lista *q = f->ini;
	
    while(q != NULL){
		Lista *t = q->prox;
		free(q);
		q = t;
	}

	free(f);
}
