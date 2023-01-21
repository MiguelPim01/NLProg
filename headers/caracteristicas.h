#ifndef CARACTERISTICAS_H
#define CARACTERISTICAS_H

typedef struct caracteristicas Caracteristicas;

Caracteristicas * AlocaCaracteristicas();

Caracteristicas * InicializaCaracteristicas(Caracteristicas * crts, int nDoc);

Caracteristicas * AtribuiCaracteristicas(Caracteristicas *crts, int nDoc, int flag);

Caracteristicas * SomaNaFrequencia(Caracteristicas *crts);

int VerificaSeAddFrequencia(Caracteristicas * crts, int nDoc);

void ImprimeCaracteristicas(Caracteristicas *crts);

void LiberaCaracteristicas(Caracteristicas *crts);

#endif