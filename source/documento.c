#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/documento.h"
#include "../headers/caracteristicas.h"

struct documento {
    char *nome, *classe;
    Caracteristicas **crts;
};

Documento * AlocaDocumento(int tamNome, int tamClasse)
{
    Documento *doc = (Documento *)malloc(sizeof(Documento));

    doc->nome = (char *)malloc(tamNome*sizeof(char));
    doc->classe = (char *)malloc(tamClasse*sizeof(char));

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

void ImprimeDoc(Documento *doc) {
    printf("nome: %s - classe: %s\n", doc->nome, doc->classe);
}

void LiberaDoc(Documento *doc)
{
    free(doc->nome);
    free(doc->classe);

    free(doc);
}