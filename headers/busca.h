#ifndef AUXBUSCA_H
#define AUXBUSCA_H

#include "documento.h"

typedef struct busca Busca;

Busca * InicializaStructBusca(Busca *b, Documento *doc, double tf_idf);

void SomaTF_IDF(Busca *b, double tf_idf);

Documento * RetornaDocumentoArrayDeBusca(Busca *b);

#endif