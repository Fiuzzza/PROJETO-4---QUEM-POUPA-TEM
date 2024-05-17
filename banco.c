#include "banco.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Cliente clientes[MAX_CLIENTES];

int num_clientes = 0;


void novoCliente() {
    if (num_clientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido. Não é possível adicionar mais clientes.\n");
        return;
    }

    Cliente novo_cliente;
    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", novo_cliente.nome);

    printf("Digite o CPF do cliente: ");
    scanf("%d", &novo_cliente.id_cliente);

    printf("Digite o tipo de conta (comum ou plus): ");
    scanf(" %[^\n]", novo_cliente.conta.tipo_conta);

    if (strcmp(novo_cliente.conta.tipo_conta, "comum") != 0 && strcmp(novo_cliente.conta.tipo_conta, "plus") != 0) {
        printf("Tipo de conta inválido. Deve ser 'comum' ou 'plus'.\n");
        return;
    }

    printf("Digite o valor inicial da conta: ");
    scanf("%f", &novo_cliente.conta.saldo);

    printf("Digite a senha do cliente: ");
    scanf(" %[^\n]", novo_cliente.conta.senha);

    novo_cliente.conta.num_operacoes = 0;
    clientes[num_clientes++] = novo_cliente;

    printf("Cliente adicionado com sucesso!\n");
}

void apagaCliente() {
    int cpf;
    printf("Digite o CPF do cliente a ser removido: ");
    scanf("%d", &cpf);

    int encontrado = 0;
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].id_cliente == cpf) {
            encontrado = 1;
            for (int j = i; j < num_clientes - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            num_clientes--;
            printf("Cliente com CPF %d removido com sucesso.\n", cpf);
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente com CPF %d não encontrado.\n", cpf);
    }
}

void listarClientes() {
    if (num_clientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    for (int i = 0; i < num_clientes; i++) {
        printf("Cliente %d:\n", i + 1);
        printf("Nome: %s\n", clientes[i].nome);
        printf("CPF: %d\n", clientes[i].id_cliente);
        printf("Tipo de Conta: %s\n", clientes[i].conta.tipo_conta);
        printf("Saldo: %.2f\n", clientes[i].conta.saldo);
        printf("\n");
    }
}

void debito() {
    int cpf;
    char senha[20];
    float valor;

    printf("Digite o CPF do cliente: ");
    scanf("%d", &cpf);

    printf("Digite a senha do cliente: ");
    scanf("%s", senha);

    printf("Digite o valor a ser debitado: ");
    scanf("%f", &valor);

    int encontrado = 0;
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].id_cliente == cpf) {
            encontrado = 1;
            if (strcmp(clientes[i].conta.senha, senha) == 0) {
                float limite_negativo = (strcmp(clientes[i].conta.tipo_conta, "comum") == 0) ? -1000.0 : -5000.0;
                float saldo_apos_debito = clientes[i].conta.saldo - valor;
                if (saldo_apos_debito >= limite_negativo) {
                    clientes[i].conta.saldo = saldo_apos_debito;
                    printf("Débito realizado com sucesso. Novo saldo: %.2f\n", clientes[i].conta.saldo);
                } else {
                    printf("Saldo insuficiente para realizar o débito. Limite negativo excedido.\n");
                }
            } else {
                printf("Senha incorreta.\n");
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente com CPF %d não encontrado.\n", cpf);
    }
}

void deposito() {
    int cpf;
    float valor;

    printf("Digite o CPF do cliente: ");
    scanf("%d", &cpf);

    printf("Digite o valor a ser depositado: ");
    scanf("%f", &valor);

    int encontrado = 0;
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].id_cliente == cpf) {
            encontrado = 1;
            clientes[i].conta.saldo += valor;
            printf("Depósito realizado com sucesso. Novo saldo: %.2f\n", clientes[i].conta.saldo);
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente com CPF %d não encontrado.\n", cpf);
    }
}
void extrato() {
    // Implementar lógica para exibir o extrato da conta
}

void transferenciaEntreContas() {
    // Implementar lógica para realizar uma transferência entre contas
}

void salvarDados() {
    // Implementar lógica para salvar os dados em arquivo binário
}

void carregarDados() {
    // Implementar lógica para carregar os dados de arquivo binário
}
