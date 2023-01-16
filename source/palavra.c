#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/palavra.h"
#include "../headers/caracteristicas.h"
#include "../headers/indiceDocs.h"

struct palavra {
    char *palavra;
    Caracteristicas **c;
    int qtdAparicoes;
};

void AtribuiPalavra(Palavra *p, char *palavra)
{
    int tamPalavra = strlen(palavra)+1;

    p->palavra = (char *)malloc(tamPalavra*sizeof(char));

    strncpy(p->palavra, palavra, tamPalavra);
}

void LiberaPalavra(Palavra *p)
{
    free(p->palavra);
}