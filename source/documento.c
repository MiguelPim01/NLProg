#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/caracteristicas.h"
#include "../headers/indicePalavras.h"

struct documento {
    char *nome, *classe;
    Caracteristicas **c;
};