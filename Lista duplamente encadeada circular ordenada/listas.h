/* Lista encadeada */
typedef struct lista{
	int info; 					// Elemento da lista
	struct lista *prox; 		// Próximo elemento
}Lista;


/* Lista duplamente encadeada */
typedef struct lista_encad{
	int info; 					// Elemento da lista
	struct lista_encad *ant; 	// Elemento anterior
	struct lista_encad *prox; 	// Próximo elemento
}Lista_encad;

/* Funções de lista encadeada */

Lista* lst_cria();
Lista* lst_insere(Lista *l, int v);
Lista* lst_insere_fim(Lista *l, int v);
void lst_imprime(Lista *l);
int lst_vazia(Lista *l);
Lista* lst_busca(Lista *l, int v);
Lista* lst_retira(Lista *l, int v);
void lst_libera(Lista *l);
Lista* lst_insere_ordenado(Lista *l, int v);
int lst_igual(Lista *l1, Lista *l2);
Lista* lst_intercala(Lista *l1, Lista *l2);

/* Funções recursivas de lista encadeada */

void lst_imprime_rec(Lista *l);
Lista* lst_retira_rec(Lista *l, int v);
void lst_libera_rec(Lista *l);

/* Funções de listas circulares */

void lcirc_imprime(Lista *l); 
void lcirc_libera(Lista *l);
Lista* lcirc_busca(Lista *l, int v);
Lista* lcirc_transforma(Lista *l);

/* Funções de listas duplamente encadeadas */

Lista_encad* lst_encad_insere(Lista_encad *l, int v);
Lista_encad* lst_encad_busca(Lista_encad *l, int v);
Lista_encad* lst_encad_retira(Lista_encad *l, int v);

/* Funções de listas duplamente encadeadas circulares */

Lista_encad* lst_encad_circ_cria();
Lista_encad* lst_encad_circ_transforma(Lista_encad *l);
Lista_encad* lst_encad_circ_insere_ordenado(Lista_encad *l, int v);
void lst_encad_circ_imprime(Lista_encad *l);
void lst_encad_circ_libera(Lista_encad *l);