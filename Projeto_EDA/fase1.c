/*****************************************************************//**
 * @file   fase1.c
 * @brief  Execucao
 *
 * @author Marco Macedo
 * @date   February 2023
 *********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include "funcoes.h"


int main() {
    // Definição de variáveis.
    Meio* inicioMeios = NULL;
    Cliente* inicioClientes = NULL;
    Gestor* inicioGestor = NULL;
    Aluguer* inicioAluguer = NULL;
    Transacao* inicioTransacao = NULL;
    Grafo* inicioGrafo = NULL;
    ResFuncoes resFunc;
    Stack* inicioStack = NULL;
    ListaStack* inicioLista;
    FILE* dadosMeios, * dadosClientes, * dadosGestor, * dadosAluguer, * dadosTransacao, * dadosGrafo, * dadosAdjacentes;
    int op, opUtilizador, utilizadorLogin = 0, gestorLogin = 0, opGestor, retFunc;
    int novoClienteCodigo, novoClienteNIF, novoClienteSaldo, novoMeioCodigo, novoMeioCusto, novoGestorCodigo, codigoMeioRemover
        , codigoClienteRemover, codigoGestorRemover, *saldo;
    float novoMeioBateria, novoMeioAutonomia, novoPesoAdjacente, tamanhoIda = 0, tamanhoVolta = 0, tamanhoTotal = 0;
    char novoClienteNome[50], novoMeioNome[50], novoMeioGeocodigo[50], novoGestorNome[50], novoGestorSenha[50], novoGestorArea[50], novoVerticeInicial[50], novoVerticeFinal[50]
        , verticeInicial[50], novoClienteGeocodigo[100], verticePartida[100];


    // No arranque é feito de imediato a leitura dos ficheiros.
    dadosMeios = fopen("meios.txt", "rt");
    inicioMeios = lerFicheiroMeios(inicioMeios, dadosMeios);
    dadosClientes = fopen("clientes.txt", "rt");
    inicioClientes = lerFicheiroClientes(inicioClientes, dadosClientes);
    dadosGestor = fopen("gestores.txt", "rt");
    inicioGestor = lerFicheiroGestores(inicioGestor, dadosGestor);
    dadosAluguer = fopen("historicoCompras.txt", "rt");
    inicioAluguer = lerFicheiroAluguer(inicioAluguer, dadosAluguer);
    dadosTransacao = fopen("historicoTransacoes.txt", "rt");
    inicioTransacao = lerFicheiroTransacao(inicioTransacao, dadosTransacao);
    dadosGrafo = fopen("vertices.txt", "rt");
    inicioGrafo = lerFicheiroVertices(inicioGrafo,inicioMeios, dadosGrafo);
    dadosAdjacentes = fopen("adjacentes.txt", "rt");
    inicioGrafo = lerFicheiroAdjacentes(inicioGrafo, dadosAdjacentes);
    bubbleSortMeios(inicioMeios);
    bubbleSortClientes(inicioClientes);
    bubbleSortGestores(inicioGestor);
    bubbleSortAluguer(inicioAluguer);
    recolhidoMeios(inicioMeios);

    inicioGrafo->clientes = adicionarClientesGrafo(inicioGrafo, inicioClientes);
    inicioGrafo->meios = adicionarMeiosGrafo(inicioGrafo, inicioMeios);
    inicioGrafo->adjacentes = adicionarMeiosAdjacente(inicioGrafo, inicioMeios);
    printf("\n");
    // Criação de Menu.
    do
    {
        op = menu();
        switch (op)
        {
        case 1:
            if (inicioClientes == NULL)
            {
                printf("Nao existem utilizadores, por favor registe-se.\n");
                break;
            }
            utilizadorLogin = 1;
            while (utilizadorLogin > 0)
            {
                opUtilizador = menuUtilizador();
                switch (opUtilizador) {
                case 1:
                    resFunc = listarMeios(inicioMeios);
                    switch (resFunc)
                    {
                    case meiosNaoExistem:
                        printf("Nao existem clientes.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    default:
                        break;
                    }
                    break;
                case 2:
                    if (inicioTransacao == NULL)
                    {
                        inicioTransacao = carregarSaldo(inicioClientes, inicioTransacao);
                        break;
                    }
                    retFunc = carregarSaldo(inicioClientes, inicioTransacao);
                    switch (retFunc)
                    {
                    case SUCESSO:
                        Sleep(2000);
                        system("cls");
                        break;
                    case codNifNaoExiste:
                        printf("Nao existe o cliente com o codigo/NIF inserido.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    case clientesNaoExistem:
                        printf("Nao existem clientes.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    case saldoCarrNegativo:
                        printf("Nao pode carregar saldo negativo.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    break;
                case 3:
                    resFunc = consultaSaldo(inicioClientes, &saldo);
                    switch (resFunc)
                    {
                    case clientesNaoExistem:
                        printf("Nao existem clientes.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    case codNifNaoExiste:
                        printf("Nao existe o cliente com o codigo/NIF inserido.\n");
                        Sleep(2000);
                        system("cls");
                        break;
                    case saldoAtual:
                        printf("Voce tem %d de saldo.\n", *saldo);
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    break;
                case 4:
                    resFunc = alterarDadosCliente(inicioClientes,inicioTransacao, inicioAluguer);
                    switch (resFunc)
                    {
                        case SUCESSO:
                            break;
                        case codClienteNaoExiste:
                        {
                            printf("Nao existe nenhum cliente registado com o cod inserido.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        case nifClienteNaoExiste:
                        {
                            printf("O codigo inserido, nao esta registado com o NIF inserido.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        case clientesNaoExistem:
                        {
                            printf("Nao existem clientes.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                    }
                    break;
                case 5:
                    resFunc = listarMeios(inicioMeios);
                    switch (resFunc)
                    {
                    case clientesNaoExistem:
                        printf("Nao existem meios para alugar.\n");
                        break;
                    }
                    if (inicioAluguer == NULL)
                    {
                        inicioAluguer = realizarAluguer(inicioClientes, inicioAluguer, inicioMeios);
                    }
                    else
                    {
                        realizarAluguer(inicioClientes, inicioAluguer, inicioMeios);
                    }
                    break;
                case 6:
                    resFunc = listarGeocodigo(inicioMeios);
                    switch (resFunc)
                    {
                        case meiosNaoExistem:
                        {
                            printf("Nao existem meios para listar.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        case geocodigoNaoExiste:
                        {
                            printf("Nao existe o geocodigo inserido.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        case SUCESSO:
                            break;
                    }
                    break;
                case 7:
                    printf("Qual pretende saber:\n");
                    printf("1- Ciclo de um vertice inicial e caminho de volta.\n");
                    int escolhaDist;
                    printf("A sua escolha:");
                    scanf("%d", &escolhaDist);
                    switch (escolhaDist)
                    {
                    case 1:
                        printf("Insira a partida:\n");
                        scanf("%s", verticePartida);
                        inicioLista = NULL;
                        inicioLista = mostrarCaminhoIda(inicioGrafo, verticePartida, inicioStack, inicioLista,tamanhoIda);
                        if (inicioLista == NULL)
                        {
                            printf("Nao existe caminho/Ponto Partida.\n");
                            break;
                        }
                        inicioLista = retirarStackMaior(inicioLista);
                        printf("Caminho de ida: ");
                        mostrarCaminho(inicioLista);
                        tamanhoTotal = inicioLista->tamanho;
                        obterUltimoVertice(inicioLista, verticeInicial);

                        printf("\nCaminho de volta: ");
                        inicioLista = mostrarCaminhoVolta(inicioGrafo, verticeInicial, verticePartida, inicioStack, inicioLista, tamanhoVolta);
                        inicioLista = retirarStackMaior(inicioLista);
                        mostrarCaminho(inicioLista);
                        tamanhoTotal += inicioLista->tamanho;

                        printf("\nKm's percorridos:%.2f\n", tamanhoTotal);
                        free(inicioLista);
                        break;
                    }
                    break;
                case 8:
                    listarAdjacentes(inicioGrafo);
                    break;
                case 9:
                    printf("Introduza em km's, a distancia pela qual pretende verificar a existencia de meios:");
                    float raioVerificar;
                    int codigoCliente;
                    char tipoMeio[20];
                    scanf("%f", &raioVerificar);
                    printf("Introduza o seu codigo:");
                    scanf("%d", &codigoCliente);
                    printf("Introduza o nome do meio a procurar:");
                    scanf("%s", tipoMeio);
                    resFunc = localizacaoRaio(inicioGrafo,inicioClientes, raioVerificar, codigoCliente, tipoMeio);
                    {
                        switch(resFunc)
                        {
                            case clientesNaoExistem:
                            {
                                printf("Nao existem clientes.\n");
                                Sleep(2000);
                                system("cls");
                                break;
                            }
                            case SUCESSO:
                                Sleep(2000);
                                system("cls");
                                break;
                            case ERRO:
                            {
                                printf("Nao e possivel ir para nenhuma localizacao com a distancia definida.\n");
                                Sleep(2000);
                                system("cls");
                                break;
                            }
                        }
                    }
                case 0:
                    utilizadorLogin = 0;
                    break;
                }
            }

            break;
        case 2:
            if (inicioGestor == NULL)
            {
                printf("Insira os dados de um novo gestor:\n");
                printf("Codigo:");
                scanf("%d", &novoGestorCodigo);
                getchar();
                printf("Nome:");
                scanf("%[^\n]", novoGestorNome);
                getchar();
                printf("Senha:");
                scanf("%[^\n]", novoGestorSenha);
                getchar();
                printf("Area:");
                scanf("%[^\n]", novoGestorArea);
                if (existeGestor(inicioGestor, novoGestorCodigo) == 1)
                {
                    inicioGestor = inserirGestor(inicioGestor, novoGestorCodigo, novoGestorNome, novoGestorSenha, novoGestorArea);
                    break;
                }
                else
                {
                    printf("Ja existe um gestor com o codigo %d", novoGestorCodigo);
                    break;
                }
                break;
            }
            else if (!modoGestor(inicioGestor))
            {
                break;
            }
            else
            {
                gestorLogin = 1;
                while (gestorLogin > 0)
                {
                    opGestor = menuGestor();
                    switch (opGestor)
                    {
                    case 1:
                        listarClientes(inicioClientes);
                        break;
                    case 2:
                        listarGestores(inicioGestor);
                        break;
                    case 3:
                        listarMeios(inicioMeios);
                        break;
                    case 4:
                        printf("Insira os novos dados de cliente:\n");
                        printf("Codigo:");
                        scanf("%d", &novoClienteCodigo);
                        getchar();
                        printf("Nome:");
                        scanf("%[^\n]", novoClienteNome);
                        printf("NIF(Entre 192 e 193 com 9 digitos ex:192999999):");
                        scanf("%d", &novoClienteNIF);
                        if (novoClienteNIF <= 192000000 || novoClienteNIF >= 193000000)
                        {
                            printf("Tente de novo.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        printf("Saldo:");
                        scanf("%d", &novoClienteSaldo);
                        printf("Localizacao:");
                        scanf("%s", novoClienteGeocodigo);
                        if (inicioClientes == NULL)
                        {
                            inicioClientes = inserirCliente(inicioClientes, novoClienteCodigo, novoClienteNome, novoClienteNIF, novoClienteSaldo, novoClienteGeocodigo);
                            break;
                        }
                        else if (existeClienteCod(inicioClientes, novoClienteCodigo) == 1 && existeClienteNIF(inicioClientes, novoClienteNIF) == 1)
                        {
                            inserirCliente(inicioClientes, novoClienteCodigo, novoClienteNome, novoClienteNIF, novoClienteSaldo, novoClienteGeocodigo);
                            break;
                        }
                        else
                        {
                            printf("Ja existe algum cliente com os dados inseridos.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                    case 5:
                        printf("Insira os novos dados de um meio:\n");
                        printf("Codigo:");
                        scanf("%d", &novoMeioCodigo);
                        getchar();
                        printf("Nome Meio:");
                        scanf("%[^\n]", novoMeioNome);
                        printf("Bateria(0.00 - 100.00):");
                        scanf("%f", &novoMeioBateria);
                        printf("nivel:%f\n", novoMeioBateria);
                        if (novoMeioBateria <= 0.00 || novoMeioBateria > 100.0001)
                        {
                            printf("Tente de novo.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        printf("Autonomia(0.00 - 100.00):");
                        scanf("%f", &novoMeioAutonomia);
                        printf("nivel:%f\n", novoMeioAutonomia);
                        if (novoMeioAutonomia <= 0.00 || novoMeioAutonomia >= 100.0001)
                        {
                            printf("Tente de novo.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        printf("Custo:");
                        scanf("%d", &novoMeioCusto);
                        getchar();
                        printf("Geocodigo:");
                        scanf("%[^\n]", novoMeioGeocodigo);
                        if (inicioMeios == NULL)
                        {
                            inicioMeios = inserirMeio(inicioGrafo, inicioMeios, novoMeioCodigo, novoMeioNome, novoMeioBateria, novoMeioAutonomia, novoMeioCusto, novoMeioGeocodigo);
                            break;
                        }
                        if (existeMeio(inicioMeios, novoMeioCodigo) == 1)
                        {
                            inserirMeio(inicioGrafo, inicioMeios, novoMeioCodigo, novoMeioNome, novoMeioBateria, novoMeioAutonomia, novoMeioCusto, novoMeioGeocodigo);
                            break;
                        }
                        else
                        {
                            printf("Ja existe um meio com o cod %d.\n", novoMeioCodigo);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        break;
                    case 6:
                        printf("Insira os dados de um novo gestor:\n");
                        printf("Codigo:");
                        scanf("%d", &novoGestorCodigo);
                        getchar();
                        printf("Nome:");
                        scanf("%[^\n]", novoGestorNome);
                        getchar();
                        printf("Senha:");
                        scanf("%[^\n]", novoGestorSenha);
                        getchar();
                        printf("Area:");
                        scanf("%[^\n]", novoGestorArea);
                        if (existeGestor(inicioGestor, novoGestorCodigo) == 1)
                        {
                            inserirGestor(inicioGestor, novoGestorCodigo, novoGestorNome, novoGestorSenha, novoGestorArea);
                            break;
                        }
                        else
                        {
                            printf("Ja existe um gestor com o codigo %d.\n", novoGestorCodigo);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        break;
                    case 7:
                        printf("Insira o codigo de meio a remover:");
                        scanf("%d", &codigoMeioRemover);
                        if (existeMeio(inicioMeios, codigoMeioRemover) == 0)
                        {
                            inicioMeios = removerMeio(inicioMeios, codigoMeioRemover);
                            break;
                        }
                        else
                        {
                            printf("O meio com cod %d nao existe.\n", codigoMeioRemover);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                    case 8:
                        printf("Insira o codigo de cliente a remover:");
                        scanf("%d", &codigoClienteRemover);
                        if (existeClienteCod(inicioClientes, codigoClienteRemover) == 0)
                        {
                            inicioClientes = removerCliente(inicioClientes, codigoClienteRemover);
                            break;
                        }
                        else
                        {
                            printf("O cliente com cod %d nao existe.\n", codigoClienteRemover);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                    case 9:
                        printf("Insira o codigo de gestor a remover:");
                        scanf("%d", &codigoGestorRemover);
                        if (existeGestor(inicioGestor, codigoGestorRemover) == 0)
                        {
                            inicioGestor = removerGestor(inicioGestor, codigoGestorRemover);
                            gestorLogin = 0;
                            printf("Terminando sessao.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        else
                        {
                            printf("O gestor com cod %d nao existe.\n", codigoGestorRemover);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                    case 10:
                        listarAluguer(inicioAluguer);
                        break;
                    case 11:
                        alterarGestor(inicioGestor);
                        break;
                    case 12:
                        alterarMeio(inicioMeios);
                        break;
                    case 13:
                        alterarDadosCliente(inicioClientes,inicioTransacao, inicioAluguer);
                        break;
                    case 14:
                        mediaAutonomia(inicioMeios);
                        break;
                    case 15:
                        listarTransacao(inicioTransacao);
                        break;
                    case 16:
                        printf("Insira os seguintes dados: Vertice inicial, vertice final e distancia em km.\n");
                        printf("Vertice inicial:");
                        scanf("%s", novoVerticeInicial);
                        printf("Vertice Final:");
                        scanf("%s", novoVerticeFinal);
                        printf("Distancia em km:");
                        scanf("%f", &novoPesoAdjacente);
                        resFunc = inserirAdjacente(inicioGrafo, novoVerticeInicial, novoVerticeFinal, novoPesoAdjacente);
                        if (resFunc==adjacenteInserido)
                        { 
                            printf("Adjacente de %s com o nome %s, adicionado com sucesso.\n", novoVerticeInicial, novoVerticeFinal);
                            Sleep(2000);
                            system("cls");
                        }  
                        else if (resFunc == adjacenteExiste)
                        {
                            printf("O Adjacente %s ja existe, no vertice %s.\n", novoVerticeFinal, novoVerticeInicial);
                            Sleep(2000);
                            system("cls");
                        }
                        break;
                    case 17:
                        printf("Nome do vertice que deseja inserir:");
                        scanf("%s", novoVerticeInicial);
                        resFunc = inserirVertice(inicioGrafo, novoVerticeInicial);
                        if (resFunc == verticeExiste)
                        {
                            printf("Ja existe o vertice inserido.\n");
                            Sleep(2000);
                            system("cls");
                        }
                        break;
                    case 0:
                        gestorLogin = 0;
                        system("cls");
                        break;
                    default:
                        getchar();
                        printf("\nInsira uma das opcoes mostradas.\n");
                        break;
                    }
                }
            }
            break;
        case 0:
            // No encerramento do programa é escrito tudo que foi adicionado/removido/alterado de novo para os seus respetivos ficheiros.
            dadosMeios = fopen("meios.txt", "rt");
            escreverFicheiroMeios(inicioMeios, dadosMeios);
            escreverFicheiroMeiosBin(inicioMeios, dadosMeios);
            dadosClientes = fopen("clientes.txt", "rt");
            escreverFicheiroClientes(inicioClientes, dadosClientes);
            escreverFicheiroClientesBin(inicioClientes, dadosClientes);
            dadosGestor = fopen("gestores.txt", "rt");
            escreverFicheiroGestores(inicioGestor, dadosGestor);
            escreverFicheiroGestoresBin(inicioGestor, dadosGestor);
            dadosAluguer = fopen("historicoCompras.txt", "rt");
            escreverFicheiroAluguer(inicioAluguer, dadosAluguer);
            escreverFicheiroAluguerBin(inicioAluguer, dadosAluguer);
            dadosTransacao = fopen("historicoTransacoes.txt", "rt");
            escreverFicheiroTransacao(inicioTransacao, dadosTransacao);
            escreverFicheiroTransacaoBin(inicioTransacao, dadosTransacao);
            dadosGrafo = fopen("vertices.txt", "rt");
            escreverFicheiroGrafo(inicioGrafo, dadosGrafo);
            escreverFicheiroGrafoBin(inicioGrafo, dadosGrafo);
            dadosAdjacentes = fopen("adjacentes.txt", "rt");
            escreverFicheiroAdjacentes(inicioGrafo, dadosAdjacentes);
            dadosAdjacentes = fopen("adjacentes.txt", "rt");
            escreverFicheiroAdjacentesBin(inicioGrafo, dadosAdjacentes);
            printf("O programa ira ser encerrado.\n");
            return 0;
        default:
            printf("Insira uma opcao.\n");
            break;
        }
    } while (op != 0);
}