/* Mateus Pereira Damasceno */

/*
1) Escreva um programa que simule o controle de uma pista de decolagem de Tie Fighters em uma Estrela
da Morte. Neste programa, o usuário deve ser capaz de realizar as seguintes tarefas:
a) Adicionar uma Tie Fighters à fila de espera;
b) Autorizar a decolagem da primeira Tie Fighters da fila;
c) Listar o número de Tie Fighters aguardando na fila de decolagem;
d) Listar todas as informações das Tie Fighters na fila de espera;
Considere que as Tie Fighters possuem o nome do piloto e um número inteiro como identificador.
Adicione outras características conforme achar necessário.
*/

#include <stdio.h>
#include <stdlib.h>
#define TAM_VET_NOME 20 // Tamanho máximo do vetor de char que guarda o nome do piloto.

/* Lista */
typedef struct lista{
	char info[TAM_VET_NOME];// Nome do piloto
    int id;                 // identificador
	struct lista *prox;     // Próximo elemento
}Lista;

/* Fila */
typedef struct fila{
	Lista *ini;
	Lista *fim;
}Fila;

void start();
void menu();
Fila *fila_cria();
void fila_insere(Fila *f, char nome[], int id);
char *fila_retira(Fila *f);
void fila_imprime(Fila *f);
int fila_conta_elementos(Fila *f);
int fila_vazia(Fila *f);
void libera_fila(Fila *f);

int main(){

    Fila *pista = fila_cria();
    char nome[TAM_VET_NOME];
    int id, opcao = -1;

    start();

    fila_insere(pista, "Fulano", 8905);
    fila_insere(pista, "Ciclano", 2357);
    fila_insere(pista, "Beltrano", 9675);
    fila_insere(pista, "Bart Weber", 4643);
    fila_insere(pista, "Indiana Jones", 1234);

    do{      
        menu();
        scanf("%d", &opcao);
        fflush(stdin);
        switch (opcao){
            case 0:
                printf("\nmay the Force be with you...\n"); // >﹏<
                break;

            case 1:
                printf("\nDigite o nome do piloto: ");
                gets(nome);
                printf("\nDigite o numero identificador do piloto: ");
                scanf("%d", &id);                
                fflush(stdin);
                fila_insere(pista, nome, id);
                printf("\nPiloto na fila.\n");
                break;

            case 2:   
                if(fila_retira(pista) != NULL){
                    printf("\nNave enviada!\n");
                }
                break;

            case 3:
                printf("\nExistem %d TIE Fighters aguardando.\n", fila_conta_elementos(pista));
                break;  
            case 4:
                fila_imprime(pista);
                break;  

            default:
                printf("Opcao invalida\n");
                break;
        }
    }while(opcao != 0);
    
    libera_fila(pista);
    return 0;
}

void start(){
printf("============== TIE FIGHTER MANAGER ==============\n\n");

printf("\t||                          ||\n");
printf("\t||                          ||\n");
printf("\t||                          ||\n");
printf("\t||                          ||\n");
printf("\t||                          ||\n");
printf("\t||           ____           ||\n");
printf("\t||         .''''''.         ||\n");
printf("\t||        /   __   \\        ||\n");
printf("\t||\\__..-':   /\\/\\   :'-..__/||\n");
printf("\t||=__ =|='  |-()-|  '=|= __=||\n");
printf("\t||/  ''-.:   \\/\\/   :.-''  \\||\n");
printf("\t||        \\   \"\"   /        ||\n");
printf("\t||         `.____.'         ||\n");
printf("\t||                          ||\n");
printf("\t||                          ||\n");
printf("\t||                          ||\n");
printf("\t||                          ||\n");
printf("\t||                          ||\n");
printf("\t||                          ||\n");
}

void menu(){

    printf("\n============== TIE FIGHTER MANAGER ==============\n\n");
    printf("[1] Adicionar uma Tie Fighter na pista\n");
    printf("[2] Autorizar a decolagem de uma Tie Fighter\n");
    printf("[3] Listar o numero de Tie Fighters aguardando\n");
    printf("[4] Listar todas as informacoes das Tie Fighters\n");
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
void fila_insere(Fila *f, char nome[], int id){
    Lista *novo = (Lista *) malloc(sizeof(Lista));
    for(int i = 0; i < TAM_VET_NOME; i++){
        novo->info[i] = nome[i];
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
	
    printf("\n======== Lista de pilotos ========\n\n");
    if(fila_vazia(f)){
		printf("Nenhum piloto!\n");
	}
    
    for(aux = f->ini; aux != NULL; aux = aux->prox){
        printf("\t%s, id: %d\n", aux->info, aux->id);
    }
    printf("\n===================================\n\n");
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
