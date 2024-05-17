#include "banco.h"
#include <stdio.h>

int main() {
    int opcao;

    do {
        printf("\nMenu de Opcoes:\n");
        printf("1. Novo cliente\n");
        printf("2. Apagar cliente\n");
        printf("3. Listar clientes\n");
        printf("4. Debito\n");
        printf("5. Deposito\n");
        printf("6. Extrato\n");
        printf("7. Transferencia Entre Contas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                novoCliente();
                break;
            case 2:
                apagaCliente();
                break;
            case 3:
                listarClientes();
                break;
            case 4:
                debito();
                break;
            case 5:
                deposito();
                break;
            case 6:
                extrato();
                break;
            case 7:
                transferenciaEntreContas();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
