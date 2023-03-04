#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funcoes.h"


int main() {
    // Definição de variáveis.
    Meio* inicio_meios = NULL;
    Cliente* inicio_clientes = NULL;
    Gestor* inicio_gestor = NULL;
    FILE* dados_meios, * dados_clientes, * dados_gestor;
    int op, bool, op_utilizador, utilizador_login = 0, gestor_login = 0, op_gestor;
    int novo_cliente_codigo, novo_cliente_NIF, novo_cliente_saldo, novo_meio_codigo, novo_meio_custo, novo_gestor_codigo;
    float novo_meio_bateria, novo_meio_autonomia;
    char novo_cliente_nome[50], novo_meio_nome[50], novo_meio_geocodigo[50], novo_gestor_nome[50], novo_gestor_senha[50];


    // No arranque é feito de imediato a leitura dos ficheiros.
    dados_meios = fopen("meios.txt", "rt");
    inicio_meios = lerFicheiro_meios(inicio_meios, dados_meios);
    dados_clientes = fopen("clientes.txt", "rt");
    inicio_clientes = lerFicheiro_clientes(inicio_clientes, dados_clientes);
    dados_gestor = fopen("gestores.txt", "rt");
    inicio_gestor = lerFicheiro_gestores(inicio_gestor, dados_gestor);
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
                    bubbleSortMeios(inicio_meios);
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
                        bubbleSortClientes(inicio_clientes);
                        listarClientes(inicio_clientes);
                        break;
                    case 2:
                        bubbleSortGestores(inicio_gestor);
                        listarGestores(inicio_gestor);
                        break;
                    case 3:
                        bubbleSortMeios(inicio_meios);
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
                        if (novo_meio_bateria <= 0.00 || novo_meio_bateria > 100.0001)
                        {
                            printf("Tente de novo.\n");
                            break;
                        }
                        printf("Autonomia(0.00 - 100.00):");
                        scanf("%f", &novo_meio_autonomia);
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
                            break;
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
                        if (existeGestor(inicio_gestor, novo_gestor_codigo) == 1)
                        {
                            inserirGestor(inicio_gestor, novo_gestor_codigo, novo_gestor_nome, novo_gestor_senha);
                            break;
                        }
                        else
                        {
                            break;
                        }
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
            printf("O programa ira ser encerrado.\n");
            return 0;
        default:
            printf("Insira uma opcao.\n");
            break;
        }
    } while (op != 0);
}