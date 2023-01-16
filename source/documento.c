#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/documento.h"
#include "../headers/caracteristicas.h"

struct documento {
    char *nome, *classe;
    Caracteristicas **c;
};

void AtribuiNomeClasse(Documento *doc, char *nome, char *classe)
{
    int tamNome = strlen(nome)+1;
    int tamClasse = strlen(classe)+1;
    printf("nome: %s - classe: %s\n", nome, classe);
    printf("tam %d - %d\n", tamNome, tamClasse);

    // SEG FAULT AQUI (??????????????????)
    doc->nome = (char *)malloc(tamNome*sizeof(char));
    doc->classe = (char *)malloc(tamClasse*sizeof(char));

    printf("----------------------------\n");

    strncpy(doc->nome, nome, tamNome);
    strncpy(doc->classe, classe, tamClasse);
}

void ImprimeDoc(Documento *doc) {
    printf("nome: %s - classe: %s\n", doc->nome, doc->classe);
}

void LiberaDoc(Documento *doc)
{
    free(doc->nome);
    free(doc->classe);
}