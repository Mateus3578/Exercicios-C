/*
Mateus Pereira Damasceno
*/
/*
Faça um programa para determinar se a sequência de parênteses
e colchetes está bem formada (ou seja, parênteses e colchetes são
fechados na ordem inversa àquela em que foram abertos).
*/

#include <stdio.h>
#include <stdlib.h>
#include "pilhas.h"

/* Verifica se a sequência de parênteses e colchetes de uma expressão está bem formada 
(ou seja, parênteses e colchetes são fechados na ordem inversa àquela em que foram abertos).*/
int verificaExpressao(char expressao[]){
	Pilha_vet *parentese = pilha_vet_cria();
    Pilha_vet *colchete = pilha_vet_cria();
    int i;
    
    for(i = 0; expressao[i] != '\0'; i++){       

/*----------------Teste de parênteses----------------*/

        if(expressao[i] == '('){
            pilha_vet_push(parentese, expressao[i]);
        }

        if(expressao[i] == ')'){
            if(pilha_vet_vazia(parentese)){
                pilha_vet_libera(parentese);
                pilha_vet_libera(colchete);
                return 0;
            }
            pilha_vet_pop(parentese);
        }

/*----------------Teste de colchetes----------------*/

        if(expressao[i] == '['){
            pilha_vet_push(colchete, expressao[i]);
        }

        if(expressao[i] == ']'){
            if(pilha_vet_vazia(colchete)){
                pilha_vet_libera(parentese);
                pilha_vet_libera(colchete);
                return 0;
            }
            pilha_vet_pop(colchete);
        }      
    }
/*--------------------Teste final-------------------*/

    if(pilha_vet_vazia(parentese) && pilha_vet_vazia(colchete)){
        pilha_vet_libera(parentese);
        pilha_vet_libera(colchete);	
        return 1;
    }else{
        pilha_vet_libera(parentese);
        pilha_vet_libera(colchete);	
        return 0;
    }
}	

int main(){

	char c[200];

	while (c[0] != 'q'){
        printf("====== Verifique se sua expressao matematica esta bem formada ======\n");
        printf("Digite uma expressao ou \"q\" para sair: ");
	    gets(c);
        if(c[0] == 'q'){
        break;
        }
        if(verificaExpressao(c)){
            printf("\nSua expressao foi digitada corretamente. Parabens!\n\n");
        }else{
            printf("Sua expressao nao foi digitada corretamente.\n\n");
        }
    }        
	return 0;
}