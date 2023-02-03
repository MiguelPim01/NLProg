#ifndef PALAVRA_H
#define PALAVRA_H

#include <stdio.h>

#include "arrayBusca.h"
#include "indiceDocs.h"

typedef struct palavra Palavra;

// Aloca memória para a struct palavra, recebe o tamanho da palavra como argumento e retorna a palavra
Palavra * AlocaPalavra(int tamPalavra);

// Aloca memória para uma struct palavra especificamente para o buscador de noticias
Palavra * AlocaPalavra_auxBusca(char *palavra);

// Libera espaço alocado para palavras alocadas no buscador
void LiberaPalavra_auxBusca(Palavra *p);

// Inicializa palavra assim que ela aparece na leitura de documentos pela primeira vez
Palavra * InicializaPalavra(Palavra *p, char *palavra, int nDoc);

// Soma frequencia se nao foi a primeira aparição da palavra no documento, e acrescenta caracteristica se foi a primeira apararição
Palavra * AdicionaFrequencia(Palavra *p, int nDoc);

// Compara a string dentro de struct palavra com uma outra string passada pra função. Retorna 1 se forem iguais e 0 caso contrario
int ComparaPalavras(Palavra *p, char *palavra);

// Funcão de comparação utilizada para ordenar, pelo qsort, o indice de palavras (ordena em ordem alfabetica)
int PelaPalavra(const void *a, const void *b);

// Calcula o TF_IDF de uma palavra um certo documento
void AtribuiTf_idfPalavra(Palavra *p, IndiceDocs *docs, int flagClassificador);

// Pega as caracteristicas da palavra e passa para a proxima funcao no passo de atribuir as caracteristicas aos documentos
void FinalizaCaracDocumentos_palavras(Palavra *p, IndiceDocs *docs, int posPalavra);

// Salva uma palavra no arquivo binario de saida
void SalvaPalavraBin(Palavra *p, FILE *f);

// Realiza a leitura de uma palavra do arquivo binario
Palavra * CarregaPalavraBin(Palavra *p, FILE *f);

// Libera uma struct palavra da memória
void LiberaPalavra(Palavra *p);

// Printa palavra
void ImprimePalavra(Palavra *p);

// Pega as caracteristicas da palavra e passa para a proxima função do passo de realizar o buscador
void CriaArrayDeBusca_Palavra(Palavra *p, ArrayBusca *arrayB, IndiceDocs *docs);

// Retorna a qauntidade de documentos em que uma palavra apareceu
int ObtemQtdAparicoes(Palavra *p);

// Retorna o ponteiro para a string palavra
char * ObtemPalavra(Palavra *p);

// Pega a caracteristica da palavra e passa adiante da funcao de criar documento para o classificador
void CriaDoc_classificador_palavra(Palavra *p, Documento *doc, int indicePalavra);

// Compara a string dentro de struct palavra com uma outra string passada pra função. Retorna 1 se forem iguais e 0 caso contrario
int StringIgualPalavra(Palavra *p, char *palavra);

// Gera Relatorio da palavra
void RelatorioPalavra(Palavra *p, char *palavra, int *arrayIndicesInt);

// Copia uma struct palavra para outra
Palavra * CopiaPalavra(Palavra *p, Palavra *Rp);

#endif