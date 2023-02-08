#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/indiceDocs.h"
#include "../headers/documento.h"
#include "../headers/caracteristicas.h"

#define QTD_INICIAL_CLASSES_ALLOC 10

struct indiceDocs {
    Documento **arrayDocs;
    int qtdDocs;
};

IndiceDocs * AlocaIndxDocumentos()
{
    IndiceDocs *docs = (IndiceDocs *)malloc(sizeof(IndiceDocs));

    int mult = 10;
    docs->arrayDocs = (Documento **)malloc(mult*sizeof(Documento *));

    return docs;
}

IndiceDocs * InicializaIndiceDocs(IndiceDocs *docs) 
{
    docs = AlocaIndxDocumentos();

    docs->qtdDocs = 0;

    return docs;
}

IndiceDocs * AtribuiNomeClasseIndiceDocs(IndiceDocs *docs, char *caminho, char *classe)
{
    static int mult = 10;

    // Formata o caminho como nome do documento
    char nome[50];
    nome[0] = '\0';

    sscanf(caminho, "%*[/]%s", nome);

    docs->arrayDocs[docs->qtdDocs] = AtribuiNomeClasse(docs->arrayDocs[docs->qtdDocs], nome, classe);
    
    docs->qtdDocs++;

    if (docs->qtdDocs >= mult)
    {
        mult *=2;
        docs->arrayDocs = (Documento **)realloc(docs->arrayDocs, mult*sizeof(Documento *));
    }

    return docs;
}

int ObtemQtdDocumentos(IndiceDocs *docs)
{
    return docs->qtdDocs;
}

void ImprimeDocs(IndiceDocs *docs)
{
    // int i;

    printf("Número de documentos: %d\n", docs->qtdDocs);
    /*for (i = 0; i < docs->qtdDocs; i++)
    {
        printf("doc %d: ", i);
        ImprimeDoc(docs->arrayDocs[i]);
    }*/
}

Documento * AchaDocumento(IndiceDocs *docs, int posDocumento)
{
    return docs->arrayDocs[posDocumento];
}

void SalvaIndiceDocsBin(IndiceDocs *docs, FILE *f)
{
    fwrite(&docs->qtdDocs, sizeof(int), 1, f);
    
    for (int i = 0; i < docs->qtdDocs; i++)
    {
        SalvaDocBin(docs->arrayDocs[i], f);
    }
}

IndiceDocs * CarregaIndiceDocsBin(IndiceDocs *docs, FILE *f)
{   
    docs = (IndiceDocs *)malloc(sizeof(IndiceDocs));

    fread(&docs->qtdDocs, sizeof(int), 1, f);

    docs->arrayDocs = (Documento **)malloc(docs->qtdDocs*sizeof(Documento *)); // Alocando espaço exato para os ponteiros de documento

    for (int i = 0; i < docs->qtdDocs; i++)
    {
        docs->arrayDocs[i] = CarregaDocBin(docs->arrayDocs[i], f);
    }

    return docs;
}

void LiberaIndiceDocs(IndiceDocs *docs)
{
    for (int i = 0; i < docs->qtdDocs; i++)
    {
        LiberaDoc(docs->arrayDocs[i]);
    }
    
    free(docs->arrayDocs);
    free(docs);
}

double * CriaArrayCossenos(IndiceDocs *docs, Documento *doc)
{
    int i = 0;
    double *cossenos, somatorio = 0;

    somatorio = ObtemSomaTF_IDFs(doc);

    cossenos = (double *)malloc(docs->qtdDocs*sizeof(double));

    for (i = 0; i < docs->qtdDocs; i++)
    {
        cossenos[i] = CalculaCosseno(docs->arrayDocs[i], doc, somatorio);
    }

    return cossenos;
}

void AtribuiArrayDouble(double *a, double *b, int tam)
{
    int i;

    for (i = 0; i < tam; i++)
    {
        b[i] = a[i];
    }
}

int OrdenaCossenos(const void *a, const void *b)
{
    double *cos1 = (double *)a;
    double *cos2 = (double *)b;

    return ((*cos2) - (*cos1));
}

int OrdenaStrings(const void *a, const void *b)
{
    const char **classe1 = (const char **)a;
    const char **classe2 = (const char **)b;

    return strcmp(*(classe1), *(classe2));
}

char * DeduzClasse(int K, Documento **docs)
{
    char **VetorClasses = NULL, *classe = NULL;
    int tamVetor = 0, flagAddChar = 0, *arrayCont = NULL, i, q;

    for (i = 0; i < K; i++)
    {
        classe = ObtemClasse(docs[i]);

        for (q = 0; q < tamVetor; q++)
        {
            if (VetorClasses[q] == classe)
            {
                flagAddChar = 1;
                arrayCont[q]++;
            }
        }

        if (flagAddChar == 0)
        {
            tamVetor++;

            VetorClasses = (char **)realloc(VetorClasses, tamVetor*sizeof(char *));
            arrayCont = (int *)realloc(arrayCont, tamVetor*sizeof(int));
            
            arrayCont[tamVetor-1] = 0;
            VetorClasses[tamVetor-1] = classe;
        }

        flagAddChar = 0;
    }

    int maior = 0;

    for (i = 0; i < tamVetor; i++)
    {
        if (!i) maior = i;
        else
        {
            if (arrayCont[i] > arrayCont[maior])
            {
                maior = i;
            }
        }
    }
    classe = VetorClasses[maior];

    free(VetorClasses);
    free(arrayCont);

    return classe;
}

char * ClassificaNoticia(double *cossenos, IndiceDocs *docs, int K)
{
    double *AuxCossenos = (double *)malloc(docs->qtdDocs*sizeof(double));
    Documento **AuxClassificador = NULL;
    char *classe;

    if (K > docs->qtdDocs)
    {
        K = docs->qtdDocs;
    }

    AuxClassificador = (Documento **)malloc(K*sizeof(Documento *));

    AtribuiArrayDouble(cossenos, AuxCossenos, docs->qtdDocs);
    qsort(AuxCossenos, docs->qtdDocs, sizeof(double), OrdenaCossenos);

    int i, q;

    for (i = 0; i < K; i++)
    {
        for (q = 0; q < docs->qtdDocs; q++)
        {
            if (AuxCossenos[i] == cossenos[q])
            {
                AuxClassificador[i] = docs->arrayDocs[q];
            }
        }
    }

    classe = DeduzClasse(K, AuxClassificador);

    free(AuxClassificador);
    free(AuxCossenos);

    return classe;
}

IndiceDocs * CopiaIndiceDocs(IndiceDocs *docs, IndiceDocs *Rdocs)
{
    int mult = 10;

    for (int i = 0; i < docs->qtdDocs; i++)
    {
        Rdocs->arrayDocs[i] = CopiaDoc(docs->arrayDocs[i], Rdocs->arrayDocs[i]);
        Rdocs->qtdDocs++;

        if (Rdocs->qtdDocs >= mult)
        {
            mult *=2;
            Rdocs->arrayDocs = (Documento **)realloc(Rdocs->arrayDocs, mult*sizeof(Documento *));
        }
    }

    return Rdocs;
}

void AtribuiSomaDasFrequencias_Indice(IndiceDocs *docs, IndiceDocs *Rdocs)
{
    for (int i = 0; i < docs->qtdDocs; i++)
    {
        AtribuiSomaDasFrequencias_Doc(docs->arrayDocs[i], Rdocs->arrayDocs[i]);
    }
}

void OrdenaRelatorioDocs(IndiceDocs *Rdocs, int flagOrdem)
{
    if (flagOrdem)
    {
        qsort(Rdocs->arrayDocs, Rdocs->qtdDocs, sizeof(Documento *), PelaSomaFrequenciaCresc);
    } else {
        qsort(Rdocs->arrayDocs, Rdocs->qtdDocs, sizeof(Documento *), PelaSomaFrequenciaDecresc);
    }
}

void ImprimeRelatorioDocs(IndiceDocs *Rdocs, int flagOrdem)
{
    if (flagOrdem)
    {
        printf("\nDOCUMENTOS MAIS CURTOS:\n\n");
    } else {
        printf("\nDOCUMENTOS MAIS LONGOS:\n\n");
    }

    for (int i = 0; i < 10; i++)
    {
        printf("%d - ", i+1);
        ImprimeDoc(Rdocs->arrayDocs[i]);
        printf("Número de palavras: %d\n", RetornaNumeroPalavras(Rdocs->arrayDocs[i]));
        printf("\n");
    }
    printf("-----------------------------\n");
}

void ImprimeDocsPorIndice(IndiceDocs *docs, int *arrayIndicesInt)
{
    int i = 0;

    while (i < 10 && arrayIndicesInt[i] != -1)
    {
        printf("%d - ", i+1);
        ImprimeDoc(docs->arrayDocs[arrayIndicesInt[i]]);
        printf("\n");
        i++;
    }
}

char ** CriaArrayClassesDeduzidas(IndiceDocs *docsTrain, IndiceDocs *docsTeste, int K)
{
    char **arrayClassesDeduzidas = NULL, *classe = NULL;
    double *cossenos = NULL;
    int i;

    arrayClassesDeduzidas = (char **)malloc(docsTeste->qtdDocs*sizeof(char *));

    for (i = 0; i < docsTeste->qtdDocs; i++)
    {
        cossenos = CriaArrayCossenos(docsTrain, docsTeste->arrayDocs[i]);
        classe = ClassificaNoticia(cossenos, docsTrain, K);

        arrayClassesDeduzidas[i] = classe;
        free(cossenos);
    }

    return arrayClassesDeduzidas;
}

char ** CriaArrayClassesVerdadeiras(IndiceDocs *docsTeste, int K)
{
    char **arrayClassesVerdadeiras = NULL, *classe = NULL;
    int i;

    arrayClassesVerdadeiras = (char **)malloc(docsTeste->qtdDocs*sizeof(char *));

    for (i = 0; i < docsTeste->qtdDocs; i++)
    {
        classe = ObtemClasse(docsTeste->arrayDocs[i]);

        arrayClassesVerdadeiras[i] = classe;
    }

    return arrayClassesVerdadeiras;
}

char ** ObtemClassesUnicas(char **classesUnicas, char **classesVerdadeiras, int qtdDocs, int *qtdClasses)
{
    int i, j, contador = 0, mult = QTD_INICIAL_CLASSES_ALLOC;

    classesUnicas = (char **)malloc(mult*sizeof(char *));
    
    for (i = 0; i < qtdDocs; i++)
    {
        int flagClasse = 0;
        for (j = 0; j < contador; j++)
        {
            if (!strcmp(classesVerdadeiras[i], classesUnicas[j]))
            {
                flagClasse = 1;
                break;
            }
        }
        if (!flagClasse)
        {
            classesUnicas[contador] = classesVerdadeiras[i];
            contador++;
        }
        if (contador >= mult)
        {
            mult *= 2;
            classesUnicas = (char **)realloc(classesUnicas, mult*sizeof(char *));
        }
    }
    *qtdClasses = contador;

    return classesUnicas;
}

int ObtemPosicaoClasse(char *classe, char **classesUnicas, int qtdClasses)
{
    for (int i = 0; i < qtdClasses; i++)
    {
        if (!strcmp(classe, classesUnicas[i]))
        {
            return i;
        }
    }
    return -1;
}