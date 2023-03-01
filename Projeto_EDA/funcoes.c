#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

// ---------------------------------------------------------------MENU---------------------------------------------------------------

#pragma region MENU
int menu()
{
    int escolha;
    printf("O que pretende fazer?\n");
    printf("1- Listar os meios disponiveis.\n");
    printf("2- Escrever toda a informacao para o ficheiro meios em txt e binario.\n");
    printf("3- Listar os clientes existentes\n");
    printf("4- Escrever toda a informacao para o ficheiro clientes em txt e binario.\n");
    printf("5- Listar os gestores disponiveis.\n");
    printf("6- Escrever toda a informacao para o ficheiro gestores em txt e binario.\n");
    printf("7- Adicionar Meios.\n");
    printf("8- Adicionar clientes.\n");
    printf("9- Adicionar Gestores.\n");
    printf("10- Listar os meios disponiveis.\n");
    printf("11- Listar os meios disponiveis.\n");
    printf("A sua escolha:");
    scanf("%d", &escolha);

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
        sscanf(linha,"%d;%[^;];%f;%f;%s\n", &novo_nodo->codigo, novo_nodo->tipo, &novo_nodo->bateria, &novo_nodo->autonomia, novo_nodo->geocodigo);
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
        printf("Codigo:%d      Tipo:%s    Nivel Bateria:%.2f     Autonomia:%.2f     Geocodigo:%s\n", inicio_meios->codigo, inicio_meios->tipo,
            inicio_meios->bateria, inicio_meios->autonomia, inicio_meios->geocodigo);
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
        fprintf(dados_meios, "%d;%s;%.2f;%.2f;%s\n", inicio_meios->codigo, inicio_meios->tipo, inicio_meios->bateria, inicio_meios->autonomia,
            inicio_meios->geocodigo);
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
        sscanf(linha, "%d;%[^;];%[^;]\n", &novo_nodo->codigo, novo_nodo->nome, novo_nodo->senha);
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

#pragma endregion

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES----------------------------------------------------



// ---------------------------------------------------INICIO-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------

Meio* inserirMeio(Meio* inicio_meios)
{

}



// ---------------------------------------------------FIM-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------


//// listar na consola o conteúdo da lista ligada dos meios disponiveis.
//void listarMeios(Meio* inicio_meios)
//{
//    printf("Dados de meios disponiveis:\n------------------------------------------------------------\n");
//    while (inicio_meios != NULL)
//    {
//        printf("%d;%s;%.2f;%.2f\n", inicio_meios->codigo, inicio_meios->tipo,
//            inicio_meios->bateria, inicio_meios->autonomia);
//        inicio_meios = inicio_meios->seguinte_meio;
//    }
//}


// Determinar existência do 'codigo' na lista ligada 'inicio'
// devolve 1 se existir ou 0 caso contrário
//int existeMeio(Meio* inicio, int cod)
//{
//    while (inicio != NULL)
//    {
//        if (inicio->codigo == cod) return(1);
//        inicio = inicio->seguinte_meio;
//    }
//    return(0);
//}







