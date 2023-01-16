#include <stdio.h>
#include <stdlib.h>

#include "../headers/indices.h"
#include "../headers/indiceDocs.h"
#include "../headers/indicePalavras.h"

struct indices {
    IndiceDocs *docs;
    IndicePalavras *palavras;
};

Indices * CarregaIndices(FILE *f, Indices *i) {
    char caminho[50], classe[10];
    caminho[0] = '\0'; classe[0] = '\0';

    // Inicializa struct indices e seus membros IndiceDocs e IndicePalavras
    i = (Indices *)malloc(sizeof(Indices));

    i->docs = InicializaIndiceDocs(i->docs);

    i->palavras = InicializaIndicePalavras(i->palavras);

    // Lê cada linha do arquivo e separa o caminho, que também servirá para obter o nome do documento, e a classe
    while (fscanf(f, "%s ", caminho) == 1)
    {
        fscanf(f, "%[^\n]", classe);
        fscanf(f, "%*c");

        // Entra em cada cada membro da struct indices para fazer as atribuições
        i->docs = AtribuiNomeClasseIndiceDocs(i->docs, caminho, classe);

        i->palavras = AtribuiIndicePalavras(i->palavras, caminho);
    }
    ImprimeDocs(i->docs);
    ImprimePalavras(i->palavras);

    return i;
}

void LiberaIndices(Indices *i)
{
    LiberaIndiceDocs(i->docs);
    LiberaIndicePalavras(i->palavras);

    free(i);
}