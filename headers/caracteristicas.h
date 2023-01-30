#ifndef CARACTERISTICAS_H
#define CARACTERISTICAS_H

#include "indicePalavras.h"
#include "indiceDocs.h"

typedef struct caracteristicas Caracteristicas;

Caracteristicas * AlocaCaracteristicas();

Caracteristicas * InicializaCaracteristicas(Caracteristicas * crts, int pos, int freq, double tf_idf);

Caracteristicas * SomaNaFrequencia(Caracteristicas *crts);

int VerificaSeAddFrequencia(Caracteristicas * crts, int pos);

void CalculaTf_idf(Caracteristicas *crts, double idf);

void SalvaCaracteristicasBin(Caracteristicas *crts, FILE *f);

Caracteristicas * CarregaCaracteristicasBin(Caracteristicas *crts, FILE *f);

void ImprimeCaracteristicas(Caracteristicas *crts);

void LiberaCaracteristicas(Caracteristicas *crts);

void FinalizaCaracDocumentos_carac(Caracteristicas *crts, IndiceDocs *docs, int posPalavra);

void CriaArrayDeBusca_Carac(Caracteristicas *crts, ArrayBusca *arrayB, IndiceDocs *docs);

int ObtemPosicao(Caracteristicas *crts);

int ObtemFrequencia(Caracteristicas *crts);

double ObtemTF_IDF(Caracteristicas *crts);

void CriaDoc_classificador_carac(Caracteristicas *crts, Documento *doc, int indicePalavra);

#endif