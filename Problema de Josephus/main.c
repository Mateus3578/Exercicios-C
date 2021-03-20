#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

int josephus(Lista *l, int quantidade){
	Lista *p = l;
	Lista *ant = NULL;
	int i, pula = 2;

	if (quantidade < 1){
		printf("Não tem ninguem!\n\n");
		return 0;
	}
	
	while(p->prox != p){// Enquanto p nao apontar pra si mesmo (só sobrar um)
		for (i = 0; i < pula; i++){
			ant = p;
			p = p->prox;
		}// Pula a quantidade de casas até o que será eliminado (p), e armazena o anterior dele (ant)

		printf("O numero %i foi eliminado\n\n", p->info);// Diz qual será eliminado
		ant->prox = p->prox;// O ponteiro do anterior ao eliminado (ant->prox) passa a apontar para quem o eliminado apontava (p->prox)
		free(p); // o eliminado é eliminado
		p = ant->prox; // p, que aponta pra nada, passa a apontar para o elemento depois dele (p->prox, que agora é ant->prox)
	}
	
	return p->info;
}

int main(){

	Lista *rebeldes;
	int i, quantidade;
	
	printf("Quantas pessoas estao no circulo?:");
	scanf("%i", &quantidade);
	fflush(stdin);
	
	rebeldes = lst_cria();
	for(i = quantidade; i > 0; i--){
		rebeldes = lst_insere(rebeldes, i);
	}// Cria a lista numerando de 1 a quantidade escolhida
	rebeldes = lcirc_transforma(rebeldes);

	printf("\n\nFinge que isso e um circulo\n\n");
	lcirc_imprime(rebeldes);
	printf("\n\n");

    printf("Josephus e o de numero: %d\n\n", josephus(rebeldes, quantidade));
	
	free(rebeldes);
	system("pause");
	return 0;
}