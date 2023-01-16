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

Palavra * AtribuiPalavra(Palavra *p, char *palavra)
{
    int tamPalavra = strlen(palavra)+1;

    p = (Palavra *)malloc(sizeof(Palavra));

    p->palavra = (char *)malloc(tamPalavra*sizeof(char));

    strncpy(p->palavra, palavra, tamPalavra);

    return p;
}

int EhRepetida(Palavra *p, char *palavra)
{
    if (!strcmp(p->palavra, palavra))
    {
        return 1;
    }
    
    return 0;
}

void ImprimePalavra(Palavra *p)
{
    printf("%s\n", p->palavra);
}

void LiberaPalavra(Palavra *p)
{
    free(p->palavra);
    free(p);
}