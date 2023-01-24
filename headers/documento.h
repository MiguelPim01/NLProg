#ifndef DOCUMENTO_H
#define DOCUMENTO_H

typedef struct documento Documento;

Documento * AtribuiNomeClasse(Documento *doc, char *nome, char *classe);

void AtribuiCaracDoc(Documento *doc, int posPalavra, int freqPalavra, double tf_idf);

void ImprimeDoc(Documento *doc);

void LiberaDoc(Documento *doc);

#endif