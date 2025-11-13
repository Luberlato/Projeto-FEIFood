#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FEIFood.h"

void cadastrarUsuario(char usuario[255]) {
    FILE *f = fopen("usuarios.txt", "r");
    char linha[255];
    int existe = 0;

    if (f != NULL) {
        while (fgets(linha, sizeof(linha), f)) {
            linha[strcspn(linha, "\n")] = '\0';
            if (strcmp(linha, usuario) == 0) {
                existe = 1;
                break;
            }
        }
        fclose(f);
    }

    if (existe) {
        printf("Esse usuario ja esta cadastrado.\n");
    } else {
        f = fopen("usuarios.txt", "a");
        if (f == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }
        fprintf(f, "%s\n", usuario);
        fclose(f);
        printf("Usuario cadastrado com sucesso!\n");
    }
}

int fazerLogin(char usuario[255]) {
    FILE *f = fopen("usuarios.txt", "r");
    char linha[255];
    int existeLogin = 0;

    if (f != NULL) {
        while (fgets(linha, sizeof(linha), f)) {
            linha[strcspn(linha, "\n")] = '\0';
            if (strcmp(linha, usuario) == 0) {
                existeLogin = 1;
                break;
            }
        }
        fclose(f);

        if (existeLogin) {
            printf("Bem-vindo ao sistema, %s!\n", usuario);
            return 1;
        } else {
            printf("Usuario nao cadastrado.\n");
            return 0;
        }
    } else {
        printf("Erro ao abrir o arquivo de usuarios.\n");
        return 0;
    }
}

void buscarComida(char usuario[255]) {
    char comida[255];
    char linha[255];
    int encontrou = 0;

    printf("Digite o alimento que deseja buscar: ");
    scanf("%s", comida);

    FILE *comidas = fopen("comidas.txt", "r");
    char arquivoUsuario[300];
    sprintf(arquivoUsuario, "historico_%s.txt", usuario);
    if (comidas == NULL) {
        printf("Erro ao abrir o arquivo de comidas.\n");
        return;
    }

    printf("=== Lista de comidas ===\n");
    while (fgets(linha, sizeof(linha), comidas)) {
        linha[strcspn(linha, "\n")] = '\0';
        printf("%s\n", linha); // lista todas as comidas
        if (strcmp(linha, comida) == 0) {
            encontrou = 1;
        }
    }
    fprintf(comidas, "%s",);
    if (encontrou) {
        printf("O alimento '%s' foi encontrado!\n", comida);
    } else {
        printf("O alimento '%s' nao foi encontrado.\n", comida);
    }

    fclose(comidas);
}

void menuInicial(char usuario[255]) {
    int option;
    do {
        printf("\n=== Menu Inicial ===\n");
        printf("1 - Fazer pedido\n");
        printf("2 - Buscar alimento\n");
        printf("3 - Listar informacoes\n");
        printf("4 - Avaliar pedido\n");
        printf("0 - Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1:
                menuPedido(usuario);
                break;
            case 2:
                buscarComida(usuario);
                break;
            case 3:
                printf("Listando informacoes...\n");
                break;
            case 4:
                printf("Avaliando pedido...\n");
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (option != 0);
}

void fazerPedido(char usuario[255]) {
    char arquivoUsuario[300];
    sprintf(arquivoUsuario, "pedidos_%s.txt", usuario);

    FILE *pedido = fopen(arquivoUsuario, "r");
    int idPedido = 1;
    if (pedido != NULL) {
        char linha[300];
        while (fgets(linha, sizeof(linha), pedido)) {
            idPedido++;
        }
        fclose(pedido);
    }

    pedido = fopen(arquivoUsuario, "a");
    if (pedido == NULL) {
        printf("Erro ao abrir o arquivo do pedido.\n");
        return;
    }

    char comida[255];
    char linhaFazer[255];
    char pedidoFinal[500];
    sprintf(pedidoFinal, "%d", idPedido);

    while (1) {
        printf("Digite o alimento que quer pedir (ou 0 para finalizar): ");
        scanf("%s", comida);
        if (strcmp(comida, "0") == 0) break;

        int existe = 0;
        FILE *comidas = fopen("comidas.txt", "r");
        if (comidas != NULL) {
            while (fgets(linhaFazer, sizeof(linhaFazer), comidas)) {
                linhaFazer[strcspn(linhaFazer, "\n")] = '\0';
                if (strcmp(linhaFazer, comida) == 0) {
                    existe = 1;
                    break;
                }
            }
            fclose(comidas);
        }

        if (!existe) {
            printf("Esse alimento nao existe. Tente novamente.\n");
            continue;
        }

        strcat(pedidoFinal, ", ");
        strcat(pedidoFinal, comida);
    }

    fprintf(pedido, "%s\n", pedidoFinal);
    fclose(pedido);

    printf("Pedido salvo com sucesso no arquivo '%s'!\n", arquivoUsuario);
}

void modificarPedido(char usuario[255]) {
    char arquivoUsuario[300];
    sprintf(arquivoUsuario, "pedidos_%s.txt", usuario);

    FILE *f = fopen(arquivoUsuario, "r");
    if (f == NULL) {
        printf("Nenhum pedido encontrado para este usuario.\n");
        return;
    }

    char pedidos[100][500];
    int totalPedidos = 0;
    while (fgets(pedidos[totalPedidos], sizeof(pedidos[totalPedidos]), f)) {
        pedidos[totalPedidos][strcspn(pedidos[totalPedidos], "\n")] = '\0';
        totalPedidos++;
    }
    fclose(f);

    if (totalPedidos == 0) {
        printf("Nenhum pedido encontrado.\n");
        return;
    }

    printf("\n=== Pedidos atuais ===\n");
    for (int i = 0; i < totalPedidos; i++) {
        printf("%s\n", pedidos[i]);
    }

    int idEscolhido;
    printf("\nDigite o ID do pedido que deseja modificar: ");
    scanf("%d", &idEscolhido);
    getchar();

    int encontrado = 0;
    for (int i = 0; i < totalPedidos; i++) {
        char idStr[10];
        sprintf(idStr, "%d", idEscolhido);
        if (strncmp(pedidos[i], idStr, strlen(idStr)) == 0) {
            encontrado = 1;

            printf("Modificando o pedido %d...\n", idEscolhido);

            char novaLinha[500];
            sprintf(novaLinha, "%d", idEscolhido);

            char comida[255];
            char linhaComida[255];
            while (1) {
                printf("Adicione uma comida (ou digite 0 para finalizar): ");
                scanf("%s", comida);
                if (strcmp(comida, "0") == 0) break;

                int existe = 0;
                FILE *comidas = fopen("comidas.txt", "r");
                if (comidas != NULL) {
                    while (fgets(linhaComida, sizeof(linhaComida), comidas)) {
                        linhaComida[strcspn(linhaComida, "\n")] = '\0';
                        if (strcmp(linhaComida, comida) == 0) {
                            existe = 1;
                            break;
                        }
                    }
                    fclose(comidas);
                }

                if (!existe) {
                    printf("Esse alimento nao existe. Tente novamente.\n");
                    continue;
                }

                strcat(novaLinha, ", ");
                strcat(novaLinha, comida);
            }

            strcpy(pedidos[i], novaLinha);
            break;
        }
    }

    if (!encontrado) {
        printf("ID nao encontrado.\n");
        return;
    }

    FILE *fw = fopen(arquivoUsuario, "w");
    if (fw == NULL) {
        printf("Erro ao abrir o arquivo de pedidos.\n");
        return;
    }

    for (int i = 0; i < totalPedidos; i++) {
        fprintf(fw, "%s\n", pedidos[i]);
    }
    fclose(fw);

    printf("Pedido modificado com sucesso!\n");
}

void cancelarPedido(char usuario[255]) {
    char arquivoUsuario[300];
    sprintf(arquivoUsuario, "pedidos_%s.txt", usuario);

    FILE *f = fopen(arquivoUsuario, "r");
    if (f == NULL) {
        printf("Nenhum pedido encontrado.\n");
        return;
    }

    char pedidos[100][500];
    int totalPedidos = 0;
    while (fgets(pedidos[totalPedidos], sizeof(pedidos[totalPedidos]), f)) {
        pedidos[totalPedidos][strcspn(pedidos[totalPedidos], "\n")] = '\0';
        totalPedidos++;
    }
    fclose(f);

    if (totalPedidos == 0) {
        printf("Nenhum pedido encontrado.\n");
        return;
    }

    printf("\n=== Pedidos atuais ===\n");
    for (int i = 0; i < totalPedidos; i++) {
        printf("%s\n", pedidos[i]);
    }

    int idEscolhido;
    printf("\nDigite o ID do pedido que deseja cancelar: ");
    scanf("%d", &idEscolhido);

    int encontrado = 0;
    for (int i = 0; i < totalPedidos; i++) {
        char idStr[10];
        sprintf(idStr, "%d", idEscolhido);
        if (strncmp(pedidos[i], idStr, strlen(idStr)) == 0) {
            encontrado = 1;
            for (int j = i; j < totalPedidos - 1; j++) {
                strcpy(pedidos[j], pedidos[j + 1]);
            }
            totalPedidos--;
            break;
        }
    }

    if (!encontrado) {
        printf("ID nao encontrado.\n");
        return;
    }

    FILE *fw = fopen(arquivoUsuario, "w");
    if (fw == NULL) {
        printf("Erro ao abrir o arquivo de pedidos.\n");
        return;
    }

    for (int i = 0; i < totalPedidos; i++) {
        fprintf(fw, "%s\n", pedidos[i]);
    }
    fclose(fw);

    printf("Pedido cancelado com sucesso!\n");
}

void menuPedido(char usuario[255]) {
    int optionPedido;
    do {
        printf("\n=== Opcoes de Pedido ===\n");
        printf("1 - Fazer pedido\n");
        printf("2 - Mudar pedido\n");
        printf("3 - Cancelar pedido\n");
        printf("4 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &optionPedido);
        getchar();

        switch (optionPedido) {
            case 1:
                fazerPedido(usuario);
                break;
            case 2:
                modificarPedido(usuario);
                break;
            case 3:
                cancelarPedido(usuario);
                break;
            case 4:
                printf("Saindo do menu de pedidos...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (optionPedido != 4);
}