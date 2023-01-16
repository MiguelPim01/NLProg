#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/indicePalavras.h"
#include "../headers/palavra.h"

struct indicePalavras {
    Palavra **arrayPalavras;
    int qtdPalavras;
};

IndicePalavras * InicializaIndicePalavras(IndicePalavras *palavras)
{
    int mult = 25;
    // Aloca espaço para a struct IndicePalavras e array de palavra dentro dela
    palavras = (IndicePalavras *)malloc(sizeof(IndicePalavras));

    palavras->arrayPalavras = (Palavra **)malloc(mult*sizeof(Palavra *));

    palavras->qtdPalavras = 0;

    return palavras;
}

IndicePalavras * AtribuiIndicePalavras(IndicePalavras *p, char *caminho)
{
    FILE *fileDoc;
    static int mult = 25;
    char palavra[50];

    fileDoc = fopen(caminho, "r");
    printf("%s\n", caminho);

    while (fscanf(fileDoc, "%s", palavra) == 1)
    {
        AtribuiPalavra(p->arrayPalavras[p->qtdPalavras], palavra);
        p->qtdPalavras++;

        if (p->qtdPalavras >= mult)
        {
            mult *=2;
            p->arrayPalavras = (Palavra **)realloc(p->arrayPalavras, mult*sizeof(Palavra *));
        }
    }

    fclose(fileDoc);

    return p;
}

void LiberaIndicePalavras(IndicePalavras *p)
{
    int i;

    for (i = 0; i < p->qtdPalavras; i++)
    {
        LiberaPalavra(p->arrayPalavras[i]);
    }

    free(p);
}