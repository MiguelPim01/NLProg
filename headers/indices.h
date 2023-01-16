#ifndef INDICES_H
#define INDICES_H

typedef struct indices Indices;

Indices * CarregaIndices(FILE *f, Indices *i);

void LiberaIndices(Indices *i);

#endif