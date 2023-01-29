#ifndef AUXBUSCA_H
#define AUXBUSCA_H

#include "documento.h"

typedef struct busca Busca;

Busca * InicializaStructBusca(Busca *b, Documento *doc, double tf_idf);

void SomaTF_IDF(Busca *b, double tf_idf);

Documento * RetornaDocumentoArrayDeBusca(Busca *b);

void LiberaBusca(Busca *b);

int PeloTF_IDF(const void *a, const void *b);

void PrintaBusca(Busca *b);

#endif