/*****************************************************************//**
 * @file   funcoes.c
 * @brief  Execucao de funcoes
 *
 * @author Marco Macedo
 * @date   February 2023
 *********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include "funcoes.h"


// ---------------------------------------------------------------MENU---------------------------------------------------------------

#pragma region menu

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

#pragma region menuGestor

//Menu do gestor. Retorna a opção escolhida pelo gestor, para executar uma tarefa.
int menuGestor()
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
    printf("11- Alterar dados gestor.\n");
    printf("12- Alterar dados meios.\n");
    printf("13- Alterar dados cliente.\n");
    printf("14- Media autonomia.\n");
    printf("15- Listar transacoes.\n");
    printf("16- Adicionar Adjacentes.\n");
    printf("17- Inserir Vertice.\n");
    printf("0- Sair.\n");
    printf("A sua escolha:");
    scanf("%d", &escolha);

    return escolha;
}

#pragma endregion

#pragma region menuUtilizador

//Menu do utilizador. Retorna o valor escolhido, para execução de uma tarefa.
int menuUtilizador()
{
    int escolha;
    printf("O que pretende fazer?\n");
    printf("1- Listar os meios existentes.\n");
    printf("2- Carregamento de saldo.\n");
    printf("3- Consulta de saldo.\n");
    printf("4- Alteracao dos seus dados.\n");
    printf("5- Alugar algum meio.\n");
    printf("6- Listar por geocodigo.\n");
    printf("7- Calcular distancias.\n");
    printf("8- Listar adjacentes.\n");
    printf("9- Localizacao de um meio.\n");
    printf("0- Sair.\n");
    printf("A sua escolha:");
    scanf("%d", &escolha);
    system("cls");

    return escolha;
}
#pragma endregion

// -------------------------------------------------------------FIM-MENU-------------------------------------------------------------


// -------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS-------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS
 /**
  * Ler ficheiro de texto, contendo informação sobre os meios.
  * Serão todos os dados, inseridos numa lista ligada, que de inicio é vazia.
  * 
  * \FunctionName lerFicheiroMeios
  * \param inicioMeios
  * \param dadosMeios
  * \return 
  */
Meio* lerFicheiroMeios(Meio* inicioMeios, FILE* dadosMeios)
{
    // Definição de variáveis.
    char linha[tamanhoLinha];
    // Usando a função fgets, lemos a partir do ficheiro dadosMeios todo o seu conteúdo, onde é armazenado em cada novoNodo criado
    // Depois é atribuido ao inicio o valor de cada nodo criado, de seguida fechamos o ficheiro e por fim damos return da variavel inicio,
    // Contendo assim toda as informações e pointers necessários para criar a lista ligada.
    while (fgets(linha, tamanhoLinha, dadosMeios))
    {
        // Enquanto é possivel obter texto do ficheiro dadosMeios, irá ser criado um novo espaço na memória para a struct meios
        // A cada iteração é atribuido todo o conteudo obtido ao inicioMeios, criando assim uma lista ligada.
        Meio* novoNodo = malloc(sizeof(Meio));
        if (novoNodo == NULL)
        {
            return 0;
        }
        sscanf(linha, "%d;%[^;];%f;%f;%d;%[^;];%d\n", &novoNodo->codigo, novoNodo->tipo, &novoNodo->bateria, &novoNodo->autonomia, &novoNodo->custo, novoNodo->geocodigo, &novoNodo->ativo);
        // O seguinte valor de memória é igual a inicioMeios que foi inicializado a NULL, para de seguida ser possivel atribuir outro elemento da lista ligada.
        novoNodo->seguinteMeio = inicioMeios;
        // Inicio_meios vai obter toda a informação que foi lida por novoNodo
        inicioMeios = novoNodo;
    }
    fclose(dadosMeios);
    return inicioMeios;
}

/**
 * Apresenta na consola toda a informação existente sobre os clientes.
 * 
 * \FunctionName listarMeios
 * \param inicioMeios
 * \return ResFuncoes
 */
ResFuncoes listarMeios(Meio* inicioMeios)
{
    system("cls");
    if (inicioMeios == NULL)
    {
        return meiosNaoExistem;
    }
    else
    {
        // Enquanto o pointer inicioMeios não for NULL (que esse mesmo está sempre a apontar para um valor de memória diferente na lista ligada)
        // É apresentada a informação dos meios.
        printf("Dados de meios disponiveis:\n------------------------------------------------------------------------------------------------------------------------\n\n");
        while (inicioMeios != NULL)
        {
            printf("Codigo:%d    Tipo:%s  Nivel Bateria:%.2f  Autonomia:%.2f  Custo:%d Geocodigo:%s Ativo:%d\n", inicioMeios->codigo, inicioMeios->tipo,
                inicioMeios->bateria, inicioMeios->autonomia, inicioMeios->custo, inicioMeios->geocodigo, inicioMeios->ativo);
            inicioMeios = inicioMeios->seguinteMeio;
        }
        printf("------------------------------------------------------------------------------------------------------------------------\n\n");
    }
    return SUCESSO;
}

/**
 * Escreve todos os dados inseridos sobre os meios, em ficheiro de texto.
 * 
 * \FunctionName escreverFicheiroMeios
 * \param inicioMeios
 * \param dadosMeios
 * \return Meio
 */
Meio* escreverFicheiroMeios(Meio* inicioMeios, FILE* dadosMeios)
{
    dadosMeios = fopen("meios.txt", "wt");
    if (dadosMeios == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicioMeios != NULL)
    {
        fprintf(dadosMeios, "%d;%s;%.2f;%.2f;%d;%s;%d\n", inicioMeios->codigo, inicioMeios->tipo, inicioMeios->bateria, inicioMeios->autonomia,
            inicioMeios->custo, inicioMeios->geocodigo, inicioMeios->ativo);
        inicioMeios = inicioMeios->seguinteMeio;
    }
    fclose(dadosMeios);
    return 1;
}

/**
 * Escreve todos os dados inseridos sobre os meios, em ficheiro binário.
 * 
 * \FunctionName escreverFicheiroMeiosBin
 * \param inicioMeios
 * \param dadosMeios
 * \return Meio
 */
Meio* escreverFicheiroMeiosBin(Meio* inicioMeios, FILE* dadosMeios)
{
    dadosMeios = fopen("meios.bin", "wb");
    if (dadosMeios == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicioMeios != NULL)
    {
        fprintf(dadosMeios, "%d;%s;%.2f;%.2f;%d;%s;%d\n", inicioMeios->codigo, inicioMeios->tipo, inicioMeios->bateria, inicioMeios->autonomia,
            inicioMeios->custo, inicioMeios->geocodigo, inicioMeios->ativo);
        inicioMeios = inicioMeios->seguinteMeio;
    }
    fclose(dadosMeios);
    return 1;
}

/**
 * Verifica, consoante o endereço de memória de certo meio, se o seu código é igual ao que foi inserido para um novo meio.
 * 
 * \FunctionName existeMeio
 * \param inicioMeios
 * \param cod
 * \return Meio
 */
Meio* existeMeio(Meio* inicioMeios, int cod)
{
    if (inicioMeios == NULL)
        return 1;
    while (inicioMeios != NULL)
    {
        if (inicioMeios->codigo == cod)
        {
            return 0;
        }
        inicioMeios = inicioMeios->seguinteMeio;
    }
    return 1;
}

/**
 * Verifica cada meio existente, se o seu valor de autonomia do elemento que está a verificar for maior que o elemento seguinte, irá ser feita uma troca
 * para ordenar todos os elementos da lista ligada por um valor decrescente a nivel de autonomia.
 * \FunctionName bubbleSortMeios
 * \param inicioMeios
 * \return Meio
 */
Meio* bubbleSortMeios(Meio* inicioMeios)
{
    Meio* atual, * seguinte;
    int b = 1, auxCodigo, auxCusto, auxAtivo;
    float auxBat, auxAutonomia;
    char auxNome[50], auxGeo[50];

    while (b)
    {
        b = 0;
        atual = inicioMeios;
        if (atual == NULL)
        {
            return 0;
        }
        while (atual->seguinteMeio != NULL)
        {
            seguinte = atual->seguinteMeio;
            if (atual->autonomia < seguinte->autonomia)
            {
                auxCodigo = atual->codigo;
                auxBat = atual->bateria;
                auxAutonomia = atual->autonomia;
                auxCusto = atual->custo;
                strcpy(auxNome, atual->tipo);
                strcpy(auxGeo, atual->geocodigo);
                auxAtivo = atual->ativo;

                atual->codigo = seguinte->codigo;
                atual->bateria = seguinte->bateria;
                atual->autonomia = seguinte->autonomia;
                atual->custo = seguinte->custo;
                strcpy(atual->tipo, seguinte->tipo);
                strcpy(atual->geocodigo, seguinte->geocodigo);
                atual->ativo = seguinte->ativo;

                seguinte->codigo = auxCodigo;
                seguinte->bateria = auxBat;
                seguinte->autonomia = auxAutonomia;
                seguinte->custo = auxCusto;
                strcpy(seguinte->tipo, auxNome);
                strcpy(seguinte->geocodigo, auxGeo);
                seguinte->ativo = auxAtivo;

                b = 1;
            }
            atual = seguinte;
        }
    }
    inicioMeios = atual;
    return inicioMeios;
}

//Devolve a media da autonimia de todos os meios existentes.
/**
 * 
 * 
 * \FunctionName mediaAutonomia
 * \param inicioMeios
 * \return 1
 */
float mediaAutonomia(Meio* inicioMeios)
{
    int tamanho = 0;
    float resultado = 0;
    if (inicioMeios == NULL)
    {
        printf("Lista ligada vazia.\n");
        Sleep(2000);
        system("cls");
        return 0;
    }
    while (inicioMeios != NULL)
    {
        resultado += inicioMeios->autonomia;
        inicioMeios = inicioMeios->seguinteMeio;
        tamanho++;
    }
    resultado = resultado / tamanho;
    printf("A media de autonomia de todos os meios e de: %.2f\n", resultado);
    return 1;
}

/**
 * Colocar todos os meios com o campo recolhido a 0.
 * 
 * \FunctionName recolhidoMeios
 * \param inicioMeios
 */
void recolhidoMeios(Meio* inicioMeios)
{
    Meio* aux = inicioMeios;
    while (aux != NULL)
    {
        aux->recolhido = 0;
        aux = aux->seguinteMeio;
    }
}

#pragma endregion 

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS--------------------------------------------------------


// --------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES--------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES

/**
 * Ler ficheiro de texto, contendo informação sobre os clientes.
 * Serão todos os dados, inseridos numa lista ligada, que de inicio é vazia.
 * \FunctionName lerFicheiroClientes
 * \param inicioClientes
 * \param dadosClientes
 * \return Cliente*
 */
Cliente* lerFicheiroClientes(Cliente* inicioClientes, FILE* dadosClientes)
{
    // Definição de variáveis.
    char linha[tamanhoLinha];

    //Usando a função fgets, lemos a partir do ficheiro dadosClientes todo o seu conteúdo, onde é armazenado em cada novoNodo criado
    //Depois é atribuido ao inicio o valor de cada nodo criado, de seguida fechamos o ficheiro e por fim damos return da variavel inicio,
    //Contendo assim toda as informações e pointers necessários para criar a lista ligada.

    while (fgets(linha, tamanhoLinha, dadosClientes))
    {
        Cliente* novoNodo = malloc(sizeof(Cliente));
        if (novoNodo == NULL)
        {
            return 0;
        }
        sscanf(linha, "%d;%[^;];%d;%d;%s\n", &novoNodo->codigo, novoNodo->nome, &novoNodo->NIF, &novoNodo->saldo, novoNodo->geocodigo);
        novoNodo->seguinteCliente = inicioClientes;
        inicioClientes = novoNodo;
    }
    fclose(dadosClientes);
    return inicioClientes;
}

/**
 * Apresenta na consola toda a informação existente sobre os clientes.
 * 
 * \FunctionName listarClientes
 * \param inicioClientes
 */
void listarClientes(Cliente* inicioClientes)
{
    system("cls");
    if (inicioClientes == NULL)
    {
        printf("Nao existem clientes.\n");
        return 0;
    }
    else
    {
        printf("Dados de Clientes:\n------------------------------------------------------------------------------------------------------------------------\n");
        // Enquanto o pointer inicioClientes não for NULL (que esse mesmo está sempre a apontar para um valor de memória diferente na lista ligada)
        // É apresentada a informação dos clientes.
        while (inicioClientes != NULL)
        {
            printf("Codigo:%d    Nome:%s     NIF:%d      Saldo:%d   Geocodigo:%s\n", inicioClientes->codigo, inicioClientes->nome, inicioClientes->NIF, inicioClientes->saldo, inicioClientes->geocodigo);
            inicioClientes = inicioClientes->seguinteCliente;
        }
        printf("------------------------------------------------------------------------------------------------------------------------");
    }
}

// 
/**
 * Escreve todos os dados inseridos sobre os clientes, em ficheiro de texto.
 * 
 * \FunctionName escreverFicheiroClientes
 * \param inicioClientes
 * \param dadosClientes
 * \return Cliente
 */
Cliente* escreverFicheiroClientes(Cliente* inicioClientes, FILE* dadosClientes)
{
    dadosClientes = fopen("clientes.txt", "wt");
    if (dadosClientes == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicioClientes != NULL)
    {
        fprintf(dadosClientes, "%d;%s;%d;%d;%s\n", inicioClientes->codigo, inicioClientes->nome, inicioClientes->NIF, inicioClientes->saldo, inicioClientes->geocodigo);
        inicioClientes = inicioClientes->seguinteCliente;
    }
    fclose(dadosClientes);
    return 1;
}

/**
 *  Escreve todos os dados inseridos sobre os clientes, em ficheiro binário.
 * 
 * \FunctionName escreverFicheiroClientesBin
 * \param inicioClientes
 * \param dadosClientes
 * \return 
 */
Cliente* escreverFicheiroClientesBin(Cliente* inicioClientes, FILE* dadosClientes)
{
    dadosClientes = fopen("clientes.bin", "wb");
    if (dadosClientes == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicioClientes != NULL)
    {
        fprintf(dadosClientes, "%d;%s;%d;%d;%s\n", inicioClientes->codigo, inicioClientes->nome, inicioClientes->NIF, inicioClientes->saldo, inicioClientes->geocodigo);
        inicioClientes = inicioClientes->seguinteCliente;
    }
    fclose(dadosClientes);
    return 1;
}

/**
 * Verifica, consoante o endereço de memória de um certo utilizador, se o seu código é igual ao que foi inserido para um novo utilizador.
 * 
 * \FunctionName existeClienteCod
 * \param inicioClientes
 * \param cod
 * \return int
 */
int existeClienteCod(Cliente* inicioClientes, int cod)
{
    while (inicioClientes != NULL)
    {
        if (inicioClientes->codigo == cod)
        {
            return 0;
        }
        inicioClientes = inicioClientes->seguinteCliente;
    }
    if (inicioClientes == NULL)
        return 1;
}

/**
 *  Verifica, consoante o endereço de memória de um certo utilizador, se o seu NIF é igual ao que foi inserido para um novo utilizador.
 * 
 * \FunctionName existeClienteNIF
 * \param inicioClientes
 * \param NIF
 * \return int
 */
int existeClienteNIF(Cliente* inicioClientes, int NIF)
{
    while (inicioClientes != NULL)
    {
        if (inicioClientes->NIF == NIF)
        {
            return 0;
        }
        inicioClientes = inicioClientes->seguinteCliente;
    }
    if (inicioClientes == NULL)
        return 1;
}

/**
 * Verifica cada cliente existente, se o seu codigo do elemento que está a verificar for maior que o elemento seguinte, irá ser feita uma troca
 * para ordenar todos os elementos da lista ligada por um valor crescente.
 * \FunctionName bubbleSortClientes
 * \param inicioClientes
 * \return Cliente
 */
Cliente* bubbleSortClientes(Cliente* inicioClientes) {
    Cliente* atual, * seguinte;
    int b = 1, auxCodigo, auxNIF, auxSaldo;
    char auxNome[50], auxGeocodigo[100];
    while (b)
    {
        b = 0;
        atual = inicioClientes;
        if (atual == NULL)
        {
            return 0;
        }
        while (atual->seguinteCliente != NULL)
        {
            seguinte = atual->seguinteCliente;
            if (atual->codigo > seguinte->codigo)
            {
                auxCodigo = atual->codigo;
                strcpy(auxNome, atual->nome);
                auxNIF = atual->NIF;
                auxSaldo = atual->saldo;
                strcpy(auxGeocodigo, atual->geocodigo);

                atual->codigo = seguinte->codigo;
                strcpy(atual->nome, seguinte->nome);
                atual->NIF = seguinte->NIF;
                atual->saldo = seguinte->saldo;
                strcpy(atual->geocodigo, seguinte->geocodigo);

                seguinte->codigo = auxCodigo;
                strcpy(seguinte->nome, auxNome);
                seguinte->NIF = auxNIF;
                seguinte->saldo = auxSaldo;
                strcpy(seguinte->geocodigo, auxGeocodigo);

                b = 1;
            }
            atual = seguinte;
        }
    }
    inicioClientes = atual;
    return inicioClientes;
}
#pragma endregion

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES----------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES----------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES

/**
 * Ler ficheiro de texto, contendo informação sobre os gestores.
 * Serão todos os dados, inseridos numa lista ligada, que de inicio é vazia.
 * \FunctionName lerFicheiroGestores
 * \param inicioGestor
 * \param dadosGestor
 * \return Gestor
 */
Gestor* lerFicheiroGestores(Gestor* inicioGestor, FILE* dadosGestor)
{
    char linha[tamanhoLinha];
    while (fgets(linha, tamanhoLinha, dadosGestor))
    {
        Gestor* novoNodo = malloc(sizeof(Gestor));
        if (novoNodo == NULL)
        {
            return 0;
        }
        sscanf(linha, "%d;%[^;];%[^;];%d;%s\n", &novoNodo->codigo, novoNodo->nome, novoNodo->senha, &novoNodo->encriptado, novoNodo->areaResponsavel);
        novoNodo->seguinteGestor = inicioGestor;
        inicioGestor = novoNodo;
    }
    fclose(dadosGestor);
    return inicioGestor;
}

/**
 * Apresenta na consola toda a informação existente sobre os gestores.
 * 
 * \FunctionName listarGestores
 * \param inicioGestor
 */
void listarGestores(Gestor* inicioGestor)
{
    system("cls");
    if (inicioGestor == NULL)
    {
        printf("Nao existem gestores, por favor registe-se.\n");
        return 0;
    }
    else
    {
        printf("Dados de Gestores:\n------------------------------------------------------------------------------------------------------------------------\n");
        while (inicioGestor != NULL)
        {
            printf("Codigo:%d        Nome:%s    Area:%s\n", inicioGestor->codigo, inicioGestor->nome, inicioGestor->areaResponsavel);
            inicioGestor = inicioGestor->seguinteGestor;
        }
        printf("------------------------------------------------------------------------------------------------------------------------\n");
    }

}

/**
 * Escreve todos os dados inseridos sobre os gestores, em ficheiro de texto.
 * 
 * \FunctionName escreverFicheiroGestores
 * \param inicioGestores
 * \param dadosGestores
 * \return Gestor
 */
Gestor* escreverFicheiroGestores(Gestor* inicioGestores, FILE* dadosGestores)
{
    dadosGestores = fopen("gestores.txt", "wt");
    if (dadosGestores == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicioGestores != NULL)
    {
        fprintf(dadosGestores, "%d;%s;%s;%d;%s\n", inicioGestores->codigo, inicioGestores->nome, inicioGestores->senha, inicioGestores->encriptado, inicioGestores->areaResponsavel);
        inicioGestores = inicioGestores->seguinteGestor;
    }

    fclose(dadosGestores);
}

/**
 * Escreve todos os dados inseridos sobre os gestores, em ficheiro binário.
 * 
 * \FunctionName escreverFicheiroGestoresBin
 * \param inicioGestores
 * \param dadosGestores
 * \return Gestor
 */
Gestor* escreverFicheiroGestoresBin(Gestor* inicioGestores, FILE* dadosGestores)
{
    dadosGestores = fopen("gestores.bin", "wb");
    if (dadosGestores == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicioGestores != NULL)
    {
        fprintf(dadosGestores, "%d;%s;%s;%d;%s\n", inicioGestores->codigo, inicioGestores->nome, inicioGestores->senha, inicioGestores->encriptado, inicioGestores->areaResponsavel);
        inicioGestores = inicioGestores->seguinteGestor;
    }
    fclose(dadosGestores);
}

/**
 * Verifica, consoante o endereço de memória de um certo gestor, se o seu código é igual ao que foi inserido para um novo gestor.
 * 
 * \FunctionName existeGestor
 * \param inicioGestores
 * \param cod
 * \return int
 */
int existeGestor(Gestor* inicioGestores, int cod)
{
    while (inicioGestores != NULL)
    {
        if (inicioGestores->codigo == cod)
        {
            return 0;
        }
        inicioGestores = inicioGestores->seguinteGestor;
    }
    if (inicioGestores == NULL)
        return 1;
}

/**
 * Verifica cada gestor existente, se o seu codigo do elemento que está a verificar for maior que o elemento seguinte, irá ser feita uma troca
 * para ordenar todos os elementos da lista ligada por um valor crescente.
 * 
 * \FunctionName bubbleSortGestores
 * \param inicioGestor
 * \return Gestor
 */
Gestor* bubbleSortGestores(Gestor* inicioGestor) {
    Gestor* atual, * seguinte;
    int auxCodigo, b = 1, auxEncriptado;
    char auxSenha[50], auxNome[50], auxAreaResponsavel[50];
    while (b)
    {
        b = 0;
        atual = inicioGestor;
        if (atual == NULL)
        {
            return 0;
        }
        while (atual->seguinteGestor != NULL)
        {
            seguinte = atual->seguinteGestor;
            if (atual->codigo > seguinte->codigo)
            {
                auxCodigo = atual->codigo;
                strcpy(auxNome, atual->nome);
                strcpy(auxSenha, atual->senha);
                auxEncriptado = atual->encriptado;
                strcpy(auxAreaResponsavel, atual->areaResponsavel);

                atual->codigo = seguinte->codigo;
                strcpy(atual->nome, seguinte->nome);
                strcpy(atual->senha, seguinte->senha);
                atual->encriptado = seguinte->encriptado;
                strcpy(atual->areaResponsavel, seguinte->areaResponsavel);

                seguinte->codigo = auxCodigo;
                strcpy(seguinte->nome, auxNome);
                strcpy(seguinte->senha, auxSenha);
                seguinte->encriptado = auxEncriptado;
                strcpy(seguinte->areaResponsavel, auxAreaResponsavel);

                b = 1;
            }
            atual = seguinte;
        }
    }
    inicioGestor = atual;
    return inicioGestor;
}


#pragma endregion

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES----------------------------------------------------


// ---------------------------------------------------INICIO-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------
#pragma region INSERIR

/**
 * Função para entrar em modo gestor, no qual é pedido um codigo e uma senha. Caso sejam iguais ao que está no ficheiro é garantido o acesso
 * a funções de gestor.
 * 
 * \FunctionName modoGestor
 * \param inicioGestores
 * \return Gestor
 */
Gestor* modoGestor(Gestor* inicioGestores) {
    int codigoInserido;
    char senha[20];
    if (inicioGestores == NULL)
    {
        printf("Ficheiro nao lido.\n");
        return 0;
    }
    printf("Insira o codigo de utilizador:");
    scanf("%d", &codigoInserido);
    printf("Insira a senha:");
    scanf("%s", senha);
    senha[20 - 1] = '\0';
    while (inicioGestores != NULL)
    {
        if (inicioGestores->codigo == codigoInserido && strcmp(inicioGestores->senha, senha) == 0 && inicioGestores->encriptado == 0)
        {
            printf("Bem-vindo %s\n", inicioGestores->nome);
            return 1;
        }
        else if (inicioGestores->codigo == codigoInserido && inicioGestores->encriptado == 1)
        {
            decryptSenha(inicioGestores, inicioGestores->senha);
            if (strcmp(senha, inicioGestores->senha) == 0)
            {
                printf("Bem-vindo %s\n", inicioGestores->nome);
                encryptSenha(inicioGestores, inicioGestores->senha);
                return 1;
            }
            else
            {
                printf("Senha errada.\n");
                return 0;
            }
        }
        else
        {
            inicioGestores = inicioGestores->seguinteGestor;
        }
    }
    if (inicioGestores == NULL)
    {
        printf("Codigo ou senha errados.\n");
        return 0;
    }
}

/**
 * Função para inserir um novo meio elétrico, é pedido ao gestor na função main, um novo codigo, nome, nivel bateria, autonomia, o seu custo
 * e a sua geolocalização. De seguida é inserido no ultimo lugar da lista ligada dos meios, quando é o ultimo endereço NULL.
 * 
 * \FunctionName inserirMeio
 * \param inicioGrafo
 * \param inicioMeios
 * \param cod
 * \param nome
 * \param bat
 * \param aut
 * \param custo
 * \param geo
 * \return Meio
 */
Meio* inserirMeio(Grafo* inicioGrafo, Meio* inicioMeios, int cod, char nome[], float bat, float aut, int custo, char geo[])
{
    Grafo* aux = inicioGrafo;
    int inserir = 0;
    while (inserir != 1)
    {
        if (inicioMeios == NULL)
        {
            Meio* novoMeio = malloc(sizeof(Meio));
            if (novoMeio == NULL)
            {
                return semEspacoMem;
            }
            novoMeio->codigo = cod;
            strcpy(novoMeio->tipo, nome);
            novoMeio->bateria = bat;
            novoMeio->autonomia = aut;
            novoMeio->custo = custo;
            strcpy(novoMeio->geocodigo, geo);
            if (!existeVertice(aux, novoMeio->geocodigo))
            {
                inserirVertice(aux, novoMeio->geocodigo);
            }
            novoMeio->ativo = 0;
            novoMeio->seguinteMeio = NULL;
            inicioMeios = novoMeio;
            printf("Meio com codigo %d inserido com sucesso.\n", novoMeio->codigo);
            Sleep(2000);
            system("cls");
            return inicioMeios;
        }
        if (inicioMeios->seguinteMeio == NULL)
        {
            Meio* novoMeio = malloc(sizeof(Meio));
            
            novoMeio->codigo = cod;
            strcpy(novoMeio->tipo, nome);
            novoMeio->bateria = bat;
            novoMeio->autonomia = aut;
            novoMeio->custo = custo;
            strcpy(novoMeio->geocodigo, geo);
            if (!existeVertice(aux, novoMeio->geocodigo))
            {
                int auxVertice, escolhaAdjacente, inserido = 1;
                auxVertice=inserirVertice(aux, novoMeio->geocodigo);
                if (auxVertice == 1)
                {
                    printf("A %s tem algum destino? 1-Sim/0-Nao\n", novoMeio->geocodigo);
                    printf("A sua escolha:");
                    scanf("%d", &escolhaAdjacente);
                    while(escolhaAdjacente == 1 && inserido != 0)
                    {
                        char novoAdjacente[50];
                        float novoPeso;
                        printf("Nome do novo adjacente a %s:", novoMeio->geocodigo);
                        scanf("%s", novoAdjacente);
                        printf("Distancia em km:");
                        scanf("%f", &novoPeso);
                        if (inserirAdjacente(aux, novoMeio->geocodigo, novoAdjacente, novoPeso))
                        {
                            printf("Adjacente inserido com sucesso.\n");
                            printf("Deseja inserir mais adjacentes ao geocodigo %s?\n 1-Sim/0-Nao\n", novoMeio->geocodigo);
                            printf("A sua escolha:");
                            scanf("%d", &inserido);
                        }
                    }
                }
            }
            novoMeio->ativo = 0;
            inicioMeios->seguinteMeio = novoMeio;
            novoMeio->seguinteMeio = NULL;
            inicioMeios = novoMeio;
            inserir = 1;
            printf("Meio com codigo %d inserido com sucesso.\n", novoMeio->codigo);
            Sleep(2000);
            system("cls");
            return inicioMeios;
        }
        inicioMeios = inicioMeios->seguinteMeio;
    }
    return inicioMeios;
}

/**
 * Função para inserir um novo cliente, é pedido ao gestor na função main, um novo codigo, nome, NIF e saldo.  
 * De seguida é inserido no ultimo lugar da lista ligada dos clientes, quando é o ultimo endereço NULL.
 * 
 * \FunctionName inserirCliente
 * \param inicioClientes
 * \param cod
 * \param nome
 * \param NIF
 * \param saldo
 * \param geocodigo
 * \return Cliente
 */
Cliente* inserirCliente(Cliente* inicioClientes, int cod, char nome[], int NIF, int saldo, char geocodigo[])
{
    int inserir = 0;
    while (inserir != 1)
    {
        if (inicioClientes == NULL)
        {
            Cliente* novoCliente = malloc(sizeof(Cliente));
            novoCliente->codigo = cod;
            strcpy(novoCliente->nome, nome);
            novoCliente->NIF = NIF;
            novoCliente->saldo = saldo;
            strcpy(novoCliente->geocodigo, geocodigo);
            novoCliente->seguinteCliente = NULL;
            inicioClientes = novoCliente;
            printf("Cliente com codigo %d adicionado com sucesso.\n", novoCliente->codigo);
            Sleep(2000);
            system("cls");
            return inicioClientes;
        }
        if (inicioClientes->seguinteCliente == NULL)
        {
            Cliente* novoCliente = malloc(sizeof(Cliente));
            novoCliente->codigo = cod;
            strcpy(novoCliente->nome, nome);
            novoCliente->NIF = NIF;
            novoCliente->saldo = saldo;
            strcpy(novoCliente->geocodigo, geocodigo);
            inicioClientes->seguinteCliente = novoCliente;
            novoCliente->seguinteCliente = NULL;
            inicioClientes = novoCliente;
            printf("Cliente com codigo %d adicionado com sucesso.\n", novoCliente->codigo);
            Sleep(2000);
            system("cls");
            return inicioClientes;
        }
        inicioClientes = inicioClientes->seguinteCliente;
    }
    return inicioClientes;
}

/**
 * Função para inserir um novo gestor, é pedido ao gestor na função main, um novo codigo, nome e senha.
 * De seguida é inserido no ultimo lugar da lista ligada dos gestores, quando é o ultimo endereço NULL.
 * 
 * \FunctionName inserirGestor
 * \param inicioGestor
 * \param cod
 * \param nome
 * \param senha
 * \param area
 * \return Gestor
 */
Gestor* inserirGestor(Gestor* inicioGestor, int cod, char nome[], char senha[], char area[])
{
    int inserir = 0, encriptado;
    while (inserir != 1)
    {
        if (inicioGestor == NULL)
        {
            Gestor* novoGestor = malloc(sizeof(Gestor));
            novoGestor->codigo = cod;
            strcpy(novoGestor->nome, nome);
            strcpy(novoGestor->senha, senha);
            printf("Deseja encriptar a sua senha?\n1-Sim/2-Nao\n");
            printf("A sua escolha:");
            scanf("%d", &encriptado);
            if (encriptado == 1)
            {
                novoGestor->encriptado = 1;
                encryptSenha(novoGestor, novoGestor->senha);
            }
            else
            {
                novoGestor->encriptado = 0;
            }
            strcpy(novoGestor->areaResponsavel, area);
            novoGestor->seguinteGestor = NULL;
            inicioGestor = novoGestor;
            printf("Gestor com codigo %d inserido com sucesso.\n", novoGestor->codigo);
            Sleep(2000);
            system("cls");
            return inicioGestor;
        }
        if (inicioGestor->seguinteGestor == NULL)
        {
            Gestor* novoGestor = malloc(sizeof(Gestor));
            novoGestor->codigo = cod;
            strcpy(novoGestor->nome, nome);
            strcpy(novoGestor->senha, senha);
            printf("Deseja encriptar a sua senha?\n1-Sim/2-Nao\n");
            printf("A sua escolha:");
            scanf("%d", &encriptado);
            if (encriptado == 1)
            {
                novoGestor->encriptado = 1;
                encryptSenha(novoGestor, novoGestor->senha);
            }
            else
            {
                novoGestor->encriptado = 0;
            }
            strcpy(novoGestor->areaResponsavel, area);
            inicioGestor->seguinteGestor = novoGestor;
            novoGestor->seguinteGestor = NULL;
            inicioGestor = novoGestor;
            inserir = 1;
            printf("Gestor com codigo %d inserido com sucesso.\n", novoGestor->codigo);
            Sleep(2000);
            system("cls");
            return inicioGestor;
        }
        inicioGestor = inicioGestor->seguinteGestor;
    }
    return inicioGestor;
}

/**
 * Pequena função para encriptação da senha do gestor.
 * 
 * \FunctionName encryptSenha
 * \param inicioGestor
 * \param senha
 * \return int
 */
int encryptSenha(Gestor* inicioGestor, char senha[])
{
    for (int i = 0; i < strlen(senha); i++)
    {
        senha[i] = senha[i] + 5;
    }
    return 1;
}

// 
/**
 * Pequena função para desencriptacao da senha do gestor.
 * 
 * \FunctionName decryptSenha
 * \param inicioGestor
 * \param senha
 * \return int
 */
int decryptSenha(Gestor* inicioGestor, char senha[])
{
    for (int i = 0; i < strlen(senha); i++)
    {
        senha[i] = senha[i] - 5;
    }
    return 1;
}
#pragma endregion 

#pragma region REMOVER

/**
 * Função para remover algum meio, a partir do código inserido pelo gestor. É removido o meio e de seguida é retornada toda a lista ligada
 * com o meio removido.
 * 
 * \FunctionName removerMeio
 * \param inicioMeios
 * \param cod
 * \return Meio
 */
Meio* removerMeio(Meio* inicioMeios, int cod)
{
    Meio* anterior = inicioMeios, * atual = inicioMeios, * aux;

    if (atual == NULL) return(NULL); // Lista vazia.
    else if (atual->codigo == cod) // remoção do 1º registo
    {
        aux = atual->seguinteMeio;
        free(atual);
        printf("Meio com cod %d removido com sucesso.\n", cod);
        Sleep(2000);
        system("cls");
        return(aux);
    }
    else
    {
        while ((atual != NULL) && (atual->codigo != cod)) // Iteração até ser igual.
        {
            anterior = atual;
            atual = atual->seguinteMeio;
        }
        if (atual == NULL) return(inicioMeios);
        else // Remoção do meio com cod introduzido.
        {
            anterior->seguinteMeio = atual->seguinteMeio;
            free(atual);
            printf("Meio com cod %d removido com sucesso.\n", cod);
            Sleep(2000);
            system("cls");
            return(inicioMeios);
        }
    }
}

/**
 * Função para remover algum cliente, a partir do código inserido pelo gestor. É removido o cliente e de seguida é retornada toda a lista ligada
 * com o meio removido.
 * 
 * \FunctionName removerCliente
 * \param inicioClientes
 * \param cod
 * \return Cliente
 */
Cliente* removerCliente(Cliente* inicioClientes, int cod)
{
    Cliente* anterior = inicioClientes, * atual = inicioClientes, * aux;

    if (atual == NULL) return(NULL); // Lista vazia.
    else if (atual->codigo == cod) // remoção do 1º registo
    {
        aux = atual->seguinteCliente;
        free(atual);
        printf("Cliente com cod %d removido com sucesso.\n", cod);
        Sleep(2000);
        system("cls");
        return(aux);
    }
    else
    {
        while ((atual != NULL) && (atual->codigo != cod)) // Iteração até ser igual.
        {
            anterior = atual;
            atual = atual->seguinteCliente;
        }
        if (atual == NULL) return(inicioClientes);
        else // Remoção do cliente com cod introduzido.
        {
            anterior->seguinteCliente = atual->seguinteCliente;
            free(atual);
            printf("Cliente com cod %d removido com sucesso.\n", cod);
            Sleep(2000);
            system("cls");
            return(inicioClientes);
        }
    }
}

/**
 * Função para remover algum gestor, a partir do código inserido pelo gestor. É removido o gestor e de seguida é retornada toda a lista ligada
 * com o meio removido.
 * 
 * \FunctionName removerGestor
 * \param inicioGestores
 * \param cod
 * \return Gestor
 */
Gestor* removerGestor(Gestor* inicioGestores, int cod)
{
    Gestor* anterior = inicioGestores, * atual = inicioGestores, * aux;

    if (atual == NULL) return(NULL); // Lista vazia.
    else if (atual->codigo == cod) // remoção do 1º registo
    {
        aux = atual->seguinteGestor;
        free(atual);
        printf("Gestor com cod %d removido com sucesso.\n", cod);
        return(aux);
    }
    else
    {
        while ((atual != NULL) && (atual->codigo != cod)) // Iteração até ser igual.
        {
            anterior = atual;
            atual = atual->seguinteGestor;
        }
        if (atual == NULL) return(inicioGestores); // Lista ligada toda percorrida, nao foi encontrado nenhum gestor com o codigo inserido.
        else // Remoção do gestor com cod introduzido.
        {
            anterior->seguinteGestor = atual->seguinteGestor;
            free(atual);
            printf("Gestor com cod %d removido com sucesso.\n", cod);
            return(inicioGestores);
        }
    }
}
#pragma endregion

#pragma region ALTERAR

/**
 * Função para alteração de dados de algum gestor.
 * Apenas é pedido o codigo de gestor. É possivel alterar codigo, nome, senha, area responsavel.
 * 
 * \FunctionName alterarGestor
 * \param inicioGestores
 * \return Gestor
 */
Gestor* alterarGestor(Gestor* inicioGestores)
{
    int cod, escolha, novoCodigo, encriptar, acabadoAlterar = 1;
    char novaSenha[50], novoNome[50], senha[50], novaAreaResponsavel[50];
    Gestor* aux = inicioGestores;
    if (inicioGestores == NULL)
    {
        printf("Nao existem gestores, por favor faca o registo de um.\n");
        Sleep(2000);
        system("cls");
        return 0;
    }
    printf("Introduza o seu codigo de gestor:");
    scanf("%d", &cod);
    if (existeGestor(aux, cod) == 1)
    {
        printf("O codigo %d nao existe.\n", cod);
        Sleep(2000);
        system("cls");
        return 0;
    }
    system("cls");
    while (inicioGestores != NULL)
    {
        if (inicioGestores->codigo == cod)
        {
            do
            {
                printf("Este sao os seus dados.\n");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("Nome:%s     Codigo:%d       Area:%s\n", inicioGestores->nome, inicioGestores->codigo, inicioGestores->areaResponsavel);
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("O que deseja alterar?\n");
                printf("1- Codigo.\n");
                printf("2- Nome.\n");
                printf("3- Area responsavel.\n");
                printf("4- Senha.\n");
                printf("0- Sair.\n");
                printf("A sua escolha:");
                scanf("%d", &escolha);
                switch (escolha)
                {
                case 1:
                    printf("Introduza um novo codigo:");
                    scanf("%d", &novoCodigo);
                    if (!existeGestor(aux, novoCodigo))
                    {
                        printf("Ja existe alguem com esse codigo.\n");
                        Sleep(2000);
                        system("cls");
                    }
                    else
                    {
                        inicioGestores->codigo = novoCodigo;
                        printf("Codigo alterado com sucesso. O seu novo codigo %d\n", inicioGestores->codigo);
                        Sleep(2000);
                        system("cls");
                    }
                    break;
                case 2:
                    printf("Introduza um novo nome:");
                    scanf("%s", novoNome);
                    strcpy(inicioGestores->nome, novoNome);
                    Sleep(2000);
                    system("cls");
                    break;
                case 3:
                    printf("Introduza a nova area para ser responsavel:");
                    scanf("%s", novaAreaResponsavel);
                    strcpy(inicioGestores->areaResponsavel, novaAreaResponsavel);
                    printf("A sua area responsavel foi alterada com sucesso.\n");
                    printf("A sua nova area e a seguinte: %s\n", inicioGestores->areaResponsavel);
                    Sleep(2000);
                    system("cls");
                    break;
                case 4:
                    printf("Introduza a sua nova senha:");
                    scanf("%s", novaSenha);
                    printf("Deseja encriptar? 1-Sim/0-Nao\n");
                    printf("A sua escolha:");
                    scanf("%d", &encriptar);
                    if (encriptar == 0)
                    {
                        printf("Senha alterada com sucesso.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    else
                    {
                        inicioGestores->encriptado = 1;
                        encryptSenha(inicioGestores, novaSenha);
                        strcpy(inicioGestores->senha, novaSenha);
                        printf("Senha encriptada e alterada com sucesso.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                case 0:
                    break;
                default:
                    printf("Insira uma opcao.\n");
                    break;
                }
            } while (escolha != 0);
        }
        inicioGestores = inicioGestores->seguinteGestor;
    }
}

/**
 *  Função para alteração de dados do cliente.
 *  É pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes é possivel fazer alteração de nome, codigo e NIF.
 * \FunctionName alterarDadosCliente
 * \param inicioClientes
 * \param inicioTransacao
 * \param inicioAluguer
 * \return ResFuncoes
 */
ResFuncoes alterarDadosCliente(Cliente* inicioClientes, Transacao* inicioTransacao, Aluguer* inicioAluguer) {
    int codigo, NIF, novoCodigo, novoNIF, inserir = 1, escolha, codigoAux;
    char novoNome[50], novoGeocodigo[100];
    Cliente* aux = inicioClientes;
    Transacao* auxTrans = inicioTransacao;
    Aluguer* auxAluguer = inicioAluguer;
    if (inicioClientes == NULL)
    {
        return clientesNaoExistem;
    }
    printf("Introduza o seu codigo:");
    scanf("%d", &codigo);
    printf("Introduza o seu NIF:");
    scanf("%d", &NIF);
    if (existeClienteCod(aux, codigo) == 1)
    {
        return codClienteNaoExiste;
    }
    else if (existeClienteNIF(aux, NIF) == 1)
    {
        return nifClienteNaoExiste;
    }
    while (inicioClientes != NULL)
    {
        if (inicioClientes->codigo == codigo && inicioClientes->NIF == NIF)
        {
            do
            {
                printf("Este sao os seus dados, %s.\n", inicioClientes->nome);
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("Nome:%s     Codigo:%d       NIF:%d      Localizacao:%s\n", inicioClientes->nome, inicioClientes->codigo, inicioClientes->NIF, inicioClientes->geocodigo);
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("O que deseja alterar?\n");
                printf("1- Nome.\n");
                printf("2- Codigo.\n");
                printf("3- NIF.\n");
                printf("4- Localizacao.\n");
                printf("0- Sair.\n");
                printf("A sua escolha:");
                scanf("%d", &escolha);
                switch (escolha)
                {
                case 1:
                    getchar();
                    printf("Insira o seu novo nome:");
                    scanf("%[^\n]", novoNome);
                    strcpy(inicioClientes->nome, novoNome);
                    printf("Nome alterado com sucesso para %s.\n", inicioClientes->nome);
                    Sleep(2000);
                    system("cls");
                    break;
                case 2:
                    printf("Insira o seu novo codigo:");
                    scanf("%d", &novoCodigo);
                    if (existeClienteCod(aux, novoCodigo))
                    {
                        codigoAux = inicioClientes->codigo;
                        inicioClientes->codigo = novoCodigo;
                        printf("O seu novo codigo %d\n", inicioClientes->codigo);
                        if (existeClienteTransacao(auxTrans, codigoAux))
                        {
                            while (auxTrans != NULL )
                            {
                                if (auxTrans->codigoUtilizador == codigoAux)
                                {
                                    auxTrans->codigoUtilizador = novoCodigo;
                                }
                                auxTrans = auxTrans->seguinteTransacao;
                            }
                        }
                        if(existeClienteAluguer(auxAluguer,codigoAux))
                        {
                            while (auxAluguer != NULL)
                            {
                                if (auxAluguer->codComprador == codigoAux)
                                {
                                    auxAluguer->codComprador = novoCodigo;
                                }
                                auxAluguer = auxAluguer->seguinteCompra;
                            }
                        }
                        Sleep(2000);
                        system("cls");
                    }
                    else
                    {
                        printf("O codigo %d ja existe.\n", novoCodigo);
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    break;
                case 3:
                    printf("Insira o seu novo NIF(deve conter 9 numeros e comecar por 192):");
                    scanf("%d", &novoNIF);
                    if (novoNIF <= 192000000 || novoNIF >= 193000000)
                    {
                        printf("Por favor tente de novo.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    else
                    {
                        if (existeClienteNIF(aux, novoNIF))
                        {
                            inicioClientes->NIF = novoNIF;
                            printf("O seu novo NIF %d\n", inicioClientes->NIF);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        else
                        {
                            printf("Ja existe alguem com o NIF inserido %d.\n", novoNIF);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                    }
                    break;
                case 4:
                    printf("Insira o seu novo geocodigo/localizacao:");
                    scanf("%s", novoGeocodigo);
                    strcpy(inicioClientes->geocodigo, novoGeocodigo);
                    printf("Geocodigo alterado com sucesso para %s.\n", inicioClientes->geocodigo);
                    Sleep(2000);
                    system("cls");
                    break;
                case 0:
                    return 1;
                    break;
                }
            } while (escolha != 0);
        }
        inicioClientes = inicioClientes->seguinteCliente;
    }
}

/**
 * Função para alteração de dados de algum meio.
 * É pedido o codigo do meio a alterar. É possivel alterar o seu codigo, tipo, se está ativo, custo, bat, aut, etc...
 * 
 * \FunctionName alterarMeio
 * \param inicioMeios
 * \return Meio
 */
Meio* alterarMeio(Meio* inicioMeios)
{
    int cod, codAlterar, ativoAlterar, custoAlterar, escolha;
    float batAlterar, autAlterar;
    char meioNomeAlterar[50], geocodigoAlterar[50];
    Meio* aux = inicioMeios;
    if (inicioMeios == NULL)
    {
        printf("Nao existem meios.\n");
        Sleep(2000);
        system("cls");
        return 0;
    }
    printf("Introduza o codigo do meio que pretende alterar:");
    scanf("%d", &cod);
    if (existeMeio(inicioMeios, cod))
    {
        printf("O meio com o codigo %d nao existe.\n", cod);
        Sleep(2000);
        system("cls");
        return 0;
    }
    system("cls");
    while (inicioMeios != NULL)
    {
        if (inicioMeios->codigo == cod)
        {
            do
            {
                printf("Este sao os dados do meio cod %d.\n", inicioMeios->codigo);
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("Codigo:%d\nTipo:%s\nBateria:%.2f\nAut:%.2f\nCusto:%d\nGeo:%s\nAtivo:%d\n", inicioMeios->codigo, inicioMeios->tipo, inicioMeios->bateria, inicioMeios->autonomia, inicioMeios->custo, inicioMeios->geocodigo, inicioMeios->ativo);
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("O que deseja alterar?\n");
                printf("1- Codigo.\n");
                printf("2- Tipo.\n");
                printf("3- Bateria.\n");
                printf("4- Autonomia.\n");
                printf("5- Custo.\n");
                printf("6- Geocodigo.\n");
                printf("7- Ativo.\n");
                printf("A sua escolha:");
                scanf("%d", &escolha);
                switch (escolha)
                {
                case 1:
                    printf("Insira o novo codigo:");
                    scanf("%d", &codAlterar);
                    if (!existeMeio(aux, codAlterar))
                    {
                        printf("Ja existe um meio com esse codigo.\n");
                        Sleep(2000);
                        system("cls");
                    }
                    else
                    {
                        inicioMeios->codigo = codAlterar;
                        printf("Codigo alterado com sucesso. Novo codigo %d.\n", inicioMeios->codigo);
                        Sleep(2000);
                        system("cls");
                    }
                    break;
                case 2:
                    printf("Insira o novo tipo de meio:");
                    scanf("%s", meioNomeAlterar);
                    strcpy(inicioMeios->tipo, meioNomeAlterar);
                    printf("Nome alterado com sucesso para %s.\n", inicioMeios->tipo);
                    Sleep(2000);
                    system("cls");
                    break;
                case 3:
                    printf("Insira o novo nivel de bateria:");
                    scanf("%f", &batAlterar);
                    if (batAlterar > 100.0001 || batAlterar < 0)
                    {
                        printf("Insira um nivel de bateria, entre 0 e 100.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    inicioMeios->bateria = batAlterar;
                    printf("Novo nivel de bateria %.2f\n", inicioMeios->bateria);
                    Sleep(2000);
                    system("cls");
                    break;
                case 4:
                    printf("Insira o novo nivel de autonomia:");
                    scanf("%f", &autAlterar);
                    if (autAlterar > 100.0001 || autAlterar < 0)
                    {
                        printf("Insira um nivel de autonomia, entre 0 e 100.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    inicioMeios->autonomia = autAlterar;
                    printf("Novo nivel de autonomia %.2f\n", inicioMeios->autonomia);
                    Sleep(2000);
                    system("cls");
                    break;
                case 5:
                    printf("Insira o novo custo:");
                    scanf("%d", &custoAlterar);
                    inicioMeios->custo = custoAlterar;
                    printf("Novo custo do meio %d\n", inicioMeios->custo);
                    Sleep(2000);
                    system("cls");
                    break;
                case 6:
                    printf("Insira um novo geocodigo:");
                    scanf("%s", geocodigoAlterar);
                    strcpy(inicioMeios->geocodigo, geocodigoAlterar);
                    printf("Novo geocodigo %s\n", inicioMeios->geocodigo);
                    Sleep(2000);
                    system("cls");
                    break;
                case 7:
                    printf("Este veiculo esta ativo?1-Sim/0-Nao\n");
                    printf("A sua escolha:");
                    scanf("%d", &ativoAlterar);
                    if (ativoAlterar == 1)
                    {
                        if (inicioMeios->ativo == 1)
                        {
                            printf("Meio ja esta ativo.\n");
                            Sleep(2000);
                            system("cls");
                        }
                        else
                        {
                            inicioMeios->ativo = 1;
                            system("cls");
                        }
                    }
                    else
                    {
                        if (inicioMeios->ativo == 0)
                        {
                            printf("Meio ja nao estava ativo.\n");
                            Sleep(2000);
                            system("cls");
                        }
                        else
                        {
                            inicioMeios->ativo = 0;

                        }
                    }
                    break;
                case 0:
                    break;
                default:
                    printf("Introduza alguma opcao.\n");
                    break;
                }
            } while (escolha != 0);
        }
        inicioMeios = inicioMeios->seguinteMeio;
    }
}
#pragma endregion
// ---------------------------------------------------FIM-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------


// ---------------------------------------------------------------INICIO_OP_UTILIZADOR-----------------------------------------------------------------
#pragma region opUtilizador
/**
 * Função para carregamento de saldo, de um certo utilizador.
 * É pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes é possivel carregar o saldo desse mesmo utilizador.
 * 
 * \FunctionName carregarSaldo
 * \param inicioClientes
 * \param inicioTransacao
 * \return Cliente
 */
Cliente* carregarSaldo(Cliente* inicioClientes, Transacao* inicioTransacao) {
    if (inicioClientes == NULL)
    {
        perror(clientesNaoExistem);
        return clientesNaoExistem;
    }
    Transacao* auxTrans = inicioTransacao;
    int codigo, NIF, inserir = 1;
    printf("Introduza o seu codigo:");
    scanf("%d", &codigo);
    printf("Introduza o seu NIF:");
    scanf("%d", &NIF);
    while (inicioClientes != NULL)
    {
        if (inicioClientes->codigo == codigo && inicioClientes->NIF == NIF)
        {
            int saldoCarregar;
            printf("O seu saldo: %d\n", inicioClientes->saldo);
            printf("Quanto saldo deseja carregar?\n");
            printf("Digite:");
            scanf("%d", &saldoCarregar);
            if (saldoCarregar < 0)
            {
                return saldoCarrNegativo;
            }
            inicioClientes->saldo = saldoCarregar + inicioClientes->saldo;
            printf("%d carregado com sucesso. Tem agora %d de saldo.\n", saldoCarregar, inicioClientes->saldo);
            if (inicioTransacao == NULL)
            {
                if (inicioTransacao = criarTransacao(inicioTransacao, inicioClientes->codigo, saldoCarregar, inicioClientes->nome))
                    return inicioTransacao;
            }
            while (inserir == 1)
            {
                if (inicioTransacao->seguinteTransacao == NULL)
                {
                    if (criarTransacao(auxTrans, inicioClientes->codigo, saldoCarregar, inicioClientes->nome))
                        inserir = 0;
                }
                inicioTransacao = inicioTransacao->seguinteTransacao;
                if (inserir == 0)
                {
                    return SUCESSO;
                }
            }
        }
        inicioClientes = inicioClientes->seguinteCliente;
    }
    if (inicioClientes == NULL)
    {
        return codNifNaoExiste;
    }
    Sleep(2000);
    system("cls");
}

/**
 * Função para consulta de saldo, de um certo utilizador.
 * É pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes é possivel visualizar quando saldo está disponível.
 * 
 * \FunctionName consultaSaldo
 * \param inicioClientes
 * \param saldo
 * \return ResFuncoes
 */
ResFuncoes consultaSaldo(Cliente* inicioClientes, int** saldo) {
    int codigo, NIF;
    printf("Introduza o seu codigo:");
    scanf("%d", &codigo);
    printf("Introduza o seu NIF:");
    scanf("%d", &NIF);
    if (inicioClientes == NULL)
    {
        return clientesNaoExistem;
    }
    while (inicioClientes != NULL)
    {
        if (inicioClientes->codigo == codigo && inicioClientes->NIF == NIF)
        {
            *saldo = &inicioClientes->saldo;
            return saldoAtual;
        }
        inicioClientes = inicioClientes->seguinteCliente;
    }
    if (inicioClientes == NULL)
    {
        return codNifNaoExiste;
    }
}

/**
 * Funcao para realização de aluguer de qualquer meio existente, que não esteja ativo.
 * É pedido o codigo de utilizador, é verificado se existe esse mesmo utilizador. De seguida é perguntado qual o meio que deseja alugar.
 * São apresentados dados, tais como o tipo de meio, o seu custo e o saldo do utilizador. Caso o utilizador, decida comprar o meio
 * É criado um novo registo na lista ligada de alugueres.
 * 
 * \FunctionName realizarAluguer
 * \param inicioClientes
 * \param inicioAluguer
 * \param inicioMeios
 * \return Aluguer
 */
Aluguer* realizarAluguer(Cliente* inicioClientes, Aluguer* inicioAluguer, Meio* inicioMeios)
{
    int meioAlugar, codigoUtilizador, NIF;
    printf("Insira o seu codigo:");
    scanf("%d", &codigoUtilizador);
    if (existeClienteCod(inicioClientes, codigoUtilizador) == 0)
    {
        while (inicioClientes->codigo != codigoUtilizador)
            inicioClientes = inicioClientes->seguinteCliente;
        printf("Qual meio deseja alugar?\n");
        scanf("%d", &meioAlugar);
        if (existeMeio(inicioMeios, meioAlugar) == 0)
        {
            while (inicioMeios->codigo != meioAlugar)
            {
                inicioMeios = inicioMeios->seguinteMeio;
            }
            printf("Nome do meio %s\n", inicioMeios->tipo);
            printf("O meio custa:%d\n", inicioMeios->custo);
            printf("Voce tem:%d\n", inicioClientes->saldo);
            int escolhaCompra;
            printf("Deseja comprar? 1-Sim/2-Nao\n");
            printf("A sua escolha:");
            scanf("%d", &escolhaCompra);
            if (escolhaCompra != 1)
            {
                return 0;
            }
            else
            {
                if (inicioClientes->saldo < inicioMeios->custo)
                {
                    printf("Nao tem saldo suficiente para efetuar a compra.\n");
                    Sleep(2000);
                    system("cls");
                    return 0;
                }
                else if (inicioMeios->ativo == 1)
                {
                    printf("Nao pode alugar esse meio, pois ja esta alugado.\n");
                    Sleep(2000);
                    system("cls");
                }
                else
                {
                    time_t dataCompra;
                    time(&dataCompra);
                    char auxDataCompra[50];
                    strcpy(auxDataCompra, ctime(&dataCompra));
                    for (int i = 0; i < strlen(auxDataCompra); i++)
                    {
                        if (auxDataCompra[i] == '\n')
                            auxDataCompra[i] = '\0';
                    }
                    printf("Data da compra: %s\n", ctime(&dataCompra));
                    int inserir = 0;
                    inicioClientes->saldo = inicioClientes->saldo - inicioMeios->custo;
                    printf("O seu novo saldo %d\n", inicioClientes->saldo);
                    while (inserir != 1)
                    {
                        if (inicioAluguer == NULL)
                        {
                            Aluguer* novoNodo = malloc(sizeof(Aluguer));
                            novoNodo->seguinteCompra = NULL;
                            inicioAluguer = novoNodo;
                        }
                        if (inicioAluguer->seguinteCompra == NULL)
                        {
                            Aluguer* novoNodo = malloc(sizeof(Aluguer));
                            novoNodo->codComprador = inicioClientes->codigo;
                            strcpy(novoNodo->nomeComprador, inicioClientes->nome);
                            strcpy(novoNodo->dataCompra, auxDataCompra);
                            strcpy(novoNodo->nomeMeioComprado, inicioMeios->tipo);
                            inicioMeios->ativo = 1;
                            inicioAluguer->seguinteCompra = novoNodo;
                            novoNodo->seguinteCompra = NULL;
                            inicioAluguer = novoNodo;
                            printf("Compra efetuada com sucesso.\n");
                            Sleep(2000);
                            system("cls");
                            inserir = 1;
                            return inicioAluguer;
                        }
                        inicioAluguer = inicioAluguer->seguinteCompra;
                    }
                }
            }
        }
        else
        {
            //printf("O meio introduzido, nao existe.\n");
            //Sleep(2000);
            //system("cls");
            return 0;
        }
    }
    else
    {
        printf("Nao existe esse codigo de cliente.\n");
        Sleep(2000);
        system("cls");
        return 0;
    }
}

/**
 * Função para listar na consola, todos os meios existentes com um certo geocodigo.
 * 
 * \FunctionName listarGeocodigo
 * \param inicioMeios
 * \return int
 */
int listarGeocodigo(Meio* inicioMeios)
{
    system("cls");
    int verificado = 0, existe = 0;
    char verificarGeocodigo[50];
    Meio* auxPrint = inicioMeios;
    printf("Introduza o geocodigo que pretende verificar:");
    scanf("%s", verificarGeocodigo);
    getchar();

    if (inicioMeios == NULL)
        return meiosNaoExistem;
    while (auxPrint != NULL && existe == 0)
    {
        if (strcmp(verificarGeocodigo, auxPrint->geocodigo) == 0)
        {
            existe = 1;
        }
        auxPrint = auxPrint->seguinteMeio;
    }
    if (existe)
    {
        printf("Estes sao os meios com o geocodigo %s\n------------------------------------------------------------------------------------------------------------------------\n", verificarGeocodigo);
    }
    else
    {
        return geocodigoNaoExiste;
    }
    while (inicioMeios != NULL)
    {
        if (strcmp(verificarGeocodigo, inicioMeios->geocodigo) == 0)
        {
            printf("Codigo:%d      Tipo:%s      Bat:%.2f      Aut:%.2f      Custo:%d\n", inicioMeios->codigo, inicioMeios->tipo, inicioMeios->bateria, inicioMeios->autonomia, inicioMeios->custo);
        }
        inicioMeios = inicioMeios->seguinteMeio;
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    return SUCESSO;
}
#pragma endregion
// -----------------------------------------------------------------FIM_OP_UTILIZADOR-------------------------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE ALUGUER----------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAÇÃO DE ALUGUER
/**
 * Ler ficheiro de texto, contendo informação sobre os alugueres.
 * Serão todos os dados, inseridos numa lista ligada, que de inicio é vazia.
 * 
 * \FunctionName lerFicheiroAluguer
 * \param inicioAluguer
 * \param dadosAluguer
 * \return Aluguer
 */
Aluguer* lerFicheiroAluguer(Aluguer* inicioAluguer, FILE* dadosAluguer)
{
    char linha[tamanhoLinha];
    while (fgets(linha, tamanhoLinha, dadosAluguer))
    {
        Aluguer* novoNodo = malloc(sizeof(Aluguer));
        sscanf(linha,"%d;%[^;];%[^;];%[^\n]\n", &novoNodo->codComprador, novoNodo->dataCompra, novoNodo->nomeComprador, novoNodo->nomeMeioComprado);
        novoNodo->seguinteCompra = inicioAluguer;
        inicioAluguer = novoNodo;
    }
    fclose(dadosAluguer);
    return inicioAluguer;
}

/**
 * Função para listar na consola, o historico dos alugueres já feitos.
 * 
 * \FunctionName listarAluguer
 * \param inicioAluguer
 */
void listarAluguer(Aluguer* inicioAluguer)
{
    system("cls");
    if (inicioAluguer == NULL)
    {
        printf("Nao existem alugueres.\n");
        Sleep(2000);
        system("cls");
        return 0;
    }
    printf("Dados de Alugueres:\n------------------------------------------------------------------------------------------------------------------------\n");
    while (inicioAluguer != NULL)
    {
        printf("Codigo:%d   Data de compra:%s       Nome:%s Meio:%s\n", inicioAluguer->codComprador, inicioAluguer->dataCompra, inicioAluguer->nomeComprador, inicioAluguer->nomeMeioComprado);
        inicioAluguer = inicioAluguer->seguinteCompra;
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}

/**
 * Verifica cada aluguer existente, se a sua data for maior que a do seguinte elemento, irá ser feita uma troca
 * para ordenar todos os elementos por ordem de compra.
 * 
 * \FunctionName bubbleSortAluguer
 * \param inicioAluguer
 * \return Aluguer
 */
Aluguer* bubbleSortAluguer(Aluguer* inicioAluguer) {
    Aluguer* atual, * seguinte;
    int auxCodigo, b = 1;
    char auxData[50], auxComprador[50], auxMeioComprado[50];
    while (b)
    {
        b = 0;
        atual = inicioAluguer;
        if (atual == NULL)
        {
            return 0;
        }
        while (atual->seguinteCompra != NULL)
        {
            seguinte = atual->seguinteCompra;
            if (strcmp(atual->dataCompra, seguinte->dataCompra) > 0)
            {
                auxCodigo = atual->codComprador;
                strcpy(auxComprador, atual->nomeComprador);
                strcpy(auxData, atual->dataCompra);
                strcpy(auxMeioComprado, atual->nomeMeioComprado);

                atual->codComprador = seguinte->codComprador;
                strcpy(atual->nomeComprador, seguinte->nomeComprador);
                strcpy(atual->dataCompra, seguinte->dataCompra);
                strcpy(atual->nomeMeioComprado, seguinte->nomeMeioComprado);

                seguinte->codComprador = auxCodigo;
                strcpy(seguinte->nomeComprador, auxComprador);
                strcpy(seguinte->dataCompra, auxData);
                strcpy(seguinte->nomeMeioComprado, auxMeioComprado);
                b = 1;
            }
            atual = seguinte;
        }
    }
    inicioAluguer = atual;
    return inicioAluguer;
}

/**
 * Escreve todos os dados sobre os alugueres, em ficheiro de texto.
 * 
 * \FunctionName escreverFicheiroAluguer
 * \param inicioAluguer
 * \param dadosAluguer
 * \return Aluguer
 */
Aluguer* escreverFicheiroAluguer(Aluguer* inicioAluguer, FILE* dadosAluguer)
{
    if (inicioAluguer == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return 0;
    }
    dadosAluguer = fopen("historicoCompras.txt", "wt");
    if (dadosAluguer == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicioAluguer != NULL)
    {
        fprintf(dadosAluguer, "%d;%s;%s;%s\n", inicioAluguer->codComprador, inicioAluguer->dataCompra, inicioAluguer->nomeComprador, inicioAluguer->nomeMeioComprado);
        inicioAluguer = inicioAluguer->seguinteCompra;
    }
    fclose(dadosAluguer);
}

/**
 * Escreve todos os dados sobre os alugueres, em ficheiro binário.
 * 
 * \FunctionName escreverFicheiroAluguerBin
 * \param inicioAluguer
 * \param dadosAluguer
 * \return Aluguer
 */
Aluguer* escreverFicheiroAluguerBin(Aluguer* inicioAluguer, FILE* dadosAluguer)
{
    if (inicioAluguer == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return 0;
    }
    dadosAluguer = fopen("historicoCompras.bin", "wb");
    if (dadosAluguer == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicioAluguer != NULL)
    {
        fprintf(dadosAluguer, "%d;%s;%s;%s\n", inicioAluguer->codComprador, inicioAluguer->dataCompra, inicioAluguer->nomeComprador, inicioAluguer->nomeMeioComprado);
        inicioAluguer = inicioAluguer->seguinteCompra;
    }
    fclose(dadosAluguer);
}

/**
 * Verifica se existe transacao de um cliente, para auxiliar em funcoes em que o codigo do cliente seja mudado, assim mudando o codigo tambem na estrutura de transacoes.
 * 
 * \FunctionName existeClienteTransacao
 * \param inicioTransacao
 * \param codVerificar
 * \return int
 */
int existeClienteTransacao(Transacao* inicioTransacao, int codVerificar)
{
    Transacao* aux = inicioTransacao;
    while (aux != NULL)
    {
        if (aux->codigoUtilizador == codVerificar)
            return 1;
        aux = aux->seguinteTransacao;
    }
    return 0;
}

/**
 * Verifica se existe Aluguer de algum cliente, para auxiliar em funcoes em que o codigo do cliente seja mudado, assim mudando tambem o codigo na estrutura de Aluguer.
 * 
 * \FunctionName existeClienteAluguer
 * \param inicioTransacao
 * \param codVerificar
 * \return int
 */
int existeClienteAluguer(Aluguer* inicioTransacao, int codVerificar)
{
    Aluguer* aux = inicioTransacao;
    while (aux != NULL)
    {
        if (aux->codComprador == codVerificar)
            return 1;
        aux = aux->seguinteCompra;
    }
    return 0;
}
#pragma endregion
// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE ALUGUER----------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE TRANSACOES----------------------------------------------------
#pragma region LEITURA/ESCRITA/REPRESENTAÇÃO DE TRANSACOES

/**
 * Ler ficheiro de texto, contendo informação sobre transacoes efetuadas.
 * Serão todos os dados, inseridos numa lista ligada, que de inicio é vazia.
 * 
 * \FunctionName lerFicheiroTransacao
 * \param inicioTransacao
 * \param dadosTransacao
 * \return Transacao
 */
Transacao* lerFicheiroTransacao(Transacao* inicioTransacao, FILE* dadosTransacao)
{
    char linha[tamanhoLinha];
    while (fgets(linha, tamanhoLinha, dadosTransacao))
    {
        Transacao* novoNodo = malloc(sizeof(Transacao));
        sscanf(linha, "%d;%[^;];%d;%[^\n]", &novoNodo->codigoUtilizador, novoNodo->nomeTransacao, &novoNodo->montanteCarregado, novoNodo->dataTransacao);
        novoNodo->seguinteTransacao = inicioTransacao;
        inicioTransacao = novoNodo;
    }
    fclose(dadosTransacao);
    return inicioTransacao;
}

/**
 * Escreve todos os dados sobre transacoes, em ficheiro de texto.
 * 
 * \FunctionName escreverFicheiroTransacao
 * \param inicioTransacao
 * \param dadosTransacao
 * \return Transacao
 */
Transacao* escreverFicheiroTransacao(Transacao* inicioTransacao, FILE* dadosTransacao)
{
    if (inicioTransacao == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return 0;
    }
    dadosTransacao = fopen("historicoTransacoes.txt", "wt");
    if (dadosTransacao == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicioTransacao != NULL)
    {
        fprintf(dadosTransacao, "%d;%s;%d;%s\n", inicioTransacao->codigoUtilizador, inicioTransacao->nomeTransacao, inicioTransacao->montanteCarregado, inicioTransacao->dataTransacao);
        inicioTransacao = inicioTransacao->seguinteTransacao;
    }
    fclose(dadosTransacao);
}

/**
 * Escreve todos os dados sobre os alugueres, em ficheiro binario.
 * 
 * \FunctionName escreverFicheiroTransacaoBin
 * \param inicioTransacao
 * \param dadosTransacao
 * \return Transacao
 */
Transacao* escreverFicheiroTransacaoBin(Transacao* inicioTransacao, FILE* dadosTransacao)
{
    if (inicioTransacao == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return 0;
    }
    dadosTransacao = fopen("historicoTransacoes.bin", "wb");
    if (dadosTransacao == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicioTransacao != NULL)
    {
        fprintf(dadosTransacao, "%d;%s;%d;%s\n", inicioTransacao->codigoUtilizador, inicioTransacao->nomeTransacao, inicioTransacao->montanteCarregado, inicioTransacao->dataTransacao);
        inicioTransacao = inicioTransacao->seguinteTransacao;
    }
    fclose(dadosTransacao);
}

/**
 * Listar transacoes existentes.
 * 
 * \FunctionName listarTransacao
 * \param inicioTransacao
 */
void listarTransacao(Transacao* inicioTransacao)
{
    system("cls");
    if (inicioTransacao == NULL)
    {
        printf("Nao existem registos de transacoes.\n");
        Sleep(2000);
        system("cls");
        return 0;
    }
    printf("Dados de transacoes:\n------------------------------------------------------------------------------------------------------------------------\n");
    while (inicioTransacao != NULL)
    {
        printf("Codigo:%d   Nome:%s     Mont.Carregado:%dEur   Data:%s \n", inicioTransacao->codigoUtilizador, inicioTransacao->nomeTransacao, inicioTransacao->montanteCarregado, inicioTransacao->dataTransacao);
        inicioTransacao = inicioTransacao->seguinteTransacao;
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}

/**
 * Sendo executada, cria uma nova transacao
 * 
 * \FunctionName criarTransacao
 * \param inicioTransacao
 * \param codigoCliente
 * \param saldoCarregar
 * \param nomeCliente
 * \return Transacao
 */
Transacao* criarTransacao(Transacao* inicioTransacao, int codigoCliente, int saldoCarregar, char nomeCliente[])
{
    Transacao* novaTransacao = malloc(sizeof(Transacao));
    novaTransacao->codigoUtilizador = codigoCliente;
    novaTransacao->montanteCarregado = saldoCarregar;
    strcpy(novaTransacao->nomeTransacao, nomeCliente);
    time_t dataTransacao;
    time(&dataTransacao);
    char auxDataTransacao[50];
    strcpy(auxDataTransacao, ctime(&dataTransacao));
    for (int i = 0; i < strlen(auxDataTransacao); i++)
    {
        if (auxDataTransacao[i] == '\n')
            auxDataTransacao[i] = '\0';
    }
    strcpy(novaTransacao->dataTransacao, auxDataTransacao);

    if (inicioTransacao == NULL) {
        inicioTransacao = novaTransacao;
    }
    else {
        Transacao* transacaoAtual = inicioTransacao;
        while (transacaoAtual->seguinteTransacao != NULL) {
            transacaoAtual = transacaoAtual->seguinteTransacao;
        }
        transacaoAtual->seguinteTransacao = novaTransacao;
    }
        novaTransacao->seguinteTransacao = NULL;
        inicioTransacao = novaTransacao;
    return inicioTransacao;
}
#pragma endregion
// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE TRANSACOES----------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE CIDADES----------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAÇÃO DE CIDADES

/**
 * Le do ficheiro e cria o grafo a partir dos valores lidos. Esta funcao e executada em primeiro lugar
 * Para ser possivel para a funcao lerFicheirAdjacentes executar.
 * 
 * \FunctionName lerFicheiroVertices
 * \param inicioGrafo
 * \param inicioMeios
 * \param dadosGrafo
 * \return Grafo
 */
Grafo* lerFicheiroVertices(Grafo* inicioGrafo,Meio* inicioMeios, FILE* dadosGrafo)
{
    char* tokenVertice;
    if (dadosGrafo == NULL)
    { 
        printf("O ficheiro nao existe.\n"); 
        return 0;
    }
    char linha[tamanhoLinha];
    while (fgets(linha, tamanhoLinha, dadosGrafo))
    {
            tokenVertice = strtok(linha, ";");
            while (tokenVertice != NULL)
            {
                int pos = strcspn(tokenVertice, "\n");
                tokenVertice[pos] = '\0';
                Grafo* novoNodo = malloc(sizeof(Grafo));
                strcpy(novoNodo->vertice, tokenVertice);
                novoNodo->meios = NULL;
                novoNodo->adjacentes = NULL;
                novoNodo->seguinteVertice = inicioGrafo;
                inicioGrafo = novoNodo;
                tokenVertice = strtok(NULL, ";");
            }
    }
    return inicioGrafo;
}

/**
 * Le do ficheiro e cria os adjacentes dos vertices existentes, a partir dos valores lidos.
 * 
 * \FunctionName lerFicheiroAdjacentes
 * \param inicioGrafo
 * \param dadosAdjacentes
 * \return Grafo
 */
Grafo* lerFicheiroAdjacentes(Grafo* inicioGrafo, FILE* dadosAdjacentes)
{
    Adjacente* novoAdj = NULL;
    Grafo* aux = inicioGrafo;
    int inserido = 0;
    char* vertice, * adjacente, * peso, linha[tamanhoLinha];
    while (fgets(linha, tamanhoLinha, dadosAdjacentes))
    {
        inserido = 0;
        vertice = strtok(linha, ";");
        aux = inicioGrafo;
        while (inserido != 1)
        {
            while (aux != NULL)
            {
                if (strcmp(aux->vertice, vertice) == 0)
                {
                    while (vertice != NULL)
                    {
                        if (novoAdj == NULL)
                        {
                            novoAdj = malloc(sizeof(Adjacente));
                            adjacente = strtok(NULL, "/");
                            peso = strtok(NULL, ";");
                            strcpy(novoAdj->vertice, adjacente);
                            novoAdj->peso = atof(peso);
                            novoAdj->seguinteAdjacente = aux->adjacentes;
                            aux->adjacentes = novoAdj;
                        }
                        else
                        {
                            if (vertice != NULL) {
                                adjacente = strtok(NULL, "/");
                                peso = strtok(NULL, ";");
                                if (adjacente == NULL || peso == NULL)
                                {
                                    vertice = NULL;
                                    inserido = 1;
                                    break;
                                }
                                novoAdj = malloc(sizeof(Adjacente));
                                strcpy(novoAdj->vertice, adjacente);
                                novoAdj->peso = atof(peso);
                                if (aux->adjacentes == NULL) 
                                {
                                    aux->adjacentes = novoAdj;
                                    novoAdj->seguinteAdjacente = NULL;
                                }
                                else 
                                {
                                    novoAdj->seguinteAdjacente = aux->adjacentes->seguinteAdjacente;
                                    aux->adjacentes->seguinteAdjacente = novoAdj;
                                }
                            }
                        }
                    }
                }
                aux = aux->seguinteVertice;
                if (inserido == 1)
                    break;
            }
        }
    }
    return inicioGrafo;
}

/**
 * Funcao para fixar os clientes ao grafo.
 * 
 * \FunctionName adicionarClientesGrafo
 * \param inicioGrafo
 * \param inicioClientes
 * \return Grafo
 */
Grafo* adicionarClientesGrafo(Grafo* inicioGrafo, Cliente* inicioClientes)
{
    int teste = 0;
    Grafo* aux = inicioGrafo;
    while (aux != NULL)
    {
        teste = 0;
        Cliente* auxClientes = inicioClientes;
        while (auxClientes != NULL)
        {
            if (strcmp(auxClientes->geocodigo, aux->vertice) == 0)
            {
                aux->clientes = auxClientes;
                teste = 1;
            }
            auxClientes = auxClientes->seguinteCliente;
        }
        if (teste == 0)
        {
            aux->clientes = NULL;
        }
        aux = aux->seguinteVertice;
    }
    return inicioGrafo->clientes;
}

/**
 *  Funcao para fixar os meios ao grafo.
 * 
 * \FunctionName adicionarMeiosGrafo
 * \param inicioGrafo
 * \param inicioMeios
 * \return Grafo
 */
Grafo* adicionarMeiosGrafo(Grafo* inicioGrafo, Meio* inicioMeios)
{
    Grafo* aux = inicioGrafo;
    while (aux != NULL)
    {
        Meio* auxMeio = inicioMeios;
        Meio* meios = NULL;
        Meio* meioAnterior = NULL;
        while (auxMeio != NULL)
        {
            if (strcmp(auxMeio->geocodigo, aux->vertice) == 0)
            {
                Meio* novoMeio = malloc(sizeof(Meio));
                memcpy(novoMeio, auxMeio, sizeof(Meio));
                novoMeio->seguinteMeio = NULL;
                if (meios == NULL)
                {
                    meios = novoMeio;
                    meioAnterior = novoMeio;
                }
                else
                {
                    meioAnterior->seguinteMeio = novoMeio;
                    meioAnterior = novoMeio;
                }
            }
            auxMeio = auxMeio->seguinteMeio;
        }
        aux->meios = meios;
        aux = aux->seguinteVertice;
    }
    return inicioGrafo->meios;
}

/**
 * Funcao para fixar os meios aos adjacentes.
 * 
 * \FunctionName adicionarMeiosAdjacente
 * \param inicioGrafo
 * \param inicioMeios
 * \return Adjacente
 */
Adjacente* adicionarMeiosAdjacente(Grafo* inicioGrafo, Meio* inicioMeios)
{
    Grafo* auxGrafo = inicioGrafo;
    while (auxGrafo != NULL)
    {
        Adjacente* auxAdj = auxGrafo->adjacentes;
        while (auxAdj != NULL)
        {
            Meio* auxMeio = inicioMeios;
            Meio* meios = NULL;
            Meio* meioAnterior = NULL;
            while (auxMeio != NULL)
            {
                if (strcmp(auxMeio->geocodigo, auxAdj->vertice) == 0)
                {
                    Meio* novoMeio = malloc(sizeof(Meio));
                    memcpy(novoMeio, auxMeio, sizeof(Meio));
                    novoMeio->seguinteMeio = NULL;
                    if (meios == NULL)
                    {
                        meios = novoMeio;
                        meioAnterior = novoMeio;
                    }
                    else
                    {
                        meioAnterior->seguinteMeio = novoMeio;
                        meioAnterior = novoMeio;
                    }
                }
                auxMeio = auxMeio->seguinteMeio;
            }
            auxAdj->meios = meios;
            auxAdj = auxAdj->seguinteAdjacente;
        }
        auxGrafo = auxGrafo->seguinteVertice;
    }
    return inicioGrafo->adjacentes;
}

/**
 * Dado um raio de distancia, e localizado o veiculo a partir do geocodigo do utilizador inserido.
 * 
 * \FunctionName localizacaoRaio
 * \param inicioGrafo
 * \param inicioClientes
 * \param raio
 * \param codigo
 * \param tipoMeio
 * \return ResFuncoes
 */
ResFuncoes localizacaoRaio(Grafo* inicioGrafo, Cliente* inicioClientes, float raio, int codigo, char tipoMeio[])
{
    Grafo* aux = inicioGrafo;
    Cliente* auxClientes = inicioClientes;
    char geocodigoProcurar[100];
    int print = 0, existe = 0;
    if (!existeClienteCod(auxClientes, codigo))
    {
        while (auxClientes->codigo != codigo)
            auxClientes = auxClientes->seguinteCliente;
    }
    else
    {
        return clientesNaoExistem;
    }
    strcpy(geocodigoProcurar, auxClientes->geocodigo);
    while (strcmp(geocodigoProcurar, aux->vertice) != 0)
    {
        aux = aux->seguinteVertice;
    }
    if ((strcmp(aux->meios->tipo, tipoMeio) == 0) && (strcmp(aux->meios->geocodigo, geocodigoProcurar) == 0))
    {
        printf("O veiculo pretendido esta na sua localizacao.\n");
        return SUCESSO;
    }
    Adjacente* auxAdj = aux->adjacentes;
    while (auxAdj != NULL)
    {
        Grafo* auxMeio = inicioGrafo;
        if (raio >= auxAdj->peso)
        {
            while (auxMeio != NULL  && strcmp(auxAdj->vertice, auxMeio->vertice) != 0)
            {
                auxMeio = auxMeio->seguinteVertice;
            }
            while (auxMeio->meios != NULL)
            {
                if (strcmp(auxMeio->meios->tipo, tipoMeio) == 0)
                {
                    printf("Existe o meio %s na localizacao %s.\n", auxMeio->meios->tipo, auxAdj->vertice);
                    print = 1;
                }
                auxMeio->meios = auxMeio->meios->seguinteMeio;
            }
        }
        auxAdj = auxAdj->seguinteAdjacente;
    }
    if (print == 0)
    {
        return ERRO;
    }
    return SUCESSO;
}

/**
 * Verificar se todos os meios e clientes foram, colocados com sucesso no grafo.
 * 
 * \FunctionName printtestgrafo
 * \param inicioGrafo
 */
void printtestgrafo(Grafo* inicioGrafo)
{
    Grafo* aux = inicioGrafo;
    while (aux != NULL)
    {
        printf("%s:\n", aux->vertice);
        while (aux->meios != NULL)
        {
            printf("Meios: %s \n", aux->meios->tipo);
            aux->meios = aux->meios->seguinteMeio;
        }
        //while (aux->clientes != NULL)
        //{
        //    printf("Cliente: %s \n", aux->clientes->nome);
        //    aux->clientes = aux->clientes->seguinteCliente;
        //}
        //while (aux->meios != NULL)
        //{
        //    printf("Meios: %s \n", aux->meios->tipo);
        //    aux->meios = aux->meios->seguinteMeio;
        //}
    aux = aux->seguinteVertice;
    }
}

/**
 * Lista o grafo.
 * 
 * \FunctionName listarGrafo
 * \param inicioGrafo
 */
void listarGrafo(Grafo* inicioGrafo)
{
    char aux[100];
    char continuar=0;
    printf("Localizacoes existentes:\n");
    while (inicioGrafo != NULL)
    {
        printf("->");
        strcpy(aux, inicioGrafo->vertice);
        int pos = strcspn(inicioGrafo->vertice, "\n");
        inicioGrafo->vertice[pos] = '\0';
        printf("%s\n", inicioGrafo->vertice);
        inicioGrafo = inicioGrafo->seguinteVertice;
    }
    printf("Prima espaco e de seguida enter para sair.");
    while (continuar != " ")
    {
        scanf("%c", &continuar);
        if (continuar == ' ')
        {
            printf("Voltando ao menu.\n");
            Sleep(2000);
            system("cls");
            return 0;
        }
    }
}

/**
 * Lista os adjacentes.
 * 
 * \FunctionName listarAdjacentes
 * \param inicioGrafo
 */
void listarAdjacentes(Grafo* inicioGrafo)
{
    char continuar = 0;
    while (inicioGrafo != NULL)
    {
        printf("Dados de %s:\n------------------------------------------------------------------------------------------------------------------------\n", inicioGrafo->vertice);
        printf("Esta localizacao pode ir para:\n");
        if (inicioGrafo->adjacentes == NULL)
        {
            printf("A localizacao %s nao tem destinos.\n", inicioGrafo->vertice);
        }
        while (inicioGrafo->adjacentes != NULL)
        {
            printf("%s com distancia de %.2f km; \n", inicioGrafo->adjacentes->vertice, inicioGrafo->adjacentes->peso);
            inicioGrafo->adjacentes = inicioGrafo->adjacentes->seguinteAdjacente;
        }
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        printf("\n");
        inicioGrafo = inicioGrafo->seguinteVertice;
    }
    printf("Prima qualquer tecla para sair.");
    getchar();
    while (1)
    {
        if (getchar())
        {
            printf("Voltando ao menu.\n");
            Sleep(2000);
            system("cls");
            return SUCESSO;
        }
    }
}

/**
 * Funcao para verificar se existe um dado vertice, dentro do grafo.
 * 
 * \FunctionName existeVertice
 * \param inicioGrafo
 * \param verticeVerificar
 * \return int
 */
int existeVertice(Grafo* inicioGrafo, char verticeVerificar[])
{
    Grafo* aux = inicioGrafo;
    while (aux != NULL)
    {
        if (strcmp(verticeVerificar, aux->vertice) == 0)
        {
            return 1;
        }
        aux = aux->seguinteVertice;
    }
    return 0;
}

/**
 * Funcao para inserir um vertice, sendo introduzido pelo utilizador
 * 
 * \FunctionName inserirVertice
 * \param inicioGrafo
 * \param verticeInserir
 * \return int
 */
int inserirVertice(Grafo* inicioGrafo, char verticeInserir[])
{
    Grafo* aux = inicioGrafo;
    if (existeVertice(inicioGrafo, verticeInserir) == 1)
    {
        return verticeExiste;
    }
    while (inicioGrafo != NULL)
    {
        if (inicioGrafo->seguinteVertice == NULL)
        {
            Grafo* novoVertice = malloc(sizeof(Grafo));
            strcpy(novoVertice->vertice, verticeInserir);
            novoVertice->adjacentes = NULL;
            novoVertice->meios = NULL;
            novoVertice->clientes = NULL;
            inicioGrafo->seguinteVertice = novoVertice;
            novoVertice->seguinteVertice = NULL;
            inicioGrafo = novoVertice;
        }
        inicioGrafo = inicioGrafo->seguinteVertice;
    }
    return inicioGrafo, 1;
}

/**
 * E copiada a ordem do grafo para uma array bidimensional e de seguida escrita para um ficheiro
 * 
 * \FunctionName escreverFicheiroGrafo
 * \param inicioGrafo
 * \param dadosGrafo
 */
void escreverFicheiroGrafo(Grafo* inicioGrafo, FILE* dadosGrafo)
{
    Grafo* aux = inicioGrafo;
    if (inicioGrafo == NULL)
    {
        return;
    }
    dadosGrafo = fopen("vertices.txt", "wt");
    if (dadosGrafo == NULL)
    {
        return;
    }
    char listaCopiada[20][50];
    int iterador = 0;
    while (aux != NULL)
    {
        strcpy(listaCopiada[iterador], aux->vertice);
        aux = aux->seguinteVertice;
        iterador++;
    }
    for (int i = iterador; i > 0; i--)
    {
        fprintf(dadosGrafo, "%s;", listaCopiada[iterador-1]);
        iterador--;
    }
    fclose(dadosGrafo);
}
 
/**
 * E copiada a ordem do grafo para uma array bidimensional e de seguida escrita para um ficheiro binario
 * 
 * \FunctionName escreverFicheiroGrafoBin
 * \param inicioGrafo
 * \param dadosGrafo
 */
void escreverFicheiroGrafoBin(Grafo* inicioGrafo, FILE* dadosGrafo)
{
    Grafo* aux = inicioGrafo;
    if (inicioGrafo == NULL)
    {
        return 1;
    }
    dadosGrafo = fopen("vertices.bin", "wt");
    if (dadosGrafo == NULL)
    {
        return 2;
    }
    char listaCopiada[20][50];
    int iterador = 0;
    while (aux != NULL)
    {
        strcpy(listaCopiada[iterador], aux->vertice);
        aux = aux->seguinteVertice;
        iterador++;
    }
    for (int i = iterador; i > 0; i--)
    {
        fprintf(dadosGrafo, "%s;", listaCopiada[iterador - 1]);
        iterador--;
    }
    fclose(dadosGrafo);
}

/**
 * E copiada a ordem dos adjacentes de todos os vertices para uma array bidimensional e de seguida escrita para um ficheiro
 * 
 * \FunctionName escreverFicheiroAdjacentes
 * \param inicioGrafo
 * \param dadosAdjacentes
 */
void escreverFicheiroAdjacentes(Grafo* inicioGrafo, FILE* dadosAdjacentes)
{
    Grafo* aux = inicioGrafo;
    if (inicioGrafo == NULL)
    {
        return 1;
    }
    char listaCopiada[20][250];
    int iterador = 0;
    char linha[tamanhoLinha];
    while (aux != NULL)
    {
        fgets(linha, tamanhoLinha, dadosAdjacentes);
        strcpy(listaCopiada[iterador], linha);
        aux = aux->seguinteVertice;
        iterador++;
    }
    dadosAdjacentes = fopen("adjacentes.txt", "wt");
    if (dadosAdjacentes == NULL)
    {
        return 2;
    }
    for (int i = 0; i < iterador; i++)
    {
        fprintf(dadosAdjacentes,"%s", listaCopiada[i]);
    }
    fclose(dadosAdjacentes);
}

/**
 * E copiada a ordem dos adjacentes de todos os vertices para uma array bidimensional e de seguida escrita para um ficheiro binario
 * 
 * \FunctionName escreverFicheiroAdjacentesBin
 * \param inicioGrafo
 * \param dadosAdjacentes
 */
void escreverFicheiroAdjacentesBin(Grafo* inicioGrafo, FILE* dadosAdjacentes)
{
    Grafo* aux = inicioGrafo;
    if (inicioGrafo == NULL)
    {
        return 1;
    }
    char listaCopiada[20][250];
    int iterador = 0;
    char linha[tamanhoLinha];
    while (aux != NULL)
    {
        fgets(linha, tamanhoLinha, dadosAdjacentes);
        strcpy(listaCopiada[iterador], linha);
        aux = aux->seguinteVertice;
        iterador++;
    }
    dadosAdjacentes = fopen("adjacentes.bin", "wt");
    if (dadosAdjacentes == NULL)
    {
        return 2;
    }
    for (int i = 0; i < iterador; i++)
    {
        fprintf(dadosAdjacentes, "%s", listaCopiada[i]);
    }
    fclose(dadosAdjacentes);
}

/**
 * Funcao para verificar se existe um adjacente de algum vertice existente.
 * 
 * \FunctionName existeAdjacente
 * \param inicioGrafo
 * \param verticeFinal
 * \return int
 */
int existeAdjacente(Grafo* inicioGrafo, char verticeFinal[])
{
    Grafo* aux = inicioGrafo;
    while (aux != NULL)
    {
        if (strcmp(aux->vertice, verticeFinal) == 0)
        {
            return 1;
        }
        aux = aux->seguinteVertice;
    }
    return 0;
}


/**
 * Funcao para inserir um novo adjacente, tendo em conta o vertice inicial, adjacente e peso.
 * 
 * \FunctionName inserirAdjacente
 * \param inicioGrafo
 * \param verticeInicial
 * \param verticeFinal
 * \param peso
 * \return int
 */
int inserirAdjacente(Grafo* inicioGrafo, char verticeInicial[], char verticeFinal[], float peso)
{
    Grafo* aux = inicioGrafo;
    int existeVert = 0, existeAdj = 0;
    existeVert = existeVertice(aux, verticeInicial);
    existeAdj = existeAdjacente(aux, verticeFinal);
    if (existeVert)
    {
        while (!strcmp(aux->vertice, verticeInicial)==0)
            aux = aux->seguinteVertice;
        if (!existeAdj)
        {
            Adjacente* novoAdj = malloc(sizeof(Adjacente));
            strcpy(novoAdj->vertice, verticeFinal);
            novoAdj->peso = peso;
            novoAdj->seguinteAdjacente = aux->adjacentes;
            aux->adjacentes = novoAdj;
            inicioGrafo = aux;
            return inicioGrafo,adjacenteInserido;
        }
        else
        {
            return adjacenteExiste;
        }
    }
    return 0;
}

/**
 * Indica quantos vertices existem no grafo.
 * 
 * \FunctionName totalVertices
 * \param inicioGrafo
 * \return int
 */
int totalVertices(Grafo* inicioGrafo)
{
    int total = 0;
    Grafo* aux = inicioGrafo;
    while (aux != NULL && aux->seguinteVertice !=NULL)
    {
        aux = aux->seguinteVertice;
        total++;
    }
    return total;
}

/**
 * Algoritmo para mostrar o ciclo de um vertice base, percorrer todos os vertices existentes.
 * 
 * \FunctionName mostrarCaminhoIda
 * \param inicioGrafo
 * \param verticeAtual
 * \param inicioStack
 * \param inicioLista
 * \param Tamanho
 * \return ListaStack
 */
ListaStack* mostrarCaminhoIda(Grafo* inicioGrafo, char verticeAtual[], Stack* inicioStack, ListaStack* inicioLista, float Tamanho)
{
    Grafo* aux = inicioGrafo;
    Stack* auxStack = inicioStack;
    Adjacente* auxAdj = NULL;
    if (existeVertice(aux, verticeAtual))
    {
        while (aux != NULL)
        {
            if (strcmp(aux->vertice, verticeAtual) == 0)
            {
                auxStack = inserirStack(auxStack, aux->vertice);
                inicioStack = auxStack;
                break;
            }
            aux = aux->seguinteVertice;
        }
    }
    else
    {
        return NULL;
    }
    if (todosVisitados(inicioStack, inicioGrafo))
    {
        ListaStack* novaListaStack = malloc(sizeof(ListaStack));
        novaListaStack->novaStack = inicioStack;
        novaListaStack->tamanho = Tamanho;
        novaListaStack->seguinteLista = inicioLista;
        inicioLista = novaListaStack;
        Tamanho = 0;
        return inicioLista;
    }

    auxAdj = aux->adjacentes;
    while (auxAdj != NULL)
    {
        if (!verticeVisitado(inicioStack, auxAdj->vertice))
        {
            Stack* novaStack = NULL;
            Stack* auxStack2 = inicioStack;
            while (auxStack2 != NULL)
            {
                Stack* novoNodo = malloc(sizeof(Stack));
                strcpy(novoNodo->vertice, auxStack2->vertice);
                novoNodo->seguinteStack = NULL;
                if (novaStack == NULL)
                    novaStack = novoNodo;
                else
                {
                    Stack* aux = novaStack;
                    while (aux->seguinteStack != NULL)
                        aux = aux->seguinteStack;
                    aux->seguinteStack = novoNodo;
                }
                auxStack2 = auxStack2->seguinteStack;
            }
            if (novaStack != NULL)
            {
                novaStack->visitado = true;
            }  
            inicioLista = mostrarCaminhoIda(inicioGrafo, auxAdj->vertice, novaStack, inicioLista, Tamanho + auxAdj->peso);
        }
        auxAdj = auxAdj->seguinteAdjacente;
    }
    return inicioLista;
}

/**
 * Algoritmo para mostrar o caminho de volta, onde o vertice destino sera o vertice base da funcao acima e o atual, ira ser retirado usando a funcao obterUltimoVertice
 * 
 * \FunctionName mostrarCaminhoVolta
 * \param inicioGrafo
 * \param verticeAtual
 * \param verticeDestino
 * \param inicioStack
 * \param inicioLista
 * \param Tamanho
 * \return ListaStack
 */
ListaStack* mostrarCaminhoVolta(Grafo* inicioGrafo, char verticeAtual[],char verticeDestino[], Stack* inicioStack, ListaStack* inicioLista, float Tamanho)
{
    Grafo* aux = inicioGrafo;
    Stack* auxStack = inicioStack;
    Adjacente* auxAdj = NULL;
    if (existeVertice(aux, verticeAtual))
    {
        while (aux != NULL)
        {
            if (strcmp(aux->vertice, verticeAtual) == 0)
            {
                auxStack = inserirStack(auxStack, aux->vertice);
                inicioStack = auxStack;
                break;
            }
            aux = aux->seguinteVertice;
        }
    }
    if (strcmp(verticeDestino, verticeAtual)==0)
    {
        ListaStack* novaListaStack = malloc(sizeof(ListaStack));
        novaListaStack->novaStack = inicioStack;
        novaListaStack->tamanho = Tamanho;
        novaListaStack->seguinteLista = inicioLista;
        inicioLista = novaListaStack;
        Tamanho = 0;
        return inicioLista;
    }

    auxAdj = aux->adjacentes;
    while (auxAdj != NULL)
    {
        if (!verticeVisitado(inicioStack, auxAdj->vertice))
        {
            Stack* novaStack = NULL;
            Stack* auxStack2 = inicioStack;
            while (auxStack2 != NULL)
            {
                Stack* novoNodo = malloc(sizeof(Stack));
                strcpy(novoNodo->vertice, auxStack2->vertice);
                novoNodo->seguinteStack = NULL;
                if (novaStack == NULL)
                    novaStack = novoNodo;
                else
                {
                    Stack* aux = novaStack;
                    while (aux->seguinteStack != NULL)
                        aux = aux->seguinteStack;
                    aux->seguinteStack = novoNodo;
                }
                auxStack2 = auxStack2->seguinteStack;
            }
            if (novaStack != NULL)
            {
                novaStack->visitado = true;
            }
            inicioLista = mostrarCaminhoVolta(inicioGrafo, auxAdj->vertice,verticeDestino, novaStack, inicioLista, Tamanho + auxAdj->peso);
        }
        auxAdj = auxAdj->seguinteAdjacente;
    }
    return inicioLista;
}

/**
 * Funcao para adicionar novos caminhos a uma lista de caminhos.
 * 
 * \FunctionName adicionarCaminho
 * \param caminho
 * \param listaCaminhos
 * \param tamanho
 * \return ListaStack
 */
ListaStack* adicionarCaminho(Stack* caminho, ListaStack* listaCaminhos, float tamanho)
{
    ListaStack* novoCaminho = malloc(sizeof(ListaStack));
    novoCaminho->novaStack = caminho;
    novoCaminho->tamanho = tamanho;
    novoCaminho->seguinteLista = listaCaminhos;
    return novoCaminho;
}

// 
/**
 * Funcao auxiliar do algoritmo de dijsktra.
 * 
 * \FunctionName todosVisitados
 * \param inicioStack
 * \param inicioGrafo
 * \return int
 */
int todosVisitados(Stack* inicioStack, Grafo* inicioGrafo)
{
    Grafo* aux = inicioGrafo;
    while (aux != NULL)
    {
        Stack* auxStack = inicioStack;
        while (auxStack !=NULL)
        {
            if (strcmp(auxStack->vertice, aux->vertice) == 0)
                break;
            auxStack = auxStack->seguinteStack;
        }
        if (auxStack == NULL)
            return 0;
        if (!verticeVisitado(inicioStack, aux->vertice))
        {
            return 0;
        }
        aux = aux->seguinteVertice;
    }
    return 1;
}

/**
 * Funcao auxiliar do algoritmo de dijsktra.
 * 
 * \FunctionName verticeVisitado
 * \param inicioStack
 * \param vertice
 * \return bool
 */
bool verticeVisitado(Stack* inicioStack, char vertice[])
{
    Stack* auxStack = inicioStack;
    while (auxStack != NULL)
    {
        if (strcmp(auxStack->vertice, vertice) == 0)
        {
            return true;
        }
        auxStack = auxStack->seguinteStack;
    }
    return false;
}
#pragma endregion

#pragma region STACK

/**
 * Insere um novo endereco de memoria numa estrutura de dados stack
 * 
 * \FunctionName inserirStack
 * \param inicioStack
 * \param vertice
 * \return Stack
 */
Stack* inserirStack(Stack* inicioStack, char vertice[])
{
    Stack* aux = inicioStack;
    if (inicioStack == NULL)
    {
        Stack* novoStack = malloc(sizeof(Stack));
        strcpy(novoStack->vertice, vertice);
        novoStack->visitado = true;
        novoStack->seguinteStack = inicioStack;
        return novoStack;
    }
    else
    {
        while (inicioStack->seguinteStack != NULL)
        {
            inicioStack = inicioStack->seguinteStack;
        }
        Stack* novoStack = malloc(sizeof(Stack));
        strcpy(novoStack->vertice, vertice);
        novoStack->seguinteStack = NULL;
        inicioStack->seguinteStack = novoStack;
    }
    return aux;  
}
 
/**
 * De todas as listas da stack criadas, compara o tamanho de todas e apenas fica a com menor tamanho.
 * 
 * \FunctionName retirarStackMaior
 * \param inicioLista
 * \return ListaStack
 */
ListaStack* retirarStackMaior(ListaStack* inicioLista)
{
    ListaStack* aux = inicioLista, * anterior = NULL;
    float menorcaminho = aux->tamanho;
    while (aux != NULL)
    {
        float auxCaminho;
        auxCaminho = aux->tamanho;
        if (auxCaminho < menorcaminho)
            menorcaminho = aux->tamanho;
        aux = aux->seguinteLista;

    }
    aux = inicioLista;
    while (aux != NULL)
    {
        if (aux->tamanho > menorcaminho)
        {
            if (anterior != NULL)
            {
                anterior->seguinteLista = aux->seguinteLista;
            }
            else
            {
                inicioLista = aux->seguinteLista;
            }
            ListaStack* auxRemover = aux;
            aux = aux->seguinteLista;
            free(auxRemover);
        }
        else
        {
            anterior = aux;
            aux = aux->seguinteLista;
        }
    }
    inicioLista = anterior;
    return inicioLista;
}

/**
 * Funcao para obter o ultimo vertice, de uma lista.
 * 
 * \FunctionName obterUltimoVertice
 * \param inicioLista
 * \param vertice
 */
void obterUltimoVertice(ListaStack* inicioLista, char* vertice)
{
    ListaStack* auxLista = inicioLista;
    while (auxLista != NULL)
    {
        Stack* auxStack = inicioLista->novaStack;
        while (auxStack->seguinteStack != NULL)
        {
            auxStack = auxStack->seguinteStack;
        }
        strcpy(vertice, auxStack->vertice);
        auxLista = auxLista->seguinteLista;
    }
    return 1;
}

/**
 * Funcao que mostra o caminho armazenado numa listaStack.
 * 
 * \FunctionName mostrarCaminho
 * \param inicioLista
 */
void mostrarCaminho(ListaStack* inicioLista) {
    if (inicioLista == NULL)
    {
        printf("Caminho nao encontrado.\n");
        return;
    }
    ListaStack* auxLista = inicioLista;
    while (auxLista != NULL)
    {
        Stack* auxStack = auxLista->novaStack;
        while (auxStack != NULL)
        {
            printf("%s", auxStack->vertice);
            if (auxStack->seguinteStack != NULL)
            {
                printf(" -> ");
            }
            auxStack = auxStack->seguinteStack;
        }
        printf("\n");
        auxLista = auxLista->seguinteLista;
    }
}
#pragma endregion

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE CIDADES----------------------------------------------------
