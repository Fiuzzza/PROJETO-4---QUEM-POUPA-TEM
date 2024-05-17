#ifndef BANCO_H
#define BANCO_H

#define MAX_CLIENTES 1000
#define MAX_OPERACOES 100

typedef struct {
    float valor;
    char tipo_operacao[20]; 
} Transacao;

typedef struct {
    int numero_conta;
    float saldo;
    char tipo_conta[10]; 
    Transacao historico[MAX_OPERACOES]; 
    int num_operacoes; 
    char senha[20]; 
} ContaBancaria;

typedef struct {
    int id_cliente; 
    char nome[50];
    char endereco[100];
    ContaBancaria conta;
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
