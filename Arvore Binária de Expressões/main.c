/* Mateus Pereira Damasceno */

/*
2) Escreva um algoritmo que receba uma expressão matemática (composta por operandos compostos por
um único algarismo, operações de +, -, * e /) representada por um string e retorne uma árvore binária
representando esta expressão.
Dada essa árvore binária, construa um algoritmo que apresente a versão infixa (ou central) da expressão e
a versão pós-fixa (ou pós-ordem) da expressão em um arquivo texto.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arvore.h"
#define TAM_STRING 30

int main(){
    Tree *arvore = cria_vazia();
    char *expressao = (char*) malloc (TAM_STRING * sizeof(char));

    printf("Digite uma expressao posfixa/polonesa: ");
    fgets(expressao, TAM_STRING, stdin);
    arvore = insere_expressao(arvore, expressao);

    printf("\nPos-fixa:\n");
    imprime_pos(arvore);
    printf("\nInfixa:");
    imprime_sim(arvore);

    FILE *arquivo;   
    if(!(arquivo = fopen("expressao.txt", "w"))){
        printf("\nErro ao salvar os dados.\n\nEncerrando...\n");     
        exit(1);
    }
    escreveNoArquivoTextoInfixa(arvore, arquivo);
    fprintf(arquivo, "\n");
    escreveNoArquivoTextoPosfixa(arvore, arquivo);
    fprintf(arquivo, "\n");
    fclose(arquivo);
    libera(arvore);

    return 0;
}

