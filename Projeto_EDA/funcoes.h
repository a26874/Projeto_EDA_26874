#include <stdio.h>
#define MAX_LINE_LEN 256

typedef struct registo_meios
{
	int codigo; // código do meio de mobilidade elétrica
	char tipo[50];
	float bateria;
	float autonomia;
	char geocodigo[100];
	struct registo_meio* seguinte_meio; // endereço de memória para uma struct registo_meio
} Meio;

typedef struct registo_clientes
{
	int codigo; // código de cliente
	char nome[50]; // nome do cliente
	int NIF; // NIF do cliente
	int saldo; // saldo do cliente

	struct registo_clientes* seguinte_cliente; // endereço de memória para uma struct registo_clientes
} Cliente;

typedef struct registo_gestor
{
	int codigo; // Identificação do gestor
	char nome[50]; // nome do gestor
	char senha[20]; // Senha do gestor
	struct registo_gestor* seguinte_gestor; // endereço de memória para uma struct registo_gestor
} Gestor;


int menu();

// -------------------------------------------------FUNÇÕES_I-LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS-------------------------------------------------


Meio* lerFicheiro_meios(Meio* inicio, FILE* dados_meios);

void listarMeios(Meio* inicio_meios);

Meio* escreverFicheiro_meios(Meio* inicio_meios, FILE* dados_meios);

Meio* escreverFicheiro_meios_bin(Meio* inicio_meios, FILE* dados_meios);


// -------------------------------------------------FUNÇÕES_F-LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS-------------------------------------------------





// -------------------------------------------------FUNÇÕES_I-LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES-------------------------------------------------

Cliente* lerFicheiro_clientes(Cliente* inicio_clientes, FILE* dados_clientes);

void listarClientes(Cliente* inicio_clientes);

Cliente* escreverFicheiro_clientes(Cliente* inicio_clientes, FILE* dados_clientes);

Cliente* escreverFicheiro_clientes_bin(Cliente* inicio_clientes, FILE* dados_clientes);
// -------------------------------------------------FUNÇÕES_F-LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES-------------------------------------------------


// -------------------------------------------------FUNÇÕES_I-LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES-------------------------------------------------

Gestor* lerFicheiro_gestores(Gestor* inicio_gestor, FILE* dados_gestor);

void listarGestores(Gestor* inicio_gestor);

Gestor* escreverFicheiro_gestores(Gestor* inicio_gestor, FILE* dados_gestor);

Gestor* escreverFicheiro_gestores_bin(Gestor* inicio_gestor, FILE* dados_gestor);

// -------------------------------------------------FUNÇÕES_F-LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES-------------------------------------------------


// ---------------------------------------------------FUNÇÕES_I-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------

Gestor* modoGestor(Gestor* inicio_gestores);

Meio* inserirMeio(Meio* inicio_meios);



Cliente* inserirCliente(Cliente* inicio_clientes);

Gestor* inserirGestor(Gestor* inicio_gestor);

// ---------------------------------------------------FUNÇÕES_F-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------
