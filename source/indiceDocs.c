#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/indiceDocs.h"
#include "../headers/documento.h"

struct indiceDocs {
    Documento **arrayDocs;
    int qtdDocs;
};

IndiceDocs * InicializaIndiceDocs(IndiceDocs *docs) {
    int mult = 10;

    docs = (IndiceDocs *)malloc(sizeof(IndiceDocs));

    docs->arrayDocs = (Documento **)malloc(mult*sizeof(Documento *));

    docs->qtdDocs = 0;

    return docs;
}

IndiceDocs * AtribuiNomeClasseIndiceDocs(IndiceDocs *docs, char *caminho, char *classe)
{
    static int mult = 10;

    // Formata o caminho como nome do documento
    char nome[50];
    nome[0] = '\0';

    sscanf(caminho, "%*[^/]/%s", nome);

    docs->arrayDocs[docs->qtdDocs] = AtribuiNomeClasse(docs->arrayDocs[docs->qtdDocs], nome, classe);
    
    docs->qtdDocs++;

    if (docs->qtdDocs >= mult)
    {
        mult *=2;
        docs->arrayDocs = (Documento **)realloc(docs->arrayDocs, mult*sizeof(Documento *));
    }

    return docs;
}

void ImprimeDocs(IndiceDocs *docs)
{
    int i;

    for (i = 0; i < docs->qtdDocs; i++)
    {
        printf("doc %d:\n", i);
        ImprimeDoc(docs->arrayDocs[i]);
        printf("\n");
    }
}

void LiberaIndiceDocs(IndiceDocs *docs)
{
    int i;

    for (i = 0; i < docs->qtdDocs; i++)
    {
        LiberaDoc(docs->arrayDocs[i]);
    }
    free(docs->arrayDocs);
    free(docs);
}