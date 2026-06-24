#include "hash.h"

void FLVazia(ListaEncadeada *Hash){
  Hash->Primeiro = (TipoCelula *)malloc(sizeof(TipoCelula));
  Hash->Ultimo = Hash->Primeiro; Hash->Primeiro->Prox = NULL;
}  

short Vazia(ListaEncadeada Hash){
    return (Hash.Primeiro == Hash.Ultimo); 
}

void Ins(TipoItem x, ListaEncadeada *Hash){
  Hash->Ultimo->Prox = (TipoCelula *)malloc(sizeof(TipoCelula));
  Hash->Ultimo = Hash->Ultimo->Prox;
  Hash->Ultimo->Item = x;
  Hash->Ultimo->Prox = NULL;
}  

void GeraPesos(TipoPesos p){
  int i, j;
  struct timeval semente;
  gettimeofday(&semente, NULL); 
  srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
  for (i = 0; i < N; i++)
    for (j = 0; j < TAMALFABETO; j++)
      p[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
}

unsigned int h(TipoPalavra Palavra, TipoPesos p){
  int i; unsigned int Soma = 0; 
  int comp = strlen(Palavra);
  for (i = 0; i < comp; i++) Soma += p[i][(unsigned int)Palavra[i]];
  return (Soma % M);
}

void Inicializa(TabelaHash T){
  int i;
  for (i = 0; i < M; i++) FLVazia(&T[i]);
}

TipoApontador PesquisaHash(TipoPalavra Ch, TipoPesos p, TabelaHash T){
  /* TipoApontador de retorno aponta para o item anterior da Hash */
  unsigned int i;
  TipoApontador Ap;
  i = h(Ch, p);
  if (Vazia(T[i])) return NULL;  /* Pesquisa sem sucesso */
  else{
    Ap = T[i].Primeiro;
    while (Ap->Prox != NULL && strncmp(Ch, Ap->Prox->Item.Palavra, sizeof(TipoPalavra)))
      Ap = Ap->Prox;
    if (Ap->Prox != NULL && !strncmp(Ch, Ap->Prox->Item.Palavra, sizeof(TipoPalavra)))
      return Ap;
    else return NULL;  /* Pesquisa sem sucesso */
  }
}  

void InsereHash(TipoItem x, TipoPesos p, TabelaHash T, int *total) {
  TipoApontador Ap = PesquisaUltima(x.Palavra, p, T);

  if (Ap == NULL) {
    /* Palavra nunca vista: insere nova célula */
    x.qnt = 1;
    Ins(x, &T[h(x.Palavra, p)]);

    if (*total < MAX_ARRAY) {
        Palavras_ordenadas[*total] = x;
        (*total)++; 
    }
  } 
  else {
    TipoApontador UltimaCelula = Ap->Prox;
    if (UltimaCelula->Item.idDoc == x.idDoc) {
      /* IdDoc é igual -> incrementa qnt */
      UltimaCelula->Item.qnt++;
      
      // atualiza qnt no vetor também
      for(int i = 0; i < *total; i++) {
        if (Palavras_ordenadas[i].idDoc == x.idDoc && !strncmp(Palavras_ordenadas[i].Palavra, x.Palavra, sizeof(TipoPalavra))) {
          Palavras_ordenadas[i].qnt++;
          break;
        }
      }
    }
    else{
      /* IdDoc é diferente -> nova célula */
      x.qnt = 1;
      Ins(x, &T[h(x.Palavra, p)]);

      if (*total < MAX_ARRAY) {
          Palavras_ordenadas[*total] = x;
          (*total)++;
      }
    }
  }
}
void Imp(ListaEncadeada Hash) {
  TipoApontador Aux;
  Aux = Hash.Primeiro->Prox;

  while (Aux != NULL) {
    /* Imprime a palavra desta célula */
    printf("%-20.*s", N, Aux->Item.Palavra);
    printf(" <%d , %d>", Aux->Item.qnt, Aux->Item.idDoc);
        
    /* Percorre as próximas células que são da mesma palavra */
    TipoApontador Prox = Aux->Prox;
    while (Prox != NULL && !strncmp(Aux->Item.Palavra, Prox->Item.Palavra, sizeof(TipoPalavra))) {
      printf(" <%d , %d>", Prox->Item.qnt, Prox->Item.idDoc);
      Prox = Prox->Prox;
    }
    printf("\n");
    Aux = Prox; /* volta caso haja palavra diferente */
  }
}

void ImprimeHash(TabelaHash Tabela) {
  int i;
  printf("%-20s %s\n", "Palavra", "<qtde, idDoc>");
  printf("--------------------------------------\n");
  for (i = 0; i < M; i++) {
    if (!Vazia(Tabela[i]))
      Imp(Tabela[i]);
  }
}
 
void LerPalavra(char *p, int Tam){
  char c; int i, j;
  fflush(stdin); j=0;
  while (((c=getchar())!='\n') && j<Tam-1) p[j++]= c;
  p[j]='\0';
  while(c != '\n') c=getchar();
  for(i=j-1;(i>=0 && p[i]==' ');i--) p[i]='\0';
}

TipoApontador PesquisaUltima(TipoPalavra Ch, TipoPesos p, TabelaHash T) {
  unsigned int i = h(Ch, p);
  TipoApontador Ap, Ultimo = NULL;

  if (Vazia(T[i])) return NULL;

  Ap = T[i].Primeiro;
  while (Ap->Prox != NULL) {
    if (!strncmp(Ch, Ap->Prox->Item.Palavra, sizeof(TipoPalavra)))
      Ultimo = Ap;
    Ap = Ap->Prox;
  }
  return Ultimo; /* aponta para o anterior da última palavra */
}

void InsereArray(TipoItem item, int *total) {
  if (*total < M) {
    Palavras_ordenadas[*total] = item;
    (*total)++;
  }
}

int comparar_elementos_vetor(const void *a, const void *b) {
    TipoItem *itemA = (TipoItem *)a;
    TipoItem *itemB = (TipoItem *)b;
    return strncmp(itemA->Palavra, itemB->Palavra, sizeof(TipoPalavra));
}

void ImprimeArrayOrdenado(int total) {
    if (total == 0) {
        printf("Nenhum elemento inserido no vetor ainda.\n");
        return;
    }

    // ordena o vetor global usando o total recebido da main
    qsort(Palavras_ordenadas, total, sizeof(TipoItem), comparar_elementos_vetor);

    printf("\n%-20s %s\n", "Palavra", "<qtde, idDoc>");
    printf("--------------------------------------\n");

    int i = 0;
    while (i < total) {
        printf("%-20.*s", N, Palavras_ordenadas[i].Palavra);
        printf(" <%d , %d>", Palavras_ordenadas[i].qnt, Palavras_ordenadas[i].idDoc);
        
        int j = i + 1;
        // bota as palavras iguais de documentos diferentes na mesma linha
        while (j < total && !strncmp(Palavras_ordenadas[i].Palavra, Palavras_ordenadas[j].Palavra, sizeof(TipoPalavra))) {
            printf(" <%d , %d>", Palavras_ordenadas[j].qnt, Palavras_ordenadas[j].idDoc);
            j++;
        }
        printf("\n");
        i = j; // vai pra próxima palavra diferente
    }
    printf("--------------------------------------\n");
}