#ifndef AUXBUSCA_H
#define AUXBUSCA_H

#include "documento.h"

typedef struct busca Busca;

// Aloca espaço para a struct e atribui ponteiro para o documento e TF_IDF dados
Busca * InicializaStructBusca(Busca *b, Documento *doc, double tf_idf);

// Para uma struct busca ja inicializada, é somado o valor TF_IDF ao somatorio da strcut
void SomaTF_IDF(Busca *b, double tf_idf);

// Retorna ponteiro para o documento
Documento * RetornaDocumentoArrayDeBusca(Busca *b);

// Libera struct busca da memoria
void LiberaBusca(Busca *b);

// Funcao utilizada pelo qsort para ordenar arrayBusca pelo somatorio de TF_IDF
int PeloTF_IDF(const void *a, const void *b);

// Printa Busca
void PrintaBusca(Busca *b);

#endif