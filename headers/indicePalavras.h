#ifndef INDICEPALAVRAS_H
#define INDICEPALAVRAS_H

typedef struct indicePalavras IndicePalavras;

IndicePalavras * InicializaIndicePalavras(IndicePalavras *palavras);

IndicePalavras * AtribuiIndicePalavras(IndicePalavras *p, char *caminho);

void LiberaIndicePalavras(IndicePalavras *p);

#endif