#ifndef INDICES_H
#define INDICES_H

#include <stdio.h>

#include "indiceDocs.h"
#include "indicePalavras.h"

typedef struct indices Indices;

Indices * CarregaIndices(FILE *f, Indices *i, char *caminhoAux);

void SalvaIndices(Indices *i, FILE *f);

Indices * CarregaIndicesBin(Indices *i, FILE *f);

void LiberaIndices(Indices *i);

IndicePalavras * RetornaIndicePalavras(Indices *i);

IndiceDocs * RetornaIndiceDocs(Indices *i);

void GeraRelatorioPalavra(Indices *i, char *palavra);

void GeraRelatorioDocs(Indices *i, IndiceDocs *Rdocs);

void GeraMatrizConfusao(Indices *indices, char **classesVerdadeiras, char **classesDeduzidas, FILE *f);

void ImprimeMatrizConfusao(int **matriz, int qtdClasses, FILE *f);

#endif