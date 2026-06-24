#include "leitura.h"
#include <ctype.h>
#include "../stopwords/stopword.h"

int LerEntrada(char *nomeArquivo) {
    FILE *entrada = fopen(nomeArquivo, "r");
    if (!entrada) {
        fprintf(stderr, "Erro ao abrir entrada.txt\n");
        return -1;
    }

    int qtd;
    fscanf(entrada, "%d\n", &qtd);

    fclose(entrada);
    return qtd;
}


void LerFabulasPATRICIA(char *nomeArquivoBase, int qtd, TipoArvore *arvore, TipoArvore arvorestop) {
    FILE *arquivo;
    char nomeArquivo[30];
    TipoChave palavra;
    int idDoc, i, j;
    char c;

    for (idDoc = 0; idDoc < qtd; idDoc++) {
        sprintf(nomeArquivo, "fabulas/fabula%02d.txt", idDoc + 1);

        arquivo = fopen(nomeArquivo, "r");
        if (arquivo == NULL) {
            printf("Arquivo %s nao encontrado\n", nomeArquivo);
            continue;
        }

        TipoItem x;
        while (fscanf(arquivo, "%19s", palavra.chave) == 1) {
            j = 0;
            for (i = 0; palavra.chave[i] != '\0'; i++) {
                c = tolower(palavra.chave[i]);
                if (c >= 'a' && c <= 'z')
                    palavra.chave[j++] = c;
            }
            palavra.chave[j] = '\0';

            if (j == 0) continue;

            if (EhStopWord(palavra, arvorestop)) {
                continue;
            }

            strcpy(x.Palavra, palavra.chave);
            x.idDoc = idDoc + 1;
            InserePatricia(palavra, arvore, idDoc + 1);
        }

        fclose(arquivo);
    }
}

void LerFabulasHash(char *nomeArquivoBase, int qtd, TipoArvore arvorestop, TabelaHash Tabela, TipoPesos pesos, int *total) {
    FILE *arquivo;
    char nomeArquivo[30];
    TipoChave palavra;
    int idDoc, i, j;
    char c;

    for (idDoc = 0; idDoc < qtd; idDoc++) {
        sprintf(nomeArquivo, "fabulas/fabula%02d.txt", idDoc + 1);

        arquivo = fopen(nomeArquivo, "r");
        if (arquivo == NULL) {
            printf("Arquivo %s nao encontrado\n", nomeArquivo);
            continue;
        }

        TipoItem x;
        while (fscanf(arquivo, "%19s", palavra.chave) == 1) {
            j = 0;
            for (i = 0; palavra.chave[i] != '\0'; i++) {
                c = tolower(palavra.chave[i]);
                if (c >= 'a' && c <= 'z')
                    palavra.chave[j++] = c;
            }
            palavra.chave[j] = '\0';

            if (j == 0) continue;

            if (EhStopWord(palavra, arvorestop)) {
                continue;
            }

            strcpy(x.Palavra, palavra.chave);
            x.idDoc = idDoc + 1;
            InsereHash(x, pesos, Tabela, total);
        }

        fclose(arquivo);
    }
}
