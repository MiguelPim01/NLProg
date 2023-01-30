#ifndef INDICEPALAVRAS_H
#define INDICEPALAVRAS_H

#include "palavra.h"

typedef struct indicePalavras IndicePalavras;

IndicePalavras * InicializaIndicePalavras(IndicePalavras *palavras);

void AdicionaPalavraBuscada(IndicePalavras *arrayDeBusca, IndicePalavras *p, char *palavra);

void CriaIndicePalavras_classificador(IndicePalavras *palavrasDigitadas, IndicePalavras *p, char *palavra, IndiceDocs *docs);

IndicePalavras * AlocaIdxPalavras();

IndicePalavras * AtribuiIndicePalavras(IndicePalavras *p, int nDoc, char *caminhoAux);

int ProcuraRepetida(IndicePalavras *p, char *palavra);

void LiberaIndicePalavras(IndicePalavras *p);

void AtribuiTf_idfIdxPalavras(IndicePalavras *p, IndiceDocs *docs, int flagClassificador);

void SalvaIndicePalavrasBin(IndicePalavras *p, FILE *f);

IndicePalavras * CarregaIndicePalavrasBin(IndicePalavras *p, FILE *f);

void ImprimePalavras(IndicePalavras *p);

void OrdenaIndicePalavras(IndicePalavras *p);

Palavra ** BuscaPalavra(IndicePalavras *p, char *palavra);

void FinalizaCaracDocumentos_indxPalavras(IndicePalavras *p, IndiceDocs *docs);

void LiberaIndicePalavrasBuscadas(IndicePalavras *p);

void CriaArrayDeBusca_IndxPalavras(IndicePalavras *p, ArrayBusca *arrayB, IndiceDocs *docs);

int RetornaIndiceDaPalavra(IndicePalavras *p, Palavra *palavra);

void CriaDoc_classificador_indPalavras(IndicePalavras *p_buscadas, Documento *doc);

#endif