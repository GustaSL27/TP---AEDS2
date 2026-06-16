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

TipoArvore CriaNoExt(TipoChave palavra)
{
    TipoArvore p; //Cria um p
    p = (TipoArvore)malloc(sizeof(TipoPatNo)); // Aloca o espaço do tamanho do TipoPatNo
    p->nt = Externo; //Define que esse p sera externo
    p->NO.palavra = palavra; 
    return p;
}

void Pesquisa(TipoChave palavra, TipoArvore t)
{
    if(t==NULL){
        printf("Arvore Vazia\n");
        return;
    }

    if (EExterno(t)) // Se chegou em um No externo entao verifica se a palavra q pesquisou é igual a palavra q ta armazenada
    {   if (strcmp(palavra.chave,t->NO.palavra.chave)==0){
        printf("Elemento encontrado: %s\n", t->NO.palavra.chave);
        } 
        else printf("Elemento nao encontrado\n");
        return;
    }
    if (palavra.chave[t->NO.NInterno.posicao] < t->NO.NInterno.caractere){//Se a letra q esta na posicao de comparacao da palavra for menor q o caracter comparado entao vai para a esq
        Pesquisa(palavra,t->NO.NInterno.Esq);
    } 
    else Pesquisa(palavra, t->NO.NInterno.Dir); // Se nao pesquisa pro lado dir
}


TipoArvore InsereEntre(TipoChave palavra, TipoArvore *t, int i)
{
  TipoArvore p;
  if (EExterno(*t) || i < (*t)->NO.NInterno.posicao) // verifica se chegou num no externo ou se na posicao que as palavras diferem é menor q a posicao atual , ai nesse caso vai precisar criar um no interno acima e um externo
  { /* cria um novo no externo */
    p = CriaNoExt(palavra);
    if (palavra.chave[i] > (*t)->NO.palavra.chave[i]){//palavra nova é maior  a nova vai pra direita, antiga vai pra esquerda
        return CriaNoInt(i, palavra.chave[i], t, &p);
    }  
    else return (CriaNoInt(i, (*t)->NO.palavra.chave[i], &p, t)); //palavra nova é MENOR -> nova vai pra esquerda, antiga vai pra direita
  } 
  else // se a posicao i é maior entao precisa descer a arvore ja que a posição que tem diferença esta mais abaixo
  { if (palavra.chave[(*t)->NO.NInterno.posicao] > (*t)->NO.NInterno.caractere) //Aqui vai verificar se irá descer para direita ou para a esq
    (*t)->NO.NInterno.Dir = InsereEntre(palavra,&(*t)->NO.NInterno.Dir,i);//Se o caracter da palavra na posicao atual for maior q o caractere divisor entao desce para direita
    else
    (*t)->NO.NInterno.Esq = InsereEntre(palavra,&(*t)->NO.NInterno.Esq,i);//  se nao for desce para esq
    return (*t);
  }

}


void Insere(TipoChave palavra, TipoArvore *t)
{
    TipoArvore p;
    int i;
    if (*t == NULL){
        *t = CriaNoExt(palavra);
        return;
    } //  Se *t é NULL é pq nao tem nenhuma palavra inserida na arvore entao cria um NoExt q armazena a palavra
    
    
    else 
    { 
        p = *t;
        while (!EExterno(p)) // Enquanto nao chegar num no externo vai descer a arvore
        {   //se o caractere na posicao atual for maior q o caracter divisor entao vai descer para direita
            if (palavra.chave[p->NO.NInterno.posicao] > p->NO.NInterno.caractere){
                p = p->NO.NInterno.Dir;
            }// se nao vai descer pra esq
            else p = p->NO.NInterno.Esq;
      }
    
      // Encontrou o No Ext agora vai achar onde q tem diferença entre a velha e a nova
    i = 0;
    while (palavra.chave[i] != '\0' && palavra.chave[i] == p->NO.palavra.chave[i]){ // Esse while vai comparar a palavra nova com a palavra que esta ali no no externo letra por letrar ate encontrar a posicao q tem uma diferença
        i++;
    } 
      
    if (strcmp(palavra.chave,p->NO.palavra.chave)==0) { // Se as palavras forem iguais entao ja está na arvore
        printf("Erro: chave ja esta na arvore\n");  
        return; 
    } 
    else {*t = InsereEntre(palavra, t, i);}// Se nao chama a InsereEntre pra inserir na posicao q tem a diferença
   }
}
