#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#define MAX_LINE_LEN 350
#define TAM 50

typedef struct registo_meios
{
	int codigo; // c�digo do meio de mobilidade el�trica
	char tipo[50];
	float bateria;
	float autonomia;
	char geocodigo[100];
	int custo;
	int ativo;
	struct registo_meio* seguinte_meio; // endere�o de mem�ria para uma struct registo_meio
} Meio;

typedef struct registo_clientes
{
	int codigo; // c�digo de cliente
	char nome[50]; // nome do cliente
	int NIF; // NIF do cliente
	int saldo; // saldo do cliente
	struct registo_aluguer* comprador;
	struct registo_clientes* seguinte_cliente; // endere�o de mem�ria para uma struct registo_clientes
} Cliente;

typedef struct registo_gestor
{
	int codigo; // Identifica��o do gestor
	char nome[50]; // nome do gestor
	char senha[20]; // Senha do gestor
	int encriptado; // Se a senha est� encriptada.
	char area_responsavel[50];
	struct registo_gestor* seguinte_gestor; // endere�o de mem�ria para uma struct registo_gestor
} Gestor;

typedef struct registo_aluguer
{
	char data_compra[50]; // Data de compra de um certo meio
	char nome_comprador[50]; // Nome do comprador.
	char nome_meio_comprado[50]; // Nome do meio.
	int cod_comprador; // Codigo do comprador.
	struct registo_aluguer* seguinte_compra;
}Aluguer;

typedef struct registo_transacoes
{
	int codigo_utilizador;
	char nome_transacao[50];
	int montante_carregado;
	char data_transacao[50];
	struct registo_transacoes* seguinte_transacao;
}Transacao;

typedef struct Meios
{
	int codigo;
	struct Meios* seguinte;
} Meios;

// Representa��o de um grafo orientado e pesado
typedef struct Adjacente
{
	char vertice[100]; // geoc�digo what3words
	float peso;
	struct Adjacente* seguinte;
} Adjacente;

typedef struct Grafo
{
	char vertice[100]; // geoc�digo what3words
	Adjacente* adjacentes;
	Meios* meios; // Lista ligada com os c�digos dos meios de transporte existente neste geoc�digo
	struct Grafo* seguinte_vertice;
} Grafo;

int menu();

int menu_utilizador();

int menu_gestor();

#pragma region MEIOS

// -------------------------------------------------FUN��ES_I-LEITURA/ESCRITA/REPRESENTA��O DE MEIOS-------------------------------------------------

Meio* lerFicheiro_meios(Meio* inicio, FILE* dados_meios);

void listarMeios(Meio* inicio_meios);

void listarGeocodigo(Meio* inicio_meios);

Meio* escreverFicheiro_meios(Meio* inicio_meios, FILE* dados_meios);

Meio* escreverFicheiro_meios_bin(Meio* inicio_meios, FILE* dados_meios);

Meio* existeMeio(Meio* inicio_meios, int cod);

Meio* bubbleSortMeios(Meio* inicio_meios);

float mediaAutonomia(Meio* inicio_meios);

// -------------------------------------------------FUN��ES_F-LEITURA/ESCRITA/REPRESENTA��O DE MEIOS-------------------------------------------------

#pragma endregion

#pragma region CLIENTES
// -------------------------------------------------FUN��ES_I-LEITURA/ESCRITA/REPRESENTA��O DE CLIENTES-------------------------------------------------

Cliente* lerFicheiro_clientes(Cliente* inicio_clientes, FILE* dados_clientes);

void listarClientes(Cliente* inicio_clientes);

Cliente* escreverFicheiro_clientes(Cliente* inicio_clientes, FILE* dados_clientes);

Cliente* escreverFicheiro_clientes_bin(Cliente* inicio_clientes, FILE* dados_clientes);

Cliente* carregarSaldo(Cliente* inicio_clientes, Transacao* inicio_transacao);

Cliente* consultaSaldo(Cliente* inicio_clientes);

Cliente* alterarDadosCliente(Cliente* inicio_clientes);

int existeClienteCod(Cliente* inicio_clientes, int cod);

int existeClienteNIF(Cliente* inicio_clientes, int NIF);

Cliente* bubbleSortClientes(Cliente* inicio_clientes);

// -------------------------------------------------FUN��ES_F-LEITURA/ESCRITA/REPRESENTA��O DE CLIENTES-------------------------------------------------
#pragma endregion

#pragma region GESTORES

// -------------------------------------------------FUN��ES_I-LEITURA/ESCRITA/REPRESENTA��O DE GESTORES-------------------------------------------------

Gestor* lerFicheiro_gestores(Gestor* inicio_gestor, FILE* dados_gestor);

void listarGestores(Gestor* inicio_gestor);

Gestor* escreverFicheiro_gestores(Gestor* inicio_gestor, FILE* dados_gestor);

Gestor* escreverFicheiro_gestores_bin(Gestor* inicio_gestor, FILE* dados_gestor);

int existeGestor(Gestor* inicio_gestor, int cod);

Gestor* bubbleSortGestores(Gestor* inicio_gestores);


// -------------------------------------------------FUN��ES_F-LEITURA/ESCRITA/REPRESENTA��O DE GESTORES-------------------------------------------------
#pragma endregion

#pragma region ADD/RMV/ALT
// ---------------------------------------------------FUN��ES_I-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------

Gestor* modoGestor(Gestor* inicio_gestores);

Meio* inserirMeio(Meio* inicio_meios, int cod, char nome[50], float bat, float aut, int custo, char geo[50]);

Cliente* inserirCliente(Cliente* inicio_clientes, int cod, char nome[50], int NIF, int saldo);

Gestor* inserirGestor(Gestor* inicio_gestor, int cod, char nome[50], char senha[50]);

Meio* removerMeio(Meio* inicio_meios, int cod);

Cliente* removerCliente(Cliente* inicio_clientes, int cod);

Gestor* removerGestor(Gestor* inicio_gestores, int cod);

Meio* alterarMeio(Meio* inicio_meios);

Gestor* alterarGestor(Gestor* inicio_gestores);

int encryptSenha(Gestor* inicio_gestor, char senha[50]);

int decryptSenha(Gestor* inicio_gestor, char senha[50]);
// ---------------------------------------------------FUN��ES_F-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------

#pragma endregion

#pragma region ALUGUER
// -------------------------------------------------------------------FUN��ES_I-ALUGUER--------------------------------------------------------------------

Aluguer* lerFicheiro_Aluguer(Aluguer* inicio_aluguer, FILE* dados_aluguer);

void listarAluguer(Aluguer* inicio_aluguer);

Aluguer* bubbleSortAluguer(Aluguer* inicio_aluguer);

Aluguer* escreverFicheiro_aluguer(Aluguer* inicio_aluguer, FILE* dados_aluguer);

Aluguer* escreverFicheiro_aluguer_bin(Aluguer* inicio_aluguer, FILE* dados_aluguer);

Aluguer* realizarAluguer(Cliente* inicio_clientes, Aluguer* inicio_aluguer, Meio* inicio_meios);

Aluguer* escreverAlug_test_bin(Aluguer* inicio_aluguer, FILE* dados_aluguer);

// -------------------------------------------------------------------FUN��ES_F-ALUGUER--------------------------------------------------------------------
#pragma endregion

#pragma region TRANSACOES
// -------------------------------------------------------------------FUN��ES_I-TRANSACOES--------------------------------------------------------------------

Transacao* lerFicheiro_transacao(Transacao* inicio_transacao, FILE* dados_transacao);

Transacao* escreverFicheiro_transacao(Transacao* inicio_transacao, FILE* dados_transacao);

Transacao* escreverFicheiro_transacao_bin(Transacao* inicio_transacao, FILE* dados_transacao);

void listarTransacao(Transacao* inicio_transacao);

// -------------------------------------------------------------------FUN��ES_F-TRANSACOES--------------------------------------------------------------------
#pragma endregion

// -------------------------------------------------------------------FUN��ES_I-CIDADES--------------------------------------------------------------------
Grafo* lerFicheiro_Vertices(Grafo* inicio_grafo, FILE* dados_vertices);

Grafo* lerFicheiro_Adjacentes(Grafo* inicio_grafo, FILE* dados_adjacentes);

int criar_Vertice(Grafo* inicio_grafo, char nome_vertice);

void listarGrafo(Grafo* inicio_grafo);

void listarAdjacentes(Grafo* inicio_grafo);
// -------------------------------------------------------------------FUN��ES_F-CIDADES--------------------------------------------------------------------
