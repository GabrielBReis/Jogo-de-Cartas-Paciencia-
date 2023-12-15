#ifndef LISTADE_H
#define LISTADE_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "pilhaC.h"
#include "struct.h"


typedef tp_cartas tp_item; // tp_item passa a representar a estrutura tp_cartas. Ajuda na intercomunicação das bibliotecas.

typedef struct tp_no_aux {
    struct tp_no_aux *ant;
    tp_item info;
    struct tp_no_aux *prox;
} tp_no;

typedef struct {
    tp_no *ini;
    tp_no *fim;
} tp_listad;

void gotoxy(int column, int line) { // posicionar o cursor. Utilizada na função imprime_listad
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

tp_listad *inicializa_listad() {
    tp_listad *lista = (tp_listad *)malloc(sizeof(tp_listad));
    lista->ini = NULL;
    lista->fim = NULL;
    return lista;
}

int listad_vazia(tp_listad *lista) {
    if (lista->ini == NULL) return 1;
    return 0;
}

tp_no *aloca() {
    tp_no *pt;
    pt = (tp_no *)malloc(sizeof(tp_no));
    return pt;
}

int insere_listad_no_fim(tp_listad *lista, tp_item e) {
    tp_no *novo;
    novo = aloca();
    if (!novo) return 0;
    novo->info = e;
    if (listad_vazia(lista)) {
        novo->prox = NULL;
        novo->ant = NULL;
        lista->ini = lista->fim = novo;
    } else {
        novo->prox = NULL;
        novo->ant = lista->fim;
        lista->fim->prox = novo;
        lista->fim = novo;
    }
    return 1;
}

void imprime_listad(tp_listad *lista, int ordem, int coluna, int linha) {
    if (lista == NULL)
        printf("Lista nao inicializada");
    else {
        tp_no *atu;
        switch (ordem) {
            case 1:
                atu = lista->ini;
                while (atu != NULL) {
                    gotoxy(coluna, linha);
                    if (atu->prox == NULL) atu->info.visivel = 1;
                    if (atu->info.cor == 'V' && atu->info.visivel == 1)
                        setcolor(4);
                    else if (atu->info.cor == 'P' && atu->info.visivel == 1)
                        setcolor(0);
                    else
                        setcolor(15);

                    if (atu->info.visivel == 0)
                        printf("-???-\n", atu->info.visivel);
                    else if (atu->info.valor == 13)
                        printf("-K%c-\n", atu->info.nipe);
                    else if (atu->info.valor == 12)
                        printf("-Q%c-\n", atu->info.nipe);
                    else if (atu->info.valor == 11)
                        printf("-J%c-\n", atu->info.nipe);
                    else if (atu->info.valor == 1)
                        printf("-A%c-\n", atu->info.nipe);
                    else
                        printf("-%d%c-\n", atu->info.valor, atu->info.nipe);
                    
                    atu = atu->prox;
                    linha++;
                    setcolor(0);
                }
                break;
            case 2:
                atu = lista->fim;
                while (atu != NULL) {
                    printf("valor:%d cor:%c nipe:%c\n", atu->info.valor, atu->info.cor, atu->info.nipe);
                    atu = atu->ant;
                }
                break;
            default:
                printf("codigo invalido");
        }
    }
    printf("\n");
}

int tamanho_listad(tp_listad *lista) {
    tp_no *aux;
    int cont = 1;
    aux = lista->ini;
    while (aux->prox != NULL) {
        cont++;
        aux = aux->prox;
    }
    return cont;
}

tp_listad *Destroi_listad(tp_listad *lista) {
    tp_no *atu;
    atu = lista->ini;
    while (atu != NULL) {
        lista->ini = atu->prox;
        free(atu);
        atu = lista->ini;
    }
    free(lista);
    return NULL;
}

#endif
