#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


int main() {

    Meio* inicio_meios = NULL;
    Cliente* inicio_clientes = NULL;
    Gestor* inicio_gestor = NULL;
    FILE* dados_meios, * dados_clientes, * dados_gestor;


    int op ;

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
        case 4:
            dados_clientes = fopen("clientes.txt", "rt");
            escreverFicheiro_clientes(inicio_clientes, dados_clientes);
            escreverFicheiro_clientes_bin(inicio_clientes, dados_clientes);
        }
    } while (op != 0);

    //dados_meios = fopen("meios.txt", "rt");

    //inicio_meios = lerFicheiro_meios(inicio_meios, dados_meios);

    //escreverFicheiro_meios(inicio_meios, dados_meios);





    //dados_clientes = fopen("clientes.txt", "rt");

    //inicio_clientes = lerFicheiro_clientes(inicio_clientes, dados_clientes);

    //escreverFicheiro_clientes(inicio_clientes, dados_clientes);
    //escreverFicheiro_clientes_bin(inicio_clientes, dados_clientes);

    //listarMeios(inicio_meios);
    //listarClientes(inicio_clientes);
    //listarMeios(inicio_gestor);

    return 0;
}