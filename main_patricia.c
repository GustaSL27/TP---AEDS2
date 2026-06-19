#include <ctype.h>
#include "patricia.h"
#include "patricia.c"

int main() {
    TipoArvore arvore = NULL;
    FILE *arquivo;
    char nomeArquivo[30];
    TipoChave palavra;
    int idDoc, i, j;
    char c;

    // le cada fabula automaticamente
    for (idDoc = 0; idDoc < MAXDOCS; idDoc++) {

        // monta o nome do arquivo ex: fabula01.txt
        sprintf(nomeArquivo, "../fabulas/fabula%02d.txt", idDoc + 1);

        arquivo = fopen(nomeArquivo, "r");
        if (arquivo == NULL) {
            printf("Arquivo %s nao encontrado\n", nomeArquivo);
            continue;
        }

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

            arvore = Insere(palavra, &arvore, idDoc);
        }

        fclose(arquivo);
    }

    // imprime a tabela
    // percorre a arvore e imprime cada palavra com suas contagens

    Imprime(arvore);

    return 0;
}
