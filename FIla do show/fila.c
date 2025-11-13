// fila.c
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila* cria_fila() {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    if (f != NULL) {
        f->inicio = NULL;
        f->fim = NULL;
        f->tamanho = 0;
    }
    return f;
}

void libera_fila(Fila *f) {
    if (f == NULL) return;

    No *atual = f->inicio;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(f);
}

bool fila_vazia(Fila *f) {
    if (f == NULL) return true;
    return (f->inicio == NULL);
}

bool enfileira(Fila *f, Fa x) {
    if (f == NULL) return false;

    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) return false;

    novo->dado = x;
    novo->prox = NULL;

    if (fila_vazia(f)) {
        f->inicio = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;
    f->tamanho++;

    return true;
}

bool desenfileira(Fila *f, Fa *x) {
    if (f == NULL || fila_vazia(f)) return false;

    No *removido = f->inicio;
    *x = removido->dado;

    f->inicio = removido->prox;
    if (f->inicio == NULL) {
        f->fim = NULL; // fila ficou vazia
    }

    free(removido);
    f->tamanho--;

    return true;
}

bool frente(Fila *f, Fa *x) {
    if (f == NULL || fila_vazia(f)) return false;

    *x = f->inicio->dado;
    return true;
}

void imprime_fila(Fila *f) {
    if (f == NULL) {
        printf("Fila inexistente.\n");
        return;
    }

    if (fila_vazia(f)) {
        printf("\n[Fila vazia]\n");
        return;
    }

    printf("\n--- Fila para o show da Katy Perry (inicio -> fim) ---\n");
    No *atual = f->inicio;
    while (atual != NULL) {
        printf("Senha: %d | Nome: %s | Ingresso: %s\n",
               atual->dado.senha,
               atual->dado.nome,
               atual->dado.tipoIngresso);
        atual = atual->prox;
    }
    printf("Total de fãs na fila: %d\n", f->tamanho);
}
