#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

// ---------------------------------------------------------------MENU---------------------------------------------------------------

#pragma region MENU

// Menu inicial do programa. Retorna o valor escolhido pelo utilizador.
int menu()
{
    int escolha;
    printf("O que pretende fazer?\n");
    printf("1- Menu utilizador.\n");
    printf("2- Menu Gestor.\n");
    printf("A sua escolha:");
    scanf("%d", &escolha);
    system("cls");

    return escolha;
}
#pragma endregion 

#pragma region MENU_GESTOR

//Menu do gestor. Retorna a op��o escolhida pelo gestor, para executar uma tarefa.
int menu_gestor()
{
    int escolha;
    printf("O que pretende fazer?\n");
    printf("1- Listar os clientes existentes.\n");
    printf("2- Listar os gestores existentes.\n");
    printf("3- Listar os meios existentes.\n");
    printf("4- Adicionar Clientes.\n");
    printf("5- Adicionar Meios.\n");
    printf("6- Adicionar Gestor.\n");
    printf("7- Remover Meio.\n");
    printf("8- Remover Cliente.\n");
    printf("9- Remover Gestor.\n");
    printf("10- Historico de compras.\n");
    printf("0- Sair.\n");
    printf("A sua escolha:");
    scanf("%d", &escolha);

    return escolha;
}

#pragma endregion

#pragma region MENU_UTILIZADOR

//Menu do utilizador. Retorna o valor escolhido, para execu��o de uma tarefa.
int menu_utilizador()
{
    int escolha;
    printf("O que pretende fazer?\n");
    printf("1- Listar os meios existentes.\n");
    printf("2- Carregamento de saldo.\n");
    printf("3- Consulta de saldo.\n");
    printf("4- Alteracao dos seus dados.\n");
    printf("5- Alugar algum meio.\n");
    printf("A sua escolha:");
    scanf("%d", &escolha);
    system("cls");

    return escolha;
}
#pragma endregion

// -------------------------------------------------------------FIM-MENU-------------------------------------------------------------


// -------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTA��O DE MEIOS-------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTA��O DE MEIOS

// Ler ficheiro de texto, contendo informa��o sobre os meios.
// Ser�o todos os dados, inseridos numa lista ligada, que de inicio � vazia.
Meio* lerFicheiro_meios(Meio* inicio_meios, FILE* dados_meios)
{
    // Defini��o de vari�veis.
    char linha[MAX_LINE_LEN];
    // Usando a fun��o fgets, lemos a partir do ficheiro dados_meios todo o seu conte�do, onde � armazenado em cada novo_nodo criado
    // Depois � atribuido ao inicio o valor de cada nodo criado, de seguida fechamos o ficheiro e por fim damos return da variavel inicio,
    // Contendo assim toda as informa��es e pointers necess�rios para criar a lista ligada.
    while (fgets(linha, MAX_LINE_LEN, dados_meios))
    {
        Meio* novo_nodo = malloc(sizeof(Meio));
        sscanf(linha,"%d;%[^;];%f;%f;%d;%[^;];%d\n", &novo_nodo->codigo, novo_nodo->tipo, &novo_nodo->bateria, &novo_nodo->autonomia,&novo_nodo->custo, novo_nodo->geocodigo, &novo_nodo->ativo);
        novo_nodo->seguinte_meio = inicio_meios;
        inicio_meios = novo_nodo;
    }
    fclose(dados_meios);

    return inicio_meios;
}

// Apresenta na consola toda a informa��o existente sobre os clientes.
void listarMeios(Meio* inicio_meios)
{
    // Enquanto o pointer inicio_meios n�o for NULL (que esse mesmo est� sempre a apontar para um valor de mem�ria diferente na lista ligada)
    // � apresentada a informa��o dos meios.
    printf("Dados de meios disponiveis:\n------------------------------------------------------------------------------------------------------------------------\n");
    while (inicio_meios != NULL)
    {
        printf("Codigo:%d    Tipo:%s  Nivel Bateria:%.2f  Autonomia:%.2f  Custo:%d Geocodigo:%s Ativo:%d\n", inicio_meios->codigo, inicio_meios->tipo,
            inicio_meios->bateria, inicio_meios->autonomia, inicio_meios->custo, inicio_meios->geocodigo, inicio_meios->ativo);
        inicio_meios = inicio_meios->seguinte_meio;
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}

// Escreve todos os dados inseridos sobre os meios, em ficheiro de texto.
Meio* escreverFicheiro_meios(Meio* inicio_meios, FILE* dados_meios)
{
    if (inicio_meios == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return 0;
    }
    dados_meios = fopen("meios.txt", "wt");
    if (dados_meios == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicio_meios != NULL)
    {
        fprintf(dados_meios, "%d;%s;%.2f;%.2f;%d;%s;%d\n", inicio_meios->codigo, inicio_meios->tipo, inicio_meios->bateria, inicio_meios->autonomia,
            inicio_meios->custo, inicio_meios->geocodigo, inicio_meios->ativo);
        inicio_meios = inicio_meios->seguinte_meio;
    }
    fclose(dados_meios);
}

// Escreve todos os dados inseridos sobre os meios, em ficheiro bin�rio.
Meio* escreverFicheiro_meios_bin(Meio* inicio_meios, FILE* dados_meios)
{
    if (inicio_meios == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return 0;
    }
    dados_meios = fopen("meios.bin", "wb");
    if (dados_meios == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicio_meios != NULL)
    {
        fprintf(dados_meios, "%d;%s;%.2f;%.2f;%d;%s;%d\n", inicio_meios->codigo, inicio_meios->tipo, inicio_meios->bateria, inicio_meios->autonomia,
            inicio_meios->custo, inicio_meios->geocodigo, inicio_meios->ativo);
        inicio_meios = inicio_meios->seguinte_meio;
    }
    fclose(dados_meios);
}

// Verifica, consoante o endere�o de mem�ria de certo meio, se o seu c�digo � igual ao que foi inserido para um novo meio.
Meio* existeMeio(Meio* inicio_meios, int cod)
{
    while (inicio_meios != NULL)
    {
        if (inicio_meios->codigo == cod)
        {
            return 0;
        }
        inicio_meios = inicio_meios->seguinte_meio;
    }
    if (inicio_meios == NULL)
        return 1;
}

// Verifica cada meio existente, se o seu codigo do elemento que est� a verificar for maior que o elemento seguinte, ir� ser feita uma troca
// para ordenar todos os elementos da lista ligada por um valor crescente.
Meio* bubbleSortMeios(Meio* inicio_meios)
{
    Meio* atual, * seguinte;
    int b = 1, aux_codigo, aux_custo;
    float aux_bat, aux_aut;
    char aux_nome[50], aux_geo[50];
    while (b)
    {
        b = 0;
        atual = inicio_meios;
        while (atual->seguinte_meio != NULL)
        {
            seguinte = atual->seguinte_meio;
            if (atual->codigo > seguinte->codigo)
            {
                aux_codigo = atual->codigo;
                aux_bat = atual->bateria;
                aux_aut = atual->autonomia;
                aux_custo = atual->custo;
                strcpy(aux_nome, atual->tipo);
                strcpy(aux_geo, atual->geocodigo);

                atual->codigo = seguinte->codigo;
                atual->bateria = seguinte->bateria;
                atual->autonomia = seguinte->autonomia;
                atual->custo = seguinte->custo;
                strcpy(atual->tipo, seguinte->tipo);
                strcpy(atual->geocodigo, seguinte->geocodigo);

                seguinte->codigo = aux_codigo;
                seguinte->bateria = aux_bat;
                seguinte->autonomia = aux_aut;
                seguinte->custo = aux_custo;
                strcpy(seguinte->tipo, aux_nome);
                strcpy(seguinte->geocodigo, aux_geo);

                b = 1;
            }
            atual = seguinte;
        }
    }
    inicio_meios = atual;
    return inicio_meios;
}

#pragma endregion 

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTA��O DE MEIOS--------------------------------------------------------


// --------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTA��O DE CLIENTES--------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTA��O DE CLIENTES

// Ler ficheiro de texto, contendo informa��o sobre os clientes.
// Ser�o todos os dados, inseridos numa lista ligada, que de inicio � vazia.
Cliente* lerFicheiro_clientes(Cliente* inicio_clientes, FILE* dados_clientes)
{
    // Defini��o de vari�veis.
    char linha[MAX_LINE_LEN];

    //Usando a fun��o fgets, lemos a partir do ficheiro dados_clientes todo o seu conte�do, onde � armazenado em cada novo_nodo criado
    //Depois � atribuido ao inicio o valor de cada nodo criado, de seguida fechamos o ficheiro e por fim damos return da variavel inicio,
    //Contendo assim toda as informa��es e pointers necess�rios para criar a lista ligada.

    while (fgets(linha, MAX_LINE_LEN, dados_clientes))
    {
        Cliente* novo_nodo = malloc(sizeof(struct registo_clientes));
        sscanf(linha, "%d;%[^;];%d;%d\n", &novo_nodo->codigo, novo_nodo->nome, &novo_nodo->NIF, &novo_nodo->saldo);
        novo_nodo->seguinte_cliente = inicio_clientes;
        inicio_clientes = novo_nodo;
    }
    fclose(dados_clientes);
    return inicio_clientes;
}

// Apresenta na consola toda a informa��o existente sobre os clientes.
void listarClientes(Cliente* inicio_clientes)
{
    printf("\nDados de Clientes:\n------------------------------------------------------------------------------------------------------------------------\n");
    // Enquanto o pointer inicio_clientes n�o for NULL (que esse mesmo est� sempre a apontar para um valor de mem�ria diferente na lista ligada)
    // � apresentada a informa��o dos clientes.
    while (inicio_clientes != NULL)
    {
        printf("Codigo:%d    Nome:%s     NIF:%d      Saldo:%d\n", inicio_clientes->codigo, inicio_clientes->nome, inicio_clientes->NIF, inicio_clientes->saldo);
        inicio_clientes = inicio_clientes->seguinte_cliente;
    }
    printf("------------------------------------------------------------------------------------------------------------------------");
}

// Escreve todos os dados inseridos sobre os clientes, em ficheiro de texto.
Cliente* escreverFicheiro_clientes(Cliente* inicio_clientes, FILE* dados_clientes)
{
    if (inicio_clientes == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return 0;
    }
    dados_clientes = fopen("clientes.txt", "wt");
    if (dados_clientes == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicio_clientes != NULL)
    {
        fprintf(dados_clientes, "%d;%s;%d;%d\n", inicio_clientes->codigo, inicio_clientes->nome, inicio_clientes->NIF, inicio_clientes->saldo);
        inicio_clientes = inicio_clientes->seguinte_cliente;
    }

    fclose(dados_clientes);
}

// Escreve todos os dados inseridos sobre os clientes, em ficheiro bin�rio.
Cliente* escreverFicheiro_clientes_bin(Cliente* inicio_clientes, FILE* dados_clientes)
{
    if (inicio_clientes == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return 0;
    }
    dados_clientes = fopen("clientes.bin", "wb");
    if (dados_clientes == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicio_clientes != NULL)
    {
        fprintf(dados_clientes, "%d;%s;%d;%d\n", inicio_clientes->codigo, inicio_clientes->nome, inicio_clientes->NIF, inicio_clientes->saldo);
        inicio_clientes = inicio_clientes->seguinte_cliente;
    }
    fclose(dados_clientes);
}

// Verifica, consoante o endere�o de mem�ria de um certo utilizador, se o seu c�digo � igual ao que foi inserido para um novo utilizador.
int existeClienteCod(Cliente* inicio_clientes, int cod)
{
    Cliente* aux;
    while (inicio_clientes != NULL)
    {
        if (inicio_clientes->codigo == cod)
        {
            return 0;
        }
        inicio_clientes = inicio_clientes->seguinte_cliente;
    }
    if (inicio_clientes == NULL)
        return 1;
}

// Verifica, consoante o endere�o de mem�ria de um certo utilizador, se o seu NIF � igual ao que foi inserido para um novo utilizador.
int existeClienteNIF(Cliente* inicio_clientes, int NIF)
{
    while (inicio_clientes != NULL)
    {
        if (inicio_clientes->NIF == NIF)
        {
            return 0;
        }
        inicio_clientes = inicio_clientes->seguinte_cliente;
    }
    if (inicio_clientes == NULL)
        return 1;
}

// Verifica cada cliente existente, se o seu codigo do elemento que est� a verificar for maior que o elemento seguinte, ir� ser feita uma troca
// para ordenar todos os elementos da lista ligada por um valor crescente.
Cliente* bubbleSortClientes(Cliente* inicio_clientes) {
    Cliente* atual, * seguinte;
    int b = 1, aux_codigo, aux_NIF, aux_saldo;
    char aux_nome[50];
    while (b)
    {
        b = 0;
        atual = inicio_clientes;
        while (atual->seguinte_cliente != NULL)
        {
            seguinte = atual->seguinte_cliente;
            if (atual->codigo > seguinte->codigo)
            {
                aux_codigo = atual->codigo;
                strcpy(aux_nome, atual->nome);
                aux_NIF = atual->NIF;
                aux_saldo = atual->saldo;

                atual->codigo = seguinte->codigo;
                strcpy(atual->nome, seguinte->nome);
                atual->NIF= seguinte->NIF;
                atual->saldo = seguinte->saldo;

                seguinte->codigo = aux_codigo;
                strcpy(seguinte->nome, aux_nome);
                seguinte->NIF = aux_NIF;
                seguinte->saldo = aux_saldo;

                b = 1;
            }
            atual = seguinte;
        }
    }
    inicio_clientes = atual;
    return inicio_clientes;
}
#pragma endregion

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTA��O DE CLIENTES----------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTA��O DE GESTORES----------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTA��O DE GESTORES

// Ler ficheiro de texto, contendo informa��o sobre os gestores.
// Ser�o todos os dados, inseridos numa lista ligada, que de inicio � vazia.
Gestor* lerFicheiro_gestores(Gestor* inicio_gestor, FILE* dados_gestor)
{
    char linha[MAX_LINE_LEN];
    while (fgets(linha, MAX_LINE_LEN, dados_gestor))
    {
        Gestor* novo_nodo = malloc(sizeof(struct registo_gestor));
        sscanf(linha, "%d;%[^;];%[^\n]\n", &novo_nodo->codigo, novo_nodo->nome, novo_nodo->senha);
        novo_nodo->seguinte_gestor = inicio_gestor;
        inicio_gestor = novo_nodo;
    }
    fclose(dados_gestor);
    return inicio_gestor;
}

// Apresenta na consola toda a informa��o existente sobre os gestores.
void listarGestores(Gestor* inicio_gestor)
{
    printf("\nDados de Gestores:\n------------------------------------------------------------------------------------------------------------------------\n");

    while (inicio_gestor != NULL)
    {
        printf("Codigo:%d        Nome:%s \n", inicio_gestor->codigo, inicio_gestor->nome);
        inicio_gestor = inicio_gestor->seguinte_gestor;
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}

// Escreve todos os dados inseridos sobre os gestores, em ficheiro de texto.
Gestor* escreverFicheiro_gestores(Gestor* inicio_gestores, FILE* dados_gestores)
{
    if (inicio_gestores == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return 0;
    }
    dados_gestores = fopen("gestores.txt", "wt");
    if (dados_gestores == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicio_gestores != NULL)
    {
        fprintf(dados_gestores, "%d;%s;%s\n", inicio_gestores->codigo, inicio_gestores->nome,inicio_gestores->senha);
        inicio_gestores = inicio_gestores->seguinte_gestor;
    }

    fclose(dados_gestores);
}

// Escreve todos os dados inseridos sobre os gestores, em ficheiro bin�rio.
Gestor* escreverFicheiro_gestores_bin(Gestor* inicio_gestores, FILE* dados_gestores)
{
    if (inicio_gestores == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return 0;
    }
    dados_gestores = fopen("gestores.bin", "wb");
    if (dados_gestores == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicio_gestores != NULL)
    {
        fprintf(dados_gestores, "%d;%s;%s\n", inicio_gestores->codigo, inicio_gestores->nome,inicio_gestores->senha);
        inicio_gestores = inicio_gestores->seguinte_gestor;
    }
    fclose(dados_gestores);
}

// Verifica, consoante o endere�o de mem�ria de um certo gestor, se o seu c�digo � igual ao que foi inserido para um novo gestor.
int existeGestor(Gestor* inicio_gestores, int cod)
{
    while (inicio_gestores != NULL)
    {
        if (inicio_gestores->codigo == cod)
        {
            return 0;
        }
        inicio_gestores = inicio_gestores->seguinte_gestor;
    }
    if (inicio_gestores == NULL)
        return 1;
}

// Verifica cada gestor existente, se o seu codigo do elemento que est� a verificar for maior que o elemento seguinte, ir� ser feita uma troca
// para ordenar todos os elementos da lista ligada por um valor crescente.
Gestor* bubbleSortGestores(Gestor* inicio_gestor) {
    Gestor* atual, * seguinte;
    int aux_codigo, b = 1;
    char aux_senha[50], aux_nome[50];
    while (b)
    {
        b = 0;
        atual = inicio_gestor;
        while (atual->seguinte_gestor != NULL)
        {
            seguinte = atual->seguinte_gestor;
            if (atual->codigo > seguinte->codigo)
            {
                aux_codigo = atual->codigo;
                strcpy(aux_nome, atual->nome);
                strcpy(aux_senha, atual->senha);

                atual->codigo = seguinte->codigo;
                strcpy(atual->nome, seguinte->nome);
                strcpy(atual->senha, seguinte->senha);

                seguinte->codigo = aux_codigo;
                strcpy(seguinte->nome, aux_nome);
                strcpy(seguinte->senha, aux_senha);

                b = 1;
            }
            atual = seguinte;
        }
    }
    inicio_gestor = atual;
    return inicio_gestor;
}


#pragma endregion

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTA��O DE GESTORES----------------------------------------------------


// ---------------------------------------------------INICIO-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------
#pragma region INSERIR

// Fun��o para entrar em modo gestor, no qual � pedido um codigo e uma senha. Caso sejam iguais ao que est� no ficheiro � garantido o acesso
// a fun��es de gestor.
Gestor* modoGestor(Gestor* inicio_gestores) {
    int codigo_inserido;
    char senha[20];
    if (inicio_gestores == NULL)
    {
        printf("Ficheiro nao lido.\n");
        return 0;
    }
    printf("Insira o codigo de utilizador:");
    scanf("%d", &codigo_inserido);
    printf("Insira a senha:");
    scanf("%s", senha);
    while (inicio_gestores != NULL)
    {
        if (inicio_gestores->codigo == codigo_inserido && strcmp(inicio_gestores->senha, senha) == 0)
        {
            printf("Modo gestor ativado.\n");
            return 1;
        }
        else
        {
            inicio_gestores = inicio_gestores->seguinte_gestor;
        }
    }
    if (inicio_gestores == NULL)
    {
        printf("Codigo ou senha errados.\n");
        return 0;
    }
}

// Fun��o para inserir um novo meio el�trico, � pedido ao gestor na fun��o main, um novo codigo, nome, nivel bateria, autonomia, o seu custo 
// e a sua geolocaliza��o. De seguida � inserido no ultimo lugar da lista ligada dos meios, quando � o ultimo endere�o NULL.
Meio* inserirMeio(Meio* inicio_meios, int cod, char nome[50], float bat, float aut, int custo, char geo[50])
{
    int inserir = 0;
    while (inserir !=1)
    {
        inicio_meios = inicio_meios->seguinte_meio;
        if (inicio_meios->seguinte_meio == NULL)
        {
            Meio* novo_meio = malloc(sizeof(Meio));
            novo_meio->codigo = cod;
            strcpy(novo_meio->tipo, nome);
            novo_meio->bateria = bat;
            novo_meio->autonomia = aut;
            novo_meio->custo = custo;
            strcpy(novo_meio->geocodigo, geo);
            inicio_meios->seguinte_meio = novo_meio;
            novo_meio->seguinte_meio = NULL;
            inicio_meios = novo_meio;
            inserir = 1;
        }
    }
    return inicio_meios;
}

// Fun��o para inserir um novo cliente, � pedido ao gestor na fun��o main, um novo codigo, nome, NIF e saldo.  
// De seguida � inserido no ultimo lugar da lista ligada dos clientes, quando � o ultimo endere�o NULL.
Cliente* inserirCliente(Cliente* inicio_clientes, int cod, char nome[50], int NIF, int saldo)
{
    int inserir = 0;
    while (inserir != 1)
    {
        inicio_clientes = inicio_clientes->seguinte_cliente;
        if (inicio_clientes->seguinte_cliente == NULL)
        {
            Cliente* novo_cliente = malloc(sizeof(Cliente));
            novo_cliente->codigo = cod;
            strcpy(novo_cliente->nome, nome);
            novo_cliente->NIF = NIF;
            novo_cliente->saldo = saldo;
            inicio_clientes->seguinte_cliente = novo_cliente;
            novo_cliente->seguinte_cliente = NULL;
            inicio_clientes = novo_cliente;
            inserir = 1;
        }
    }
    return inicio_clientes;
}

// Fun��o para inserir um novo gestor, � pedido ao gestor na fun��o main, um novo codigo, nome e senha.  
// De seguida � inserido no ultimo lugar da lista ligada dos gestores, quando � o ultimo endere�o NULL.
Gestor* inserirGestor(Gestor* inicio_gestor, int cod, char nome[50], char senha[50])
{
    int inserir = 0;
    while (inserir != 1)
    {
        inicio_gestor = inicio_gestor->seguinte_gestor;
        if (inicio_gestor->seguinte_gestor == NULL)
        {
            Gestor* novo_gestor = malloc(sizeof(Gestor));
            novo_gestor->codigo = cod;
            strcpy(novo_gestor->nome, nome);
            strcpy(novo_gestor->senha, senha);
            //encryptSenha(novo_gestor,novo_gestor->senha);
            inicio_gestor->seguinte_gestor = novo_gestor;
            novo_gestor->seguinte_gestor = NULL;
            inicio_gestor = novo_gestor;
            inserir = 1;
        }
    }
    return inicio_gestor;
}

//Desenvolvimento.
int encryptSenha(Gestor* inicio_gestor, char senha[50])
{
    for (int i = 0; i < strlen(senha); i++)
    {
        senha[i] = senha[i] + 64;
    }
    puts(senha);
    printf("\n");
    return 1;
}

#pragma endregion 

#pragma region REMOVER

// Fun��o para remover algum meio, a partir do c�digo inserido pelo gestor. � removido o meio e de seguida � retornada toda a lista ligada
// com o meio removido.
Meio* removerMeio(Meio* inicio_meios, int cod)
{
    Meio* atual=inicio_meios, * anterior = inicio_meios, * aux;
    atual = inicio_meios;
    while ((atual != NULL) && (atual->codigo != cod))
    {
        anterior = atual;
        atual = atual->seguinte_meio;
    }
    if (atual == NULL)
    {
        return inicio_meios;
    }
    else
    {
        anterior->seguinte_meio = atual->seguinte_meio;
        free(atual);
        return(inicio_meios);
    }
}

// Fun��o para remover algum cliente, a partir do c�digo inserido pelo gestor. � removido o cliente e de seguida � retornada toda a lista ligada
// com o meio removido.
Cliente* removerCliente(Cliente* inicio_clientes, int cod)
{
    Cliente* atual = inicio_clientes, * anterior = inicio_clientes, * aux;
    atual = inicio_clientes;
    while ((atual != NULL) && (atual->codigo != cod))
    {
        anterior = atual;
        atual = atual->seguinte_cliente;
    }
    if (atual == NULL)
    {
        return inicio_clientes;
    }
    else
    {
        anterior->seguinte_cliente = atual->seguinte_cliente;
        free(atual);
        return(inicio_clientes);
    }
}

// Fun��o para remover algum gestor, a partir do c�digo inserido pelo gestor. � removido o gestor e de seguida � retornada toda a lista ligada
// com o meio removido.
Gestor* removerGestor(Gestor* inicio_gestores, int cod)
{
    Gestor* atual = inicio_gestores, * anterior = inicio_gestores, * aux;
    atual = inicio_gestores;
    while ((atual != NULL) && (atual->codigo != cod))
    {
        anterior = atual;
        atual = atual->seguinte_gestor;
    }
    if (atual == NULL)
    {
        return inicio_gestores;
    }
    else
    {
        anterior->seguinte_gestor = atual->seguinte_gestor;
        free(atual);
        return(inicio_gestores);
    }
}
#pragma endregion

// ---------------------------------------------------FIM-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------


// ---------------------------------------------------------------INICIO_OP_UTILIZADOR-----------------------------------------------------------------

// Fun��o para carregamento de saldo, de um certo utilizador.
// � pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes � possivel carregar o saldo desse mesmo utilizador.
Cliente* carregarSaldo(Cliente* inicio_clientes) {
    int codigo, NIF;
    printf("Introduza o seu codigo:");
    scanf("%d", &codigo);
    printf("Introduza o seu NIF:");
    scanf("%d", &NIF);
    while (inicio_clientes != NULL)
    {
        if (inicio_clientes->codigo == codigo && inicio_clientes->NIF == NIF)
        {
            int saldo_carregar;
            printf("O seu saldo: %d\n", inicio_clientes->saldo);
            printf("Quanto saldo deseja carregar?\n");
            printf("Digite:");
            scanf("%d", &saldo_carregar);
            if (saldo_carregar < 0)
                printf("Nao pode carregar saldo negativo.\n");
            inicio_clientes->saldo = saldo_carregar + inicio_clientes->saldo;
            printf("%d carregado com sucesso. Tem agora %d de saldo.\n", saldo_carregar, inicio_clientes->saldo);
            return 1;
        }
        inicio_clientes = inicio_clientes->seguinte_cliente;
    }
    if (inicio_clientes == NULL)
    {
        printf("Nao existe nenhum cliente com esse codigo.\n");
        return 0;
    }
    return inicio_clientes;
}

// Fun��o para consulta de saldo, de um certo utilizador.
// � pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes � possivel visualizar quando saldo est� dispon�vel.
Cliente* consultaSaldo(Cliente* inicio_clientes) {
    int codigo, NIF;
    printf("Introduza o seu codigo:");
    scanf("%d", &codigo);
    //printf("Introduza o seu NIF:");
    //scanf("%d", &NIF);
    while (inicio_clientes != NULL)
    {
        if (inicio_clientes->codigo == codigo /*&& inicio_clientes->NIF == NIF*/)
        {
            printf("Voce tem %d de saldo.\n", inicio_clientes->saldo);
            return 1;
        }
        inicio_clientes = inicio_clientes->seguinte_cliente;
    }
    return 0;
}

// Fun��o para altera��o de dados do cliente.
// � pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes � possivel fazer altera��o de nome, codigo e NIF.
Cliente* alterarDadosCliente(Cliente* inicio_clientes) {
    int codigo, NIF, novo_codigo, novo_NIF;
    char novo_nome[50];
    Cliente* aux = inicio_clientes;
    printf("Introduza o seu codigo:");
    scanf("%d", &codigo);
    //printf("Introduza o seu NIF:");
    //scanf("%d", &NIF);
    while (inicio_clientes != NULL)
    {
        if (inicio_clientes->codigo == codigo /*&& inicio_clientes->NIF == NIF*/)
        {
            printf("Este sao os seus dados.\n");
            int escolha;
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("Nome:%s     Codigo:%d       NIF:%d\n", inicio_clientes->nome, inicio_clientes->codigo, inicio_clientes->NIF);
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("O que deseja alterar?\n");
            printf("1- Nome.\n");
            printf("2- Codigo.\n");
            printf("3- NIF.\n");
            printf("4- Sair.\n");
            printf("A sua escolha:");
            scanf("%d", &escolha);
            switch (escolha)
            {
            case 1:
                getchar();
                printf("Insira o seu novo nome:");
                scanf("%[^\n]", novo_nome);
                strcpy(inicio_clientes->nome, novo_nome);
                printf("Nome alterado com sucesso para %s\n", inicio_clientes->nome);
                break;
            case 2:
                printf("Insira o seu novo codigo:");
                scanf("%d", &novo_codigo);
                if (existeClienteCod(aux, novo_codigo))
                {
                    inicio_clientes->codigo = novo_codigo;
                    printf("O seu novo codigo %d\n", inicio_clientes->codigo);
                }
                break;
            case 3:
                printf("Insira o seu novo NIF(deve conter 9 numeros e comecar por 192):");
                scanf("%d", &novo_NIF);
                if (novo_NIF <= 192000000 || novo_NIF >= 193000000)
                {
                    printf("Por favor tente de novo.\n");
                    break;
                }
                else
                {
                    if (existeClienteNIF(aux, novo_NIF))
                    {
                        inicio_clientes->NIF = novo_NIF;
                        printf("O seu novo NIF %d\n", inicio_clientes->NIF);
                    }
                }
            }
        }
        inicio_clientes = inicio_clientes->seguinte_cliente;
    }
}

Aluguer* realizarAluguer(Cliente* inicio_clientes, Aluguer* inicio_aluguer, Meio* inicio_meios)
{
    int meio_Alugar, codigo_utilizador, NIF;
    printf("Insira o seu codigo:");
    scanf("%d", &codigo_utilizador);
    if (existeClienteCod(inicio_clientes, codigo_utilizador)==0);
    {
        while (inicio_clientes->codigo != codigo_utilizador)
            inicio_clientes = inicio_clientes->seguinte_cliente;
        //printf("codigo e nome %d %s\n", inicio_clientes->codigo, inicio_clientes->nome);
        printf("Qual meio deseja alugar?\n");
        scanf("%d", &meio_Alugar);
        if (existeMeio(inicio_meios, meio_Alugar) == 0)
        {
            while (inicio_meios->codigo != meio_Alugar)
            {
                inicio_meios = inicio_meios->seguinte_meio;
            }
            printf("Nome do meio %s\n", inicio_meios->tipo);
            printf("O meio custa:%d\n", inicio_meios->custo);
            printf("Voce tem:%d\n", inicio_clientes->saldo);
            int escolha_compra;
            printf("Deseja comprar? 1-Sim/2-Nao\n");
            printf("A sua escolha:");
            scanf("%d", &escolha_compra);
            if (escolha_compra != 1)
            {
                return 0;
            }
            else
            {
                time_t dataCompra;
                time(&dataCompra);
                printf("Data da compra %s", ctime(&dataCompra));
                int inserir = 0;
                while (inserir != 1)
                {
                    inicio_aluguer = inicio_aluguer->seguinte_compra;
                    if (inicio_aluguer->seguinte_compra == NULL)
                    {
                        Aluguer* novo_nodo = malloc(sizeof(Aluguer));
                        novo_nodo->cod_comprador = inicio_clientes->codigo;
                        strcpy(novo_nodo->nome_comprador, inicio_clientes->nome);
                        strcpy(novo_nodo->data_compra, &dataCompra);
                        //encryptSenha(novo_gestor,novo_gestor->senha);
                        inicio_aluguer->seguinte_compra = novo_nodo;
                        novo_nodo->seguinte_compra = NULL;
                        inicio_aluguer = novo_nodo;
                        inserir = 1;
                    }
                }
            }
        }
    }
}

// -----------------------------------------------------------------FIM_OP_UTILIZADOR-------------------------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTA��O DE ALUGUER----------------------------------------------------

Aluguer* lerFicheiro_Aluguer(Aluguer* inicio_aluguer, FILE* dados_aluguer)
{
    char linha[MAX_LINE_LEN];
    while (fgets(linha, MAX_LINE_LEN, dados_aluguer))
    {
        Aluguer* novo_nodo = malloc(sizeof(Aluguer));
        sscanf(linha, "%d;%[^;];%[^\n]\n", &novo_nodo->cod_comprador, novo_nodo->data_compra, novo_nodo->nome_comprador);
        novo_nodo->seguinte_compra = inicio_aluguer;
        inicio_aluguer = novo_nodo;
    }
    fclose(dados_aluguer);
    return inicio_aluguer;
}

void listarAluguer(Aluguer* inicio_aluguer)
{
    printf("\nDados de Alugueres:\n------------------------------------------------------------------------------------------------------------------------\n");
    while (inicio_aluguer != NULL)
    {
        printf("Codigo:%d   Data de compra:%s       Nome:%s\n", inicio_aluguer->cod_comprador, inicio_aluguer->data_compra, inicio_aluguer->nome_comprador);
        inicio_aluguer = inicio_aluguer->seguinte_compra;
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}

Aluguer* bubbleSortAluguer(Aluguer* inicio_aluguer) {
    Aluguer* atual, * seguinte;
    int aux_codigo, b = 1;
    char aux_data[50], aux_comprador[50];
    while (b)
    {
        b = 0;
        atual = inicio_aluguer;
        while (atual->seguinte_compra != NULL)
        {
            seguinte = atual->seguinte_compra;
            if (atual->cod_comprador > seguinte->cod_comprador)
            {
                aux_codigo = atual->cod_comprador;
                strcpy(aux_comprador, atual->nome_comprador);
                strcpy(aux_data, atual->data_compra);

                atual->cod_comprador = seguinte->cod_comprador;
                strcpy(atual->nome_comprador, seguinte->nome_comprador);
                strcpy(atual->data_compra, seguinte->data_compra);

                seguinte->cod_comprador = aux_codigo;
                strcpy(seguinte->nome_comprador, aux_comprador);
                strcpy(seguinte->data_compra, aux_data);

                b = 1;
            }
            atual = seguinte;
        }
    }
    inicio_aluguer = atual;
    return inicio_aluguer;
}

// Escreve todos os dados sobre os alugueres, em ficheiro de texto.
Aluguer* escreverFicheiro_aluguer(Aluguer* inicio_aluguer, FILE* dados_aluguer)
{
    if (inicio_aluguer == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return 0;
    }
    dados_aluguer = fopen("historico_compras.txt", "wt");
    if (dados_aluguer == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicio_aluguer != NULL)
    {
        fprintf(dados_aluguer, "%d;%s;%s\n", inicio_aluguer->cod_comprador, inicio_aluguer->nome_comprador, inicio_aluguer->data_compra);
        inicio_aluguer = inicio_aluguer->seguinte_compra;
    }
    fclose(dados_aluguer);
}

// Escreve todos os dados sobre os alugueres, em ficheiro bin�rio.
Aluguer* escreverFicheiro_aluguer_bin(Aluguer* inicio_aluguer, FILE* dados_aluguer)
{
    if (inicio_aluguer == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return 0;
    }
    dados_aluguer = fopen("historico_compras.bin", "wb");
    if (dados_aluguer == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicio_aluguer != NULL)
    {
        fprintf(dados_aluguer, "%d;%s;%s\n", inicio_aluguer->cod_comprador, inicio_aluguer->nome_comprador, inicio_aluguer->data_compra);
        inicio_aluguer = inicio_aluguer->seguinte_compra;
    }
    fclose(dados_aluguer);
}

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTA��O DE ALUGUER----------------------------------------------------
