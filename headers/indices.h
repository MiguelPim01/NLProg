#ifndef INDICES_H
#define INDICES_H

#include <stdio.h>

typedef struct indices Indices;

Indices * CarregaIndices(FILE *f, Indices *i, char *caminhoAux);

void SalvaIndices(Indices *i, FILE *f);

Indices * CarregaIndicesBin(Indices *i, FILE *f);

void LiberaIndices(Indices *i);

#endif