#include <stdio.h>
#include <string.h>

#include "../headers/indiceDocs.h"
#include "../headers/indicePalavras.h"
#include "../headers/indices.h"

int main(int argc, char *argv[])
{
    FILE *fileTxt, *fileIndice;
    Indices *indices = NULL;

    char caminho[300];
    char caminhoTxt[310];
    caminho[0] = '\0'; caminhoTxt[0] = '\0';

    int tamArg = 0;

    if (argc <= 2)
    {
        printf("ERRO: Não foram informados todos os caminhos necessários para os arquivos.\n");
        printf("PARA RODAR CORRETAMENTE DIGITE: <executavel> <caminho_para_'train.txt'> <nome_arquivo_saida.bin>\n");
        return 1;
    }

    // Obtem caminho até a pasta train
    tamArg = strlen(argv[1])-4;
    strncpy(caminho, argv[1], tamArg);

    // Obtem caminho até o arquivo train.txt
    sprintf(caminhoTxt, "%s.txt", caminho);

    fileTxt = fopen(caminhoTxt, "r");

    if (fileTxt == NULL)
    {
        printf("ERRO: Não foi possível abrir o arquivo com o caminho %s.\n", caminhoTxt);
        return 1;
    }

    // PASSO 1 (Ler os arquivos de noticias e criar os vetores de palavra e documento):

    indices = CarregaIndices(fileTxt, indices, caminho);

    // Abrindo o arquivo de saida do programa (indice)
    sprintf(caminho, "%s", argv[2]);
    fileIndice = fopen(caminho, "wb");

    if (fileIndice == NULL)
    {
        printf("ERRO: Não foi possível abrir o arquivo com o caminho %s.\n", caminho);
        return 1;
    }

    // PASSO 2 (Salvar vetores em um arquivo binario):

    LiberaIndices(indices);

    fclose(fileTxt);
    fclose(fileIndice);

    return 0;
}