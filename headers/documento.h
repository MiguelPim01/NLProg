#ifndef DOCUMENTO_H
#define DOCUMENTO_H

#include <stdio.h>

typedef struct documento Documento;

// Atribui os membros nome e classe, passados como parametro, na struct documento e retorna ela
Documento * AtribuiNomeClasse(Documento *doc, char *nome, char *classe);

// Adiciona uma caracteristica (membros da struct caracteristicas sao recebidos pela funcao) no vetor de caracteristicas membro da struct documento. Essa caracteristica é atribuida na posicao referente a quantidade de palavras do doc (armazenada como membro da struct) menos 1
void AtribuiCaracDoc(Documento *doc, int posPalavra, int freqPalavra, double tf_idf);

// Escreve em binário no file o nome, classe, qtd de palavras e o vetor caracteristicas
void SalvaDocBin(Documento *doc, FILE *f);

// Lê em binário do file o nome, a classe, a qtd de palavras e o vetor caracteristicas
Documento * CarregaDocBin(Documento *doc, FILE *f);

// Imprime os membros da stuct documento
void ImprimeDoc(Documento *doc);

// Libera da memoria os membros da struct documento e a propria struct
void LiberaDoc(Documento *doc);

// Retorna valor verdadeiro se a struct doc1 for igual a doc2, e falso se nao for
int DocsSaoIguais(Documento *doc1, Documento *doc2);

// Inicializa struct e seus membros para serem usados no classificador, e retorna a struct
Documento * InicializaDocumento_classificador();

// Retorna a soma dos tf_idfs do documento
double ObtemSomaTF_IDFs(Documento *doc);

// Faz o calculo do cosseno entre os dois documentos recebidos (utilizando tambem o somatorio do doc2) e retorna esse valor
double CalculaCosseno(Documento *doc1, Documento *doc2, double somatorio_doc2);

// Retorna a string classe da struct doc
char * ObtemClasse(Documento *doc);

// Atribui na struct Rdoc, os membros da struct doc, ou seja, copiando a struct doc para a struct Rdoc
Documento * CopiaDoc(Documento *doc, Documento *Rdoc);

// Acessa struct Rdoc para atribuir no membro somaFreq a soma das frequencias da outra struct documento, doc
void AtribuiSomaDasFrequencias_Doc(Documento *doc, Documento *Rdoc);

// Soma as frequencias da struct doc
int SomaFrequenciasDoc(Documento *doc);

// Funcao utilizada no qsort para ordenar pela frequencia em ordem crescente
int PelaSomaFrequenciaCresc(const void *a, const void *b);

// Funcao utilizada no qsort para ordenar pela frequencia em ordem decrescente
int PelaSomaFrequenciaDecresc(const void *a, const void *b);

// Retorna o membro somaFreq, que equivale a qtd de palavras, da struct doc
int RetornaNumeroPalavras(Documento *doc);

#endif