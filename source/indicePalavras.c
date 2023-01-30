#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/indicePalavras.h"
#include "../headers/palavra.h"
#include "../headers/indiceDocs.h"
#include "../headers/arrayBusca.h"

#define QTD_INICIAL_ALLOC 25

struct indicePalavras {
    Palavra **arrayPalavras;
    int qtdPalavras;
};

IndicePalavras * AlocaIdxPalavras()
{
    IndicePalavras *palavras = (IndicePalavras *)malloc(sizeof(IndicePalavras));

    int mult = QTD_INICIAL_ALLOC;
    palavras->arrayPalavras = (Palavra **)malloc(mult*sizeof(Palavra *));

    return palavras;
}

IndicePalavras * InicializaIndicePalavras(IndicePalavras *palavras)
{
    palavras = AlocaIdxPalavras();

    palavras->qtdPalavras = 0;

    return palavras;
}

void AdicionaPalavraBuscada(IndicePalavras *arrayDeBusca, IndicePalavras *p, char *palavra)
{
    static int mult = QTD_INICIAL_ALLOC;
    Palavra **p_buscada = NULL;
    int rtnRepetida = 0;

    p_buscada = BuscaPalavra(p, palavra);

    rtnRepetida = ProcuraRepetida(arrayDeBusca, palavra);

    if (rtnRepetida == -1)
    {
        if (p_buscada != NULL)
        {   
            if (arrayDeBusca->qtdPalavras >= mult)
            {
                mult *= 2;
                arrayDeBusca->arrayPalavras = (Palavra **)realloc(arrayDeBusca->arrayPalavras, mult*sizeof(Palavra *));
            }

            arrayDeBusca->arrayPalavras[arrayDeBusca->qtdPalavras] = *p_buscada;
            arrayDeBusca->qtdPalavras++;
        }
    }
}

void CriaIndicePalavras_classificador(IndicePalavras *palavrasDigitadas, IndicePalavras *p, char *palavra, IndiceDocs *docs)
{
    static int mult = QTD_INICIAL_ALLOC;
    Palavra **p_buscada = NULL;
    int rtnRepetida = 0;

    p_buscada = BuscaPalavra(p, palavra);

    rtnRepetida = ProcuraRepetida(palavrasDigitadas, palavra);

    if (rtnRepetida != -1)
    {
        palavrasDigitadas->arrayPalavras[rtnRepetida] = AdicionaFrequencia(palavrasDigitadas->arrayPalavras[rtnRepetida], ObtemQtdDocumentos(docs)+1);
    }
    else 
    {
        if (p_buscada != NULL)
        {   
            if (palavrasDigitadas->qtdPalavras >= mult)
            {
                mult *= 2;
                palavrasDigitadas->arrayPalavras = (Palavra **)realloc(palavrasDigitadas->arrayPalavras, mult*sizeof(Palavra *));
            }

            palavrasDigitadas->arrayPalavras[palavrasDigitadas->qtdPalavras] = *p_buscada;
            palavrasDigitadas->arrayPalavras[palavrasDigitadas->qtdPalavras] = AdicionaFrequencia(palavrasDigitadas->arrayPalavras[palavrasDigitadas->qtdPalavras], ObtemQtdDocumentos(docs)+1);

            palavrasDigitadas->qtdPalavras++;
        }
    }
}

IndicePalavras * AtribuiIndicePalavras(IndicePalavras *p, int nDoc, char *caminho)
{
    FILE *fileDoc;
    static int mult = QTD_INICIAL_ALLOC, posicao = 0;
    char palavra[50];
    palavra[0] = '\0';

    fileDoc = fopen(caminho, "r");

    if (fileDoc == NULL)
    {
        printf("ERRO: Não foi possível abrir o documento com o caminho %s.\n", caminho);
        exit(1);
    }

    int rtrnProcura = 0;

    while (fscanf(fileDoc, "%s", palavra) == 1)
    {
        fscanf(fileDoc, "%*[^ ]");
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

void AtribuiTf_idfIdxPalavras(IndicePalavras *p, IndiceDocs *docs, int flagClassificador)
{
    int i;

    for (i = 0; i < p->qtdPalavras; i++)
    {
        AtribuiTf_idfPalavra(p->arrayPalavras[i], docs, flagClassificador);
    }
}

void OrdenaIndicePalavras(IndicePalavras *p)
{   
    qsort(p->arrayPalavras, p->qtdPalavras, sizeof(Palavra *), PelaPalavra);
}

Palavra ** BuscaPalavra(IndicePalavras *p, char *palavra)
{
    Palavra *p_usuario = AlocaPalavra_auxBusca(palavra);
    Palavra **ptr_pUsuario = &p_usuario;

    Palavra **p_buscada = (Palavra **)bsearch(ptr_pUsuario, p->arrayPalavras, p->qtdPalavras, sizeof(Palavra *), PelaPalavra);

    LiberaPalavra_auxBusca(p_usuario);

    return p_buscada;
}

void FinalizaCaracDocumentos_indxPalavras(IndicePalavras *p, IndiceDocs *docs)
{
    int i;

    for (i = 0; i < p->qtdPalavras; i++)
    {
        FinalizaCaracDocumentos_palavras(p->arrayPalavras[i], docs, i);
    }
}

void SalvaIndicePalavrasBin(IndicePalavras *p, FILE *f)
{
    fwrite(&p->qtdPalavras, sizeof(int), 1, f); // QTD_PALAVRAS

    for (int i = 0; i < p->qtdPalavras; i++)
    {
        SalvaPalavraBin(p->arrayPalavras[i], f); // PALAVRAS
    }
}

IndicePalavras * CarregaIndicePalavrasBin(IndicePalavras *p, FILE *f)
{
    p = (IndicePalavras *)malloc(sizeof(IndicePalavras));

    fread(&p->qtdPalavras, sizeof(int), 1, f); // QTD_PALAVRAS

    p->arrayPalavras = (Palavra **)malloc(p->qtdPalavras*sizeof(Palavra *)); // Alocando espaço exato para os ponteiros de palavra

    for (int i = 0; i < p->qtdPalavras; i++)
    {
        p->arrayPalavras[i] = CarregaPalavraBin(p->arrayPalavras[i], f); // PALAVRAS
    }

    return p;
}

void LiberaIndicePalavras(IndicePalavras *p)
{
    for (int i = 0; i < p->qtdPalavras; i++)
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
    // printf("    qtd: %d", p->qtdPalavras);
}

void LiberaIndicePalavrasBuscadas(IndicePalavras *p)
{
    free(p->arrayPalavras);
    free(p);
}

void CriaArrayDeBusca_IndxPalavras(IndicePalavras *p, ArrayBusca *arrayB, IndiceDocs *docs)
{
    for (int i = 0; i < p->qtdPalavras; i++)
    {
        CriaArrayDeBusca_Palavra(p->arrayPalavras[i], arrayB, docs);
    }
}

int RetornaIndiceDaPalavra(IndicePalavras *p, Palavra *palavra)
{
    int i = 0;

    for (i = 0; i < p->qtdPalavras; i++)
    {
        if (p->arrayPalavras[i] == palavra)
        {
            return i;
        }
    }

    return -1;
}

void CriaDoc_classificador_indPalavras(IndicePalavras *p_buscadas, Documento *doc)
{
    int i;

    for (i = 0; i < p_buscadas->qtdPalavras; i++)
    {
        CriaDoc_classificador_palavra(p_buscadas->arrayPalavras[i], doc);
    }
}