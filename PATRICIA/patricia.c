#include "patricia.h"
#include "string.h"


void InicializaPatricia(TipoArvore *p){
    *p = NULL;
}

short EExterno(TipoArvore p)
{
    return (p->nt == Externo);  // Se o nt for o no externo vai retornar 1;
}

TipoArvore CriaNoInt(int i, char c, TipoArvore *Esq, TipoArvore *Dir)
{
    TipoArvore p; // Cria um p
    p = (TipoArvore)malloc(sizeof(TipoPatNo));  // Aloca espaço do tamanho do TipoPatNo
    p->nt = Interno; // Define  que o union sera o interno
    p->NO.NInterno.Esq = *Esq; //Define o filho a esq
    p->NO.NInterno.Dir = *Dir;  //Define o filho a dir
    p->NO.NInterno.posicao = i;  // Define a posicao de comparacao
    p->NO.NInterno.caractere = c; // Define a palavra de comparacao
    return p;

}

TipoArvore CriaNoExt(TipoChave palavra, int idDoc)
{
    TipoArvore p; //Cria um p
    p = (TipoArvore)malloc(sizeof(TipoPatNo)); // Aloca o espaço do tamanho do TipoPatNo
    p->nt = Externo; //Define que esse p sera externo
    p->NO.NExterno.palavra = palavra; 
    
    FLVaziaOcorrencia(&p->NO.NExterno.ocorrencias);  // inicializa a lista vazia
    
    TipoItemOcorrencia novoItem;
    novoItem.qtde = 1;
    novoItem.idDoc = idDoc;
    InsereListaOcorrencia(novoItem, &p->NO.NExterno.ocorrencias);  // insere o primeiro par


    return p;
}

void Pesquisa(TipoChave palavra, TipoArvore t, int *comp)
{
    if(t==NULL){
        printf("Arvore Vazia\n");
        return;
    }

    if (EExterno(t)) // Se chegou em um No externo entao verifica se a palavra q pesquisou é igual a palavra q ta armazenada
    {   
        if(comp) (*comp)++;
        if (strcmp(palavra.chave,t->NO.NExterno.palavra.chave)==0){
        printf("Elemento encontrado: %s\n", t->NO.NExterno.palavra.chave);
        } 
        else printf("Elemento nao encontrado\n");
        return;
    }
    if(comp) (*comp)++;
    if (palavra.chave[t->NO.NInterno.posicao] < t->NO.NInterno.caractere){//Se a letra q esta na posicao de comparacao da palavra for menor q o caracter comparado entao vai para a esq
        Pesquisa(palavra,t->NO.NInterno.Esq, comp);
    } 
    else Pesquisa(palavra, t->NO.NInterno.Dir, comp); // Se nao pesquisa pro lado dir
}



TipoArvore InsereEntrePatricia(TipoChave palavra, TipoArvore *t, int i,int idDoc, int *comp)
{
  TipoArvore p;
  TipoArvore repExterno;
  if (EExterno(*t) || i < (*t)->NO.NInterno.posicao) // verifica se chegou num no externo ou se na posicao que as palavras diferem é menor q a posicao atual , ai nesse caso vai precisar criar um no interno acima e um externo
  { /* cria um novo no externo */
    p = CriaNoExt(palavra,idDoc);
    repExterno = EExterno(*t) ? *t : PegaPalavraQualquer(*t); // pega um no externo representativo da subarvore, mesmo se *t for interno
    
    if(comp) (*comp)++;
    if (palavra.chave[i] > repExterno->NO.NExterno.palavra.chave[i]){//palavra nova é maior  a nova vai pra direita, antiga vai pra esquerda
        return CriaNoInt(i, palavra.chave[i], t, &p);
    }  
    else return (CriaNoInt(i, repExterno->NO.NExterno.palavra.chave[i], &p, t)); //palavra nova é MENOR -> nova vai pra esquerda, antiga vai pra direita
  } 
  else // se a posicao i é maior entao precisa descer a arvore ja que a posição que tem diferença esta mais abaixo
  { 
    if(comp) (*comp)++;
    if (palavra.chave[(*t)->NO.NInterno.posicao] >= (*t)->NO.NInterno.caractere) //Aqui vai verificar se irá descer para direita ou para a esq
    (*t)->NO.NInterno.Dir = InsereEntrePatricia(palavra,&(*t)->NO.NInterno.Dir,i,idDoc, comp);//Se o caracter da palavra na posicao atual for maior ou igual q o caractere divisor entao desce para direita
    else
    (*t)->NO.NInterno.Esq = InsereEntrePatricia(palavra,&(*t)->NO.NInterno.Esq,i,idDoc, comp);//  se nao for desce para esq
    return (*t);
  }

}


TipoArvore PegaPalavraQualquer(TipoArvore t) {
    // desce ate achar qualquer no externo dessa subarvore
    while (!EExterno(t)) {
        t = t->NO.NInterno.Esq;
    }
    return t;
}


void InserePatricia(TipoChave palavra, TipoArvore *t, int idDoc, int *comp)
{
    TipoArvore p;
    int i;
    if (*t == NULL){
        *t = CriaNoExt(palavra,idDoc);
        return;
    } //  Se *t é NULL é pq nao tem nenhuma palavra inserida na arvore entao cria um NoExt q armazena a palavra
    
    
    else 
    { 
        p = *t;
        while (!EExterno(p)) // Enquanto nao chegar num no externo vai descer a arvore
        {   
            if(comp) (*comp)++;
            //se o caractere na posicao atual for maior ou igual q o caracter divisor entao vai descer para direita
            if (palavra.chave[p->NO.NInterno.posicao] >= p->NO.NInterno.caractere){
                p = p->NO.NInterno.Dir;
            }// se nao vai descer pra esq
            else p = p->NO.NInterno.Esq;
      }
    
      // Encontrou o No Ext agora vai achar onde q tem diferença entre a velha e a nova
    i = 0;
    while (palavra.chave[i] != '\0' && palavra.chave[i] == p->NO.NExterno.palavra.chave[i]){ // Esse while vai comparar a palavra nova com a palavra que esta ali no no externo letra por letrar ate encontrar a posicao q tem uma diferença
        if(comp) (*comp)++;
        i++;
    } 
      
    if(comp) (*comp)++;
    if (strcmp(palavra.chave,p->NO.NExterno.palavra.chave)==0) { // Se as palavras forem iguais entao ja está na arvore
        AtualizaOcorrencia(&p->NO.NExterno.ocorrencias, idDoc, comp); // chama a atualizaOcorrencia para somar a quantidade
        return; 
    } 
    else {*t = InsereEntrePatricia(palavra, t, i,idDoc, comp);}// Se nao chama a InsereEntre pra inserir na posicao q tem a diferença
   }
}

void ImprimePatricia(TipoArvore p){
    if(p == NULL) return;

    if(EExterno(p)){
        printf("%-20s ", p->NO.NExterno.palavra.chave);
        ImprimeListaOcorrencia(p->NO.NExterno.ocorrencias);
        printf("\n");
        return;
    }

    // se for interno, percorre esquerda, depois direita
    ImprimePatricia(p->NO.NInterno.Esq);
    ImprimePatricia(p->NO.NInterno.Dir);
}

// Função auxiliar para buscar o nó de uma palavra específica
TipoArvore BuscaNoPatricia(TipoChave palavra, TipoArvore t, int *comp) {
    if (t == NULL) return NULL;
    if (EExterno(t)) {
        if(comp) (*comp)++;
        return (strcmp(palavra.chave, t->NO.NExterno.palavra.chave) == 0) ? t : NULL;
    }
    if(comp) (*comp)++;
    if (palavra.chave[t->NO.NInterno.posicao] < t->NO.NInterno.caractere)
        return BuscaNoPatricia(palavra, t->NO.NInterno.Esq, comp);
    else
        return BuscaNoPatricia(palavra, t->NO.NInterno.Dir, comp);
}