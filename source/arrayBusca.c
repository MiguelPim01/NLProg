#include <stdio.h>
#include <stdlib.h>

#include "../headers/arrayBusca.h"
#include "../headers/busca.h"
#include "../headers/documento.h"
#include "../headers/indiceDocs.h"

#define ALLOC_INICIAL 25

struct arrayBusca {
    Busca **arrayBusca;
    int qtdDocs;
};

ArrayBusca * AlocaArrayBusca()
{
    ArrayBusca *arrayB = (ArrayBusca *)malloc(sizeof(ArrayBusca));

    arrayB->arrayBusca = (Busca **)malloc(ALLOC_INICIAL*sizeof(Busca *));

    return arrayB;
}

ArrayBusca * InicializaArrayBusca()
{
    ArrayBusca *arrayB = AlocaArrayBusca();

    arrayB->qtdDocs = 0;

    return arrayB;
}

void CriaArrayDeBusca(ArrayBusca *arrayB, int posicaoDoc, double tf_idf, IndiceDocs *docs)
{
    int i = 0;
    static int mult = ALLOC_INICIAL;

    for (i = 0; i < arrayB->qtdDocs; i++)
    {
        if (DocsSaoIguais(AchaDocumento(docs, posicaoDoc), RetornaDocumentoArrayDeBusca(arrayB->arrayBusca[i])))
        {
            SomaTF_IDF(arrayB->arrayBusca[i], tf_idf);
            return;
        }
    }

    if (i == arrayB->qtdDocs)
    {
        arrayB->qtdDocs++;

        if (arrayB->qtdDocs >= mult)
        {
            mult *= 2;
            arrayB->arrayBusca = (Busca **)realloc(arrayB->arrayBusca, mult*sizeof(Busca *));
        }

        arrayB->arrayBusca[arrayB->qtdDocs-1] = InicializaStructBusca(arrayB->arrayBusca[arrayB->qtdDocs-1], AchaDocumento(docs, posicaoDoc), tf_idf);
    }
    
}

void LiberaArrayBusca(ArrayBusca *arrayB)
{
    int i = 0;

    for (i = 0; i < arrayB->qtdDocs; i++)
    {
        LiberaBusca(arrayB->arrayBusca[i]);
    }

    free(arrayB->arrayBusca);
    free(arrayB);
}

void OrdenaArrayBusca(ArrayBusca *arrayB)
{
    qsort(arrayB->arrayBusca, arrayB->qtdDocs, sizeof(Busca *), PeloTF_IDF);
}

void PrintaResultadoDaBusca(ArrayBusca *arrayB)
{
    if (arrayB->qtdDocs == 0)
    {
        printf("Nao existem documentos achados para a sua procura!\n");
    }
    else 
    {
        int i = 0;

        for (i = 0; i < arrayB->qtdDocs && i < 10; i++)
        {
            printf("%d ==> ", i);
            PrintaBusca(arrayB->arrayBusca[i]);
        }
    }
}