#ifndef CARACTERISTICAS_H
#define CARACTERISTICAS_H

#include "indicePalavras.h"
#include "indiceDocs.h"

typedef struct caracteristicas Caracteristicas;

// Aloca memoria para a struct caracteristicas e retorna o ponteiro para essa struct
Caracteristicas * AlocaCaracteristicas();

// Inicializa caracteristica, recebendo e atribuindo a posicao, frequencia e tf_idf, e retorna o ponteiro para essa struct
Caracteristicas * InicializaCaracteristicas(Caracteristicas * crts, int pos, int freq, double tf_idf);

// Aumenta em 1 o valor da frequencia na característica recebida
Caracteristicas * SomaNaFrequencia(Caracteristicas *crts);

// Retorna valor verdadeiro se o valor no membro posição da caracteristica é igual ao numero do Documento passado como parâmetro e falso se não for
int VerificaSeAddFrequencia(Caracteristicas * crts, int nDoc);

// Recebe o idf e faz o cálculo do tf_idf, atribuindo no membro tf_idf da struct
void CalculaTf_idf(Caracteristicas *crts, double idf);

// Escreve em binário no file a posicao, frequencia e tf_idf da struct
void SalvaCaracteristicasBin(Caracteristicas *crts, FILE *f);

// Lê em binário do file a posicao, frequencia e tf_idf da struct e atribui na nova struct caracteristica, que é retornada
Caracteristicas * CarregaCaracteristicasBin(Caracteristicas *crts, FILE *f);

// Imprime a posicao, frequencia e tf_idf da struct
void ImprimeCaracteristicas(Caracteristicas *crts);

// Libera a struct da memoria
void LiberaCaracteristicas(Caracteristicas *crts);

// Acessa a struct caracteristica para atribuir a posicao(obtida a partir do indice de docs e posicao passados como parametro), frequencia e tf_idf correspondentes
void FinalizaCaracDocumentos_carac(Caracteristicas *crts, IndiceDocs *docs, int posPalavra);

// Acessa a struct caracteristica para conseguir a posicao e tf_idf para em outra funcao atribuir a stuct Busca
void CriaArrayDeBusca_Carac(Caracteristicas *crts, ArrayBusca *arrayB, IndiceDocs *docs);

// Retorna valor do membro posicao da struct
int ObtemPosicao(Caracteristicas *crts);

// Retorna valor do membro frequencia da struct
int ObtemFrequencia(Caracteristicas *crts);

// Retorna valor do membro tf_idf da struct
double ObtemTF_IDF(Caracteristicas *crts);

// Acessa a struct caracteristica para, em outra funcao, atribuir a posicao (indice da palavra passado como parametro) a frequencia e tf_idf ao documento, usado no classificador
void CriaDoc_classificador_carac(Caracteristicas *crts, Documento *doc, int indicePalavra);

// Acessa struct caracteristicas para, em outra funcao, atribuir a posicao, frequencia e tf_idf no documento Rdoc, usado no relatorio
void CopiaCaracDoc(Caracteristicas *crts, Documento *Rdoc);

// Atribui na struct Rcrts, usada no relatorio, os membros da struct crts, ou seja, copiando a struct crts na Rcrts, e retorna a struct Rcrts
Caracteristicas * CopiaCarac(Caracteristicas *crts, Caracteristicas *Rcrts);

// Retorna o valor do membro posicao da struct
int RetornaFrequencia(Caracteristicas *crts);

// Retorna o valor do membro posicao da struct
int RetornaPosicao(Caracteristicas *crts);

// Funcao utilizada pelo qsort para ordenar pela frequencia
int PelaFrequencia(const void *a, const void *b);

#endif