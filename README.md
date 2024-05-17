# QuemPoupaTem - Sistema Bancário

QuemPoupaTem é um sistema bancário em C que gerencia clientes e suas contas (Comum e Plus). Oferece funcionalidades como criação, listagem, débito, depósito, transferência e extrato, com persistência de dados em arquivos binários.

## Funcionalidades

1. **Novo Cliente:** Criação de clientes.
2. **Apaga Cliente:** Remoção de clientes pelo CPF.
3. **Listar Clientes:** Exibição de todos os clientes.
4. **Débito:** Débito com verificação de CPF e senha.
5. **Depósito:** Depósito na conta do cliente.
6. **Extrato:** Geração de extrato em formato txt.
7. **Transferência:** Transferência entre contas com verificação.

## Compilação e Execução

Para compilar o projeto, use o comando `gcc -o quempoupatem main.c banco.c -Wall`. Após a compilação, execute o sistema com `./quempoupatem`.


