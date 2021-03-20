/*
Mateus Pereira Damasceno
*/

/*
Exercício 3: Dada uma lista duplamente encadeada e circular mantida ordenada:
(ou seja, o  último elemento aponta para o primeiro e vice-versa)
a) Defina os tipos necessários para representá-la.
b) Faça uma função para inserção de um elemento na lista. Lembre-se que ela deve ser mantida ordenada.
c) Faça uma função para imprimir os elementos da lista.
d) Faça uma função para liberar a lista.
*/

#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

//Para facilitar a inserção de elementos na lista
#define a 0
#define b 6
#define c -4
#define d 9
#define e 130
#define f 9

int main(){
    
    Lista_encad *lst = lst_encad_circ_cria();
    
    lst = lst_encad_circ_insere_ordenado(lst, a);
    lst_encad_circ_imprime(lst);

    lst = lst_encad_circ_insere_ordenado(lst, b);
    lst_encad_circ_imprime(lst);

    lst = lst_encad_circ_insere_ordenado(lst, c);
    lst_encad_circ_imprime(lst);

    lst = lst_encad_circ_insere_ordenado(lst, d);
    lst_encad_circ_imprime(lst);

    lst = lst_encad_circ_insere_ordenado(lst, e);
    lst_encad_circ_imprime(lst);
    
    lst = lst_encad_circ_insere_ordenado(lst, f);
    lst_encad_circ_imprime(lst);

    lst_encad_circ_libera(lst);
    return 0;
}

