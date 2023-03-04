#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funcoes.h"

// ---------------------------------------------------------------MENU---------------------------------------------------------------

#pragma region MENU
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
    printf("A sua escolha:");
    scanf("%d", &escolha);

    return escolha;
}

#pragma endregion

#pragma region MENU_UTILIZADOR
int menu_utilizador()
{
    int escolha;
    printf("O que pretende fazer?\n");
    printf("1- Listar os meios existentes.\n");
    printf("2- Carregamento de saldo.\n");
    printf("3- Consulta de saldo.\n");
    printf("4- Alteracao dos seus dados.\n");
    printf("A sua escolha:");
    scanf("%d", &escolha);
    system("cls");

    return escolha;
}
#pragma endregion

// -------------------------------------------------------------FIM-MENU-------------------------------------------------------------




// -------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS-------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS

// Ler ficheiro de texto, contendo informação sobre os clientes.
// Serão todos os dados, inseridos numa lista ligada, que de inicio é vazia.Meio* lerFicheiro_meios(Meio* inicio, FILE* dados_meios)
Meio* lerFicheiro_meios(Meio* inicio_meios, FILE* dados_meios)
{
    // Definição de variáveis.
    char linha[MAX_LINE_LEN];
    // Usando a função fgets, lemos a partir do ficheiro dados_meios todo o seu conteúdo, onde é armazenado em cada novo_nodo criado
    // Depois é atribuido ao inicio o valor de cada nodo criado, de seguida fechamos o ficheiro e por fim damos return da variavel inicio,
    // Contendo assim toda as informações e pointers necessários para criar a lista ligada.
    while (fgets(linha, MAX_LINE_LEN, dados_meios))
    {
        Meio* novo_nodo = malloc(sizeof(Meio));
        sscanf(linha,"%d;%[^;];%f;%f;%d;%s\n", &novo_nodo->codigo, novo_nodo->tipo, &novo_nodo->bateria, &novo_nodo->autonomia,&novo_nodo->custo, novo_nodo->geocodigo);
        novo_nodo->seguinte_meio = inicio_meios;
        inicio_meios = novo_nodo;
    }
    fclose(dados_meios);

    return inicio_meios;

}


// Apresenta na consola toda a informação existente sobre os clientes.
void listarMeios(Meio* inicio_meios)
{
    // Enquanto o pointer inicio_meios não for NULL (que esse mesmo está sempre a apontar para um valor de memória diferente na lista ligada)
    // É apresentada a informação dos meios.
    printf("Dados de meios disponiveis:\n------------------------------------------------------------------------------------------------------------------------\n");
    while (inicio_meios != NULL)
    {
        printf("Codigo:%d      Tipo:%s    Nivel Bateria:%.2f     Autonomia:%.2f     Custo:%d    Geocodigo:%s\n", inicio_meios->codigo, inicio_meios->tipo,
            inicio_meios->bateria, inicio_meios->autonomia, inicio_meios->custo, inicio_meios->geocodigo);
        inicio_meios = inicio_meios->seguinte_meio;
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}

//Escreve todos os dados inseridos sobre os clientes p
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
        fprintf(dados_meios, "%d;%s;%.2f;%.2f;%d;%s\n", inicio_meios->codigo, inicio_meios->tipo, inicio_meios->bateria, inicio_meios->autonomia,
            inicio_meios->custo, inicio_meios->geocodigo);
        inicio_meios = inicio_meios->seguinte_meio;
    }
    fclose(dados_meios);
}

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
        fprintf(dados_meios, "%d;%s;%.2f;%.2f;%s\n", inicio_meios->codigo, inicio_meios->tipo, inicio_meios->bateria, inicio_meios->autonomia,
            inicio_meios->geocodigo);
        inicio_meios = inicio_meios->seguinte_meio;
    }
    fclose(dados_meios);
}

Meio* existeMeio(Meio* inicio_meios, int cod)
{
    while (inicio_meios != NULL)
    {
        if (inicio_meios->codigo == cod)
        {
            printf("Ja existe um meio com o cod %d.\n", cod);
            return 0;
        }
        inicio_meios = inicio_meios->seguinte_meio;
    }
    if (inicio_meios == NULL)
        return 1;
}
#pragma endregion 

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS--------------------------------------------------------


// --------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES--------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES

// Ler ficheiro de texto, contendo informação sobre os clientes.
// Serão todos os dados, inseridos numa lista ligada, que de inicio é vazia.
Cliente* lerFicheiro_clientes(Cliente* inicio_clientes, FILE* dados_clientes)
{
    // Definição de variáveis.
    char linha[MAX_LINE_LEN];

    //Usando a função fgets, lemos a partir do ficheiro dados_clientes todo o seu conteúdo, onde é armazenado em cada novo_nodo criado
    //Depois é atribuido ao inicio o valor de cada nodo criado, de seguida fechamos o ficheiro e por fim damos return da variavel inicio,
    //Contendo assim toda as informações e pointers necessários para criar a lista ligada.

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

// Apresenta na consola toda a informação existente sobre os clientes.
void listarClientes(Cliente* inicio_clientes)
{
    printf("\nDados de Clientes:\n------------------------------------------------------------------------------------------------------------------------\n");
    // Enquanto o pointer inicio_clientes não for NULL (que esse mesmo está sempre a apontar para um valor de memória diferente na lista ligada)
    // É apresentada a informação dos clientes.
    while (inicio_clientes != NULL)
    {
        printf("Codigo:%d    Nome:%s     NIF:%d      Saldo:%d\n", inicio_clientes->codigo, inicio_clientes->nome, inicio_clientes->NIF, inicio_clientes->saldo);
        inicio_clientes = inicio_clientes->seguinte_cliente;
    }
    printf("------------------------------------------------------------------------------------------------------------------------");
}

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

int existeClienteCod(Cliente* inicio_clientes, int cod)
{
    while (inicio_clientes != NULL)
    {
        if (inicio_clientes->codigo == cod)
        {
            printf("Ja existe alguem com o codigo %d.\n", cod);
            return 0;
        }
        inicio_clientes = inicio_clientes->seguinte_cliente;
    }
    if (inicio_clientes == NULL)
        return 1;
}

int existeClienteNIF(Cliente* inicio_clientes, int NIF)
{
    while (inicio_clientes != NULL)
    {
        if (inicio_clientes->NIF == NIF)
        {
            printf("Ja existe alguem com o NIF %d.\n", NIF);
            return 0;
        }
        inicio_clientes = inicio_clientes->seguinte_cliente;
    }
    if (inicio_clientes == NULL)
        return 1;
}
#pragma endregion

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES----------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES----------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES
Gestor* lerFicheiro_gestores(Gestor* inicio_gestor, FILE* dados_gestor)
{
    char linha[MAX_LINE_LEN];
    while (fgets(linha, MAX_LINE_LEN, dados_gestor))
    {
        Gestor* novo_nodo = malloc(sizeof(struct registo_gestor));
        sscanf(linha, "%d;%[^;];%s\n", &novo_nodo->codigo, novo_nodo->nome, novo_nodo->senha);
        novo_nodo->seguinte_gestor = inicio_gestor;
        inicio_gestor = novo_nodo;
    }
    fclose(dados_gestor);
    return inicio_gestor;
}

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

int existeGestor(Gestor* inicio_gestores, int cod)
{
    while (inicio_gestores != NULL)
    {
        if (inicio_gestores->codigo == cod)
        {
            printf("Ja existe um gestor com o codigo %d", cod);
            break;
        }
        inicio_gestores = inicio_gestores->seguinte_gestor;
    }
    if (inicio_gestores == NULL)
        return 1;
}

#pragma endregion

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES----------------------------------------------------


// ---------------------------------------------------INICIO-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------
#pragma region INSERIR

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
    if (inicio_gestores->codigo == codigo_inserido && strcmp(inicio_gestores->senha, senha) ==0)
    {
        printf("Modo gestor ativado.\n");
        return 1;
    }
    else
    {
        printf("Senha ou codigo errados.\n");
        return 0;
    }
}

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

Gestor* inserirGestor(Gestor* inicio_gestor, int cod, char nome[50], char senha[50])
{
    int inserir = 0;
    while (inserir != 1)
    {
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
        inicio_gestor = inicio_gestor->seguinte_gestor;
    }
    return inicio_gestor;
}

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

// ---------------------------------------------------FIM-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------


// ---------------------------------------------------------------INICIO_OP_UTILIZADOR-----------------------------------------------------------------

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



// -----------------------------------------------------------------FIM_OP_UTILIZADOR-------------------------------------------------------------------
