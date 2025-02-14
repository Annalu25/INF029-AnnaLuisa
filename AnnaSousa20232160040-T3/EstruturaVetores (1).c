#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

typedef struct {
  int *estruturaAuxiliar;
  int tamanho;
  int quantidadeElementos;
} VetorPrincipal;

VetorPrincipal principal[TAM];

VetorPrincipal *estrutura;

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho) {
  int retorno = 0;

  // Verifica se a posição é válida (deve estar entre 1 e TAM)
  if (posicao < 1 || posicao > TAM) {
    retorno = POSICAO_INVALIDA;
    return retorno;
  }

  // Verifica se o tamanho é válido (maior que 0)
  if (tamanho <= 0) {
    retorno = TAMANHO_INVALIDO;
    return retorno;
  }

  // Ajusta a posição para começar de 0
  posicao--;
  VetorPrincipal *estrutura = &principal[posicao];

  // Se a estrutura auxiliar já existir, retorna JA_TEM_ESTRUTURA_AUXILIAR
  if (estrutura->estruturaAuxiliar != NULL) {
    retorno = JA_TEM_ESTRUTURA_AUXILIAR;
    return retorno;
  }

  // Aloca a estrutura auxiliar
  estrutura->estruturaAuxiliar = (int *)malloc(sizeof(int) * tamanho);
  if (estrutura->estruturaAuxiliar == NULL) {
    retorno = TAMANHO_INVALIDO;
    return retorno;
  }

  estrutura->tamanho = tamanho;
  estrutura->quantidadeElementos = 0;

  retorno = SUCESSO;
  return retorno;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor) {
  int retorno = 0;

  // Verifica se a posição é válida (deve estar entre 1 e TAM)
  if (posicao < 1 || posicao > TAM) {
    retorno = POSICAO_INVALIDA;
    return retorno;
  }

  posicao--; // Ajusta a posição para começar de 0
  VetorPrincipal *estrutura = &principal[posicao];

  // Verifica se a estrutura auxiliar existe
  if (estrutura->estruturaAuxiliar == NULL) {
    retorno = SEM_ESTRUTURA_AUXILIAR;
    return retorno;
  }

  // Verifica se há espaço na estrutura auxiliar
  if (estrutura->quantidadeElementos >= estrutura->tamanho) {
    retorno = SEM_ESPACO;
    return retorno;
  }

  // Insere o valor no próximo espaço disponível
  estrutura->estruturaAuxiliar[estrutura->quantidadeElementos] = valor;

  // Atualiza a quantidade de elementos
  estrutura->quantidadeElementos++;

  retorno = SUCESSO;
  return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar
da seguinte forma [3, 8, 7,  ,  ,  ]. Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao) {
  int retorno = 0;

  // Verifica se a posição é válida (deve estar entre 1 e TAM)
  if (posicao < 1 || posicao > TAM) {
    return POSICAO_INVALIDA;
  }

  posicao--; // Ajusta para a posição correta do vetor (de 1 para 0)
  VetorPrincipal *estrutura = &principal[posicao];

  // Verifica se a estrutura auxiliar existe
  if (estrutura->estruturaAuxiliar == NULL) {
    return SEM_ESTRUTURA_AUXILIAR;
  }

  // Verifica se a estrutura auxiliar está vazia
  if (estrutura->quantidadeElementos == 0) {
    return ESTRUTURA_AUXILIAR_VAZIA;
  }

  // Realiza a exclusão lógica, diminuindo a quantidade de elementos
  estrutura->quantidadeElementos--;

  return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições
anteriores ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o
valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ] Obs. Esta é
uma exclusão lógica Rertono (int) SUCESSO - excluido com sucesso 'valor' da
estrutura na posição 'posicao' ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
  int retorno = 0;

  // Verifica se a posição é válida
  if (posicao < 1 || posicao > TAM) {
    return POSICAO_INVALIDA;
  }

  posicao--; // Ajusta a posição para o índice correto (de 1 para 0)
  VetorPrincipal *estrutura = &principal[posicao];

  // Verifica se a estrutura auxiliar existe
  if (estrutura->estruturaAuxiliar == NULL) {
    return SEM_ESTRUTURA_AUXILIAR;
  }

  // Verifica se a estrutura auxiliar está vazia
  if (estrutura->quantidadeElementos == 0) {
    return ESTRUTURA_AUXILIAR_VAZIA;
  }

  // Percorre os elementos da estrutura auxiliar procurando o valor
  for (int i = 0; i < estrutura->quantidadeElementos; i++) {
    if (estrutura->estruturaAuxiliar[i] == valor) {
      // Move os elementos subsequentes para as posições anteriores
      for (int j = i; j < estrutura->quantidadeElementos - 1; j++) {
        estrutura->estruturaAuxiliar[j] = estrutura->estruturaAuxiliar[j + 1];
      }

      // Diminui a quantidade de elementos
      estrutura->quantidadeElementos--;

      // Retorna SUCESSO imediatamente
      return SUCESSO;
    }
  }

  // Se não encontrou o número, retorna NUMERO_INEXISTENTE
  return NUMERO_INEXISTENTE;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao) {
  int retorno = 0;
  if (posicao < 1 || posicao > 10) {
    retorno = POSICAO_INVALIDA;
  } else
    retorno = SUCESSO;

  return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição
'posicao' SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar POSICAO_INVALIDA -
Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {

  int retorno = 0;

  // Verifica a validade da posição
  if (posicao < 1 || posicao > TAM) {
    return POSICAO_INVALIDA;
  }

  posicao--; // Ajusta a posição para o índice correto (de 1 para 0)
  VetorPrincipal *estrutura = &principal[posicao];

  // Verifica se existe uma estrutura auxiliar
  if (estrutura->estruturaAuxiliar == NULL) {
    return SEM_ESTRUTURA_AUXILIAR;
  }

  // Preenche o vetorAux com os dados da estrutura auxiliar
  for (int i = 0; i < estrutura->quantidadeElementos; i++) {
    vetorAux[i] = estrutura->estruturaAuxiliar[i];
  }

  retorno = SUCESSO;
  return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao
(1..10)'. os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao
(1..10)' SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar POSICAO_INVALIDA -
Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {

  int retorno = 0;

  // Verifica a validade da posição
  if (posicao < 1 || posicao > TAM) {
    return POSICAO_INVALIDA;
  }

  VetorPrincipal *estrutura = &principal[posicao - 1];

  // Verifica se existe uma estrutura auxiliar
  if (estrutura->estruturaAuxiliar == NULL) {
    return SEM_ESTRUTURA_AUXILIAR;
  }

  // Preenche o vetorAux com os dados da estrutura auxiliar
  for (int i = 0; i < estrutura->quantidadeElementos; i++) {
    vetorAux[i] = estrutura->estruturaAuxiliar[i];
  }

  // Ordena os dados em ordem crescente
  for (int i = 0; i < estrutura->quantidadeElementos - 1; i++) {
    for (int j = i + 1; j < estrutura->quantidadeElementos; j++) {
      if (vetorAux[i] > vetorAux[j]) {
        int temp = vetorAux[i];
        vetorAux[i] = vetorAux[j];
        vetorAux[j] = temp;
      }
    }
  }

  retorno = SUCESSO;
  return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição
'posicao' TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares
estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {

  int retorno = 0;
  int k = 0; // Índice para armazenar os dados no vetorAux
  int todasVazias =
      1; // Flag para verificar se todas as estruturas estão vazias

  // Percorrer todas as estruturas auxiliares
  for (int i = 0; i < TAM; i++) {
    VetorPrincipal *estrutura = &principal[i];

    // Verifica se a estrutura auxiliar existe e não está vazia
    if (estrutura->estruturaAuxiliar != NULL &&
        estrutura->quantidadeElementos > 0) {
      todasVazias = 0; // Se encontrar alguma estrutura com elementos, marca
                       // como não vazia

      // Preenche o vetorAux com os dados da estrutura auxiliar
      for (int j = 0; j < estrutura->quantidadeElementos; j++) {
        vetorAux[k++] = estrutura->estruturaAuxiliar[j];
      }
    }
  }

  // Se todas as estruturas auxiliares estiverem vazias
  if (todasVazias) {
    retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
  } else {
    retorno = SUCESSO;
  }

  return retorno;
}
/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição
'posicao' TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares
estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {

  int retorno = 0;
  int k = 0;
  for (int i = 0; i < TAM; i++) {
    if (principal[i].estruturaAuxiliar != NULL &&
        principal[i].quantidadeElementos > 0) {
      for (int j = 0; j < principal[i].quantidadeElementos; j++) {
        vetorAux[k++] = principal[i].estruturaAuxiliar[j];
      }
    }
  }
  if (k == 0) {
    retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
  } else {
    for (int i = 0; i < k - 1; i++) {
      for (int j = i + 1; j < k; j++) {
        if (vetorAux[i] > vetorAux[j]) {
          int temp = vetorAux[i];
          vetorAux[i] = vetorAux[j];
          vetorAux[j] = temp;
        }
      }
    }
    retorno = SUCESSO;
  }
  return retorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o
novo tamanho 'novoTamanho' + tamanho atual Suponha o tamanho inicial = x, e novo
tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser
sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {

  int retorno = 0;
  if (posicao < 1 || posicao > TAM) {
    retorno = POSICAO_INVALIDA;
  } else {
    VetorPrincipal *vp = &principal[posicao - 1];
    if (vp->estruturaAuxiliar == NULL) {
      retorno = SEM_ESTRUTURA_AUXILIAR;
    } else {
      int novoTamanhoFinal = vp->tamanho + novoTamanho;
      if (novoTamanhoFinal < 1) {
        retorno = NOVO_TAMANHO_INVALIDO;
      } else {
        int *novoArray =
            realloc(vp->estruturaAuxiliar, novoTamanhoFinal * sizeof(int));
        if (novoArray == NULL) {
          retorno = SEM_ESPACO_DE_MEMORIA;
        } else {
          vp->estruturaAuxiliar = novoArray;
          vp->tamanho = novoTamanhoFinal;
          if (vp->quantidadeElementos > novoTamanhoFinal) {
            vp->quantidadeElementos = novoTamanhoFinal;
          }
          retorno = SUCESSO;
        }
      }
    }
  }
  return retorno;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da
posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da
estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao) {

  int retorno = 0;
  if (posicao < 1 || posicao > TAM) {
    retorno = POSICAO_INVALIDA;
  } else {
    VetorPrincipal *vp = &principal[posicao - 1];
    if (vp->estruturaAuxiliar == NULL) {
      retorno = SEM_ESTRUTURA_AUXILIAR;
    } else if (vp->quantidadeElementos == 0) {
      retorno = ESTRUTURA_AUXILIAR_VAZIA;
    } else {
      retorno = vp->quantidadeElementos;
    }
  }
  return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes
em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote() {
  No *cabecote = (No *)malloc(sizeof(No));
  if (cabecote == NULL) {
    return NULL;
  }
  cabecote->prox = NULL;

  No *ultimo = cabecote;
  int temElementos = 0;

  for (int i = 0; i < TAM; i++) {
    if (principal[i].estruturaAuxiliar != NULL && principal[i].quantidadeElementos > 0) {
      for (int j = 0; j < principal[i].quantidadeElementos; j++) {
        No *novo = (No *)malloc(sizeof(No));
        if (novo == NULL) {
          No *atual = cabecote->prox;
          while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
          }
          free(cabecote);
          return NULL;
        }
        novo->conteudo = principal[i].estruturaAuxiliar[j];
        novo->prox = NULL;
        ultimo->prox = novo;
        ultimo = novo;
        temElementos = 1;
      }
    }
  }

  if (!temElementos) {
    free(cabecote);
    return NULL;
  }
  return cabecote;
}
/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em
vetorAux. Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
  int i = 0;
  No *atual = inicio->prox;
  while (atual != NULL && i < 10) {
    vetorAux[i] = atual->conteudo;
    atual = atual->prox;
    i++;
  }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio) {
  while (*inicio != NULL) {
    No *temp = *inicio;
    *inicio = (*inicio)->prox;
    free(temp);
  }
}

int salvarArquivo(const char *Arquivolista){
    FILE *fp = fopen(Arquivolista, "w");
    if(fp == NULL){
        perror("fopen");
        return 0;
    }
    for(int i = 0; i < TAM; i++){
        if(i>0){
            fprintf(fp, "\n");
        }
        fprintf(fp, "%d %d %d", i+1, principal[i].quantidadeElementos, principal[i].tamanho);
        for(int j = 0; j < principal[i].quantidadeElementos; j++){
            fprintf(fp, " %d", principal[i].estruturaAuxiliar[j]);
        }
    }
    fclose(fp);
    return 1;
}

  int recuperarArquivo(const char *Arquivolista){
      int aux, quantidadeElementos;
      int tamanho, valor, retorno;
      FILE *fp = fopen(Arquivolista, "r");

      if(fp == NULL){
          printf("Não há arquivo!\n");
          return 0;
      }

      while(fscanf(fp, "%d %d %d", &aux, &quantidadeElementos, &tamanho) == 3){
        if((aux < 1 || aux > TAM) || (tamanho < 0) || (quantidadeElementos < 0 || quantidadeElementos > tamanho)){
            fclose(fp);
            return 0;
        }

          if(tamanho > 0){
              retorno = criarEstruturaAuxiliar(aux, tamanho);
              if(retorno != SUCESSO){
                  printf("Estrutura auxiliar não criada\n");
                  fclose(fp);
                  return 0;
              }

              for(int i = 0; i < quantidadeElementos; i++){
                  if(fscanf(fp, "%d", &valor) != 1){
                      printf("Valor não possível de ler\n");
                      fclose(fp);
                      return 0;
                  }
                  if(i < tamanho){
                      retorno = inserirNumeroEmEstrutura(aux, valor);
                      if(retorno != SUCESSO){
                          printf("Não é possível adicionar o valor na estrutura\n");
                          fclose(fp);
                          return 0;
                      }
                  }
              }
          }
      }
      fclose(fp);
      return 1;
  }


  /*
  Objetivo: inicializa o programa. deve ser chamado ao inicio do programa

  */

void inicializar() { 
  const char *Arquivolista = "Arquivolista.txt"; 
  FILE *fp;
  
  fp = fopen(Arquivolista, "r"); 
  
  if(fp == NULL){
      fp = fopen(Arquivolista, "w"); 
      if (fp == NULL) {
          return;
      }
  }else{
      printf("Arquivo encontrado.\n");
  }
  fclose(fp); 

  estrutura = malloc(sizeof(VetorPrincipal) * TAM);
  
  for (int i = 0; i < TAM; i++) {
    principal[i].estruturaAuxiliar = NULL;
    principal[i].tamanho = 0;
    principal[i].quantidadeElementos = 0;
  }
  recuperarArquivo(Arquivolista);
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar() {
  const char *Arquivolista = "Arquivolista.txt";
  int retorno = salvarArquivo(Arquivolista);

  if(retorno != 1){
      printf("Houve um erro ao salvar o arquivo\n");
  }
  for (int i = 0; i < TAM; i++) {
    if (principal[i].estruturaAuxiliar != NULL) {
      free(principal[i].estruturaAuxiliar);
      principal[i].estruturaAuxiliar = NULL;
    }
  }
  free(estrutura);
  estrutura = NULL;
}
