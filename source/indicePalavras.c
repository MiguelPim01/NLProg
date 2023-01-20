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

    while (fscanf(fileDoc, "%s", palavra) == 1)
    {
        fscanf(fileDoc, "%*c");
        // Caso a função ProcuraRepetida retorne -1, é a primeira aparição da palavra, caso contrário a função retornará o índice da palavra repetida
        if (ProcuraRepetida(p, palavra) == -1)
        {
            p->qtdPalavras++;

            posicao = p->qtdPalavras-1;
            
            p->arrayPalavras[posicao] = InicializaPalavra(p->arrayPalavras[posicao], palavra);
        } else {
            posicao = ProcuraRepetida(p, palavra);
        }
        AtribuiPalavra(p->arrayPalavras[posicao], palavra, nDoc);
            /*
            SE FOR REPETIDA NO MESMO DOCUMENTO -> ADICIONAR FREQUENCIA
            SE FOR REPETIDA DE OUTRO DOCUMENTO -> ADICIONAR POSICAO NO ARRAY CARACTERISTICAS
            aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
            */
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
        if (ComparaPalavras(p->arrayPalavras[i], palavra)) {
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