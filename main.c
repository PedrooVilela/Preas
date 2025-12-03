#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

static void mostrar_legenda_prioridade() {
    printf("\nSugestao de prioridades:\n");
    printf("  10 - VIP / Camarote\n");
    printf("   5 - Pista Premium\n");
    printf("   1 - Ingresso comum\n\n");
}

int main() {
    FilaPrioridade* fila = criar_fila();
    int opcao;
    char nome[60];
    int prioridade;

    do {
        printf("\n===== GERENCIADOR DE FILA - SHOW KATY PERRY =====\n");
        printf("1 - Inserir fã na fila\n");
        printf("2 - Chamar proximo fã (remover de maior prioridade)\n");
        printf("3 - Listar todos os fãs na fila\n");
        printf("4 - Consultar fã pelo nome\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida.\n");
            return 1;
        }
        getchar(); // consome o '\n' que ficou no buffer

        switch (opcao) {
            case 1:
                printf("Nome do fã: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';  // remove o \n do final

                mostrar_legenda_prioridade();
                printf("Informe a prioridade (numero inteiro): ");
                if (scanf("%d", &prioridade) != 1) {
                    printf("Prioridade invalida.\n");
                    // limpa buffer simples
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
                }
                getchar(); // consome o '\n'

                inserir(fila, nome, prioridade);
                break;

            case 2:
                remover(fila);
                break;

            case 3:
                imprimir(fila);
                break;

            case 4:
                printf("Digite o nome do fã a ser consultado: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                consultar(fila, nome);
                break;

            case 0:
                printf("Encerrando sistema da fila do show...\n");
                break;

            default:
                printf("Opcao inexistente. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    // (Opcional) Poderia liberar toda a fila aqui percorrendo e dando free.

    return 0;
}
