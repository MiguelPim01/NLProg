#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/indices.h"

int main(int argc, char *argv[])
{
    FILE *fileBin, *fileTest, *fileSaida;
    
    Indices *indicesTrain = NULL, *indicesTeste = NULL;

    char caminho[100], caminhoPasta[100], **classesDeduzidas = NULL, **classesVerdadeiras = NULL;
    caminho[0]='\0'; caminhoPasta[0]='\0';

    int tamCaminho=0, K=0;
    
    if (argc <= 4)
    {
        printf("ERRO: Quantidade de argumentos dados invalido!\n");
        printf("Para rodar corretamente: ./prog3 <arquivo_indices.bin> <caminho_teste.txt> <numero_K> <nome_arquivo_saida>\n");
        return 1;
    }

    sscanf(argv[3], "%d", &K);
    if (K <= 0)
    {
        printf("ERRO: Valor de K dado é invalido. Digite um numero inteiro positivo!\n");
        return 1;
    }

    sprintf(caminho, "%s", argv[1]);
    fileBin = fopen(caminho, "rb");

    if (fileBin == NULL)
    {
        printf("ERRO: Nao foi possivel abrir o arquivo %s\n", caminho);
        return 1;
    }

    // LENDO O ARQUIVO BINARIO E ARMAZENANDO OS INDICES
    indicesTrain = CarregaIndicesBin(indicesTrain, fileBin);

    sprintf(caminho, "%s", argv[2]);
    fileTest = fopen(caminho, "r");

    tamCaminho = strlen(caminho)-4;
    strncpy(caminhoPasta, caminho, tamCaminho);
    caminhoPasta[tamCaminho] = '\0';

    // LENDO O ARQUIVO test.txt E ARMAZENANDO OS INDICES
    indicesTeste = CarregaIndices(fileTest, indicesTeste, caminhoPasta);

    
    // FUNCIONAMENTO DO PROGRAMA:

    // LENDO ARQUIVO DE SAIDA
    sprintf(caminho, "%s", argv[4]);
    fileSaida = fopen(caminho, "w");

    classesDeduzidas = CriaArrayClassesDeduzidas(RetornaIndiceDocs(indicesTrain), RetornaIndiceDocs(indicesTeste), K);
    classesVerdadeiras = CriaArrayClassesVerdadeiras(RetornaIndiceDocs(indicesTeste), K);

    GeraMatrizConfusao(indicesTeste, classesVerdadeiras, classesDeduzidas, fileSaida);

    // LIBERANDO MEMORIA
    free(classesDeduzidas);
    free(classesVerdadeiras);
    LiberaIndices(indicesTeste);
    LiberaIndices(indicesTrain);
    fclose(fileBin);
    fclose(fileTest);
    fclose(fileSaida);

    return 0;
}