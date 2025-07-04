#include <stdio.h>
#include <stdbool.h>

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

// Função para verificar se o jogo empatou

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

        return 1; // 1 significa sim

    } else if (continuar == 'n') {

        return 0; // 0 significa não

    } else {

        printf("Resposta invalida. Por favor, digite 's' ou 'n'.\n");

        return continuar_jogo(); // Chama a função novamente para começar do inicio

    }

}



//função 5

int main() {

    char tabuleiro[3][3];

    char jogador_atual;

    int linha, coluna;

    bool jogar_novamente = true; // Controla o loop de múltiplos jogos



    printf("Bem-vindo ao Jogo da Velha!\n");



    // Loop externo: para o usuário jogar uma nova partida

    while (jogar_novamente) {

        // --- NOVO JOGO ---

        // 1. Limpa o tabuleiro

        for (int i = 0; i < 3; i++) {

            for (int j = 0; j < 3; j++) {

                tabuleiro[i][j] = ' '; 

            }

        }

        // 2. define o jogador inicial

        jogador_atual = 'X'; 

        // 3. Ativa o jogo atual

        bool jogo_ativo_partida = true; // Variável para controlar uma unica partida



        // Loop interno: gerencia o andamento de uma unica partida

        while (jogo_ativo_partida) {

            imprime_tabuleiro(tabuleiro);



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

                    printf("O jogo empatou!\n");

                    jogo_ativo_partida = false; // a partida atual terminou

                } else {

                    jogador_atual = (jogador_atual == 'X') ? 'O' : 'X';

                }

            } else {

                printf("Jogada invalida. Tente novamente.\n");

            }

        } // fim do loop de uma partida



        // após a partida terminar, pergunte ao usuário se ele quer jogar novamente

        jogar_novamente = continuar_jogo(); 

    } // Fim do loop de múltiplos jogos



    printf("Obrigado por jogar!\n");

    return 0;

}