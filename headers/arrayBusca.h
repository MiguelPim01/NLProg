#ifndef ARRAYBUSCA_H
#define ARRAYBUSCA_H

#include "indiceDocs.h"

typedef struct arrayBusca ArrayBusca;

ArrayBusca * AlocaArrayBusca();

ArrayBusca * InicializaArrayBusca();

void CriaArrayDeBusca(ArrayBusca *arrayB, int posicaoDoc, double tf_idf, IndiceDocs *docs);

void LiberaArrayBusca(ArrayBusca *arrayB);

void OrdenaArrayBusca(ArrayBusca *arrayB);

void PrintaResultadoDaBusca(ArrayBusca *arrayB);

#endif