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

//Menu do gestor. Retorna a op��o escolhida pelo gestor, para executar uma tarefa.
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
    printf("0- Sair.\n");
    printf("A sua escolha:");
    scanf("%d", &escolha);

    return escolha;
}

#pragma endregion

#pragma region menuUtilizador

//Menu do utilizador. Retorna o valor escolhido, para execu��o de uma tarefa.
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


// -------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTA��O DE MEIOS-------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTA��O DE MEIOS
// Ler ficheiro de texto, contendo informa��o sobre os meios.
// Ser�o todos os dados, inseridos numa lista ligada, que de inicio � vazia.
Meio* lerFicheiroMeios(Meio* inicioMeios, FILE* dadosMeios)
{
    // Defini��o de vari�veis.
    char linha[tamanhoLinha];
    // Usando a fun��o fgets, lemos a partir do ficheiro dadosMeios todo o seu conte�do, onde � armazenado em cada novoNodo criado
    // Depois � atribuido ao inicio o valor de cada nodo criado, de seguida fechamos o ficheiro e por fim damos return da variavel inicio,
    // Contendo assim toda as informa��es e pointers necess�rios para criar a lista ligada.
    while (fgets(linha, tamanhoLinha, dadosMeios))
    {
        // Enquanto � possivel obter texto do ficheiro dadosMeios, ir� ser criado um novo espa�o na mem�ria para a struct meios
        // A cada itera��o � atribuido todo o conteudo obtido ao inicioMeios, criando assim uma lista ligada.
        Meio* novoNodo = malloc(sizeof(Meio));
        if (novoNodo == NULL)
        {
            return 0;
        }
        sscanf(linha, "%d;%[^;];%f;%f;%d;%[^;];%d\n", &novoNodo->codigo, novoNodo->tipo, &novoNodo->bateria, &novoNodo->autonomia, &novoNodo->custo, novoNodo->geocodigo, &novoNodo->ativo);
        // O seguinte valor de mem�ria � igual a inicioMeios que foi inicializado a NULL, para de seguida ser possivel atribuir outro elemento da lista ligada.
        novoNodo->seguinteMeio = inicioMeios;
        // Inicio_meios vai obter toda a informa��o que foi lida por novoNodo
        inicioMeios = novoNodo;
    }
    fclose(dadosMeios);
    return inicioMeios;
}

// Apresenta na consola toda a informa��o existente sobre os clientes.
ResFuncoes listarMeios(Meio* inicioMeios)
{
    system("cls");
    if (inicioMeios == NULL)
    {
        return meiosNaoExistem;
    }
    else
    {
        // Enquanto o pointer inicioMeios n�o for NULL (que esse mesmo est� sempre a apontar para um valor de mem�ria diferente na lista ligada)
        // � apresentada a informa��o dos meios.
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

// Escreve todos os dados inseridos sobre os meios, em ficheiro de texto.
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

// Escreve todos os dados inseridos sobre os meios, em ficheiro bin�rio.
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
}

// Verifica, consoante o endere�o de mem�ria de certo meio, se o seu c�digo � igual ao que foi inserido para um novo meio.
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

// Verifica cada meio existente, se o seu valor de autonomia do elemento que est� a verificar for maior que o elemento seguinte, ir� ser feita uma troca
// para ordenar todos os elementos da lista ligada por um valor decrescente a nivel de autonomia.
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
}

//Colocar todos os meios com o campo recolhido a 0.
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

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTA��O DE MEIOS--------------------------------------------------------


// --------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTA��O DE CLIENTES--------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTA��O DE CLIENTES

// Ler ficheiro de texto, contendo informa��o sobre os clientes.
// Ser�o todos os dados, inseridos numa lista ligada, que de inicio � vazia.
Cliente* lerFicheiroClientes(Cliente* inicioClientes, FILE* dadosClientes)
{
    // Defini��o de vari�veis.
    char linha[tamanhoLinha];

    //Usando a fun��o fgets, lemos a partir do ficheiro dadosClientes todo o seu conte�do, onde � armazenado em cada novoNodo criado
    //Depois � atribuido ao inicio o valor de cada nodo criado, de seguida fechamos o ficheiro e por fim damos return da variavel inicio,
    //Contendo assim toda as informa��es e pointers necess�rios para criar a lista ligada.

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

// Apresenta na consola toda a informa��o existente sobre os clientes.
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
        // Enquanto o pointer inicioClientes n�o for NULL (que esse mesmo est� sempre a apontar para um valor de mem�ria diferente na lista ligada)
        // � apresentada a informa��o dos clientes.
        while (inicioClientes != NULL)
        {
            printf("Codigo:%d    Nome:%s     NIF:%d      Saldo:%d   Geocodigo:%s\n", inicioClientes->codigo, inicioClientes->nome, inicioClientes->NIF, inicioClientes->saldo, inicioClientes->geocodigo);
            inicioClientes = inicioClientes->seguinteCliente;
        }
        printf("------------------------------------------------------------------------------------------------------------------------");
    }
}

// Escreve todos os dados inseridos sobre os clientes, em ficheiro de texto.
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
}

// Escreve todos os dados inseridos sobre os clientes, em ficheiro bin�rio.
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
}

// Verifica, consoante o endere�o de mem�ria de um certo utilizador, se o seu c�digo � igual ao que foi inserido para um novo utilizador.
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

// Verifica, consoante o endere�o de mem�ria de um certo utilizador, se o seu NIF � igual ao que foi inserido para um novo utilizador.
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

// Verifica cada cliente existente, se o seu codigo do elemento que est� a verificar for maior que o elemento seguinte, ir� ser feita uma troca
// para ordenar todos os elementos da lista ligada por um valor crescente.
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

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTA��O DE CLIENTES----------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTA��O DE GESTORES----------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTA��O DE GESTORES

// Ler ficheiro de texto, contendo informa��o sobre os gestores.
// Ser�o todos os dados, inseridos numa lista ligada, que de inicio � vazia.
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

// Apresenta na consola toda a informa��o existente sobre os gestores.
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

// Escreve todos os dados inseridos sobre os gestores, em ficheiro de texto.
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

// Escreve todos os dados inseridos sobre os gestores, em ficheiro bin�rio.
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

// Verifica, consoante o endere�o de mem�ria de um certo gestor, se o seu c�digo � igual ao que foi inserido para um novo gestor.
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

// Verifica cada gestor existente, se o seu codigo do elemento que est� a verificar for maior que o elemento seguinte, ir� ser feita uma troca
// para ordenar todos os elementos da lista ligada por um valor crescente.
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

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTA��O DE GESTORES----------------------------------------------------


// ---------------------------------------------------INICIO-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------
#pragma region INSERIR

// Fun��o para entrar em modo gestor, no qual � pedido um codigo e uma senha. Caso sejam iguais ao que est� no ficheiro � garantido o acesso
// a fun��es de gestor.
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

// Fun��o para inserir um novo meio el�trico, � pedido ao gestor na fun��o main, um novo codigo, nome, nivel bateria, autonomia, o seu custo 
// e a sua geolocaliza��o. De seguida � inserido no ultimo lugar da lista ligada dos meios, quando � o ultimo endere�o NULL.
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

// Fun��o para inserir um novo cliente, � pedido ao gestor na fun��o main, um novo codigo, nome, NIF e saldo.  
// De seguida � inserido no ultimo lugar da lista ligada dos clientes, quando � o ultimo endere�o NULL.
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

// Fun��o para inserir um novo gestor, � pedido ao gestor na fun��o main, um novo codigo, nome e senha.  
// De seguida � inserido no ultimo lugar da lista ligada dos gestores, quando � o ultimo endere�o NULL.
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

// Pequena fun��o para encripta��o da senha do gestor.
int encryptSenha(Gestor* inicioGestor, char senha[])
{
    for (int i = 0; i < strlen(senha); i++)
    {
        senha[i] = senha[i] + 5;
    }
    return 1;
}

// Pequena fun��o para desencripta��o da senha do gestor.
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

// Fun��o para remover algum meio, a partir do c�digo inserido pelo gestor. � removido o meio e de seguida � retornada toda a lista ligada
// com o meio removido.
Meio* removerMeio(Meio* inicioMeios, int cod)
{
    Meio* anterior = inicioMeios, * atual = inicioMeios, * aux;

    if (atual == NULL) return(NULL); // Lista vazia.
    else if (atual->codigo == cod) // remo��o do 1� registo
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
        while ((atual != NULL) && (atual->codigo != cod)) // Itera��o at� ser igual.
        {
            anterior = atual;
            atual = atual->seguinteMeio;
        }
        if (atual == NULL) return(inicioMeios);
        else // Remo��o do meio com cod introduzido.
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

// Fun��o para remover algum cliente, a partir do c�digo inserido pelo gestor. � removido o cliente e de seguida � retornada toda a lista ligada
// com o meio removido.
Cliente* removerCliente(Cliente* inicioClientes, int cod)
{
    Cliente* anterior = inicioClientes, * atual = inicioClientes, * aux;

    if (atual == NULL) return(NULL); // Lista vazia.
    else if (atual->codigo == cod) // remo��o do 1� registo
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
        while ((atual != NULL) && (atual->codigo != cod)) // Itera��o at� ser igual.
        {
            anterior = atual;
            atual = atual->seguinteCliente;
        }
        if (atual == NULL) return(inicioClientes);
        else // Remo��o do cliente com cod introduzido.
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

// Fun��o para remover algum gestor, a partir do c�digo inserido pelo gestor. � removido o gestor e de seguida � retornada toda a lista ligada
// com o meio removido.
Gestor* removerGestor(Gestor* inicioGestores, int cod)
{
    Gestor* anterior = inicioGestores, * atual = inicioGestores, * aux;

    if (atual == NULL) return(NULL); // Lista vazia.
    else if (atual->codigo == cod) // remo��o do 1� registo
    {
        aux = atual->seguinteGestor;
        free(atual);
        printf("Gestor com cod %d removido com sucesso.\n", cod);
        return(aux);
    }
    else
    {
        while ((atual != NULL) && (atual->codigo != cod)) // Itera��o at� ser igual.
        {
            anterior = atual;
            atual = atual->seguinteGestor;
        }
        if (atual == NULL) return(inicioGestores); // Lista ligada toda percorrida, nao foi encontrado nenhum gestor com o codigo inserido.
        else // Remo��o do gestor com cod introduzido.
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

// Fun��o para altera��o de dados de algum gestor.
// Apenas � pedido o codigo de gestor. � possivel alterar codigo, nome, senha, area responsavel.
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

// Fun��o para altera��o de dados do cliente.
// � pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes � possivel fazer altera��o de nome, codigo e NIF.
ResFuncoes alterarDadosCliente(Cliente* inicioClientes, Transacao* inicioTransacao) {
    int codigo, NIF, novoCodigoigo, novoNIF, inserir = 1, escolha, codigoAux;
    char novoNome[50], novoGeocodigo[100];
    Cliente* aux = inicioClientes;
    Transacao* auxTrans = inicioTransacao;
    if (inicioClientes == NULL)
    {
       /* printf("Nao existem clientes.\n");
        Sleep(2000);
        system("cls");*/
        fprintf(stderr, "Nao existem clientes registados.\n");
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
        /*printf("O codigo %d, nao esta registado com o NIF %d.\n", codigo, NIF);
        Sleep(2000);
        system("cls");*/
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
                    scanf("%d", &novoCodigoigo);
                    if (existeClienteCod(aux, novoCodigoigo))
                    {
                        codigoAux = inicioClientes->codigo;
                        inicioClientes->codigo = novoCodigoigo;
                        printf("O seu novo codigo %d\n", inicioClientes->codigo);
                        if (existeClienteTransacao(auxTrans, codigoAux))
                        {
                            while (auxTrans != NULL )
                            {
                                if (auxTrans->codigoUtilizador == codigoAux)
                                {
                                    auxTrans->codigoUtilizador = novoCodigoigo;
                                }
                                auxTrans = auxTrans->seguinteTransacao;
                            }
                        }
                        Sleep(2000);
                        system("cls");
                    }
                    else
                    {
                        printf("O codigo %d ja existe.\n", novoCodigoigo);
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

// Fun��o para altera��o de dados de algum meio.
// � pedido o codigo do meio a alterar. � possivel alterar o seu codigo, tipo, se est� ativo, custo, bat, aut, etc...
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
// Fun��o para carregamento de saldo, de um certo utilizador.
// � pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes � possivel carregar o saldo desse mesmo utilizador.
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

// Fun��o para consulta de saldo, de um certo utilizador.
// � pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes � possivel visualizar quando saldo est� dispon�vel.
ResFuncoes consultaSaldo(Cliente* inicioClientes) {
    int codigo, NIF;
    printf("Introduza o seu codigo:");
    scanf("%d", &codigo);
    //printf("Introduza o seu NIF:");
    //scanf("%d", &NIF);
    if (inicioClientes == NULL)
    {
        return clientesNaoExistem;
    }
    while (inicioClientes != NULL)
    {
        if (inicioClientes->codigo == codigo /*&& inicioClientes->NIF == NIF*/)
        {
            printf("Voce tem %d de saldo.\n", inicioClientes->saldo);
            return saldoAtual;
        }
        inicioClientes = inicioClientes->seguinteCliente;
    }
    if (inicioClientes == NULL)
    {
        //printf("Nao existe o cliente com o cod %d.\n", codigo);
        return codNifNaoExiste;
    }
}

// Fun��o para realiza��o de aluguer de qualquer meio existente, que n�o esteja ativo.
// � pedido o codigo de utilizador, � verificado se existe esse mesmo utilizador. De seguida � perguntado qual o meio que deseja alugar. 
// S�o apresentados dados, tais como o tipo de meio, o seu custo e o saldo do utilizador. Caso o utilizador, decida comprar o meio
// � criado um novo registo na lista ligada de alugueres.
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

// Fun��o para listar na consola, todos os meios existentes com um certo geocodigo.
void listarGeocodigo(Meio* inicioMeios)
{
    system("cls");
    int verificado = 0, existe = 0;
    char verificarGeocodigo[50];
    Meio* auxPrint = inicioMeios;
    printf("Introduza o geocodigo que pretende verificar:");
    scanf("%s", verificarGeocodigo);
    getchar();

    if (inicioMeios == NULL)
        return 0;
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
        printf("Nao existe o geocodigo inserido.\n");
        Sleep(2000);
        system("cls");
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
}
#pragma endregion
// -----------------------------------------------------------------FIM_OP_UTILIZADOR-------------------------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTA��O DE ALUGUER----------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTA��O DE ALUGUER
// Ler ficheiro de texto, contendo informa��o sobre os alugueres.
// Ser�o todos os dados, inseridos numa lista ligada, que de inicio � vazia.
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

// Fun��o para listar na consola, o historico dos alugueres j� feitos.
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

// Verifica cada aluguer existente, se a sua data for maior que a do seguinte elemento, ir� ser feita uma troca
// para ordenar todos os elementos por ordem de compra.
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

// Escreve todos os dados sobre os alugueres, em ficheiro de texto.
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

 //Escreve todos os dados sobre os alugueres, em ficheiro bin�rio.
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

int existeClienteTransacao(Transacao* inicioTransacao, int codVerificar)
{
    int teste = 0;
    Transacao* aux = inicioTransacao;
    while (aux != NULL)
    {
        if (aux->codigoUtilizador == codVerificar)
            return 1;
        aux = aux->seguinteTransacao;
    }
    return 0;
}
#pragma endregion
// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTA��O DE ALUGUER----------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTA��O DE TRANSACOES----------------------------------------------------
#pragma region LEITURA/ESCRITA/REPRESENTA��O DE TRANSACOES
// Ler ficheiro de texto, contendo informa��o sobre transacoes efetuadas.
// Ser�o todos os dados, inseridos numa lista ligada, que de inicio � vazia.
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

// Escreve todos os dados sobre transacoes, em ficheiro de texto.
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

// Escreve todos os dados sobre os alugueres, em ficheiro binario.
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

// Listar transacoes existentes.
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

// Sendo executada, cria uma nova transacao
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
// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTA��O DE TRANSACOES----------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTA��O DE CIDADES----------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTA��O DE CIDADES
// Le do ficheiro e cria o grafo a partir dos valores lidos. Esta funcao e executada em primeiro lugar
// Para ser possivel para a funcao lerFicheirAdjacentes executar.
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
// Le do ficheiro e cria os adjacentes dos vertices existentes, a partir dos valores lidos.
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
// Funcao para fixar os clientes ao grafo.
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
// Funcao para fixar os meios ao grafo.
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
// Funcao para fixar os meios aos adjacentes.
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
// Dado um raio de distancia, e localizado o veiculo a partir do geocodigo do utilizador inserido.
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
        printf("Nao e possivel ir para nenhuma localizacao com a distancia definida.\n");
        return ERRO;
    }
    return SUCESSO;
}

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
// Lista o grafo.
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
// Lista os adjacentes.
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
            return 0;
        }
    }
}

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
            return inicioGrafo,1;
        }
        else
        {
            return 2;
        }
    }
    return 0;
}

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
            Stack* stackBateriaBaixa = NULL;
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
    if (/*todosVisitados(inicioStack, inicioGrafo) && */strcmp(verticeDestino, verticeAtual)==0)
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
            Stack* stackBateriaBaixa = NULL;
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

ListaStack* mostrarCaminhoCamiao(Grafo* inicioGrafo, char verticeAtual[], Stack* inicioStack, ListaStack* inicioLista, float Tamanho)
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
    ListaStack* camiaoCheioCaminho = NULL;
    static int camiao = 0;
    while (auxAdj != NULL)
    {
        if (!verticeVisitado(inicioStack, auxAdj->vertice))
        {
            Adjacente* auxAdjMeio = auxAdj;
            while (auxAdjMeio->meios != NULL)
            {
                if (auxAdjMeio->meios->bateria < 50 && auxAdjMeio->meios->recolhido==0)
                {
                    auxAdjMeio->meios->recolhido = 1;
                    camiao++;
                }
                auxAdjMeio->meios = auxAdjMeio->meios->seguinteMeio;
            }
            Stack* novaStack = NULL;
            Stack* auxStack2 = inicioStack;
            Stack* stackBateriaBaixa = NULL;
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
            if (camiao >= 2)
            {
                camiao = 0;
                camiaoCheioCaminho = novaStack;
                inicioLista = mostrarCaminhoCamiao(inicioGrafo, auxAdj->vertice, novaStack, inicioLista, Tamanho + auxAdj->peso);
            }
            inicioLista = mostrarCaminhoCamiao(inicioGrafo, auxAdj->vertice, novaStack, inicioLista, Tamanho + auxAdj->peso);
        }
        auxAdj = auxAdj->seguinteAdjacente;
    }
    return inicioLista;
}

ListaStack* mostrarCaminhoTeste(Grafo* inicioGrafo, char verticeAtual[], Stack* inicioStack, ListaStack* inicioLista, float Tamanho)
{
    ListaStack* caminhoAtual = NULL;
    ListaStack* caminhoArmazenado = NULL;
    Stack* camiaoStack = NULL;
    int camiao = 0;
    int camiaoCheio = 0;

    do {
        Grafo* aux = inicioGrafo;
        Stack* auxStack = inicioStack;
        Adjacente* auxAdj = NULL;

        // Find the starting vertex
        if (existeVertice(aux, verticeAtual))
        {
            while (aux != NULL)
            {
                if (strcmp(aux->vertice, verticeAtual) == 0)
                {
                    auxStack = inserirStack(auxStack, aux->vertice);
                    break;
                }
                aux = aux->seguinteVertice;
            }
        }
        else
        {
            return NULL;
        }

        // Traverse the graph
        while (auxStack != NULL)
        {
            Stack* topoStack = auxStack;
            auxStack = auxStack->seguinteStack;

            //if (!verticeVisitado(topoStack, topoStack->vertice))
            //{
                Adjacente* auxAdjMeio = aux->adjacentes;

                while (auxAdjMeio != NULL)
                {
                    if (!verticeVisitado(topoStack, auxAdjMeio->vertice))
                    {
                        Meio* auxMeio = auxAdjMeio->meios;
                        while (auxMeio != NULL)
                        {
                            if (auxMeio->bateria < 50 && auxMeio->recolhido == 0)
                            {
                                auxMeio->recolhido = 1;
                                camiao++;
                            }
                            auxMeio = auxMeio->seguinteMeio;
                        }

                        Stack* novaStack = NULL;
                        Stack* auxStack2 = topoStack;

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
                            novaStack->visitado = true;

                        if (camiao >= 2)
                        {
                            caminhoArmazenado = adicionarCaminho(camiaoStack, caminhoArmazenado, Tamanho + auxAdjMeio->peso);
                            camiaoStack = NULL;
                            camiaoCheio = 1;
                            break;
                        }
                        else
                        {
                            if (auxAdjMeio->seguinteAdjacente == NULL && caminhoAtual != NULL && camiaoCheio == 0)
                            {
                                caminhoArmazenado = adicionarCaminho(novaStack, caminhoArmazenado, Tamanho + auxAdjMeio->peso);
                                caminhoAtual = NULL;
                            }
                            else
                            {
                                camiaoStack = novaStack;
                                caminhoAtual = adicionarCaminho(novaStack, caminhoAtual, Tamanho + auxAdjMeio->peso);
                            }
                        }
                    }
                    auxAdjMeio = auxAdjMeio->seguinteAdjacente;
                }
            //}
            free(topoStack);
        }

        caminhoAtual = caminhoArmazenado;
        caminhoArmazenado = NULL;
        camiao = 0;
        camiaoCheio = 0;

    } while (caminhoAtual != NULL);

    return caminhoArmazenado;
}

ListaStack* adicionarCaminho(Stack* caminho, ListaStack* listaCaminhos, float tamanho)
{
    ListaStack* novoCaminho = malloc(sizeof(ListaStack));
    novoCaminho->novaStack = caminho;
    novoCaminho->tamanho = tamanho;
    novoCaminho->seguinteLista = listaCaminhos;
    return novoCaminho;
}

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

int tamanhoStack(Stack* inicioStack)
{
    Stack* aux = inicioStack;
    float tamanho = 0;
    while (aux != NULL)
    {
        tamanho++;
        aux = aux->seguinteStack;
    }
    return tamanho;
}

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
        auxLista = auxLista->seguinteLista;
    }
}
#pragma endregion

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTA��O DE CIDADES----------------------------------------------------
