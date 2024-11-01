#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define MAX_PESSOAS 50
#define MAX_DIS 10
#define MAX_DIGITOS 13
#define MAX_CHAR 102
#define MIN_CHAR 3
#define MAX_LINHA 1000
#define POUCASDIS 3
#define MAX_NOME 102
#define VAGAS 40
#define TRUE 1
#define FALSE 0
#define ERRO -20  
#define ALUNO 0
#define PROF 1
#define DIS 2


typedef struct{
    int dia;
    int mes;
    int ano;
  } Data;

typedef struct{
  int matriculados[MAX_PESSOAS];
  int qtdTurma;
} MatricularDisciplina;

typedef struct{
  int matricula;
  char tipo_mat[MAX_DIGITOS];
  char nome[MAX_NOME];
  char sexo[MAX_DIGITOS];
  Data nas;
  char CPF[MAX_DIGITOS];
} Pessoa;

typedef struct{
  char nome[MAX_NOME];
  int codigo;
  int semestre;
  int matProf;
  MatricularDisciplina AlDis;
} Disciplinas;

//Todas as funções utilizadas
void ListarAlunosdaDisciplina();
int QuantasVezesOAlunoApareceu();
void AlunosComPoucasDisciplinas();
MatricularDisciplina ProcurarPraExcluir();
void ImprimirTurma();
MatricularDisciplina QualAlunoPraDel();
Disciplinas DelAlunoDeDis();
MatricularDisciplina QualAlunoPraAdd();
Disciplinas MatAlunoEmDis();
void sexocadastro();
Data nascimentocadastro();
void nomecadastro();
void cpfcadastro();
Pessoa cadastroaluno();
Pessoa cadastroprof();
void BuscaChar();
int BuscaPessoaChar();
int semestrecadastroDisciplina();
int MatProfcadastroDisciplina();
void nomecadastroDisciplina();
Disciplinas cadastroDiscplina();
int excluirCadastro();
int excluirDisciplina();
Pessoa atualizarcadastro();
Disciplinas atualizarDisciplina();
void ImprimirCadastro();
void ImprimirDisciplina();
void Listar();
void ListarDisciplinas();
void ListarDisciplinaPorVagas();
int menu_secundario();
int menu_principal();
void continuar();
int Temcadastros();
int main();
int MenuListasDisciplinas();
int menuListas();
void listaCrescente();
void listaDecrescente();
void listaPorData();
void listaMatricula();
void listaSexo();
int funcaoBusca();
int funcaoBuscaDisciplinas();
int funcaoBuscaTurma();
Pessoa letraMaiuscula();
void BuscarAniversario();


void ListarAlunosdaDisciplina(int qtdDis, Disciplinas listaDis[], int qtdProf, Pessoa listaProf[], int qtdAl, Pessoa listaAl[]){
  int cod = ERRO;
  int contatoDis;

  system("clear");
  ListarDisciplinas(qtdDis, qtdProf, listaDis, listaProf);
  printf("Informe a numeração da disciplina:\n");
  scanf("%d", &cod);
  contatoDis = funcaoBuscaDisciplinas(qtdDis, cod, listaDis);
  getchar();

  system("clear");
  if(contatoDis < qtdDis){
    ImprimirTurma(contatoDis, listaDis, qtdProf, listaProf, qtdAl, listaAl);
  } else{
    printf("Não existe essa numeração.\n");
  }
}

int QuantasVezesOAlunoApareceu(int mat, int qtdAlunosNaDis, int matAlunos[]){
  int i;
  int vezes = 0;
  for(i = 0; i < qtdAlunosNaDis; i++){
    if(matAlunos[i] == mat){
      vezes++;
    }
  }
  return vezes;
}

void AlunosComPoucasDisciplinas(Pessoa listaalunos[], Disciplinas listadisc[], int qtdAlunos, int qtdDisc){
  int disciplinas = 0;
  int contagem = 0;
  system("clear");
  for(int i=0; i<qtdAlunos; i++){
    for(int j=0; j<qtdDisc; j++){
      if(QuantasVezesOAlunoApareceu(listaalunos[i].matricula, listadisc[j].AlDis.qtdTurma, listadisc[j].AlDis.matriculados) > 0){
        disciplinas++;
      }
    } 
    if(disciplinas < POUCASDIS){
      ImprimirCadastro(i, listaalunos);
      contagem++;
    }
    disciplinas = 0;
  }
  if(contagem == 0){
    printf("Nenhum aluno matriculado nesses requisitos");
  }
  getchar();
}

MatricularDisciplina ProcurarPraExcluir(MatricularDisciplina Aldis, int qtdAlunos, Pessoa listaalunos[]){
  int posicao, j, z;
  for(j = 0; j < Aldis.qtdTurma; j++){
      posicao = funcaoBusca(qtdAlunos, Aldis.matriculados[j], listaalunos);
    if(posicao >= qtdAlunos){
      for(int z = j; z < Aldis.qtdTurma; z++)
        Aldis.matriculados[z] = Aldis.matriculados[z+1];
      Aldis.qtdTurma--;
    }
  }
  return Aldis;
}

void ImprimirTurma(int contatoDis, Disciplinas listaDis[], int qtdProf, Pessoa listaProf[], int qtdAl, Pessoa listaAl[]){
  int achou, resultado;
  ImprimirDisciplina(qtdProf, contatoDis, listaDis, listaProf);
  printf("\nLista de alunos:\n\n");

  if(listaDis[contatoDis].AlDis.qtdTurma <= 0)
    printf("Não há alunos matriculados nessa disciplina.\n");

  for(int j = 0; j < listaDis[contatoDis].AlDis.qtdTurma; j++){
    achou = funcaoBusca(qtdAl, listaDis[contatoDis].AlDis.matriculados[j], listaAl);
    if(achou < qtdAl){
      ImprimirCadastro(achou, listaAl);
    }
  }
}

MatricularDisciplina QualAlunoPraDel(Disciplinas Turma, int qtdAl, Pessoa listaAl[], int qtdProf, Pessoa listaProf[], int contatoDis, Disciplinas listaDis[]){
  int mat = ERRO;
  int contatoAl, contatoTurma;

  while(1){
    system("clear");
    ImprimirTurma(contatoDis, listaDis, qtdProf, listaProf, qtdAl, listaAl);
    printf("\nInforme a matrícula do aluno que quer excluir da disciplina: \n");
    scanf("%d", &mat);

    contatoAl = funcaoBusca(qtdAl, mat, listaAl);

    contatoTurma = funcaoBuscaTurma(Turma.AlDis.qtdTurma, mat, Turma.AlDis.matriculados);

    system("clear");
    if(contatoAl >= qtdAl){
      printf("\nNão existe a matricula inserida.\n");
      getchar();
      continuar();
    } else if(contatoTurma < Turma.AlDis.qtdTurma){ 
      for(int z = contatoTurma; z < Turma.AlDis.qtdTurma; z++)
        Turma.AlDis.matriculados[z] = Turma.AlDis.matriculados[z+1];
      Turma.AlDis.qtdTurma--;
      break;
    } else{
      printf("\nEsse aluno não está matriculado nesta disciplina.\n");
      getchar();
      continuar();
    }
  }

  return Turma.AlDis;
}

Disciplinas DelAlunoDeDis(int qtdDis, Disciplinas listaDis[], int qtdProf, Pessoa listaProf[], int qtdAlunos, Pessoa listaAl[]){
  int cod = ERRO;
  int contatoDis;
  int opcao = ERRO, resultado;

  system("clear");

  if(qtdDis <= 0){
    getchar();
    printf("Não é possível pois não há disciplinas.\n");
    return listaDis[qtdDis];
  } else if(qtdAlunos <= 0){
    getchar();
    printf("Não é possivel pois não há alunos.\n");
    return listaDis[qtdDis];
  }

  ListarDisciplinas(qtdDis, qtdProf, listaDis, listaProf);
  printf("Informe a numeração da disciplina:\n");
  scanf("%d", &cod);
  contatoDis = funcaoBuscaDisciplinas(qtdDis, cod, listaDis);
  getchar();

  if(contatoDis < qtdDis){
    while(1){
      listaDis[contatoDis].AlDis = ProcurarPraExcluir(listaDis[contatoDis].AlDis, qtdAlunos, listaAl);

      if(listaDis[contatoDis].AlDis.qtdTurma <= 0){
        system("clear");
        printf("\nSem alunos.\n");
        break;
      }

      listaDis[contatoDis].AlDis = QualAlunoPraDel(listaDis[contatoDis], qtdAlunos, listaAl, qtdProf, listaProf, contatoDis, listaDis);

      system("clear");
      printf("Feita com sucesso!\n\n");
      ImprimirTurma(contatoDis, listaDis, qtdProf, listaProf, qtdAlunos, listaAl);
      printf("\n\nExcluir outro aluno?\n1 p/ Sim\nQualquer valor para Não\n");
      scanf("%d", &opcao);
      getchar();
      if(opcao != 1) break;
    }
  } else{
    system("clear");
    printf("Não existe a numeração inserida.\n");
  }

  return listaDis[qtdDis];
}

MatricularDisciplina QualAlunoPraAdd(Disciplinas Turma, int qtdAl, Pessoa listaAl[]){
  int mat = ERRO;
  int contatoAl;

  while(1){
    system("clear");
    Listar(qtdAl, listaAl);
    printf("%s\nInforme a matricula do aluno que quer colocar nesta disciplina: \n", Turma.nome);
    scanf("%d", &mat);

    contatoAl = funcaoBusca(qtdAl, mat, listaAl);
    int vezes = QuantasVezesOAlunoApareceu(mat, Turma.AlDis.qtdTurma, Turma.AlDis.matriculados);

    system("clear");
    if(contatoAl >= qtdAl){
      printf("\nNão existe essa matrícula.\n");
      getchar();
      continuar();
    } else if(vezes > 0){ 
      printf("\nEsse aluno ja está matriculado.\n");
      getchar();
      continuar();
    } else{
      Turma.AlDis.matriculados[Turma.AlDis.qtdTurma] = listaAl[contatoAl].matricula;
      Turma.AlDis.qtdTurma++;
      break;
    }
  }

  return Turma.AlDis;
}

Disciplinas MatAlunoEmDis(int qtdDis, Disciplinas listaDis[], int qtdProf, Pessoa listaProf[], int qtdAlunos, Pessoa listaAl[]){
  int cod = ERRO;
  int contatoDis;
  int opcao = ERRO, resultado;

  system("clear");
  if(qtdDis <= 0){
    printf("Não há matérias.\n");
    return listaDis[qtdDis];
  } else if(qtdAlunos <= 0){
    printf("Não há alunos.\n");
    return listaDis[qtdDis];
  }

  system("clear");
  ListarDisciplinas(qtdDis, qtdProf, listaDis, listaProf);
  printf("Informe a numeração da disciplina:\n");
  scanf("%d", &cod);
  contatoDis = funcaoBuscaDisciplinas(qtdDis, cod, listaDis);

  if(contatoDis < qtdDis){
    while(1){
      listaDis[contatoDis].AlDis = ProcurarPraExcluir(listaDis[contatoDis].AlDis, qtdAlunos, listaAl);

      if(listaDis[contatoDis].AlDis.qtdTurma >= qtdAlunos){
        system("clear");
        printf("\nTodos os alunos já foram matriculados.\n");
        break;
      }

      listaDis[contatoDis].AlDis = QualAlunoPraAdd(listaDis[contatoDis], qtdAlunos, listaAl);

      system("clear");
      printf("Feita com sucesso!\n\n");
      ImprimirTurma(contatoDis, listaDis, qtdProf, listaProf, qtdAlunos, listaAl);
      printf("\n\nMatricular outro aluno?\n1 p/ Sim\n Qualquer valor para Não\n");
      scanf("%d", &opcao);
      getchar();
      if(opcao != 1) break;
    }
  } else{
    getchar();
    system("clear");
    printf("Não existe essa numeração.\n");
  }

  return listaDis[qtdDis];
}

//Cadastro de sexo
void sexocadastro(char * p, char * tipo){
  system("clear");
  int repeat = TRUE;
  char sexo[MAX_DIGITOS];
  int sexo_opcao;
  while(repeat){
    repeat = FALSE;
    printf("Digite o sexo %s: \n1 p/ masculino\n2 p/ feminino\n3 p/ outro\n", tipo);
    scanf("%d", &sexo_opcao);
    getchar();
    switch(sexo_opcao){
        case 1: strcpy(p, "Masculino"); break;
        case 2: strcpy(p, "Feminino"); break;
        case 3: strcpy(p, "Outro"); break;
        default: system("clear"); printf("Input inválido.\n"); repeat = TRUE; break;
    }
  }
}

//cadastrar data de nascimento
Data nascimentocadastro(char * tipo){
  Data nas;
  nas.ano = ERRO;
  system("clear");
  while(1){
    printf("Digite o dia de nascimento %s: \n", tipo);
    scanf("%d", &nas.dia);
    printf("Digite o mês de nascimento %s: \n", tipo);
    scanf("%d", &nas.mes);
    printf("Digite o ano de nascimento %s: \n", tipo);
    scanf("%d", &nas.ano);

    if(nas.dia > 0 && nas.dia < 32 && nas.mes > 0 && nas.mes < 13 && nas.ano > 0){
      break;
    } else{
      getchar();
      system("clear");
      printf("Data inválida.\n");
    }
  }
  return nas;
}

void nomecadastro(char * nome, char * tipo){
  int i, repete = TRUE;
  system("clear");
  while(repete){
    repete = FALSE;  
    i = 0;

    printf("Digite o nome %s:\n(sem acento): \n", tipo);
    fgets(nome, MAX_NOME, stdin);
    *strchr(nome, '\n') = '\0';

    for(i = 0; nome[i] != '\0' && nome[i] != '\n'; i++){
      if((nome[i] < ' ') || (nome[i] > ' ' && nome[i] < 'A') || (nome[i] > 'Z' && nome[i] < 'a') || (nome[i] > 'z') || (nome[i] == ' ' && nome[i+1] == ' ') || (nome[0] == ' ')){
        repete = TRUE;
        system("clear");
        printf("Nome fora dos parametros.\n");
        break;
      }
    }
  }
}

void cpfcadastro(char * cpf, char * tipo, int qtdProf, Pessoa listaProf[], int qtdAl, Pessoa listaAl[]){
  int i, j, resultado = ERRO, Jaexiste;
  system("clear");
  while(1){
    i = 0;
    j = 0;
    Jaexiste = FALSE;

    printf("Digite o CPF %s: \n", tipo);
    fgets(cpf, 13, stdin);
    *strchr(cpf, '\n') = '\0';

    for(i = 0; cpf[i] != '\n' && cpf[i] >= '0' && cpf[i] <= '9'; i++);
    if(cpf[11] != '\n' && cpf[11] != '\0' && (cpf[11] < '0' || cpf[11] > '9')) i++;


    for(j = 0; j < qtdAl; j++){
      resultado = strcmp(cpf, listaAl[j].CPF);
      if(resultado == 0){
        Jaexiste = TRUE;
        break;
      }
    }

    for(j = 0; j < qtdProf; j++){
      resultado = strcmp(cpf, listaProf[j].CPF);
      if(resultado == 0){
        Jaexiste = TRUE;
        break;
      }
    }

    system("clear");
    if(i != 11){
      printf("CPF inválido.\n");
    } else if(Jaexiste == TRUE){
      printf("Este CPF já está com outra pessoa.\n");
    } else break;
  }
}

Pessoa cadastroaluno(int fquantAlunos, int numeromat, char * tipo, int qtdProf, Pessoa listaProf[], Pessoa listaAl[]){
  Pessoa listaaluno[MAX_PESSOAS];
  getchar();  
  system("clear");     
  int i = 0;

  nomecadastro(listaaluno[fquantAlunos].nome, tipo);

  sexocadastro(listaaluno[fquantAlunos].sexo, tipo);

  listaaluno[fquantAlunos].nas = nascimentocadastro(tipo);

  getchar();
  cpfcadastro(listaaluno[fquantAlunos].CPF, tipo, qtdProf, listaProf, fquantAlunos, listaAl);

  system("clear");
  listaaluno[fquantAlunos].matricula = numeromat;
  printf("\nMatrícula: %d \n", listaaluno[fquantAlunos].matricula);

  strcpy(listaaluno[fquantAlunos].tipo_mat, "Aluno");

  return listaaluno[fquantAlunos];
}

Pessoa cadastroprof(int fquantProfs, int numeromat, char * tipo, Pessoa listaProf[], int qtdAl, Pessoa listaAl[]){
  Pessoa listaprofessor[MAX_PESSOAS];
  getchar();  
  system("clear");    
  int i = 0;

  nomecadastro(listaprofessor[fquantProfs].nome, tipo);

  sexocadastro(listaprofessor[fquantProfs].sexo, tipo);

  listaprofessor[fquantProfs].nas = nascimentocadastro(tipo);

  getchar();
  cpfcadastro(listaprofessor[fquantProfs].CPF, tipo, fquantProfs, listaProf, qtdAl, listaAl);

  system("clear");
  listaprofessor[fquantProfs].matricula = numeromat;
  printf("\nMatrícula: %d \n", listaprofessor[fquantProfs].matricula);

  strcpy(listaprofessor[fquantProfs].tipo_mat, "Professor");

  return listaprofessor[fquantProfs];
}

void BuscaChar(Pessoa listaalunos[], Pessoa listaprofessores[], int qtdAlunos, int qtdProfs) {
  int i = 0;
  int j = 0;
  int acessou = 0;
  int TAM;
  char chars[MAX_CHAR];

  system("clear");
  printf("Insira os caracteres que pretende pesquisar (Min %d; Máx %d) \n", MIN_CHAR, MAX_CHAR-2);
  printf("Coloque todos juntos uma unica vez: ");
  fgets(chars, MAX_CHAR, stdin);
  chars[strcspn(chars, "\n")] = 0;
  TAM = strlen(chars);

  for (int aux = 0; aux < TAM; aux++) {
      if (chars[aux] >= 'a' && chars[aux] <= 'z') {
          chars[aux] = chars[aux] - 32;
      }
  }

  if (TAM < MIN_CHAR) {
      printf("Não pode ser feita a pesquisa com menor de %d caracteres.\n", MIN_CHAR);
  } else {
      if (BuscaPessoaChar(listaalunos, qtdAlunos, chars, TAM) == TRUE) {
          acessou++;
      }
      if (BuscaPessoaChar(listaprofessores, qtdProfs, chars, TAM) == TRUE) {
          acessou++;
      }
      if (acessou == 0) {
          printf("Não foi possivel encontrar com essa sequencia, tente outra.\n");
      }
  }
}

int BuscaPessoaChar(Pessoa listapessoa[], int qtdPessoas, char chars[], int TAM) {
  int i = 0;
  int j = 0;
  int acessou = FALSE;
  char *achou;
  Pessoa comparativa[qtdPessoas];

  for(i=0;i<qtdPessoas;i++){
    comparativa[i] = letraMaiuscula(listapessoa[i]);
    achou = strstr(comparativa[i].nome, chars);
    if(achou != NULL){
      ImprimirCadastro(i, listapessoa);
      acessou = TRUE;
    }
  }

  return acessou;
}

int semestrecadastroDisciplina(){
  int semestre = 0;
  system("clear");
  while(1){
    printf("Digite o semestre da disciplina: ");
    scanf("%d",&semestre);
    getchar();
    if(semestre >= 1 && semestre <= 8){
      break;
    } else{
      system("clear");
      printf("Inválido.\n");
    }
  }
  return semestre;
}

int MatProfcadastroDisciplina(int fquantDis, int numeromat, int qtdProf, Pessoa listaprofessor[]){
  int mProf, posicao;
  while(1){
    system("clear");
    Listar(qtdProf, listaprofessor);
    printf("Digite a matrícula do professor(a) da disciplina: \n");
    scanf("%d",&mProf);

    posicao = funcaoBusca(qtdProf, mProf, listaprofessor);

    if(posicao < qtdProf){
      return mProf;
      break;
    } else{
      system("clear");
      getchar();
      printf("A matrícula inserida não existe.\n");
    }
  }
}
void nomecadastroDisciplina(char * nome){
  system("clear");
  getchar();

  int i, repete = TRUE;
  system("clear");
  while(repete){
    repete = FALSE;  
    i = 0;

    printf("===== Cadastro Disciplina =====\n");
    printf("Digite o nome da disciplina: \n(somente letras)\n");
    fgets(nome, MAX_NOME, stdin);
    *strchr(nome, '\n') = '\0';

    for(i = 0; nome[i] != '\0' && nome[i] != '\n'; i++){
      if(!((nome[i] >= 'A' && nome[i] <= 'Z') || (nome[i] >= 'a' && nome[i] <= 'z') || (nome[i] >= '0' && nome[i] <= '9') || (nome[i] == ' ' && nome[i+1] != ' ' && nome[0] != ' '))){
        repete = TRUE;
        system("clear");
        printf("Nome inválido.\n");
        break;
      }
    }
  }
}

Disciplinas cadastroDiscplina(int fquantDis, int numeromat, int qtdProf, Pessoa listaprofessor[]){
  Disciplinas listadisciplina[MAX_DIS];
  int posicao;

  nomecadastroDisciplina(listadisciplina[fquantDis].nome);

  listadisciplina[fquantDis].semestre = semestrecadastroDisciplina();

  listadisciplina[fquantDis].matProf = MatProfcadastroDisciplina( fquantDis,  numeromat,  qtdProf, listaprofessor);

  listadisciplina[fquantDis].codigo = numeromat;

  listadisciplina[fquantDis].AlDis.qtdTurma = 0;

  posicao = funcaoBusca(qtdProf, listadisciplina[fquantDis].matProf, listaprofessor);

  getchar();
  system("clear");
  ImprimirDisciplina(qtdProf, fquantDis, listadisciplina, listaprofessor);

  return listadisciplina[fquantDis];
}

//excluir cadastros
int excluirCadastro(int qtdcadastros, Pessoa lista[], char * tipo){
  int mat, confirm;
  Pessoa aux;
  int repete = TRUE;
  int i;

  int resultado = Temcadastros(qtdcadastros);
  if(resultado == FALSE) return FALSE;

  Listar(qtdcadastros, lista);
  printf("Digite a matrícula %s que deseja excluir:\n", tipo);
  scanf("%d",&mat);
  system("clear");
  getchar();

  i = funcaoBusca(qtdcadastros,mat,lista);


  if(i < qtdcadastros){
    while(repete){
      repete = FALSE;
      ImprimirCadastro(i, lista);
      printf("\nConfirma que quer deletar esse cadastro?\n");
      printf("1 - Sim\n2 - Não\n");
      scanf("%d", &confirm);
      getchar();
      switch(confirm){
        case 1: 
          for(mat=i; mat<qtdcadastros; mat++){
            aux = lista[mat+1];
            lista[mat] = aux;
          }
          printf("Deletado com sucesso.\n");
          return TRUE;
        case 2: break;
        default: system("clear"); printf("Opção Inválida.\n"); repete = TRUE; break;
      }
    }
  } else{
    printf("A matrícula inserida não existe.\n");
  }
  return FALSE;
}

//excluir disciplinas
int excluirDisciplina(int qtdcadastros, int qtdProf, Disciplinas lista[], Pessoa listaProf[]){
  int mat, confirm;
  Disciplinas aux;
  int repete = TRUE;
  int i;

  if(qtdcadastros <= 0){
    printf("Não existem cadastros para excluir.\n");
    return FALSE;
  }

  ListarDisciplinas(qtdcadastros, qtdProf, lista, listaProf);
  printf("Digite o código da disciplina que deseja excluir:\n");
  scanf("%d",&mat);
  system("clear");
  getchar();

  i = funcaoBuscaDisciplinas(qtdcadastros,mat,lista);


  if(i < qtdcadastros){
    while(repete){
      repete = FALSE;
      ImprimirDisciplina(qtdProf, i, lista, listaProf);
      printf("\nCerteza de que você quer deletar esse cadastro?\n");
      printf("1 - Sim\n2 - Não\n");
      scanf("%d", &confirm);
      getchar();
      switch(confirm){
        case 1: 
          for(mat=i; mat<qtdcadastros; mat++){
            aux = lista[mat+1];
            lista[mat] = aux;
          }
          printf("Operação realizada com sucesso.\n");
          return TRUE;
        case 2: break;
        default: system("clear"); printf("Opção Inválida.\n"); repete = TRUE; break;
      }
    }
  } else{
    printf("O código inserido não existe.\n");
  }
  return FALSE;
}


Pessoa atualizarcadastro(int qtd, Pessoa lista[],  char * tipo, int qtdsec, Pessoa listasec[]){
  system("clear");
  int mat, contato, opcao;
  int repete;

  int resultado = Temcadastros(qtd);
  if(resultado == FALSE) return lista[qtd];

  Listar(qtd, lista);
  printf("Informe a matrícula que você quer atualizar: \n");
  scanf("%d", &mat);

  contato = funcaoBusca(qtd, mat, lista);
  getchar();

  if(contato < qtd){
    while(1){
      repete = TRUE;
      while(repete){
        repete = FALSE;
        system("clear");
        ImprimirCadastro(contato, lista);
        printf("\nInforme o que quer editar:\n1 - Nome\n2 - gênero\n3 - Data de nascimento\n4 - CPF\n\n0 - Voltar\n\nEntrada: ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao){
          case 1: nomecadastro(lista[contato].nome, tipo); break;
          case 2: sexocadastro(lista[contato].sexo, tipo); break;
          case 3: lista[contato].nas = nascimentocadastro(tipo); break;
          case 4: cpfcadastro(lista[contato].CPF, tipo, qtd, lista, qtdsec, listasec); break;
          case 0: return lista[qtd]; 
          default: printf("Opção Inválida.\n"); repete = TRUE; break;
        }
        system("clear");
        ImprimirCadastro(contato, lista);
        printf("\nFeita com sucesso!\n");
      }

      printf("Editar novamente?\n1 para Sim\nQualquer valor para Não\n");
      scanf("%d", &opcao);
      getchar();
      if(opcao != 1) break;
    }
  } else{
    system("clear");
    printf("Matricula inválida.\n");
  }

  return lista[qtd]; 
}

Disciplinas atualizarDisciplina(int qtdDis, Disciplinas lista[],  Pessoa listaProf[], int qtdProf){
  system("clear");
  int cod, contatoDis, contatoProf, opcao;
  int repete;

  if(qtdDis <= 0){
    printf("Não existem contatos para atualizar.\n");
    return lista[qtdDis];
  }

  ListarDisciplinas(qtdDis, qtdProf, lista, listaProf);
  printf("Informe a numeração da matéria que você quer atualizar\n");
  scanf("%d", &cod);
  contatoDis = funcaoBuscaDisciplinas(qtdDis, cod, lista);
  getchar();

  if(contatoDis < qtdDis){
    contatoProf = funcaoBusca(qtdProf, lista[contatoDis].matProf, listaProf);
    while(1){
      repete = TRUE;
      while(repete){
        repete = FALSE;
        system("clear");
        ImprimirDisciplina(qtdProf, contatoDis, lista, listaProf);
        printf("\nInforme o que quer atualizar:\n1 - Nome\n2 - Semestre\n3 - Professor\n\n0 - Voltar\n\nEntrada: ");
        scanf("%d", &opcao);
        switch(opcao){
          case 1: nomecadastroDisciplina(lista[contatoDis].nome); break;
          case 2: getchar(); lista[contatoDis].semestre = semestrecadastroDisciplina(); break;
          case 3:  
            if(qtdProf > 0){
              lista[contatoDis].matProf = MatProfcadastroDisciplina( qtdDis,  cod,  qtdProf, listaProf); 
            } else{
              getchar();
              system("clear");
              printf("Não foi possivel pois não existem professores.\n");
              repete = TRUE;
              continuar();
            }
            break;
          case 0: return lista[qtdDis]; 
          default: printf("Opção Inválida.\n"); repete = TRUE; break;
        }
        system("clear");
        ImprimirDisciplina(qtdProf, contatoDis, lista, listaProf);
        printf("\nFeito com sucesso!\n");
      }

      printf("Atualizar novamente?\n1 para Sim\nQualquer valor para Não\n");
      scanf("%d", &opcao);
      getchar();
      if(opcao != 1) break;
    }
  } else{
    system("clear");
    printf("Não existe essa numeração.\n");
  }

  return lista[qtdDis]; 
}

void ImprimirCadastro(int i, Pessoa lista[]){
  printf("========== %s ==========\n", lista[i].tipo_mat);
  printf("Matrícula: %d\n", lista[i].matricula);
  printf("Nome: %s\n", lista[i].nome);
  printf("Sexo: %s\n", lista[i].sexo);
  printf("Data de Nascimento: %02d/%02d/%04d\n", lista[i].nas.dia,lista[i].nas.mes,lista[i].nas.ano);
  printf("CPF: %s\n",lista[i].CPF);
  printf("==================================\n");
}

void ImprimirDisciplina(int qtdProfs, int i, Disciplinas lista[], Pessoa Profs[]){
  int posicaoprof;
  posicaoprof = funcaoBusca(qtdProfs, lista[i].matProf, Profs);
  printf("============ Disciplina ===========\n");
  printf("Código: %d\n", lista[i].codigo);
  printf("Nome: %s\n", lista[i].nome);
  printf("Semestre: %d\n", lista[i].semestre);
  if(posicaoprof < qtdProfs){
    printf("Professor:\n Matrícula - %d\n Nome      - %s\n", lista[i].matProf, Profs[posicaoprof].nome);
  } else{
    printf("Professor:\n(O professor desta matéria foi excluído.\nPor favor atualize a matéria.)\n");
  }
  printf("==================================\n");
}

void Listar(int qtdpessoas, Pessoa lista[]){
  system("clear");
  getchar();

  int cont;
  if(qtdpessoas <= 0){
    printf("Não existem cadastros.\n");
  } else {
    for(cont=0; cont<qtdpessoas; cont++){
      ImprimirCadastro(cont, lista);
    }
  }
}

void ListarDisciplinas(int qtdDis, int qtdProfs, Disciplinas lista[], Pessoa listaProf[]){
  system("clear");
  getchar();
  int cont, contatoProf;

  if(qtdDis <= 0){
    printf("Não existem cadastros.\n");
  } else{
    for(cont=0; cont<qtdDis; cont++){
      contatoProf = funcaoBusca(qtdProfs, lista[cont].matProf, listaProf);
      ImprimirDisciplina(qtdProfs, cont, lista, listaProf);
    }
  }
}

void ListarDisciplinaPorVagas(Disciplinas listaDisciplina[], Pessoa listaProfs[], int qtdProfs, int qtdDisc){
  int acessado = FALSE;
  system("clear");
  getchar();
  for(int i=0;i<qtdDisc;i++){
    if(listaDisciplina[i].AlDis.qtdTurma > VAGAS){
      ImprimirDisciplina(qtdProfs, i, listaDisciplina, listaProfs);
      printf("\nMatrículas: %d\n\n", listaDisciplina[i].AlDis.qtdTurma);
      acessado = TRUE;
    }
  }
  if(acessado == FALSE){
    printf("Não foi encontrada disciplinas assim\n");
  }
}

int menu_secundario(int tipo){
  system("clear");
  int opcao2 = ERRO;
  char menu[25];
  menu[0] = '\0';
  if(tipo == 1){
    strcpy(menu, "     Menu do Aluno     ");
  } else if(tipo == 2){
    strcpy(menu, "   Menu do Professor(a)   ");
  } else if(tipo == 3){
    strcpy(menu, "   Menu da Disciplina   ");
  }
  printf("==================================\n");
  printf("%s", menu);
  printf("==================================\n");
  printf("\nSelecione uma opção.\n");
  printf("\n1 - Cadastrar");
  printf("\n2 - Excluir");
  printf("\n3 - Atualizar");
  printf("\n4 - Listar cadastros");
  if(tipo == 3){
    printf("\n5 - Matricular alunos em disciplina");
    printf("\n6 - Excluir alunos de disciplina");
  }
  printf("\n\n0 - Voltar");
  printf("\n\nEntrada: ");
  scanf("%d", &opcao2);

  return opcao2;
}

int menu_principal(){
  int opcao1 = ERRO; 
  system("clear");
  printf("==================================\n");
  printf("         Escola         ");
  printf("==================================\n");
  printf("\nSelecione uma opção.\n");
  printf("1 - Aluno\n");
  printf("2 - Professor\n");
  printf("3 - Disciplina\n");
  printf("4 - Buscar pessoas\n");
  printf("5 - Aniversariantes do mês\n");
  printf("\n0 - Sair\n");
  printf("\nEntrada: ");
  scanf("%d", &opcao1);

  return opcao1;
}

void continuar(){
  char confirm;
  printf("\nPressione qualquer tecla.\n");
  scanf("%c", &confirm);
}

int Temcadastros(int qtd){
  if(qtd <= 0){
    getchar();
    printf("Não existem cadastros nessa categoria.\n");
    return FALSE;
  } else{
    return TRUE;
  }
}

int main(){
  setlocale(LC_ALL,"Portuguese");
  int resultado, repete, repetelista;
  int opcao1 = 1, opcao2 = 1, opcao3=1;
  int quantAlunos=0, quantProfs=0,quantDis=0;
  int proxmat[3];
  char tipo[15];
  tipo[0] = '\0';
  Pessoa listaaluno[MAX_PESSOAS], listaprofessor[MAX_PESSOAS];
  Disciplinas listadisciplinas[MAX_DIS];

  while(1){
    repete = TRUE;
    opcao1 = menu_principal();
    getchar();

    while(repete == TRUE){
      switch(opcao1){
        case 1: 
              strcpy(tipo, "do aluno");
              opcao2 = menu_secundario(opcao1);
              system("clear");
              switch(opcao2){
                case 1:
                  if(quantAlunos == MAX_PESSOAS){
                    printf("O número máximo de pessoas nessa categoria já foi alcançado.");
                    getchar();
                  }else {
                    listaaluno[quantAlunos] = cadastroaluno(quantAlunos, proxmat[ALUNO], tipo, quantProfs, listaprofessor, listaaluno);
                    proxmat[ALUNO]++;
                    quantAlunos++;
                    printf("\nCadastro feito com sucesso!");
                  }
                  continuar();
                  break;
                case 2:
                  resultado = excluirCadastro(quantAlunos, listaaluno, tipo);
                  if(resultado == 1){
                    quantAlunos--;
                  }
                  continuar();
                  break;
                case 3:
                  listaaluno[quantAlunos] = atualizarcadastro(quantAlunos, listaaluno, tipo, quantProfs, listaprofessor);
                  continuar();
                  break;
                case 4:
                  resultado = Temcadastros(quantAlunos);

                  repetelista = TRUE;
                  while(repetelista && resultado){
                    Listar(quantAlunos,listaaluno);
                    opcao3= menuListas(opcao1);
                    switch(opcao3){
                      case 1: 
                        listaCrescente(quantAlunos,listaaluno);
                        continuar(); 
                        break;
                      case 2:
                        listaDecrescente(quantAlunos,listaaluno);
                        continuar();
                        break;
                      case 3:
                        listaPorData(quantAlunos,listaaluno);
                        continuar();
                        break;
                      case 4:
                        listaSexo(quantAlunos,listaaluno);
                        continuar();
                        break;
                      case 5:
                        AlunosComPoucasDisciplinas(listaaluno, listadisciplinas, quantAlunos, quantDis);
                        continuar();    
                        break;
                      case 0: repetelista = FALSE; break;
                      case ERRO: getchar();
                      default: printf("Opção Inválida."); getchar(); continuar(); break;
                    }
                  }
                  continuar();
                  break;
                case 0: repete = FALSE; break;   
                case ERRO: getchar();
                default: printf("Opção Inválida."); getchar(); continuar(); break;
              }
              break;
          case 2:
              strcpy(tipo, "do professor");
              opcao2 = menu_secundario(opcao1);
              system("clear");
              switch(opcao2){
                case 1:
                  if(quantProfs == MAX_PESSOAS){
                    printf("Já está cheia.");
                    getchar();
                  }else {
                    listaprofessor[quantProfs] = cadastroprof(quantProfs, proxmat[PROF], tipo, listaprofessor, quantAlunos, listaaluno);
                    proxmat[PROF]++;
                    quantProfs++;
                    printf("\nEfetuado com sucesso!");
                  }
                  continuar();
                  break;
                case 2:
                  resultado = excluirCadastro(quantProfs, listaprofessor, tipo);
                  if(resultado == 1){
                    quantProfs--;
                  }
                  continuar();
                  break;
                case 3:
                  listaprofessor[quantProfs] = atualizarcadastro(quantProfs, listaprofessor, tipo, quantAlunos, listaaluno);
                  continuar();
                  break;
                case 4:
                  resultado = Temcadastros(quantProfs);
                  repetelista = TRUE;

                  while(repetelista && resultado){
                    Listar(quantProfs,listaprofessor);
                    opcao3= menuListas(opcao1);
                    switch(opcao3){
                      case 1: 
                        listaCrescente(quantProfs,listaprofessor);
                        continuar(); 
                        break;
                      case 2:
                        listaDecrescente(quantProfs,listaprofessor);
                        continuar();
                        break;
                      case 3:
                        listaPorData(quantProfs,listaprofessor);
                        continuar();
                        break;
                      case 4:
                        listaSexo(quantProfs,listaprofessor);
                        continuar();
                        break;
                      case 0: repetelista = FALSE; break;
                      case ERRO: getchar();
                      default: printf("Opção Inválida."); getchar(); continuar(); break;
                    }
                  }
                  continuar();
                  break;
                case 0: repete = FALSE; break;
                case ERRO: getchar();
                default: printf("Opção Inválida."); getchar(); continuar(); break;
              }
              break;
        case 3:
              strcpy(tipo, "da disciplina");
              opcao2 = menu_secundario(opcao1);
              system("clear");
              switch(opcao2){
                case 1: 
                  if(quantDis == MAX_DIS){
                    printf("Não tem espaços para mais disciplinas.");
                    getchar();
                  }else{
                    if(quantProfs > 0){
                      listadisciplinas[quantDis] = cadastroDiscplina(quantDis, proxmat[DIS], quantProfs, listaprofessor);
                      quantDis++;
                      proxmat[DIS]++;
                      printf("\nEfetuado com sucesso!");
                    } else{
                      getchar();
                      printf("Não existem professores para o cadastro de disciplinas.\n");
                    }
                  }
                  continuar();
                  break;
                case 2:
                  resultado = excluirDisciplina(quantDis, quantProfs, listadisciplinas, listaprofessor);
                  if(resultado == 1){
                    quantDis--;
                  }
                  continuar();
                  break;
                case 3:
                  listadisciplinas[quantDis] = atualizarDisciplina(quantDis, listadisciplinas, listaprofessor, quantProfs);
                  continuar();
                  break;
                case 4:
                  resultado = Temcadastros(quantDis);
                  repetelista = TRUE;

                  while(repetelista && resultado){
                    opcao3 = MenuListasDisciplinas();
                    switch(opcao3){
                      case 1: 
                        ListarDisciplinas(quantDis, quantProfs, listadisciplinas, listaprofessor);
                        continuar();
                        break;
                      case 2: 
                        ListarAlunosdaDisciplina(quantDis, listadisciplinas, quantProfs, listaprofessor, quantAlunos, listaaluno); 
                        continuar();
                        break;
                      case 3:
                        ListarDisciplinaPorVagas(listadisciplinas, listaprofessor, quantProfs, quantDis);
                        continuar();
                      break;
                      case 0: repetelista = FALSE; break;
                      case ERRO: getchar();
                      default: printf("Opção Inválida."); getchar(); continuar(); break;
                    }
                  }
                  continuar();
                  break;
                case 5:
                  listadisciplinas[quantDis] = MatAlunoEmDis(quantDis, listadisciplinas, quantProfs, listaprofessor, quantAlunos, listaaluno);
                  continuar();
                  break;
                case 6:
                  listadisciplinas[quantDis] = DelAlunoDeDis(quantDis, listadisciplinas, quantProfs, listaprofessor, quantAlunos, listaaluno);
                  continuar();
                  break;
                case 0: repete = FALSE; break; 
                case ERRO: getchar();
                default: printf("Opção Inválida."); getchar(); continuar(); break;
              }
              break;
        case 4:
          BuscaChar(listaaluno, listaprofessor, quantAlunos, quantProfs);
          continuar();
          repete = FALSE;
        break;
        case 5:
          if(quantProfs <= 0 && quantAlunos <= 0){
            system("clear");
            printf("Não existem cadastros.\n");
          } else{
            BuscarAniversario(quantAlunos, quantProfs,listaaluno, listaprofessor);
            getchar();
          }
          repete=FALSE;
          continuar();
          break;
        case 0:
          printf("Operação finalizada.\n");
          return FALSE;
          break;
        default:
          repete = FALSE;
          printf("Entrada inválida.");
          printf(" Digite novamente.");
          break;
      }
    }
  }
}

int MenuListasDisciplinas(){
  int opcao = ERRO;
  system("clear");
  printf("===== Listas =====\n");
  printf("1 - Listar Disciplinas\n");
  printf("2 - Listar alunos de uma disciplina\n");
  printf("3 - Listar disciplinas com mais de %d vagas\n", VAGAS);
  printf("\n0 - Voltar\n");
  printf("Entrada => ");
  scanf("%d",&opcao);

  return opcao;
}

int menuListas(int opcao1){
  int opcao = ERRO;
  printf("===== Ordenação =====\n");
  printf("1 - Ordem alfabetica crescente\n");
  printf("2 - Ordem alfabetica decrescente\n");
  printf("3 - Data de nascimento em ordem crescente\n");
  printf("4 - Filtro por Sexo\n");
  if(opcao1 == 1){
    printf("5 - Alunos com menos de %d disciplinas\n", POUCASDIS);
  }
  printf("\n0 - Voltar\n");
  printf("Entrada => ");
  scanf("%d",&opcao);

  return opcao;
}

void listaCrescente(int qtd, Pessoa pessoa[]){
  char nome[qtd][MAX_NOME], help[MAX_NOME];
  int i,j,r;
  Pessoa aux[qtd],maiuscula[qtd];
  for(i=0;i<qtd;i++){
    maiuscula[i]=letraMaiuscula(pessoa[i]);
    strcpy(nome[i], maiuscula[i].nome);
  }

  for(i=0;i<qtd;i++){
    for(j=i+1;j<qtd;j++){
      r = strcmp(nome[i],nome[j]);
      if(r>0){
        strcpy(help,nome[j]);
        strcpy(nome[j],nome[i]);
        strcpy(nome[i],help);
        aux[i] = pessoa[j];
        pessoa[j]=pessoa[i];
        pessoa[i]=aux[i];
      }
    }
  }
  Listar(qtd,pessoa);
  listaMatricula(qtd, pessoa);
}

void listaDecrescente(int qtd, Pessoa pessoa[]){
  char nome[qtd][MAX_NOME], help[MAX_NOME];
  int i,j,r;
  Pessoa aux[qtd],maiuscula[qtd];

  for(i=0;i<qtd;i++){
    maiuscula[i]=letraMaiuscula(pessoa[i]);
    strcpy(nome[i], maiuscula[i].nome);
  }

  for(i=0;i<qtd;i++){
    for(j=i+1;j<qtd;j++){
      r = strcmp(nome[i],nome[j]);
      if(r<0){
        strcpy(help,nome[j]);
        strcpy(nome[j],nome[i]);
        strcpy(nome[i],help);
        aux[i] = pessoa[j];
        pessoa[j]=pessoa[i];
        pessoa[i]=aux[i];
      }
    }
  }
  Listar(qtd,pessoa);
  listaMatricula(qtd, pessoa);
}
void listaPorData(int qtd, Pessoa pessoa[]){
  int i,j,min;
  Pessoa aux;
  for(i=0;i < (qtd-1);i++){
      min=i;
      for(j=i+1;j<qtd;j++){
        if(pessoa[j].nas.ano > pessoa[min].nas.ano){
          min=j;
      }
    }
    if(i!=min){
    aux=pessoa[i];
    pessoa[i]=pessoa[min];
    pessoa[min]=aux;
    }
  }
  for(i=0;i < (qtd-1);i++){
      min=i;
      for(j=i+1;j<qtd;j++){
        if((pessoa[j].nas.mes > pessoa[min].nas.mes)&&(pessoa[j].nas.ano == pessoa[min].nas.ano)){
          min=j;
      }
    }
    if(i!=min){
    aux=pessoa[i];
    pessoa[i]=pessoa[min];
    pessoa[min]=aux;
    }
  }
  for(i=0;i < (qtd-1);i++){
      min=i;
      for(j=i+1;j<qtd;j++){
        if((pessoa[j].nas.dia > pessoa[min].nas.dia)&&(pessoa[j].nas.ano == pessoa[min].nas.ano)&&(pessoa[j].nas.mes == pessoa[min].nas.mes)){
          min=j;
      }
    }
    if(i!=min){
    aux=pessoa[i];
    pessoa[i]=pessoa[min];
    pessoa[min]=aux;
    }
  }
  Listar(qtd,pessoa);
  listaMatricula(qtd,pessoa);
}
void listaMatricula(int qtd, Pessoa pessoa[]){
  int i,min,j;
  Pessoa aux;

  for(i=0; i<qtd-1; i++){
    min=i;
    for(j=i+1; j<qtd; j++){
      if(pessoa[j].matricula<pessoa[min].matricula){
        min=j;
      }
    }
    if(i!=min){
      aux=pessoa[i];
      pessoa[i]=pessoa[min];
      pessoa[min]=aux;
    }
  }
} 
void listaSexo(int qtd,Pessoa pessoa[]){
  int i,j=0, repeat=TRUE,filtro;
  char p;
  Pessoa aux[MAX_PESSOAS];
  while(repeat == TRUE){
    repeat = FALSE;
    printf("===== Filtro de Sexo =====\n");
    printf("Escolha uma opção: \n");
    printf("1 - Masculino\n");
    printf("2 - Feminino\n");
    printf("3 - Outro\n");
    printf("Entrada => ");
    scanf("%d",&filtro);

    switch(filtro){
        case 1: p='M'; break;
        case 2: p='F'; break;
        case 3: p='O'; break;
        default: system("clear");  getchar(); printf("Input inválido.\n"); repeat = 1; break;
    }
  }

  for(i=0; i<qtd; i++){
    if(pessoa[i].sexo[0] == p){
      aux[j]=pessoa[i];
      j++;
    }
  }
  Listar(j,aux);
}

int funcaoBusca( int qtd, int pessoa, Pessoa individuo[]){
  int i=0, encontrado, posicao= qtd +1;
  encontrado = FALSE;
  while(i<qtd && !encontrado){
    if(individuo[i].matricula == pessoa){
      encontrado = TRUE;
      posicao = i;
    }else{
      i++;
    }
  }
  return posicao;
}

int funcaoBuscaDisciplinas( int qtd, int disciplina, Disciplinas materias[]){
  int i=0, encontrado, posicao= qtd +1;
  encontrado = FALSE;
  while(i<qtd && !encontrado){
    if(materias[i].codigo == disciplina){
      encontrado = TRUE;
      posicao = i;
    }else{
      i++;
    }
  }
  return posicao;
}

int funcaoBuscaTurma(int qtd, int procurado, int lista[]){
  int i=0, encontrado, posicao= qtd +1;
  encontrado = FALSE;
  while(i<qtd && !encontrado){
    if(lista[i] == procurado){
      encontrado = TRUE;
      posicao = i;
    }else{
      i++;
    }
  }
  return posicao;
}

Pessoa letraMaiuscula(Pessoa pessoa){
  int size;
  Pessoa maiuscula;
  char aux[MAX_NOME];
  strcpy(aux,pessoa.nome);
  maiuscula=pessoa;
  size=strlen(pessoa.nome);

  for(int i=0; i<size; i++){
    if(aux[i]>='A' && aux[i]<='Z'){
      maiuscula.nome[i]=aux[i];
    }else if(pessoa.nome[i]>='a' && pessoa.nome[i]<='z'){
      maiuscula.nome[i]=aux[i]-32;
    }else{
      maiuscula.nome[i]=aux[i];
    }
  }
  return maiuscula;
}

void BuscarAniversario(int qtdAluno, int qtdProf, Pessoa aluno[], Pessoa professor[]){
  system("clear");
  int i=0,j=0,mes = ERRO, encontradoA=0, encontradoP=0;
  printf("Informe a numeração do mês: ");
  scanf("%d",&mes);
  while(i<qtdAluno){
    if(aluno[i].nas.mes == mes){  
      ImprimirCadastro(i,aluno);
      encontradoA=1;
      i++;
    }else{
      i++;
    }
  }

  while(j<qtdProf){
    if(professor[j].nas.mes == mes){
      ImprimirCadastro(j,professor);
      encontradoP=1;
      j++;
    }else{
      j++;
    }
  }
  if(mes < 1 || mes > 12){
    system("clear");
    printf("Mês inválido\n");
  } else if(encontradoA==0 && encontradoP==0){
    system("clear");
    printf("Sem aniversariantes no mês inserido!\n");
  }
}