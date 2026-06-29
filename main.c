#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "PATRICIA/patricia.h"
#include "stopwords/stopword.h"
#include "hash/hash.h"
#include "leitura/leitura.h"
#include "relevancia/relevancia.h"
#include <time.h>

int main() {
    TipoArvore arvore = NULL;
    TipoArvore arvorestop = NULL;
    char nomeArquivoStop[30] = "stopwords/stopwords.txt";
    char decisao;
    int opcao;
    
    clock_t tempo_inicio_Hash, tempo_final_Hash;
    clock_t tempo_inicio_PATRICIA, tempo_final_PATRICIA;
    double tempo_total_Hash = 0.0;
    double tempo_total_PATRICIA = 0.0;
    
    int total_elementos_array = 0;
    int comparacoes_hash = 0;
    int comparacoes_patricia = 0;
    int qtd = 0;

    TabelaHash Tabela;
    TipoPesos pesos;
    Inicializa(Tabela);
    GeraPesos(pesos);

    printf("Iniciando o sistema e carregando stopwords...\n");
    LerStopWord(nomeArquivoStop, &arvorestop);

    printf("Bem vindo ao sistema de indexacao de fabulas\n\n");

    // Começo do menu
    do {
        printf("\nQual funcao voce gostaria de usar:\n\n");
        printf("a - Receber e inserir as fabulas\n");
        printf("b - Imprimir a tabela hash e a arvore PATRICIA\n");
        printf("c - Buscar palavra\n");
        printf("d - Sair\n\n");
        printf("Digite a letra da funcao desejada: ");
        scanf(" %c", &decisao);

        // Escolhe inserir
        if(decisao == 'a'){
            // Salva a quantidade de fábulas na variável qtd
            qtd = LerEntrada("fabulas/entrada.txt");
            if (qtd == -1) {
                printf("Erro ao ler entrada.txt\n");
                continue;
            }

            do{
                printf("\nOnde voce gostaria de inserir as fabulas:\n");
                printf("\n1- Hash\n");
                printf("2- Patricia\n");
                printf("Digite a opcao desejada: ");
                scanf("%d",&opcao);

                if(opcao != 1 && opcao != 2){
                    printf("Opcao invalida!!!!\n\n");
                }
            } while (opcao != 1 && opcao != 2);

            if(opcao == 1){
                printf("Inserindo na tabela hash...\n\n");
                
                comparacoes_hash = 0;
                total_elementos_array = 0;
                Inicializa(Tabela); 

                tempo_inicio_Hash = clock();
                LerFabulasHash("fabulas/fabula", qtd, arvorestop, Tabela, pesos, &total_elementos_array, &comparacoes_hash);
                tempo_final_Hash = clock();

                tempo_total_Hash = (double)(tempo_final_Hash - tempo_inicio_Hash) / CLOCKS_PER_SEC;
                printf("Insercao hash concluida\n\n");
            }
            else if(opcao == 2){
                printf("Inserindo na arvore PATRICIA\n\n");
                
                comparacoes_patricia = 0;
                InicializaPatricia(&arvore);

                tempo_inicio_PATRICIA = clock();
                LerFabulasPATRICIA("fabulas/fabula", qtd, &arvore, arvorestop, &comparacoes_patricia);
                tempo_final_PATRICIA = clock();

                tempo_total_PATRICIA = (double)(tempo_final_PATRICIA - tempo_inicio_PATRICIA) / CLOCKS_PER_SEC;
                printf("Insercao PATRICIA concluida\n\n");
            }
        }

        // Escolhe imprimir (ordem alfabetica + estatistica de tempo)
        else if (decisao == 'b') {
            do {
                printf("Qual estrutura voce gostaria de imprimir\n");
                printf("\n1- Hash\n");
                printf("2- Patricia\n");
                printf("Digite a opcao desejada: ");
                scanf("%d",&opcao);

                if(opcao != 1 && opcao != 2){
                    printf("Opcao invalida!!!!\n\n");
                }
            } while (opcao != 1 && opcao != 2);

            if(opcao == 1){
                printf("Imprimindo tabela hash...\n\n");
                printf("Hash apos entrada:\n\n");
                ImprimeArrayOrdenado(total_elementos_array);
                printf("Imprimindo tempo da tabela hash...\n\n");
                printf("%.5f segundos\n", tempo_total_Hash);
                printf("Numero de comparacoes: %d\n", comparacoes_hash);
            }
            else if(opcao == 2){
                printf("Imprimindo arvore PATRICIA\n\n");
                printf("PATRICIA apos entrada:\n\n");
                ImprimePatricia(arvore);
                printf("Imprimindo tempo da arvore PATRICIA\n\n");
                printf("%.5f segundos\n", tempo_total_PATRICIA);
                printf("Numero de comparacoes: %d\n", comparacoes_patricia);
            }
        }

        else if(decisao == 'c') {
            int subOpcao;
            printf("\nEscolha o TAD para busca:\n1 - Hash\n2 - Patricia\nDigite a opcao: ");
            scanf("%d", &subOpcao);

            char termo[20];
            printf("Digite o termo: ");
            scanf("%s", termo);

            int numTotalDocs = qtd; 
            TipoResultadoBusca resultados[numTotalDocs];
            for(int i = 0; i < numTotalDocs; i++) {
                resultados[i].idDoc = i + 1;
                resultados[i].pesoTotal = 0;
            }

            if (subOpcao == 2) { 
                TipoChave chave;
                strcpy(chave.chave, termo);
                TipoArvore no = BuscaNoPatricia(chave, arvore, NULL); 
                if (no != NULL) {
                    int dj = ContaDocumentos(no->NO.NExterno.ocorrencias);
                    TipoApontadorOcorrencia aux = no->NO.NExterno.ocorrencias.Primeiro->Prox;
                    while(aux != NULL) {
                        float peso = CalculaPesoTFIDF(aux->Item.qtde, numTotalDocs, dj);
                        resultados[aux->Item.idDoc - 1].pesoTotal += peso;
                        aux = aux->Prox;
                    }
                } else printf("Termo nao encontrado.\n");
            } 
            else if (subOpcao == 1) { 
                TipoApontador no = BuscaListaHash(termo, pesos, Tabela, NULL);
                if (no != NULL) {
                    int dj = 0;
                    TipoApontador aux = no;
                    while(aux != NULL && strncmp(termo, aux->Item.Palavra, sizeof(TipoPalavra)) == 0) {
                        dj++;
                        aux = aux->Prox;
                    }
                    aux = no;
                    while(aux != NULL && strncmp(termo, aux->Item.Palavra, sizeof(TipoPalavra)) == 0) {
                        float peso = CalculaPesoTFIDF(aux->Item.qnt, numTotalDocs, dj);
                        resultados[aux->Item.idDoc - 1].pesoTotal += peso;
                        aux = aux->Prox;
                    }
                } else printf("Termo nao encontrado.\n");
            }
            OrdenaResultados(resultados, numTotalDocs);
            printf("\nRanking de relevancia:\n");
            for(int i = 0; i < numTotalDocs; i++) {
                if(resultados[i].pesoTotal > 0)
                    printf("Arquivo %d: Peso %.4f\n", resultados[i].idDoc, resultados[i].pesoTotal);
            }
        }

        else if(decisao == 'd') {
            printf("Saindo...\n");
        }
        else{
            printf("Opcao invalida! Tente novamente.\n\n");
        }

    } while (decisao != 'd');

    return 0;
}