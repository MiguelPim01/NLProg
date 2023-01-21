#ifndef PALAVRA_H
#define PALAVRA_H

typedef struct palavra Palavra;

Palavra * AlocaPalavra(char *palavra, int tamPalavra);

Palavra * InicializaPalavra(Palavra *p, char *palavra, int nDoc);

Palavra * AdicionaFrequencia(Palavra *p, int nDoc);

void AtribuiPalavra(Palavra *p, char *palavra, int nDoc);

int ComparaPalavras(Palavra *p, char *palavra);

void LiberaPalavra(Palavra *p);

void ImprimePalavra(Palavra *p);

#endif