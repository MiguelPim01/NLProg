#ifndef DOCUMENTO_H
#define DOCUMENTO_H

typedef struct documento Documento;

void AtribuiNomeClasse(Documento *doc, char *nome, char *classe);

void ImprimeDoc(Documento *doc);

void LiberaDoc(Documento *doc);

#endif