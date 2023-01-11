#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "caracteristicas.h"
#include "indicePalavras.h"

struct documento {
    char *nome, *classe;
    Caracteristicas **c;
};