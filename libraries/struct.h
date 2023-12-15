#ifndef STRUCT_H
#define STRUCT_H
#include <stdio.h>

typedef struct { // criando o tipo carta
    char cor; // caractestica referente a cor da carta usada para comparacao
    int valor; // caractestica referente a valor realizar as operacoes do jogo
    char nipe; // caractestica referente a nipe da carta usada para comparacao
    int visivel; //condição de visibilidade das cartas
} tp_cartas;

typedef tp_cartas tp_item;

#endif
