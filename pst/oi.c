#include <stdio.h>
#include <stdbool.h> // lib para usar o tipo bool
#include <stdlib.h> // lib para limpar o terminal

// função 1
// Função para imprimir o tabuleiro
void imprime_tabuleiro(char tabuleiro[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", tabuleiro[i][0], tabuleiro[i][1], tabuleiro[i][2]);
        if (i < 2) {
            printf("---+---+---\n");
        }
    }
    printf("\n");
}

//função 2
// Função para verificar se um jogador venceu
bool verificar_vitoria(char tabuleiro[3][3], char jogador) {
    // linhas
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) {
            return true;
        }
    }
    // colunas
    for (int j = 0; j < 3; j++) {
        if (tabuleiro[0][j] == jogador && tabuleiro[1][j] == jogador && tabuleiro[2][j] == jogador) {
            return true;
        }
    }
    // diagonais
    if (tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) {
        return true;
    }
    if (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador) {
        return true;
    }
    return false;
}

// função 3
// Função para verificar se deu velha
bool verificar_empate(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

//função 4
int continuar_jogo(void) {
    char continuar;
    // Limpar o input de entrada
    while (getchar() != '\n'); 

    printf("Deseja jogar novamente? (s/n): ");
    scanf("%c", &continuar);
    continuar = tolower(continuar); // Converte para minúscula

    if (continuar == 's') {
        return 1; // 1 para sim
    } else if (continuar == 'n') {
        return 0; // 0 para não
    } else {
        printf("Resposta invalida. Por favor, digite 's' ou 'n'.\n");
        return continuar_jogo(); // se a pessoa digita algo inesperado a pergunta é refeita
    }
}

// função 5
int sair_qal_moment(){
    char sair;

    while (getchar() != '\n'); 

    printf("Sair (s/n): ");
    scanf("%c", &sair);
    sair = tolower(sair);

    if(sair == 's'){
        system("cls"); // para limpar a tele
        return 1;
    }else if(sair == 'n'){
        return 0;
    }else{
        printf("Resposta invalida. Por favor, digite 's' ou 'n'.\n");
        return sair_qal_moment(); // aqui uso o mesmo truque explicado na linha 71
    }
}

//função 6
int main() {
    char tabuleiro[3][3];
    char jogador_atual;
    int linha, coluna;
    bool jogar_novamente = true; // truque usado para o loop de partidas infinitas
    int saida; //eu criei essa variavel para poder saber se o jogador quer sair ou não; eu teria feito como na linha 162 onde o return da função é o valor da variavel
    // mas achei que assim seria melhor já que teria alterar o valor de 2 variáveis

    printf("Bem-vindo ao Jogo da Velha!\n");

    // Loop de novas partidas
    while (jogar_novamente) {
        // Limpa o tabuleiro / preenche o tabuleiro de forma dinâmica
        for (int i = 0; i < 3; i++) {  
            for (int j = 0; j < 3; j++) {
                tabuleiro[i][j] = ' '; 
            }
        }
        jogador_atual = 'X'; // define o jogador
        bool jogo_ativo_partida = true; // mesmo truque de antes; ativa o jogo, usado no loop, linha 97
        int rounds = 0; //criei isso para verificar se não é a primeira jogada. Será que alguém ia pular fora logo de cara?!

        // Loop de uma unica partida
        while (jogo_ativo_partida) {
            imprime_tabuleiro(tabuleiro);

            if(rounds > 0){
                saida = sair_qal_moment();

                if(saida == 1){
                    jogo_ativo_partida = false;
                    jogar_novamente = false;
                    break;
                }
            }

            printf("Jogador %c, digite a linha (1-3) e a coluna (1-3) separadas por espaco: ", jogador_atual);
            if (scanf(" %d %d", &linha, &coluna) != 2) { 
                printf("Entrada invalida.\n");
                while (getchar() != '\n'); // Limpa o input
                continue; 
            }

            linha--; 
            coluna--;

            if (linha >= 0 && linha < 3 && coluna >= 0 && coluna < 3 && tabuleiro[linha][coluna] == ' ') {
                tabuleiro[linha][coluna] = jogador_atual;

                if (verificar_vitoria(tabuleiro, jogador_atual)) {
                    imprime_tabuleiro(tabuleiro);
                    printf("Jogador %c venceu!\n", jogador_atual);
                    jogo_ativo_partida = false; // jogo acabou
                } else if (verificar_empate(tabuleiro)) {
                    imprime_tabuleiro(tabuleiro);
                    printf("Deu velha!\n");
                    jogo_ativo_partida = false; // jogo acabou
                } else {
                    jogador_atual = (jogador_atual == 'X') ? 'O' : 'X';
                }
            } else {
                printf("Jogada invalida. Tente novamente.\n");
            }

            rounds++;
        }

        // opção de jogar novamente
        jogar_novamente = continuar_jogo(); 
    }

    printf("Obrigado por jogar!\n");
    return 0;
}
