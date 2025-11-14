#include <stdio.h>
#include "FEIFood.h"

int main() {
    while (1) {
        printf("Bem vindo ao FEIFood\n");

        printf("1- Cadastrar-se\n");
        printf("2- Login Usuario\n");
        printf("3- Login Administrador\n");
        printf("4- Sair\n");

        int op = 0;
        printf("Escolha a opcao desejada: ");
        scanf("%d", &op);
        switch (op) {
            case 1:
                char usuario[255] = "";
                printf("Digite seu usuario: ");
                scanf("%s", usuario);
                cadastrarUsuario(usuario);
                continue;
            case 2:
                printf("Digite seu usuario: ");
                scanf("%s", usuario);
                fazerLogin(usuario);
                menuInicial(usuario);
                break;
            case 3:
                loginAdm(usuario);
            case 4:
                printf("Saindo do programa\n");
                break;
            default:
                printf("Opcao invalida, tente novamente\n");
                printf("\n");
                continue;

        }
        return 0;

    }


}