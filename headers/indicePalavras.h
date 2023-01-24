#ifndef INDICEPALAVRAS_H
#define INDICEPALAVRAS_H

typedef struct indicePalavras IndicePalavras;

IndicePalavras * InicializaIndicePalavras(IndicePalavras *palavras);

IndicePalavras * AlocaIdxPalavras();

IndicePalavras * AtribuiIndicePalavras(IndicePalavras *p, int nDoc, char *caminhoAux);

int ProcuraRepetida(IndicePalavras *p, char *palavra);

void LiberaIndicePalavras(IndicePalavras *p);

void AtribuiTf_idfIdxPalavras(IndicePalavras *p, int qtdDocs);

void ImprimePalavras(IndicePalavras *p);

void OrdenaIndicePalavras(IndicePalavras *p);

#endif