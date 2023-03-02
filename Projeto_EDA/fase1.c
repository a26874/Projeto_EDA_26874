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
    int op, bool, op_utilizador, utilizador_login = 0;

    // No arranque é feito imediato a leitura dos ficheiros.
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
        case 2:
            
            break;
        case 3:
            
            listarClientes(inicio_clientes);
            break;
        case 4:

            break;
        case 5:
           
            listarGestores(inicio_gestor);
            break;
        case 6:
            break;
        case 7:
            bool = modoGestor(inicio_gestor);
            if (bool != 1)
            {
                printf("Modo de gestor nao ativado.\n");
                break;
            }
            else
            {
                int escolha;
                printf("O que pretende fazer?\n");
                printf("1- Adicionar um novo meio.\n");
                printf("2- Adicionar um novo cliente.\n");
                printf("3- Adicionar um novo gestor.\n");
                printf("A sua escolha:");
                scanf("%d", &escolha);
                switch (escolha)
                {
                case 1:
                    inserirMeio(inicio_meios);
                    break;
                case 2:
                    inserirCliente(inicio_clientes);
                    break;
                case 3:
                    inserirGestor(inicio_gestor);
                    break;
                case 0:
                    break;
                }
            }
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