/* Mateus Pereira Damasceno */

/* 
1. Implemente os três tipos de percurso em árvores binárias.

2. Implemente uma inserção em árvore binária onde elementos menores que a raiz 
ficam à esquerda e elementos maiores que a raiz ficam à direita.

3. Dada uma árvore binária, faça uma função para contar o número de folhas, 
o número de nós com um filho e o número de nós com dois filhos.

4. Considere uma árvore binária, faça uma função que monte um histograma de ocorrência 
dos caracteres que aparecem na árvore.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvore.h"

int main(){

    Tree *arvore = cria_vazia();

    arvore = insere_ordenado(arvore, 'A');
    arvore = insere_ordenado(arvore, 'b');
    arvore = insere_ordenado(arvore, 'A');
    arvore = insere_ordenado(arvore, 'A');
    arvore = insere_ordenado(arvore, 'b');
    arvore = insere_ordenado(arvore, '+');
    arvore = insere_ordenado(arvore, '-');
    arvore = insere_ordenado(arvore, '-');
    arvore = insere_ordenado(arvore, '+');
    arvore = insere_ordenado(arvore, '+');
    arvore = insere_ordenado(arvore, '/');

    printf("\n\nImpressao pre-ordem: ");
    imprime_pre(arvore);
    printf("\n\nImpressao pos-ordem: ");
    imprime_pos(arvore);
    printf("\n\nImpressao ordem simetrica: ");
    imprime_sim(arvore);

    printf("\n\nNumero de folhas: %d", conta_folhas(arvore));
    printf("\nNumero de nos com um filho: %d", conta_nos_umFilho(arvore));
    printf("\nNumero de nos com dois filhos: %d", conta_nos_doisFilhos(arvore));
    printf("\nNumero total de nos: %d", conta_nos(arvore));

    printf("\n\n");
    histograma(arvore);
    
    arvore = libera(arvore);
    return 0;
}

