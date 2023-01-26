#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/palavra.h"
#include "../headers/caracteristicas.h"
#include "../headers/indiceDocs.h"

#define FREQ_INICIAL 1
#define TF_IDF_PADRAO 0

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

    p->crts[0] = InicializaCaracteristicas(p->crts[0], nDoc, FREQ_INICIAL, TF_IDF_PADRAO);

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
        p->crts[p->qtdAparicoes-1] = InicializaCaracteristicas(p->crts[p->qtdAparicoes-1], nDoc, FREQ_INICIAL, TF_IDF_PADRAO);
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

int PelaPalavra(const void *a, const void *b)
{
    Palavra *p1 = (Palavra *)a;
    Palavra *p2 = (Palavra *)b;

    return strcmp(p1->palavra, p2->palavra);
}

void AtribuiTf_idfPalavra(Palavra *p, int n)
{
    int i;

    for (i = 0; i < p->qtdAparicoes; i++)
    {
        CalculaTf_idf(p->crts[i], p->qtdAparicoes, n);
    }
}

void FinalizaCaracDocumentos_palavras(Palavra *p, IndiceDocs *docs, int posPalavra)
{
    int i;

    for (i = 0; i < p->qtdAparicoes; i++)
    {
        FinalizaCaracDocumentos_carac(p->crts[i], docs, posPalavra);
    }
}

void SalvaPalavraBin(Palavra *p, FILE *f)
{
    fwrite(p->palavra, sizeof(char), strlen(p->palavra), f);

    fwrite(&p->qtdAparicoes, sizeof(int), 1, f);

    for (int i = 0; i < p->qtdAparicoes; i++)
    {
        SalvaCaracteristicasBin(p->crts[i], f);
    }
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