/*
Mateus Pereira Damasceno
*/

/*
Use uma estrutura de dados do tipo PILHA para identificar se uma sequência de caracteres é um palíndromo.
Ex.: "Socorram-me, subi no ônibus em Marrocos!"
Ex.: "arara"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilhas.h"

/* Verifica se uma sequência de caracteres é um palíndromo 
(Se invertida permanece a mesma sequência)
Ex.:"Socorram-me, subi no ônibus em Marrocos" ou "arara"*/
int verificaPalindromo(char frase[]){
	Pilha_vet *p = pilha_vet_cria();
    int i;

    for(i = 0; i < strlen(frase); i++){      
        if(frase[i] != ' '){
            pilha_vet_push(p,frase[i]);
        }
    }// empilha a frase sem os espaços

    for(i = 0; i < strlen(frase); i++){
        if(frase[i] != ' ' && frase[i] != pilha_vet_pop(p)){
            return 0;
        }// compara cada caractere retirado da pilha com a frase original (sem espaço). Para na primeira diferença
    }
    return 1;
}

int main(){

	char c[200];

    printf("====== Verifique se sua frase e um palindromo! ======\n");
    printf("Nao use acentuacoes nem simbolos como hifen ou virgula\n\n");
    printf("Digite sua frase: ");
    gets(c);
    if(verificaPalindromo(c)){
        printf("\n\nA frase e um palindromo!\n\n");
    }else{
        printf("\n\nA frase nao e um palindromo :(\n\n");
    }
	return 0;
}