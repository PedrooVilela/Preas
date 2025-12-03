#ifndef FILA_PRIORIDADE_KATY_H
#define FILA_PRIORIDADE_KATY_H

// Nó da fila de prioridade (representa um fã)
typedef struct NoFila {
    char nome[60];            // nome do fã
    int prioridade;           // quanto maior o número, maior a prioridade
    struct NoFila* prox;      // próximo nó da lista
} NoFila;

// Estrutura que guarda apenas o ponteiro para o início da fila
typedef struct {
    NoFila* inicio;           // fã mais prioritário da fila
} FilaPrioridade;

// Cria e inicializa uma fila vazia
FilaPrioridade* criar_fila();

// Insere um novo fã na fila, respeitando a ordem de prioridade
void inserir(FilaPrioridade* f, char nome[], int prioridade);

// Remove o fã mais prioritário (início da fila)
void remover(FilaPrioridade* f);

// Mostra todos os fãs na fila, do mais prioritário para o menos prioritário
void imprimir(FilaPrioridade* f);

// Procura um fã pelo nome e mostra suas informações, se existir
void consultar(FilaPrioridade* f, const char* nome);

#endif
