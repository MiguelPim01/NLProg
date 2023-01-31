#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/indiceDocs.h"
#include "../headers/documento.h"
#include "../headers/caracteristicas.h"

struct indiceDocs {
    Documento **arrayDocs;
    int qtdDocs;
};

IndiceDocs * AlocaIndxDocumentos()
{
    IndiceDocs *docs = (IndiceDocs *)malloc(sizeof(IndiceDocs));

    int mult = 10;
    docs->arrayDocs = (Documento **)malloc(mult*sizeof(Documento *));

    return docs;
}

IndiceDocs * InicializaIndiceDocs(IndiceDocs *docs) 
{
    docs = AlocaIndxDocumentos();

    docs->qtdDocs = 0;

    return docs;
}

IndiceDocs * AtribuiNomeClasseIndiceDocs(IndiceDocs *docs, char *caminho, char *classe)
{
    static int mult = 10;

    // Formata o caminho como nome do documento
    char nome[50];
    nome[0] = '\0';

    sscanf(caminho, "%*[/]%s", nome);

    docs->arrayDocs[docs->qtdDocs] = AtribuiNomeClasse(docs->arrayDocs[docs->qtdDocs], nome, classe);
    
    docs->qtdDocs++;

    if (docs->qtdDocs >= mult)
    {
        mult *=2;
        docs->arrayDocs = (Documento **)realloc(docs->arrayDocs, mult*sizeof(Documento *));
    }

    return docs;
}

int ObtemQtdDocumentos(IndiceDocs *docs)
{
    return docs->qtdDocs;
}

void ImprimeDocs(IndiceDocs *docs)
{
    int i;

    for (i = 0; i < docs->qtdDocs; i++)
    {
        printf("doc %d: ", i);
        ImprimeDoc(docs->arrayDocs[i]);
    }
}

Documento * AchaDocumento(IndiceDocs *docs, int posDocumento)
{
    return docs->arrayDocs[posDocumento];
}

void SalvaIndiceDocsBin(IndiceDocs *docs, FILE *f)
{
    fwrite(&docs->qtdDocs, sizeof(int), 1, f);
    
    for (int i = 0; i < docs->qtdDocs; i++)
    {
        SalvaDocBin(docs->arrayDocs[i], f);
    }
}

IndiceDocs * CarregaIndiceDocsBin(IndiceDocs *docs, FILE *f)
{   
    docs = (IndiceDocs *)malloc(sizeof(IndiceDocs));

    fread(&docs->qtdDocs, sizeof(int), 1, f);

    docs->arrayDocs = (Documento **)malloc(docs->qtdDocs*sizeof(Documento *)); // Alocando espaço exato para os ponteiros de documento

    for (int i = 0; i < docs->qtdDocs; i++)
    {
        docs->arrayDocs[i] = CarregaDocBin(docs->arrayDocs[i], f);
    }

    return docs;
}

void LiberaIndiceDocs(IndiceDocs *docs)
{
    for (int i = 0; i < docs->qtdDocs; i++)
    {
        LiberaDoc(docs->arrayDocs[i]);
    }
    
    free(docs->arrayDocs);
    free(docs);
}

double * CriaArrayCossenos(IndiceDocs *docs, Documento *doc)
{
    int i = 0;
    double *cossenos, somatorio = 0;

    somatorio = ObtemSomaTF_IDFs(doc);

    cossenos = (double *)malloc(docs->qtdDocs*sizeof(double));

    for (i = 0; i < docs->qtdDocs; i++)
    {
        cossenos[i] = CalculaCosseno(docs->arrayDocs[i], doc, somatorio);
    }

    return cossenos;
}

void AtribuiArrayDouble(double *a, double *b, int tam)
{
    int i;

    for (i = 0; i < tam; i++)
    {
        b[i] = a[i];
    }
}

int OrdenaCossenos(const void *a, const void *b)
{
    double *cos1 = (double *)a;
    double *cos2 = (double *)b;

    return ((*cos2) - (*cos1));
}

char * DeduzClasse(int K, Documento **docs)
{
    char **VetorClasses = NULL, *classe = NULL;
    int tamVetor = 0, flagAddChar = 0, *arrayCont = NULL, i, q;

    for (i = 0; i < K; i++)
    {
        classe = ObtemClasse(docs[i]);

        for (q = 0; q < tamVetor; q++)
        {
            if (VetorClasses[q] == classe)
            {
                flagAddChar = 1;
                arrayCont[q]++;
            }
        }

        if (flagAddChar == 0)
        {
            tamVetor++;

            VetorClasses = (char **)realloc(VetorClasses, tamVetor*sizeof(char *));
            arrayCont = (int *)realloc(arrayCont, tamVetor*sizeof(int));
            
            arrayCont[tamVetor-1] = 0;
            VetorClasses[tamVetor-1] = classe;
        }

        flagAddChar = 0;
    }

    int maior = 0;

    for (i = 0; i < tamVetor; i++)
    {
        if (!i) maior = i;
        else
        {
            if (arrayCont[i] > arrayCont[maior])
            {
                maior = i;
            }
        }
    }
    classe = VetorClasses[maior];

    free(VetorClasses);
    free(arrayCont);

    return classe;
}

void ClassificaNoticia(double *cossenos, IndiceDocs *docs, int K)
{
    double *AuxCossenos = (double *)malloc(docs->qtdDocs*sizeof(double));
    Documento **AuxClassificador = NULL;
    char *classe;

    AuxClassificador = (Documento **)malloc(K*sizeof(Documento *));

    AtribuiArrayDouble(cossenos, AuxCossenos, docs->qtdDocs);
    qsort(AuxCossenos, docs->qtdDocs, sizeof(double), OrdenaCossenos);

    int i, q;

    for (i = 0; i < K; i++)
    {
        for (q = 0; q < docs->qtdDocs; q++)
        {
            if (AuxCossenos[i] == cossenos[q])
            {
                AuxClassificador[i] = docs->arrayDocs[q];
            }
        }
    }

    classe = DeduzClasse(K, AuxClassificador);

    printf("\nClasse Deduzida: %s\n", classe);

    free(AuxClassificador);
    free(AuxCossenos);
}