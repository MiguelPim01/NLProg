#ifndef INDICEDOCS_H
#define INDICEDOCS_H

#include "documento.h"

typedef struct indiceDocs IndiceDocs;

// Armazena no indice de docs o nome e classe de cada um dos documentos
IndiceDocs * AtribuiNomeClasseIndiceDocs(IndiceDocs *docs, char *caminho, char *classe);

// Inicializa variaveis e aloca espaço inicial para indice de documentos
IndiceDocs * InicializaIndiceDocs(IndiceDocs *docs);

// Retorna quantidade de documentos que existem no indice
int ObtemQtdDocumentos(IndiceDocs *docs);

// Printa documentos
void ImprimeDocs(IndiceDocs *docs);

// Retorna ponteiro para um documento especifico
Documento * AchaDocumento(IndiceDocs *docs, int posDocumento);

// Salva o indice do documentos em binario
void SalvaIndiceDocsBin(IndiceDocs *docs, FILE *f);

// Realiza a leitura do indice de documentos em binario
IndiceDocs * CarregaIndiceDocsBin(IndiceDocs *docs, FILE *f);

// Libera o indice de documentos da memoria
void LiberaIndiceDocs(IndiceDocs *docs);

// Retorna um array de cossenos dados um documento para comparação com o indice de documentos
double * CriaArrayCossenos(IndiceDocs *docs, Documento *doc);

// Faz a copia de um array de double para outro
void AtribuiArrayDouble(double *a, double *b, int tam);

// Funcao de comparação utilizada pelo qsort para ordenar os cossenos em ordem decrescente
int OrdenaCossenos(const void *a, const void *b);

// Funcao utilizada pelo qosrt para ordenar um array de classes em ordem alfabetica
int OrdenaStrings(const void *a, const void *b);

// Recebe um documento, arra de cossenos, o numero K e retorna a classe que ele foi classificada 
char * ClassificaNoticia(double *cossenos, IndiceDocs *docs, int K);

// Faz a copia de um indice de documentos para outro
IndiceDocs * CopiaIndiceDocs(IndiceDocs *docs, IndiceDocs *Rdocs);


void AtribuiSomaDasFrequencias_Indice(IndiceDocs *docs, IndiceDocs *Rdocs);

// Ordena relatorio de documentos ou em ordem crescente ou decrescente
void OrdenaRelatorioDocs(IndiceDocs *Rdocs, int flagOrdem);

// Imprime Relatorio de documentos
void ImprimeRelatorioDocs(IndiceDocs *Rdocs, int flagOrdem);


void ImprimeDocsPorIndice(IndiceDocs *docs, int *arrayIndicesInt);

// Retorna array de todas as classes que foram deduzidas pelo classificador
char ** CriaArrayClassesDeduzidas(IndiceDocs *docsTrain, IndiceDocs *docsTeste, int K);

// Retorna um array de todas as classes verdadeiras lidas da entrada
char ** CriaArrayClassesVerdadeiras(IndiceDocs *docsTeste, int K);

// Recebe um array de classes e retorna um array sem classes repetidas
char ** ObtemClassesUnicas(char **classesUnicas, char **classesVerdadeiras, int qtdDocs, int *qtdClasses);

// Retorna a posicao de uma classe no array de classes verdadeiras
int ObtemPosicaoClasse(char *classe, char **classesUnicas, int qtdClasses);

#endif