#include <stdio.h>
#include <stdlib.h>

typedef struct Dieta {
    char nome[50];
    float pesoPorcao;
    int calorias;
    struct Dieta* proximo;
} Dieta;

void solicitarDados(Dieta* comida) {
    printf("Digite o nome da comida: ");
    scanf(" %[^\n]s", comida->nome);
    printf("Digite o peso de uma porção (em gramas): ");
    scanf("%f", &(comida->pesoPorcao));
    printf("Digite o número de calorias: ");
    scanf("%d", &(comida->calorias));
}

void listarComidas(Dieta* primeiraComida) {
    Dieta* comidaAtual = primeiraComida;

    if (comidaAtual == NULL) {
        printf("A lista de comidas está vazia.\n");
        return;
    }

    printf("Lista de comidas:\n");

    while (comidaAtual != NULL) {
        printf("Nome: %s\n", comidaAtual->nome);
        printf("Peso porção: %.2fg\n", comidaAtual->pesoPorcao);
        printf("Calorias: %d\n", comidaAtual->calorias);
        printf("\n");

        comidaAtual = comidaAtual->proximo;
    }
}

void liberarComidas(Dieta* primeiraComida) {
    Dieta* comidaAtual = primeiraComida;
    while (comidaAtual != NULL) {
        Dieta* comidaParaLiberar = comidaAtual;
        comidaAtual = comidaAtual->proximo;
        free(comidaParaLiberar);
    }
}

int main() {
    Dieta* primeiraComida = NULL;
    Dieta* ultimaComida = NULL;

    int opcao;

    do {
        printf("Selecione uma opção:\n");
        printf("1. Adicionar comida\n");
        printf("2. Listar comidas\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Dieta* novaComida = (Dieta*)malloc(sizeof(Dieta));
                novaComida->proximo = NULL;
                solicitarDados(novaComida);

                if (primeiraComida == NULL) {
                    primeiraComida = novaComida;
                    ultimaComida = novaComida;
                } else {
                    ultimaComida->proximo = novaComida;
                    ultimaComida = novaComida;
                }

                printf("Comida adicionada com sucesso!\n");
                break;
            }
            case 2:
                listarComidas(primeiraComida);
                break;
            case 0:
                printf("Saindo...\n");
                liberarComidas(primeiraComida);
                break;
            default:
                printf("Opção inválida. Por favor, tente novamente.\n");
                break;
        }

        printf("\n");
    } while (opcao != 0);

    return 0;
}
