#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/indices.h"
#include "../headers/indiceDocs.h"
#include "../headers/indicePalavras.h"

struct indices {
    IndiceDocs *docs;
    IndicePalavras *palavras;
};

Indices * AlocaIndices()
{
    Indices *i = (Indices *)malloc(sizeof(Indices));

    i->docs = InicializaIndiceDocs(i->docs);
    i->palavras = InicializaIndicePalavras(i->palavras);

    return i;
}

Indices * CarregaIndices(FILE *f, Indices *i, char *caminhoAux)
{
    int contDocs = 0;
    char caminhoTxt[100], caminho[100], classe[10];
    caminhoTxt[0] = '\0'; caminho[0] = '\0'; classe[0] = '\0';

    i = AlocaIndices();

    // Lê, no arquivo train.txt, os nomes dos documentos e as classes, linha por linha
    while (fscanf(f, "%*[^/]%s ", caminhoTxt) == 1)
    {
        fscanf(f, "%[^\n]", classe);
        fscanf(f, "%*c");

        // Constroi caminho para o documento
        strncpy(caminho, caminhoAux, strlen(caminhoAux)+1);
        strcat(caminho, caminhoTxt);

        // Inicializa indice de docs (nome e classe)
        i->docs = AtribuiNomeClasseIndiceDocs(i->docs, caminhoTxt, classe);

        // Cria indice de palavras
        i->palavras = AtribuiIndicePalavras(i->palavras, contDocs, caminho);

        strncpy(caminho, caminhoAux, strlen(caminhoAux)+1);

        contDocs++;
    }

    OrdenaIndicePalavras(i->palavras);

    // ImprimeDocs(i->docs);
    ImprimePalavras(i->palavras);

    return i;
}

void LiberaIndices(Indices *i)
{
    LiberaIndiceDocs(i->docs);
    LiberaIndicePalavras(i->palavras);

    free(i);
}