#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fileBin;

    if (argc <= 2)
    {
        printf("ERRO: Quantidade insuficiente de argumentos dados\n");
        printf("Para rodar corretamente: ./prog2 <arquivo_indices.bin> <numero_K>");
        return 1;
    }
}