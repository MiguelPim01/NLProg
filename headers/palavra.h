#ifndef PALAVRA_H
#define PALAVRA_H

#include "../headers/indiceDocs.h"

typedef struct palavra Palavra;

Palavra * AlocaPalavra(char *palavra, int tamPalavra);

Palavra * AlocaPalavra_auxBusca(char *palavra);

void LiberaPalavra_auxBusca(Palavra *p);

Palavra * InicializaPalavra(Palavra *p, char *palavra, int nDoc);

Palavra * AdicionaFrequencia(Palavra *p, int nDoc);

int ComparaPalavras(Palavra *p, char *palavra);

int PelaPalavra(const void *a, const void *b);

void AtribuiTf_idfPalavra(Palavra *p, int n);

void FinalizaCaracDocumentos_palavras(Palavra *p, IndiceDocs *docs, int posPalavra);

void SalvaPalavraBin(Palavra *p, FILE *f);

Palavra * CarregaPalavraBin(Palavra *p, FILE *f);

void LiberaPalavra(Palavra *p);

void ImprimePalavra(Palavra *p);

#endif