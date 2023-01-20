#include <stdio.h>
#include <stdlib.h>

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

Indices * CarregaIndices(FILE *f, Indices *i) 
{
    int contDocs = 0;
    char caminho[50], classe[10];
    caminho[0] = '\0'; classe[0] = '\0';


    i = AlocaIndices();

    // Lê, no arquivo train.txt, os nomes dos documentos e as classes, linha por linha
    while (fscanf(f, "%s ", caminho) == 1)
    {
        fscanf(f, "%[^\n]", classe);
        fscanf(f, "%*c");

        i->docs = AtribuiNomeClasseIndiceDocs(i->docs, caminho, classe); // Inicializa indice de docs (nome e classe)

        i->palavras = AtribuiIndicePalavras(i->palavras, contDocs, caminho); // Cria indice de palavras

        contDocs++;
    }
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