/* Struct de árvore binária */
typedef struct arv{
    char info;
    struct arv *esq;    // Galho da esquerda
    struct arv *dir;    // Galho da direita
}Tree;

/* Funções de árvore binária */

Tree *cria_vazia();
Tree *cria(char informacao, Tree *galho_esquerda, Tree *galho_direita);
int vazia(Tree *arvore);
void imprime_pre(Tree *arvore);
void imprime_sim(Tree *arvore);
void imprime_pos(Tree *arvore);
Tree *libera(Tree *arvore);
int pertence(Tree *arvore, char elemento);
static int comparaMaior(int a, int b);
int altura(Tree *arvore);
Tree *insere_ordenado(Tree *arvore, char informacao);
int conta_nos(Tree *arvore);
int conta_folhas(Tree *arvore);
int conta_nos_umFilho(Tree *arvore);
int conta_nos_doisFilhos(Tree *arvore);
void histograma(Tree *arvore);
void conta_repeticoes(Tree *arvore, int *vetor);
void tree_to_array(Tree *arvore, char *vetor);

Tree *insere_expressao(Tree *arvore, char *expressao);
void escreveNoArquivoTextoInfixa(Tree *arvore, FILE *arquivo);
void escreveNoArquivoTextoPosfixa(Tree *arvore, FILE *arquivo);

/* ============================================================================================= */
// Pilhas adicionado para a função para manipular as expressões
/* ============================================================================================= */

/* Struct "empilhar árvores" */
typedef struct lista_tree{
	Tree *info;
	struct lista_tree *prox;
}Lista_Tree;

/* Pilha */
typedef struct pilha_tree{
	Lista_Tree *prim;
} Pilha_Tree;

/* Funções de pilha com lista */

Pilha_Tree *pilha_tree_cria();
int pilha_tree_vazia(Pilha_Tree *p);
void pilha_tree_push(Pilha_Tree *p, Tree *v);
Tree *pilha_tree_pop(Pilha_Tree *p);
void pilha_tree_libera(Pilha_Tree *p);


