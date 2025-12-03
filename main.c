#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

#define CAPACIDADE_MAX 5

typedef struct {
    FilaPrioridade* pista;
    FilaPrioridade* premium;
    FilaPrioridade* camarote;
    FilaPrioridade* espera;
    FilaPrioridade* atendidos;
    int total_dentro;
    int contador_escalonamento;
} SistemaShow;

void inicializar_sistema(SistemaShow* s) {
    s->pista = criar_fila();
    s->premium = criar_fila();
    s->camarote = criar_fila();
    s->espera = criar_fila();
    s->atendidos = criar_fila();
    s->total_dentro = 0;
    s->contador_escalonamento = 0;
}

void destruir_sistema(SistemaShow* s) {
    destruir_fila(s->pista);
    destruir_fila(s->premium);
    destruir_fila(s->camarote);
    destruir_fila(s->espera);
    destruir_fila(s->atendidos);
}

void adicionar_fa(SistemaShow* s) {
    char nome[60];
    int setor, prioridade = 1;

    printf("\nNome do fã: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Setor: 1=Pista, 2=Premium, 3=Camarote: ");
    scanf("%d", &setor);
    getchar();

    switch (setor) {
        case 1: prioridade = 1; break;
        case 2: prioridade = 5; break;
        case 3: prioridade = 10; break;
        default: printf("Setor inválido.\n"); return;
    }

    int total_fila = tamanho_fila(s->pista) + tamanho_fila(s->premium) + tamanho_fila(s->camarote);

    if (s->total_dentro + total_fila >= CAPACIDADE_MAX) {
        inserir(s->espera, nome, prioridade);
        printf("Capacidade atingida! Fã movido para lista de espera.\n");
        return;
    }

    if (setor == 1) inserir(s->pista, nome, prioridade);
    else if (setor == 2) inserir(s->premium, nome, prioridade);
    else inserir(s->camarote, nome, prioridade);
}

void chamar_proximo(SistemaShow* s) {
    if (s->total_dentro >= CAPACIDADE_MAX) {
        printf("Capacidade máxima já atingida.\n");
        return;
    }

    NoFila* chamado = NULL;

    // Regras de escalonamento: 2 Premium -> 1 Pista -> 1 Camarote (rodando)
    if (s->contador_escalonamento < 2 && s->premium->inicio != NULL) {
        chamado = remover(s->premium);
        s->contador_escalonamento++;
    } else if (s->pista->inicio != NULL) {
        chamado = remover(s->pista);
        s->contador_escalonamento = 0;
    } else if (s->camarote->inicio != NULL) {
        chamado = remover(s->camarote);
    } else {
        printf("Nenhum fã na fila.\n");
        return;
    }

    if (chamado) {
        printf("Chamando: %s (prioridade %d)\n", chamado->nome, chamado->prioridade);
        inserir(s->atendidos, chamado->nome, chamado->prioridade);
        s->total_dentro++;
        free(chamado);
    }

    // Se há alguém na lista de espera e ainda cabe
    if (s->espera->inicio != NULL && s->total_dentro < CAPACIDADE_MAX) {
        NoFila* da_espera = remover(s->espera);
        printf("Liberando da lista de espera: %s\n", da_espera->nome);
        inserir(s->pista, da_espera->nome, da_espera->prioridade);
        free(da_espera);
    }
}

void listar_tudo(SistemaShow* s) {
    imprimir(s->camarote, "Fila Camarote");
    imprimir(s->premium, "Fila Premium");
    imprimir(s->pista, "Fila Pista");
    imprimir(s->espera, "Lista de Espera");
    printf("\nTotal dentro do show: %d / %d\n", s->total_dentro, CAPACIDADE_MAX);
}

void listar_atendidos(SistemaShow* s) {
    imprimir(s->atendidos, "Histórico de Atendidos");
}

int main() {
    SistemaShow s;
    inicializar_sistema(&s);
    int op;

    do {
        printf("\n====== SISTEMA DE FILA - SHOW KATY PERRY ======\n");
        printf("1 - Adicionar fã à fila\n");
        printf("2 - Chamar próximo fã\n");
        printf("3 - Listar todas as filas\n");
        printf("4 - Consultar fã\n");
        printf("5 - Ver histórico de atendidos\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1: adicionar_fa(&s); break;
            case 2: chamar_proximo(&s); break;
            case 3: listar_tudo(&s); break;
            case 4: {
                char nome[60];
                printf("Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                consultar(s.pista, nome);
                consultar(s.premium, nome);
                consultar(s.camarote, nome);
                break;
            }
            case 5: listar_atendidos(&s); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opção inválida.\n");
        }

    } while (op != 0);

    destruir_sistema(&s);
    return 0;
}
