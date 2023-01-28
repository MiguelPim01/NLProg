#ifndef ARRAYBUSCA_H
#define ARRAYBUSCA_H

#include "indicePalavras.h"

typedef struct arrayBusca ArrayBusca;

ArrayBusca * AlocaArrayBusca();

ArrayBusca * InicializaArrayBusca();

void CriaArrayDeBusca(ArrayBusca *arrayB, int posicaoDoc, double tf_idf, IndiceDocs *docs);

#endif