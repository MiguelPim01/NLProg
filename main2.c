#include <stdio.h>
#include <stdlib.h>

#include "headers/indices.h"
#include "headers/palavra.h"
#include "headers/indicePalavras.h"

int main(int argc, char *argv[])
{
    FILE *fileBin;
    Indices *indices = NULL;
    Palavra **palavraBuscada = NULL;

    char texto[100], caminho[100];
    texto[0]='\0'; caminho[0]='\0';

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

    // ImprimePalavras(RetornaArrayPalavras(indices));

    // TESTANDO A FUNCAO bsearch:
    scanf("%[^\n]", texto);
    scanf("%*c");
    printf("palavra digitada -> %s\n", texto);

    palavraBuscada = BuscaPalavra(RetornaArrayPalavras(indices), texto);

    if (palavraBuscada == NULL)
    {
        printf("Essa palavra nao existe no indice!\n");
    }
    else 
    {
        ImprimePalavra(*palavraBuscada);
    }

    // LIBERANDO MEMORIA:
    LiberaIndices(indices);

    fclose(fileBin);


    return 0;
}