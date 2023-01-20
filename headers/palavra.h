#ifndef PALAVRA_H
#define PALAVRA_H

typedef struct palavra Palavra;

Palavra * InicializaPalavra(Palavra *p, char *palavra);

void AtribuiPalavra(Palavra *p, char *palavra, int nDoc);

int ComparaPalavras(Palavra *p, char *palavra);

void LiberaPalavra(Palavra *p);

void ImprimePalavra(Palavra *p);

#endif