// fila.h
#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

#define TAM_NOME 50
#define TAM_TIPO_INGRESSO 20

// Estrutura que representa um fã do show da Katy Perry
typedef struct {
    int senha;  // número da senha na fila
    char nome[TAM_NOME];
    char tipoIngresso[TAM_TIPO_INGRESSO]; // ex: "Pista", "VIP", "Premium"
} Fa;

// Nó da lista encadeada
typedef struct No {
    Fa dado;
    struct No *prox;
} No;

// Estrutura da fila
typedef struct {
    No *inicio;  // primeiro da fila
    No *fim;     // último da fila
    int tamanho; // quantidade de fãs na fila
} Fila;

// Cria e inicializa uma fila vazia
Fila* cria_fila();

// Libera toda a memória da fila
void libera_fila(Fila *f);

// Retorna true se a fila estiver vazia
bool fila_vazia(Fila *f);

// Insere um fã no final da fila
bool enfileira(Fila *f, Fa x);

// Remove o fã do início da fila (quem vai entrar no show)
bool desenfileira(Fila *f, Fa *x);

// Consulta o fã do início da fila sem remover
bool frente(Fila *f, Fa *x);

// Exibe toda a fila (para visualização)
void imprime_fila(Fila *f);

#endif
