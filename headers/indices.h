#ifndef INDICES_H
#define INDICES_H

#include <stdio.h>

#include "indiceDocs.h"
#include "indicePalavras.h"

typedef struct indices Indices;

// Realiza a leitura de todos os documentos e armazena na struct indice o indice de palavras e documentos
Indices * CarregaIndices(FILE *f, Indices *i, char *caminhoAux);

// Salva os indices em um arquivo binario
void SalvaIndices(Indices *i, FILE *f);

// Realiza a leitura da struct indices de um arquivo binario
Indices * CarregaIndicesBin(Indices *i, FILE *f);

// Libera indices da memória
void LiberaIndices(Indices *i);

// Retorna ponteiro para indice de palavras
IndicePalavras * RetornaIndicePalavras(Indices *i);

// Retorna ponteiro para indice de documentos
IndiceDocs * RetornaIndiceDocs(Indices *i);

// Gera o relatorio da palavra
void GeraRelatorioPalavra(Indices *i, char *palavra);

// Gera o relatorio de documentos
void GeraRelatorioDocs(Indices *i, IndiceDocs *Rdocs);

void GeraMatrizConfusao(Indices *indices, char **classesVerdadeiras, char **classesDeduzidas, FILE *f);

int ** InicializaMatrizConfusao(int **matriz, int qtdClasses);

int ** AlocaMatrizConfusao(int **matriz, int qtdClasses);

void ImprimeMatrizConfusao(int **matriz, int qtdClasses, char **classes, FILE *f);

double CalculaAcuracia(int **matriz, int qtdClasses, int qtdDocs);

void LiberaMatrizConfusao(int **matriz, int qtdClasses);

#endif