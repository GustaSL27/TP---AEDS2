#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#define M 7
#define N 20
#define TAMALFABETO 256

typedef char TipoChave[N];
typedef unsigned TipoPesos[N][TAMALFABETO];
typedef struct TipoItem {
  TipoChave Chave;
  int qnt;
  int idDoc;
} TipoItem;

typedef unsigned int TipoIndice;
typedef struct TipoCelula* TipoApontador;
typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct TipoLista {
  TipoCelula *Primeiro, *Ultimo;
} TipoLista;

typedef TipoLista TipoDicionario[M];

void FLVazia(TipoLista *Lista);
short Vazia(TipoLista Lista);
void Ret(TipoApontador p, TipoLista *Lista, TipoItem *Item);
void GeraPesos(TipoPesos p);
TipoIndice h(TipoChave Chave, TipoPesos p);
void Inicializa(TipoDicionario T);
TipoApontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T);
void Insere(TipoItem x, TipoPesos p, TipoDicionario T);
void Retira(TipoItem x, TipoPesos p, TipoDicionario T);
void Imp(TipoLista Lista);
void Imprime(TipoDicionario Tabela);
void LerPalavra(char *p, int Tam);
