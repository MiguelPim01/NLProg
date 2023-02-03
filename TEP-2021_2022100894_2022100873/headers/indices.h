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

int ** InicializaMatrizConfusao(int **matriz, int qtdClasses);

int ** AlocaMatrizConfusao(int **matriz, int qtdClasses);

void ImprimeMatrizConfusao(int **matriz, int qtdClasses, char **classes, FILE *f);

double CalculaAcuracia(int **matriz, int qtdClasses, int qtdDocs);

void LiberaMatrizConfusao(int **matriz, int qtdClasses);

#endif