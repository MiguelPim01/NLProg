#include <stdio.h>
#include <stdlib.h>

#include "../headers/arrayBusca.h"
#include "../headers/busca.h"
#include "../headers/documento.h"
#include "../headers/indiceDocs.h"

struct arrayBusca {
    Busca **arrayBusca;
    int qtdDocs;
};

ArrayBusca * AlocaArrayBusca()
{
    ArrayBusca *arrayB = (ArrayBusca *)malloc(sizeof(ArrayBusca));

    return arrayB;
}

ArrayBusca * InicializaArrayBusca()
{
    ArrayBusca *arrayB = AlocaArrayBusca();

    arrayB->arrayBusca = NULL;
    arrayB->qtdDocs = 0;

    return arrayB;
}

void CriaArrayDeBusca(ArrayBusca *arrayB, int posicaoDoc, double tf_idf, IndiceDocs *docs)
{
    if (arrayB->arrayBusca[0] == NULL)
    {
        arrayB->arrayBusca = (Busca **)malloc(sizeof(Busca *));

        arrayB->arrayBusca[0] = InicializaStructBusca(arrayB->arrayBusca[0], AchaDocumento(docs, posicaoDoc), tf_idf);

        arrayB->qtdDocs++;
    }
    else
    {
        int i = 0;

        for (i = 0; i < arrayB->qtdDocs; i++)
        {
            if (DocsSaoIguais(AchaDocumento(docs, posicaoDoc), RetornaDocumentoArrayDeBusca(arrayB->arrayBusca[i])))
            {
                SomaTF_IDF(arrayB->arrayBusca[i], tf_idf);
                break;
            }
        }

        if (i == arrayB->qtdDocs)
        {
            arrayB->qtdDocs++;
            arrayB->arrayBusca = (Busca **)realloc(arrayB->arrayBusca, arrayB->qtdDocs*sizeof(Busca *));

            arrayB->arrayBusca[arrayB->qtdDocs-1] = InicializaStructBusca(arrayB->arrayBusca[arrayB->qtdDocs-1], AchaDocumento(docs, posicaoDoc), tf_idf);
        }
    }
}