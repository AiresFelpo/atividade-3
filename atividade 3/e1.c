#include <stdio.h>
#include <stdlib.h>

typedef struct Restaurante {
    char nome[50];
    char endereco[100];
    float precoMedio;
    char tipoComida[50];
    struct Restaurante* proximo;
} Restaurante;

void solicitarDados(Restaurante* restaurante) {
    printf("Digite o nome do restaurante: ");
    scanf(" %[^\n]s", restaurante->nome);
    printf("Digite o endereço do restaurante: ");
    scanf(" %[^\n]s", restaurante->endereco);
    printf("Digite o preço médio do restaurante: ");
    scanf("%f", &(restaurante->precoMedio));
    printf("Digite o tipo de comida do restaurante: ");
    scanf(" %[^\n]s", restaurante->tipoComida);
}

void listarRestaurantes(Restaurante* primeiroRestaurante) {
    Restaurante* restauranteAtual = primeiroRestaurante;

    if (restauranteAtual == NULL) {
        printf("A lista de restaurantes está vazia.\n");
        return;
    }

    printf("Lista de restaurantes:\n");

    while (restauranteAtual != NULL) {
        printf("Nome: %s\n", restauranteAtual->nome);
        printf("Endereço: %s\n", restauranteAtual->endereco);
        printf("Preço médio: R$%.2f\n", restauranteAtual->precoMedio);
        printf("Tipo de comida: %s\n", restauranteAtual->tipoComida);
        printf("\n");

        restauranteAtual = restauranteAtual->proximo;
    }
}

int main() {
    Restaurante* primeiroRestaurante = NULL;
    Restaurante* ultimoRestaurante = NULL;

    int opcao;

    do {
        printf("Selecione uma opção:\n");
        printf("1. Adicionar restaurante\n");
        printf("2. Listar restaurantes\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Restaurante* novoRestaurante = (Restaurante*)malloc(sizeof(Restaurante));
                novoRestaurante->proximo = NULL;
                solicitarDados(novoRestaurante);

                if (primeiroRestaurante == NULL) {
                    primeiroRestaurante = novoRestaurante;
                    ultimoRestaurante = novoRestaurante;
                } else {
                    ultimoRestaurante->proximo = novoRestaurante;
                    ultimoRestaurante = novoRestaurante;
                }

                printf("Restaurante adicionado com sucesso!\n");
                break;
            }
            case 2:
                listarRestaurantes(primeiroRestaurante);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Por favor, tente novamente.\n");
                break;
        }

        printf("\n");
    } while (opcao != 0);

    Restaurante* restauranteAtual = primeiroRestaurante;
    while (restauranteAtual != NULL) {
        Restaurante* restauranteParaLiberar = restauranteAtual;
        restauranteAtual = restauranteAtual->proximo;
        free(restauranteParaLiberar);
    }

    return 0;
}
