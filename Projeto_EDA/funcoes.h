#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE_LEN 350

typedef struct registo_meios
{
	int codigo; // c�digo do meio de mobilidade el�trica
	char tipo[50];
	float bateria;
	float autonomia;
	char geocodigo[100];
	int custo;
	struct registo_meio* seguinte_meio; // endere�o de mem�ria para uma struct registo_meio
} Meio;

typedef struct registo_clientes
{
	int codigo; // c�digo de cliente
	char nome[50]; // nome do cliente
	int NIF; // NIF do cliente
	int saldo; // saldo do cliente

	struct registo_clientes* seguinte_cliente; // endere�o de mem�ria para uma struct registo_clientes
} Cliente;

typedef struct registo_gestor
{
	int codigo; // Identifica��o do gestor
	char nome[50]; // nome do gestor
	char senha[20]; // Senha do gestor
	struct registo_gestor* seguinte_gestor; // endere�o de mem�ria para uma struct registo_gestor
} Gestor;


int menu();

int menu_utilizador();

int menu_gestor();


// -------------------------------------------------FUN��ES_I-LEITURA/ESCRITA/REPRESENTA��O DE MEIOS-------------------------------------------------


Meio* lerFicheiro_meios(Meio* inicio, FILE* dados_meios);

void listarMeios(Meio* inicio_meios);

Meio* escreverFicheiro_meios(Meio* inicio_meios, FILE* dados_meios);

Meio* escreverFicheiro_meios_bin(Meio* inicio_meios, FILE* dados_meios);

Meio* existeMeio(Meio* inicio_meios, int cod);

Meio* bubbleSortMeios(Meio* inicio_meios);


// -------------------------------------------------FUN��ES_F-LEITURA/ESCRITA/REPRESENTA��O DE MEIOS-------------------------------------------------





// -------------------------------------------------FUN��ES_I-LEITURA/ESCRITA/REPRESENTA��O DE CLIENTES-------------------------------------------------

Cliente* lerFicheiro_clientes(Cliente* inicio_clientes, FILE* dados_clientes);

void listarClientes(Cliente* inicio_clientes);

Cliente* escreverFicheiro_clientes(Cliente* inicio_clientes, FILE* dados_clientes);

Cliente* escreverFicheiro_clientes_bin(Cliente* inicio_clientes, FILE* dados_clientes);

Cliente *carregarSaldo(Cliente* inicio_clientes);

Cliente *consultaSaldo(Cliente * inicio_clientes);

Cliente* alterarDadosCliente(Cliente* inicio_clientes);

int existeClienteCod(Cliente* inicio_clientes, int cod);

int existeClienteNIF(Cliente* inicio_clientes, int NIF);

Cliente* bubbleSortClientes(Cliente* inicio_clientes);


// -------------------------------------------------FUN��ES_F-LEITURA/ESCRITA/REPRESENTA��O DE CLIENTES-------------------------------------------------


// -------------------------------------------------FUN��ES_I-LEITURA/ESCRITA/REPRESENTA��O DE GESTORES-------------------------------------------------

Gestor* lerFicheiro_gestores(Gestor* inicio_gestor, FILE* dados_gestor);

void listarGestores(Gestor* inicio_gestor);

Gestor* escreverFicheiro_gestores(Gestor* inicio_gestor, FILE* dados_gestor);

Gestor* escreverFicheiro_gestores_bin(Gestor* inicio_gestor, FILE* dados_gestor);

int existeGestor(Gestor* inicio_gestor, int cod);

Gestor* bubbleSortGestores(Gestor* inicio_gestores);


// -------------------------------------------------FUN��ES_F-LEITURA/ESCRITA/REPRESENTA��O DE GESTORES-------------------------------------------------


// ---------------------------------------------------FUN��ES_I-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------

Gestor* modoGestor(Gestor* inicio_gestores);

Meio* inserirMeio(Meio* inicio_meios, int cod, char nome[50], float bat, float aut, int custo, char geo[50]);


Cliente* inserirCliente(Cliente* inicio_clientes, int cod, char nome[50], int NIF, int saldo);

Gestor* inserirGestor(Gestor* inicio_gestor, int cod, char nome[50], char senha[50]);

// ---------------------------------------------------FUN��ES_F-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------
