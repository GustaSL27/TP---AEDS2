#include "stopword.h"
#include <string.h>

int LerStopWord(char * arquivo_teste, TipoArvore * arvore_stop ){
    FILE *arquivo;
    TipoChave palavra;

    arquivo = fopen(arquivo_teste,"r");

    if(arquivo == NULL){
        printf("ERRO AO ABRIR ARQUIVO!");
        return 0;
    }

    while (fscanf(arquivo, "%19s", palavra.chave) == 1){
        // idDoc em 0 pois as stopwords nao pertencem a nenhum documento especifico
        // Passa NULL no final para nao contar as comparacoes no benchmark
        InserePatricia(palavra, arvore_stop, 0, NULL);
    }

    fclose(arquivo);
    return 1;

}

int EhStopWord(TipoChave k, TipoArvore t) {
    if (t == NULL) return 0;

    // chegou em folha
    if (EExterno(t)) {
        if (strcmp(k.chave, t->NO.NExterno.palavra.chave) == 0){
            return 1;
        }else{
            return 0;
        }
        
    }

  if (k.chave[t->NO.NInterno.posicao] < t->NO.NInterno.caractere)
    return EhStopWord(k, t->NO.NInterno.Esq);
  else
    return EhStopWord(k, t->NO.NInterno.Dir);
}