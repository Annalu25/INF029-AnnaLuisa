// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome:
//  email:
//  Matrícula:
//  Semestre:

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "AnnaSousa20232160040.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
#include <string.h>
#include <locale.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
    char sMes[3];
    char sAno[5];
    int i; 

    for (i = 0; data[i] != '/'; i++){
        sDia[i] = data[i];	
    }
    if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
        sDia[i] = '\0';  // coloca o barra zero no final
    }else {
        dq.valido = 0;
    return dq;
  }  


    int j = i + 1; //anda 1 cada para pular a barra
    i = 0;

    for (; data[j] != '/'; j++){
        sMes[i] = data[j];
        i++;
    }

    if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
        sMes[i] = '\0';  // coloca o barra zero no final
    }else {
        dq.valido = 0;
    return dq;
  }


    j = j + 1; //anda 1 cada para pular a barra
    i = 0;

    for(; data[j] != '\0'; j++){
        sAno[i] = data[j];
        i++;
    }

    if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
        sAno[i] = '\0';  // coloca o barra zero no final
    }else {
        dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

    dq.valido = 1;

  return dq;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */

DataQuebrada separadata(char data[]){
    int i, j;
    char copia[5];
    DataQuebrada dma;
    dma.valido = 1;

      for(i = 0, j = 0; data[i] != '/'; i++, j++){
        copia[j] = data[i];
        if(j > 2) dma.valido = 0;
      }
      copia[j] = '\0';

      dma.iDia = atoi(copia);

      for(i += 1, j = 0; data[i] != '/'; i++, j++){
        copia[j] = data[i];
        if(j > 2) dma.valido = 0;
      }
      copia[j] = '\0';

      dma.iMes = atoi(copia);

      for(i += 1, j = 0; data[i] != '\0'; i++, j++){
        copia[j] = data[i];
      }
      copia[j] = '\0';

      dma.iAno = atoi(copia);
      if(dma.iAno > 0 && dma.iAno < 100)
        dma.iAno += 2000;

      return dma;
    }

    int bissexto(int ano){
      return (ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0;
    }

    int q1(char data[]){
      int datavalida = 1;
      int i, j;
      char copia[5];
      int dia, mes, ano;
      DataQuebrada dma;

      dma = separadata(data);
      if(!dma.valido)
        return 0;

      //Teste para os dias

      if(dma.iMes == 4 || dma.iMes == 6 || dma.iMes == 9 || dma.iMes == 11){
        if(dma.iDia < 1 || dma.iDia > 30){
          datavalida = 0;
        }
      } else if(dma.iMes != 2){
        if(dma.iDia < 1 || dma.iDia > 31){
          datavalida = 0;
        }
      }

      if(bissexto(dma.iAno)){
        if(dma.iMes == 2 && (dma.iDia < 1 || dma.iDia > 29)){
          datavalida = 0;
        }
      } else {
        if(dma.iMes == 2 && (dma.iDia < 1 || dma.iDia > 28)){
          datavalida = 0;
        }
      }

      //Teste para os meses

      if(dma.iMes < 1 || dma.iMes > 12){
        datavalida = 0;
      }

      //Teste para o ano

      if(dma.iAno <= 0){
        datavalida = 0;
      }

      return datavalida;
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    DataQuebrada idata, fdata;
        int DiasMes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        //calcule os dados e armazene nas três variáveis a seguir
        DiasMesesAnos dma = {0,0,0,0};

        if (q1(datainicial) == 0){
          dma.retorno = 2;
          return dma;
        }else if (q1(datafinal) == 0){
          dma.retorno = 3;
          return dma;
        }else{
          //verifique se a data final não é menor que a data inicial
          idata = separadata(datainicial);
          fdata = separadata(datafinal);

          if(idata.iAno > fdata.iAno){
            dma.retorno = 4;
            return dma;
          } else if(idata.iAno == fdata.iAno){
            if(idata.iMes > fdata.iMes){
              dma.retorno = 4;
              return dma;
            } else if(idata.iMes == fdata.iMes){
              if(idata.iDia > fdata.iDia){
                dma.retorno = 4;
                return dma;
              }
            }
          }

          //calcule a distancia entre as datas      
          for(dma.qtdAnos = 0; idata.iAno + dma.qtdAnos != fdata.iAno; dma.qtdAnos++);

          if(bissexto(fdata.iAno)) DiasMes[2] = 29;

          if(idata.iMes == 2 && idata.iDia == 29 && fdata.iMes == 2 && fdata.iDia == 28 && bissexto(fdata.iAno) == 0)
              idata.iDia--;
            else if(fdata.iMes == 2 && fdata.iDia == 29 && idata.iMes == 2 && idata.iDia == 28 && bissexto(idata.iAno) == 0)
              fdata.iDia--;

          if((idata.iMes < fdata.iMes) || (idata.iMes == fdata.iMes && idata.iDia <= fdata.iDia)){
              for(dma.qtdMeses = 0; idata.iMes + dma.qtdMeses != fdata.iMes; dma.qtdMeses++);
              if(idata.iDia <= fdata.iDia){
                  dma.qtdDias = fdata.iDia - idata.iDia;
              } else{
                  dma.qtdMeses--;
                  dma.qtdDias = DiasMes[idata.iMes + dma.qtdMeses] - idata.iDia + fdata.iDia;
              }

          } else{
              dma.qtdAnos--;


              if(idata.iDia > fdata.iDia){
                dma.qtdMeses = 12 - idata.iMes + fdata.iMes - 1;
                dma.qtdDias = DiasMes[dma.qtdMeses+1] - (idata.iDia - fdata.iDia);
              } else{
                dma.qtdMeses = 12 - idata.iMes + fdata.iMes;
                dma.qtdDias = fdata.iDia - idata.iDia;
              }
            }

           // printf("\nfDias: %d Meses: %d Anos: %d\n", dma.qtdDias, dma.qtdMeses, dma.qtdAnos);

          //se tudo der certo
          dma.retorno = 1;
          return dma;

        }

}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;
        int i;
        char copiatexto[250];

        strcpy(copiatexto, texto);

        if(isCaseSensitive){
          for(i = 0; texto[i] != '\0'; i++){
            if(texto[i] == c)
              qtdOcorrencias++;        
          }
        }else{
          if(c >= 65 && c <= 90)
            c += 32;

          for(i = 0; copiatexto[i] != '\0'; i++){
            if(copiatexto[i] >= 65 && copiatexto[i] <= 90)
              copiatexto[i] += 32;
          }

          for(i = 0; copiatexto[i] != '\0'; i++){
            if(copiatexto[i] == c)
              qtdOcorrencias++;
          }

        }

        return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int i, j, k = 0;
    int iposicao, fposicao;
    wchar_t copiaT[250];
    wchar_t copiaB[50];

    setlocale(LC_ALL, "");

    mbstowcs(copiaT, strTexto, 250);
    mbstowcs(copiaB, strBusca, 50);


    for(i = 0, j = 0; copiaT[i] != '\0'; i++){
      if(copiaT[i] == copiaB[j]){
        if(j == 0){
          iposicao = i + 1;
        }

        j++;
      } else{
        j = 0;
      }

      if(copiaB[j] == '\0'){
        qtdOcorrencias++;
        posicoes[k] = iposicao;
        k++;
        posicoes[k] = i + 1;
        k++;
        j = 0;
      }
    }


    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
    int invertido = 0;
    for (; num != 0; num /= 10) {
        int digito = num % 10;
        invertido = invertido * 10 + digito;  
    }
    num = invertido;
    
    return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    char strBase[50], strBusca[50];
    sprintf(strBase, "%d", numerobase);  
    sprintf(strBusca, "%d", numerobusca); 
    int qtdOcorrencias = 0;

        for (int i = 0; strBase[i] != '\0'; i++) {
            if (strBase[i] == strBusca[0]) {
                qtdOcorrencias++; 
            }
        }

        return qtdOcorrencias; 
}