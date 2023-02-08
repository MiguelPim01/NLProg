#ifndef ARRAYBUSCA_H
#define ARRAYBUSCA_H

#include "indiceDocs.h"

typedef struct arrayBusca ArrayBusca;

// Aloca array de Busca na memoria
ArrayBusca * AlocaArrayBusca();

// Inicializa variaveis e aloca array de busca
ArrayBusca * InicializaArrayBusca();

// Cria o array de Busca utilizado pelo buscador
void CriaArrayDeBusca(ArrayBusca *arrayB, int posicaoDoc, double tf_idf, IndiceDocs *docs);

// Libera array de busca da memoria
void LiberaArrayBusca(ArrayBusca *arrayB);

// Ordena array de busca pelos TF_IDF's
void OrdenaArrayBusca(ArrayBusca *arrayB);

// Printa Array de Busca
void PrintaResultadoDaBusca(ArrayBusca *arrayB);

#endif