#include "banco.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Cliente clientes[MAX_CLIENTES];

int num_clientes = 0;


void novoCliente() {
    if (num_clientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido. Nao e possivel adicionar mais clientes.\n");
        return;
    }

    Cliente novo_cliente;
    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", novo_cliente.nome); 
    printf("Digite o CPF do cliente: ");
    scanf("%d", &novo_cliente.id_cliente);
    printf("Digite o tipo de conta (comum ou plus): ");
    scanf(" %[^\n]", novo_cliente.conta.tipo_conta);
    printf("Digite o valor inicial da conta: ");
    scanf("%f", &novo_cliente.conta.saldo);
    printf("Digite a senha do cliente: ");
    scanf(" %[^\n]", novo_cliente.conta.senha);

    clientes[num_clientes++] = novo_cliente;

    printf("Cliente adicionado com sucesso!\n");
}

void apagaCliente() {
    // Implementar lógica para apagar um cliente
}

void listarClientes() {
    // Implementar lógica para listar os clientes
}

void debito() {
    // Implementar lógica para realizar um débito na conta
}

void deposito() {
    // Implementar lógica para realizar um depósito na conta
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
