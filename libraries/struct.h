#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>

typedef struct { // criando o tipo carta
    char cor; // caractestica referente a cor da carta usada para comparacao
    int valor; // caractestica referente a valor realizar as operacoes do jogo
    char nipe; // caractestica referente a nipe da carta usada para comparacao
    int visivel; //condição de visibilidade das cartas
} tp_cartas;

//estrutura das cartas

void pisca_pisca() { //efeito especial opicional. AVISO: PODE CAUSAR CONVULSÕES A PESSOAS FOTOSENSÍVEIS, UTILIZE COM CAUTELA.
    system("color 10");
    system("color 20");
    system("color 30");
    system("color 40");
    system("color 50");
    system("color 60");
    system("color 70");
    system("color 80");
    system("color 90");
    system("color 20");
}

typedef tp_cartas tp_item;

#endif
