#include <stdio.h>
#include <stdlib.h>

#include "headers/indices.h"

int main(int argc, char *argv[])
{
    FILE *fileBin;
    Indices *indices = NULL;

    if (argc <= 2)
    {
        printf("ERRO: Quantidade insuficiente de argumentos dados\n");
        printf("Para rodar corretamente: ./prog2 <arquivo_indices.bin> <numero_K>\n");
        return 1;
    }

    char caminho[100];
    caminho[0]='\0';

    sprintf(caminho, "%s", argv[1]);
    fileBin = fopen(caminho, "rb");

    if (fileBin == NULL)
    {
        printf("ERRO: Não foi possivel abrir o arquivo %s\n", caminho);
        return 1;
    }

    indices = CarregaIndicesBin(indices, fileBin);

    LiberaIndices(indices);

    fclose(fileBin);


    return 0;
}