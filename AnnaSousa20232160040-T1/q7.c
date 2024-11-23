#include <stdio.h>
#include "AnnaSousa20232160040.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
#include <string.h>

void ImprimirMatriz(char matriz[][3]){
  printf("  1   2   3\n");
  printf("A %c | %c | %c\n", matriz[0][0], matriz[0][1], matriz[0][2]);
  printf("  ---------\n");
  printf("B %c | %c | %c\n", matriz[1][0], matriz[1][1], matriz[1][2]);
  printf("  ---------\n");
  printf("C %c | %c | %c\n", matriz[2][0], matriz[2][1], matriz[2][2]);
}

void Imprimirjogada(int p, char posicao[]){
  printf("\nJogador %d, informe sua jogada:\n", p+1);
  scanf("%s", posicao);
  // *strchr(posicao, '\n') = '\0';
  // printf("len %ld %c\n", strlen(posicao), posicao[1]);
}

int main(){
  char matriz[3][3] = {
    ' ', ' ', ' ',
    ' ', ' ', ' ',
    ' ', ' ', ' '
  };
  int player = 0;
  char marca[2] = {'X', 'O'};
  char posicao[255];
  int col, lin;
  int i, j, troca;

  ImprimirMatriz(matriz);

  while(strchr(*matriz, ' ') != NULL){
    troca = 0;
    Imprimirjogada(player, posicao);

    if(posicao[0] >= 'a' && posicao[0] <= 'c')
      posicao[0] -= 32;

    if(strlen(posicao) == 2 && (posicao[0] >= 'A' && posicao[0] <= 'C') && (posicao[1] >= '1' && posicao[1] <= '3')){
      col = posicao[1] - '0' - 1; //Converte char ao int correspondente ('0' = 48 e '3' = 51 em ASCII)
      lin = posicao[0] - 'A';

      if(matriz[lin][col] == ' '){
        matriz[lin][col] = marca[player];
        troca = 1;
      } else{
        printf("Célula já preenchida.\n\n");
      }

    } else{
      printf("Célula inválida.\n\n");
    }

    ImprimirMatriz(matriz);


    if((matriz[lin][0] == marca[player] && matriz[lin][1] == marca[player] && matriz[lin][2] == marca[player]) || (matriz[0][col] == marca[player] && matriz[1][col] == marca[player] && matriz[2][col] == marca[player]) || (matriz[0][0] == marca[player] && matriz[1][1] == marca[player] && matriz[2][2] == marca[player]) || (matriz[0][2] == marca[player] && matriz[1][1] == marca[player] && matriz[2][0] == marca[player])){
      printf("\nO jogador %d ganhou!\n", player+1);
      return 0;
    }

    if(player && troca)
      player = 0;
    else 
      player = 1;
  }

  printf("\nDeu velha!\n");
  return 0; 
}