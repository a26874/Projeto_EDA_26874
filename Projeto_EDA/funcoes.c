#define _CRT_SECURE_NO_WARNINGS
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
int menu_utilizador()
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
Meio* lerFicheiro_meios(Meio* inicio_meios, FILE* dados_meios)
{
    // Definição de variáveis.
    char linha[MAX_LINE_LEN];
    // Usando a função fgets, lemos a partir do ficheiro dados_meios todo o seu conteúdo, onde é armazenado em cada novo_nodo criado
    // Depois é atribuido ao inicio o valor de cada nodo criado, de seguida fechamos o ficheiro e por fim damos return da variavel inicio,
    // Contendo assim toda as informações e pointers necessários para criar a lista ligada.
    while (fgets(linha, MAX_LINE_LEN, dados_meios))
    {
        // Enquanto é possivel obter texto do ficheiro dados_meios, irá ser criado um novo espaço na memória para a struct meios
        // A cada iteração é atribuido todo o conteudo obtido ao inicio_meios, criando assim uma lista ligada.
        Meio* novo_nodo = malloc(sizeof(Meio));
        sscanf(linha, "%d;%[^;];%f;%f;%d;%[^;];%d\n", &novo_nodo->codigo, novo_nodo->tipo, &novo_nodo->bateria, &novo_nodo->autonomia, &novo_nodo->custo, novo_nodo->geocodigo, &novo_nodo->ativo);
        // O seguinte valor de memória é igual a inicio_meios que foi inicializado a NULL, para de seguida ser possivel atribuir outro elemento da lista ligada.
        novo_nodo->seguinte_meio = inicio_meios;
        // Inicio_meios vai obter toda a informação que foi lida por novo_nodo
        inicio_meios = novo_nodo;
    }
    fclose(dados_meios);
    return inicio_meios;
}

// Apresenta na consola toda a informação existente sobre os clientes.
ResFuncoes listarMeios(Meio* inicio_meios)
{
    system("cls");
    if (inicio_meios == NULL)
    {
        return MEIOS_NAO_EXISTEM;
    }
    else
    {
        // Enquanto o pointer inicio_meios não for NULL (que esse mesmo está sempre a apontar para um valor de memória diferente na lista ligada)
        // É apresentada a informação dos meios.
        printf("Dados de meios disponiveis:\n------------------------------------------------------------------------------------------------------------------------\n\n");
        while (inicio_meios != NULL)
        {
            printf("Codigo:%d    Tipo:%s  Nivel Bateria:%.2f  Autonomia:%.2f  Custo:%d Geocodigo:%s Ativo:%d\n", inicio_meios->codigo, inicio_meios->tipo,
                inicio_meios->bateria, inicio_meios->autonomia, inicio_meios->custo, inicio_meios->geocodigo, inicio_meios->ativo);
            inicio_meios = inicio_meios->seguinte_meio;
        }
        printf("------------------------------------------------------------------------------------------------------------------------\n\n");
    }
    return SUCESSO;
}

// Escreve todos os dados inseridos sobre os meios, em ficheiro de texto.
Meio* escreverFicheiro_meios(Meio* inicio_meios, FILE* dados_meios)
{
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

// Escreve todos os dados inseridos sobre os meios, em ficheiro binário.
Meio* escreverFicheiro_meios_bin(Meio* inicio_meios, FILE* dados_meios)
{
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

// Verifica, consoante o endereço de memória de certo meio, se o seu código é igual ao que foi inserido para um novo meio.
Meio* existeMeio(Meio* inicio_meios, int cod)
{
    if (inicio_meios == NULL)
        return 1;
    while (inicio_meios != NULL)
    {
        if (inicio_meios->codigo == cod)
        {
            return 0;
        }
        inicio_meios = inicio_meios->seguinte_meio;
    }
    return 1;
}

// Verifica cada meio existente, se o seu valor de autonomia do elemento que está a verificar for maior que o elemento seguinte, irá ser feita uma troca
// para ordenar todos os elementos da lista ligada por um valor decrescente a nivel de autonomia.
Meio* bubbleSortMeios(Meio* inicio_meios)
{
    Meio* atual, * seguinte;
    int b = 1, aux_codigo, aux_custo, aux_ativo;
    float aux_bat, aux_aut;
    char aux_nome[50], aux_geo[50];

    while (b)
    {
        b = 0;
        atual = inicio_meios;
        if (atual == NULL)
        {
            return 0;
        }
        while (atual->seguinte_meio != NULL)
        {
            seguinte = atual->seguinte_meio;
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
    inicio_meios = atual;
    return inicio_meios;
}

float mediaAutonomia(Meio* inicio_meios)
{
    int tamanho = 0;
    float resultado = 0;
    if (inicio_meios == NULL)
    {
        printf("Lista ligada vazia.\n");
        Sleep(2000);
        system("cls");
        return 0;
    }
    while (inicio_meios != NULL)
    {
        resultado += inicio_meios->autonomia;
        inicio_meios = inicio_meios->seguinte_meio;
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
        sscanf(linha, "%d;%[^;];%d;%d;%s\n", &novo_nodo->codigo, novo_nodo->nome, &novo_nodo->NIF, &novo_nodo->saldo, novo_nodo->geocodigo);
        novo_nodo->seguinte_cliente = inicio_clientes;
        inicio_clientes = novo_nodo;
    }
    fclose(dados_clientes);
    return inicio_clientes;
}

// Apresenta na consola toda a informação existente sobre os clientes.
void listarClientes(Cliente* inicio_clientes)
{
    system("cls");
    if (inicio_clientes == NULL)
    {
        printf("Nao existem clientes.\n");
        return 0;
    }
    else
    {
        printf("Dados de Clientes:\n------------------------------------------------------------------------------------------------------------------------\n");
        // Enquanto o pointer inicio_clientes não for NULL (que esse mesmo está sempre a apontar para um valor de memória diferente na lista ligada)
        // É apresentada a informação dos clientes.
        while (inicio_clientes != NULL)
        {
            printf("Codigo:%d    Nome:%s     NIF:%d      Saldo:%d   Geocodigo:%s\n", inicio_clientes->codigo, inicio_clientes->nome, inicio_clientes->NIF, inicio_clientes->saldo, inicio_clientes->geocodigo);
            inicio_clientes = inicio_clientes->seguinte_cliente;
        }
        printf("------------------------------------------------------------------------------------------------------------------------");
    }
}

// Escreve todos os dados inseridos sobre os clientes, em ficheiro de texto.
Cliente* escreverFicheiro_clientes(Cliente* inicio_clientes, FILE* dados_clientes)
{
    dados_clientes = fopen("clientes.txt", "wt");
    if (dados_clientes == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicio_clientes != NULL)
    {
        fprintf(dados_clientes, "%d;%s;%d;%d;%s\n", inicio_clientes->codigo, inicio_clientes->nome, inicio_clientes->NIF, inicio_clientes->saldo, inicio_clientes->geocodigo);
        inicio_clientes = inicio_clientes->seguinte_cliente;
    }
    fclose(dados_clientes);
}

// Escreve todos os dados inseridos sobre os clientes, em ficheiro binário.
Cliente* escreverFicheiro_clientes_bin(Cliente* inicio_clientes, FILE* dados_clientes)
{
    dados_clientes = fopen("clientes.bin", "wb");
    if (dados_clientes == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicio_clientes != NULL)
    {
        fprintf(dados_clientes, "%d;%s;%d;%d;%s\n", inicio_clientes->codigo, inicio_clientes->nome, inicio_clientes->NIF, inicio_clientes->saldo, inicio_clientes->geocodigo);
        inicio_clientes = inicio_clientes->seguinte_cliente;
    }
    fclose(dados_clientes);
}

// Verifica, consoante o endereço de memória de um certo utilizador, se o seu código é igual ao que foi inserido para um novo utilizador.
int existeClienteCod(Cliente* inicio_clientes, int cod)
{
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

// Verifica, consoante o endereço de memória de um certo utilizador, se o seu NIF é igual ao que foi inserido para um novo utilizador.
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

// Verifica cada cliente existente, se o seu codigo do elemento que está a verificar for maior que o elemento seguinte, irá ser feita uma troca
// para ordenar todos os elementos da lista ligada por um valor crescente.
Cliente* bubbleSortClientes(Cliente* inicio_clientes) {
    Cliente* atual, * seguinte;
    int b = 1, aux_codigo, aux_NIF, aux_saldo;
    char aux_nome[50], aux_geocodigo[100];
    while (b)
    {
        b = 0;
        atual = inicio_clientes;
        if (atual == NULL)
        {
            return 0;
        }
        while (atual->seguinte_cliente != NULL)
        {
            seguinte = atual->seguinte_cliente;
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
    inicio_clientes = atual;
    return inicio_clientes;
}
#pragma endregion

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES----------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES----------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES

// Ler ficheiro de texto, contendo informação sobre os gestores.
// Serão todos os dados, inseridos numa lista ligada, que de inicio é vazia.
Gestor* lerFicheiro_gestores(Gestor* inicio_gestor, FILE* dados_gestor)
{
    char linha[MAX_LINE_LEN];
    while (fgets(linha, MAX_LINE_LEN, dados_gestor))
    {
        Gestor* novo_nodo = malloc(sizeof(struct registo_gestor));
        sscanf(linha, "%d;%[^;];%[^;];%d;%s\n", &novo_nodo->codigo, novo_nodo->nome, novo_nodo->senha, &novo_nodo->encriptado, novo_nodo->area_responsavel);
        novo_nodo->seguinte_gestor = inicio_gestor;
        inicio_gestor = novo_nodo;
    }
    fclose(dados_gestor);
    return inicio_gestor;
}

// Apresenta na consola toda a informação existente sobre os gestores.
void listarGestores(Gestor* inicio_gestor)
{
    system("cls");
    if (inicio_gestor == NULL)
    {
        printf("Nao existem gestores, por favor registe-se.\n");
        return 0;
    }
    else
    {
        printf("Dados de Gestores:\n------------------------------------------------------------------------------------------------------------------------\n");
        while (inicio_gestor != NULL)
        {
            printf("Codigo:%d        Nome:%s    Area:%s\n", inicio_gestor->codigo, inicio_gestor->nome, inicio_gestor->area_responsavel);
            inicio_gestor = inicio_gestor->seguinte_gestor;
        }
        printf("------------------------------------------------------------------------------------------------------------------------\n");
    }

}

// Escreve todos os dados inseridos sobre os gestores, em ficheiro de texto.
Gestor* escreverFicheiro_gestores(Gestor* inicio_gestores, FILE* dados_gestores)
{
    dados_gestores = fopen("gestores.txt", "wt");
    if (dados_gestores == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicio_gestores != NULL)
    {
        fprintf(dados_gestores, "%d;%s;%s;%d;%s\n", inicio_gestores->codigo, inicio_gestores->nome, inicio_gestores->senha, inicio_gestores->encriptado, inicio_gestores->area_responsavel);
        inicio_gestores = inicio_gestores->seguinte_gestor;
    }

    fclose(dados_gestores);
}

// Escreve todos os dados inseridos sobre os gestores, em ficheiro binário.
Gestor* escreverFicheiro_gestores_bin(Gestor* inicio_gestores, FILE* dados_gestores)
{
    dados_gestores = fopen("gestores.bin", "wb");
    if (dados_gestores == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicio_gestores != NULL)
    {
        fprintf(dados_gestores, "%d;%s;%s;%d;%s\n", inicio_gestores->codigo, inicio_gestores->nome, inicio_gestores->senha, inicio_gestores->encriptado, inicio_gestores->area_responsavel);
        inicio_gestores = inicio_gestores->seguinte_gestor;
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
        inicio_gestores = inicio_gestores->seguinte_gestor;
    }
    if (inicio_gestores == NULL)
        return 1;
}

// Verifica cada gestor existente, se o seu codigo do elemento que está a verificar for maior que o elemento seguinte, irá ser feita uma troca
// para ordenar todos os elementos da lista ligada por um valor crescente.
Gestor* bubbleSortGestores(Gestor* inicio_gestor) {
    Gestor* atual, * seguinte;
    int aux_codigo, b = 1, aux_encriptado;
    char aux_senha[50], aux_nome[50], aux_area_responsavel[50];
    while (b)
    {
        b = 0;
        atual = inicio_gestor;
        if (atual == NULL)
        {
            return 0;
        }
        while (atual->seguinte_gestor != NULL)
        {
            seguinte = atual->seguinte_gestor;
            if (atual->codigo > seguinte->codigo)
            {
                aux_codigo = atual->codigo;
                strcpy(aux_nome, atual->nome);
                strcpy(aux_senha, atual->senha);
                aux_encriptado = atual->encriptado;
                strcpy(aux_area_responsavel, atual->area_responsavel);

                atual->codigo = seguinte->codigo;
                strcpy(atual->nome, seguinte->nome);
                strcpy(atual->senha, seguinte->senha);
                atual->encriptado = seguinte->encriptado;
                strcpy(atual->area_responsavel, seguinte->area_responsavel);

                seguinte->codigo = aux_codigo;
                strcpy(seguinte->nome, aux_nome);
                strcpy(seguinte->senha, aux_senha);
                seguinte->encriptado = aux_encriptado;
                strcpy(seguinte->area_responsavel, aux_area_responsavel);

                b = 1;
            }
            atual = seguinte;
        }
    }
    inicio_gestor = atual;
    return inicio_gestor;
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
            inicio_gestores = inicio_gestores->seguinte_gestor;
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
Meio* inserirMeio(Grafo* inicio_grafo, Meio* inicio_meios, int cod, char nome[50], float bat, float aut, int custo, char geo[50])
{
    Grafo* aux = inicio_grafo;
    int inserir = 0;
    while (inserir != 1)
    {
        if (inicio_meios == NULL)
        {
            Meio* novo_meio = malloc(sizeof(Meio));
            novo_meio->codigo = cod;
            strcpy(novo_meio->tipo, nome);
            novo_meio->bateria = bat;
            novo_meio->autonomia = aut;
            novo_meio->custo = custo;
            strcpy(novo_meio->geocodigo, geo);
            if (!existeVertice(aux, novo_meio->geocodigo))
            {
                inserirVertice(aux, novo_meio->geocodigo);
            }
            novo_meio->ativo = 0;
            novo_meio->seguinte_meio = NULL;
            inicio_meios = novo_meio;
            printf("Meio com codigo %d inserido com sucesso.\n", novo_meio->codigo);
            Sleep(2000);
            system("cls");
            return inicio_meios;
        }
        if (inicio_meios->seguinte_meio == NULL)
        {
            Meio* novo_meio = malloc(sizeof(Meio));
            novo_meio->codigo = cod;
            strcpy(novo_meio->tipo, nome);
            novo_meio->bateria = bat;
            novo_meio->autonomia = aut;
            novo_meio->custo = custo;
            strcpy(novo_meio->geocodigo, geo);
            if (!existeVertice(aux, novo_meio->geocodigo))
            {
                int auxVertice, escolhaAdjacente, inserido = 1;
                auxVertice=inserirVertice(aux, novo_meio->geocodigo);
                if (auxVertice == 1)
                {
                    printf("A %s tem algum destino? 1-Sim/0-Nao\n", novo_meio->geocodigo);
                    printf("A sua escolha:");
                    scanf("%d", &escolhaAdjacente);
                    while(escolhaAdjacente == 1 && inserido != 0)
                    {
                        char novoAdjacente[50];
                        float novoPeso;
                        printf("Nome do novo adjacente a %s:", novo_meio->geocodigo);
                        scanf("%s", novoAdjacente);
                        printf("Distancia em km:");
                        scanf("%f", &novoPeso);
                        if (inserirAdjacente(aux, novo_meio->geocodigo, novoAdjacente, novoPeso))
                        {
                            printf("Adjacente inserido com sucesso.\n");
                            printf("Deseja inserir mais adjacentes ao geocodigo %s?\n 1-Sim/0-Nao\n", novo_meio->geocodigo);
                            printf("A sua escolha:");
                            scanf("%d", &inserido);
                        }
                    }
                }
            }
            novo_meio->ativo = 0;
            inicio_meios->seguinte_meio = novo_meio;
            novo_meio->seguinte_meio = NULL;
            inicio_meios = novo_meio;
            inserir = 1;
            printf("Meio com codigo %d inserido com sucesso.\n", novo_meio->codigo);
            Sleep(2000);
            system("cls");
            return inicio_meios;
        }
        inicio_meios = inicio_meios->seguinte_meio;
    }
    return inicio_meios;
}

// Função para inserir um novo cliente, é pedido ao gestor na função main, um novo codigo, nome, NIF e saldo.  
// De seguida é inserido no ultimo lugar da lista ligada dos clientes, quando é o ultimo endereço NULL.
Cliente* inserirCliente(Cliente* inicio_clientes, int cod, char nome[50], int NIF, int saldo, char geocodigo[100])
{
    int inserir = 0;
    while (inserir != 1)
    {
        if (inicio_clientes == NULL)
        {
            Cliente* novo_cliente = malloc(sizeof(Cliente));
            novo_cliente->codigo = cod;
            strcpy(novo_cliente->nome, nome);
            novo_cliente->NIF = NIF;
            novo_cliente->saldo = saldo;
            strcpy(novo_cliente->geocodigo, geocodigo);
            novo_cliente->seguinte_cliente = NULL;
            inicio_clientes = novo_cliente;
            printf("Cliente com codigo %d adicionado com sucesso.\n", novo_cliente->codigo);
            Sleep(2000);
            system("cls");
            return inicio_clientes;
        }
        if (inicio_clientes->seguinte_cliente == NULL)
        {
            Cliente* novo_cliente = malloc(sizeof(Cliente));
            novo_cliente->codigo = cod;
            strcpy(novo_cliente->nome, nome);
            novo_cliente->NIF = NIF;
            novo_cliente->saldo = saldo;
            strcpy(novo_cliente->geocodigo, geocodigo);
            inicio_clientes->seguinte_cliente = novo_cliente;
            novo_cliente->seguinte_cliente = NULL;
            inicio_clientes = novo_cliente;
            printf("Cliente com codigo %d adicionado com sucesso.\n", novo_cliente->codigo);
            Sleep(2000);
            system("cls");
            return inicio_clientes;
        }
        inicio_clientes = inicio_clientes->seguinte_cliente;
    }
    return inicio_clientes;
}

// Função para inserir um novo gestor, é pedido ao gestor na função main, um novo codigo, nome e senha.  
// De seguida é inserido no ultimo lugar da lista ligada dos gestores, quando é o ultimo endereço NULL.
Gestor* inserirGestor(Gestor* inicio_gestor, int cod, char nome[50], char senha[50], char area[50])
{
    int inserir = 0, encriptado;
    while (inserir != 1)
    {
        if (inicio_gestor == NULL)
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
            strcpy(novo_gestor->area_responsavel, area);
            novo_gestor->seguinte_gestor = NULL;
            inicio_gestor = novo_gestor;
            printf("Gestor com codigo %d inserido com sucesso.\n", novo_gestor->codigo);
            Sleep(2000);
            system("cls");
            return inicio_gestor;
        }
        if (inicio_gestor->seguinte_gestor == NULL)
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
            strcpy(novo_gestor->area_responsavel, area);
            inicio_gestor->seguinte_gestor = novo_gestor;
            novo_gestor->seguinte_gestor = NULL;
            inicio_gestor = novo_gestor;
            inserir = 1;
            printf("Gestor com codigo %d inserido com sucesso.\n", novo_gestor->codigo);
            Sleep(2000);
            system("cls");
            return inicio_gestor;
        }
        inicio_gestor = inicio_gestor->seguinte_gestor;
    }
    return inicio_gestor;
}

// Pequena função para encriptação da senha do gestor.
int encryptSenha(Gestor* inicio_gestor, char senha[50])
{
    for (int i = 0; i < strlen(senha); i++)
    {
        senha[i] = senha[i] + 5;
    }
    return 1;
}

// Pequena função para desencriptação da senha do gestor.
int decryptSenha(Gestor* inicio_gestor, char senha[50])
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
Meio* removerMeio(Meio* inicio_meios, int cod)
{
    Meio* anterior = inicio_meios, * atual = inicio_meios, * aux;

    if (atual == NULL) return(NULL); // Lista vazia.
    else if (atual->codigo == cod) // remoção do 1º registo
    {
        aux = atual->seguinte_meio;
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
            atual = atual->seguinte_meio;
        }
        if (atual == NULL) return(inicio_meios);
        else // Remoção do meio com cod introduzido.
        {
            anterior->seguinte_meio = atual->seguinte_meio;
            free(atual);
            printf("Meio com cod %d removido com sucesso.\n", cod);
            Sleep(2000);
            system("cls");
            return(inicio_meios);
        }
    }
}

// Função para remover algum cliente, a partir do código inserido pelo gestor. É removido o cliente e de seguida é retornada toda a lista ligada
// com o meio removido.
Cliente* removerCliente(Cliente* inicio_clientes, int cod)
{
    Cliente* anterior = inicio_clientes, * atual = inicio_clientes, * aux;

    if (atual == NULL) return(NULL); // Lista vazia.
    else if (atual->codigo == cod) // remoção do 1º registo
    {
        aux = atual->seguinte_cliente;
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
            atual = atual->seguinte_cliente;
        }
        if (atual == NULL) return(inicio_clientes);
        else // Remoção do cliente com cod introduzido.
        {
            anterior->seguinte_cliente = atual->seguinte_cliente;
            free(atual);
            printf("Cliente com cod %d removido com sucesso.\n", cod);
            Sleep(2000);
            system("cls");
            return(inicio_clientes);
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
        aux = atual->seguinte_gestor;
        free(atual);
        printf("Gestor com cod %d removido com sucesso.\n", cod);
        return(aux);
    }
    else
    {
        while ((atual != NULL) && (atual->codigo != cod)) // Iteração até ser igual.
        {
            anterior = atual;
            atual = atual->seguinte_gestor;
        }
        if (atual == NULL) return(inicio_gestores); // Lista ligada toda percorrida, nao foi encontrado nenhum gestor com o codigo inserido.
        else // Remoção do gestor com cod introduzido.
        {
            anterior->seguinte_gestor = atual->seguinte_gestor;
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
    char nova_senha[50], novo_nome[50], senha[50], nova_area_responsavel[50];
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
                printf("Nome:%s     Codigo:%d       Area:%s\n", inicio_gestores->nome, inicio_gestores->codigo, inicio_gestores->area_responsavel);
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
                    scanf("%s", nova_area_responsavel);
                    strcpy(inicio_gestores->area_responsavel, nova_area_responsavel);
                    printf("A sua area responsavel foi alterada com sucesso.\n");
                    printf("A sua nova area e a seguinte: %s\n", inicio_gestores->area_responsavel);
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
        inicio_gestores = inicio_gestores->seguinte_gestor;
    }
}

// Função para alteração de dados do cliente.
// É pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes é possivel fazer alteração de nome, codigo e NIF.
ResFuncoes alterarDadosCliente(Cliente* inicio_clientes, Transacao* inicio_transacao) {
    int codigo, NIF, novo_codigo, novo_NIF, inserir = 1, escolha, codigoAux;
    char novo_nome[50], novo_geocodigo[100];
    Cliente* aux = inicio_clientes;
    Transacao* auxTrans = inicio_transacao;
    if (inicio_clientes == NULL)
    {
       /* printf("Nao existem clientes.\n");
        Sleep(2000);
        system("cls");*/
        return CLIENTES_NAO_EXISTEM;
    }
    printf("Introduza o seu codigo:");
    scanf("%d", &codigo);
    printf("Introduza o seu NIF:");
    scanf("%d", &NIF);
    if (existeClienteCod(aux, codigo) == 1)
    {
        return COD_CLIENTE_NAO_EXISTE;
    }
    else if (existeClienteNIF(aux, NIF) == 1)
    {
        /*printf("O codigo %d, nao esta registado com o NIF %d.\n", codigo, NIF);
        Sleep(2000);
        system("cls");*/
        return NIF_CLIENTE_NAO_EXISTE;
    }
    while (inicio_clientes != NULL)
    {
        if (inicio_clientes->codigo == codigo && inicio_clientes->NIF == NIF)
        {
            do
            {
                printf("Este sao os seus dados, %s.\n", inicio_clientes->nome);
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("Nome:%s     Codigo:%d       NIF:%d      Localizacao:%s\n", inicio_clientes->nome, inicio_clientes->codigo, inicio_clientes->NIF, inicio_clientes->geocodigo);
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
                    strcpy(inicio_clientes->nome, novo_nome);
                    printf("Nome alterado com sucesso para %s.\n", inicio_clientes->nome);
                    Sleep(2000);
                    system("cls");
                    break;
                case 2:
                    printf("Insira o seu novo codigo:");
                    scanf("%d", &novo_codigo);
                    if (existeClienteCod(aux, novo_codigo))
                    {
                        codigoAux = inicio_clientes->codigo;
                        inicio_clientes->codigo = novo_codigo;
                        printf("O seu novo codigo %d\n", inicio_clientes->codigo);
                        if (existeClienteTransacao(auxTrans, codigoAux))
                        {
                            while (auxTrans != NULL )
                            {
                                if (auxTrans->codigo_utilizador == codigoAux)
                                {
                                    auxTrans->codigo_utilizador = novo_codigo;
                                }
                                auxTrans = auxTrans->seguinte_transacao;
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
                            inicio_clientes->NIF = novo_NIF;
                            printf("O seu novo NIF %d\n", inicio_clientes->NIF);
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
                    strcpy(inicio_clientes->geocodigo, novo_geocodigo);
                    printf("Geocodigo alterado com sucesso para %s.\n", inicio_clientes->geocodigo);
                    Sleep(2000);
                    system("cls");
                    break;
                case 0:
                    return 1;
                    break;
                }
            } while (escolha != 0);
        }
        inicio_clientes = inicio_clientes->seguinte_cliente;
    }
}

// Função para alteração de dados de algum meio.
// É pedido o codigo do meio a alterar. É possivel alterar o seu codigo, tipo, se está ativo, custo, bat, aut, etc...
Meio* alterarMeio(Meio* inicio_meios)
{
    int cod, cod_alterar, ativo_alterar, custo_alterar, escolha;
    float bat_alterar, aut_alterar;
    char meio_nome_alterar[50], geocodigo_alterar[50];
    Meio* aux = inicio_meios;
    if (inicio_meios == NULL)
    {
        printf("Nao existem meios.\n");
        Sleep(2000);
        system("cls");
        return 0;
    }
    printf("Introduza o codigo do meio que pretende alterar:");
    scanf("%d", &cod);
    if (existeMeio(inicio_meios, cod))
    {
        printf("O meio com o codigo %d nao existe.\n", cod);
        Sleep(2000);
        system("cls");
        return 0;
    }
    system("cls");
    while (inicio_meios != NULL)
    {
        if (inicio_meios->codigo == cod)
        {
            do
            {
                printf("Este sao os dados do meio cod %d.\n", inicio_meios->codigo);
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                printf("Codigo:%d\nTipo:%s\nBateria:%.2f\nAut:%.2f\nCusto:%d\nGeo:%s\nAtivo:%d\n", inicio_meios->codigo, inicio_meios->tipo, inicio_meios->bateria, inicio_meios->autonomia, inicio_meios->custo, inicio_meios->geocodigo, inicio_meios->ativo);
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
                        inicio_meios->codigo = cod_alterar;
                        printf("Codigo alterado com sucesso. Novo codigo %d.\n", inicio_meios->codigo);
                        Sleep(2000);
                        system("cls");
                    }
                    break;
                case 2:
                    printf("Insira o novo tipo de meio:");
                    scanf("%s", meio_nome_alterar);
                    strcpy(inicio_meios->tipo, meio_nome_alterar);
                    printf("Nome alterado com sucesso para %s.\n", inicio_meios->tipo);
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
                    inicio_meios->bateria = bat_alterar;
                    printf("Novo nivel de bateria %.2f\n", inicio_meios->bateria);
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
                    inicio_meios->autonomia = aut_alterar;
                    printf("Novo nivel de autonomia %.2f\n", inicio_meios->autonomia);
                    Sleep(2000);
                    system("cls");
                    break;
                case 5:
                    printf("Insira o novo custo:");
                    scanf("%d", &custo_alterar);
                    inicio_meios->custo = custo_alterar;
                    printf("Novo custo do meio %d\n", inicio_meios->custo);
                    Sleep(2000);
                    system("cls");
                    break;
                case 6:
                    printf("Insira um novo geocodigo:");
                    scanf("%s", geocodigo_alterar);
                    strcpy(inicio_meios->geocodigo, geocodigo_alterar);
                    printf("Novo geocodigo %s\n", inicio_meios->geocodigo);
                    Sleep(2000);
                    system("cls");
                    break;
                case 7:
                    printf("Este veiculo esta ativo?1-Sim/0-Nao\n");
                    printf("A sua escolha:");
                    scanf("%d", &ativo_alterar);
                    if (ativo_alterar == 1)
                    {
                        if (inicio_meios->ativo == 1)
                        {
                            printf("Meio ja esta ativo.\n");
                            Sleep(2000);
                            system("cls");
                        }
                        else
                        {
                            inicio_meios->ativo = 1;
                            system("cls");
                        }
                    }
                    else
                    {
                        if (inicio_meios->ativo == 0)
                        {
                            printf("Meio ja nao estava ativo.\n");
                            Sleep(2000);
                            system("cls");
                        }
                        else
                        {
                            inicio_meios->ativo = 0;

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
        inicio_meios = inicio_meios->seguinte_meio;
    }
}
#pragma endregion
// ---------------------------------------------------FIM-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------


// ---------------------------------------------------------------INICIO_OP_UTILIZADOR-----------------------------------------------------------------
#pragma region OP_Utilizador
// Função para carregamento de saldo, de um certo utilizador.
// É pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes é possivel carregar o saldo desse mesmo utilizador.
Cliente* carregarSaldo(Cliente* inicio_clientes, Transacao* inicio_transacao) {
    if (inicio_clientes == NULL)
    {
        return CLIENTES_NAO_EXISTEM;
    }
    Transacao* auxTrans = inicio_transacao;
    int codigo, NIF, inserir = 1;
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
            {
                return SALDO_CARR_NEGATIVO;
            }
            inicio_clientes->saldo = saldo_carregar + inicio_clientes->saldo;
            printf("%d carregado com sucesso. Tem agora %d de saldo.\n", saldo_carregar, inicio_clientes->saldo);
            if (inicio_transacao == NULL)
            {
                if (inicio_transacao = criarTransacao(inicio_transacao, inicio_clientes->codigo, saldo_carregar, inicio_clientes->nome))
                    return inicio_transacao;
            }
            while (inserir == 1)
            {
                if (inicio_transacao->seguinte_transacao == NULL)
                {
                    if (criarTransacao(auxTrans, inicio_clientes->codigo, saldo_carregar, inicio_clientes->nome))
                        inserir = 0;
                }
                inicio_transacao = inicio_transacao->seguinte_transacao;
                if (inserir == 0)
                {
                    return SUCESSO;
                }
            }
        }
        inicio_clientes = inicio_clientes->seguinte_cliente;
    }
    if (inicio_clientes == NULL)
    {
        return COD_NIF_NAO_EXISTE;
    }
    Sleep(2000);
    system("cls");
}

// Função para consulta de saldo, de um certo utilizador.
// É pedido o codigo e o NIF, caso coincidam com algum dos utilizadores existentes é possivel visualizar quando saldo está disponível.
ResFuncoes consultaSaldo(Cliente* inicio_clientes, int *saldoVerifica) {
    int codigo, NIF;
    printf("Introduza o seu codigo:");
    scanf("%d", &codigo);
    //printf("Introduza o seu NIF:");
    //scanf("%d", &NIF);
    if (inicio_clientes == NULL)
    {
        return CLIENTES_NAO_EXISTEM;
    }
    while (inicio_clientes != NULL)
    {
        if (inicio_clientes->codigo == codigo /*&& inicio_clientes->NIF == NIF*/)
        {
            printf("Voce tem %d de saldo.\n", inicio_clientes->saldo);
            return SALDO_ATUAL;
        }
        inicio_clientes = inicio_clientes->seguinte_cliente;
    }
    if (inicio_clientes == NULL)
    {
        //printf("Nao existe o cliente com o cod %d.\n", codigo);
        return COD_NIF_NAO_EXISTE;
    }
}

// Funçáo para realização de aluguer de qualquer meio existente, que não esteja ativo.
// É pedido o codigo de utilizador, é verificado se existe esse mesmo utilizador. De seguida é perguntado qual o meio que deseja alugar. 
// São apresentados dados, tais como o tipo de meio, o seu custo e o saldo do utilizador. Caso o utilizador, decida comprar o meio
// É criado um novo registo na lista ligada de alugueres.
Aluguer* realizarAluguer(Cliente* inicio_clientes, Aluguer* inicio_aluguer, Meio* inicio_meios)
{
    int meio_Alugar, codigo_utilizador, NIF;
    printf("Insira o seu codigo:");
    scanf("%d", &codigo_utilizador);
    if (existeClienteCod(inicio_clientes, codigo_utilizador) == 0)
    {
        while (inicio_clientes->codigo != codigo_utilizador)
            inicio_clientes = inicio_clientes->seguinte_cliente;
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
                if (inicio_clientes->saldo < inicio_meios->custo)
                {
                    printf("Nao tem saldo suficiente para efetuar a compra.\n");
                    Sleep(2000);
                    system("cls");
                    return 0;
                }
                else if (inicio_meios->ativo == 1)
                {
                    printf("Nao pode alugar esse meio, pois ja esta alugado.\n");
                    Sleep(2000);
                    system("cls");
                }
                else
                {
                    time_t dataCompra;
                    time(&dataCompra);
                    char aux_data_compra[50];
                    strcpy(aux_data_compra, ctime(&dataCompra));
                    for (int i = 0; i < strlen(aux_data_compra); i++)
                    {
                        if (aux_data_compra[i] == '\n')
                            aux_data_compra[i] = '\0';
                    }
                    printf("Data da compra: %s\n", ctime(&dataCompra));
                    int inserir = 0;
                    inicio_clientes->saldo = inicio_clientes->saldo - inicio_meios->custo;
                    printf("O seu novo saldo %d\n", inicio_clientes->saldo);
                    while (inserir != 1)
                    {
                        if (inicio_aluguer == NULL)
                        {
                            Aluguer* novo_nodo = malloc(sizeof(Aluguer));
                            novo_nodo->seguinte_compra = NULL;
                            inicio_aluguer = novo_nodo;
                        }
                        if (inicio_aluguer->seguinte_compra == NULL)
                        {
                            Aluguer* novo_nodo = malloc(sizeof(Aluguer));
                            novo_nodo->cod_comprador = inicio_clientes->codigo;
                            strcpy(novo_nodo->nome_comprador, inicio_clientes->nome);
                            strcpy(novo_nodo->data_compra, aux_data_compra);
                            strcpy(novo_nodo->nome_meio_comprado, inicio_meios->tipo);
                            inicio_meios->ativo = 1;
                            inicio_aluguer->seguinte_compra = novo_nodo;
                            novo_nodo->seguinte_compra = NULL;
                            inicio_aluguer = novo_nodo;
                            printf("Compra efetuada com sucesso.\n");
                            Sleep(2000);
                            system("cls");
                            inserir = 1;
                            return inicio_aluguer;
                        }
                        inicio_aluguer = inicio_aluguer->seguinte_compra;
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
void listarGeocodigo(Meio* inicio_meios)
{
    system("cls");
    int verificado = 0, existe = 0;
    char verificar_geocodigo[50];
    Meio* aux_print = inicio_meios;
    printf("Introduza o geocodigo que pretende verificar:");
    scanf("%s", verificar_geocodigo);
    getchar();

    if (inicio_meios == NULL)
        return 0;
    while (aux_print != NULL && existe == 0)
    {
        if (strcmp(verificar_geocodigo, aux_print->geocodigo) == 0)
        {
            existe = 1;
        }
        aux_print = aux_print->seguinte_meio;
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
    while (inicio_meios != NULL)
    {
        if (strcmp(verificar_geocodigo, inicio_meios->geocodigo) == 0)
        {
            printf("Codigo:%d      Tipo:%s      Bat:%.2f      Aut:%.2f      Custo:%d\n", inicio_meios->codigo, inicio_meios->tipo, inicio_meios->bateria, inicio_meios->autonomia, inicio_meios->custo);
        }
        inicio_meios = inicio_meios->seguinte_meio;
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}
#pragma endregion
// -----------------------------------------------------------------FIM_OP_UTILIZADOR-------------------------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE ALUGUER----------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAÇÃO DE ALUGUER
// Ler ficheiro de texto, contendo informação sobre os alugueres.
// Serão todos os dados, inseridos numa lista ligada, que de inicio é vazia.
Aluguer* lerFicheiro_Aluguer(Aluguer* inicio_aluguer, FILE* dados_aluguer)
{
    char linha[MAX_LINE_LEN];
    while (fgets(linha, MAX_LINE_LEN, dados_aluguer))
    {
        Aluguer* novo_nodo = malloc(sizeof(Aluguer));
        sscanf(linha,"%d;%[^;];%[^;];%[^\n]\n", &novo_nodo->cod_comprador, novo_nodo->data_compra, novo_nodo->nome_comprador, novo_nodo->nome_meio_comprado);
        novo_nodo->seguinte_compra = inicio_aluguer;
        inicio_aluguer = novo_nodo;
    }
    fclose(dados_aluguer);
    return inicio_aluguer;
}

// Função para listar na consola, o historico dos alugueres já feitos.
void listarAluguer(Aluguer* inicio_aluguer)
{
    system("cls");
    if (inicio_aluguer == NULL)
    {
        printf("Nao existem alugueres.\n");
        Sleep(2000);
        system("cls");
        return 0;
    }
    printf("Dados de Alugueres:\n------------------------------------------------------------------------------------------------------------------------\n");
    while (inicio_aluguer != NULL)
    {
        printf("Codigo:%d   Data de compra:%s       Nome:%s Meio:%s\n", inicio_aluguer->cod_comprador, inicio_aluguer->data_compra, inicio_aluguer->nome_comprador, inicio_aluguer->nome_meio_comprado);
        inicio_aluguer = inicio_aluguer->seguinte_compra;
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}

// Verifica cada aluguer existente, se a sua data for maior que a do seguinte elemento, irá ser feita uma troca
// para ordenar todos os elementos por ordem de compra.
Aluguer* bubbleSortAluguer(Aluguer* inicio_aluguer) {
    Aluguer* atual, * seguinte;
    int aux_codigo, b = 1;
    char aux_data[50], aux_comprador[50], aux_meio_comprado[50];
    while (b)
    {
        b = 0;
        atual = inicio_aluguer;
        if (atual == NULL)
        {
            return 0;
        }
        while (atual->seguinte_compra != NULL)
        {
            seguinte = atual->seguinte_compra;
            if (strcmp(atual->data_compra, seguinte->data_compra) > 0)
            {
                aux_codigo = atual->cod_comprador;
                strcpy(aux_comprador, atual->nome_comprador);
                strcpy(aux_data, atual->data_compra);
                strcpy(aux_meio_comprado, atual->nome_meio_comprado);

                atual->cod_comprador = seguinte->cod_comprador;
                strcpy(atual->nome_comprador, seguinte->nome_comprador);
                strcpy(atual->data_compra, seguinte->data_compra);
                strcpy(atual->nome_meio_comprado, seguinte->nome_meio_comprado);

                seguinte->cod_comprador = aux_codigo;
                strcpy(seguinte->nome_comprador, aux_comprador);
                strcpy(seguinte->data_compra, aux_data);
                strcpy(seguinte->nome_meio_comprado, aux_meio_comprado);
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
        fprintf(dados_aluguer, "%d;%s;%s;%s\n", inicio_aluguer->cod_comprador, inicio_aluguer->data_compra, inicio_aluguer->nome_comprador, inicio_aluguer->nome_meio_comprado);
        inicio_aluguer = inicio_aluguer->seguinte_compra;
    }
    fclose(dados_aluguer);
}

 //Escreve todos os dados sobre os alugueres, em ficheiro binário.
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
        fprintf(dados_aluguer, "%d;%s;%s;%s\n", inicio_aluguer->cod_comprador, inicio_aluguer->data_compra, inicio_aluguer->nome_comprador, inicio_aluguer->nome_meio_comprado);
        inicio_aluguer = inicio_aluguer->seguinte_compra;
    }
    fclose(dados_aluguer);
}

int existeClienteTransacao(Transacao* inicio_transacao, int codVerificar)
{
    int teste = 0;
    Transacao* aux = inicio_transacao;
    while (aux != NULL)
    {
        if (aux->codigo_utilizador == codVerificar)
            return 1;
        aux = aux->seguinte_transacao;
    }
    return 0;
}
#pragma endregion
// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE ALUGUER----------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE TRANSACOES----------------------------------------------------
#pragma region LEITURA/ESCRITA/REPRESENTAÇÃO DE TRANSACOES
Transacao* lerFicheiro_transacao(Transacao* inicio_transacao, FILE* dados_transacao)
{
    char linha[MAX_LINE_LEN];
    while (fgets(linha, MAX_LINE_LEN, dados_transacao))
    {
        Transacao* novo_nodo = malloc(sizeof(Transacao));
        sscanf(linha, "%d;%[^;];%d;%[^\n]", &novo_nodo->codigo_utilizador, novo_nodo->nome_transacao, &novo_nodo->montante_carregado, novo_nodo->data_transacao);
        novo_nodo->seguinte_transacao = inicio_transacao;
        inicio_transacao = novo_nodo;
    }
    fclose(dados_transacao);
    return inicio_transacao;
}

Transacao* escreverFicheiro_transacao(Transacao* inicio_transacao, FILE* dados_transacao)
{
    if (inicio_transacao == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return 0;
    }
    dados_transacao = fopen("historico_transacoes.txt", "wt");
    if (dados_transacao == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicio_transacao != NULL)
    {
        fprintf(dados_transacao, "%d;%s;%d;%s\n", inicio_transacao->codigo_utilizador, inicio_transacao->nome_transacao, inicio_transacao->montante_carregado, inicio_transacao->data_transacao);
        inicio_transacao = inicio_transacao->seguinte_transacao;
    }
    fclose(dados_transacao);
}

Transacao* escreverFicheiro_transacao_bin(Transacao* inicio_transacao, FILE* dados_transacao)
{
    if (inicio_transacao == NULL)
    {
        printf("O ficheiro nao foi lido.\n");
        return 0;
    }
    dados_transacao = fopen("historico_transacoes.bin", "wb");
    if (dados_transacao == NULL)
    {
        printf("Nao foi possivel abrir o ficheiro.\n");
        return 0;
    }
    while (inicio_transacao != NULL)
    {
        fprintf(dados_transacao, "%d;%s;%d;%s\n", inicio_transacao->codigo_utilizador, inicio_transacao->nome_transacao, inicio_transacao->montante_carregado, inicio_transacao->data_transacao);
        inicio_transacao = inicio_transacao->seguinte_transacao;
    }
    fclose(dados_transacao);
}

void listarTransacao(Transacao* inicio_transacao)
{
    system("cls");
    if (inicio_transacao == NULL)
    {
        printf("Nao existem registos de transacoes.\n");
        Sleep(2000);
        system("cls");
        return 0;
    }
    printf("Dados de transacoes:\n------------------------------------------------------------------------------------------------------------------------\n");
    while (inicio_transacao != NULL)
    {
        printf("Codigo:%d   Nome:%s     Mont.Carregado:%dEur   Data:%s \n", inicio_transacao->codigo_utilizador, inicio_transacao->nome_transacao, inicio_transacao->montante_carregado, inicio_transacao->data_transacao);
        inicio_transacao = inicio_transacao->seguinte_transacao;
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}

Transacao* criarTransacao(Transacao* inicio_transacao, int codigoCliente, int saldoCarregar, char nomeCliente[50])
{
    Transacao* nova_transacao = malloc(sizeof(Transacao));
    nova_transacao->codigo_utilizador = codigoCliente;
    nova_transacao->montante_carregado = saldoCarregar;
    strcpy(nova_transacao->nome_transacao, nomeCliente);
    time_t dataTransacao;
    time(&dataTransacao);
    char aux_data_transacao[50];
    strcpy(aux_data_transacao, ctime(&dataTransacao));
    for (int i = 0; i < strlen(aux_data_transacao); i++)
    {
        if (aux_data_transacao[i] == '\n')
            aux_data_transacao[i] = '\0';
    }
    strcpy(nova_transacao->data_transacao, aux_data_transacao);

    if (inicio_transacao == NULL) {
        inicio_transacao = nova_transacao;
    }
    else {
        Transacao* current_transacao = inicio_transacao;
        while (current_transacao->seguinte_transacao != NULL) {
            current_transacao = current_transacao->seguinte_transacao;
        }
        current_transacao->seguinte_transacao = nova_transacao;
    }
        nova_transacao->seguinte_transacao = NULL;
        inicio_transacao = nova_transacao;
    return inicio_transacao;
}
#pragma endregion
// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE TRANSACOES----------------------------------------------------


// ---------------------------------------------------INICIO-LEITURA/ESCRITA/REPRESENTAÇÃO DE CIDADES----------------------------------------------------

#pragma region LEITURA/ESCRITA/REPRESENTAÇÃO DE CIDADES
Grafo* lerFicheiro_Vertices(Grafo* inicio_grafo,Meio* inicio_meios, FILE* dados_grafo)
{
    //int existe = 0;
    //Grafo* aux = inicio_grafo;
    //Grafo* auxExiste = inicio_grafo;
    //Meio* auxMeio = inicio_meios;
    //while (auxMeio != NULL)
    //{
    //    existe = 0;
    //    auxExiste = inicio_grafo;
    //    if (auxExiste == NULL)
    //    {
    //    }
    //    else
    //    {
    //        while (auxExiste != NULL)
    //        {
    //            if (strcmp(auxExiste->vertice, auxMeio->geocodigo) == 0)
    //            {
    //                existe = 1;
    //            }
    //            auxExiste = auxExiste->seguinte_vertice;
    //        }
    //    }
    //    while (existe == 0)
    //    {
    //        Grafo* novo_nodo = malloc(sizeof(Grafo));
    //        strcpy(novo_nodo->vertice, auxMeio->geocodigo);
    //        novo_nodo->meios = NULL;
    //        novo_nodo->clientes = NULL;
    //        novo_nodo->adjacentes = NULL;
    //        novo_nodo->seguinte_vertice = inicio_grafo;
    //        inicio_grafo = novo_nodo;
    //        existe = 1;
    //    }
    //    //Grafo* novo_nodo = malloc(sizeof(Grafo));
    //    //strcpy(novo_nodo->vertice, auxMeio->geocodigo);
    //    //novo_nodo->meios = NULL;
    //    //novo_nodo->clientes = NULL;
    //    //novo_nodo->adjacentes = NULL;
    //    //novo_nodo->seguinte_vertice = inicio_grafo;
    //    //inicio_grafo = novo_nodo;
    //    auxMeio = auxMeio->seguinte_meio;
    //}
    //return inicio_grafo;
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
                Grafo* novo_nodo = malloc(sizeof(Grafo));
                strcpy(novo_nodo->vertice, token_vertice);
                novo_nodo->meios = NULL;
                novo_nodo->adjacentes = NULL;
                novo_nodo->seguinte_vertice = inicio_grafo;
                inicio_grafo = novo_nodo;
                token_vertice = strtok(NULL, ";");
            }
    }
    return inicio_grafo;
}

Grafo* lerFicheiro_Adjacentes(Grafo* inicio_grafo, FILE* dados_adjacentes)
{
    Adjacente* novo_adj = NULL;
    Grafo* aux = inicio_grafo;
    int inserido = 0;
    char* vertice, * adjacente, * peso, linha[MAX_LINE_LEN];
    while (fgets(linha, MAX_LINE_LEN, dados_adjacentes))
    {
        inserido = 0;
        vertice = strtok(linha, ";");
        aux = inicio_grafo;
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
                            novo_adj->seguinte_adjacente = aux->adjacentes;
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
                                    novo_adj->seguinte_adjacente = NULL;
                                }
                                else 
                                {
                                    novo_adj->seguinte_adjacente = aux->adjacentes->seguinte_adjacente;
                                    aux->adjacentes->seguinte_adjacente = novo_adj;
                                }
                            }
                        }
                    }
                }
                aux = aux->seguinte_vertice;
                if (inserido == 1)
                    break;
            }
        }
    }
    return inicio_grafo;
}

void testeCLientes(Grafo* inicio_grafo)
{
    Grafo* aux = inicio_grafo;
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
        aux = aux->seguinte_vertice;
    }
}

Grafo* adicionarClientesGrafo(Grafo* inicio_grafo, Cliente* inicio_clientes)
{
    int teste = 0;
    Grafo* aux = inicio_grafo;
    while (aux != NULL)
    {
        teste = 0;
        Cliente* auxClientes = inicio_clientes;
        while (auxClientes != NULL)
        {
            if (strcmp(auxClientes->geocodigo, aux->vertice) == 0)
            {
                aux->clientes = auxClientes;
                teste = 1;
            }
            auxClientes = auxClientes->seguinte_cliente;
        }
        if (teste == 0)
        {
            aux->clientes = NULL;
        }
        aux = aux->seguinte_vertice;
    }
    return inicio_grafo->clientes;
}

Grafo* adicionarMeiosGrafo(Grafo* inicio_grafo, Meio* inicio_meios)
{
    Grafo* aux = inicio_grafo;
    while (aux!=NULL)
    {
        Meio* auxMeio = inicio_meios;
        while (auxMeio!=NULL)
        {
            if (strcmp(auxMeio->geocodigo, aux->vertice) == 0)
            {
                aux->meios = auxMeio;
            }
            auxMeio = auxMeio->seguinte_meio;
        }
        aux = aux->seguinte_vertice;
    }
    return inicio_grafo->meios;
}

ResFuncoes localizacaoRaio(Grafo* inicio_grafo, Cliente* inicio_clientes, float raio, int codigo)
{
    Grafo* aux = inicio_grafo;
    Cliente* auxClientes = inicio_clientes;
    char geocodigoProcurar[100];
    int print = 0;
    if (!existeClienteCod(auxClientes, codigo))
    {
        while (auxClientes->codigo != codigo)
            auxClientes = auxClientes->seguinte_cliente;
    }
    else
    {
        return CLIENTES_NAO_EXISTEM;
    }
    strcpy(geocodigoProcurar, auxClientes->geocodigo);
    while (strcmp(geocodigoProcurar, aux->vertice) != 0)
    {
        aux = aux->seguinte_vertice;
    }
    Adjacente* auxAdj = aux->adjacentes;
    while (auxAdj != NULL)
    {
        if (raio > auxAdj->peso)
        {
            printf("Pode ir para %s com uma distancia de %.2f\n", auxAdj->vertice, auxAdj->peso);
            print = 1;
        }
        auxAdj = auxAdj->seguinte_adjacente;
    }
    if (print == 0)
    {
        printf("Nao e possivel ir para nenhuma localizacao com a distancia definida.\n");
        return ERRO;
    }
    return SUCESSO;
}

void printtestgrafo(Grafo* inicio_grafo)
{
    Grafo* aux = inicio_grafo;
    while (aux->clientes != NULL)
    {
        printf("Cliente: %s \n", aux->clientes->nome);
        aux->clientes = aux->clientes->seguinte_cliente;
    }
    while (aux->meios != NULL)
    {
        printf("Meios: %s \n", aux->meios->tipo);
        aux->meios = aux->meios->seguinte_meio;
    }
}
void listarGrafo(Grafo* inicio_grafo)
{
    char aux[100];
    char continuar=0;
    printf("Localizacoes existentes:\n");
    while (inicio_grafo != NULL)
    {
        printf("->");
        strcpy(aux, inicio_grafo->vertice);
        int pos = strcspn(inicio_grafo->vertice, "\n");
        inicio_grafo->vertice[pos] = '\0';
        printf("%s\n", inicio_grafo->vertice);
        inicio_grafo = inicio_grafo->seguinte_vertice;
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

void listarAdjacentes(Grafo* inicio_grafo)
{
    char continuar = 0;
    while (inicio_grafo != NULL)
    {
        printf("Dados de %s:\n------------------------------------------------------------------------------------------------------------------------\n", inicio_grafo->vertice);
        printf("Esta localizacao pode ir para:\n");
        if (inicio_grafo->adjacentes == NULL)
        {
            printf("A localizacao %s nao tem destinos.\n", inicio_grafo->vertice);
        }
        while (inicio_grafo->adjacentes != NULL)
        {
            printf("%s com distancia de %.2f km; \n", inicio_grafo->adjacentes->vertice, inicio_grafo->adjacentes->peso);
            inicio_grafo->adjacentes = inicio_grafo->adjacentes->seguinte_adjacente;
        }
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        printf("\n");
        inicio_grafo = inicio_grafo->seguinte_vertice;
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

int existeVertice(Grafo* inicio_grafo, char verticeVerificar[50])
{
    Grafo* aux = inicio_grafo;
    while (aux != NULL)
    {
        if (strcmp(verticeVerificar, aux->vertice) == 0)
        {
            return 1;
        }
        aux = aux->seguinte_vertice;
    }
    return 0;
}

int inserirVertice(Grafo* inicio_grafo, char verticeInserir[50])
{
    while (inicio_grafo != NULL)
    {
        if (inicio_grafo->seguinte_vertice == NULL)
        {
            Grafo* novo_vertice = malloc(sizeof(Grafo));
            strcpy(novo_vertice->vertice, verticeInserir);
            novo_vertice->adjacentes = NULL;
            novo_vertice->meios = NULL;
            inicio_grafo->seguinte_vertice = novo_vertice;
            novo_vertice->seguinte_vertice = NULL;
            inicio_grafo = novo_vertice;
        }
        inicio_grafo = inicio_grafo->seguinte_vertice;
    }
    return inicio_grafo, 1;
}

void escreverFicheiroGrafo(Grafo* inicio_grafo, FILE* dados_grafo)
{
    Grafo* aux = inicio_grafo;
    if (inicio_grafo == NULL)
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
        aux = aux->seguinte_vertice;
        iterador++;
    }
    for (int i = iterador; i > 0; i--)
    {
        fprintf(dados_grafo, "%s;", listaCopiada[iterador-1]);
        iterador--;
    }
    fclose(dados_grafo);
}

int existeAdjacente(Grafo* inicio_grafo, char verticeFinal[50])
{
    Grafo* aux = inicio_grafo;
    while (aux != NULL)
    {
        if (strcmp(aux->adjacentes->vertice, verticeFinal) == 0)
        {
            return 1;
        }
        aux = aux->seguinte_vertice;
    }
    return 0;
}

int inserirAdjacente(Grafo* inicio_grafo, char verticeInicial[50], char verticeFinal[50], float peso)
{
    Grafo* aux = inicio_grafo;
    int existeVert = 0, existeAdj = 0;
    existeVert = existeVertice(aux, verticeInicial);
    existeAdj = existeAdjacente(aux, verticeFinal);
    if (existeVert)
    {
        while (!strcmp(aux->vertice, verticeInicial)==0)
            aux = aux->seguinte_vertice;
        if (!existeAdj)
        {
            Adjacente* novo_adj = malloc(sizeof(Adjacente));
            strcpy(novo_adj->vertice, verticeFinal);
            novo_adj->peso = peso;
            novo_adj->seguinte_adjacente = aux->adjacentes;
            aux->adjacentes = novo_adj;
            inicio_grafo = aux;
            return inicio_grafo,1;
        }
        else
        {
            return 2;
        }
    }
    return 0;
}

int totalVertices(Grafo* inicio_grafo)
{
    int total = 0;
    Grafo* aux = inicio_grafo;
    while (aux != NULL && aux->seguinte_vertice !=NULL)
    {
        aux = aux->seguinte_vertice;
        total++;
    }
    return total;
}

ListaStack* caminhoTexto(Grafo* inicio_grafo, char verticeAtual[50], char verticeDestino[50], Stack* inicio_stack, ListaStack* inicio_lista)
{
    Grafo* aux = inicio_grafo;
    Stack* aux_stack = inicio_stack;
    Adjacente* aux_adj = NULL;
    if (existeVertice(aux, verticeAtual))
    {
        while (aux != NULL)
        {
            if (strcmp(aux->vertice, verticeAtual) == 0)
            {
                aux_stack = push(aux_stack, aux->vertice);
                inicio_stack = aux_stack;
                break;
            }
            aux = aux->seguinte_vertice;
        }
    }
    else
        return;

    if (strcmp(aux->vertice, verticeDestino) == 0)
    {
        ListaStack* novaListaStack = malloc(sizeof(ListaStack));
        novaListaStack->novaStack = inicio_stack;
        novaListaStack->seguinte_lista = inicio_lista;
        inicio_lista = novaListaStack;
        mostrarCaminho(inicio_lista);
        return;
    }

    aux_adj = aux->adjacentes;
    while (aux_adj != NULL)
    {
        if (!verticeVisitado(inicio_stack, aux_adj->vertice))
        {
            Stack* novo_stack = NULL;
            Stack* aux_stack2 = inicio_stack;
            while (aux_stack2 != NULL)
            {
                novo_stack = push(novo_stack, aux_stack2->vertice);
                aux_stack2 = aux_stack2->seguinte_stack;
            }

            inicio_stack->visitado = true;
            caminhoTexto(inicio_grafo, aux_adj->vertice, verticeDestino, novo_stack, inicio_lista);
        }
        aux_adj = aux_adj->seguinte_adjacente;
    }
    return inicio_lista;
}

bool verticeVisitado(Stack* inicio_stack, char* vertice)
{
    Stack* aux_stack = inicio_stack;
    while (aux_stack != NULL)
    {
        if (strcmp(aux_stack->vertice, vertice) == 0)
        {
            return true;
        }
        aux_stack = aux_stack->seguinte_stack;
    }
    return false;
}
#pragma endregion

#pragma region STACK

Stack* push(Stack* inicio_stack, char vertice[50])
{
    Stack* aux = inicio_stack;
    if (inicio_stack == NULL)
    {
        Stack* novo_stack = malloc(sizeof(Stack));
        strcpy(novo_stack->vertice, vertice);
        novo_stack->visitado = true;
        novo_stack->seguinte_stack = inicio_stack;
        return novo_stack;
    }
    else
    {
        while (inicio_stack->seguinte_stack != NULL)
        {
            inicio_stack = inicio_stack->seguinte_stack;
        }
        Stack* novo_stack = malloc(sizeof(Stack));
        strcpy(novo_stack->vertice, vertice);
        novo_stack->seguinte_stack = NULL;
        inicio_stack->seguinte_stack = novo_stack;
    }
    return aux;  
}



void mostrarCaminho(ListaStack* inicio_lista) {
    if (inicio_lista == NULL)
    {
        printf("Caminho nao encontrado.\n");
        return;
    }

    ListaStack* aux_lista = inicio_lista;
    while (aux_lista != NULL)
    {
        Stack* aux_stack = aux_lista->novaStack;

        while (aux_stack != NULL)
        {
            printf("%s", aux_stack->vertice);
            if (aux_stack->seguinte_stack != NULL)
            {
                printf(" -> ");
            }
            aux_stack = aux_stack->seguinte_stack;
        }
        printf("\n");
        aux_lista = aux_lista->seguinte_lista;
    }
}
#pragma endregion

// ---------------------------------------------------FIM-LEITURA/ESCRITA/REPRESENTAÇÃO DE CIDADES----------------------------------------------------
