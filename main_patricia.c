#include <ctype.h>
#include <string.h>
#include "PATRICIA/patricia.h"
#include "hash/hash.h"

int main() {
    TipoArvore arvore = NULL;
    FILE *arquivo;
    char nomeArquivo[30];
    TipoChave palavra;
    int idDoc, i, j;
    char c;

    TabelaHash Tabela;
    TipoPesos pesos;
    Inicializa(Tabela);
    GeraPesos(pesos);

    // le cada fabula automaticamente
    for (idDoc = 0; idDoc < MAXDOCS; idDoc++) {

        // monta o nome do arquivo ex: fabula01.txt
        sprintf(nomeArquivo, "../fabulas/fabula%02d.txt", idDoc + 1);

        arquivo = fopen(nomeArquivo, "r");
        if (arquivo == NULL) {
            printf("Arquivo %s nao encontrado\n", nomeArquivo);
            continue;
        }

        TipoItem x;
        // le cada palavra do arquivo
        while (fscanf(arquivo, "%99s", palavra) == 1) {

            // converte para minusculo e remove sinais
            j = 0;
            for (i = 0; palavra[i] != '\0'; i++) {
                c = tolower(palavra[i]);
                if (c >= 'a' && c <= 'z')  // aceita apenas letras
                    palavra[j++] = c;
            }
            palavra[j] = '\0';  // finaliza a palavra

            // ignora palavras vazias
            if (j == 0) continue;

            strcpy(x.Palavra, (char *)palavra);
            x.idDoc = idDoc + 1;
            arvore = InserePatricia(palavra, &arvore, idDoc);
            InsereHash(x, pesos, Tabela);
        }

        fclose(arquivo);
    }

    // imprime a tabela
    // percorre a arvore e imprime cada palavra com suas contagens

    printf("Hash apos entrada:\n\n");
    ImprimeHash(Tabela);

    printf("PATRICIA apos entrada:\n\n");
    ImprimePatricia(arvore);

    return 0;
}
