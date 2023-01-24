#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/documento.h"
#include "../headers/caracteristicas.h"

struct documento {
    char *nome, *classe;
    Caracteristicas **crts;
    int qtdPalavras;
};

Documento * AlocaDocumento(int tamNome, int tamClasse)
{
    Documento *doc = (Documento *)malloc(sizeof(Documento));

    doc->nome = (char *)malloc(tamNome*sizeof(char));
    doc->classe = (char *)malloc(tamClasse*sizeof(char));
    doc->crts = NULL;
    doc->qtdPalavras = 0;

    return doc;
}

Documento * AtribuiNomeClasse(Documento *doc, char *nome, char *classe)
{
    int tamNome = strlen(nome)+1;
    int tamClasse = strlen(classe)+1;

    doc = AlocaDocumento(tamNome, tamClasse);

    strncpy(doc->nome, nome, tamNome);
    strncpy(doc->classe, classe, tamClasse);

    return doc;
}

void AtribuiCaracDoc(Documento *doc, int posPalavra, int freqPalavra, double tf_idf)
{
    doc->qtdPalavras++;
    doc->crts = (Caracteristicas **)realloc(doc->crts, doc->qtdPalavras*sizeof(Caracteristicas *));

    doc->crts[doc->qtdPalavras-1] = InicializaCaracteristicas(doc->crts[doc->qtdPalavras], posPalavra, freqPalavra, tf_idf);
}

void ImprimeDoc(Documento *doc) 
{
    int i;
 
    for (i = 0; i < doc->qtdPalavras; i++)
    {
        ImprimeCaracteristicas(doc->crts[i]);
    }
    
    // printf("nome: %s - classe: %s\n", doc->nome, doc->classe);
}

void LiberaDoc(Documento *doc)
{
    int i;

    for (i = 0; i < doc->qtdPalavras; i++)
    {
        LiberaCaracteristicas(doc->crts[i]);
    }
    
    free(doc->crts);
    free(doc->nome);
    free(doc->classe);

    free(doc);
}