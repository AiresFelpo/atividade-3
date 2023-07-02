#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Veiculo {
    char proprietario[100];
    char combustivel[20];
    char modelo[50];
    char cor[20];
    char chassi[20];
    int ano;
    char placa[8];
    struct Veiculo* proximo;
} Veiculo;

void listarProprietariosAnoDiesel(Veiculo* primeiroVeiculo) {
    Veiculo* veiculoAtual = primeiroVeiculo;
    int encontrou = 0;

    printf("Proprietários de veículos do ano de 2010 ou posterior e movidos a diesel:\n");

    while (veiculoAtual != NULL) {
        if (veiculoAtual->ano >= 2010 && strcmp(veiculoAtual->combustivel, "diesel") == 0) {
            printf("Proprietário: %s\n", veiculoAtual->proprietario);
            encontrou = 1;
        }

        veiculoAtual = veiculoAtual->proximo;
    }

    if (!encontrou) {
        printf("Nenhum veículo corresponde aos critérios.\n");
    }
}

void listarPlacasProprietariosJ(Veiculo* primeiroVeiculo) {
    Veiculo* veiculoAtual = primeiroVeiculo;
    int encontrou = 0;

    printf("Placas que começam com a letra J e terminam com 0, 2, 4 ou 7 e seus respectivos proprietários:\n");

    while (veiculoAtual != NULL) {
        char primeiraLetra = veiculoAtual->placa[0];
        char ultimaLetra = veiculoAtual->placa[6];

        if (primeiraLetra == 'J' && (ultimaLetra == '0' || ultimaLetra == '2' || ultimaLetra == '4' || ultimaLetra == '7')) {
            printf("Placa: %s\n", veiculoAtual->placa);
            printf("Proprietário: %s\n", veiculoAtual->proprietario);
            encontrou = 1;
        }

        veiculoAtual = veiculoAtual->proximo;
    }

    if (!encontrou) {
        printf("Nenhum veículo corresponde aos critérios.\n");
    }
}

void listarModeloCorPlacasVogalSomaPar(Veiculo* primeiroVeiculo) {
    Veiculo* veiculoAtual = primeiroVeiculo;
    int encontrou = 0;

    printf("Modelo e cor dos veículos cujas placas possuem como segunda letra uma vogal\n");
    printf("e cuja soma dos valores numéricos fornece um número par:\n");

    while (veiculoAtual != NULL) {
        char segundaLetra = veiculoAtual->placa[1];

        if (segundaLetra == 'A' || segundaLetra == 'E' || segundaLetra == 'I' || segundaLetra == 'O' || segundaLetra == 'U') {
            int somaNumeros = 0;
            for (int i = 3; i < 7; i++) {
                somaNumeros += veiculoAtual->placa[i] - '0';
            }

            if (somaNumeros % 2 == 0) {
                printf("Modelo: %s\n", veiculoAtual->modelo);
                printf("Cor: %s\n", veiculoAtual->cor);
                encontrou = 1;
            }
        }

        veiculoAtual = veiculoAtual->proximo;
    }

    if (!encontrou) {
        printf("Nenhum veículo corresponde aos critérios.\n");
    }
}

void trocarProprietario(Veiculo* primeiroVeiculo, char* chassi) {
    Veiculo* veiculoAtual = primeiroVeiculo;
    int encontrou = 0;

    while (veiculoAtual != NULL) {
        if (strcmp(veiculoAtual->chassi, chassi) == 0) {
            if (strchr(veiculoAtual->placa, '0') == NULL) {
                printf("Digite o novo proprietário: ");
                scanf(" %[^\n]s", veiculoAtual->proprietario);
                printf("Proprietário alterado com sucesso!\n");
            } else {
                printf("A placa contém pelo menos um dígito igual a zero. A troca de proprietário não é permitida.\n");
            }

            encontrou = 1;
            break;
        }

        veiculoAtual = veiculoAtual->proximo;
    }

    if (!encontrou) {
        printf("Nenhum veículo com o chassi fornecido foi encontrado.\n");
    }
}

void liberarVeiculos(Veiculo* primeiroVeiculo) {
    Veiculo* veiculoAtual = primeiroVeiculo;
    while (veiculoAtual != NULL) {
        Veiculo* veiculoParaLiberar = veiculoAtual;
        veiculoAtual = veiculoAtual->proximo;
        free(veiculoParaLiberar);
    }
}

int main() {
    Veiculo* primeiroVeiculo = NULL;
    Veiculo* ultimoVeiculo = NULL;

    int opcao;

    do {
        printf("Selecione uma opção:\n");
        printf("1. Adicionar veículo\n");
        printf("2. Listar proprietários de veículos do ano de 2010 ou posterior e movidos a diesel\n");
        printf("3. Listar placas que começam com a letra J e terminam com 0, 2, 4 ou 7 e seus respectivos proprietários\n");
        printf("4. Listar modelo e cor dos veículos cujas placas possuem como segunda letra uma vogal e cuja soma dos valores numéricos fornece um número par\n");
        printf("5. Trocar proprietário com base no número do chassi\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Veiculo* novoVeiculo = (Veiculo*)malloc(sizeof(Veiculo));
                novoVeiculo->proximo = NULL;

                printf("Digite o nome do proprietário: ");
                scanf(" %[^\n]s", novoVeiculo->proprietario);
                printf("Digite o tipo de combustível (álcool, diesel ou gasolina): ");
                scanf(" %[^\n]s", novoVeiculo->combustivel);
                printf("Digite o modelo do veículo: ");
                scanf(" %[^\n]s", novoVeiculo->modelo);
                printf("Digite a cor do veículo: ");
                scanf(" %[^\n]s", novoVeiculo->cor);
                printf("Digite o número do chassi: ");
                scanf(" %[^\n]s", novoVeiculo->chassi);
                printf("Digite o ano do veículo: ");
                scanf("%d", &(novoVeiculo->ano));
                printf("Digite a placa do veículo (letras maiúsculas, três primeiras letras alfabéticas seguidas de quatro valores numéricos): ");
                scanf(" %[^\n]s", novoVeiculo->placa);

                if (primeiroVeiculo == NULL) {
                    primeiroVeiculo = novoVeiculo;
                    ultimoVeiculo = novoVeiculo;
                } else {
                    ultimoVeiculo->proximo = novoVeiculo;
                    ultimoVeiculo = novoVeiculo;
                }

                printf("Veículo adicionado com sucesso!\n");
                break;
            }
            case 2:
                listarProprietariosAnoDiesel(primeiroVeiculo);
                break;
            case 3:
                listarPlacasProprietariosJ(primeiroVeiculo);
                break;
            case 4:
                listarModeloCorPlacasVogalSomaPar(primeiroVeiculo);
                break;
            case 5: {
                char chassi[20];
                printf("Digite o número do chassi do veículo: ");
                scanf(" %[^\n]s", chassi);
                trocarProprietario(primeiroVeiculo, chassi);
                break;
            }
            case 0:
                printf("Saindo...\n");
                liberarVeiculos(primeiroVeiculo);
                break;
            default:
                printf("Opção inválida. Por favor, tente novamente.\n");
                break;
        }

        printf("\n");
    } while (opcao != 0);

    return 0;
}
