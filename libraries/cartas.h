#ifndef CARTAS_H
#define CARTAS_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pilhaC.h"
#include "listaSE.h"
#include "listaDE.h"
#include "struct.h"
// \x03 copas
// \x04 ouros
// \x05 paus
// \x06 espadas
void criar_cartas(tp_pilha *cava) { // Funcao que cria as 52 cartas do jogo, 13 cartas de cada nipe
    tp_listase *lista; // lista se para embaralhar as cartas
    tp_cartas carta; // cartas

    // mostrar a struct tp_cartas
    lista = inicializa_tp_listase();
    int n = 0, i, m = 13, k = 1 ; // valores que serão utilizados no looping de criação das cartas
    char nipes[4];
    nipes[0] = '\x03';
    nipes[1] = '\x04';
    nipes[2] = '\x05';
    nipes[3] = '\x06';

    // criação de uma string com 4 elementos para criar as cartas de um naipe específico
    for(i = 0; i < 2; i++) { // looping para criar as cartas vermelhas
        while(n < m) { // looping para atribuir os valores às cartas
            carta.valor = k;
            carta.nipe = nipes[i];
            carta.cor = 'V';
            n++; // variável que dita o looping para determinar a quantidade de cartas por naipe
            k++; // valor da carta
            insere_listase_no_fim(&lista, carta);
        }
        m = m + 13; // o inteiro m dobra, pois o n fica = 13
        k = 1; // redefinição do k para criação das cartas pretas
    }
    for(i = 2; i < 4; i++) { // looping para criar as cartas pretas
        while(n < m) { // looping para atribuir os valores às cartas
            carta.valor = k;
            carta.nipe = nipes[i];
            carta.cor = 'P';
            n++; // variável que dita o looping para determinar a quantidade de cartas por naipe
            k++; // valor da carta
            insere_listase_no_fim(&lista, carta);
        }
        m = m + 13;
        k = 1;
    }
    srand(time(NULL)); // função para possibilitar embaralhar as cartas
    int a = 0, tc = 52, g = 0; // determina o total de cartas a serem embaralhadas
    tp_listase *aux, *ant; // ponteiros para percorrer a lista com as cartas

    // imprime_listase(lista);
    while(lista != NULL) {
        aux = lista; // ponteiro que apontará para o elemento a ser sorteado
        ant = NULL;
        g = (rand() % tc + 1); // função para selecionar, aleatoriamente, alguma das 52 cartas inseridas na lista
        a = 1;
        while(a < g) { // looping para determinar a carta que ponteiro apontará, de acordo com o número sorteado previamente
            a++;
            ant = aux;
            aux = aux->prox;
        }
        push(cava, aux->info); // insere a carta sorteada no cava
        if(g == 1) { // para caso o número seja 1, pois não comportará a condição do looping
            lista = aux->prox;
        } else {
            ant->prox = aux->prox;
        }
        free(aux); //"libera" o conteúdo de aux
        tc--; // reduz a quantidade de cartas
    }
}


void imprime_tabuleiro(tp_listad **tabu, tp_pilha *monte, tp_pilha *cava, tp_pilha *mfinais) {
    tp_item e;
    top(monte, &e); // determina a carta que estará no topo do monte
    setcolor(15); // branco
    printf("--%d-- ", altura_pilha(cava)); // mostra quantas cartas ainda têm no cava
    setcolor(0); // preto
    if (e.cor == 'V' && e.visivel == 1)
        setcolor(4); // se a carta tiver cor 'V' e estiver visível, setcolor(4) = vermelho
    else if (e.cor == 'P' && e.visivel == 1)
        setcolor(0); // se a carta tiver cor 'P' e estiver visível, setcolor(0) = preto
    else
        setcolor(15); // as demais cartas do tabuleiro não visíveis serão representadas por: "???" com setcolor(15) = branco
    if (pilha_vazia(monte) == 1) { // se a pilha do monte estiver vazia
        setcolor(15); // branco
        printf("-----\t\t"); // senão
        setcolor(0); // preto
    } else {
        if (e.valor == 13)
            printf("-K%c-\t\t", e.nipe); // se o valor da carta for 13, imprima K
        else if (e.valor == 12)
            printf("-Q%c-\t\t", e.nipe); // se o valor da carta for 12, imprima Q
        else if (e.valor == 11)
            printf("-J%c-\t\t", e.nipe); // se o valor da carta for 11, imprima J
        else if (e.valor == 1)
            printf("-A%c-\t\t", e.nipe); // se o valor da carta for 1, imprima A
        else
            printf("-%d%c-\t\t", e.valor, e.nipe); // senão imprima normal
    }
    setcolor(0);
    int i;
    for (i = 0; i < 4; i++) { // looping para verificar os montes finais
        if (pilha_vazia(&mfinais[i])) { // se estiverem vazios
            setcolor(15); // branco
            printf(" -----");
            setcolor(0); // preto
        } else {
            top(&mfinais[i], &e); // senão, mostra a carta do topo do monte final
            if (e.cor == 'V' && e.visivel == 1)
                setcolor(4); // se a carta tiver cor 'V' e estiver visível, setcolor(4) = vermelho
            else if (e.cor == 'P' && e.visivel == 1)
                setcolor(0); // se a carta tiver cor 'P' e estiver visível, setcolor(0) = preto
            else
                setcolor(15);
            // Determinação da troca dos valores nos montes finais
            if (e.valor == 13)
                printf(" -K%c-", e.nipe);
            else if (e.valor == 12)
                printf(" -Q%c-", e.nipe);
            else if (e.valor == 11)
                printf(" -J%c-", e.nipe);
            else if (e.valor == 1)
                printf(" -A%c-", e.nipe);
            else
                printf(" -%d%c-", e.valor, e.nipe);
            setcolor(0);
        }
    }
    setcolor(0);
    // printf("casoooo");
    // printf("\n");
    int ii;
    for ( ii = 0; ii < 7; ii++) { // imprimir lista dos montes do tabuleiro
        imprime_listad(tabu[ii], 1, ii * 7, 2); // imprime a lista do início ao fim com linhas e colunas determinadas
    }
    gotoxy(1, 15); // local específico embaixo do tabuleiro para listar as opções de jogada do usuário
    setcolor(15);
    printf("\n\n\n\n---------------------------------------------------------\n");
    printf("|\t1-Puxa do cava. \t|\n"); // retorna ao cava
    printf("|\t2-Pegar do monte. \t|\n");
    printf("|\t3-Mover carta. \t|\n");
    printf("|\t4-Mover carta para o monte final. \t|\n");
    printf("|\t5-Mover carta do monte final para uma pilha.\t|\n");
    printf("|\t6-Sair \t|\n");
    printf("---------------------------------------------------------\n");
}

void puxa_cava(tp_pilha *monte, tp_pilha *cava) { // função para puxar do cava e colocar no monte
    tp_item e;
    if (pilha_vazia(cava)) { // caso o cava esteja vazio
        while (!pilha_vazia(monte)) { // tira do monte e põe no cava enquanto o monte não estiver vazio
            pop(monte, &e);
            push(cava, e);
        }
    }
    pop(cava, &e); // tira da pilha do cava
    push(monte, e); // coloca na pilha do monte
    // imprime_pilha(*monte);
}


void distribui_cartas(tp_listad **tabu, tp_pilha *cava) {
    tp_item carta;
    int a = 0;
    int i,k;
    for (i = 0; i < 7; i++) { // colocar as cartas no tabuleiro
        for ( k = 0; k < (i + 1); k++) { // define quantas cartas devem ser colocadas em cada lista do tabuleiro
            pop(cava, &carta); // tira do cava
            if (k < i && a == 0) { // define se o usuário deve ou não ver a carta
                carta.visivel = 0;
            }
            // printf("cart: %d\n", cart);
            insere_listad_no_fim(tabu[i], carta); // insere no tabuleiro
            // carta.visivel=0
        }
    }
    a++;
}

void desce_monte(tp_pilha *monte, tp_listad *tabu) { // tira uma carta do monte e põe no tabuleiro, sendo que a lista a ser inserida está na passagem de parâmetro
    tp_item e;
    tp_no *no;
    pop(monte, &e);
    if (tabu->fim == NULL) { // se a lista estiver vazia
        insere_listad_no_fim(tabu, e);
    } else if (e.valor == (tabu->fim->info.valor) - 1 && e.cor != tabu->fim->info.cor) { // confere se a jogada está dentro da regra
        insere_listad_no_fim(tabu, e);
    } else { // caso esteja fora da regra
        push(monte, e);
        printf("\nFuncao Invalida\n");
    }
}


int mover_carta(tp_listad *listam, tp_listad *listae, int q_cartas) {
    int i = 1;
    tp_no *lm_atu, *lm_ant, *le;

    lm_atu = listam->fim; // último elemento da lista que quer modificar
    le = listae->fim; // último elemento da lista estática

    while (i < q_cartas) { // Vai mover até a carta
        lm_atu = lm_atu->ant;
        i++;
        if (lm_atu->info.visivel == 0 || lm_atu == NULL) {
            return 0;
        }
    }
    lm_ant = lm_atu;

    lm_ant = lm_ant->ant;

    if (le == NULL) {
        if (!(lm_ant == NULL)) {
            lm_ant->prox = NULL;
            lm_atu->ant = NULL;
            listae->ini = lm_atu;
            listae->fim = listam->fim;
            listam->fim = lm_ant;
        } else {
            listae->ini = lm_atu;
            listae->fim = listam->fim;
            listam->fim = NULL;
            listam->ini = NULL;
        }
    } else {
        if ((lm_atu->info.valor == ((le->info.valor) - 1)) && (lm_atu->info.cor != le->info.cor)) {
            if (!(lm_ant == NULL)) {
                le->prox = lm_atu;
                lm_atu->ant = le;
                lm_ant->prox = NULL;
                listae->fim = listam->fim;
                listam->fim = lm_ant;
            } else {
                lm_atu->ant = le;
                le->prox = lm_atu;
                listae->fim = listam->fim;
                listam->fim = NULL;
                listam->ini = NULL;
            }
        }
    }
    if (listam->fim != NULL) listam->fim->info.visivel = 1;
    return 0;
}


void empilha_final(tp_listad *listam, tp_pilha *pilha_final) {
    tp_no *lm_atu, *lm_ant;
    tp_item e;

    lm_atu = listam->fim; // último elemento da lista que quer modificar
    lm_ant = listam->fim;
    lm_ant = lm_ant->ant;

    if (pilha_vazia(pilha_final) && (lm_atu->info.valor == 1)) {
        e.valor = lm_atu->info.valor;
        e.cor = lm_atu->info.cor;
        e.nipe = lm_atu->info.nipe;
        push(pilha_final, e);

        if (listam->ini == listam->fim) {
            listam->fim = NULL;
            listam->ini = NULL;
        } else {
            listam->fim = lm_ant;
            lm_ant->prox = NULL;
            free(lm_atu);
        }
    } else {
        pop(pilha_final, &e);

        if ((e.valor + 1) == (lm_atu->info.valor)) {
            push(pilha_final, e);
            e.valor = lm_atu->info.valor;
            e.cor = lm_atu->info.cor;
            e.nipe = lm_atu->info.nipe;

            if (listam->ini == listam->fim) {
                listam->fim = NULL;
                listam->ini = NULL;
            } else {
                listam->fim = lm_ant;
                lm_ant->prox = NULL;
                free(lm_atu);
            }

            push(pilha_final, e);
        } else {
            printf("\nFuncao invalida!\n\n");
            push(pilha_final, e);
        }
    }
}



void cima_baixo(tp_pilha *pilha_final, tp_listad *tabu) {
    tp_item e;
    tp_no *no;
    pop(pilha_final, &e);

    if (tabu->fim == NULL) {
        insere_listad_no_fim(tabu, e);
    }

    if (e.valor == (tabu->fim->info.valor) - 1 && e.cor != tabu->fim->info.cor) {
        insere_listad_no_fim(tabu, e);
    } else {
        push(pilha_final, e);
        printf("\nFuncao Invalida\n");
    }
}

void monte_para_final(tp_pilha *monte, tp_pilha *mfinal) {
    tp_item e, g;
    pop(monte, &e);

    if (pilha_vazia(mfinal) && (e.valor == 1)) {
        push(mfinal, e);
    } else {
        pop(mfinal, &g);

        if (e.valor == (g.valor + 1) && e.nipe == g.nipe) {
            push(mfinal, g);
            push(mfinal, e);
        } else {
            printf("\nEscolha inválida\n");
            push(monte, e);
            push(mfinal, g);
        }
    }
}


// tentativa de criar funcao que indica a derrota
void checa_derrota(tp_listad *tabu[], tp_pilha *monte, tp_pilha *cava, tp_pilha *mfinais){
	tp_pilha aux;
	tp_item e, f;
	int cont = 0, pont = 0,i;
	tp_no *l_ref[7]; // ; l_ref == aponta
	inicializar_pilha(&aux);
	if(pilha_vazia(cava)==1){
		while(!pilha_vazia(monte)){
			pop(monte, &e);
			for ( i = 0; i < 7; i++){
				if((e.valor != (tabu[i]->fim->info.valor)-1) || (e.cor == tabu[i]->fim->info.cor)){
					cont++;
				}
			}
			for(i = 0; i < 4; i++){
				top(&mfinais[i], &f);
				if((e.valor != f.valor+1) && e.nipe != f.nipe){
					cont++;
				}
			}
			push(&aux, e);
		}
		while(!pilha_vazia(&aux)){
			pop(&aux, &e);
			push(monte, e);
		}
		for( i = 0; i < 7; i++){
			l_ref[i] = tabu[i]->fim;
		}
		for(i = 0; i < 6; i++){
			while(l_ref[i+1]->info.visivel == 1){
				if((l_ref[i]->info.valor != (l_ref[i+1]->info.valor)+1) || (l_ref[i]->info.valor != (l_ref[i+1]->info.valor)-1) && l_ref[i]->info.cor == l_ref[i+1]->info.cor){
					cont++;
				}
			}
		}
		for( i = 0; i < 5; i++) {
			while(l_ref[i + 2]->info.visivel == 1) {
				if((l_ref[i]->info.valor != (l_ref[i + 2]->info.valor) + 1) ||
				(l_ref[i]->info.valor != (l_ref[i + 2]->info.valor) - 1) && l_ref[i]->info.cor ==
				l_ref[i + 2]->info.cor) {
					cont++;
				}
			}
		}

		for( i = 0; i < 4; i++) {
			while(l_ref[i + 3]->info.visivel == 1) {
				if((l_ref[i]->info.valor != (l_ref[i + 3]->info.valor) + 1) ||
				(l_ref[i]->info.valor != (l_ref[i + 3]->info.valor) - 1) && l_ref[i]->info.cor ==
				l_ref[i + 3]->info.cor) {
					cont++;
				}
			}
		}

		for( i = 0; i < 3; i++) {
			while(l_ref[i + 4]->info.visivel == 1) {
				if((l_ref[i]->info.valor != (l_ref[i + 4]->info.valor) + 1) ||
				(l_ref[i]->info.valor != (l_ref[i + 4]->info.valor) - 1) && l_ref[i]->info.cor ==
				l_ref[i + 4]->info.cor) {
					cont++;
				}
			}
		}

		for( i = 0; i < 2; i++) {
			while(l_ref[i + 5]->info.visivel == 1) {
				if((l_ref[i]->info.valor != (l_ref[i + 5]->info.valor) + 1) ||
				(l_ref[i]->info.valor != (l_ref[i + 5]->info.valor) - 1) && l_ref[i]->info.cor ==
				l_ref[i + 5]->info.cor) {
					cont++;
				}
			}
		}

		for( i = 0; i < 1; i++) {
			while(l_ref[i + 6]->info.visivel == 1) {
				if((l_ref[i]->info.valor != (l_ref[i + 6]->info.valor) + 1) ||
				(l_ref[i]->info.valor != (l_ref[i + 6]->info.valor) - 1) && l_ref[i]->info.cor ==
				l_ref[i + 6]->info.cor) {
					cont++;
				}
			}
		}

		for( i = 0; i < 6; i++) {
			while(l_ref[i + 1]->info.visivel == 1) {
				if((l_ref[i]->info.valor != (l_ref[i + 1]->info.valor) + 1) ||
				(l_ref[i]->info.valor != (l_ref[i + 1]->info.valor) - 1) && l_ref[i]->info.cor ==
				l_ref[i + 1]->info.cor) {
					cont++;
				}
			}
		}

		for( i = 0; i < 5; i++) {
			while(l_ref[i + 2]->info.visivel == 1) {
				if((l_ref[i]->info.valor != (l_ref[i + 2]->info.valor) + 1) ||
				(l_ref[i]->info.valor != (l_ref[i + 2]->info.valor) - 1) && l_ref[i]->info.cor ==
				l_ref[i + 2]->info.cor) {
					cont++;
				}
			}
		}

		for( i = 0; i < 4; i++) {
			while(l_ref[i + 3]->info.visivel == 1) {
				if((l_ref[i]->info.valor != (l_ref[i + 3]->info.valor) + 1) ||
				(l_ref[i]->info.valor != (l_ref[i + 3]->info.valor) - 1) && l_ref[i]->info.cor ==
				l_ref[i + 3]->info.cor) {
					cont++;
				}
			}
		}

		for( i = 0; i < 3; i++){
			while(l_ref[i+4]->info.visivel == 1){
				if((l_ref[i]->info.valor != (l_ref[i+4]->info.valor)+1) || (l_ref[i]->info.valor != (l_ref[i+4]->info.valor)-1) && l_ref[i]->info.cor == l_ref[i+4]->info.cor){
					cont++;
				}
			}
		}
		for( i = 0; i < 2; i++){
			while(l_ref[i+5]->info.visivel == 1){
				if((l_ref[i]->info.valor != (l_ref[i+5]->info.valor)+1) || (l_ref[i]->info.valor != (l_ref[i+5]->info.valor)-1) && l_ref[i]->info.cor == l_ref[i+5]->info.cor){
					cont++;
				}
			}
		}
		for( i = 0; i < 1; i++){
			while(l_ref[i+6]->info.visivel == 1){
				if((l_ref[i]->info.valor != (l_ref[i+6]->info.valor)+1) || (l_ref[i]->info.valor != (l_ref[i+6]->info.valor)-1) && l_ref[i]->info.cor == l_ref[i+6]->info.cor){
					cont++;
				}
			}
		}
	}
}
#endif
