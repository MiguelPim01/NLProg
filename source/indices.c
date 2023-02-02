#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/indices.h"
#include "../headers/indiceDocs.h"
#include "../headers/indicePalavras.h"

#define FLAG_CLASSIFICADOR 0
#define DECRESC 0
#define CRESC 1

struct indices {
    IndiceDocs *docs;
    IndicePalavras *palavras;
};

Indices * AlocaIndices()
{
    Indices *i = (Indices *)malloc(sizeof(Indices));

    i->docs = InicializaIndiceDocs(i->docs);
    i->palavras = InicializaIndicePalavras(i->palavras);

    return i;
}

Indices * CarregaIndices(FILE *f, Indices *i, char *caminhoAux)
{
    int contDocs = 0;
    char caminhoTxt[100], caminho[100], classe[10];
    caminhoTxt[0] = '\0'; caminho[0] = '\0'; classe[0] = '\0';

    i = AlocaIndices();

    // Lê, no arquivo train.txt, os nomes dos documentos e as classes, linha por linha
    while (fscanf(f, "%*[^/]%s ", caminhoTxt) == 1)
    {
        fscanf(f, "%[^\n]", classe);
        fscanf(f, "%*c");

        // Constroi caminho para o documento
        strncpy(caminho, caminhoAux, strlen(caminhoAux)+1);
        strcat(caminho, caminhoTxt);

        // Inicializa indice de docs (nome e classe)
        i->docs = AtribuiNomeClasseIndiceDocs(i->docs, caminhoTxt, classe);

        // Cria indice de palavras
        i->palavras = AtribuiIndicePalavras(i->palavras, contDocs, caminho);

        strncpy(caminho, caminhoAux, strlen(caminhoAux)+1);

        contDocs++;
    }

    AtribuiTf_idfIdxPalavras(i->palavras, i->docs, FLAG_CLASSIFICADOR);

    OrdenaIndicePalavras(i->palavras);

    FinalizaCaracDocumentos_indxPalavras(i->palavras, i->docs);

    // ImprimeDocs(i->docs);
    // ImprimePalavras(i->palavras);

    return i;
}

void SalvaIndices(Indices *i, FILE *f)
{
    SalvaIndiceDocsBin(i->docs, f);
    SalvaIndicePalavrasBin(i->palavras, f);
}

Indices * CarregaIndicesBin(Indices *i, FILE *f)
{
    i = (Indices *)malloc(sizeof(Indices));
    
    i->docs = CarregaIndiceDocsBin(i->docs, f);
    i->palavras = CarregaIndicePalavrasBin(i->palavras, f);

    return i;
}

void LiberaIndices(Indices *i)
{
    LiberaIndiceDocs(i->docs);
    LiberaIndicePalavras(i->palavras);

    free(i);
}

IndicePalavras * RetornaIndicePalavras(Indices *i)
{
    return i->palavras;
}

IndiceDocs * RetornaIndiceDocs(Indices *i)
{
    return i->docs;
}

void GeraRelatorioDocs(Indices *i, IndiceDocs *Rdocs)
{
    Rdocs = CopiaIndiceDocs(i->docs, Rdocs);

    AtribuiSomaDasFrequencias_Indice(i->docs, Rdocs);

    OrdenaRelatorioDocs(Rdocs, CRESC);
    ImprimeRelatorioDocs(Rdocs, CRESC);

    OrdenaRelatorioDocs(Rdocs, DECRESC);
    ImprimeRelatorioDocs(Rdocs, DECRESC);
}

void GeraRelatorioPalavra(Indices *i, char *palavra)
{
    RelatorioPalavra_indxPalavra(i->palavras, i->docs, palavra);
}

void GeraMatrizConfusao(Indices *indices, char **classesVerdadeiras, char **classesDeduzidas, FILE *f)
{
    char **classesUnicas = NULL;

    int qtdDocs = ObtemQtdDocumentos(indices->docs), qtdClasses;

    // Constroi vetor de classes únicas, usado para construir a matriz de confusão
    classesUnicas = ObtemClassesUnicas(classesUnicas, classesVerdadeiras, qtdDocs, &qtdClasses);

    int j = 0;
    while (j < qtdClasses)
    {
        printf("%d - classe: %s\n", j, classesUnicas[j]);
        j++;
    }

    // Inicialização e construção da matriz de confusão
    int **matrizConfusao = NULL;
    
    matrizConfusao = InicializaMatrizConfusao(matrizConfusao, qtdClasses);

    int i, linha, coluna;
    
    for (i = 0; i < qtdDocs; i++)
    {
        linha = ObtemPosicaoClasse(classesVerdadeiras[i], classesUnicas, qtdClasses); // Obtem posição da linha, ou seja, classe verdadeira
        coluna = ObtemPosicaoClasse(classesDeduzidas[i], classesUnicas, qtdClasses); // Obtem posição da coluna, ou seja, classe deduzida;
        matrizConfusao[linha][coluna]++;
    }

    ImprimeMatrizConfusao(matrizConfusao, qtdClasses, classesUnicas, f);

    double acuracia = CalculaAcuracia(matrizConfusao, qtdClasses, qtdDocs);
    fprintf(f, "Acurácia: %.2lf%%\n", acuracia*100);

    LiberaMatrizConfusao(matrizConfusao, qtdClasses);
    free(classesUnicas);
}

void ImprimeMatrizConfusao(int **matriz, int qtdClasses, char **classes, FILE *f) {
    int i, j;

    fprintf(f, "    ");
    for (i = 0; i < qtdClasses; i++)
    {
        fprintf(f, " %s ", classes[i]);
    }
    fprintf(f, "\n");

    for (i = 0; i < qtdClasses; i++)
    {
        fprintf(f, "%s  ", classes[i]);
        for (j = 0; j < qtdClasses; j++)
        {
            fprintf(f, "%d", matriz[i][j]);
            for (int k = 0; k < 4-(matriz[i][j]/10); k++) fprintf(f, " "); // Formata matriz saída
        }
        fprintf(f, "\n");
    }
    fprintf(f, "\n");
}

int ** InicializaMatrizConfusao(int **matriz, int qtdClasses)
{
    matriz = AlocaMatrizConfusao(matriz, qtdClasses);

    for (int i = 0; i < qtdClasses; i++)
    {
        for (int j = 0; j < qtdClasses; j++)
        {
            matriz[i][j] = 0;
        }
    }

    return matriz;
}

int ** AlocaMatrizConfusao(int **matriz, int qtdClasses)
{
    matriz = (int **)malloc(qtdClasses*sizeof(int *));

    for (int i = 0; i < qtdClasses; i++)
    {
        matriz[i] = (int *)malloc(qtdClasses*sizeof(int));
    }

    return matriz;
}

double CalculaAcuracia(int **matriz, int qtdClasses, int qtdDocs)
{
    int i;
    double somatorio = 0.0, acuracia;

    for (i = 0; i < qtdClasses; i++)
    {
        somatorio += matriz[i][i];
    }
    acuracia = somatorio/qtdDocs;

    printf("CU %lf\n", acuracia);
    return acuracia;
}

void LiberaMatrizConfusao(int **matriz, int qtdClasses)
{
    for (int i = 0; i < qtdClasses; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}