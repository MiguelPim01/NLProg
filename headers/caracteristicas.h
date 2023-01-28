#ifndef CARACTERISTICAS_H
#define CARACTERISTICAS_H

#include "../headers/indiceDocs.h"

typedef struct caracteristicas Caracteristicas;

Caracteristicas * AlocaCaracteristicas();

Caracteristicas * InicializaCaracteristicas(Caracteristicas * crts, int pos, int freq, double tf_idf);

Caracteristicas * SomaNaFrequencia(Caracteristicas *crts);

int VerificaSeAddFrequencia(Caracteristicas * crts, int pos);

void CalculaTf_idf(Caracteristicas *crts, int df, int n);

void SalvaCaracteristicasBin(Caracteristicas *crts, FILE *f);

Caracteristicas * CarregaCaracteristicasBin(Caracteristicas *crts, FILE *f);

void ImprimeCaracteristicas(Caracteristicas *crts);

void LiberaCaracteristicas(Caracteristicas *crts);

void FinalizaCaracDocumentos_carac(Caracteristicas *crts, IndiceDocs *docs, int posPalavra);

#endif