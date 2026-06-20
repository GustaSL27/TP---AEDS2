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
    char decisao;

    TabelaHash Tabela;
    TipoPesos pesos;
    Inicializa(Tabela);
    GeraPesos(pesos);

    printf("Bem vindo ao sistema de indexacao de fabulas\n\n");
    printf("Qual funcao voce gostaria de usar:\n\n");
    printf("a - Receber e inserir as fabulas\n");
    printf("b - Imprimir a tabela hash e a arvore PATRICIA\n");
    printf("c - Buscar palavra\n");
    printf("d - Sair\n\n");
    while(1) {
        printf("Digite a letra da funcao desejada: ");
        scanf(" %c", &decisao);
        if(decisao == 'a'){
            printf("Recebendo e inserindo as fabulas\n\n");
            FILE *entrada = fopen("entrada.txt", "r");
            if (!entrada){
                fprintf(stderr, "Erro ao abrir entrada.txt\n");
                return 1;
            }

            int qtd;
            fscanf(entrada, "%d\n", &qtd);

            // le cada fabula automaticamente
            for (idDoc = 0; idDoc < qtd; idDoc++) {

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
            printf("Fabulas recebidas e inseridas com sucesso\n\n");
        }
        if (decisao == 'b') {
            // imprime a tabela
            // percorre a arvore e imprime cada palavra com suas contagens
            printf("Imprimindo tabela hash e arvore PATRICIA\n\n");
            printf("Hash apos entrada:\n\n");
            ImprimeHash(Tabela);

            printf("PATRICIA apos entrada:\n\n");
            ImprimePatricia(arvore);
        }
        
        if(decisao == 'c') {
            // busca por ordem de relevancia a ser implementada
        }

        if(decisao == 'd') {
            printf("Finalizando o programa.\n");
            break;
        }
    }

    return 0;
}
