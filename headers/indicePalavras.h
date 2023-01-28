#ifndef INDICEPALAVRAS_H
#define INDICEPALAVRAS_H

#include "../headers/indiceDocs.h"
#include "../headers/palavra.h"

typedef struct indicePalavras IndicePalavras;

IndicePalavras * InicializaIndicePalavras(IndicePalavras *palavras);

IndicePalavras * AlocaIdxPalavras();

IndicePalavras * AtribuiIndicePalavras(IndicePalavras *p, int nDoc, char *caminhoAux);

int ProcuraRepetida(IndicePalavras *p, char *palavra);

void LiberaIndicePalavras(IndicePalavras *p);

void AtribuiTf_idfIdxPalavras(IndicePalavras *p, int qtdDocs);

void SalvaIndicePalavrasBin(IndicePalavras *p, FILE *f);

IndicePalavras * CarregaIndicePalavrasBin(IndicePalavras *p, FILE *f);

void ImprimePalavras(IndicePalavras *p);

void OrdenaIndicePalavras(IndicePalavras *p);

Palavra * BuscaPalavra(IndicePalavras *p, Palavra *palavra);

void FinalizaCaracDocumentos_indxPalavras(IndicePalavras *p, IndiceDocs *docs);

#endif