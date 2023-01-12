#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/caracteristicas.h"
#include "../headers/indiceDoc.h"

struct palavra {
    char *palavra;
    Caracteristicas **c;
    int qtdAparicoes;
    double tfidf;
};