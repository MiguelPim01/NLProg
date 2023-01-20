#ifndef CARACTERISTICAS_H
#define CARACTERISTICAS_H

typedef struct caracteristicas Caracteristicas;

Caracteristicas * AtribuiCaracteristicas(Caracteristicas *crts, int nDoc, int flag);

int VerificaSeAddFrequencia(Caracteristicas * crts, int nDoc);

void ImprimeCaracteristicas(Caracteristicas *crts);

void LiberaCaracteristicas(Caracteristicas *crts);

#endif