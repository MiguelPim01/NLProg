#include <stdio.h>

#include "../headers/indiceDoc.h"
#include "../headers/indicePalavras.h"

int main(int argc, char *argv[])
{
    FILE *fileTxt, *fileIndice;
    char caminho[100];

    if (argc <= 2)
    {
        printf("ERRO: Não foram informados todos os caminhos necessários para os arquivos.\n");
        printf("PARA RODAR CORRETAMENTE DIGITE: <executavel> <caminho_para_'train.txt'> <nome_arquivo_saida.bin>\n");
        return 1;
    }

    // Abrindo o arquivo dos nomes dos arquivos (train.txt)
    sprintf(caminho, "%s", argv[1]);
    fileTxt = fopen(caminho, "r");

    if (fileTxt == NULL)
    {
        printf("ERRO: Não foi possível abrir o arquivo com o caminho %s.\n", caminho);
        return 1;
    }

    // PASSO 1 (Ler os arquivos de noticias e criar os vetores de palavra e documento):

    // Arbindo o arquivo de saida do programa (indice)
    sprintf(caminho, "%s", argv[2]);
    fileIndice = fopen(caminho, "wb");

    if (fileIndice == NULL)
    {
        printf("ERRO: Não foi possível abrir o arquivo com o caminho %s.\n", caminho);
        return 1;
    }

    // PASSO 2 (Salvar vetores em um arquivo binario):

    fclose(fileTxt);
    fclose(fileIndice);

    return 0;
}