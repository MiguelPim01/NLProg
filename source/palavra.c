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

    int mult = 5;

    p->crts = (Caracteristicas **)malloc(mult*sizeof(Caracteristicas *));
    p->palavra = (char *)malloc(tamPalavra*sizeof(char));

    return p;
}

Palavra * InicializaPalavra(Palavra *p, char *palavra)
{
    int tamPalavra = strlen(palavra)+1;
    
    p = AlocaPalavra(palavra, tamPalavra);

    strncpy(p->palavra, palavra, tamPalavra); // Atribui a palavra (string) na struct

    p->qtdAparicoes = 0;

    return p;
}

void AtribuiPalavra(Palavra *p, char *palavra, int nDoc)
{
    int i, flagFrequencia = 0;
    static int mult = 5;

    // Caso seja a primeira aparição da palavra, atribuir na posicao 0 do vetor caracteristicas
    if (!p->qtdAparicoes)
    {
        p->crts[0] = AtribuiCaracteristicas(p->crts[0], nDoc, flagFrequencia);p->qtdAparicoes++;
        return;
    }

    for (i = 0; i < p->qtdAparicoes; i++)
    {
        if (VerificaSeAddFrequencia(p->crts[i], nDoc)) {
            flagFrequencia = 1;
            break;
        }
    }

    // Adiciona uma apariçao (tamanho do vetor caracteristicas) caso não seja apenas a frequencia que esteja aumentando
    if (!flagFrequencia) p->qtdAparicoes++;

    // Aloca mais espaço no vetor de caracteristicas caso precise
    if (p->qtdAparicoes >= mult)
    {
        mult *= 2;
        p->crts = (Caracteristicas **)realloc(p->crts, mult*sizeof(Caracteristicas *));
    }

    p->crts[i] = AtribuiCaracteristicas(p->crts[i], nDoc, flagFrequencia);
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