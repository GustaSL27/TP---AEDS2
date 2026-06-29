#ifndef STOPWORD_H
#define STOPWORD_H

#include "../PATRICIA/patricia.h"

int LerStopWord(char * arquivo_teste, TipoArvore * arvore_stop );
int EhStopWord(TipoChave k , TipoArvore t);

#endif