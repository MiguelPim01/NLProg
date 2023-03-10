#include <stdio.h>
#include <string.h>

#include "headers/indiceDocs.h"
#include "headers/indicePalavras.h"
#include "headers/indices.h"

int main(int argc, char *argv[]) 
{
    FILE *fileTxt, *fileIndices;
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
    sprintf(caminhoTxt, "%s", argv[1]); // copia argv para 'caminhoTxt'

    tamArg = strlen(caminhoTxt)-4; // diminui 4 do tamanho para nao considerar o '.txt'

    strncpy(caminho, caminhoTxt, tamArg); // copia o caminho sem o '.txt' para 'caminho'
    caminho[tamArg] = '\0';

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
    fileIndices = fopen(caminho, "wb");

    if (fileIndices == NULL)
    {
        printf("ERRO: Não foi possível abrir o arquivo com o caminho %s.\n", caminho);
        return 1;
    }

    // PASSO 2 (Salvar vetores em um arquivo binario):
    SalvaIndices(indices, fileIndices);

    LiberaIndices(indices);

    fclose(fileTxt);
    fclose(fileIndices);

    return 0;
}