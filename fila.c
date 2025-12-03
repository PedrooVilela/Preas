#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

// Função auxiliar para criar um novo nó já preenchido
static NoFila* criar_no(const char* nome, int prioridade) {
    NoFila* novo = (NoFila*)malloc(sizeof(NoFila));
    if (novo == NULL) {
        printf("Erro ao alocar memoria para novo no.\n");
        exit(1);
    }
    strcpy(novo->nome, nome);
    novo->prioridade = prioridade;
    novo->prox = NULL;
    return novo;
}

FilaPrioridade* criar_fila() {
    FilaPrioridade* f = (FilaPrioridade*)malloc(sizeof(FilaPrioridade));
    if (f == NULL) {
        printf("Erro ao criar fila.\n");
        exit(1);
    }
    f->inicio = NULL;
    return f;
}

void inserir(FilaPrioridade* f, char nome[], int prioridade) {
    if (f == NULL) {
        printf("Fila inexistente.\n");
        return;
    }

    NoFila* novo = criar_no(nome, prioridade);

    // Ponteiro para ponteiro, para facilitar a inserção em qualquer posição
    NoFila** pp = &f->inicio;

    // Avança enquanto o próximo tiver prioridade maior ou igual
    while (*pp != NULL && (*pp)->prioridade >= prioridade) {
        pp = &((*pp)->prox);
    }

    // Insere o nó no ponto encontrado
    novo->prox = *pp;
    *pp = novo;

    printf("Fã \"%s\" adicionado à fila (prioridade %d).\n", nome, prioridade);
}

void remover(FilaPrioridade* f) {
    if (f == NULL || f->inicio == NULL) {
        printf("Nao ha ninguem aguardando na fila.\n");
        return;
    }

    NoFila* removido = f->inicio;
    f->inicio = removido->prox;

    printf("Chamando para entrar no show: %s (prioridade %d)\n",
           removido->nome, removido->prioridade);

    free(removido);
}

void imprimir(FilaPrioridade* f) {
    if (f == NULL || f->inicio == NULL) {
        printf("Fila vazia. Nenhum fã aguardando.\n");
        return;
    }

    NoFila* atual = f->inicio;
    int posicao = 1;

    printf("\n========== FILA DO SHOW DA KATY PERRY ==========\n");
    while (atual != NULL) {
        printf("%2d) Fã: %-20s | Prioridade: %d\n",
               posicao, atual->nome, atual->prioridade);
        atual = atual->prox;
        posicao++;
    }
    printf("===============================================\n");
}

void consultar(FilaPrioridade* f, const char* nome) {
    if (f == NULL || f->inicio == NULL) {
        printf("Fila vazia. Nao ha ninguem para consultar.\n");
        return;
    }

    NoFila* atual = f->inicio;
    int posicao = 1;

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Fã encontrado na fila!\n");
            printf("Posicao: %d\n", posicao);
            printf("Nome: %s\n", atual->nome);
            printf("Prioridade: %d\n", atual->prioridade);
            return;
        }
        atual = atual->prox;
        posicao++;
    }

    printf("Fã \"%s\" nao esta na fila.\n", nome);
}
