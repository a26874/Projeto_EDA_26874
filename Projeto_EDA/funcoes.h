/*****************************************************************
 * @file   funcoes.h
 * @brief  Listagem Funcoes
 *
 * @author Marco Macedo
 * @date   February 2023
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <float.h>
#include <stdbool.h>
#define tamanhoLinha 350

typedef enum ResultadoFuncoes {
	ERRO,
	SUCESSO,
	clientesNaoExistem,
	codClienteNaoExiste,
	nifClienteNaoExiste,
	codNifNaoExiste,
	existeCodCliente,
	saldoCarrNegativo,
	saldoCarregado,
	saldoAtual,
	meiosNaoExistem,
	verticeNaoExiste,
	adjacenteNaoExiste,
	semEspacoMem,
	verticeExiste,
	adjacenteInserido,
	adjacenteExiste,
	geocodigoNaoExiste,

}ResFuncoes;

typedef struct Meio
{
	int codigo; // código do meio de mobilidade elétrica
	char tipo[50];
	float bateria;
	float autonomia;
	char geocodigo[100];
	int custo;
	int ativo;
	int recolhido;
	struct Meio* seguinteMeio; // endereço de memória para uma struct registoMeio
} Meio;

typedef struct Cliente
{
	int codigo; // código de cliente
	char nome[50]; // nome do cliente
	int NIF; // NIF do cliente
	int saldo; // saldo do cliente
	char geocodigo[100];
	struct Aluguer* comprador;
	struct Cliente* seguinteCliente; // endereço de memória para uma struct registoClientes
} Cliente;

typedef struct Gestor
{
	int codigo; // Identificação do gestor
	char nome[50]; // nome do gestor
	char senha[20]; // Senha do gestor
	int encriptado; // Se a senha está encriptada.
	char areaResponsavel[50];
	struct Gestor* seguinteGestor; // endereço de memória para uma struct registoGestor
} Gestor;

typedef struct Aluguer
{
	char dataCompra[50]; // Data de compra de um certo meio
	char nomeComprador[50]; // Nome do comprador.
	char nomeMeioComprado[50]; // Nome do meio.
	int codComprador; // Codigo do comprador.
	struct Aluguer* seguinteCompra;
}Aluguer;

typedef struct Transacao
{
	int codigoUtilizador;
	char nomeTransacao[50];
	int montanteCarregado;
	char dataTransacao[50];
	struct Transacao* seguinteTransacao;
}Transacao;

typedef struct Adjacente
{
	char vertice[100]; // geocódigo what3words
	float peso;
	Meio* meios;
	struct Adjacente* seguinteAdjacente;
} Adjacente;

typedef struct Grafo
{
	char vertice[100]; // geocódigo what3words
	Adjacente* adjacentes;
	Cliente* clientes;
	Meio* meios; // Lista ligada com os códigos dos meios de transporte existente neste geocódigo
	struct Grafo* seguinteVertice;
} Grafo;

#pragma region STACK

typedef struct Stack
{
	char vertice[100];
	bool visitado;
	float dist;
	struct Stack* seguinteStack;
}Stack;

typedef struct ListaStack
{
	Stack* novaStack;
	float tamanho;
	struct ListaStack* seguinteLista;
} ListaStack;

#pragma endregion

int menu();

int menuUtilizador();

int menuGestor();

#pragma region MEIOS

// -------------------------------------------------FUNÇÕES_I-LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS-------------------------------------------------

Meio* lerFicheiroMeios(Meio* inicioMeios, FILE* dadosMeios);

ResFuncoes listarMeios(Meio* inicioMeios);

int listarGeocodigo(Meio* inicioMeios);

Meio* escreverFicheiroMeios(Meio* inicioMeios, FILE* dadosMeios);

Meio* escreverFicheiroMeiosBin(Meio* inicioMeios, FILE* dadosMeios);

Meio* existeMeio(Meio* inicioMeios, int cod);

Meio* bubbleSortMeios(Meio* inicioMeios);

float mediaAutonomia(Meio* inicioMeios);

void recolhidoMeios(Meio* inicioMeios);

// -------------------------------------------------FUNÇÕES_F-LEITURA/ESCRITA/REPRESENTAÇÃO DE MEIOS-------------------------------------------------

#pragma endregion

#pragma region CLIENTES
// -------------------------------------------------FUNÇÕES_I-LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES-------------------------------------------------

Cliente* lerFicheiroClientes(Cliente* inicioClientes, FILE* dadosClientes);

void listarClientes(Cliente* inicioClientes);

Cliente* escreverFicheiroClientes(Cliente* inicioClientes, FILE* dadosClientes);

Cliente* escreverFicheiroClientesBin(Cliente* inicioClientes, FILE* dadosClientes);

Cliente* carregarSaldo(Cliente* inicioClientes, Transacao* inicioTransacao);

ResFuncoes consultaSaldo(Cliente* inicioClientes, int** saldo);

ResFuncoes alterarDadosCliente(Cliente* inicioClientes,Transacao* inicioTransacao, Aluguer* inicioAluguer);

int existeClienteCod(Cliente* inicioClientes, int cod);

int existeClienteNIF(Cliente* inicioClientes, int NIF);

Cliente* bubbleSortClientes(Cliente* inicioClientes);

// -------------------------------------------------FUNÇÕES_F-LEITURA/ESCRITA/REPRESENTAÇÃO DE CLIENTES-------------------------------------------------
#pragma endregion

#pragma region GESTORES

// -------------------------------------------------FUNÇÕES_I-LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES-------------------------------------------------

Gestor* lerFicheiroGestores(Gestor* inicioGestor, FILE* dadosGestor);

void listarGestores(Gestor* inicioGestor);

Gestor* escreverFicheiroGestores(Gestor* inicioGestor, FILE* dadosGestor);

Gestor* escreverFicheiroGestoresBin(Gestor* inicioGestor, FILE* dadosGestor);

int existeGestor(Gestor* inicioGestor, int cod);

Gestor* bubbleSortGestores(Gestor* inicioGestor);


// -------------------------------------------------FUNÇÕES_F-LEITURA/ESCRITA/REPRESENTAÇÃO DE GESTORES-------------------------------------------------
#pragma endregion

#pragma region ADD/RMV/ALT
// ---------------------------------------------------FUNÇÕES_I-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------

Gestor* modoGestor(Gestor* inicioGestor);

void printtestgrafo(Grafo* inicioGrafo);

Meio* inserirMeio(Grafo* inicioGrafo, Meio* inicioMeios, int cod, char nome[], float bat, float aut, int custo, char geo[]);

Cliente* inserirCliente(Cliente* inicioClientes, int cod, char nome[], int NIF, int saldo, char geocodigo[]);

Gestor* inserirGestor(Gestor* inicioGestor, int cod, char nome[], char senha[], char area[]);

Meio* removerMeio(Meio* inicioMeios, int cod);

Cliente* removerCliente(Cliente* inicioClientes, int cod);

Gestor* removerGestor(Gestor* inicioGestor, int cod);

Meio* alterarMeio(Meio* inicioMeios);

Gestor* alterarGestor(Gestor* inicioGestor);

int encryptSenha(Gestor* inicioGestor, char senha[]);

int decryptSenha(Gestor* inicioGestor, char senha[]);
// ---------------------------------------------------FUNÇÕES_F-ADICIONAR/REMOVER/ALTERAR MEIOS/CLIENTES/GESTORES----------------------------------------------------

#pragma endregion

#pragma region ALUGUER
// -------------------------------------------------------------------FUNÇÕES_I-ALUGUER--------------------------------------------------------------------

Aluguer* lerFicheiroAluguer(Aluguer* inicioAluguer, FILE* dadosAluguer);

void listarAluguer(Aluguer* inicioAluguer);

Aluguer* bubbleSortAluguer(Aluguer* inicioAluguer);

Aluguer* escreverFicheiroAluguer(Aluguer* inicioAluguer, FILE* dadosAluguer);

Aluguer* escreverFicheiroAluguerBin(Aluguer* inicioAluguer, FILE* dadosAluguer);

Aluguer* realizarAluguer(Cliente* inicioClientes, Aluguer* inicioAluguer, Meio* inicioMeios);



// -------------------------------------------------------------------FUNÇÕES_F-ALUGUER--------------------------------------------------------------------
#pragma endregion

#pragma region TRANSACOES
// -------------------------------------------------------------------FUNÇÕES_I-TRANSACOES--------------------------------------------------------------------

Transacao* lerFicheiroTransacao(Transacao* inicioTransacao, FILE* dadosTransacao);

Transacao* escreverFicheiroTransacao(Transacao* inicioTransacao, FILE* dadosTransacao);

Transacao* escreverFicheiroTransacaoBin(Transacao* inicioTransacao, FILE* dadosTransacao);

void listarTransacao(Transacao* inicioTransacao);

int existeClienteTransacao(Transacao* inicioTransacao, int codVerificar);

Transacao* criarTransacao(Transacao* inicioTransacao, int codigoCliente, int saldoCarregar, char nomeCliente[]);


// -------------------------------------------------------------------FUNÇÕES_F-TRANSACOES--------------------------------------------------------------------
#pragma endregion

#pragma region GRAFO
// -------------------------------------------------------------------FUNÇÕES_I-CIDADES--------------------------------------------------------------------
Grafo* lerFicheiroVertices(Grafo* inicioGrafo, Meio* inicioMeios, FILE* dadosVertices);

Grafo* lerFicheiroAdjacentes(Grafo* inicioGrafo, FILE* dadosAdjacentes);

void escreverFicheiroGrafo(Grafo* inicioGrafo, FILE* dadosGrafo);

void escreverFicheiroGrafoBin(Grafo* inicioGrafo, FILE* dadosGrafo);

void escreverFicheiroAdjacentes(Grafo* inicioGrafo, FILE* dadosAdjacentes);

void escreverFicheiroAdjacentesBin(Grafo* inicioGrafo, FILE* dadosAdjacentes);

Adjacente* adicionarMeiosAdjacente(Grafo* inicioGrafo, Meio* inicioMeios);

Grafo* adicionarMeiosGrafo(Grafo* inicioGrafo, Meio* inicioMeios);

Grafo* adicionarClientesGrafo(Grafo* inicioGrafo, Cliente* inicioClientes);

void printtestgrafo(Grafo* inicioGrafo);

ResFuncoes localizacaoRaio(Grafo* inicioGrafo,Cliente* inicio_cliente, float raio, int codigo, char tipoMeio[]);

int existeVertice(Grafo* inicioGrafo, char verticeVerificar[]);

int inserirVertice(Grafo* inicioGrafo, char verticeInserir[]);

int inserirAdjacente(Grafo* inicioGrafo, char verticeInicial[], char verticeFinal[], float peso);

void listarGrafo(Grafo* inicioGrafo);

int totalVertices(Grafo* inicioGrafo);

void listarAdjacentes(Grafo* inicioGrafo);

ListaStack* mostrarCaminhoIda(Grafo* inicioGrafo, char verticeAtual[], Stack* inicioStack, ListaStack* inicioLista, float Tamanho);

ListaStack* mostrarCaminhoVolta(Grafo* inicioGrafo, char verticeAtual[], char verticeDestino[], Stack* inicioStack, ListaStack* inicioLista, float Tamanho);

int todosVisitados(Stack* inicioStack, Grafo* inicioGrafo);

bool verticeVisitado(Stack* inicioStack, char vertice[]);

#pragma endregion

#pragma region STACK

void obterUltimoVertice(ListaStack* inicioLista, char* vertice);

Stack* inserirStack(Stack* inicioStack, char vertice[]);

void mostrarCaminho(ListaStack* inicioLista);

ListaStack* retirarStackMaior(ListaStack* inicioLista);

ListaStack* adicionarCaminho(Stack* caminho, ListaStack* listaCaminhos, float tamanho);


#pragma endregion
// -------------------------------------------------------------------FUNÇÕES_F-CIDADES--------------------------------------------------------------------
