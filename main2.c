#include <stdio.h>
#include <stdlib.h>

#include "headers/indices.h"
#include "headers/palavra.h"
#include "headers/indicePalavras.h"
#include "headers/arrayBusca.h"

int main(int argc, char *argv[])
{
    FILE *fileBin;
    Indices *indices = NULL;
    IndicePalavras *palavrasBuscadas = NULL;
    ArrayBusca *arrayB = NULL;

    char caminho[100], pal[50];
    caminho[0]='\0'; pal[0]='\0';

    if (argc <= 2)
    {
        printf("ERRO: Quantidade insuficiente de argumentos dados\n");
        printf("Para rodar corretamente: ./prog2 <arquivo_indices.bin> <numero_K>\n");
        return 1;
    }

    sprintf(caminho, "%s", argv[1]);
    fileBin = fopen(caminho, "rb");

    if (fileBin == NULL)
    {
        printf("ERRO: Não foi possivel abrir o arquivo %s\n", caminho);
        return 1;
    }

    // LENDO E ARMAZENANDO OS INDICES DE DOCS E PALAVRAS:
    indices = CarregaIndicesBin(indices, fileBin);

    // 1 - BUSCAR NOTICIAS:
        while (scanf("%s", pal) == 1)
        {
            scanf("%*c");

            AdicionaPalavraBuscada(palavrasBuscadas, RetornaArrayPalavras(indices), pal);
        } // Constroi array de de ponteiros para as palavras digitadas

        arrayB = InicializaArrayBusca();




    // LIBERANDO MEMORIA:
    LiberaIndices(indices);
    LiberaIndicePalavrasBuscadas(palavrasBuscadas);

    // FECHANDO ARQUIVO:
    fclose(fileBin);


    return 0;
}