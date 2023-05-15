#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
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
    printf("0- Sair.\n");
    printf("A sua escolha:");
    scanf("%d", &escolha);

    return escolha;
}

#pragma endregion

#pragma region MENU_UTILIZADOR

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
// Ler ficheiro de texto, contendo informação sobre os meios.
// Serão todos os dados, inseridos numa lista ligada, que de inicio é vazia.
Meio* lerFicheiroMeios(Meio* inicioMeios, FILE* dadosMeios)
{
    // Definição de variáveis.
    char linha[MAX_LINE_LEN];
    // Usando a função fgets, lemos a partir do ficheiro dadosMeios todo o seu conteúdo, onde é armazenado em cada novoNodo criado
    // Depois é atribuido ao inicio o valor de cada nodo criado, de seguida fechamos o ficheiro e por fim damos return da variavel inicio,
    // Contendo assim toda as informações e pointers necessários para criar a lista ligada.
    while (fgets(linha, MAX_LINE_LEN, dadosMeios))
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

// Apresenta na consola toda a informação existente sobre os clientes.
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

// Escreve todos os dados inseridos sobre os meios, em ficheiro binário.
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

// Verifica, consoante o endereço de memória de certo meio, se o seu código é igual ao que foi inserido para um novo meio.
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

// Verifica cada meio existente, se o seu valor de autonomia do elemento que está a verificar for maior que o elemento seguinte, irá ser feita uma troca
// para ordenar todos os elementos da lista ligada por um valor decrescente a nivel de autonomia.
Meio* bubbleSortMeios(Meio* inicioMeios)
{
    Meio* atual, * seguinte;
    int b = 1, aux_codigo, aux_custo, aux_ativo;
    float aux_bat, aux_aut;
    char aux_nome[50], aux_geo[50];

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
                aux_codigo = atual->codigo;
                aux_bat = atual->bateria;
                aux_aut = atual->autonomia;
                aux_custo = atual->custo;
                strcpy(aux_nome, atual->tipo);
                strcpy(aux_geo, atual->geocodigo);
                aux_ativo = atual->ativo;

                atual->codigo = seguinte->codigo;
                atual->bateria = seguinte->bateria;
                atual->autonomia = seguinte->autonomia;
                atual->custo = seguinte->custo;
                strcpy(atual->tipo, seguinte->tipo);
                strcpy(atual->geocodigo, seguinte->geocodigo);
                atual->ativo = seguinte->ativo;

                seguinte->codigo = aux_codigo;
                seguinte->bateria = aux_bat;
                seguinte->autonomia = aux_aut;
                seguinte->custo = aux_custo;
                strcpy(seguinte->tipo, aux_nome);
                strcpy(seguinte->geocodigo, aux_geo);
                seguinte->ativo = aux_ativo;

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
#pragma endregion 

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS--------------------------------------------------------


// --------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES--------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES

// Ler ficheiro de texto, contendo informação sobre os clientes.
// Serão todos os dados, inseridos numa lista ligada, que de inicio é vazia.
Cliente* lerFicheiroClientes(Cliente* inicioClientes, FILE* dadosClientes)
{
    // Definição de variáveis.
    char linha[MAX_LINE_LEN];

    //Usando a função fgets, lemos a partir do ficheiro dadosClientes todo o seu conteúdo, onde é armazenado em cada novoNodo criado
    //Depois é atribuido ao inicio o valor de cada nodo criado, de seguida fechamos o ficheiro e por fim damos return da variavel inicio,
    //Contendo assim toda as informações e pointers necessários para criar a lista ligada.

    while (fgets(linha, MAX_LINE_LEN, dadosClientes))
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

// Apresenta na consola toda a informação existente sobre os clientes.
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

// Escreve todos os dados inseridos sobre os clientes, em ficheiro binário.
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

// Verifica, consoante o endereço de memória de um certo utilizador, se o seu código é igual ao que foi inserido para um novo utilizador.
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

// Verifica, consoante o endereço de memória de um certo utilizador, se o seu NIF é igual ao que foi inserido para um novo utilizador.
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

// Verifica cada cliente existente, se o seu codigo do elemento que está a verificar for maior que o elemento seguinte, irá ser feita uma troca
// para ordenar todos os elementos da lista ligada por um valor crescente.
Cliente* bubbleSortClientes(Cliente* inicioClientes) {
    Cliente* atual, * seguinte;
    int b = 1, aux_codigo, aux_NIF, aux_saldo;
    char aux_nome[50], aux_geocodigo[100];
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
                aux_codigo = atual->codigo;
                strcpy(aux_nome, atual->nome);
                aux_NIF = atual->NIF;
                aux_saldo = atual->saldo;
                strcpy(aux_geocodigo, atual->geocodigo);

                atual->codigo = seguinte->codigo;
                strcpy(atual->nome, seguinte->nome);
                atual->NIF = seguinte->NIF;
                atual->saldo = seguinte->saldo;
                strcpy(atual->geocodigo, seguinte->geocodigo);

                seguinte->codigo = aux_codigo;
                strcpy(seguinte->nome, aux_nome);
                seguinte->NIF = aux_NIF;
                seguinte->saldo = aux_saldo;
                strcpy(seguinte->geocodigo, aux_geocodigo);

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

// Ler ficheiro de texto, contendo informação sobre os gestores.
// Serão todos os dados, inseridos numa lista ligada, que de inicio é vazia.
Gestor* lerFicheiroGestores(Gestor* inicioGestor, FILE* dadosGestor)
{
    char linha[MAX_LINE_LEN];
    while (fgets(linha, MAX_LINE_LEN, dadosGestor))
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

// Apresenta na consola toda a informação existente sobre os gestores.
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
Gestor* escreverFicheiroGestores(Gestor* inicio_gestores, FILE* dados_gestores)
{
    dados_gestores = fopen("gestores.txt", "wt");
    if (dados_gestores == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicio_gestores != NULL)
    {
        fprintf(dados_gestores, "%d;%s;%s;%d;%s\n", inicio_gestores->codigo, inicio_gestores->nome, inicio_gestores->senha, inicio_gestores->encriptado, inicio_gestores->areaResponsavel);
        inicio_gestores = inicio_gestores->seguinteGestor;
    }

    fclose(dados_gestores);
}

// Escreve todos os dados inseridos sobre os gestores, em ficheiro binário.
Gestor* escreverFicheiroGestoresBin(Gestor* inicio_gestores, FILE* dados_gestores)
{
    dados_gestores = fopen("gestores.bin", "wb");
    if (dados_gestores == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicio_gestores != NULL)
    {
        fprintf(dados_gestores, "%d;%s;%s;%d;%s\n", inicio_gestores->codigo, inicio_gestores->nome, inicio_gestores->senha, inicio_gestores->encriptado, inicio_gestores->areaResponsavel);
        inicio_gestores = inicio_gestores->seguinteGestor;
    }
    fclose(dados_gestores);
}

// Verifica, consoante o endereço de memória de um certo gestor, se o seu código é igual ao que foi inserido para um novo gestor.
int existeGestor(Gestor* inicio_gestores, int cod)
{
    while (inicio_gestores != NULL)
    {
        if (inicio_gestores->codigo == cod)
        {
            return 0;
        }
        inicio_gestores = inicio_gestores->seguinteGestor;
    }
    if (inicio_gestores == NULL)
        return 1;
}

// Verifica cada gestor existente, se o seu codigo do elemento que está a verificar for maior que o elemento seguinte, irá ser feita uma troca
// para ordenar todos os elementos da lista ligada por um valor crescente.
Gestor* bubbleSortGestores(Gestor* inicioGestor) {
    Gestor* atual, * seguinte;
    int aux_codigo, b = 1, aux_encriptado;
    char aux_senha[50], aux_nome[50], aux_areaResponsavel[50];
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
                aux_codigo = atual->codigo;
                strcpy(aux_nome, atual->nome);
                strcpy(aux_senha, atual->senha);
                aux_encriptado = atual->encriptado;
                strcpy(aux_areaResponsavel, atual->areaResponsavel);

                atual->codigo = seguinte->codigo;
                strcpy(atual->nome, seguinte->nome);
                strcpy(atual->senha, seguinte->senha);
                atual->encriptado = seguinte->encriptado;
                strcpy(atual->areaResponsavel, seguinte->areaResponsavel);

                seguinte->codigo = aux_codigo;
                strcpy(seguinte->nome, aux_nome);
                strcpy(seguinte->senha, aux_senha);
                seguinte->encriptado = aux_encriptado;
                strcpy(seguinte->areaResponsavel, aux_areaResponsavel);

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

// Função para entrar em modo gestor, no qual é pedido um codigo e uma senha. Caso sejam iguais ao que está no ficheiro é garantido o acesso
// a funções de gestor.
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
    senha[20 - 1] = '\0';
    while (inicio_gestores != NULL)
    {
        if (inicio_gestores->codigo == codigo_inserido && strcmp(inicio_gestores->senha, senha) == 0 && inicio_gestores->encriptado == 0)
        {
            printf("Bem-vindo %s\n", inicio_gestores->nome);
            return 1;
        }
        else if (inicio_gestores->codigo == codigo_inserido && inicio_gestores->encriptado == 1)
        {
            decryptSenha(inicio_gestores, inicio_gestores->senha);
            if (strcmp(senha, inicio_gestores->senha) == 0)
            {
                printf("Bem-vindo %s\n", inicio_gestores->nome);
                encryptSenha(inicio_gestores, inicio_gestores->senha);
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
            inicio_gestores = inicio_gestores->seguinteGestor;
        }
    }
    if (inicio_gestores == NULL)
    {
        printf("Codigo ou senha errados.\n");
        return 0;
    }
}

// Função para inserir um novo meio elétrico, é pedido ao gestor na função main, um novo codigo, nome, nivel bateria, autonomia, o seu custo 
// e a sua geolocalização. De seguida é inserido no ultimo lugar da lista ligada dos meios, quando é o ultimo endereço NULL.
Meio* inserirMeio(Grafo* inicioGrafo, Meio* inicioMeios, int cod, char nome[50], float bat, float aut, int custo, char geo[50])
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

// Função para inserir um novo cliente, é pedido ao gestor na função main, um novo codigo, nome, NIF e saldo.  
// De seguida é inserido no ultimo lugar da lista ligada dos clientes, quando é o ultimo endereço NULL.
Cliente* inserirCliente(Cliente* inicioClientes, int cod, char nome[50], int NIF, int saldo, char geocodigo[100])
{
    int inserir = 0;
    while (inserir != 1)
    {
        if (inicioClientes == NULL)
        {
            Cliente* novo_cliente = malloc(sizeof(Cliente));
            novo_cliente->codigo = cod;
            strcpy(novo_cliente->nome, nome);
            novo_cliente->NIF = NIF;
            novo_cliente->saldo = saldo;
            strcpy(novo_cliente->geocodigo, geocodigo);
            novo_cliente->seguinteCliente = NULL;
            inicioClientes = novo_cliente;
            printf("Cliente com codigo %d adicionado com sucesso.\n", novo_cliente->codigo);
            Sleep(2000);
            system("cls");
            return inicioClientes;
        }
        if (inicioClientes->seguinteCliente == NULL)
        {
            Cliente* novo_cliente = malloc(sizeof(Cliente));
            novo_cliente->codigo = cod;
            strcpy(novo_cliente->nome, nome);
            novo_cliente->NIF = NIF;
            novo_cliente->saldo = saldo;
            strcpy(novo_cliente->geocodigo, geocodigo);
            inicioClientes->seguinteCliente = novo_cliente;
            novo_cliente->seguinteCliente = NULL;
            inicioClientes = novo_cliente;
            printf("Cliente com codigo %d adicionado com sucesso.\n", novo_cliente->codigo);
            Sleep(2000);
            system("cls");
            return inicioClientes;
        }
        inicioClientes = inicioClientes->seguinteCliente;
    }
    return inicioClientes;
}

// Função para inserir um novo gestor, é pedido ao gestor na função main, um novo codigo, nome e senha.  
// De seguida é inserido no ultimo lugar da lista ligada dos gestores, quando é o ultimo endereço NULL.
Gestor* inserirGestor(Gestor* inicioGestor, int cod, char nome[50], char senha[50], char area[50])
{
    int inserir = 0, encriptado;
    while (inserir != 1)
    {
        if (inicioGestor == NULL)
        {
            Gestor* novo_gestor = malloc(sizeof(Gestor));
            novo_gestor->codigo = cod;
            strcpy(novo_gestor->nome, nome);
            strcpy(novo_gestor->senha, senha);
            printf("Deseja encriptar a sua senha?\n1-Sim/2-Nao\n");
            printf("A sua escolha:");
            scanf("%d", &encriptado);
            if (encriptado == 1)
            {
                novo_gestor->encriptado = 1;
                encryptSenha(novo_gestor, novo_gestor->senha);
            }
            else
            {
                novo_gestor->encriptado = 0;
            }
            strcpy(novo_gestor->areaResponsavel, area);
            novo_gestor->seguinteGestor = NULL;
            inicioGestor = novo_gestor;
            printf("Gestor com codigo %d inserido com sucesso.\n", novo_gestor->codigo);
            Sleep(2000);
            system("cls");
            return inicioGestor;
        }
        if (inicioGestor->seguinteGestor == NULL)
        {
            Gestor* novo_gestor = malloc(sizeof(Gestor));
            novo_gestor->codigo = cod;
            strcpy(novo_gestor->nome, nome);
            strcpy(novo_gestor->senha, senha);
            printf("Deseja encriptar a sua senha?\n1-Sim/2-Nao\n");
            printf("A sua escolha:");
            scanf("%d", &encriptado);
            if (encriptado == 1)
            {
                novo_gestor->encriptado = 1;
                encryptSenha(novo_gestor, novo_gestor->senha);
            }
            else
            {
                novo_gestor->encriptado = 0;
            }
            strcpy(novo_gestor->areaResponsavel, area);
            inicioGestor->seguinteGestor = novo_gestor;
            novo_gestor->seguinteGestor = NULL;
            inicioGestor = novo_gestor;
            inserir = 1;
            printf("Gestor com codigo %d inserido com sucesso.\n", novo_gestor->codigo);
            Sleep(2000);
            system("cls");
            return inicioGestor;
        }
        inicioGestor = inicioGestor->seguinteGestor;
    }
    return inicioGestor;
}

// Pequena função para encriptação da senha do gestor.
int encryptSenha(Gestor* inicioGestor, char senha[50])
{
    for (int i = 0; i < strlen(senha); i++)
    {
        senha[i] = senha[i] + 5;
    }
    return 1;
}

// Pequena função para desencriptação da senha do gestor.
int decryptSenha(Gestor* inicioGestor, char senha[50])
{
    for (int i = 0; i < strlen(senha); i++)
    {
        senha[i] = senha[i] - 5;
    }
    return 1;
}
#pragma endregion 

#pragma region REMOVER

// Função para remover algum meio, a partir do código inserido pelo gestor. É removido o meio e de seguida é retornada toda a lista ligada
// com o meio removido.
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

// Função para remover algum cliente, a partir do código inserido pelo gestor. É removido o cliente e de seguida é retornada toda a lista ligada
// com o meio removido.
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

// Função para remover algum gestor, a partir do código inserido pelo gestor. É removido o gestor e de seguida é retornada toda a lista ligada
// com o meio removido.
Gestor* removerGestor(Gestor* inicio_gestores, int cod)
{
    Gestor* anterior = inicio_gestores, * atual = inicio_gestores, * aux;

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
        if (atual == NULL) return(inicio_gestores); // Lista ligada toda percorrida, nao foi encontrado nenhum gestor com o codigo inserido.
        else // Remoção do gestor com cod introduzido.
        {
            anterior->seguinteGestor = atual->seguinteGestor;
            free(atual);
            printf("Gestor com cod %d removido com sucesso.\n", cod);
            return(inicio_gestores);
        }
    }
}
#pragma endregion

#pragma region ALTERAR

// Função para alteração de dados de algum gestor.
// Apenas é pedido o codigo de gestor. É possivel alterar codigo, nome, senha, area responsavel.
Gestor* alterarGestor(Gestor* inicio_gestores)
{
    int cod, escolha, novo_cod, encriptar, acabadoAlterar = 1;
    char nova_senha[50], novo_nome[50], senha[50], nova_areaResponsavel[50];
    Gestor* aux = inicio_gestores;
    if (inicio_gestores == NULL)
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
    while (inicio_gestores != NULL)
    {
        if (inicio_gestores->codigo == cod)
        {
            do
            {
                printf("Este sao os seus dados.\n");
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("Nome:%s     Codigo:%d       Area:%s\n", inicio_gestores->nome, inicio_gestores->codigo, inicio_gestores->areaResponsavel);
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
                    scanf("%d", &novo_cod);
                    if (!existeGestor(aux, novo_cod))
                    {
                        printf("Ja existe alguem com esse codigo.\n");
                        Sleep(2000);
                        system("cls");
                    }
                    else
                    {
                        inicio_gestores->codigo = novo_cod;
                        printf("Codigo alterado com sucesso. O seu novo codigo %d\n", inicio_gestores->codigo);
                        Sleep(2000);
                        system("cls");
                    }
                    break;
                case 2:
                    printf("Introduza um novo nome:");
                    scanf("%s", novo_nome);
                    strcpy(inicio_gestores->nome, novo_nome);
                    Sleep(2000);
                    system("cls");
                    break;
                case 3:
                    printf("Introduza a nova area para ser responsavel:");
                    scanf("%s", nova_areaResponsavel);
                    strcpy(inicio_gestores->areaResponsavel, nova_areaResponsavel);
                    printf("A sua area responsavel foi alterada com sucesso.\n");
                    printf("A sua nova area e a seguinte: %s\n", inicio_gestores->areaResponsavel);
                    Sleep(2000);
                    system("cls");
                    break;
                case 4:
                    printf("Introduza a sua nova senha:");
                    scanf("%s", nova_senha);
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
                        inicio_gestores->encriptado = 1;
                        encryptSenha(inicio_gestores, nova_senha);
                        strcpy(inicio_gestores->senha, nova_senha);
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
        inicio_gestores = inicio_gestores->seguinteGestor;
    }
}

// Função para alteração de dados do cliente.
// É pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes é possivel fazer alteração de nome, codigo e NIF.
ResFuncoes alterarDadosCliente(Cliente* inicioClientes, Transacao* inicioTransacao) {
    int codigo, NIF, novo_codigo, novo_NIF, inserir = 1, escolha, codigoAux;
    char novo_nome[50], novo_geocodigo[100];
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
                    scanf("%[^\n]", novo_nome);
                    strcpy(inicioClientes->nome, novo_nome);
                    printf("Nome alterado com sucesso para %s.\n", inicioClientes->nome);
                    Sleep(2000);
                    system("cls");
                    break;
                case 2:
                    printf("Insira o seu novo codigo:");
                    scanf("%d", &novo_codigo);
                    if (existeClienteCod(aux, novo_codigo))
                    {
                        codigoAux = inicioClientes->codigo;
                        inicioClientes->codigo = novo_codigo;
                        printf("O seu novo codigo %d\n", inicioClientes->codigo);
                        if (existeClienteTransacao(auxTrans, codigoAux))
                        {
                            while (auxTrans != NULL )
                            {
                                if (auxTrans->codigoUtilizador == codigoAux)
                                {
                                    auxTrans->codigoUtilizador = novo_codigo;
                                }
                                auxTrans = auxTrans->seguinteTransacao;
                            }
                        }
                        Sleep(2000);
                        system("cls");
                    }
                    else
                    {
                        printf("O codigo %d ja existe.\n", novo_codigo);
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    break;
                case 3:
                    printf("Insira o seu novo NIF(deve conter 9 numeros e comecar por 192):");
                    scanf("%d", &novo_NIF);
                    if (novo_NIF <= 192000000 || novo_NIF >= 193000000)
                    {
                        printf("Por favor tente de novo.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    else
                    {
                        if (existeClienteNIF(aux, novo_NIF))
                        {
                            inicioClientes->NIF = novo_NIF;
                            printf("O seu novo NIF %d\n", inicioClientes->NIF);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        else
                        {
                            printf("Ja existe alguem com o NIF inserido %d.\n", novo_NIF);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                    }
                    break;
                case 4:
                    printf("Insira o seu novo geocodigo/localizacao:");
                    scanf("%s", novo_geocodigo);
                    strcpy(inicioClientes->geocodigo, novo_geocodigo);
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

// Função para alteração de dados de algum meio.
// É pedido o codigo do meio a alterar. É possivel alterar o seu codigo, tipo, se está ativo, custo, bat, aut, etc...
Meio* alterarMeio(Meio* inicioMeios)
{
    int cod, cod_alterar, ativo_alterar, custo_alterar, escolha;
    float bat_alterar, aut_alterar;
    char meio_nome_alterar[50], geocodigo_alterar[50];
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
                    scanf("%d", &cod_alterar);
                    if (!existeMeio(aux, cod_alterar))
                    {
                        printf("Ja existe um meio com esse codigo.\n");
                        Sleep(2000);
                        system("cls");
                    }
                    else
                    {
                        inicioMeios->codigo = cod_alterar;
                        printf("Codigo alterado com sucesso. Novo codigo %d.\n", inicioMeios->codigo);
                        Sleep(2000);
                        system("cls");
                    }
                    break;
                case 2:
                    printf("Insira o novo tipo de meio:");
                    scanf("%s", meio_nome_alterar);
                    strcpy(inicioMeios->tipo, meio_nome_alterar);
                    printf("Nome alterado com sucesso para %s.\n", inicioMeios->tipo);
                    Sleep(2000);
                    system("cls");
                    break;
                case 3:
                    printf("Insira o novo nivel de bateria:");
                    scanf("%f", &bat_alterar);
                    if (bat_alterar > 100.0001 || bat_alterar < 0)
                    {
                        printf("Insira um nivel de bateria, entre 0 e 100.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    inicioMeios->bateria = bat_alterar;
                    printf("Novo nivel de bateria %.2f\n", inicioMeios->bateria);
                    Sleep(2000);
                    system("cls");
                    break;
                case 4:
                    printf("Insira o novo nivel de autonomia:");
                    scanf("%f", &aut_alterar);
                    if (aut_alterar > 100.0001 || aut_alterar < 0)
                    {
                        printf("Insira um nivel de autonomia, entre 0 e 100.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    inicioMeios->autonomia = aut_alterar;
                    printf("Novo nivel de autonomia %.2f\n", inicioMeios->autonomia);
                    Sleep(2000);
                    system("cls");
                    break;
                case 5:
                    printf("Insira o novo custo:");
                    scanf("%d", &custo_alterar);
                    inicioMeios->custo = custo_alterar;
                    printf("Novo custo do meio %d\n", inicioMeios->custo);
                    Sleep(2000);
                    system("cls");
                    break;
                case 6:
                    printf("Insira um novo geocodigo:");
                    scanf("%s", geocodigo_alterar);
                    strcpy(inicioMeios->geocodigo, geocodigo_alterar);
                    printf("Novo geocodigo %s\n", inicioMeios->geocodigo);
                    Sleep(2000);
                    system("cls");
                    break;
                case 7:
                    printf("Este veiculo esta ativo?1-Sim/0-Nao\n");
                    printf("A sua escolha:");
                    scanf("%d", &ativo_alterar);
                    if (ativo_alterar == 1)
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
#pragma region OP_Utilizador
// Função para carregamento de saldo, de um certo utilizador.
// É pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes é possivel carregar o saldo desse mesmo utilizador.
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
            int saldo_carregar;
            printf("O seu saldo: %d\n", inicioClientes->saldo);
            printf("Quanto saldo deseja carregar?\n");
            printf("Digite:");
            scanf("%d", &saldo_carregar);
            if (saldo_carregar < 0)
            {
                return saldoCarrNegativo;
            }
            inicioClientes->saldo = saldo_carregar + inicioClientes->saldo;
            printf("%d carregado com sucesso. Tem agora %d de saldo.\n", saldo_carregar, inicioClientes->saldo);
            if (inicioTransacao == NULL)
            {
                if (inicioTransacao = criarTransacao(inicioTransacao, inicioClientes->codigo, saldo_carregar, inicioClientes->nome))
                    return inicioTransacao;
            }
            while (inserir == 1)
            {
                if (inicioTransacao->seguinteTransacao == NULL)
                {
                    if (criarTransacao(auxTrans, inicioClientes->codigo, saldo_carregar, inicioClientes->nome))
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

// Função para consulta de saldo, de um certo utilizador.
// É pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes é possivel visualizar quando saldo está disponível.
ResFuncoes consultaSaldo(Cliente* inicioClientes, int *saldoVerifica) {
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

// Funçáo para realização de aluguer de qualquer meio existente, que não esteja ativo.
// É pedido o codigo de utilizador, é verificado se existe esse mesmo utilizador. De seguida é perguntado qual o meio que deseja alugar. 
// São apresentados dados, tais como o tipo de meio, o seu custo e o saldo do utilizador. Caso o utilizador, decida comprar o meio
// É criado um novo registo na lista ligada de alugueres.
Aluguer* realizarAluguer(Cliente* inicioClientes, Aluguer* inicioAluguer, Meio* inicioMeios)
{
    int meio_Alugar, codigoUtilizador, NIF;
    printf("Insira o seu codigo:");
    scanf("%d", &codigoUtilizador);
    if (existeClienteCod(inicioClientes, codigoUtilizador) == 0)
    {
        while (inicioClientes->codigo != codigoUtilizador)
            inicioClientes = inicioClientes->seguinteCliente;
        printf("Qual meio deseja alugar?\n");
        scanf("%d", &meio_Alugar);
        if (existeMeio(inicioMeios, meio_Alugar) == 0)
        {
            while (inicioMeios->codigo != meio_Alugar)
            {
                inicioMeios = inicioMeios->seguinteMeio;
            }
            printf("Nome do meio %s\n", inicioMeios->tipo);
            printf("O meio custa:%d\n", inicioMeios->custo);
            printf("Voce tem:%d\n", inicioClientes->saldo);
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
                    char aux_dataCompra[50];
                    strcpy(aux_dataCompra, ctime(&dataCompra));
                    for (int i = 0; i < strlen(aux_dataCompra); i++)
                    {
                        if (aux_dataCompra[i] == '\n')
                            aux_dataCompra[i] = '\0';
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
                            strcpy(novoNodo->dataCompra, aux_dataCompra);
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

// Função para listar na consola, todos os meios existentes com um certo geocodigo.
void listarGeocodigo(Meio* inicioMeios)
{
    system("cls");
    int verificado = 0, existe = 0;
    char verificar_geocodigo[50];
    Meio* aux_print = inicioMeios;
    printf("Introduza o geocodigo que pretende verificar:");
    scanf("%s", verificar_geocodigo);
    getchar();

    if (inicioMeios == NULL)
        return 0;
    while (aux_print != NULL && existe == 0)
    {
        if (strcmp(verificar_geocodigo, aux_print->geocodigo) == 0)
        {
            existe = 1;
        }
        aux_print = aux_print->seguinteMeio;
    }
    if (existe)
    {
        printf("Estes sao os meios com o geocodigo %s\n------------------------------------------------------------------------------------------------------------------------\n", verificar_geocodigo);
    }
    else
    {
        printf("Nao existe o geocodigo inserido.\n");
        Sleep(2000);
        system("cls");
    }
    while (inicioMeios != NULL)
    {
        if (strcmp(verificar_geocodigo, inicioMeios->geocodigo) == 0)
        {
            printf("Codigo:%d      Tipo:%s      Bat:%.2f      Aut:%.2f      Custo:%d\n", inicioMeios->codigo, inicioMeios->tipo, inicioMeios->bateria, inicioMeios->autonomia, inicioMeios->custo);
        }
        inicioMeios = inicioMeios->seguinteMeio;
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}
#pragma endregion
// -----------------------------------------------------------------FIM_OP_UTILIZADOR-------------------------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE ALUGUER----------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAÇÃO DE ALUGUER
// Ler ficheiro de texto, contendo informação sobre os alugueres.
// Serão todos os dados, inseridos numa lista ligada, que de inicio é vazia.
Aluguer* lerFicheiroAluguer(Aluguer* inicioAluguer, FILE* dadosAluguer)
{
    char linha[MAX_LINE_LEN];
    while (fgets(linha, MAX_LINE_LEN, dadosAluguer))
    {
        Aluguer* novoNodo = malloc(sizeof(Aluguer));
        sscanf(linha,"%d;%[^;];%[^;];%[^\n]\n", &novoNodo->codComprador, novoNodo->dataCompra, novoNodo->nomeComprador, novoNodo->nomeMeioComprado);
        novoNodo->seguinteCompra = inicioAluguer;
        inicioAluguer = novoNodo;
    }
    fclose(dadosAluguer);
    return inicioAluguer;
}

// Função para listar na consola, o historico dos alugueres já feitos.
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

// Verifica cada aluguer existente, se a sua data for maior que a do seguinte elemento, irá ser feita uma troca
// para ordenar todos os elementos por ordem de compra.
Aluguer* bubbleSortAluguer(Aluguer* inicioAluguer) {
    Aluguer* atual, * seguinte;
    int aux_codigo, b = 1;
    char aux_data[50], aux_comprador[50], aux_meio_comprado[50];
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
                aux_codigo = atual->codComprador;
                strcpy(aux_comprador, atual->nomeComprador);
                strcpy(aux_data, atual->dataCompra);
                strcpy(aux_meio_comprado, atual->nomeMeioComprado);

                atual->codComprador = seguinte->codComprador;
                strcpy(atual->nomeComprador, seguinte->nomeComprador);
                strcpy(atual->dataCompra, seguinte->dataCompra);
                strcpy(atual->nomeMeioComprado, seguinte->nomeMeioComprado);

                seguinte->codComprador = aux_codigo;
                strcpy(seguinte->nomeComprador, aux_comprador);
                strcpy(seguinte->dataCompra, aux_data);
                strcpy(seguinte->nomeMeioComprado, aux_meio_comprado);
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
    dadosAluguer = fopen("historico_compras.txt", "wt");
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

 //Escreve todos os dados sobre os alugueres, em ficheiro binário.
Aluguer* escreverFicheiroAluguerBin(Aluguer* inicioAluguer, FILE* dadosAluguer)
{
    if (inicioAluguer == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return 0;
    }
    dadosAluguer = fopen("historico_compras.bin", "wb");
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
// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE ALUGUER----------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE TRANSACOES----------------------------------------------------
#pragma region LEITURA/ESCRITA/REPRESENTAÇÃO DE TRANSACOES
Transacao* lerFicheiroTransacao(Transacao* inicioTransacao, FILE* dadosTransacao)
{
    char linha[MAX_LINE_LEN];
    while (fgets(linha, MAX_LINE_LEN, dadosTransacao))
    {
        Transacao* novoNodo = malloc(sizeof(Transacao));
        sscanf(linha, "%d;%[^;];%d;%[^\n]", &novoNodo->codigoUtilizador, novoNodo->nomeTransacao, &novoNodo->montanteCarregado, novoNodo->dataTransacao);
        novoNodo->seguinteTransacao = inicioTransacao;
        inicioTransacao = novoNodo;
    }
    fclose(dadosTransacao);
    return inicioTransacao;
}

Transacao* escreverFicheiroTransacao(Transacao* inicioTransacao, FILE* dadosTransacao)
{
    if (inicioTransacao == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return 0;
    }
    dadosTransacao = fopen("historico_transacoes.txt", "wt");
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

Transacao* escreverFicheiroTransacaoBin(Transacao* inicioTransacao, FILE* dadosTransacao)
{
    if (inicioTransacao == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return 0;
    }
    dadosTransacao = fopen("historico_transacoes.bin", "wb");
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

Transacao* criarTransacao(Transacao* inicioTransacao, int codigoCliente, int saldoCarregar, char nomeCliente[50])
{
    Transacao* nova_transacao = malloc(sizeof(Transacao));
    nova_transacao->codigoUtilizador = codigoCliente;
    nova_transacao->montanteCarregado = saldoCarregar;
    strcpy(nova_transacao->nomeTransacao, nomeCliente);
    time_t dataTransacao;
    time(&dataTransacao);
    char aux_dataTransacao[50];
    strcpy(aux_dataTransacao, ctime(&dataTransacao));
    for (int i = 0; i < strlen(aux_dataTransacao); i++)
    {
        if (aux_dataTransacao[i] == '\n')
            aux_dataTransacao[i] = '\0';
    }
    strcpy(nova_transacao->dataTransacao, aux_dataTransacao);

    if (inicioTransacao == NULL) {
        inicioTransacao = nova_transacao;
    }
    else {
        Transacao* current_transacao = inicioTransacao;
        while (current_transacao->seguinteTransacao != NULL) {
            current_transacao = current_transacao->seguinteTransacao;
        }
        current_transacao->seguinteTransacao = nova_transacao;
    }
        nova_transacao->seguinteTransacao = NULL;
        inicioTransacao = nova_transacao;
    return inicioTransacao;
}
#pragma endregion
// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE TRANSACOES----------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE CIDADES----------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAÇÃO DE CIDADES
Grafo* lerFicheiroVertices(Grafo* inicioGrafo,Meio* inicioMeios, FILE* dados_grafo)
{
    char* token_vertice;
    if (dados_grafo == NULL)
    { 
        printf("O ficheiro nao existe.\n"); 
        return 0;
    }
    char linha[MAX_LINE_LEN];
    while (fgets(linha, MAX_LINE_LEN, dados_grafo))
    {
            token_vertice = strtok(linha, ";");
            while (token_vertice != NULL)
            {
                int pos = strcspn(token_vertice, "\n");
                token_vertice[pos] = '\0';
                Grafo* novoNodo = malloc(sizeof(Grafo));
                strcpy(novoNodo->vertice, token_vertice);
                novoNodo->meios = NULL;
                novoNodo->adjacentes = NULL;
                novoNodo->seguinteVertice = inicioGrafo;
                inicioGrafo = novoNodo;
                token_vertice = strtok(NULL, ";");
            }
    }
    return inicioGrafo;
}

Grafo* lerFicheiroAdjacentes(Grafo* inicioGrafo, FILE* dados_adjacentes)
{
    Adjacente* novo_adj = NULL;
    Grafo* aux = inicioGrafo;
    int inserido = 0;
    char* vertice, * adjacente, * peso, linha[MAX_LINE_LEN];
    while (fgets(linha, MAX_LINE_LEN, dados_adjacentes))
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
                        if (novo_adj == NULL)
                        {
                            novo_adj = malloc(sizeof(Adjacente));
                            adjacente = strtok(NULL, "/");
                            peso = strtok(NULL, ";");
                            strcpy(novo_adj->vertice, adjacente);
                            novo_adj->peso = atof(peso);
                            novo_adj->seguinteAdjacente = aux->adjacentes;
                            aux->adjacentes = novo_adj;
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
                                novo_adj = malloc(sizeof(Adjacente));
                                strcpy(novo_adj->vertice, adjacente);
                                novo_adj->peso = atof(peso);
                                if (aux->adjacentes == NULL) 
                                {
                                    aux->adjacentes = novo_adj;
                                    novo_adj->seguinteAdjacente = NULL;
                                }
                                else 
                                {
                                    novo_adj->seguinteAdjacente = aux->adjacentes->seguinteAdjacente;
                                    aux->adjacentes->seguinteAdjacente = novo_adj;
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

void teste(Grafo* inicioGrafo)
{
    //Teste clientes;
   /* Grafo* aux = inicioGrafo;
    while (aux != NULL)
    {
        if (aux->clientes == NULL)
        {
            printf("Nao existe clientes registados com a cidade: %s\n", aux->vertice);
        }
        else if (aux->clientes != NULL)
        {
            printf("Nome: %s    Cod: %d\n", aux->clientes->nome, aux->clientes->codigo);
        }
        aux = aux->seguinteVertice;
    }*/

    //Teste Meios;
    Grafo* aux = inicioGrafo;
    while (aux != NULL)
    {
        Adjacente* auxAdj = aux->adjacentes;
        while (auxAdj != NULL)
        {
            while (auxAdj->meios != NULL)
            {
                printf("Adjacente: %s com o meio %s, bateria %.2f\n", auxAdj->vertice, auxAdj->meios->tipo, auxAdj->meios->bateria);
                auxAdj->meios = auxAdj->meios->seguinteMeio;
            }
            auxAdj = auxAdj->seguinteAdjacente;
        }
        aux = aux->seguinteVertice;
    }
}


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

Grafo* adicionarMeiosGrafo(Grafo* inicioGrafo, Meio* inicioMeios)
{
    Grafo* aux = inicioGrafo;
    while (aux != NULL)
    {
        Meio* auxMeio = inicioMeios;
        Meio* meios = NULL;
        Meio* ultimo_meio = NULL;
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
                    ultimo_meio = novoMeio;
                }
                else
                {
                    ultimo_meio->seguinteMeio = novoMeio;
                    ultimo_meio = novoMeio;
                }
            }
            auxMeio = auxMeio->seguinteMeio;
        }
        aux->meios = meios;
        aux = aux->seguinteVertice;
    }
    return inicioGrafo->meios;
}

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
            Meio* ultimo_meio = NULL;
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
                        ultimo_meio = novoMeio;
                    }
                    else
                    {
                        ultimo_meio->seguinteMeio = novoMeio;
                        ultimo_meio = novoMeio;
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

ResFuncoes localizacaoRaio(Grafo* inicioGrafo, Cliente* inicioClientes, float raio, int codigo, char tipoMeio[20])
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
    while (aux->clientes != NULL)
    {
        printf("Cliente: %s \n", aux->clientes->nome);
        aux->clientes = aux->clientes->seguinteCliente;
    }
    while (aux->meios != NULL)
    {
        printf("Meios: %s \n", aux->meios->tipo);
        aux->meios = aux->meios->seguinteMeio;
    }
}

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
    printf("Prima espaco e enter para sair.");
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

int existeVertice(Grafo* inicioGrafo, char verticeVerificar[50])
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

int inserirVertice(Grafo* inicioGrafo, char verticeInserir[50])
{
    while (inicioGrafo != NULL)
    {
        if (inicioGrafo->seguinteVertice == NULL)
        {
            Grafo* novo_vertice = malloc(sizeof(Grafo));
            strcpy(novo_vertice->vertice, verticeInserir);
            novo_vertice->adjacentes = NULL;
            novo_vertice->meios = NULL;
            inicioGrafo->seguinteVertice = novo_vertice;
            novo_vertice->seguinteVertice = NULL;
            inicioGrafo = novo_vertice;
        }
        inicioGrafo = inicioGrafo->seguinteVertice;
    }
    return inicioGrafo, 1;
}

void escreverFicheiroGrafo(Grafo* inicioGrafo, FILE* dados_grafo)
{
    Grafo* aux = inicioGrafo;
    if (inicioGrafo == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return;
    }
    dados_grafo = fopen("vertices.txt", "wt");
    if (dados_grafo == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
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
        fprintf(dados_grafo, "%s;", listaCopiada[iterador-1]);
        iterador--;
    }
    fclose(dados_grafo);
}

int existeAdjacente(Grafo* inicioGrafo, char verticeFinal[50])
{
    Grafo* aux = inicioGrafo;
    while (aux != NULL)
    {
        if (strcmp(aux->adjacentes->vertice, verticeFinal) == 0)
        {
            return 1;
        }
        aux = aux->seguinteVertice;
    }
    return 0;
}

int inserirAdjacente(Grafo* inicioGrafo, char verticeInicial[50], char verticeFinal[50], float peso)
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
            Adjacente* novo_adj = malloc(sizeof(Adjacente));
            strcpy(novo_adj->vertice, verticeFinal);
            novo_adj->peso = peso;
            novo_adj->seguinteAdjacente = aux->adjacentes;
            aux->adjacentes = novo_adj;
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

ListaStack* caminhoTexto(Grafo* inicioGrafo, char verticeAtual[50], char verticeDestino[50], Stack* inicioStack, ListaStack* inicioLista)
{
    Grafo* aux = inicioGrafo;
    Stack* aux_stack = inicioStack;
    Adjacente* aux_adj = NULL;
    float tamanho = 0;
    if (existeVertice(aux, verticeAtual))
    {
        while (aux != NULL)
        {
            if (strcmp(aux->vertice, verticeAtual) == 0)
            {
                aux_stack = push(aux_stack, aux->vertice);
                inicioStack = aux_stack;
                break;
            }
            aux = aux->seguinteVertice;
        }
    }
    if (strcmp(aux->vertice, verticeDestino) == 0)
    {
        ListaStack* novaListaStack = malloc(sizeof(ListaStack));
        novaListaStack->novaStack = inicioStack;
        novaListaStack->tamanho = tamanhoStack(inicioStack);
        novaListaStack->seguinteLista = inicioLista;
        inicioLista = novaListaStack;
        return inicioLista;
    }

    aux_adj = aux->adjacentes;
    while (aux_adj != NULL)
    {
        if (!verticeVisitado(inicioStack, aux_adj->vertice))
        {
            Stack* novo_stack = NULL;
            Stack* aux_stack2 = inicioStack;
            while (aux_stack2 != NULL)
            {
                novo_stack = push(novo_stack, aux_stack2->vertice);
                novo_stack->dist = aux_adj->peso;
                aux_stack2 = aux_stack2->seguinteStack;
            }
            tamanho = tamanho + novo_stack->dist;
            inicioStack->visitado = true;
            inicioLista = caminhoTexto(inicioGrafo, aux_adj->vertice, verticeDestino, novo_stack, inicioLista);
        }
        aux_adj = aux_adj->seguinteAdjacente;
    }
    return inicioLista;
}

int tamanhoStack(Stack* inicioStack)
{
    Stack* aux = inicioStack;
    int tamanho = 0;
    while (aux!= NULL)
    {
        tamanho++;
        aux= aux->seguinteStack;
    }
    return tamanho;
}

ListaStack* retirarStackMaior(ListaStack* inicioLista)
{

    ListaStack* aux = inicioLista, *anterior = NULL;
    int menorcaminho = aux->tamanho;
    while (aux != NULL)
    {
        int auxCaminho;
        auxCaminho = aux->tamanho;
        if (auxCaminho < menorcaminho)
            menorcaminho = aux->tamanho;
        aux = aux->seguinteLista;

    }
    aux = inicioLista;
    while (aux!=NULL)
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
            ListaStack* aux_remover = aux;
            aux = aux->seguinteLista;
            free(aux_remover);
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

ListaStack* retirarStackMaiorVolta(ListaStack* inicioLista, char verticeDestino[50], char verticeInicial[50])
{

    ListaStack* aux = inicioLista, * anterior = NULL;
    int menorcaminho = aux->tamanho;
    while (aux != NULL)
    {
        int auxCaminho;
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
            ListaStack* aux_remover = aux;
            aux = aux->seguinteLista;
            free(aux_remover);
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

bool verticeVisitado(Stack* inicioStack, char* vertice)
{
    Stack* aux_stack = inicioStack;
    while (aux_stack != NULL)
    {
        if (strcmp(aux_stack->vertice, vertice) == 0)
        {
            return true;
        }
        aux_stack = aux_stack->seguinteStack;
    }
    return false;
}
#pragma endregion

#pragma region STACK

Stack* push(Stack* inicioStack, char vertice[50])
{
    Stack* aux = inicioStack;
    if (inicioStack == NULL)
    {
        Stack* novo_stack = malloc(sizeof(Stack));
        strcpy(novo_stack->vertice, vertice);
        novo_stack->visitado = true;
        novo_stack->seguinteStack = inicioStack;
        return novo_stack;
    }
    else
    {
        while (inicioStack->seguinteStack != NULL)
        {
            inicioStack = inicioStack->seguinteStack;
        }
        Stack* novo_stack = malloc(sizeof(Stack));
        strcpy(novo_stack->vertice, vertice);
        novo_stack->seguinteStack = NULL;
        inicioStack->seguinteStack = novo_stack;
    }
    return aux;  
}



void mostrarCaminho(ListaStack* inicioLista) {
    if (inicioLista == NULL)
    {
        printf("Caminho nao encontrado.\n");
        return;
    }
    ListaStack* aux_lista = inicioLista;
    while (aux_lista != NULL)
    {
        Stack* aux_stack = aux_lista->novaStack;
        while (aux_stack != NULL)
        {
            printf("%s", aux_stack->vertice);
            if (aux_stack->seguinteStack != NULL)
            {
                printf(" -> ");
            }
            aux_stack = aux_stack->seguinteStack;
        }
        printf("\ntamanho:%d\n", aux_lista->tamanho);
        aux_lista = aux_lista->seguinteLista;
    }
}
#pragma endregion

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE CIDADES----------------------------------------------------
