// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

void limpa_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void exibe_menu() {
    printf("\n====== FILA PARA SHOW DA KATY PERRY ======\n");
    printf("1 - Adicionar fã à fila\n");
    printf("2 - Deixar entrar o próximo fã (atender)\n");
    printf("3 - Ver quem é o próximo da fila\n");
    printf("4 - Listar toda a fila\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
}

int main() {
    Fila *fila = cria_fila();
    if (fila == NULL) {
        printf("Erro ao criar fila. Memoria insuficiente.\n");
        return 1;
    }

    int opcao;
    int proxima_senha = 1;

    do {
        exibe_menu();
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida.\n");
            limpa_buffer();
            continue;
        }

        limpa_buffer(); // limpa o '\n' que sobrou

        if (opcao == 1) {
            // Adicionar fã
            Fa f;
            f.senha = proxima_senha++;

            printf("Nome do fã: ");
            fgets(f.nome, TAM_NOME, stdin);
            size_t len = strlen(f.nome);
            if (len > 0 && f.nome[len - 1] == '\n') {
                f.nome[len - 1] = '\0';
            }

            printf("Tipo de ingresso (Pista, VIP, Premium): ");
            fgets(f.tipoIngresso, TAM_TIPO_INGRESSO, stdin);
            len = strlen(f.tipoIngresso);
            if (len > 0 && f.tipoIngresso[len - 1] == '\n') {
                f.tipoIngresso[len - 1] = '\0';
            }

            if (enfileira(fila, f)) {
                printf("Fã '%s' adicionado com a senha %d (%s).\n",
                       f.nome, f.senha, f.tipoIngresso);
            } else {
                printf("Erro ao adicionar fã na fila.\n");
            }

        } else if (opcao == 2) {
            // Atender próximo fã
            Fa f;
            if (desenfileira(fila, &f)) {
                printf("\nPróximo fã entrando no show:\n");
                printf("Senha: %d | Nome: %s | Ingresso: %s\n",
                       f.senha, f.nome, f.tipoIngresso);
            } else {
                printf("Nenhum fã na fila para entrar.\n");
            }

        } else if (opcao == 3) {
            // Ver próximo fã
            Fa f;
            if (frente(fila, &f)) {
                printf("\nPróximo fã na fila:\n");
                printf("Senha: %d | Nome: %s | Ingresso: %s\n",
                       f.senha, f.nome, f.tipoIngresso);
            } else {
                printf("Fila vazia.\n");
            }

        } else if (opcao == 4) {
            // Listar todos os fãs
            imprime_fila(fila);

        } else if (opcao == 0) {
            printf("Encerrando o sistema da fila do show...\n");
        } else {
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    libera_fila(fila);
    return 0;
}
