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