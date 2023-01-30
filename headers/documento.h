#ifndef DOCUMENTO_H
#define DOCUMENTO_H

#include <stdio.h>

typedef struct documento Documento;

Documento * AtribuiNomeClasse(Documento *doc, char *nome, char *classe);

void AtribuiCaracDoc(Documento *doc, int posPalavra, int freqPalavra, double tf_idf);

void SalvaDocBin(Documento *doc, FILE *f);

Documento * CarregaDocBin(Documento *doc, FILE *f);

void ImprimeDoc(Documento *doc);

void LiberaDoc(Documento *doc);

int DocsSaoIguais(Documento *doc1, Documento *doc2);

Documento * InicializaDocumento_classificador();

double ObtemSomaTF_IDFs(Documento *doc);

double CalculaCosseno(Documento *doc1, Documento *doc2, double somatorio_doc2);

char * ObtemClasse(Documento *doc);

#endif