#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "caracteristicas.h"
#include "indiceDoc.h"

struct palavra {
    char *palavra;
    Caracteristicas **c;
    int qtdAparicoes;
    double tfidf;
};