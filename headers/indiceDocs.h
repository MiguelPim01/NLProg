#ifndef INDICEDOCS_H
#define INDICEDOCS_H

#include "documento.h"

typedef struct indiceDocs IndiceDocs;

IndiceDocs * AtribuiNomeClasseIndiceDocs(IndiceDocs *docs, char *caminho, char *classe);

IndiceDocs * InicializaIndiceDocs(IndiceDocs *docs);

int ObtemQtdDocumentos(IndiceDocs *docs);

void ImprimeDocs(IndiceDocs *docs);

Documento * AchaDocumento(IndiceDocs *docs, int posDocumento);

void SalvaIndiceDocsBin(IndiceDocs *docs, FILE *f);

IndiceDocs * CarregaIndiceDocsBin(IndiceDocs *docs, FILE *f);

void LiberaIndiceDocs(IndiceDocs *docs);

#endif