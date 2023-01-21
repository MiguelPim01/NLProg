#ifndef INDICES_H
#define INDICES_H

typedef struct indices Indices;

Indices * CarregaIndices(FILE *f, Indices *i, char *caminhoAux);

void LiberaIndices(Indices *i);

#endif