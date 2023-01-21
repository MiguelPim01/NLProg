#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/indicePalavras.h"
#include "../headers/palavra.h"

struct indicePalavras {
    Palavra **arrayPalavras;
    int qtdPalavras;
};

IndicePalavras * AlocaIndxPalavras()
{
    IndicePalavras *palavras = (IndicePalavras *)malloc(sizeof(IndicePalavras));

    int mult = 25;
    palavras->arrayPalavras = (Palavra **)malloc(mult*sizeof(Palavra *));

    return palavras;
}

IndicePalavras * InicializaIndicePalavras(IndicePalavras *palavras)
{
    palavras = AlocaIndxPalavras();

    palavras->qtdPalavras = 0;

    return palavras;
}

IndicePalavras * AtribuiIndicePalavras(IndicePalavras *p, int nDoc, char *caminhoAux)
{
    FILE *fileDoc;
    static int mult = 25, posicao = 0;
    char caminho[50], palavra[50];
    palavra[0] = '\0';

    sprintf(caminho, "data/%s", caminhoAux);
    fileDoc = fopen(caminho, "r");

    if (fileDoc == NULL)
    {
        printf("ERRO: Não foi possível abrir o documento com o caminho %s.\n", caminho);
        exit(1);
    }

    int rtrnProcura=0;

    while (fscanf(fileDoc, "%s", palavra) == 1)
    {
        fscanf(fileDoc, "%*c");

        // Caso a função ProcuraRepetida retorne -1, é a primeira aparição da palavra, caso contrário a função retornará o índice da palavra repetida
        rtrnProcura = ProcuraRepetida(p, palavra);

        if (rtrnProcura == -1)
        {
            p->qtdPalavras++;

            posicao = p->qtdPalavras-1;
            
            p->arrayPalavras[posicao] = InicializaPalavra(p->arrayPalavras[posicao], palavra, nDoc);
        } 
        else 
        {
            posicao = rtrnProcura;

            p->arrayPalavras[posicao] = AdicionaFrequencia(p->arrayPalavras[posicao], nDoc);
        }

        // AtribuiPalavra(p->arrayPalavras[posicao], palavra, nDoc);
        

        if (p->qtdPalavras >= mult)
        {
            mult *= 2;
            p->arrayPalavras = (Palavra **)realloc(p->arrayPalavras, mult*sizeof(Palavra *));
        }
    }

    fclose(fileDoc);

    return p;
}

int ProcuraRepetida(IndicePalavras *p, char *palavra)
{
    int i;

    for (i = 0; i < p->qtdPalavras; i++)
    {
        if (ComparaPalavras(p->arrayPalavras[i], palavra)) 
        {
            return i;
        }
    }
    return -1;
}

void LiberaIndicePalavras(IndicePalavras *p)
{
    int i;

    for (i = 0; i < p->qtdPalavras; i++)
    {
        LiberaPalavra(p->arrayPalavras[i]);
    }
    
    free(p->arrayPalavras);
    free(p);
}

void ImprimePalavras(IndicePalavras *p)
{
    int i;
    
    for (i = 0; i < p->qtdPalavras; i++)
    {
        printf("palavra %d: ", i);
        ImprimePalavra(p->arrayPalavras[i]);
    }
}