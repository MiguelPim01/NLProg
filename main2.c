#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    char caminho[100], texto[100], *token;
    caminho[0]='\0'; texto[0]='\0';

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
        scanf("%[^\n]", texto);

        token = strtok(texto, " ");

        while (token)
        {
            AdicionaPalavraBuscada(palavrasBuscadas, RetornaArrayPalavras(indices), token);

            token = strtok(NULL, " ");
        } // Constroi array de de ponteiros para as palavras digitadas

        arrayB = InicializaArrayBusca();

        CriaArrayDeBusca_IndxPalavras(RetornaArrayPalavras(indices), arrayB, RetornaIndiceDocs(indices));

        OrdenaArrayBusca(arrayB);

        PrintaResultadoDaBusca(arrayB);

    // LIBERANDO MEMORIA:
    LiberaIndices(indices);
    LiberaIndicePalavrasBuscadas(palavrasBuscadas);
    LiberaArrayBusca(arrayB);

    // FECHANDO ARQUIVO:
    fclose(fileBin);


    return 0;
}