#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoSimples {
    char nome[60];           // nome do fã
    int tipoIngresso;        // 1 = Comum, 2 = Premium, 3 = VIP
    struct NoSimples* prox;
} NoSimples;

typedef struct {
    NoSimples* inicio;
    NoSimples* fim;
} Fila;

// Converte o tipo do ingresso para texto
const char* tipo_para_texto(int tipo) {
    switch (tipo) {
        case 3: return "VIP";
        case 2: return "Premium";
        case 1: return "Comum";
        default: return "Desconhecido";
    }
}

// Cria uma fila simples vazia
Fila* criar_fila_simples() {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    if (f == NULL) {
        printf("Erro ao criar fila simples.\n");
        exit(1);
    }
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

// Insere fã no final da fila (FIFO)
void enfileirar(Fila* f, const char* nome, int tipoIngresso) {
    NoSimples* novo = (NoSimples*)malloc(sizeof(NoSimples));
    if (novo == NULL) {
        printf("Erro ao alocar no.\n");
        exit(1);
    }

    strcpy(novo->nome, nome);
    novo->tipoIngresso = tipoIngresso;
    novo->prox = NULL;

    if (f->fim == NULL) {  // fila vazia
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

// Remove do início da fila
void desenfileirar(Fila* f) {
    if (f->inicio == NULL) {
        printf("Fila simples vazia, nada para remover.\n");
        return;
    }

    NoSimples* removido = f->inicio;

    printf("Removendo fã: %s | Ingresso: %s (%d)\n",
           removido->nome,
           tipo_para_texto(removido->tipoIngresso),
           removido->tipoIngresso);

    f->inicio = removido->prox;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    free(removido);
}

// Mostra todos os elementos da fila
void mostrar_fila(Fila* f) {
    NoSimples* atual = f->inicio;
    if (atual == NULL) {
        printf("Fila simples vazia.\n");
        return;
    }

    printf("\nFila simples (ordem de chegada):\n");
    while (atual != NULL) {
        printf("Fã: %-15s | Ingresso: %-7s (%d)\n",
               atual->nome,
               tipo_para_texto(atual->tipoIngresso),
               atual->tipoIngresso);
        atual = atual->prox;
    }
    printf("\n");
}

// Exemplo de uso
int main() {
    Fila* f = criar_fila_simples();

    // Exemplo de fãs entrando na fila na ordem de chegada
    enfileirar(f, "Ana",   3); // VIP
    enfileirar(f, "Bruno", 1); // Comum
    enfileirar(f, "Carla", 2); // Premium
    enfileirar(f, "Diego", 1); // Comum

    mostrar_fila(f);

    // Removendo alguns fãs (sempre o primeiro da fila)
    desenfileirar(f);
    mostrar_fila(f);

    desenfileirar(f);
    mostrar_fila(f);

    return 0;
}
