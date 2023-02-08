#ifndef INDICEPALAVRAS_H
#define INDICEPALAVRAS_H

#include "palavra.h"

typedef struct indicePalavras IndicePalavras;

// Inicializa indice de palavras e retorna um ponteiro para ele
IndicePalavras * InicializaIndicePalavras(IndicePalavras *palavras);

// Aloca espaço na memora para o indice de palavras
IndicePalavras * AlocaIdxPalavras();

// Adiciona a palavra recebida no indice de palavras arrayDeBusca, usado no buscador
void AdicionaPalavraBuscada(IndicePalavras *arrayDeBusca, IndicePalavras *p, char *palavra);

// Cria indice de palavras palavrasDigitadas, usado no classificador
void CriaIndicePalavras_classificador(IndicePalavras *palavrasDigitadas, IndicePalavras *p, char *palavra, IndiceDocs *docs);

// Constroi o indice de palavras com os documentos presentes na pasta train, cujo caminho é passado como parametro
IndicePalavras * AtribuiIndicePalavras(IndicePalavras *p, int nDoc, char *caminhoAux);

// Retorna o indice da palavra repetida, ou -1 caso não haja nenhuma
int ProcuraRepetida(IndicePalavras *p, char *palavra);

// Libera da memoria os membros e o proprio indice de palavras
void LiberaIndicePalavras(IndicePalavras *p);

// Acessa struct indicePalavras para poder atribuir o tf_idf de cada palavra em outra funcao
void AtribuiTf_idfIdxPalavras(IndicePalavras *p, IndiceDocs *docs, int flagClassificador);

// Escreve em binario qtd de palavras e array de palavras no file
void SalvaIndicePalavrasBin(IndicePalavras *p, FILE *f);

// Lê em binario a qtd de palavras e array de palavras e salva no novo indice de palavras
IndicePalavras * CarregaIndicePalavrasBin(IndicePalavras *p, FILE *f);

//Imprime indice de palavras
void ImprimePalavras(IndicePalavras *p);

// Acessa indice de palavras para usar o qsort na array de palavras que é membro da struct
void OrdenaIndicePalavras(IndicePalavras *p);

// Faz a busca de uma palavra dentro do indice de palavras
Palavra ** BuscaPalavra(IndicePalavras *p, char *palavra);

// Acessa indice de palavras para usar cada palavra da array de palavras na proxima funcao
void FinalizaCaracDocumentos_indxPalavras(IndicePalavras *p, IndiceDocs *docs);

// Libera array de palavras, que é membro da struct, e a propria struct
void LiberaIndicePalavrasBuscadas(IndicePalavras *p);

// Acessa indice de palavras para usar cada palavra da array de palavras na proxima funcao
void CriaArrayDeBusca_IndxPalavras(IndicePalavras *p, ArrayBusca *arrayB, IndiceDocs *docs);

// Retorna indice da palavra passada como parametro ou, caso essa palavra nao exista no indice, retorna -1
int RetornaIndiceDaPalavra(IndicePalavras *p, Palavra *palavra);

// Acessa indice de palavras para usar cada palavra da array de palavras na proxima funcao
void CriaDoc_classificador_indPalavras(IndicePalavras *p_buscadas, Documento *doc, IndicePalavras *p);

// Gera o relatório da palavra
void RelatorioPalavra_indxPalavra(IndicePalavras *p, IndiceDocs *docs, char *palavra);

#endif