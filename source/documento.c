#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../headers/documento.h"
#include "../headers/caracteristicas.h"

#define TAMANHO_NOME_CLASSIFICADOR 0
#define TAMANHO_CLASSE_CLASSIFICADOR 4
#define FREQUENCIA_DEFAULT_CLASSIFICADOR 0
#define TF_IDF_DEFAULT_CLASSIFICADOR 0

struct documento {
    char *nome, *classe;
    Caracteristicas **crts;
    int qtdPalavras;
    int somaFreq;
};

Documento * AlocaDocumento(int tamNome, int tamClasse)
{
    Documento *doc = (Documento *)malloc(sizeof(Documento));

    doc->nome = (char *)malloc(tamNome*sizeof(char));
    doc->classe = (char *)malloc(tamClasse*sizeof(char));
    doc->crts = NULL;
    doc->qtdPalavras = 0;
    doc->somaFreq = 0;

    return doc;
}

Documento * AtribuiNomeClasse(Documento *doc, char *nome, char *classe)
{
    int tamNome = strlen(nome)+1;
    int tamClasse = strlen(classe)+1;

    doc = AlocaDocumento(tamNome, tamClasse);

    strncpy(doc->nome, nome, tamNome);
    strncpy(doc->classe, classe, tamClasse);

    return doc;
}

void AtribuiCaracDoc(Documento *doc, int posPalavra, int freqPalavra, double tf_idf)
{   
    doc->qtdPalavras++;
    doc->crts = (Caracteristicas **)realloc(doc->crts, doc->qtdPalavras*sizeof(Caracteristicas *));

    doc->crts[doc->qtdPalavras-1] = InicializaCaracteristicas(doc->crts[doc->qtdPalavras-1], posPalavra, freqPalavra, tf_idf);
}

void SalvaDocBin(Documento *doc, FILE *f)
{
    int tamNome = strlen(doc->nome)+1;
    int tamClasse = strlen(doc->classe)+1;

    fwrite(&tamNome, sizeof(int), 1, f); // TAMANHO NOME
    fwrite(&tamClasse, sizeof(int), 1, f); // TAMANHO CLASSE

    for (int i = 0; i < tamNome; i++)
    {
        fwrite(&doc->nome[i], sizeof(char), 1, f); // NOME
    }
    for (int i = 0; i < tamClasse; i++)
    {
        fwrite(&doc->classe[i], sizeof(char), 1, f); // CLASSE
    }

    fwrite(&doc->qtdPalavras, sizeof(int), 1, f); // QTD_PALAVRAS

    for (int i = 0; i < doc->qtdPalavras; i++)
    {
        SalvaCaracteristicasBin(doc->crts[i], f); // CARACTERISTICAS
    }
}

Documento * CarregaDocBin(Documento *doc, FILE *f)
{
    int tamNome=0, tamClasse=0;

    fread(&tamNome, sizeof(int), 1, f); // TAMANHO NOME
    fread(&tamClasse, sizeof(int), 1, f); // TAMANHO CLASSE

    doc = AlocaDocumento(tamNome, tamClasse);

    // Lendo o nome
    for (int i = 0; i < tamNome; i++)
    {
        fread(&doc->nome[i], sizeof(char), 1, f); // NOME
    }

    // Lendo a classe
    for (int i = 0; i < tamClasse; i++)
    {
        fread(&doc->classe[i], sizeof(char), 1, f); // CLASSE
    }

    fread(&doc->qtdPalavras, sizeof(int), 1, f); // QTD_PALAVRAS

    doc->crts = (Caracteristicas **)malloc(doc->qtdPalavras*sizeof(Caracteristicas *));

    for (int i = 0; i < doc->qtdPalavras; i++)
    {
        doc->crts[i] = CarregaCaracteristicasBin(doc->crts[i], f); // CARACTERISTICAS
    }

    return doc;
}

void ImprimeDoc(Documento *doc) 
{
    printf("Nome: %s Classe: %s\n", doc->nome, doc->classe);
 
    /*for (int i = 0; i < doc->qtdPalavras; i++)
    {
         ImprimeCaracteristicas(doc->crts[i]);
    }*/
}

void LiberaDoc(Documento *doc)
{
    for (int i = 0; i < doc->qtdPalavras; i++)
    {
        LiberaCaracteristicas(doc->crts[i]);
    }
    
    free(doc->crts);
    free(doc->nome);
    free(doc->classe);

    free(doc);
}

int DocsSaoIguais(Documento *doc1, Documento *doc2)
{
    if (doc1 == doc2)
    {
        return 1;
    }

    return 0;
}

Documento * InicializaDocumento_classificador()
{
    Documento *doc = NULL;
    char nome[1], classe[4]={'0', '0', '0'};
    nome[0]='\0';

    doc = AtribuiNomeClasse(doc, nome, classe);

    return doc;
}

double ObtemSomaTF_IDFs(Documento *doc)
{
    int i = 0;
    double somatorio = 0;

    for (i = 0; i < doc->qtdPalavras; i++)
    {
        somatorio = sqrt(pow(ObtemTF_IDF(doc->crts[i]), 2));
    }

    return somatorio;
}

double CalculaCosseno(Documento *doc1, Documento *doc2, double somatorio_doc2)
{
    double somatorio_doc1 = ObtemSomaTF_IDFs(doc1);
    double soma_numerador = 0, resultado = 0, denominador = 0;

    int i = 0, q = 0;

    for (i = 0 ; i < doc1->qtdPalavras; i++)
    {
        for (q = 0; q < doc2->qtdPalavras; q++)
        {
            if (ObtemPosicao(doc1->crts[i]) == ObtemPosicao(doc2->crts[q]))
            {
                soma_numerador += (ObtemTF_IDF(doc1->crts[i])*ObtemTF_IDF(doc2->crts[q]));
            }
        }
    }

    denominador = somatorio_doc1*somatorio_doc2;

    if (denominador == 0)
    {
        return 0;
    }

    resultado = soma_numerador/denominador;

    return resultado;
}

char * ObtemClasse(Documento *doc)
{
    return doc->classe;
}

Documento * CopiaDoc(Documento *doc, Documento *Rdoc)
{
    Rdoc = AtribuiNomeClasse(Rdoc, doc->nome, doc->classe);

    for (int i = 1; i <= doc->qtdPalavras; i++)
    {
        CopiaCaracDoc(doc->crts[i-1], Rdoc);
    }

    return Rdoc;
}

void AtribuiSomaDasFrequencias_Doc(Documento *doc, Documento *Rdoc)
{
    Rdoc->somaFreq = SomaFrequenciasDoc(doc);
}

int SomaFrequenciasDoc(Documento *doc)
{
    int i, soma = 0;

    for (i = 0; i < doc->qtdPalavras; i++)
    {
        soma += RetornaFrequencia(doc->crts[i]);   
    }

    return soma;
}

int PelaSomaFrequenciaCresc(const void *a, const void *b)
{
    const Documento **doc1 = (const Documento **)a;
    const Documento **doc2 = (const Documento **)b;

    return (*doc1)->somaFreq - (*doc2)->somaFreq;
}

int PelaSomaFrequenciaDecresc(const void *a, const void *b)
{
    const Documento **doc1 = (const Documento **)a;
    const Documento **doc2 = (const Documento **)b;

    return (*doc2)->somaFreq - (*doc1)->somaFreq;
}

int RetornaNumeroPalavras(Documento *doc)
{
    return doc->somaFreq;
}