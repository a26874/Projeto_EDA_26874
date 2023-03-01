#include <stdio.h>
#define MAX_LINE_LEN 256

typedef struct registo_meios
{
	int codigo; // c�digo do meio de mobilidade el�trica
	char tipo[50];
	float bateria;
	float autonomia;
	char geocodigo[100];
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
	int codigo; // c�digo do gestor
	char nome[50]; // nome do gestor
	struct registo_gestor* seguinte_gestor; // endere�o de mem�ria para uma struct registo_gestor
} Gestor;

// -------------------------------------------------FUN��ES_I-LEITURA/ESCRITA/REPRESENTA��O DE MEIOS-------------------------------------------------


Meio* lerFicheiro_meios(Meio* inicio, FILE* dados_meios);

void listarMeios(Meio* inicio_meios);

Meio* escreverFicheiro_meios(Meio* inicio_meios, FILE* dados_meios);

Meio* escreverFicheiro_meios_bin(Meio* inicio_meios, FILE* dados_meios);


// -------------------------------------------------FUN��ES_F-LEITURA/ESCRITA/REPRESENTA��O DE MEIOS-------------------------------------------------





// -------------------------------------------------FUN��ES_I-LEITURA/ESCRITA/REPRESENTA��O DE CLIENTES-------------------------------------------------

Cliente* lerFicheiro_clientes(Cliente* inicio_clientes, FILE* dados_clientes);

void listarClientes(Cliente* inicio_clientes);

Cliente* escreverFicheiro_clientes(Cliente* inicio_clientes, FILE* dados_clientes);

Cliente* escreverFicheiro_clientes_bin(Cliente* inicio_clientes, FILE* dados_clientes);
// -------------------------------------------------FUN��ES_F-LEITURA/ESCRITA/REPRESENTA��O DE CLIENTES-------------------------------------------------




// -------------------------------------------------FUN��ES_I-LEITURA/ESCRITA/REPRESENTA��O DE GESTORES-------------------------------------------------


//void listarGestor(Gestor* inicio_gestor);




// -------------------------------------------------FUN��ES_F-LEITURA/ESCRITA/REPRESENTA��O DE GESTORES-------------------------------------------------
