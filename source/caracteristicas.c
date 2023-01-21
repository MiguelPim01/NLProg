#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/caracteristicas.h"

struct caracteristicas {
    int posicao, frequencia;
    double tfidf;
};

Caracteristicas * AlocaCaracteristicas()
{
    Caracteristicas *crts = (Caracteristicas *)malloc(sizeof(Caracteristicas));

    return crts;
}

Caracteristicas * InicializaCaracteristicas(Caracteristicas * crts, int nDoc)
{
    crts = AlocaCaracteristicas();
    crts->posicao = nDoc;
    crts->frequencia = 1;

    return crts;
}

Caracteristicas * AtribuiCaracteristicas(Caracteristicas *crts, int nDoc, int flag)
{
    if (flag)
    {
        crts->frequencia++;
    } 
    else 
    {
        crts = AlocaCaracteristicas();
        crts->posicao = nDoc;
        crts->frequencia = 1;
    }

    return crts;
}

Caracteristicas * SomaNaFrequencia(Caracteristicas *crts)
{
    crts->frequencia++;
}

int VerificaSeAddFrequencia(Caracteristicas * crts, int nDoc)
{
    if (crts->posicao == nDoc) 
    {
        return 1;
    }
    
    return 0;
}

void ImprimeCaracteristicas(Caracteristicas *crts)
{
    printf("pos: %d - freq: %d\n", crts->posicao, crts->frequencia);
}

void LiberaCaracteristicas(Caracteristicas *crts)
{
    free(crts);
}