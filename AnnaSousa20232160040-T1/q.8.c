#include <stdio.h>
#include "AnnaSousa20232160040.h"" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
#include <string.h>

#define NBARCOS 5

void ImprimirMatrizNaval(char linhas[10][50], int player){
  char i, j;

  printf("Jogador %d:\n", player+1);
  printf("  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9\n");
  for(i = 0, j = 'A'; i < 10; i++, j++){
    printf("------------------------------------------\n");
    printf("%c %s\n", j, linhas[i]);
  }
  printf("\n\n");

}

void PosicionarBarcos(char matriz[][10][50], int barcos[][5]){
  char posicao[255];
  int lin, col;
  int i, j;
  int repete = 1, repete2 = 1;
  int direcao;

  for(int p = 0; p <= 1; p++){  
    for(i = 4; i >= 1; i--){  
      while(1){
        if(barcos[p][i] <= 0) break;

        ImprimirMatrizNaval(matriz[p], p);
        printf("Jogador %d, posicione um barco de %d unidades (há %d restantes):\n", p+1, i, barcos[p][i]);
        scanf("%s", posicao);

        if(posicao[0] >= 'a' && posicao[0] <= 'j')
          posicao[0] -= 32;

        if(strlen(posicao) == 2 && (posicao[0] >= 'A' && posicao[0] <= 'J') && (posicao[1] >= '0' && posicao[1] <= '9')){
          col = 2 + (posicao[1] - '0')*4; //Converte char ao int correspondente ('0' = 48 e '3' = 51 em ASCII)
          lin = posicao[0] - 'A';

          if(matriz[p][lin][col] == ' '){
            repete2 = 1;

            while(repete2){
              repete2 = 0;

              if(i == 1){
                direcao = -1;
                matriz[p][lin][col] = 'N';
              } else{
                printf("Escolha a direção para onde aponta o outro extremo do barco:\n");
                printf("1 - Cima, 2 - Baixo, 3 - Esquerda, 4 - Direita, 0 - Voltar\n");
                scanf("%d", &direcao);
                switch(direcao){
                  case 1: 
                    if(lin - (i-1) >= 0){
                      for(j = 0; j < i && repete2 == 0; j++)
                        if(matriz[p][lin-j][col] != ' ')
                          repete2 = 1;
                      for(j = 0; j < i && repete2 == 0; j++)
                        matriz[p][lin-j][col] = 'N';
                    } else repete2 = 1;
                    break;
                  case 2: 
                    if(lin + (i-1) < 10){
                      for(j = 0; j < i && repete2 == 0; j++)
                        if(matriz[p][lin+j][col] != ' ')
                          repete2 = 1;
                      for(j = 0; j < i && repete2 == 0; j++)
                        matriz[p][lin+j][col] = 'N';
                    } else repete2 = 1;
                    break;
                  case 3: 
                    if(col - (i-1)*4 >= 2){
                      for(j = 0; j < i && repete2 == 0; j++)
                        if(matriz[p][lin][col-j*4] != ' ')
                          repete2 = 1;
                      for(j = 0; j < i && repete2 == 0; j++)
                        matriz[p][lin][col-j*4] = 'N';
                    } else repete2 = 1;
                    break;
                  case 4: 
                    if(col + (i-1)*4 <= 38){
                      for(j = 0; j < i && repete2 == 0; j++)
                        if(matriz[p][lin][col+j*4] != ' ')
                          repete2 = 1;
                      for(j = 0; j < i && repete2 == 0; j++)
                        matriz[p][lin][col+j*4] = 'N';
                    } else repete2 = 1;
                    break;
                  case 0: break;
                  default: printf("Opção inválida.\n"); repete2 = 1; break;
                }
              }  
              if(repete2 == 0 && direcao != 0)
                barcos[p][i]--;
              if(repete2 == 1 && direcao >= 1 && direcao <= 4)
                printf("O barco não cabe nesse espaço.\n");

            }
          } else printf("O barco não cabe nesse espaço.\n");

        } else{
          printf("Célula inválida.\n");
        }
      }

    }
    ImprimirMatrizNaval(matriz[p], p);
    printf("Acabaram os barcos! Pressione qualquer tecla para continuar.\n");
    getchar();
    getchar();
    system("clear");
  }

}

int BNJogar(char seujogo[][10][50], char oponente[][10][50], int vez){
  char posicao[255];
  int col, lin;
  int repete, achouN[2];
  int opp;
  char confirm;

  achouN[0] = 0;
  achouN[1] = 0;
  for(int p = 0; p <= 1; p++){
    for(int l = 0; l < 10; l++){
      if(strchr(seujogo[p][l], 'N') != NULL){
        achouN[p] = 1;
        break;
      }
    }
  }

  if(achouN[0] && achouN[1]){
    if(vez == 1){
      vez = 0;
      opp = 1;
    } else{
      vez = 1;
      opp = 0;
    }

    ImprimirMatrizNaval(seujogo[vez], vez);
    ImprimirMatrizNaval(oponente[opp], opp);

    repete = 1;
    while(repete){
      repete = 0;
      printf("Jogador %d, escolha a posição para atacar o oponente:\n", vez+1);
      scanf("%s", posicao);

      if(posicao[0] >= 'a' && posicao[0] <= 'j')
        posicao[0] -= 32;

      if(strlen(posicao) == 2 && (posicao[0] >= 'A' && posicao[0] <= 'J') && (posicao[1] >= '0' && posicao[1] <= '9')){
        col = 2 + (posicao[1] - '0')*4; //Converte char ao int correspondente ('0' = 48 e '3' = 51 em ASCII)
        lin = posicao[0] - 'A';

        if(seujogo[opp][lin][col] == 'N'){
          seujogo[opp][lin][col] = 'O';
          oponente[opp][lin][col] = 'O';
        } else if(seujogo[opp][lin][col] == ' '){
          seujogo[opp][lin][col] = 'X';
          oponente[opp][lin][col] = 'X';
        }  else{
          printf("Você já atirou nesse local!\n");
          repete = 1;
        }

      } else{ 
        printf("Opção inválida.\n");
        repete = 1;
      }
    }

    printf("Você atirou!\n");
    ImprimirMatrizNaval(oponente[opp], opp);
    printf("Pressione qualquer tecla para continuar.\n");
    getchar();
    getchar();
    system("clear");

    return BNJogar(seujogo, oponente, vez);
  } else{
    return vez+1;
  }
}

int main(){
  int barcos[2][5] = {{0, 3, NBARCOS-5, 1, 1}, {0, 3, NBARCOS-5, 1, 1}};
  char matriz[10][11];
  char seujogo[2][10][50];
  char oponente[2][10][50];
  int player = 0, vez = 0;

  for(int p = 0; p <= 1; p++){
    for(int i = 0; i < 10; i++){
      strcpy(seujogo[p][i], "|   |   |   |   |   |   |   |   |   |   ");
      strcpy(oponente[p][i], "|   |   |   |   |   |   |   |   |   |   ");
    }
  }

  PosicionarBarcos(seujogo, barcos);

  printf("O jogador %d venceu o jogo!\n", BNJogar(seujogo, oponente, 1));
  return 0;
}