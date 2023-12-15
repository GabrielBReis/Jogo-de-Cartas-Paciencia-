#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "struct.h"

#define MAX 100

void setcolor(int ForgC) { 
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

typedef tp_cartas tp_item;

typedef struct {
    int topo;
    tp_item item[MAX];
} tp_pilha;

void inicializar_pilha(tp_pilha *p) {
    p->topo = -1;
}

int pilha_vazia(tp_pilha *p) {
    if (p->topo == -1) return 1;
    return 0;
}

int pilha_cheia(tp_pilha *p) {
    if (p->topo == MAX - 1) {
        return 1;
    } else {
        return 0;
    }
}

int push(tp_pilha *p, tp_item e) {
    if (pilha_cheia(p) == 1) return 0;
    p->topo++;
    p->item[p->topo] = e;
    return 1;
}

int pop(tp_pilha *p, tp_item *e) {
    if (pilha_vazia(p) == 1) return 0;
    *e = p->item[p->topo];
    p->topo--;
    return 1;
}

int top(tp_pilha *p, tp_item *e) {
    if (pilha_vazia(p) == 1) return 0;
    *e = p->item[p->topo];
    return 1;
}

void imprime_pilha(tp_pilha p) {
    tp_item e;
    printf("\n");
    while (!pilha_vazia(&p)) {
        pop(&p, &e);
        printf("cor: %c valor: %d nipe: %c\n", e.cor, e.valor, e.nipe);
    }
}

int altura_pilha(tp_pilha *p) {
    return p->topo + 1;
}

void empilha_pilha(tp_pilha *p, tp_pilha *pi) {
    //tp_item e;
    //pop(pi,e);
    //push(p,e);
}

#endif
