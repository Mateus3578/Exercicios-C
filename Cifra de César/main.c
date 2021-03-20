/* Mateus Pereira Damasceno */

/*
4) A Cifra de César: Em criptografia, a Cifra de César, também conhecida como cifra de troca, código de
César ou troca de César, é uma das mais simples e conhecidas técnicas de criptografia. É um tipo de cifra
de substituição na qual cada letra do texto é substituída por outra, que se apresenta no alfabeto abaixo dela
um número fixo de vezes. Por exemplo, com uma troca de três posições, A seria substituído por D, B se
tornaria E, e assim por diante. O nome do método é em homenagem a Júlio César, que o usou para se
comunicar com os seus generais.
A transformação pode ser representada alinhando-se dois alfabetos; o alfabeto cifrado é o alfabeto normal
rotacionado à direita ou esquerda por um número de posições. Por exemplo, aqui está uma cifra de César
usando uma rotação à esquerda de três posições (o parâmetro de troca, três neste caso, é usado como
chave).
Para criptografar uma mensagem, deve-se simplesmente observar cada letra da mensagem na linha
"Normal"e escrever a letra correspondente na linha "Cifrado". Para descriptografar, deve-se fazer o
contrário.
Normal: Eu gosto muito da aula de AEDS
Cifrado: HX JRVWR PXLWR GD DXOD GH DHGV

Dada a Cifra de César usando uma rotação à esquerda de três posições, faça:
-Implemente uma Fila com Lista Encadeada onde cada elemento é uma Senha criptografada de tamanho
máximo 6. 
-A Fila deve conter apenas as senhas criptogradas. 
-Deve ser possível listar as senhas armazenadas e descriptografá-las.
Dica: Lembre-se que o char A somado a 3 é igual a D.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAM_VET_INFO 7 // Tamanho máximo da senha + 1 ('\0')

/* Lista */
typedef struct lista{
    char info[TAM_VET_INFO];    // Informação
	struct lista *prox;         // Próximo elemento
}Lista;

/* Fila */
typedef struct fila{
	Lista *ini;
	Lista *fim;
}Fila;

void menu();
Fila *fila_cria();
void fila_insere(Fila *f, char info[]);
char *fila_retira(Fila *f);
void fila_imprime(Fila *f);
void fila_imprime_decodificada(Fila *f);
int fila_vazia(Fila *f);
void libera_fila(Fila *f);

int main(){

    Fila *f = fila_cria();
    char *nome = (char*)malloc(TAM_VET_INFO*sizeof(char));
    int opcao = -1;

/*
    fila_insere(f, "senha");
    fila_insere(f, "de");
    fila_insere(f, "seis");
    fila_insere(f, "carac-");
    fila_insere(f, "teres");
    fila_insere(f, "e");
    fila_insere(f, "fraca");
*/
    do{      
        menu();
        fflush(stdin);
        scanf("%d", &opcao);
        fflush(stdin);
        switch (opcao){
            case 0:
                printf("\nEncerrando...\n");
                break;
            case 1:
                printf("\nDigite a senha: ");
                fgets(nome, TAM_VET_INFO-1, stdin);
                fila_insere(f, nome);
                break;
            case 2:   
                if(fila_retira(f) != NULL){
                    printf("\nSenha removida.\n");
                }
                break;
            case 3:
                fila_imprime(f);
                break;
            case 4:
                fila_imprime_decodificada(f);
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

    printf("\n============== CIFRA DE CESAR ==============\n\n");
    printf("[1] Inserir uma senha\n");
    printf("[2] Retirar a primeira senha\n");
    printf("[3] Imprimir as senhas\n");
    printf("[4] Imprimir as senhas descriptografadas\n");
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
void fila_insere(Fila *f, char info[]){
    Lista *novo = (Lista *) malloc(sizeof(Lista));
    int i;

    // Limpa a informação. Sem isso, fica lixo na string
    for(i = 0; i < TAM_VET_INFO; i++){
        novo->info[i] = ' ';
    }

    // Insere a senha codificada 
    for(i = 0; i < strlen(info); i++){
        if(isalnum(info[i])){
            novo->info[i] = (char)((info[i])-3);  
        }else{
            novo->info[i] = '*';
        }
    }

    // Finaliza com '\0'
    novo->info[strlen(info)] = '\0';

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
		printf("\nNenhuma senha!\n");
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
	
    printf("\n====== Lista de senhas ======\n\n");
    if(fila_vazia(f)){
		printf("Nenhuma senha!\n");
	}  
    for(aux = f->ini; aux != NULL; aux = aux->prox){
        printf("\t");
        for(int i = 0; i < strlen(aux->info); i++){
            printf("%c", aux->info[i]);
        }
        printf("\n");
    }
    printf("\n===============================\n\n");
}

/* Mostra os elementos na fila descriptografados */
void fila_imprime_decodificada(Fila *f){
   	Lista *aux;
	
    printf("\n========= Lista de senhas =========\n\n");
    if(fila_vazia(f)){
		printf("Nenhuma senha!\n");
	}  
    for(aux = f->ini; aux != NULL; aux = aux->prox){
        printf("\t");
        for(int i = 0; i < strlen(aux->info); i++){
            if(aux->info[i] == '*'){
                printf(" ");
            }else{
                printf("%c", (aux->info[i]+3));
            }
        }
        printf("\n");
    }
    printf("\n=====================================\n\n");
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
