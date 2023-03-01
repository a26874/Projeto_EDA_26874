#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


int main() {
    // Defini��o de vari�veis.
    Meio* inicio_meios = NULL;
    Cliente* inicio_clientes = NULL;
    Gestor* inicio_gestor = NULL;
    FILE* dados_meios, * dados_clientes, * dados_gestor;
    int op, bool;


    // Cria��o de Menu.
    do
    {
        op = menu();
        switch (op)
        {
        case 1:
            dados_meios = fopen("meios.txt", "rt");
            inicio_meios = lerFicheiro_meios(inicio_meios, dados_meios);
            listarMeios(inicio_meios);
            break;
        case 2:
            dados_meios = fopen("meios.txt", "rt");
            escreverFicheiro_meios(inicio_meios, dados_meios);
            escreverFicheiro_meios_bin(inicio_meios, dados_meios);
            break;
        case 3:
            dados_clientes = fopen("clientes.txt", "rt");
            inicio_clientes = lerFicheiro_clientes(inicio_clientes, dados_clientes);
            listarClientes(inicio_clientes);
            break;
        case 4:
            dados_clientes = fopen("clientes.txt", "rt");
            escreverFicheiro_clientes(inicio_clientes, dados_clientes);
            escreverFicheiro_clientes_bin(inicio_clientes, dados_clientes);
            break;
        case 5:
            dados_gestor = fopen("gestores.txt", "rt");
            inicio_gestor = lerFicheiro_gestores(inicio_gestor, dados_gestor);
            listarGestores(inicio_gestor);
            break;
        case 6:
            dados_gestor = fopen("gestores.txt", "rt");
            escreverFicheiro_gestores(inicio_gestor, dados_gestor);
            escreverFicheiro_gestores_bin(inicio_gestor, dados_gestor);
            break;
        case 7:
            bool = modoGestor();
            if (modoGestor != 1)
            {
                printf("Modo de gestor nao ativado.\n");
                return 0;
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
                case 2:
                    inserirCliente(inicio_clientes);
                case 3:
                    inserirGestor(inicio_gestor);
                case 0:
                    return 0;
                }
            }
        case 0:
            printf("O programa ira ser encerrado.\n");
            return 0;
        default:
            printf("Insira uma opcao.\n");
            break;
        }
    } while (op != 0);

    return 0;
}