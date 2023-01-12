#include <stdio.h>

#include "indiceDoc.h"
#include "indicePalavras.h"

int main(int argc, char *argv[])
{
    FILE *fileTxt, *fileIndice;
    char caminho[100];

    if (argc <= 2)
    {
        printf("Não foram informados todos os caminhos necessários para os arquivos.\n");
        return 1;

    }

    // Abrindo o arquivo dos nomes dos arquivos (teste.txt)
    sprintf(caminho, "%s", argv[1]);
    fileTxt = fopen(caminho, "r");

    if (fileTxt == NULL)
    {
        printf("Não foi possível abrir o arquivo com o caminho %s.\n", caminho);
        return 1;
    }

    sprintf(caminho, "%s", argv[2]);
    fileIndice = fopen(caminho, "wb");

    if (fileIndice == NULL)
    {
        printf("Não foi possível abrir o arquivo com o caminho %s.\n", caminho);
        return 1;
    }

    fclose(fileTxt);
    fclose(fileIndice);

    return 0;
}