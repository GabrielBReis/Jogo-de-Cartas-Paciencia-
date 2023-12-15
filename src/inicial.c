#include "../libraries/common.h"

int main(){

    int choice, i, m_n, m_e, q_cartas, cont;
    tp_item e;
    tp_pilha monte, cava, mfinal[4]; // cria cava e monte de cartas
    tp_listad *tabu[7]; // cria as listas que vai se construir o jogo

    inicializar_pilha(&monte); //inicializa a pilha que vai guardar as cartas viradas
    inicializar_pilha(&cava); // inicializar a pilha que vai guardar todas as cartas
    criar_cartas(&cava); //criando as cartas
    
    system("color 20"); // cor do mesa
    
    for( i = 0 ; i < 7 ; i++){
        tabu[i] = inicializa_listad();//inicializa as listas
    }

    for(i = 0 ; i < 4 ; i++){
        inicializar_pilha(&mfinal[i]); // criação dos montes finais de cada nipe
    }
    distribui_cartas(tabu,&cava); //funcao que distribui as cartas iniciais do tabuleiro, visiveis e invisiveis
    
    while(1){
        imprime_tabuleiro(tabu,&monte,&cava,mfinal); // imprime o tabuleiro, as listas, montes finais, monte e cava
        printf("Movimento: "); //pede um movimento do usuario
        scanf(" %d", &choice);
        switch (choice){ // vai direcionar a escolha do usuario para alguma função
            case (1):{
                puxa_cava(&monte, &cava); // puxa uma carta do monte onde fica as cartas cobertas e passa para o cava
                break;
            }
            case (2):{ //caso em que quer se pegar uma carta do monte
                printf("Digite a pilha para a qual quer mover a carta (1 a 7): "); //
                scanf(" %d",&m_e);
                if(m_e<1 || m_e> 7){
                    printf("Valor Invalido!\n");
                    break;
                }
                desce_monte(&monte, tabu[m_e-1]); //função que faz o movimento do monte para uma lista
                break;
            }
            case (3):{ // função que movimenta uma quantidade de cartas de uma lista para outra
                printf("\n");
                printf("Digite a pilha da qual quer mover (n) carta(s). (1 a 7): "); // numero da lista que se quer modificar
                scanf(" %d",&m_n);
                if(m_n<1 || m_n> 7){
                    printf("Valor Invalido!\n"); // verifica se o numero da lista é valido
                    break;
                }
                printf("Digite a pilha para a qual quer mover (n) carta(s). (1 a 7): "); // numero da lista para onde as cartas serão enviadas
                scanf(" %d",&m_e);
                if(m_e<1 || m_e> 7){
                    printf("Valor Invalido!\n");
                    break;
                }
                printf("Digite a quantidade de cartas que quer mover: "); // a quantidade de cartas a ser movido
                scanf(" %d",&q_cartas);
                if(q_cartas>tamanho_listad(tabu[m_n-1])){ // se a quantidade de cartas que quer mover é maior do que a quantidade de cartas que existe na pilha
                    printf("Valor Invalido");
                    break;
                }
                mover_carta(tabu[m_n-1],tabu[m_e-1],q_cartas); // função que faz o movimento das cartas
                break;
            }
            case (4):{
                // caso em que se deseja mover cartas para o monte final
                printf("1-Mover de umas das pilhas do tabuleiro.\n"); // situação em que se move da parte de baixo (tabuleiro) para parte de cima (monte final)
                printf("2-Mover do monte.\n"); // situação em que quer se mover as cartas do monte que guardas as cartas para o monte final
                printf("Movimento: ");
                scanf(" %d", &choice);
                printf("\n");
                // entra em um switch case secundario que vai direcionar para o submovimento desejado
                switch(choice){
                    case(1):{ // situação que se deseja movimentar do tabuleiro para o monte final
                        printf("\nDigite a pilha da qual quer mover cartas. (1 a 7): "); // pergunta de qual lista vai ser a carta movida para o monte final
                        scanf(" %d",&m_n);
                        if(m_n<1 || m_n> 7){
                            printf("Valor Invalido!\n");
                            break;
                        }
                        printf("Digite a pilha final para a qual quer mover cartas. (1 a 4): "); //pergunta para que monte final deseja se colocar a carta
                        scanf(" %d",&m_e);
                        if(m_e<1 || m_e> 4){
                            printf("Valor Invalido!\n");
                            break;
                        }
                        empilha_final(tabu[m_n-1],&mfinal[m_e-1]); // função que realiza o movimento de colocar a carta do tabuleito para o monte final
                        break;
                    }
                    case(2):{
                        //situação em que quer se mover uma carta do monte para o monte final
                        printf("\nDigite a pilha final para a qual quer mover cartas (1 a 4): "); // pergunta se para qual monte final vai a carta
                        scanf("%d",&m_e);
                        if(m_e>4 || m_e<1){
                            printf("Valor Invalido!\n");
                            break;
                        }else
                            monte_para_final(&monte, &mfinal[m_e-1]); //função que realiza a movimentação das cartas do monte para o monte final
                        break;
                    }
                }
                break;
            }
            case (5):{
                // situacao em que deseja se pegar uma carta do monte final e coloca la em uma lista
                printf("\nDigite de qual monte final quer mover carta (1 a 4): "); //pergunta de qual monte final e a carta a ser movida
                scanf("%d",&m_n);
                if(m_n<1 || m_n> 4){
                    printf("Valor Invalido!\n"); // caso o numero referente ao monte final seja diferente dos existentes
                    break;
                }
                printf("\nDigite a pilha para a qual quer mover carta (1 a 7): "); // pergunta para que lista quer colocar a carta tirada do monte final
                scanf("%d",&m_e);
                if(m_e<1 || m_e> 7){
                    printf("Valor Invalido!\n"); // situacao em que o numero da lista é diferente dos existentes
                    break;
                }else
                    cima_baixo(&mfinal[m_e-1],tabu[m_n-1]); // funcao que realiza a movimentacao do monte final para uma lista
                break;
            }
            case (6):{
                // caso o usuario deseja sair do jogo
                return 0; // termina o progrma
                break;
            }
        }
        cont=0; // contador que vai verificar se os montes finais estão completos e o jogador ganhou
        for( i = 0; i < 4; i++){
            top(&mfinal[i], &e); // analisa se a ultima carta da das pilhas referentes ao monte final é o numero 13 ou o K, vulgo rei
            if(e.valor == 13){
                cont++;// contador que vai indicar vitoria do jogador
            }
        }
        if(cont == 4){ // imprime mensagem de vitoria
            printf(" \ / \x03 _______ ____ ____ x06 /\.");
            printf(" \ / | | | | | | | / \.");
            printf(" \ / | | | | |____| | /____\.");
            printf(" \ / | | | | | | / \.");
            printf(" \/ | | |____| | | / \.");
            return 0;
        }
        system("pause"); //da uma pausa no sistema, espera que o usuario tecle na barra de espaco
        // epilepsia();
        system("cls"); // limpa a tela
    }
    return 0;
}
