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

void loginAdm(char usuario[255]) {
    printf("Digite o seu usuario: ");
    scanf("%s", usuario);
    FILE *f = fopen("adms.txt", "r");
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
            menuAdm(usuario);

        } else {
            printf("Administrador nao encontrado.\n");

        }
    } else {
        printf("Erro ao abrir o arquivo de usuarios.\n");

    }
}

void menuEstatistica() {
    int opcao;

    printf("\n=== Estatísticas do Sistema ===\n");
    printf("1 - Top 5 alimentos mais bem avaliados\n");
    printf("2 - Top 5 alimentos mais mal avaliados\n");
    printf("3 - Total de usuários\n");
    printf("4 - Total de estabelecimentos\n");
    printf("5 - Total de alimentos cadastrados\n");
    printf("6 - Voltar\n");

    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    char usuario[255];

    switch (opcao) {
        case 1:
             top5BemAvaliados();
            break;
        case 2:
             top5MalAvaliados();
            break;
        case 3:
             visualizarUsuario();
            break;
        case 4:
            // contarEstabelecimentos();
            break;
        case 5:
            // contarAlimentos();
            break;
        case 6:
            printf("Voltando...\n");
            return;
        default:
            printf("Opcao invalida!\n");
    }
}

void menuEditarAlimentos() {
    int opcao;

    printf("\n=== Editar Alimentos ===\n");
    printf("1 - Cadastrar alimento\n");
    printf("2 - Excluir alimento\n");
    printf("3 - Voltar\n");

    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            cadastrarAlimento();
            break;
        case 2:
            excluirAlimento();
            break;
        case 3:
            printf("Voltando...\n");
            return;
        default:
            printf("Opcao invalida!\n");
    }
}

void cadastrarEstabelecimento() {

    FILE *f = fopen("estabelecimentos.txt", "r");
    char linha[255];
    int existe = 0;
    char estabelecimento[255];
    printf("Digite o estabelicmento que gostaria de adicionar: ");
    scanf("%s", estabelecimento);

    if (f != NULL) {
        while (fgets(linha, sizeof(linha), f)) {
            linha[strcspn(linha, "\n")] = '\0';
            if (strcmp(linha, estabelecimento) == 0) {
                existe = 1;
                break;
            }
        }
        fclose(f);
    }

    if (existe) {
        printf("Esse estabelecimento ja esta cadastrado.\n");
    } else {
        f = fopen("estabelecimentos.txt", "a");
        if (f == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }
        fprintf(f, "%s\n", estabelecimento);
        fclose(f);
        printf("Estabelecimento cadastrado com sucesso!\n");
    }
};

void visualizarUsuario() {
        char linha[255];
        char usuario[255];
        FILE *f = fopen("usuarios.txt", "r");

        if (f == NULL) {
            printf("Erro ao abrir usuarios.txt\n");
            return;
        }

        printf("\n=== Usuarios cadastrados ===\n");

        while (fgets(linha, sizeof(linha), f)) {
            linha[strcspn(linha, "\n")] = '\0';
            printf("%s\n", linha);
        }

        fclose(f);

        printf("\nPressione ENTER para voltar ao menu...");
        getchar();
        getchar();
    }

void cadastrarAlimento() {
    char comida[255];
    printf("Digite o alimento que gostaria de cadastrar: ");
    scanf("%s", comida);
    FILE *f = fopen("comidas.txt", "r");
    char linha[255];
    int existe = 0;

    if (f != NULL) {
        while (fgets(linha, sizeof(linha), f)) {
            linha[strcspn(linha, "\n")] = '\0';
            if (strcmp(linha, comida) == 0) {
                existe = 1;
                break;
            }
        }
        fclose(f);
    }

    if (existe) {
        printf("Esse alimento ja esta cadastrado.\n");
    } else {
        f = fopen("comidas.txt", "a");
        if (f == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }
        fprintf(f, "%s\n", comida);
        fclose(f);
        printf("Alimento cadastrado com sucesso!\n");
    }
};

void excluirAlimento() {
    char alimento[255];
    char linha[255];
    int encontrado = 0;

    FILE *f = fopen("comidas.txt", "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo de comidas.\n");
        return;
    }

    char comidas[200][255];
    int total = 0;

    while (fgets(comidas[total], sizeof(comidas[total]), f)) {
        comidas[total][strcspn(comidas[total], "\n")] = '\0';
        total++;
    }
    fclose(f);

    if (total == 0) {
        printf("Nao ha alimentos cadastrados.\n");
        return;
    }

    printf("\n=== Alimentos cadastrados ===\n");
    for (int i = 0; i < total; i++) {
        printf("%s\n", comidas[i]);
    }

    printf("\nDigite o alimento que deseja excluir: ");
    scanf("%s", alimento);

    for (int i = 0; i < total; i++) {
        if (strcmp(comidas[i], alimento) == 0) {
            encontrado = 1;
            for (int j = i; j < total - 1; j++) {
                strcpy(comidas[j], comidas[j + 1]);
            }
            total--;
            break;
        }
    }

    if (!encontrado) {
        printf("Alimento '%s' nao encontrado.\n", alimento);
        return;
    }

    f = fopen("comidas.txt", "w");
    if (f == NULL) {
        printf("Erro ao salvar alteracoes.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        fprintf(f, "%s\n", comidas[i]);
    }
    fclose(f);

    printf("Alimento '%s' excluido com sucesso!\n", alimento);
}

int menuAdm(char usuario[255]) {
    int opcao = 0;

    while (1) {
        printf("Bem-vindo Administrador!\n");
        printf("1- Visualizar todos os usuarios\n");
        printf("2- Editar alimentos\n");
        printf("3- Cadastrar estabelecimentos\n");
        printf("4- Visualizar estatisticas do sistema\n");
        printf("5- Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                visualizarUsuario(usuario);
                break;
            case 2:
                menuEditarAlimentos();
                break;
            case 3:
                cadastrarEstabelecimento();
                break;
            case 4:
                menuEstatistica();
                break;
            case 5:
                printf("Saindo do programa\n");
                return 0;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
}

void fazerLogin(char usuario[255]) {
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

        } else {
            printf("Usuario nao cadastrado.\n");

        }
    } else {
        printf("Erro ao abrir o arquivo de usuarios.\n");

    }
}

void listarInformacoes(char usuario[255]) {
    char arquivoUsuario[255];
    char linha[255];

    sprintf(arquivoUsuario, "historico_%s.txt", usuario);
    FILE *f = fopen(arquivoUsuario, "r");

    if (f != NULL) {
        while (fgets(linha, sizeof(linha), f)) {
            printf("%s", linha);
        }
    }
    else {
        printf("Erro ao abrir o arquivo.\n");
    }
}

void avaliarPedido(char usuario[255]) {


    char arquivoUsuario[300];
    sprintf(arquivoUsuario, "pedidos_%s.txt", usuario);

    FILE *f = fopen(arquivoUsuario, "r");
    if (!f) {
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

    printf("\n=== Pedidos ===\n");
    for (int i = 0; i < totalPedidos; i++) {
        printf("%s\n", pedidos[i]);
    }

    int idEscolhido;
    printf("\nDigite o ID do pedido que deseja avaliar: ");
    scanf("%d", &idEscolhido);

    int index = -1;
    for (int i = 0; i < totalPedidos; i++) {
        char idStr[10];
        sprintf(idStr, "%d", idEscolhido);
        if (strncmp(pedidos[i], idStr, strlen(idStr)) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("ID nao encontrado.\n");
        return;
    }

    int nota;
    do {
        printf("Dê uma nota ao pedido (1 a 5): ");
        scanf("%d", &nota);
    } while (nota < 1 || nota > 5);

    char novaLinha[600];
    sprintf(novaLinha, "%s, AVALIACAO=%d", pedidos[index], nota);
    strcpy(pedidos[index], novaLinha);

    FILE *fw = fopen(arquivoUsuario, "w");
    for (int i = 0; i < totalPedidos; i++) {
        fprintf(fw, "%s\n", pedidos[i]);
    }
    fclose(fw);

    FILE *ft = fopen("todas_avaliacoes.txt", "a"); // cria se não existir
    if (!ft) {
        printf("Erro ao criar todas_avaliacoes.txt\n");
        return;
    }

    char copia[600];
    strcpy(copia, pedidos[index]);

    char *token = strtok(copia, ","); // pula ID
    token = strtok(NULL, ",");
    while (token) {
        while (*token == ' ') token++;
        if (strncmp(token, "AVALIACAO=", 10) == 0) break;
        fprintf(ft, "%s,%d\n", token, nota); // cada alimento + nota
        token = strtok(NULL, ",");
    }

    fclose(ft);
    printf("Avaliação salva com sucesso para todos os usuários!\n");
}

void top5BemAvaliados() {
    char usuario[255];
    char arquivoAval[300];
    char comida[255];
    int nota;

    // Hash map simples
    char comidas[500][255];
    int notas[500] = {0};
    int qtd[500] = {0};
    int total = 0;

    FILE *u = fopen("usuarios.txt", "r");
    if (u == NULL) {
        printf("Erro ao abrir usuarios.txt\n");
        return;
    }

    while (fgets(usuario, sizeof(usuario), u)) {
        usuario[strcspn(usuario, "\n")] = '\0';

        sprintf(arquivoAval, "avaliacoes_%s.txt", usuario);
        FILE *f = fopen(arquivoAval, "r");
        if (f == NULL) continue;

        while (fscanf(f, "%[^;];%d\n", comida, &nota) == 2) {
            int found = 0;
            for (int i = 0; i < total; i++) {
                if (strcmp(comidas[i], comida) == 0) {
                    notas[i] += nota;
                    qtd[i]++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(comidas[total], comida);
                notas[total] = nota;
                qtd[total] = 1;
                total++;
            }
        }

        fclose(f);
    }
    fclose(u);

    // Ordenar
    for (int i = 0; i < total; i++) {
        for (int j = i + 1; j < total; j++) {
            float media_i = (float) notas[i] / qtd[i];
            float media_j = (float) notas[j] / qtd[j];

            if (media_j > media_i) {
                char tempC[255];
                int tempN, tempQ;

                strcpy(tempC, comidas[i]);
                strcpy(comidas[i], comidas[j]);
                strcpy(comidas[j], tempC);

                tempN = notas[i];
                notas[i] = notas[j];
                notas[j] = tempN;

                tempQ = qtd[i];
                qtd[i] = qtd[j];
                qtd[j] = tempQ;
            }
        }
    }

    printf("\n--- TOP 5 MELHORES AVALIADOS ---\n");
    for (int i = 0; i < 5 && i < total; i++) {
        printf("%d. %s (%.2f)\n", i + 1, comidas[i], (float) notas[i] / qtd[i]);
    }
}

void top5MalAvaliados() {
    FILE *f = fopen("todas_avaliacoes.txt", "r");
    if (!f) {
        printf("Nenhuma avaliacao encontrada.\n");
        return;
    }

    char linha[500], alimento[100];
    char nomes[200][100];
    int soma[200] = {0}, qtd[200] = {0};
    int total = 0;

    while (fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = '\0';

        char copia[500];
        strcpy(copia, linha);

        char *token = strtok(linha, ",");
        char *ultimo = NULL;

        while (token) {
            ultimo = token;
            token = strtok(NULL, ",");
        }

        int nota = atoi(ultimo);

        token = strtok(copia, ",");
        token = strtok(NULL, ",");

        while (token) {
            while (*token == ' ') token++;
            if (atoi(token) != 0) break;

            strcpy(alimento, token);
            int achou = 0;

            for (int i = 0; i < total; i++) {
                if (strcmp(nomes[i], alimento) == 0) {
                    soma[i] += nota;
                    qtd[i]++;
                    achou = 1;
                    break;
                }
            }

            if (!achou) {
                strcpy(nomes[total], alimento);
                soma[total] = nota;
                qtd[total] = 1;
                total++;
            }

            token = strtok(NULL, ",");
        }
    }

    fclose(f);

    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            float mi = (float)soma[i] / qtd[i];
            float mj = (float)soma[j] / qtd[j];
            if (mj < mi) {
                char tmpNome[100];
                int tmpSoma = soma[i];
                int tmpQtd = qtd[i];

                strcpy(tmpNome, nomes[i]);
                strcpy(nomes[i], nomes[j]);
                strcpy(nomes[j], tmpNome);

                soma[i] = soma[j];
                soma[j] = tmpSoma;

                qtd[i] = qtd[j];
                qtd[j] = tmpQtd;
            }
        }
    }

    printf("\n=== TOP 5 MAL AVALIADOS ===\n");

    for (int i = 0; i < total && i < 5; i++) {
        float media = (float)soma[i] / qtd[i];
        printf("%d - %s (%.2f)\n", i + 1, nomes[i], media);
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
    FILE *historico = fopen(arquivoUsuario, "a");
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
    fprintf(historico, "%s\n", comida);
    if (encontrou) {
        printf("O alimento '%s' foi encontrado!\n", comida);
    } else {
        printf("O alimento '%s' nao foi encontrado.\n", comida);
    }

    fclose(comidas);
    fclose(historico);
}

int menuInicial(char usuario[255]) {
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
                listarInformacoes(usuario);
                break;
            case 4:
                avaliarPedido(usuario);
                break;
            case 0:
                printf("Saindo...\n");
                return 0;
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
