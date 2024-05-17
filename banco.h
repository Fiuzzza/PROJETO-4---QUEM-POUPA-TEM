#ifndef BANCO_H
#define BANCO_H

#define MAX_CLIENTES 1000
#define MAX_OPERACOES 100

typedef enum {
    DEPOSITO,
    DEBITO,
    TRANSFERENCIA_ENTRADA,
    TRANSFERENCIA_SAIDA
} TipoOperacao;

typedef struct {
    TipoOperacao tipo;
    int id_origem;
    int id_destino;
    float valor;
    float tarifa;
} Operacao;

typedef struct {
    char nome[50];
    int id_cliente;
    struct {
        char tipo_conta[10];
        float saldo;
        char senha[20];
        int num_operacoes;
        Operacao operacoes[MAX_OPERACOES];
    } conta;
} Cliente;

void novoCliente();
void apagaCliente();
void listarClientes();
void debito();
void deposito();
void extrato();
void transferenciaEntreContas();
void salvarDados();
void carregarDados();

#endif
