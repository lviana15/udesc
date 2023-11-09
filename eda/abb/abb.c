#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

NoABB *criaABB(int valor) {
    NoABB *raiz = malloc(sizeof(NoABB));
    raiz->filhoDir = NULL;
    raiz->filhoEsq = NULL;
    raiz->data = valor;

    return raiz;
}

