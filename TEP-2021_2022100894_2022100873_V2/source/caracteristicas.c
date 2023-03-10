#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/caracteristicas.h"
#include "../headers/indiceDocs.h"
#include "../headers/documento.h"
#include "../headers/arrayBusca.h"

struct caracteristicas {
    int posicao, frequencia;
    double tf_idf;
};

Caracteristicas * AlocaCaracteristicas()
{
    Caracteristicas *crts = (Caracteristicas *)malloc(sizeof(Caracteristicas));

    return crts;
}

Caracteristicas * InicializaCaracteristicas(Caracteristicas * crts, int pos, int freq, double tf_idf)
{
    crts = AlocaCaracteristicas();
    crts->posicao = pos;
    crts->frequencia = freq;
    crts->tf_idf = tf_idf;

    return crts;
}

Caracteristicas * SomaNaFrequencia(Caracteristicas *crts)
{
    crts->frequencia++;

    return crts;
}

int VerificaSeAddFrequencia(Caracteristicas * crts, int nDoc)
{
    if (crts->posicao == nDoc) 
    {
        return 1;
    }
    
    return 0;
}

void CalculaTf_idf(Caracteristicas *crts, double idf)
{
    double tf;

    tf = crts->frequencia;

    crts->tf_idf = tf*idf;
}

void SalvaCaracteristicasBin(Caracteristicas *crts, FILE *f)
{
    fwrite(&crts->posicao, sizeof(int), 1, f);

    fwrite(&crts->frequencia, sizeof(int), 1, f);

    fwrite(&crts->tf_idf, sizeof(double), 1, f);
}

Caracteristicas * CarregaCaracteristicasBin(Caracteristicas *crts, FILE *f)
{
    crts = AlocaCaracteristicas();

    fread(&crts->posicao, sizeof(int), 1, f);

    fread(&crts->frequencia, sizeof(int), 1, f);

    fread(&crts->tf_idf, sizeof(double), 1, f);

    return crts;
}

void ImprimeCaracteristicas(Caracteristicas *crts)
{
    printf("pos: %d - freq: %d - tf_idf: %.2lf\n", crts->posicao, crts->frequencia, crts->tf_idf);
}

void LiberaCaracteristicas(Caracteristicas *crts)
{
    free(crts);
}

void FinalizaCaracDocumentos_carac(Caracteristicas *crts, IndiceDocs *docs, int posPalavra)
{
    AtribuiCaracDoc(AchaDocumento(docs, crts->posicao), posPalavra, crts->frequencia, crts->tf_idf);
}

void CriaArrayDeBusca_Carac(Caracteristicas *crts, ArrayBusca *arrayB, IndiceDocs *docs)
{
    CriaArrayDeBusca(arrayB, crts->posicao, crts->tf_idf, docs);
}

int ObtemPosicao(Caracteristicas *crts)
{
    return crts->posicao;
}

int ObtemFrequencia(Caracteristicas *crts)
{
    return crts->frequencia;
}

double ObtemTF_IDF(Caracteristicas *crts)
{
    return crts->tf_idf;
}

void CriaDoc_classificador_carac(Caracteristicas *crts, Documento *doc, int indicePalavra)
{
    AtribuiCaracDoc(doc, indicePalavra, crts->frequencia, crts->tf_idf);
}

void CopiaCaracDoc(Caracteristicas *crts, Documento *Rdoc)
{
    AtribuiCaracDoc(Rdoc, crts->posicao, crts->frequencia, crts->tf_idf);
}

int RetornaFrequencia(Caracteristicas *crts)
{
    return crts->frequencia;
}

Caracteristicas * CopiaCarac(Caracteristicas *crts, Caracteristicas *Rcrts)
{
    Rcrts = InicializaCaracteristicas(Rcrts, crts->posicao, crts->frequencia, crts->tf_idf);

    return Rcrts;
}

int RetornaPosicao(Caracteristicas *crts)
{
    return crts->posicao;
}

int PelaFrequencia(const void *a, const void *b)
{
    const Caracteristicas **crtsA = (const Caracteristicas **)a;
    const Caracteristicas **crtsB = (const Caracteristicas **)b;

    return (*crtsB)->frequencia - (*crtsA)->frequencia;
}