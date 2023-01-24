#ifndef INDICEDOCS_H
#define INDICEDOCS_H

typedef struct indiceDocs IndiceDocs;

IndiceDocs * AtribuiNomeClasseIndiceDocs(IndiceDocs *docs, char *caminho, char *classe);

IndiceDocs * InicializaIndiceDocs(IndiceDocs *docs);

int ObtemQtdDocs(IndiceDocs *docs);

void ImprimeDocs(IndiceDocs *docs);

void LiberaIndiceDocs(IndiceDocs *docs);

#endif