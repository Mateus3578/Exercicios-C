#include <stdio.h>
#include <stdlib.h>
#include "pilhas.h"

/* -------- Funções de pilhas com vetor -------- */

/* Cria uma pilha (vetor). 
Não se esqueça de liberar com a função correta (vetor) */
Pilha_vet *pilha_vet_cria() {
	Pilha_vet *p = (Pilha_vet *) malloc (sizeof(Pilha_vet));
	p->n = 0;

	return p;
}

/* Inclui um elemento no topo da pilha (vetor) */
void pilha_vet_push(Pilha_vet *p, char v) {
	if (p->n == N) {
		printf("A capacidade da pilha estorou.");
		exit(1);
	}

	p->vet[p->n++] = v;
}

/* Retira o elemento no topo da pilha (vetor) */
char pilha_vet_pop(Pilha_vet *p) {
	if (pilha_vet_vazia(p)) {
		printf("Pilha vazia.");
		exit(1);
	}

	return p->vet[--p->n];
}

/* Verifica se a pilha (vetor) está vazia. 
Retorna falso (0) se possui elemento(s) ou verdadeiro (1) se vazia */
int pilha_vet_vazia(Pilha_vet *p) {
	return (p->n == 0);
}

/* Libera a pilha (vetor) */
void pilha_vet_libera(Pilha_vet *p) {
	free(p);
}

/* Imprime os elementos da pilha (vetor) */
void pilha_vet_imprime(Pilha_vet *p){
	int i;

	for(i=p->n-1;i>=0;i--){
		printf("%c\n", p->vet[i]);
	}
}

/* -------- Funções de pilhas com lista -------- */

/* Cria uma pilha (lista). 
Não se esqueça de liberar com a função correta (lista) */
Pilha_lst *pilha_lst_cria(){
	Pilha_lst *p=(Pilha_lst *)malloc(sizeof(Pilha_lst));
	p->prim=NULL;
	return p;
}

/* Inclui um elemento no topo da pilha (lista) */
void pilha_lst_push(Pilha_lst *p, char v){
	Lista *l=(Lista *)malloc(sizeof(Lista));
	l->info=v;
	l->prox=p->prim;
	p->prim=l;
}

/* Retira o elemento no topo da pilha (lista) */
char pilha_lst_pop(Pilha_lst *p){
	Lista *l;
	char c;
	if(pilha_lst_vazia(p)){
		printf("Pilha vazia\n");
		exit(1);
	}
	l=p->prim;
	c = l->info;
	p->prim = l->prox;
	free(l);
	return c;
}

/* Verifica se a pilha (lista) está vazia. 
Retorna falso (0) se possui elemento(s) ou verdadeiro (1) se vazia */
int pilha_lst_vazia(Pilha_lst *p){
	return (p->prim==NULL);
}

/* Libera a pilha (lista) */
void pilha_lst_libera(Pilha_lst *p){
	Lista *l=p->prim;
	while(l != NULL){
		Lista *t = l->prox;
		free(l);
		l=t;
	}
	free(p);
}

/* Imprime os elementos da pilha (lista) */
void pilha_lst_imprime(Pilha_lst *p){
	Lista *l;

	for(l=p->prim;l!=NULL;l=l->prox){
		printf("%c\n", l->info);
	}
}