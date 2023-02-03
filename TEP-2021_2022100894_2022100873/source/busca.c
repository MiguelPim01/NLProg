#include <stdio.h>
#include <stdlib.h>

#include "../headers/busca.h"
#include "../headers/documento.h"

struct busca {
    Documento *doc;
    double somatorio_tf_idf;
};

Busca * InicializaStructBusca(Busca *b, Documento *doc, double tf_idf)
{
    b = (Busca *)malloc(sizeof(Busca));

    b->doc = doc;
    b->somatorio_tf_idf = tf_idf;

    return b;
}

void SomaTF_IDF(Busca *b, double tf_idf)
{
    b->somatorio_tf_idf += tf_idf;
}

Documento * RetornaDocumentoArrayDeBusca(Busca *b)
{
    return b->doc;
}

int PeloTF_IDF(const void *a, const void *b)
{
    const Busca **b1 = (const Busca **)a;
    const Busca **b2 = (const Busca **)b;

    return ((*b2)->somatorio_tf_idf - (*b1)->somatorio_tf_idf);
}

void PrintaBusca(Busca *b)
{
    ImprimeDoc(b->doc);
}

void LiberaBusca(Busca *b)
{
    free(b);
}