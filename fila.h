#ifndef FILA_PRIORIDADE_KATY_H
#define FILA_PRIORIDADE_KATY_H

// Nó da fila de prioridade (representa um fã)
typedef struct NoFila {
    char nome[60];
    int prioridade;
    struct NoFila* prox;
} NoFila;

// Estrutura de uma fila genérica
typedef struct {
    NoFila* inicio;
    int tamanho;
} FilaPrioridade;

// Cria e inicializa uma fila vazia
FilaPrioridade* criar_fila();

// Insere um novo fã na fila (mantendo a ordem de prioridade)
void inserir(FilaPrioridade* f, const char nome[], int prioridade);

// Remove o fã mais prioritário
NoFila* remover(FilaPrioridade* f);

// Mostra todos os fãs na fila
void imprimir(FilaPrioridade* f, const char* titulo);

// Consulta um fã pelo nome
void consultar(FilaPrioridade* f, const char* nome);

// Libera toda a memória da fila
void destruir_fila(FilaPrioridade* f);

// Retorna tamanho atual da fila
int tamanho_fila(FilaPrioridade* f);

#endif

