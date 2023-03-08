#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"


int main() {
    // Definição de variáveis.
    Meio* inicio_meios = NULL;
    Cliente* inicio_clientes = NULL;
    Gestor* inicio_gestor = NULL;
    Aluguer* inicio_aluguer = NULL;
    FILE* dados_meios, * dados_clientes, * dados_gestor, * dados_aluguer;
    int op, bool, op_utilizador, utilizador_login = 0, gestor_login = 0, op_gestor;
    int novo_cliente_codigo, novo_cliente_NIF, novo_cliente_saldo, novo_meio_codigo, novo_meio_custo, novo_gestor_codigo, codigo_meio_remover
        , codigo_cliente_remover, codigo_gestor_remover, codigo_login_utilizador;
    float novo_meio_bateria, novo_meio_autonomia;
    char novo_cliente_nome[50], novo_meio_nome[50], novo_meio_geocodigo[50], novo_gestor_nome[50], novo_gestor_senha[50], novo_gestor_area[50];


    // No arranque é feito de imediato a leitura dos ficheiros.
    dados_meios = fopen("meios.txt", "rt");
    inicio_meios = lerFicheiro_meios(inicio_meios, dados_meios);
    dados_clientes = fopen("clientes.txt", "rt");
    inicio_clientes = lerFicheiro_clientes(inicio_clientes, dados_clientes);
    dados_gestor = fopen("gestores.txt", "rt");
    inicio_gestor = lerFicheiro_gestores(inicio_gestor, dados_gestor);
    dados_aluguer = fopen("historico_compras.txt", "rt");
    inicio_aluguer = lerFicheiro_Aluguer(inicio_aluguer, dados_aluguer);
    bubbleSortMeios(inicio_meios);
    bubbleSortClientes(inicio_clientes);
    bubbleSortGestores(inicio_gestor);
    bubbleSortAluguer(inicio_aluguer);
    // Criação de Menu.
    do
    {
        op = menu();
        switch (op)
        {
        case 1:
            utilizador_login = 1;
            while (utilizador_login > 0)
            {
                op_utilizador = menu_utilizador();
                switch (op_utilizador) {
                case 1:
                    listarMeios(inicio_meios);
                    break;
                case 2:
                    carregarSaldo(inicio_clientes);
                    break;
                case 3:
                    consultaSaldo(inicio_clientes);
                    break;
                case 4:
                    alterarDadosCliente(inicio_clientes);
                    break;
                case 5:
                    listarMeios(inicio_meios);
                    if (inicio_aluguer == NULL)
                    {
                        inicio_aluguer = realizarAluguer(inicio_clientes, inicio_aluguer, inicio_meios);
                    }
                    else
                    {
                        realizarAluguer(inicio_clientes, inicio_aluguer, inicio_meios);
                    }
                    break;
                case 0:
                    utilizador_login = 0;
                    break;
                }
            }
                
            break;
        case 2:
            if (!modoGestor(inicio_gestor))
            {
                break;
            }
            else
            {
                gestor_login = 1;
                while (gestor_login > 0)
                {
                    op_gestor = menu_gestor();
                    switch (op_gestor)
                    {
                    case 1:
                        listarClientes(inicio_clientes);
                        break;
                    case 2:
                        listarGestores(inicio_gestor);
                        break;
                    case 3:
                        listarMeios(inicio_meios);
                        break;
                    case 4:
                        printf("Insira os novos dados de cliente:\n");
                        printf("Codigo:");
                        scanf("%d", &novo_cliente_codigo);
                        getchar();
                        printf("Nome:");
                        scanf("%[^\n]", novo_cliente_nome);
                        printf("NIF(Entre 192 e 193 com 9 digitos ex:192999999):");
                        scanf("%d", &novo_cliente_NIF);
                        if (novo_cliente_NIF <= 192000000 || novo_cliente_NIF >= 193000000)
                        {
                            printf("Tente de novo.\n");
                            break;
                        }
                        printf("Saldo:");
                        scanf("%d", &novo_cliente_saldo);
                        if (existeClienteCod(inicio_clientes, novo_cliente_codigo) == 1 && existeClienteNIF(inicio_clientes, novo_cliente_NIF) == 1)
                        {
                            inserirCliente(inicio_clientes, novo_cliente_codigo, novo_cliente_nome, novo_cliente_NIF, novo_cliente_saldo);
                            break;
                        }
                        else
                        {
                            printf("Ja existe alguem com o codigo %d.\n", novo_cliente_codigo);
                            printf("Ja existe alguem com o NIF %d.\n", novo_cliente_NIF);
                            break;
                        }
                    case 5:
                        printf("Insira os novos dados de um meio:\n");
                        printf("Codigo:");
                        scanf("%d", &novo_meio_codigo);
                        getchar();
                        printf("Nome Meio:");
                        scanf("%[^\n]", novo_meio_nome);
                        printf("Bateria(0.00 - 100.00):");
                        scanf("%f", &novo_meio_bateria);
                        printf("nivel:%f\n", novo_meio_bateria);
                        if (novo_meio_bateria <= 0.00 || novo_meio_bateria > 100.0001)
                        {
                            printf("Tente de novo.\n");
                            break;
                        }
                        printf("Autonomia(0.00 - 100.00):");
                        scanf("%f", &novo_meio_autonomia);
                        printf("nivel:%f\n", novo_meio_autonomia);
                        if (novo_meio_autonomia <= 0.00 || novo_meio_autonomia >= 100.0001)
                        {
                            printf("Tente de novo.\n");
                            break;
                        }
                        printf("Custo:");
                        scanf("%d", &novo_meio_custo);
                        getchar();
                        printf("Geocodigo:");
                        scanf("%[^\n]", novo_meio_geocodigo);
                        if (existeMeio(inicio_meios, novo_meio_codigo) == 1)
                        {
                            inserirMeio(inicio_meios, novo_meio_codigo, novo_meio_nome, novo_meio_bateria, novo_meio_autonomia, novo_meio_custo, novo_meio_geocodigo);
                            break;
                        }
                        else
                        {
                            printf("Ja existe um meio com o cod %d.\n", novo_meio_codigo);
                            break;
                        }
                        break;
                    case 6:
                        printf("Insira os dados de um novo gestor:\n");
                        printf("Codigo:");
                        scanf("%d", &novo_gestor_codigo);
                        getchar();
                        printf("Nome:");
                        scanf("%[^\n]", novo_gestor_nome);
                        getchar();
                        printf("Senha:");
                        scanf("%[^\n]", novo_gestor_senha);
                        getchar();
                        printf("Area:");
                        scanf("%[^\n]", novo_gestor_area);
                        if (existeGestor(inicio_gestor, novo_gestor_codigo) == 1)
                        {
                            inserirGestor(inicio_gestor, novo_gestor_codigo, novo_gestor_nome, novo_gestor_senha, novo_gestor_area);
                            break;
                        }
                        else
                        {
                            printf("Ja existe um gestor com o codigo %d", novo_gestor_codigo);
                            break;
                        }
                        break;
                    case 7:
                        printf("Insira o codigo de meio a remover:");
                        scanf("%d", &codigo_meio_remover);
                        if (existeMeio(inicio_meios, codigo_meio_remover) == 0)
                        {
                            removerMeio(inicio_meios, codigo_meio_remover);
                            break;
                        }
                        else
                        {
                            break;
                        }
                    case 8:
                        printf("Insira o codigo de cliente a remover:");
                        scanf("%d", &codigo_cliente_remover);
                        if (existeClienteCod(inicio_clientes, codigo_cliente_remover) == 0)
                        {
                            removerCliente(inicio_clientes, codigo_cliente_remover);
                            break;
                        }
                        else
                        {
                            break;
                        }
                    case 9:
                        printf("Insira o codigo de gestor a remover:");
                        scanf("%d", &codigo_gestor_remover);
                        if (existeGestor(inicio_gestor, codigo_gestor_remover) == 0)
                        {
                            removerGestor(inicio_gestor, codigo_gestor_remover);
                            break;
                        }
                        else
                        {
                            break;
                        }
                    case 10:
                        listarAluguer(inicio_aluguer);
                        break;
                    case 11:
                        alterarGestor(inicio_gestor);
                        break;
                    case 12:
                        alterarMeio(inicio_meios);
                        break;
                    case 0:
                        gestor_login = 0;
                        break;
                    }
                }
            }
            break;
        case 0:
            // No encerramento do programa é escrito tudo que foi adicionado/removido/alterado de novo para os seus respetivos ficheiros.
            dados_meios = fopen("meios.txt", "rt");
            escreverFicheiro_meios(inicio_meios, dados_meios);
            escreverFicheiro_meios_bin(inicio_meios, dados_meios);
            dados_clientes = fopen("clientes.txt", "rt");
            escreverFicheiro_clientes(inicio_clientes, dados_clientes);
            escreverFicheiro_clientes_bin(inicio_clientes, dados_clientes);
            dados_gestor = fopen("gestores.txt", "rt");
            escreverFicheiro_gestores(inicio_gestor, dados_gestor);
            escreverFicheiro_gestores_bin(inicio_gestor, dados_gestor);
            dados_aluguer = fopen("historico_compras.txt", "rt");
            escreverFicheiro_aluguer(inicio_aluguer, dados_aluguer);
            escreverFicheiro_aluguer_bin(inicio_aluguer, dados_aluguer);
            printf("O programa ira ser encerrado.\n");
            return 0;
        default:
            printf("Insira uma opcao.\n");
            break;
        }
    } while (op != 0);
}