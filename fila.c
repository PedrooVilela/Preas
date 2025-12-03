#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

static NoFila* criar_no(const char* nome, int prioridade) {
    NoFila* novo = (NoFila*)malloc(sizeof(NoFila));
    if (!novo) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    strcpy(novo->nome, nome);
    novo->prioridade = prioridade;
    novo->prox = NULL;
    return novo;
}

FilaPrioridade* criar_fila() {
    FilaPrioridade* f = (FilaPrioridade*)malloc(sizeof(FilaPrioridade));
    if (!f) {
        printf("Erro ao criar fila.\n");
        exit(1);
    }
    f->inicio = NULL;
    f->tamanho = 0;
    return f;
}

void inserir(FilaPrioridade* f, const char nome[], int prioridade) {
    if (!f) return;

    NoFila* novo = criar_no(nome, prioridade);
    NoFila** pp = &f->inicio;

    while (*pp && (*pp)->prioridade >= prioridade)
        pp = &((*pp)->prox);

    novo->prox = *pp;
    *pp = novo;
    f->tamanho++;

    printf("Fã \"%s\" adicionado (prioridade %d).\n", nome, prioridade);
}

NoFila* remover(FilaPrioridade* f) {
    if (!f || !f->inicio) {
        printf("Fila vazia.\n");
        return NULL;
    }

    NoFila* removido = f->inicio;
    f->inicio = removido->prox;
    f->tamanho--;

    return removido;
}

void imprimir(FilaPrioridade* f, const char* titulo) {
    if (!f || !f->inicio) {
        printf("\n%s está vazia.\n", titulo);
        return;
    }

    printf("\n========== %s ==========\n", titulo);
    NoFila* atual = f->inicio;
    int pos = 1;
    while (atual) {
        printf("%2d) %-20s | Prioridade: %d\n", pos++, atual->nome, atual->prioridade);
        atual = atual->prox;
    }
    printf("Total: %d\n", f->tamanho);
    printf("===================================\n");
}

void consultar(FilaPrioridade* f, const char* nome) {
    if (!f || !f->inicio) {
        printf("Fila vazia.\n");
        return;
    }

    NoFila* atual = f->inicio;
    int pos = 1;
    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Fã encontrado na posição %d (prioridade %d)\n", pos, atual->prioridade);
            return;
        }
        atual = atual->prox;
        pos++;
    }

    printf("Fã \"%s\" não encontrado.\n", nome);
}

void destruir_fila(FilaPrioridade* f) {
    if (!f) return;
    NoFila* atual = f->inicio;
    while (atual) {
        NoFila* prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(f);
}

int tamanho_fila(FilaPrioridade* f) {
    return (f ? f->tamanho : 0);
}
