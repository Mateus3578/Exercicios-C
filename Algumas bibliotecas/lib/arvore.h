/* Struct de árvore binária */
typedef struct arv{
    char info;
    struct arv *esq; // Galho da esquerda
    struct arv *dir; // Galho da direita
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