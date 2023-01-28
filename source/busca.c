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