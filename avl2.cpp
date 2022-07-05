#pragma once
// Rafael Pinheiro Carlos Maia

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <queue>
using namespace std;

void atualizar(struct noBstAvl* no);
struct noBstAvl* balancear(struct noBstAvl* no);
struct noBstAvl* rebalancearEsqEsq(struct noBstAvl* no);
struct noBstAvl* rebalancearEsqDir(struct noBstAvl* no);
struct noBstAvl* rebalancearDirDir(struct noBstAvl* no);
struct noBstAvl* rebalancearDirEsq(struct noBstAvl* no);
int altura(struct noBstAvl* raiz);


struct avl {
    struct noBstAvl* raiz;
    int tam;
};


struct noBstAvl {
    int val;
    int altura;
    int balanco;
    struct noBstAvl* esq;
    struct noBstAvl* dir;
};


/**
 * Funcao que aloca uma nova arvore avl.
 **/
struct avl* alocarAvl() {
    struct avl* alocarNovaAvl = (struct avl*)malloc(sizeof(struct avl));

    alocarNovaAvl->raiz = NULL;
    alocarNovaAvl->tam = NULL;

    return alocarNovaAvl;
}


/**
 * Funcao que aloca um novo noBstAvl, e
 * ajusta os ponteiros esq e dir para NULL,
 * e variáveis altura e balanco para 0.
 **/
struct noBstAvl* alocarNovoNo(int val) {
    struct noBstAvl* novoNo = (struct noBstAvl*)malloc(sizeof(struct noBstAvl));
    novoNo->val = val;
    novoNo->altura = 0;
    novoNo->balanco = 0;
    novoNo->dir = NULL;
    novoNo->esq = NULL;
    return novoNo;
}

/**
 * Funcao que rotaciona uma arvore para a
 * direita e retorna a nova raiz.
 **/
struct noBstAvl* rotacaoDireita(struct noBstAvl* arvore) {
    struct noBstAvl* esq = arvore->esq;
    arvore->esq = esq->dir;
    esq->dir = arvore;
    atualizar(arvore);
    atualizar(esq);
    return esq;
}

/**
 * Funcao que rotaciona uma arvore para a
 * esquerda e retorna a nova raiz.
 **/
struct noBstAvl* rotacaoEsquerda(struct noBstAvl* arvore) {
    struct noBstAvl* dir = arvore->dir;
    arvore->dir = dir->esq;
    dir->esq = arvore;
    atualizar(arvore);
    atualizar(dir);
    return dir;
}

/**
 * Funcao que recebe a raiz de uma bstAvl, e
 * insere um novo valor nela.
 * Raiz é passada por referência (ponteiro de ponteiro).
 * Lembrar de atualizar altura e fator de balanco dos nós
 * antecessores do nó inserido, bem como balanceá-los caso
 * seja necessário.
 * Dica: reutilizar a função de inserir de BST, e lembrar
 * de como usar inteligentemente a recursão para conseguir
 * atualizar e balancear os nós antecessores.
 **/
void inserirNo(struct noBstAvl** raiz, int val) {
    if (*raiz == NULL) {
        *raiz = alocarNovoNo(val);
        //*tamanho += 1;
        return;
    }

    else if ((*raiz)->val > val) {
        inserirNo(&(*raiz)->esq, val);
        *raiz = balancear(*raiz);
        atualizar(*raiz);
    }
    else {
        inserirNo(&(*raiz)->dir, val);
        *raiz = balancear(*raiz);
        atualizar(*raiz);
    }

    *raiz = balancear(*raiz);
    atualizar(*raiz);
}

/**
 * Funcao fachada para insercao, similar a funcao de
 * insercao na BST.
 * Lembrar de incrementar tamanho.
 **/
void inserir(struct avl* avl, int val) {
      /*struct avl* val = alocarNovoNo(val);
      if (avl->tam == NULL) {
          avl->raiz = val;
          avl->tam++;
      }
      else {*/
    inserirNo(&(avl->raiz), val);
    avl->tam++;
    //}
}


/**
 * Funcao que recebe a raiz de uma bstAvl e atualiza sua altura
 * e fator de balanço.
 * Lembre que a altura das sub-árvores direita e esquerda
 * não vão mudar, por isso a implementação não é tão complicada.
 **/
void atualizar(struct noBstAvl* no) {
    no->altura = altura(no);
    if (no->dir != NULL && no->esq != NULL) {
        no->balanco = no->dir->altura - no->esq->altura;
    }
    else if (no->dir != NULL) {
        no->balanco = no->dir->altura;
    }
    else if (no->esq != NULL) {
        no->balanco = -no->esq->altura;
    }
    else {
        no->balanco = 0;
    }
}

/**
 * Funcao que recebe a raiz de uma bstAvl e identifica em qual caso
 * ela se encaixa para executar os procedimentos de balanceamento
 * corretos:
 *      - Caso 1: esquerda-esquerda e esquerda-cheio
 *      - Caso 2: esquerda-direita
 *      - Caso 3: direita-direita e direita-cheio
 *      - Caso 4: direita-esquerda
 * Lembrar que quando há balanceamento temos uma nova raiz
 * que deve ser retornada para a função que chama o balanceamento.
 * Dica: usar fator de balanço do nó e de uma de suas sub-árvores
 * para descobrir qual é o caso.
 **/
struct noBstAvl* balancear(struct noBstAvl* no) {
    if (no->balanco == -2) {
        if (no->esq->balanco <= 0) {
            no = rebalancearEsqEsq(no);
        }
        else {
            no = rebalancearEsqDir(no);
        }
    }
    if (no->balanco == 2) {
        if (no->dir->balanco >= 0) {
            no = rebalancearDirDir(no);
        }
        else {
            no = rebalancearDirEsq(no);
        }
    }
    return no;
}

/**
 * Funcao que recebe a raiz de uma bstAvl e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 1.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/
struct noBstAvl* rebalancearEsqEsq(struct noBstAvl* no) {
    no = rotacaoDireita(no);
    return no;
}

/**
 * Funcao que recebe a raiz de uma bstAvl e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 2.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/
struct noBstAvl* rebalancearEsqDir(struct noBstAvl* no) {
    no->esq = rotacaoEsquerda(no->esq);
    no = rotacaoDireita(no);
    return no;
}

/**
 * Funcao que recebe a raiz de uma bstAvl e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 3.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/
struct noBstAvl* rebalancearDirDir(struct noBstAvl* no) {
    no = rotacaoEsquerda(no);
    return no;
}

/**
 * Funcao que recebe a raiz de uma bstAvl e usa as rotações
 * apropriadas para balancear uma árvore desbalanceada no caso 4.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa função deve retornar a nova raiz.
 **/
struct noBstAvl* rebalancearDirEsq(struct noBstAvl* no) {
    no->dir = rotacaoDireita(no->dir);
    no = rotacaoEsquerda(no);
    return no;
}

/**
 * Funcao que retorna o maior valor de uma árvore AVL.
 * Mesma implementação da BST.
 **/
int max(struct noBstAvl* raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    else if (raiz->dir != NULL) {
        return max(raiz->dir);
    }
    return raiz->val;
}

/**
 * Funcao que retorna o menor valor de uma árvore AVL.
 * Mesma implementação da BST.
 **/
int min(struct noBstAvl* raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    else if (raiz->esq != NULL) {
        return min(raiz->esq);
    }
    return raiz->val;
}

/**
 * Funcao que retorna a altura de uma árvore.
 * A altura de uma árvore é dada pela quantidade
 * de arestas entre a raiz e a folha mais distante.
 * Mesma implementação da BST.
 **/
int altura(struct noBstAvl* raiz) {
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
 * Funcao que recebe a raiz de uma árvore AVL, e
 * remove o nó que contem o valor passado como
 * argumento.
 * Lembrar de atualizar altura e fator de balanco dos nós
 * antecessores do nó removido, bem como balanceá-los caso
 * seja necessário.
 * Dica: reutilizar a função de remover de BST, e lembrar
 * de como usar inteligentemente a recursão para conseguir
 * atualizar e balancear os nós antecessores.
 **/
 struct noBstAvl* removerNo(struct noBstAvl* raiz, int val) {
     if (raiz == NULL) {
         return raiz;
     }
 
     if (raiz->val > val) {
         raiz->esq = removerNo(raiz->esq,val);
         raiz = balancear(raiz);
         atualizar(raiz);
     }
     else if (raiz->val < val) {
         raiz->dir = removerNo(raiz->dir, val);
         raiz = balancear(raiz);
         atualizar(raiz);
     }
     else {
     if (raiz->esq == NULL && raiz->dir == NULL) {
         free(raiz);
         //*tamanho -= 1;
         return NULL;
     }
     else if (raiz->esq == NULL || raiz->dir == NULL) {
         struct noBstAvl* aux;
         if (raiz->esq == NULL) {
             aux = raiz->dir;
         }
         else {
             aux = raiz->esq;
         }
         free(raiz);
         //*tamanho -= 1;
         return aux;
     }
     else {
         int aux;
         aux = min(raiz->dir);
         raiz->val = aux;
         raiz->dir = removerNo(raiz->dir, aux);
     }
     }
     raiz = balancear(raiz);
     atualizar(raiz);
     return raiz;
 
 }

 /**
  * Funcao fachada para remocao, similar a funcao de
  * remocao na BST.
  * Lembrar de decrementar tamanho.
  **/
  void remover(struct avl* avl, int val) {
      if (removerNo(avl->raiz, val) != NULL) {
          avl->tam--;
      }
  }


void imprimir(queue<struct noBstAvl*> nosImpressao);

/**
* Função que imprime a árvore.
* Pode ser útil para depuração.
**/
void imprimir(struct noBstAvl* raiz) {
    queue<struct noBstAvl*> nosImpressao;
    nosImpressao.push(raiz);
    imprimir(nosImpressao);
}

void imprimir(queue<struct noBstAvl*> nosImpressao) {

    queue<struct noBstAvl*> nosImpressaoProxNivel;

    while (!nosImpressao.empty()) {
        struct noBstAvl* noImpressao = nosImpressao.front();
        //add filhos na fila
        if (noImpressao != NULL) {
            if (noImpressao->esq != NULL)
                nosImpressaoProxNivel.push(noImpressao->esq);
            else
                nosImpressaoProxNivel.push(NULL);
            if (noImpressao->dir != NULL)
                nosImpressaoProxNivel.push(noImpressao->dir);
            else
                nosImpressaoProxNivel.push(NULL);
        }
        nosImpressao.pop();

        if (noImpressao != NULL) {
            cout << to_string(noImpressao->val) << " | ";
        }
        else {
            cout << "N | ";
        }
    }
    cout << endl << endl;
    if (!nosImpressaoProxNivel.empty())
        imprimir(nosImpressaoProxNivel);
}