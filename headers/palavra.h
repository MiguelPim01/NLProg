#ifndef PALAVRA_H
#define PALAVRA_H

typedef struct palavra Palavra;

Palavra * AtribuiPalavra(Palavra *p, char *palavra);

void LiberaPalavra(Palavra *p);

void ImprimePalavra(Palavra *p);

#endif