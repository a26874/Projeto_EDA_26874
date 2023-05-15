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
    ListaStack* inicioLista = NULL;
    ListastackVolta* iniciolistaVolta = NULL;
    FILE* dadosMeios, * dadosClientes, * dadosGestor, * dadosAluguer, * dadosTransacao, * dadosGrafo, * dadosAdjacentes;
    int op, opUtilizador, utilizadorLogin = 0, gestorLogin = 0, opGestor, retFunc;
    int novoclienteCodigo, novoclienteNIF, novoclienteSaldo, novomeioCodigo, novomeioCusto, novogestorCodigo, codigomeioRemover
        , codigoclienteRemover, codigogestorRemover;
    float novomeioBateria, novomeioAutonomia, novopesoAdjacente;
    char novoclienteNome[50], novomeioNome[50], novomeioGeocodigo[50], novogestorNome[50], novogestorSenha[50], novogestorArea[50], novoverticeInicial[50], novoverticeFinal[50]
        , verticeInicial[50], verticeDestino[50], novoclienteGeocodigo[100];


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

    inicioGrafo->clientes = adicionarClientesGrafo(inicioGrafo, inicioClientes);
    inicioGrafo->meios = adicionarMeiosGrafo(inicioGrafo, inicioMeios);
    inicioGrafo->adjacentes = adicionarMeiosAdjacente(inicioGrafo, inicioMeios);
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
                    case SUCESSO:
                        printf("sucesso.\n");
                        break;
                    case clientesNaoExistem:
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
                    resFunc = consultaSaldo(inicioClientes);
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
                        Sleep(2000);
                        system("cls");
                        break;
                    }
                    break;
                case 4:
                    resFunc = alterarDadosCliente(inicioClientes,inicioTransacao);
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
                            //printf("Nao existem clientes registados.\n");
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
                    listarGeocodigo(inicioMeios);
                    break;
                case 7:
                    printf("Qual pretende saber:\n");
                    printf("1- Distancia de uma cidade a outra.\n");
                    int escolhaDist;
                    printf("A sua escolha:");
                    scanf("%d", &escolhaDist);
                    switch (escolhaDist)
                    {
                    case 1:
                        printf("Insira a partida e o destino:\n");
                        /*printf("Partida:");
                        scanf("%s", verticeInicial);
                        printf("Chegada:");
                        scanf("%s", verticeDestino);
                        */
                        strcpy(verticeInicial, "fagocitose.crestar.esperanca");
                        strcpy(verticeDestino, "reparou.definicao.artilheiro");
                        inicioLista = caminhoTexto(inicioGrafo, verticeInicial, verticeDestino, inicioStack, inicioLista);
                        //inicioLista = retirarStackMaior(inicioLista);

                        iniciolistaVolta = caminhoTexto(inicioGrafo, verticeDestino, verticeInicial, inicioStack, iniciolistaVolta);
                        mostrarCaminho(inicioLista);
                        mostrarCaminho(iniciolistaVolta);
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
                    localizacaoRaio(inicioGrafo,inicioClientes, raioVerificar, codigoCliente, tipoMeio);
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
                scanf("%d", &novogestorCodigo);
                getchar();
                printf("Nome:");
                scanf("%[^\n]", novogestorNome);
                getchar();
                printf("Senha:");
                scanf("%[^\n]", novogestorSenha);
                getchar();
                printf("Area:");
                scanf("%[^\n]", novogestorArea);
                if (existeGestor(inicioGestor, novogestorCodigo) == 1)
                {
                    inicioGestor = inserirGestor(inicioGestor, novogestorCodigo, novogestorNome, novogestorSenha, novogestorArea);
                    break;
                }
                else
                {
                    printf("Ja existe um gestor com o codigo %d", novogestorCodigo);
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
                        scanf("%d", &novoclienteCodigo);
                        getchar();
                        printf("Nome:");
                        scanf("%[^\n]", novoclienteNome);
                        printf("NIF(Entre 192 e 193 com 9 digitos ex:192999999):");
                        scanf("%d", &novoclienteNIF);
                        if (novoclienteNIF <= 192000000 || novoclienteNIF >= 193000000)
                        {
                            printf("Tente de novo.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        printf("Saldo:");
                        scanf("%d", &novoclienteSaldo);
                        printf("Localizacao:");
                        scanf("%s", novoclienteGeocodigo);
                        if (inicioClientes == NULL)
                        {
                            inicioClientes = inserirCliente(inicioClientes, novoclienteCodigo, novoclienteNome, novoclienteNIF, novoclienteSaldo, novoclienteGeocodigo);
                            break;
                        }
                        else if (existeClienteCod(inicioClientes, novoclienteCodigo) == 1 && existeClienteNIF(inicioClientes, novoclienteNIF) == 1)
                        {
                            inserirCliente(inicioClientes, novoclienteCodigo, novoclienteNome, novoclienteNIF, novoclienteSaldo, novoclienteGeocodigo);
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
                        scanf("%d", &novomeioCodigo);
                        getchar();
                        printf("Nome Meio:");
                        scanf("%[^\n]", novomeioNome);
                        printf("Bateria(0.00 - 100.00):");
                        scanf("%f", &novomeioBateria);
                        printf("nivel:%f\n", novomeioBateria);
                        if (novomeioBateria <= 0.00 || novomeioBateria > 100.0001)
                        {
                            printf("Tente de novo.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        printf("Autonomia(0.00 - 100.00):");
                        scanf("%f", &novomeioAutonomia);
                        printf("nivel:%f\n", novomeioAutonomia);
                        if (novomeioAutonomia <= 0.00 || novomeioAutonomia >= 100.0001)
                        {
                            printf("Tente de novo.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        printf("Custo:");
                        scanf("%d", &novomeioCusto);
                        getchar();
                        printf("Geocodigo:");
                        scanf("%[^\n]", novomeioGeocodigo);
                        if (inicioMeios == NULL)
                        {
                            inicioMeios = inserirMeio(inicioGrafo, inicioMeios, novomeioCodigo, novomeioNome, novomeioBateria, novomeioAutonomia, novomeioCusto, novomeioGeocodigo);
                            break;
                        }
                        if (existeMeio(inicioMeios, novomeioCodigo) == 1)
                        {
                            inserirMeio(inicioGrafo, inicioMeios, novomeioCodigo, novomeioNome, novomeioBateria, novomeioAutonomia, novomeioCusto, novomeioGeocodigo);
                            break;
                        }
                        else
                        {
                            printf("Ja existe um meio com o cod %d.\n", novomeioCodigo);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        break;
                    case 6:
                        printf("Insira os dados de um novo gestor:\n");
                        printf("Codigo:");
                        scanf("%d", &novogestorCodigo);
                        getchar();
                        printf("Nome:");
                        scanf("%[^\n]", novogestorNome);
                        getchar();
                        printf("Senha:");
                        scanf("%[^\n]", novogestorSenha);
                        getchar();
                        printf("Area:");
                        scanf("%[^\n]", novogestorArea);
                        if (existeGestor(inicioGestor, novogestorCodigo) == 1)
                        {
                            inserirGestor(inicioGestor, novogestorCodigo, novogestorNome, novogestorSenha, novogestorArea);
                            break;
                        }
                        else
                        {
                            printf("Ja existe um gestor com o codigo %d.\n", novogestorCodigo);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        break;
                    case 7:
                        printf("Insira o codigo de meio a remover:");
                        scanf("%d", &codigomeioRemover);
                        if (existeMeio(inicioMeios, codigomeioRemover) == 0)
                        {
                            inicioMeios = removerMeio(inicioMeios, codigomeioRemover);
                            break;
                        }
                        else
                        {
                            printf("O meio com cod %d nao existe.\n", codigomeioRemover);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                    case 8:
                        printf("Insira o codigo de cliente a remover:");
                        scanf("%d", &codigoclienteRemover);
                        if (existeClienteCod(inicioClientes, codigoclienteRemover) == 0)
                        {
                            inicioClientes = removerCliente(inicioClientes, codigoclienteRemover);
                            break;
                        }
                        else
                        {
                            printf("O cliente com cod %d nao existe.\n", codigoclienteRemover);
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                    case 9:
                        printf("Insira o codigo de gestor a remover:");
                        scanf("%d", &codigogestorRemover);
                        if (existeGestor(inicioGestor, codigogestorRemover) == 0)
                        {
                            inicioGestor = removerGestor(inicioGestor, codigogestorRemover);
                            gestorLogin = 0;
                            printf("Terminando sessao.\n");
                            Sleep(2000);
                            system("cls");
                            break;
                        }
                        else
                        {
                            printf("O gestor com cod %d nao existe.\n", codigogestorRemover);
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
                        alterarDadosCliente(inicioClientes,inicioTransacao);
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
                        scanf("%s", novoverticeInicial);
                        printf("Vertice Final:");
                        scanf("%s", novoverticeFinal);
                        printf("Distancia em km:");
                        scanf("%f", &novopesoAdjacente);
                        int resultado = inserirAdjacente(inicioGrafo, novoverticeInicial, novoverticeFinal, novopesoAdjacente);
                        if (resultado==1)
                        { 
                            printf("Adjacente de %s, adicionado com sucesso.\n", novoverticeInicial);
                            Sleep(2000);
                            system("cls");
                        }  
                        else if (resultado == 2)
                        {
                            printf("O Adjacente %s ja existe, no vertice %s.\n", novoverticeFinal, novoverticeInicial);
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
            printf("O programa ira ser encerrado.\n");
            return 0;
        default:
            printf("Insira uma opcao.\n");
            break;
        }
    } while (op != 0);
}