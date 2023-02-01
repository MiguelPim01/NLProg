#ifndef PALAVRA_H
#define PALAVRA_H

#include <stdio.h>

#include "arrayBusca.h"
#include "indiceDocs.h"

typedef struct palavra Palavra;

Palavra * AlocaPalavra(int tamPalavra);

Palavra * AlocaPalavra_auxBusca(char *palavra);

void LiberaPalavra_auxBusca(Palavra *p);

Palavra * InicializaPalavra(Palavra *p, char *palavra, int nDoc);

Palavra * AdicionaFrequencia(Palavra *p, int nDoc);

int ComparaPalavras(Palavra *p, char *palavra);

int PelaPalavra(const void *a, const void *b);

void AtribuiTf_idfPalavra(Palavra *p, IndiceDocs *docs, int flagClassificador);

void FinalizaCaracDocumentos_palavras(Palavra *p, IndiceDocs *docs, int posPalavra);

void SalvaPalavraBin(Palavra *p, FILE *f);

Palavra * CarregaPalavraBin(Palavra *p, FILE *f);

void LiberaPalavra(Palavra *p);

void ImprimePalavra(Palavra *p);

void CriaArrayDeBusca_Palavra(Palavra *p, ArrayBusca *arrayB, IndiceDocs *docs);

int ObtemQtdAparicoes(Palavra *p);

char * ObtemPalavra(Palavra *p);

void CriaDoc_classificador_palavra(Palavra *p, Documento *doc, int indicePalavra);

int StringIgualPalavra(Palavra *p, char *palavra);

void RelatorioPalavra(Palavra *p, char *palavra);

Palavra * CopiaPalavra(Palavra *p, Palavra *Rp);

#endif