#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvore.h"

/* Cria uma árvore binária vazia (return NULL) */
Tree *cria_vazia(){
    return NULL;
}

/* Cria uma árvore binária com algum conteúdo (não-vazia) */
Tree *cria(char informacao, Tree *galho_esquerda, Tree *galho_direita){
    Tree *p = (Tree*) malloc (sizeof(Tree));

    p->info = informacao;
    p->esq = galho_esquerda;
    p->dir = galho_direita;
    return p;
}

/* Verifica se uma árvore binária está vazia:
    Retorna 0 se possui alguma coisa
    Retorna 1 se vazia */
int vazia(Tree *arvore){
    return arvore == NULL;
}

/* Imprime os elementos de uma árvore binária. 
    Versão pré-ordem (raiz, esquerda, direita) */
void imprime_pre(Tree *arvore){
    if(!vazia(arvore)){
        printf("%c ", arvore->info);
        imprime_pre(arvore->esq);
        imprime_pre(arvore->dir);
    }
}

/* Imprime os elementos de uma árvore binária. 
    Versão simétrica (esquerda, raiz, direita) */
void imprime_sim(Tree *arvore){
    if(!vazia(arvore)){
        imprime_sim(arvore->esq);
        printf("%c ", arvore->info);
        imprime_sim(arvore->dir);
    }
}

/* Imprime os elementos de uma árvore binária. 
    Versão pós-ordem (esquerda, direita, raiz) */
void imprime_pos(Tree *arvore){
    if(!vazia(arvore)){
        imprime_pos(arvore->esq);
        imprime_pos(arvore->dir);
        printf("%c ", arvore->info);
    }
}

/* Libera uma árvore binária */
Tree *libera(Tree *arvore){
    if(!vazia(arvore)){
        libera(arvore->esq);
        libera(arvore->dir);
        free(arvore);
    }
    return NULL;
}

/* Verifica se um elemento pertence a uma árvore binária */
int pertence(Tree *arvore, char elemento){
    if(vazia(arvore)){
        return 0; // se ta vazia não tem elemento!
    }
    else{
        return arvore->info == elemento ||
                pertence(arvore->esq, elemento) ||
                pertence(arvore->dir, elemento);
        // Verifica se o elemento está na raiz, na esquerda ou na direita
    }
}

/* Verifica qual o maior número entre dois inteiros "a" e "b". */
static int comparaMaior(int a, int b){
    if (a > b){
        return a;
    }else{
        return b;
    }
    // serve também return (a > b) ? a : b;
}

/* Retorna a altura de uma árvore binária */
int altura(Tree *arvore){
    if(vazia(arvore)){
        return -1; // Por que verificar a altura de uma árvore vazia?
    }else{
        return 1 + comparaMaior(altura(arvore->esq), altura(arvore->esq));
        /* recursão que compara o tamanho dos lados. 
        A cada galho, soma-se 1 e verifica com o próximo.
        Quando não for mais possível (esq ou dir == NULL), se obtem o tamanho de um lado.
        Os tamanhos são comparados usando a função comparaMaior(), onde o que importa é o maior lado.
        */
    }
}

/* Insere um elemento na árvore binária, onde elementos menores que a raiz ficam à esquerda e elementos maiores que a raiz ficam à direita. */
Tree *insere_ordenado(Tree *arvore, char informacao){
    if(vazia(arvore)){
        arvore = (Tree*)malloc(sizeof(Tree));
        arvore->info = informacao;
        arvore->esq = arvore->dir = NULL;
    }
    else if(informacao < arvore->info){
        arvore->esq = insere_ordenado(arvore->esq, informacao);
    }
    else{
        arvore->dir = insere_ordenado(arvore->dir, informacao);
    }
    return arvore;
}

/* Retorna o número total de nós de uma árvore binária */
int conta_nos(Tree *arvore){
   if(vazia(arvore)){
        return 0;
    }
    else{
        return 1 + conta_nos(arvore->esq) + conta_nos(arvore->dir);
    }
}

/* Retorna o número de folhas (nós sem filho) de uma árvore binária */
int conta_folhas(Tree *arvore){
    if(vazia(arvore)){
        return 0;
    }
    else if(vazia(arvore->esq) && vazia(arvore->dir)){
        return 1;
    }
    else{
        return conta_folhas(arvore->esq) + conta_folhas(arvore->dir);
    }
}

/* Retorna o número de nós com um filho de uma árvore binária */
int conta_nos_umFilho(Tree *arvore){
    if(vazia(arvore)){
        return 0;
    }    
    else if((vazia(arvore->esq) || vazia(arvore->dir))){
        return 1 + conta_nos_umFilho(arvore->esq) + conta_nos_umFilho(arvore->dir);
    }
    else{
        return conta_nos_umFilho(arvore->esq) + conta_nos_umFilho(arvore->dir);
    }

}

/* Retorna o número de nós com dois filhos de uma árvore binária */
int conta_nos_doisFilhos(Tree *arvore){
   if(vazia(arvore)){
        return 0;
    }
    else if(arvore->esq != NULL && arvore->dir != NULL){
        return 1 + conta_nos_doisFilhos(arvore->esq) + conta_nos_doisFilhos(arvore->dir);
    }
    else{
        return 0;
    }
}

/* Conta quantas vezes cada elemento se repete em uma árvore binária.
    Aceita somente letras minúsculas. */
void histograma(Tree *arvore){
    int tam_vet = 96; //número mágico. Basicamente é a quantidade de elementos que podem ser impressos da tabela ASCII
    
    int *repeticoes = (int*)calloc(tam_vet, sizeof(int));       
    char *caracteres = (char*)calloc(tam_vet, sizeof(char));// Inicializa os vetores
    
    conta_repeticoes(arvore, repeticoes);
    tree_to_array(arvore, caracteres);  // Escreve nos vetores
    
    printf("==== HISTOGRAMA ====\n\n");

    for(int i = 0; i < tam_vet; i++){
        if(repeticoes[i] != 0){
            printf("%c: ", caracteres[i]);
            printf("%d vezes\t", repeticoes[i]);
            for(int j = 0; j < repeticoes[i]; j++){
                printf("|");
            }
            printf("\n");
        }
    }

    free(repeticoes);
    free(caracteres);
}

/* Conta quantas vezes um elemento se repete em uma árvore binária, e escreve no vetor informado.
    
    O VETOR DEVE POSSUIR TAMANHO 96 E TODOS OS ELEMENTOS DEVEM SER 0 (zero). */
void conta_repeticoes(Tree *arvore, int *vetor){
    if(!vazia(arvore)){
        vetor[arvore->info - 32]++;// 32 é o número de elementos que não podem ser impressos da tabela ASCII (0 a 31)
        conta_repeticoes(arvore->esq, vetor);
        conta_repeticoes(arvore->dir, vetor);
    }
}

/* Copia os elementos de árvore binária para o vetor informado.
    
    O VETOR DEVE POSSUIR TAMANHO 96 PARA RECEBER QUALQUER ELEMENTO DA TABELA ASCII */
void tree_to_array(Tree *arvore, char *vetor){
    if(!vazia(arvore)){
        vetor[arvore->info - 32] = arvore->info;// 32 é o número de elementos que não podem ser impressos da tabela ASCII (0 a 31)
        tree_to_array(arvore->esq, vetor);
        tree_to_array(arvore->dir, vetor);
    }
}
