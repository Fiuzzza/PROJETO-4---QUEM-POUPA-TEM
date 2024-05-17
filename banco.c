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
    int cpf;
    char senha[20];

    printf("Digite o CPF do cliente: ");
    scanf("%d", &cpf);

    printf("Digite a senha do cliente: ");
    scanf("%s", senha);

    int encontrado = 0;
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].id_cliente == cpf) {
            encontrado = 1;
            if (strcmp(clientes[i].conta.senha, senha) == 0) {
                char nome_arquivo[50];
                sprintf(nome_arquivo, "extrato_%d.txt", cpf);
                FILE *arquivo = fopen(nome_arquivo, "w");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo para escrita.\n");
                    return;
                }

                fprintf(arquivo, "Extrato de Operacoes\n\n");
                fprintf(arquivo, "Cliente: %s\n", clientes[i].nome);
                fprintf(arquivo, "CPF: %d\n\n", clientes[i].id_cliente);
                fprintf(arquivo, "Historico de Operacoes:\n");

                for (int j = 0; j < clientes[i].conta.num_operacoes; j++) {
                    Operacao op = clientes[i].conta.operacoes[j];
                    fprintf(arquivo, "Operacao %d: ", j + 1);
                    if (op.tipo == DEPOSITO) {
                        fprintf(arquivo, "Deposito de %.2f\n", op.valor);
                    } else if (op.tipo == DEBITO) {
                        fprintf(arquivo, "Debito de %.2f (Tarifa: %.2f)\n", op.valor, op.tarifa);
                    } else if (op.tipo == TRANSFERENCIA_ENTRADA) {
                        fprintf(arquivo, "Transferencia recebida de %d no valor de %.2f\n", op.id_origem, op.valor);
                    } else if (op.tipo == TRANSFERENCIA_SAIDA) {
                        fprintf(arquivo, "Transferencia enviada para %d no valor de %.2f (Tarifa: %.2f)\n", op.id_destino, op.valor, op.tarifa);
                    }
                }

                fclose(arquivo);

                printf("Extrato gerado com sucesso. Verifique o arquivo %s\n", nome_arquivo);
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

void transferenciaEntreContas() {
    int cpf_origem, cpf_destino;
    char senha[20];
    float valor;

    printf("Digite o CPF da conta de origem: ");
    scanf("%d", &cpf_origem);

    printf("Digite a senha da conta de origem: ");
    scanf("%s", senha);

    printf("Digite o CPF da conta de destino: ");
    scanf("%d", &cpf_destino);

    printf("Digite o valor a ser transferido: ");
    scanf("%f", &valor);

    int encontrado_origem = 0;
    int index_origem = -1;
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].id_cliente == cpf_origem) {
            encontrado_origem = 1;
            index_origem = i;
            if (strcmp(clientes[i].conta.senha, senha) != 0) {
                printf("Senha incorreta para a conta de origem.\n");
                return;
            }
            break;
        }
    }

    if (!encontrado_origem) {
        printf("Conta de origem com CPF %d não encontrada.\n", cpf_origem);
        return;
    }

    if (clientes[index_origem].conta.saldo < valor) {
        printf("Saldo insuficiente na conta de origem.\n");
        return;
    }

    int encontrado_destino = 0;
    int index_destino = -1;
    for (int i = 0; i < num_clientes; i++) {
        if (clientes[i].id_cliente == cpf_destino) {
            encontrado_destino = 1;
            index_destino = i;
            break;
        }
    }

    if (!encontrado_destino) {
        printf("Conta de destino com CPF %d não encontrada.\n", cpf_destino);
        return;
    }

    clientes[index_origem].conta.saldo -= valor;
    clientes[index_destino].conta.saldo += valor;

    clientes[index_origem].conta.operacoes[clientes[index_origem].conta.num_operacoes].tipo = TRANSFERENCIA_SAIDA;
    clientes[index_origem].conta.operacoes[clientes[index_origem].conta.num_operacoes].id_destino = cpf_destino;
    clientes[index_origem].conta.operacoes[clientes[index_origem].conta.num_operacoes].valor = valor;
    clientes[index_origem].conta.operacoes[clientes[index_origem].conta.num_operacoes].tarifa = 0;
    clientes[index_origem].conta.num_operacoes++;

    clientes[index_destino].conta.operacoes[clientes[index_destino].conta.num_operacoes].tipo = TRANSFERENCIA_ENTRADA;
    clientes[index_destino].conta.operacoes[clientes[index_destino].conta.num_operacoes].id_origem = cpf_origem;
    clientes[index_destino].conta.operacoes[clientes[index_destino].conta.num_operacoes].valor = valor;
    clientes[index_destino].conta.num_operacoes++;

    printf("Transferência realizada com sucesso.\n");
}

void salvarDados() {
    FILE *arquivo = fopen("dados_clientes.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fwrite(&num_clientes, sizeof(int), 1, arquivo);

    for (int i = 0; i < num_clientes; i++) {
        fwrite(&clientes[i], sizeof(Cliente), 1, arquivo);
    }

    fclose(arquivo);
    printf("Dados dos clientes salvos com sucesso.\n");
}

void carregarDados() {
    FILE *arquivo = fopen("dados_clientes.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    fread(&num_clientes, sizeof(int), 1, arquivo);

    for (int i = 0; i < num_clientes; i++) {
        fread(&clientes[i], sizeof(Cliente), 1, arquivo);
    }

    fclose(arquivo);
    printf("Dados dos clientes carregados com sucesso.\n");
}
