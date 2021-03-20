#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

/* -------- Funções de listas encadeadas -------- */

/* Cria uma lista encadeada */
Lista *lst_cria(){
	return NULL; // lista vazia = null
}

/* Insere um elemento no início de uma lista encadeada */
Lista *lst_insere(Lista *l, int v){
	Lista *novo = (Lista *) malloc (sizeof(Lista)); // auxiliar
	
	novo->info = v; // auxiliar recebe o valor
	novo->prox = l; // auxiliar entra na frente do primeiro da lista
	return novo;
}

/* Insere um elemento no fim de uma lista encadeada */
Lista *lst_insere_fim(Lista *l, int v){
	Lista *novo = (Lista *) malloc (sizeof(Lista)); // auxiliar

    if(lst_vazia(l)){
		novo->info = v; // auxiliar recebe o valor
		novo->prox = NULL; // novo é o ultimo, o prox é null
		return novo;

	}else{
		Lista *p = l;
		while(p->prox != NULL){
		p = p->prox;
		} // Vai até o final. Se só tiver um nem entra no while
		
		novo->info = v;// auxiliar recebe o valor
		p->prox = novo; // antigo último aponta para o novo
		novo->prox = NULL; // novo é o ultimo, o prox é null
		return l;
		}
	}

/* Imprime os elementos de uma lista encadeada */
void lst_imprime(Lista *l){
	Lista *p; // p recebe a lista
	
	for(p = l; p != NULL; p = p->prox){
		printf("Valor: %d\n", p->info);
	}
}

/* Verifica se uma lista encadeada está vazia. 
Retorna verdadeiro(1) se estiver vazia ou falso(0) se tiver algum elemento */
int lst_vazia(Lista *l){
	if(l == NULL){
		return 1;
	}else{
		return 0;
	}// Está vazia? Sim ou não
}

/* Busca um elemento em uma lista encadeada */
Lista *lst_busca(Lista *l, int v){
	Lista *p; // p recebe a lista
	
	for(p = l; p != NULL; p = p->prox){
		if(p->info == v){
			return p; // vai até onde o elemento está e retorna onde ele está
		}
	}

	if(p == NULL){
		printf("Elemento não encontrado\n"); // ou lista vazia
		return NULL;
	}
}

/* Retira um elemento de uma lista encadeada */
Lista *lst_retira(Lista *l, int v){
	Lista *p = l; // p recebe a lista
	Lista *ant = NULL; // auxiliar para guardar o anterior de p (lista)
	
	while(p != NULL && p->info != v){
		ant = p;
		p = p->prox;
	} // Percorre a lista até achar o elemento

	if(p == NULL){
		printf("Elemento não encontrado\n"); // ou lista vazia
		return l;
	}

	if(ant == NULL){
		l = p->prox; // caso seja o primeiro elemento
	}
	else{
		ant->prox = p->prox; 
		// o ponteiro que aponta para o elemento que será removido passa a apontar 
		// para o ponteiro que aponta para o elemento depois do que será removido
	}
	
	free(p);
	return l;
}

/* Libera uma lista encadeada */
void lst_libera(Lista *l){
	Lista *p = l; // p recebe a lista
	
	while(p != NULL){
		Lista *t = p->prox; // auxiliar para guardar o próximo elemento para ele não ir embora com o p
		free(p);
		p = t; // p vira o elemento depois dele
	}
}

/* Insere um elemento em ordem crescente em uma lista encadeada */
Lista *lst_insere_ordenado(Lista *l, int v){
	Lista *novo = (Lista *) malloc (sizeof(Lista));
	novo->info = v;// auxiliar recebe o elemento inserido
	
	Lista *ant = NULL; //auxiliar para lembrar o anterior
	Lista *p = l; // p recebe a lista
	
	while(p != NULL && p->info < v){
		ant = p;
		p = p->prox;
	}// percorre até achar onde inserir

	if(ant == NULL){
		novo->prox = l;
		return novo;
	}// se for no começo
	else{
		ant->prox = novo;
		novo->prox = p;
		return l;
	} // encaixa o elemento onde ele deve estar
}

/* Verifica se duas listas encadeadas são iguais (mesmo tamanho e conteúdo).
	Compara o tamanho e depois cada elemento.
	Retorna falso(0) se diferentes e verdadeiro(1) se iguais */
int lst_igual(Lista *l1, Lista *l2){
	Lista *p1;
	Lista *p2;
	int tam1 = 0, tam2 = 0;
	
	for(p1 = l1; p1 != NULL; p1 = p1->prox){
		tam1++;
	}
	for(p2 = l2; p2 != NULL; p2 = p2->prox){
		tam2++;
	}// conta quantos elementos em cada lista
	
	p1 = l1;
	p2 = l2;

	if(tam1 != tam2){
		return 0;
	}// tamanhos diferentes == listas diferentes
	else{
		while(p1 != NULL){
			if(p1->info == p2->info){
				p1 = p1->prox;
				p2 = p2->prox;
			}// compara cada elemento
			else{
				return 0;
			}
		}
	}
	return 1;
}

/* Intercala duas listas (l1, l2, l1->prox, l2->prox etc) */
Lista *lst_intercala(Lista *l1, Lista *l2){
 	Lista *p1 = l1; // recebe lista 1 para manter ela sem alterações
	Lista *p2 = l2; // recebe lista 2 para manter ela sem alterações
	Lista *intercalada = lst_cria(); // lista intercalada

	while(p1 != NULL || p2 != NULL){
		if(p1 != NULL){
			intercalada = lst_insere_fim(intercalada, p1->info);
			p1 = p1->prox;
		}
		if(p2 != NULL){
			intercalada = lst_insere_fim(intercalada, p2->info);
			p2 = p2->prox;
		}
	}
	/*
	Enquanto pelo menos uma lista tiver elementos(ao menos uma nao for null), o while continua.
	Se p1 tiver um elemento, ele é inserido no final e p1 vira seu próximo elemento. O mesmo para p2.
	Quando uma lista acabar (p1 ou p2), continua inserindo da que ainda tem.  
	*/
	
	return intercalada;
}

/* -------- Funções recursivas de listas encadeadas -------- */

/* Imprime uma lista encadeada (função recursiva) */
void lst_imprime_rec(Lista *l){
    Lista *p = l; // p recebe a lista
    
    if(p != NULL){
        printf("Valor: %d\n", p->info); // se existe alguém, imprime sua informação
        lst_imprime_rec(p->prox); // se existe próximo, repete
    }
}

/* Retira um elemento de uma lista encadeada (função recursiva) */
Lista *lst_retira_rec(Lista *l, int v){
	Lista *p = l;
	
	if(p == NULL){
		printf("Elemento não encontrado\n");
		return l;
	}
	
	if(p->info == v){
		l = p->prox;
		free(p);
		return l;
	}// se achar, l vira o próximo, o elemento é removido e l(elemento->prox) e é retornado

	p->prox = lst_retira_rec(p->prox, v);
	return p;// se não cair no if, continua procurando com o proximo mantendo a lista
}

/* Libera uma lista encadeada (função recursiva) */
void lst_libera_rec(Lista *l){
    Lista *p = l; // p recebe a lista
	
	if(p == NULL){
		free(p); // Se p é nulo a lista não tem mais nada
	}else{
        Lista *t = p->prox; // t(temporário) recebe o próximo elemento
		free(p); // p é liberado
        lst_libera_rec(t); // continua com t(p->prox)
    }
}

/* -------- Funções de listas circulares -------- */

/* Imprime os elementos de uma lista circular */
void lcirc_imprime(Lista *l){
	Lista *p = l;
	
	if(p){
		do{
			printf("%d ", p->info);
			p = p->prox;
		} while(p != l);
	}
	printf("\n");
}

/* Converte uma lista encadeada em uma lista encadeada circular */
Lista *lcirc_transforma(Lista *l){
	Lista *p = l;
	
	while(p->prox != NULL){
		p = p->prox;
	}

	if(l == NULL){
		return l;
	}
	else{
		p->prox = l;
		return l;
	}
}

/* Libera uma lista encadeada circular */
void lcirc_libera(Lista *l){
	Lista *p = l;
	do{
		Lista *t = p->prox;
		free(p);
		p = t;
	} while(p != l);
}

/* Busca um elemento em uma lista encadeada circular */
Lista *lcirc_busca(Lista *l, int v){
	Lista *p = l;
	do{
		if(p->info == v){
			return p;
		}
		else{
			p = p->prox;
		}
	} while(p != l);

	if(p == l){
		printf("Elemento não encontrado\n");
		return NULL;
	}
}

/* -------- Funções de listas duplamente encadeadas -------- */

/* Insere um elemento em uma lista duplamente encadeada */
Lista_encad *lst_encad_insere(Lista_encad *l, int v){
	Lista_encad *novo = (Lista_encad *)malloc(sizeof(Lista_encad));
	novo->prox = l;
	novo->ant = NULL;
	novo->info = v;
	if(l != NULL){
		l->ant = novo;
	}
	return novo;
}

/* Busca um elemento em uma lista duplamente encadeada */
Lista_encad *lst_encad_busca(Lista_encad *l, int v){
	Lista_encad *p;
	
	for(p = l; p != NULL; p = p->prox){
		if(p->info == v){
			return p;
		}
	}
	return NULL;
}

/* Retira um elemento em uma lista duplamente encadeada */
Lista_encad *lst_encad_retira(Lista_encad *l, int v){
	Lista_encad *p;
	
	p = lst_encad_busca(l, v);

	if(p->ant == NULL){
		l=p->prox;
	}
	else if(p->prox == NULL){
		p->ant->prox = NULL;
	}
	else if(p == NULL){
		printf("Elemento não encontrado\n");
	}
	else{
		p->ant->prox = p->prox;
	}
	return l;
}

/* -------- Funções de listas duplamente encadeadas circulares -------- */

/* Cria uma lista duplamente encadeada circular */
Lista_encad *lst_encad_circ_cria(){
	Lista_encad *novo = (Lista_encad *) malloc (sizeof(Lista_encad));
	novo = novo->ant = novo->prox = NULL;
	return novo; // lista vazia == tudo null
}

/* Insere um elemento em ordem crescente em uma lista duplamente encadeada circular */
Lista_encad* lst_encad_circ_insere_ordenado(Lista_encad *l, int v){
	Lista_encad *p = l; // p recebe a lista
	Lista_encad *novo = (Lista_encad *) malloc (sizeof(Lista_encad));
	novo->info = v;// auxiliar recebe o elemento inserido
	
	// Caso 1: nada na lista. O elemento é o seu anterior e o seu próximo
	if(p == NULL){
		novo->prox = novo->ant = novo;
		return novo;
	}

	// percorre até achar onde inserir(até um maior ou até o final)
	while(p->info < v && p->prox != l){
		p = p->prox;
	}
	
	// Caso 2: número v é maior que todos. O fim da lista foi alcançado, portanto p virou o último elemento (p->prox = início).
	if(p->info < v && p->prox == l){
		p->prox->ant = novo;	// o *ant do primeiro aponta para o novo último(novo)
		p->prox = novo;			// o *prox do último aponta para o novo último
		novo->prox = l;			// o *prox novo último aponta para o primeiro da lista
		novo->ant = p;			// o *ant do novo último aponta para o antigo último(p)
		return l;				// retorna o primeiro da lista
	}
	
	// Caso 3: número v é menor que todos ou igual ao primeiro(menor da lista), portanto p não saiu do primeiro elemento (p == l)
	else if(p->info >= v && p == l){
		novo->ant = p->ant;		// o *ant do novo elemento aponta para o último da lista
		p->ant->prox = novo;	// o *prox do último da lista aponta para o novo elemento
		novo->prox = l;			// o *prox do novo aponta para o início da lista
		novo->prox->ant = novo;	// o *ant do antigo início da fila (l->ant) passa a apontar para o novo
		return novo;			// retorna o novo primeiro da lista
		}
	
	// Caso 4: número v entre 2 números, portanto p parou no primeiro maior que v
	else{
		novo->prox = p;			// o *prox do novo aponta para o maior ou igual a ele
		p->ant->prox = novo;	// o *prox do anterior a p passa a apontar para o novo (lembrando: p > novo)
		novo->ant = p->ant;		// o *ant do novo elemento aponta para o anterior a p
		p->ant = novo;			// o *ant de p agora é o novo elemento
		return l;				// retorna o primeiro da lista
	}
}

/* Imprime os elementos de uma lista duplamente encadeada circular */
void lst_encad_circ_imprime(Lista_encad *l){
	Lista_encad *p = l;
	
	if(p){
		printf("\ninfo\tant\tprox\n");
		do{
			printf("%d\t%d\t%d\n", p->info, p->ant->info, p->prox->info);
			p = p->prox;
		} while(p != l);
	}
	printf("\n");

}

/* Libera uma lista duplamente encadeada circular */
void lst_encad_circ_libera(Lista_encad *l){
	Lista_encad *p = l;
	do{
		Lista_encad *t = p->prox;
		free(p);
		p = t;
	} while(p != l);
}
