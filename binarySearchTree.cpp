// Rafael Pinheiro Carlos Maia
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct bst {
	struct noBst* raiz;
	int tam;
};


struct noBst {
	int val;
	struct noBst* esq;
	struct noBst* dir;
};


struct bst* alocarBst() {
	struct bst* alocarNovaBst = (struct bst*)malloc(sizeof(struct bst));

	alocarNovaBst->raiz = NULL;
	alocarNovaBst->tam = NULL;

	return alocarNovaBst;
}

/**
 * Funcao que aloca um novo noBst.
 **/
struct noBst* alocarNovoNo(int val) {
	struct noBst* temp = (struct noBst*)malloc(sizeof(struct noBst));

	temp->val = val;
	temp->esq = NULL;
	temp->dir = NULL;

	return temp;
}


/**
 * Funcao recursiva para inserir novo no na arvore passada
 * atraves da raiz.
 **/
void inserirNoRec(struct noBst** raiz, struct noBst* novoNo) {
	if (*raiz == NULL) {
		*raiz = alocarNovoNo(novoNo->val);
	}
	else if ((*raiz)->val > novoNo->val) {
		inserirNoRec(&(*raiz)->esq, novoNo);
	}
	else {
		inserirNoRec(&(*raiz)->dir, novoNo);
	}
}

/**
* Funcao iterativa para inserir novo no na arvore passada
* atraves da raiz.
**/
void inserirNoIt(struct noBst* raiz, struct noBst* novoNo) {
	noBst* prev = NULL;
	while (raiz != NULL) {
		prev = raiz;
		if (novoNo->val == raiz->val) {
			return;
		}
		else if (novoNo->val < raiz->val) {
			raiz = raiz->esq;
		}
		else {
			raiz = raiz->dir;
		}
	}
	noBst* temp = alocarNovoNo(novoNo->val);
	if (novoNo->val < prev->val) {
		prev->esq = temp;
	}
	else {
		prev->dir = temp;
	}
}

/**
 * Fachada para função de insercao.
 **/
void inserir(struct bst* bst, int val, bool rec) {
	struct noBst* novoNo = alocarNovoNo(val);
	if (bst->tam == NULL) {
		bst->raiz = novoNo;
		bst->tam++;
	}
	else if (rec) {
		inserirNoRec(&(bst->raiz), novoNo);
		bst->tam++;
	}
	else {
		inserirNoIt(bst->raiz, novoNo);
		bst->tam++;
	}
}


/**
 * Funcao recursiva para buscar val na arvore passada
 * atraves da raiz.
 **/
bool buscarRec(struct noBst* raiz, int val) {
	if (raiz == NULL || val == NULL) {
		return false;
	}
	else if (raiz->val == val) {
		return raiz;
	}
	else if (raiz->val > val) {
		return buscarRec(raiz->esq, val);
	}
	else {
		return buscarRec(raiz->dir, val);
	}
}

/**
 * Funcao iterativa para buscar v na arvore passada
 * atraves da raiz.
 **/
bool buscarIt(struct noBst* raiz, int v) {
	while (raiz != NULL) {
		if (raiz->val == v) {
			return raiz;
		}
		else {
			if (raiz->val > v) {
				raiz = raiz->esq;
			}
			else {
				raiz = raiz->dir;
			}
		}
	}
	return false;
}

/**
 * Fachada para função de busca.
 **/
bool buscar(struct bst* bst, int val, bool rec) {
	if (bst->tam == 0 || bst->raiz == NULL) {
		return false;
	}
	else if (rec) {
		buscarRec((bst->raiz), val);
	}
	else {
		buscarIt(bst->raiz, val);
	}
}


/**
 * Funcao rec para navegacao em-ordem.
 **/
void navEmOrdem(struct noBst* raiz) {
	if (raiz == NULL) {
		return;
	}

	navEmOrdem(raiz->esq);
	printf("%d ", raiz->val);
	navEmOrdem(raiz->dir);
}

/**
 * Funcao rec para navegacao pre-ordem.
 **/
void navPreOrdem(struct noBst* raiz) {
	if (raiz == NULL) {
		return;
	}

	printf("%d ", raiz->val);
	navPreOrdem(raiz->esq);
	navPreOrdem(raiz->dir);
}

/**
 * Funcao rec para navegacao pos-ordem.
 **/
void navPosOrdem(struct noBst* raiz) {
	if (raiz == NULL){
		return;
	}

	navPosOrdem(raiz->esq);
	navPosOrdem(raiz->dir);
	printf("%d ", raiz->val);
}


/**
 * Funcao rec para obter valor minimo.
 **/
int min(struct noBst* raiz) {
	if (raiz == NULL) {
		return 0;
	}

	while (raiz->esq != NULL) {
		raiz = raiz->esq;
	}
	return (raiz->val);
}

/**
 * Funcao rec para obter valor maximo.
 **/
int max(struct noBst* raiz) {
	if (raiz == NULL) {
		return 0;
	}
	while (raiz->dir != NULL) {
		raiz = raiz->dir;
	}

	return(raiz->val);
}

/**
 * Funcao rec para obter altura da arvore.
 **/
int altura(struct noBst* raiz) {
	if (raiz == NULL || (raiz->esq == NULL && raiz->dir == NULL)) {
		return 0;
	}

	int esq = altura(raiz->esq);
	int dir = altura(raiz->dir);

	if (esq > dir) {
		return esq + 1;
	}
	else {
		return dir + 1;
	}
}


/**
 * Funcao rec para remover da arvore no com valor especifico.
 **/
struct noBst* removerRec(struct noBst* raiz, int val) {
	if (raiz == NULL) {
		return raiz;
	}

	if (raiz->val > val) {
		raiz->esq = removerRec(raiz->esq, val);
		return raiz;
	}
	else if (raiz->val < val) {
		raiz->dir = removerRec(raiz->dir, val);
		return raiz;
	}

	if (raiz->esq == NULL) {
		noBst* temp = raiz->dir;
		delete raiz;
		return temp;
	}
	else if (raiz->dir == NULL) {
		noBst* temp = raiz->esq;
		delete raiz;
		return temp;
	}
	else {
		noBst* Aux = raiz;

		noBst* prox = raiz->dir;
		while (prox->esq != NULL) {
			Aux = prox;
			prox = prox->esq;
		}

		if (Aux != raiz)
			Aux->esq = prox->dir;
		else {
			Aux->dir = prox->dir;
		}

		raiz->val = prox->val;

		delete prox;
		return raiz;
	}
}

/**
 * Fachada para funcao de remocao.
*/
void remover(struct bst* bst, int val) {
	if (bst->raiz == NULL || val == 0) {
		return;
	}
	else {
		removerRec((bst->raiz), val);
		bst->tam--;
	}
}
