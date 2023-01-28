#ifndef INDICEPALAVRAS_H
#define INDICEPALAVRAS_H

#include "indiceDocs.h"
#include "palavra.h"
#include "arrayBusca.h"

typedef struct indicePalavras IndicePalavras;

IndicePalavras * InicializaIndicePalavras(IndicePalavras *palavras);

void AdicionaPalavraBuscada(IndicePalavras *arrayDeBusca, IndicePalavras *p, char *palavra);

IndicePalavras * AlocaIdxPalavras();

IndicePalavras * AtribuiIndicePalavras(IndicePalavras *p, int nDoc, char *caminhoAux);

int ProcuraRepetida(IndicePalavras *p, char *palavra);

void LiberaIndicePalavras(IndicePalavras *p);

void AtribuiTf_idfIdxPalavras(IndicePalavras *p, int qtdDocs);

void SalvaIndicePalavrasBin(IndicePalavras *p, FILE *f);

IndicePalavras * CarregaIndicePalavrasBin(IndicePalavras *p, FILE *f);

void ImprimePalavras(IndicePalavras *p);

void OrdenaIndicePalavras(IndicePalavras *p);

Palavra ** BuscaPalavra(IndicePalavras *p, char *palavra);

void FinalizaCaracDocumentos_indxPalavras(IndicePalavras *p, IndiceDocs *docs);

void LiberaIndicePalavrasBuscadas(IndicePalavras *p);

void CriaArrayDeBusca_IndxPalavras(IndicePalavras *p, ArrayBusca *arrayB, IndiceDocs *docs);

#endif