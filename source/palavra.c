#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/palavra.h"
#include "../headers/caracteristicas.h"
#include "../headers/indiceDocs.h"

struct palavra {
    char *palavra;
    Caracteristicas **crts;
    int qtdAparicoes;
};

Palavra * AlocaPalavra(char *palavra, int tamPalavra)
{
    Palavra *p = (Palavra *)malloc(sizeof(Palavra));

    p->crts = (Caracteristicas **)malloc(sizeof(Caracteristicas *));
    p->palavra = (char *)malloc(tamPalavra*sizeof(char));

    return p;
}

Palavra * InicializaPalavra(Palavra *p, char *palavra, int nDoc)
{
    int tamPalavra = strlen(palavra)+1;
    
    p = AlocaPalavra(palavra, tamPalavra);

    p->crts[0] = InicializaCaracteristicas(p->crts[0], nDoc);

    strncpy(p->palavra, palavra, tamPalavra); // Atribui a palavra (string) na struct

    p->qtdAparicoes = 1;

    return p;
}

Palavra * AdicionaFrequencia(Palavra *p, int nDoc)
{
    if (VerificaSeAddFrequencia(p->crts[p->qtdAparicoes-1], nDoc))
    {
        p->crts[p->qtdAparicoes-1] = SomaNaFrequencia(p->crts[p->qtdAparicoes-1]);
    }
    else 
    {
        p->qtdAparicoes++;
        
        p->crts = (Caracteristicas **)realloc(p->crts, p->qtdAparicoes*sizeof(Caracteristicas *));
        p->crts[p->qtdAparicoes-1] = InicializaCaracteristicas(p->crts[p->qtdAparicoes-1], nDoc);
    }
    
    return p;
}

int ComparaPalavras(Palavra *p, char *palavra)
{
    if (!strcmp(p->palavra, palavra))
    {
        return 1;
    }
    
    return 0;
}

void ImprimePalavra(Palavra *p)
{
    int i;

    printf("%s\n", p->palavra);

    for (i = 0; i < p->qtdAparicoes; i++)
    {
        ImprimeCaracteristicas(p->crts[i]);
    }

}

void LiberaPalavra(Palavra *p)
{
    int i;

    for (i = 0; i < p->qtdAparicoes; i++)
    {
        LiberaCaracteristicas(p->crts[i]);
    }  

    free(p->crts); 
    free(p->palavra);
    free(p);
}

int PelaPalavra(const void *a, const void *b)
{
    Palavra *p1 = (Palavra *)a;
    Palavra *p2 = (Palavra *)b;

    return strcmp(p1->palavra, p2->palavra);
}

size_t RetornaTamStructPalavra()
{
    return sizeof(Palavra);
}

char * RetornaPalavra(Palavra *p)
{
    return p->palavra;
}