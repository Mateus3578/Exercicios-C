/*
Mateus Pereira Damasceno
*/

/*
A fila de prioridade nada mais é que uma fila comum que
permite que elementos sejam adicionados associados com uma
prioridade. Cada elemento na fila deve possuir um dado adicional
que representa sua prioridade de atendimento. Uma regra explicita
define que o elemento de maior prioridade (o que tem o maior
número associado) deve ser o primeiro a ser removido da fila,
quando uma remoção é requerida.

Dada a definição de fila de prioridade, altere o exercício do
estacionamento(ex. 8) para que carros de idosos sejam sempre colocados
para sair primeiro. Idosos são pessoas acima de 60 anos. Caso o
primeiro da fila já seja um idoso, o idoso mais velho passa a frente.
Armazene o estado do estacionamento em um arquivo texto.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct carro{
	char info[8];
    int idade;
	struct carro *prox;
}Carro;

typedef struct vaga{
	Carro *ini;
	Carro *fim;
}Fila;

void menu();
Fila *criaFila();
void insereCarro(Fila *f, char placa[], int idade);
char *removeCarro(Fila *f, char placa[]);
void imprimeCarros(Fila *f);
int filaVazia(Fila *f);
void encerraExpediente(Fila *f, char nome_arquivo[]);
void recuperaDados(Fila *f, char nome_arquivo[]);

int main(){

    Fila *normal = criaFila();
    Fila *prioridade = criaFila();
    char placa[8]; // ABC1234 + /0 = 8
    int opcao, idade;

    recuperaDados(normal, "mem_normal.txt");
    recuperaDados(prioridade, "mem_prioridade.txt");

/*
    insereCarro(normal, "aaa", 55);
    insereCarro(normal, "bbb", 22);
    insereCarro(normal, "ccc", 30);
    insereCarro(normal, "ddd", 48);
    insereCarro(normal, "eee", 11);
    
    insereCarro(prioridade, "AAA1111", 61);
    insereCarro(prioridade, "BBB2222", 86);
    insereCarro(prioridade, "CCC3333", 70);
*/
    do{      
        menu();
        scanf("%d", &opcao);
        fflush(stdin);
        switch (opcao){
            case 0:
                printf("\nEncerrando...\n");
                break;
            case 1:
                printf("\nInserindo carro:\nDigite a placa do carro (Ex.: AAA1234): ");
                gets(placa);
                printf("\nDigite a idade do motorista: ");
                scanf("%d", &idade);
                fflush(stdin);
                if(idade > 60){
                    insereCarro(prioridade, placa, idade);
                }else{
                    insereCarro(normal, placa, idade);
                }
                break;
            case 2:
                printf("\nRemovendo carro:\nDigite a placa do carro (Ex.: AAA1234): ");
                gets(placa);
                printf("\nDigite a idade do motorista: ");
                scanf("%d", &idade);
                fflush(stdin);
                if(idade > 60){
                    removeCarro(prioridade, placa);
                }else{
                    removeCarro(normal, placa);
                }                
                break;
            case 3:
                printf("\n==== Lista de veiculos ====\n\n");
                imprimeCarros(prioridade);
                imprimeCarros(normal);
                printf("\n===========================\n\n");
                break;       
            default:
                printf("Opcao invalida\n");
                break;
        }
    }while(opcao != 0);
    
    encerraExpediente(normal, "mem_normal.txt");
    encerraExpediente(prioridade, "mem_prioridade.txt");
    return 0;
}

void menu(){
    
    printf("\n============ Estacionamento ============\n\n");
    printf("Digite [1] para inserir um carro\n");
    printf("Digite [2] para retirar um carro\n");
    printf("Digite [3] para mostrar os carros estacionados\n");
    printf("Digite [0] para sair\n");
    printf("Opcao: ");

}

/* Cria uma fila */
Fila *criaFila(){
	Fila *f = (Fila *) malloc(sizeof(Fila));
	f->ini = f->fim = NULL;
	return f;
}

/* Insere um carro no final da fila */
void insereCarro(Fila *f, char placa[], int idade){
    Carro *novo = (Carro *) malloc(sizeof(Carro));
	int i;
	
    novo->idade = idade;
    for(i = 0; i < 8; i++){
        novo->info[i] = placa[i];
    }// Escreve a placa na info do novo carro
	
    novo->prox = NULL; // o novo carro é o último da fila, não tem nada depois dele

	if(f->fim != NULL){
        f->fim->prox = novo; // Se existe alguém no fim, então o novo passa a ser o final
    }
	else{
        f->ini = novo;// Se for o primeiro carro, ele é o primeiro e o último
    }

	f->fim = novo; // registra que o novo carro é o último da fila 
}

/* Remove o carro escolhido. Se não achar, não faz nada */
char *removeCarro(Fila *f, char placa[]){
	if(filaVazia(f)){
		printf("Estacionamento vazio!");
		return f->ini->info;
	}// Se tiver vazio não faz nada

    Carro *aux;
	char *v, *primeiro;

    primeiro = f->ini->info;// guarda o primeiro para evitar um while infinito

    if(f->fim->info == primeiro){
        f->ini = f->fim = NULL;
        printf("\nCarro %s liberado.\n", placa);
        free(aux);
        return f->ini->info;
    }

	do{
        aux = f->ini; // aux guarda o início da fila
	    v = aux->info; // v guarda a placa
	    if(strcmp(v, placa) != 0){
            insereCarro(f, v, aux->idade);
            f->ini = aux->prox; // o início vira o segundo carro
        }
        else{
            f->ini = aux->prox;
        }
    }while(strcmp(v, placa) != 0 && strcmp(f->ini->info, primeiro) != 0);
    /*  Faz uma rotação procurando o carro. 
        Enquanto não acha, coloca o primeiro no final e ve o próximo
        Assim que achar, para a rotação
        Se voltar no primeiro e não achou para a rotação também */
    
    if(strcmp(f->ini->info, primeiro) == 0){
        printf("\nCarro nao encontrado.\n");
        free(aux);
        return primeiro;
    }// se o carro não estiver na fila, devolve a fila "sem alterações"
    else{
        printf("\nCarro %s liberado.\n", placa);
        free(aux);
        return v;
    }
}

/* Mostra os carros na fila */
void imprimeCarros(Fila *f){
	Carro *q;
	
    for(q = f->ini; q != NULL; q = q->prox){
        printf("\t%s - %d\n", q->info, q->idade);
    }
}

/* Retorna 1 se a fila estiver vazia, caso contrário retorna 0 */
int filaVazia(Fila *f){
	return (f->ini == NULL);
}

/* Função de nome curioso que salva o estado atual do estacionamento e libera a fila */
void encerraExpediente(Fila *f, char nome_arquivo[]){
	Carro *q = f->ini;
    FILE *arquivo;
    
    if(!(arquivo = fopen(nome_arquivo, "w"))){
        printf("\nErro ao salvar os dados.\n\nEncerrando...\n");     
        exit(1);
    }// abre o arquivo para salvar os dados
	
    fprintf(arquivo, "\n"); // quebra de linha para a leitura do arquivo
    while(q != NULL){
        fprintf(arquivo, "%s\n", q->info);
        fprintf(arquivo, "%d", q->idade);
        if(q->prox != NULL){
            fprintf(arquivo, "\n");// só coloca a quebra de linha se ainda tiver dados para escrever
        }
        Carro *t = q->prox;
		free(q);
		q = t;
    }

    fclose(arquivo);
	free(f);
}

/* Recupera as informações do estacionamento */
void recuperaDados(Fila *f, char nome_arquivo[]){
    
    FILE *arquivo;
    char placa[8], aux[13];
    int idade;

    if(!(arquivo = fopen(nome_arquivo, "r"))){
        printf("\nErro na recuperacao dos dados.\n\nEncerrando...\n");
        exit(1);
    }// abre o arquivo para salvar os dados

    while(fgets(aux, 13, arquivo)){
        fscanf(arquivo, "%s", &placa);
        fscanf(arquivo, "%d", &idade);
        insereCarro(f, placa, idade);
    }// lê a placa e a idade do motorista salvos no arquivo

    fclose(arquivo);

}