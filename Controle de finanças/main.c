/*
Gerenciador de finanças

Pequeno projeto de um gerenciador de finanças feito em C, para treino da linguagem

@author Mateus Pereira Damasceno
Start at: 06/02/2021 15:59:38

*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/* Declarações */

float getSaldo();
void setSaldo();
int getId();
void setId(int novo_valor);
void registraSaldo(float novo_valor);
void registraOperacao(char tipo_op[], char descricao[]);
void incluiReceita(int saldo_atual);
void incluiDespesa(int saldo_atual);
void imprimeRegistro();
void menu();

/* main */

int main(){

    int num_menu = -1;

    while (num_menu != 0){
        menu();
        scanf("%d", &num_menu);
        switch (num_menu){
            case 0:
                printf("\nEncerrando...");
                break;
            case 1:
                printf("\nSaldo: %.2f\n\n", getSaldo());
                break;
            case 2:
                setSaldo();
                break;
            case 3:
                incluiReceita(getSaldo());
                break;
            case 4:
                incluiDespesa(getSaldo());
                break;
            case 5:
                //imprimeRegistro();
                break;
            default:
                printf("Opcao invalida.\n\n");
                break;
        }
    }

    return 0;
}

/* Funções */

/* Recupera o saldo antigo */
float getSaldo(){

    FILE *reg_saldo;
    float saldo;

    if(!(reg_saldo = fopen("reg_saldo.txt", "r"))){
        printf("Erro na leitura do saldo. \n\n Encerrando...");
        exit(1);
    }
    
    fscanf(reg_saldo, "%f", &saldo);
    
    fclose(reg_saldo);
    
    return saldo;
}

/* Função para alterar o saldo */
void setSaldo(){

    float valor;
    char descricao[50];

    printf("---- SEMPRE USE O FORMATO 3.14 E NAO 3,14 ----\n"); // dumb C -.-
    printf("Digite o novo saldo:");
    scanf("%f", &valor);
    fflush(stdin);
    printf("Digite o motivo:");
    gets(descricao);

    registraSaldo(valor);
    registraOperacao("alt_saldo", descricao);

    printf("\nSaldo alterado para %.2f\n\n", valor);

}

/* Função para salvar o saldo em um arquivo próprio */
void registraSaldo(float novo_valor){

    FILE *reg_saldo;
    char confirm;
    
    if(!(reg_saldo = fopen("reg_saldo.txt", "w"))){
        printf("Erro no registro do novo saldo.\n");     
        printf("Alteracoes NAO serao registradas.\n");
        printf("Deseja continuar? (y/n): ");
        scanf("%c", confirm);
        if(confirm == 'n'){
            exit(1);
        }else{
            return;
        }
    }

    fprintf(reg_saldo, "%f", novo_valor);
    fclose(reg_saldo);
}

/* Escreve o registro de operações no arquivo

    Registra um id de operação, data, hora e tipo.
    A variável semana (matriz de ponteiros) foi uma adaptação de um exemplo para reunir mensagens de erro.
    Por não saber se os free(s) são necessários, antes ter do que faltar.

*/
void registraOperacao(char tipo_op[], char descricao[]){
    
    FILE *log;
    char confirm;

    if(!(log = fopen("log.txt", "a"))){
        printf("Erro na abertura do log de operações.\n"); 
        printf("Alteracoes NAO serao registradas.\n");
        printf("Deseja continuar? (y/n): ");
        scanf("%c", confirm);
        if(confirm == 'n'){
            exit(1);
        }else{
            return;
        }
    }
    // Se não abrir o arquivo não precisa fazer mais nada. Agora começa a função

    struct tm *p;
    time_t seg;
    int id_op = getId();
    char *semana[] = {
        "dom",  // 0
        "seg",  // 1
        "ter",  // 2
        "qua",  // 3
        "qui",  // 4
        "sex",  // 5
        "sab"   // 6
    };

    time(&seg);
    p = localtime(&seg);

    id_op++;

    fprintf(log, "%d\t", id_op);
    fprintf(log, "%s\t", semana[p->tm_wday]);
    fprintf(log, "%d-%d-%d at ", p->tm_mday, p->tm_mon +1, p->tm_year +1900);
    fprintf(log, "%d:%d:%d\t", p->tm_hour, p->tm_min, p->tm_sec);
    fprintf(log, "%s\t", tipo_op);
    fprintf(log, "%s\n", descricao);

    

    free(p);
    fclose(log);

}

/* Menu do programa (Apenas printf) */
void menu(){
    
    printf("---- Menu ----\n");

    printf("[1]: Mostrar saldo\n");
    printf("[2]: Alterar saldo\n");
    printf("[3]: Incluir receita\n");
    printf("[4]: Incluir despesa\n");
    printf("[5]: Ver registro de operacoes\n");
    printf("[0]: Sair\n");
    
    printf("--------------\n");

    printf("Opcao:");

}

/* Inclui uma receita, alterando o saldo e registrando a operação */
void incluiReceita(int saldo_atual){

    float receita;
    char descricao[50];
    
    printf("---- SEMPRE USE O FORMATO 3.14 E NAO 3,14 ----\n"); // dumb C -.-
    printf("Digite o valor da receita:");
    scanf("%f", &receita);
    fflush(stdin);
    printf("Digite a descricao da receita:");
    gets(descricao);

    registraSaldo(saldo_atual + receita);
    registraOperacao("receita", descricao);

    printf("\nReceita incluida com sucesso.\n\n");

}

/* Inclui uma despesa, alterando o saldo e registrando a operação
    Porque isso não está junto da função de receira se a única diferença é a operação com o saldo?
 */
void incluiDespesa(int saldo_atual){

    float despesa;
    char descricao[50];
    
    printf("---- SEMPRE USE O FORMATO 3.14 E NAO 3,14 ----\n"); // dumb C -.-
    printf("Digite o valor da despesa:");
    scanf("%f", &despesa);
    fflush(stdin);
    printf("Digite a descricao da despesa:");
    gets(descricao);

    registraSaldo(saldo_atual - despesa);
    registraOperacao("despesa", descricao);

    printf("\nDespesa incluida com sucesso.\n\n");

}

int getId(){

    FILE *reg_id;
    float id;

    if(!(reg_id = fopen("reg_id.txt", "r"))){
        printf("Erro na leitura do log(id). \n\n Encerrando...");
        exit(1);
    }
    
    fscanf(reg_id, "%d", &id);
    
    fclose(reg_id);
    
    return id;

}

void setId(int novo_valor){

    FILE *reg_id;
    char confirm;
    
    if(!(reg_id = fopen("reg_id.txt", "w"))){
        printf("Erro no registro do log(id).\n");     
        printf("Alteracoes NAO serao registradas.\n");
        printf("Deseja continuar? (y/n): ");
        scanf("%c", confirm);
        if(confirm == 'n'){
            exit(1);
        }else{
            return;
        }
    }

    fprintf(reg_id, "%f", novo_valor);
    fclose(reg_id);
}

void imprimeRegistro(){

    FILE *log;
    char confirm, aux;

    if(!(log = fopen("log.txt", "a"))){
        printf("Erro na abertura do log de operações.\n"); 
        printf("Alteracoes NAO serao registradas.\n");
        printf("Deseja continuar? (y/n): ");
        scanf("%c", confirm);
        if(confirm == 'n'){
            exit(1);
        }else{
            return;
        }
    }
    
    while(!feof(log))
    {
        aux = fgetc(log);
        printf("%c", aux);
    }

}