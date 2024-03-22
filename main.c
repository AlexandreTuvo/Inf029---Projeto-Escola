#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define AnoMinimo 1920
#define cls system("clear||cls");
#define TAM 100

// Limite de caracteres para um nome
#define qt 60
// Qt = quantidade de alunos/professores maximo
#define materias 20
// materias que podem ser cadastradas

// Menus de printf
void menucadastro(int *cad) {
  printf("Menu de cadastro\n");
  printf("1:Cadastrar Aluno\n");
  printf("2:Cadastrar Professor\n");
  printf("3:Cadastrar Disciplinas\n");
  printf("4:Atualizar/inserir/excluir\n");
  printf("5:voltar\n");
  scanf(" %d", &*cad);
}
void menulista(int *cad) {
  printf("O que deseja listar?\n");
  printf("1:Opcões de Alunos\n");
  printf("2:Opcões de Professores\n");
  printf("3:Opcões de Disciplinas\n");
  printf("4:Aniversariantes do mes\n");
  printf("5:Buscar pessoas por nome\n");
  printf("6:Voltar\n\n");
  scanf(" %d", &*cad);
}
void menualuno(int *opcao) {
  printf("Selecione a opcao desejada:\n");
  printf("1:Listar todos os alunos\n");
  printf("2:Listar alunos por sexo\n");
  printf("3:Listar alunos por nome\n");
  printf("4:Listar por data de nascimento\n");
  printf("5:Listar alunos em menos de 3 materias\n");
  printf("6:Voltar\n\n");
  scanf(" %d", &*opcao);
}
void menuprof(int *opcao) {
  printf("Selecione a opcao desejada:\n");
  printf("1:Listar todos os professores\n");
  printf("2:Listar professores por sexo\n");
  printf("3:Listar professores por nome\n");
  printf("4:Listar professores por data de nascimento\n");
  printf("5:Voltar\n\n");
  scanf(" %d", &*opcao);
}
void menudisciplina(int *opcao) {
  printf("Selecione a opcao desejada:\n");
  printf("1:Listar todas as disciplinas\n");
  printf("2:Listar uma disciplinas e os alunos inseridos\n");
  printf("3:Disciplinas que extrapolam 40 vagas\n");
  printf("4:Voltar\n\n");
  scanf(" %d", &*opcao);
}
void menuEditar(int *cad){
printf("O que deseja fazer?\n");
printf("1: Atualizar/Excluir Aluno\n");
printf("2: Atualizar/Excluir Professor\n");
printf("3: Atualizar/Excluir Disciplina\n");
printf("4: Inserir Aluno na disciplina\n");
printf("5: Excluir Aluno da disciplina\n");
printf("6: Voltar\n");
scanf(" %d", &*cad);
}
void menuEditarAluno(int *opcao){
  printf("Gerenciar Aluno\n");
  printf("O que deseja fazer?\n");
  printf("1: Atualizar\n");
  printf("2: Excluir\n");
  scanf(" %d", &*opcao);
}
void menuEditarProf(int *opcao){
  printf("Gerenciar Professor\n");
  printf("O que deseja fazer?\n");
  printf("1: Atualizar\n");
  printf("2: Excluir\n");
  scanf(" %d", &*opcao);
}
void menuEditarDis(int *opcao){
  printf("Gerenciar Disciplina\n");
  printf("O que deseja fazer?\n");
  printf("1: Atualizar\n");
  printf("2: Excluir\n");
  scanf(" %d", &*opcao);
}

// fim de menus de printf

// struct
typedef struct cadastro {
  long int matri;
  char nome[TAM];
  int sexo;
  int data[3];
  char cpf[13];
  int contadordisciplinas;
} cadastro;

typedef struct cadastro2 {
  char nome[TAM];
  int codigo;
  int semestre;
  int vagas;
  long int matriprof;
  long int matrialuno[qt];
  int contadoraluno;
} cadastro2;
// fim de struct
// funções
//  cpf gerado para ajudar a validar 747.401.452-19
int validarCPF(char *cpf) {
  int i, j;
  int digito1 = 0, digito2 = 0;
  int cpf_numerico[11];
  int Caracterespecialerrado = 0;

  // Transforma os caracteres numéricos do CPF em inteiros e verifica se há
  // caracteres especiais inválidos
  for (i = 0, j = 0; cpf[i] != '\0'; i++) {
    if (cpf[i] >= '0' && cpf[i] <= '9') {
      cpf_numerico[j++] = cpf[i] - '0';
    } else if (cpf[i] != '.' && cpf[i] != '-') {
      Caracterespecialerrado = 1;
      break;
    }
  }

  // Verifica se o CPF tem a quantidade correta de dígitos
  if (j != 11) {
    return 0; // CPF inválido
  }

  // Verifica se todos os dígitos são iguais
  for (i = 1; i < 11; i++) {
    if (cpf_numerico[i] != cpf_numerico[i - 1]) {
      break;
    }
  }
  if (i == 11) {
    return 0; // CPF com todos os dígitos iguais é inválido
  }

  // Calcula o primeiro dígito verificador
  for (i = 0; i < 9; i++) {
    digito1 += cpf_numerico[i] * (10 - i);
  }
  digito1 = (digito1 * 10) % 11;
  if (digito1 == 10) {
    digito1 = 0;
  }

  // Calcula o segundo dígito verificador
  for (i = 0; i < 10; i++) {
    digito2 += cpf_numerico[i] * (11 - i);
  }
  digito2 = (digito2 * 10) % 11;
  if (digito2 == 10) {
    digito2 = 0;
  }

  // Verifica se os dígitos calculados coincidem com os dígitos verificadores
  // originais
  if (digito1 == cpf_numerico[9] && digito2 == cpf_numerico[10] &&
      Caracterespecialerrado == 0) {
    return 1; // CPF válido
  } else {
    return 0; // CPF inválido
  }
}

void NomeCorreto(char nome[]) {
    int Maisculo = 1; // Flag para indicar se a próxima letra deve ser maiúscula

    for (int i = 0; nome[i] != '\0'; i++) {
        if (isalpha(nome[i])) { // Verifica se o caractere é uma letra
            if (Maisculo) {
                  nome[i] = toupper(nome[i]); // Converte a letra para maiúscula
                  Maisculo = 0; // Desativa a flag após converter a letra
            } else {
                  nome[i] = tolower(nome[i]); // Converte a letra para minúscula
            }
        } else {
              Maisculo = 1; // Ativa a flag se encontrar um espaço ou caractere especial
        }
    }
}

void cadastrarPessoa(cadastro reg[2][qt], int cad, int *contador,int AnoAtual) {
  cls
  int valido = 0;
  char digit;
  long int matricula;
  int matriculaexistente;
  int caracter_especial;
  cad--;
  // se o limite de alunos for atingido, ele não cadastra
  if (*contador == qt) {
    printf("Numero maximo atingido:\n");
    return;
  }

  while (valido != 1) {
    while (valido != 6) {
      matriculaexistente = 0;
      printf("Numero de matricula:\n");
      scanf(" %ld", &matricula);
      if (matricula <= 2000000000) {
        printf("Numero de matricula invalido\n");
        continue;
      } else {
        for (int k = 0; k < 2; k++) {
          for (int j = 0; j < qt; j++) {
            if (reg[k][j].matri == matricula) {
              printf("Matricula ja existente\n");
              matriculaexistente = 1;
              break;
            }
          }
          if (matriculaexistente)
            break;
        }
        if (!matriculaexistente) {
          reg[cad][*contador].matri = matricula;
          valido = 6;
        }
      }
    }
    while(valido != 7){
    printf("Nome completo:\n");
    scanf(" %[^\n]s", &reg[cad][*contador].nome[0]);
    NomeCorreto(reg[cad][*contador].nome);

      caracter_especial = 0;
      
    for (int i = 0; reg[cad][*contador].nome[i] != '\0'; i++)
      if (!isalpha(reg[cad][*contador].nome[i]) && reg[cad][*contador].nome[i] != ' '){
        caracter_especial = 1;
        break;
      }
        if(!caracter_especial){
          valido = 7;
        }else{
          printf("Caracter especial não é valido\n");
          continue;
        }
  }

    printf("Sexo:\n1:Masculino\n2:Feminino\n3:Outro\n");
    scanf("%d", &reg[cad][*contador].sexo);

    while (valido != 2){
      printf("Data de nascimento:\n");
      printf("Dia:\t");
      scanf("%d", &reg[cad][*contador].data[0]);
      printf("Mes:\t");
      scanf("%d", &reg[cad][*contador].data[1]);
      printf("Ano:\t");
      scanf("%d", &reg[cad][*contador].data[2]);

      // Verificar ano
        //Se for alterar o if variavel >= *Ano minimo* && variavel < (AnoAtual - *idademinima*)) podemos colocar a amostragem de anos que serão admitidos na instituição
      if (reg[cad][*contador].data[2] >= AnoMinimo &&
          reg[cad][*contador].data[2] < (AnoAtual - 4)) {
        // Verificar mes
        if (reg[cad][*contador].data[1] >= 1 &&
            reg[cad][*contador].data[1] <= 12) {
          // verificar dia
          if ((reg[cad][*contador].data[0] >= 1 &&
               reg[cad][*contador].data[0] <= 31) &&
              (reg[cad][*contador].data[1] == 1 ||
               reg[cad][*contador].data[1] == 3 ||
               reg[cad][*contador].data[1] == 5 ||
               reg[cad][*contador].data[1] == 7 ||
               reg[cad][*contador].data[1] == 8 ||
               reg[cad][*contador].data[1] == 10 ||
               reg[cad][*contador].data[1] == 12)) {
            printf("Data Valida.\n");
            valido = 2;
          } else if ((reg[cad][*contador].data[0] >= 1 &&
                      reg[cad][*contador].data[0] <= 30) &&
                     (reg[cad][*contador].data[1] == 4 ||
                      reg[cad][*contador].data[1] == 6 ||
                      reg[cad][*contador].data[1] == 9 ||
                      reg[cad][*contador].data[1] == 11)) {
            printf("Data Valida.\n");
            valido = 2;
          } else if ((reg[cad][*contador].data[0] >= 1 &&
                      reg[cad][*contador].data[0] <= 28) &&
                     (reg[cad][*contador].data[1] == 2)) {
            printf("Data Valida.\n");
            valido = 2;
          } else if (reg[cad][*contador].data[0] == 29 &&
                     reg[cad][*contador].data[1] == 2 &&
                     (reg[cad][*contador].data[2] % 400 == 0 ||
                      (reg[cad][*contador].data[2] % 4 == 0 &&
                       reg[cad][*contador].data[2] % 100 != 0))) {
            printf("Data Valida.\n");
            valido = 2;
          } else {
            printf("Data Não Valida.\n");
            continue;
          }
        } else {
          printf("Mes Não Valido.\n");
          continue;
        }
      } else {
        printf("Ano Não Valido.\n");
        continue;
      }
    }  
  

    while (valido != 3) {
      printf("CPF:\n");
      scanf(" %[^\n]s", reg[cad][*contador].cpf);

      if (validarCPF(reg[cad][*contador].cpf)) {
        printf("Cadastro validado!\n");
        valido = 3;
        (*contador)++;
      } else {
        printf("CPF invalido!\n");
      }
    }
    valido = 1;
    printf("Digite alguma coisa para continuar:\n");
    scanf(" %c", &digit);
    cls
  }
}

void cadastrarDisciplina(cadastro2 dis[], int *contadordisciplinas,cadastro reg[2][qt], int contadorprofessor) {
  int valido = 0;
  int codigo = 0;
  char digit;

  cls 
    while (valido != 1) {
    if (*contadordisciplinas == materias) {
      printf("Numero maximo de disciplinas atingido!!");
    } else {
      printf("Nome da disciplina:\n");
      scanf(" %[^\n]s", &dis[*contadordisciplinas].nome[0]);
      NomeCorreto(dis[*contadordisciplinas].nome);
      while (valido != 2) {
        printf("Codigo da disciplina:\n");
        scanf(" %d", &codigo);
        int codigo_duplicado = 0;
        for (int j = 0; j < *contadordisciplinas; j++) {
          if (dis[j].codigo == codigo) {
            codigo_duplicado = 1;
            printf("Esse codigo já está sendo utilizado\n");
            break;
          }
        }

        if (!codigo_duplicado) {
          dis[*contadordisciplinas].codigo = codigo;
          valido = 2;
        }
      }

      printf("Digite o semestre(numero)\n");
      scanf(" %d", &dis[*contadordisciplinas].semestre);

      printf("Digite quantas vagas essa disciplina possui(Lembrando que o limite de alunos a serem cadastrados atualmente é %d):\n", qt);
      scanf(" %d", &dis[*contadordisciplinas].vagas);
      
      printf("Digite o codigo de matricula do professor:\n");
      scanf(" %ld", &dis[*contadordisciplinas].matriprof);
      int professor_encontrado = 0;
      for (int i = 0; i < qt; i++) {
        if (reg[1][i].matri == dis[*contadordisciplinas].matriprof) {
          professor_encontrado = 1;
          break;
        }
      }
      if (!professor_encontrado) {
        printf("Professor não encontrado!\n");
        printf("Cadastre-o e tente novamente!\n");
        printf("Digite alguma coisa para continuar:\n");
        scanf(" %c", &digit);
        cls
        return;
      }
      printf("Obrigado por cadastrar a disciplina\n");
      valido = 1;
      (*contadordisciplinas)++;
    }
    printf("Digite alguma coisa para continuar:\n");
    scanf(" %c", &digit);
    cls
  }
}

void atualizarPessoaPorMatricula(int cad, cadastro reg[2][qt], int *contador,int AnoAtual){
  cls
  cad--;
  char digit;
  int posicao = -1;
  int valido = -1;
  long int matricula;
  printf("Digite a matricula:\n");
  scanf(" %ld", &matricula);
  // Verifica a matrícula do aluno ou professor
  for (int i = 0; i < qt; i++) {
    if (reg[cad][i].matri == matricula) {
      posicao = i;
      break; // Se a matrícula for encontrada, sai do loop
    }
  }

  if (posicao != -1) {
    // Exibe os dados atuais da disciplina
    printf("Dados atuais do aluno/professor:\n");
    printf("Nome: %s\n", reg[cad][posicao].nome);
    printf("Sexo: ");
    if (reg[cad][posicao].sexo == 1)
      printf("Masculino\n");
    else if (reg[cad][posicao].sexo == 2)
      printf("Feminino\n");
    else if (reg[cad][posicao].sexo == 3)
      printf("Outro\n");
    printf("Data: %02d/%02d/%02d\n", reg[cad][posicao].data[0], reg[cad][posicao].data[1], reg[cad][posicao].data[2]);
    printf("Cpf: %s\n", reg[cad][posicao].cpf);
    
    // Pergunta ao usuário o que ele deseja atualizar
    int opcao;
    while(valido != 1){
    printf("O que deseja alterar?\n");
    printf("1: Nome\n");
    printf("2: Sexo\n");
    printf("3: Data de Nascimento\n");
    printf("4: CPF\n");
    printf("5: Voltar\n");
    scanf(" %d", &opcao);
    
    // Realiza a atualização com base na opção selecionada
    switch (opcao) {
    case 1:
      printf("Digite o novo nome:\n");
      scanf(" %[^\n]s", &reg[cad][posicao].nome[0]);
      NomeCorreto(reg[cad][posicao].nome);
      break;
    case 2:
      printf("Digite o novo sexo (1-Masculino, 2-Feminino, 3-Outro):\n");
      scanf(" %d", &reg[cad][posicao].sexo);
      break;
    case 3:
      while (valido != 2) {
        printf("Data de nascimento:\n");
        printf("Dia:\t");
        scanf("%d", &reg[cad][*contador].data[0]);
        printf("Mes:\t");
        scanf("%d", &reg[cad][*contador].data[1]);
        printf("Ano:\t");
        scanf("%d", &reg[cad][*contador].data[2]);

        // Verificar ano
        if (reg[cad][*contador].data[2] >= AnoMinimo && reg[cad][*contador].data[2] < (AnoAtual - 4)) {
          // Verificar mes
          if (reg[cad][*contador].data[1] >= 1 && reg[cad][*contador].data[1] <= 12) {
            // verificar dia
            if ((reg[cad][*contador].data[0] >= 1 && reg[cad][*contador].data[0] <= 31) && (reg[cad][*contador].data[1] == 1 || reg[cad][*contador].data[1] == 3 || reg[cad][*contador].data[1] == 5 || reg[cad][*contador].data[1] == 7 || reg[cad][*contador].data[1] == 8 || reg[cad][*contador].data[1] == 10 || reg[cad][*contador].data[1] == 12)) {
              printf("Data Valida.\n");
              valido = 2;
            } else if ((reg[cad][*contador].data[0] >= 1 && reg[cad][*contador].data[0] <= 30) && (reg[cad][*contador].data[1] == 4 || reg[cad][*contador].data[1] == 6 || reg[cad][*contador].data[1] == 9 || reg[cad][*contador].data[1] == 11)) {
              printf("Data Valida.\n");
              valido = 2;
            } else if ((reg[cad][*contador].data[0] >= 1 &&
                        reg[cad][*contador].data[0] <= 28) &&
                       (reg[cad][*contador].data[1] == 2)) {
              printf("Data Valida.\n");
              valido = 2;
            } else if (reg[cad][*contador].data[0] == 29 &&
                       reg[cad][*contador].data[1] == 2 &&
                       (reg[cad][*contador].data[2] % 400 == 0 ||
                        (reg[cad][*contador].data[2] % 4 == 0 &&
                         reg[cad][*contador].data[2] % 100 != 0))) {
              printf("Data Valida.\n");
              valido = 2;
            } else {
              printf("Data Não Valida.\n");
              continue;
            }
          } else {
            printf("Mes Não Valido.\n");
            continue;
          }
        } else {
          printf("Ano Não Valido.\n");
          continue;
        }
      }
      break;
    case 4:
      while (valido != 3){
        printf("Digite o novo CPF:\n");
        scanf(" %[^\n]s", reg[cad][posicao].cpf);
      if (validarCPF(reg[cad][*contador].cpf)) {
        printf("Cadastro validado!\n");
        valido = 3;
        (*contador)++;
      } else {
        printf("CPF invalido!\n");
      }
      break;
      }
    case 5: valido = 1;
      break;
    default: cls
      printf("Opcao invalida!\n");
      break;
     }
    }
   
  } else {
    printf("Aluno/Professor com matricula %ld nao encontrado.\n", matricula);
  }
  printf("Digite alguma coisa para continuar:\n");
  scanf(" %c", &digit);
  cls
}

void excluirPessoaPorMatricula(int cad, cadastro reg[2][qt], int *contador,long int matricula, int *contadordisciplinas,cadastro2 dis[]) {
  cls
  char digit;
  cad--;
  int posicao = -1;
  printf("Digite a matricula:\n");
  scanf(" %ld", &matricula);
  // Verifica a matrícula
  for (int i = 0; i < qt; i++) {
    if (reg[cad][i].matri == matricula) {
      posicao = i;
      break; // Se a matrícula for encontrada, sai do loop
    }
  }

  if (posicao != -1) {
    printf("Encontrado e excluido:\n");
    printf("Nome: %s\n", reg[cad][posicao].nome);
    printf("Matricula: %ld\n", reg[cad][posicao].matri);

    // Exclui o aluno movendo todos os alunos à esquerda
    for (int i = posicao; i < *contador; i++) {
      reg[cad][i] = reg[cad][i + 1];
    }
    (*contador)--; // Decrementa o contador

    // Remover o aluno das disciplinas
    for (int i = 0; i < *contadordisciplinas; i++) {
      for (int j = 0; j < dis[i].contadoraluno; j++) {
        if (dis[i].matrialuno[j] == matricula) {
          // Remover o aluno da disciplina movendo todos os alunos à esquerda
          for (int k = j; k < dis[i].contadoraluno - 1; k++) {
            dis[i].matrialuno[k] = dis[i].matrialuno[k + 1];
          }
          dis[i]
              .contadoraluno--; // Decrementa o contador de alunos da disciplina
          break; // Se o aluno for encontrado na disciplina, sai do loop interno
        }
      }
    }
  } else {
    printf("Pessoa com matricula %ld nao encontrado.\n", matricula);
  }
  printf("Digite alguma coisa para continuar:\n");
  scanf(" %c", &digit);
  cls
}

void atualizarDisciplina(cadastro2 dis[], int *contadordisciplinas, cadastro reg[2][qt]) {
  cls
  int codigo;
  int disciplina_encontrada = 0;
  char digit;
  int posicao;
  int valido = 0;
  printf("Digite o código da disciplina que deseja atualizar:\n");
  scanf(" %d", &codigo);

  // Verifica se a disciplina com o código fornecido existe
  for (int i = 0; i < *contadordisciplinas; i++) {
    if (dis[i].codigo == codigo) {
      disciplina_encontrada = 1;
      posicao = i;
    }
  }
  //Pergunta sobre o que quer modificar
         
      // Exibe os dados atuais da disciplina
      printf("Dados atuais da disciplina:\n");
      printf("Nome: %s\n", dis[posicao].nome);
      printf("Código: %d\n", dis[posicao].codigo);
      printf("Semestre: %d\n", dis[posicao].semestre);
      printf("Vagas: %d\n", dis[posicao].vagas);
      printf("Matrícula do professor: %ld\n", dis[posicao].matriprof);

      // Pergunta ao usuário o que ele deseja atualizar
      int opcao;
      printf("O que deseja alterar?\n");
      printf("1: Nome\n");
      printf("2: Código\n");
      printf("3: Semestre\n");
      printf("4: Vagas\n");
      printf("5: Matrícula do professor\n");
      scanf(" %d", &opcao);

    
      switch(opcao){
        case 1: 
            printf("Digite o novo nome da disciplina:\n");
            scanf(" %[^\n]s", dis[posicao].nome);
          break;
        case 2:
            while (valido != 2) {
              printf("Codigo da disciplina:\n");
              scanf(" %d", &codigo);
              int codigo_duplicado = 0;
              for (int j = 0; j < *contadordisciplinas; j++) {
                if (dis[j].codigo == codigo) {
                  codigo_duplicado = 1;
                  printf("Esse codigo já está sendo utilizado\n");
                  break;
                }
              }
          
              if (!codigo_duplicado) {
                dis[*contadordisciplinas].codigo = codigo;
                valido = 2;
              }
            }
          break;
        case 3:
            printf("Digite o novo semestre da disciplina:\n");
            scanf(" %d", &dis[posicao].semestre);
          break;
        case 4:
            printf("Digite a nova quantidade de vagas da disciplina:\n");
            scanf(" %d", &dis[posicao].vagas);
          break;
        case 5:
          while(valido != 3){
            printf("Digite a nova matrícula do professor:\n");
            scanf(" %ld", &dis[posicao].matriprof);
            int professor_encontrado = 0;
            for (int i = 0; i < qt; i++) {
              if (reg[1][i].matri == dis[*contadordisciplinas].matriprof){
                professor_encontrado = 1;
                valido = 3;
                break;
              }
            }
            if (!professor_encontrado)
              printf("Professor não encontrado!\n");
          }
          break;
        default: cls printf("Opcao digitada não existe");
      }
      // Solicita e atualiza os novos dados da disciplina
  
  if(disciplina_encontrada)
    printf("Disciplina atualizada com sucesso!\n");
  
  if (!disciplina_encontrada) 
    printf("Disciplina com código %d não encontrada.\n", codigo);
  
  printf("Digite alguma coisa para continuar:\n");
  scanf(" %c", &digit);
  cls
}

void excluirDisciplina(cadastro2 dis[], int *contadorDisciplinas) {
    cls
    int codigoDisciplina;
    char digit;
    printf("Digite o codigo da Disciplina:\n");
    scanf(" %d", &codigoDisciplina);
    // Verifica se a disciplina existe
    int posicaoDisciplina = -1;
    for (int i = 0; i < *contadorDisciplinas; i++) {
        if (dis[i].codigo == codigoDisciplina) {
            posicaoDisciplina = i;
            break;
        }
    }

    if (posicaoDisciplina != -1) {
        printf("Disciplina encontrada e excluída:\n");
        printf("Nome: %s\n", dis[posicaoDisciplina].nome);
        printf("Código: %d\n", dis[posicaoDisciplina].codigo);

        // Excluir a disciplina movendo todas as disciplinas à esquerda
        for (int i = posicaoDisciplina; i < *contadorDisciplinas - 1; i++) {
            dis[i] = dis[i + 1];
        }
        (*contadorDisciplinas)--; // Decrementa o contador de disciplinas
    } else {
        printf("Disciplina com código %d não encontrada.\n", codigoDisciplina);
    }
  printf("Digite alguma coisa para continuar:\n");
  scanf(" %c", &digit);
  cls
}

void adicionarAlunoDaDisciplina(cadastro reg[2][qt], cadastro2 dis[]){
  cls 
  int posicao;
  int codigo;
  int disciplina_encontrada = 0;
  char digit;
  printf("Digite o codigo da disciplina:\t");
  
  scanf(" %d", &codigo);
  
  for (int i = 0; i < materias; i++) {
    if (dis[i].codigo == codigo) {
      codigo = i;
      disciplina_encontrada = 1;
      break;
    }
  }
  if (!disciplina_encontrada) {
    printf("Codigo não encontrado\n");
  } else {
    if(dis[codigo].contadoraluno < dis[codigo].vagas){
      printf("Digite o numero de matricula do aluno\n");
      long int matricula;
      scanf(" %ld", &matricula);
  
  
      // Verifica a matrícula
      int alunoencontrado = 0;
      for (int i = 0; i < qt; i++) {
        if (reg[0][i].matri == matricula) {
          posicao = i;
          alunoencontrado = 1;
          break; // Se a matrícula for encontrada, sai do loop
        }
      }
  
      if (!alunoencontrado) {
        printf("Matricula do aluno não encontrada\n");
      }else{
        printf("Aluno encontrado e matriculado na disciplina\n");
        printf("Nome: %s\n", reg[0][posicao].nome);
        dis[codigo].matrialuno[dis[codigo].contadoraluno] = matricula;
        reg[0][posicao].contadordisciplinas++;
        dis[codigo].contadoraluno++;
      }
    } else
      printf("Número máximo de alunos alcançado para esta disciplina.\n");
  }
  printf("Digite alguma coisa para continuar:\n");
  scanf(" %c", &digit);
  cls
}

void excluirAlunoDaDisciplina(cadastro reg[2][qt], cadastro2 dis[]){
    cls
    char digit;
    long int matricula;
    int codigoDisciplina;
    int posicaoAluno = -1;
    int posicaoDis = -1;
    int posicaoNome;
    // Verifica a disciplina
    printf("Digite o codigo da disciplina:\n");
    scanf(" %d", &codigoDisciplina);
    for (int i = 0; i < qt; i++) {
        if (dis[i].codigo == codigoDisciplina) {
            posicaoDis = i;
            break;
        }
    }

    printf("Digite a matricula do aluno:\n");
    scanf(" %ld", &matricula);
    if (posicaoDis != -1) {
        // Verifica a matrícula do aluno na disciplina
        for (int i = 0; i < dis[posicaoDis].contadoraluno; i++) {
            if (dis[posicaoDis].matrialuno[i] == matricula) {
                posicaoAluno = i;
                break; // Se a matrícula for encontrada, sai do loop
            }
        }

      for (int i = 0; i < qt; i++) {
        if (reg[0][i].matri == matricula) {
          posicaoNome = i;
          break; // Se a matrícula for encontrada, sai do loop
        }
      }
        if (posicaoAluno != -1) {
            printf("Aluno encontrado e excluído:\n");
            printf("Nome: %s\n", reg[0][posicaoNome].nome);
            printf("Matrícula: %ld\n", matricula);

            // Exclui o aluno movendo todos os alunos à esquerda
            for (int i = posicaoAluno; i < dis[posicaoDis].contadoraluno; i++) {
                dis[posicaoDis].matrialuno[i] = dis[posicaoDis].matrialuno[i + 1];
            }
            dis[posicaoDis].contadoraluno--; // Decrementa o contador de alunos na disciplina
        } else {
            printf("Aluno com matrícula %ld não encontrado nesta disciplina.\n", matricula);
        }
    } else {
        printf("Disciplina com código %d não encontrada.\n", codigoDisciplina);
    }

    printf("Digite alguma coisa para continuar:\n");
    scanf(" %c", &digit);
  cls
}

void listarAlunoProf(cadastro reg[2][qt], int cad, int *contadoraluno,int *contadorprofessor) {
  cls
  char digit;

  cad--;
  if (cad == 0 && *contadoraluno == 0)
    printf("Nenhum Aluno cadastrado\n");
  else if (cad == 1 && *contadorprofessor == 0)
    printf("Nenhum Professor cadastrado\n");
  else {
    for (int i = 0; i < qt; i++) {
      if (reg[cad][i].matri != 0) {
        printf("Numero de matricula:\t%ld\n", reg[cad][i].matri);
        printf("Nome:\t%s\n", reg[cad][i].nome);
        printf("Sexo:\t");
        if (reg[cad][i].sexo == 1)
          printf("Masculino\n");
        else if (reg[cad][i].sexo == 2)
          printf("Feminino\n");
        else if (reg[cad][i].sexo == 3)
          printf("Outro\n");
        printf("Data:\t%02d/%02d/%d\n", reg[cad][i].data[0],
               reg[cad][i].data[1], reg[cad][i].data[2]);
        printf("Cpf:\t%s\n", reg[cad][i].cpf);
        if(cad == 0)
          printf("Quantidade de materias:\t %d\n", reg[0][i].contadordisciplinas);
        printf("----------------------\n");
      }
    }
  }
  printf("Digite alguma coisa para continuar:\n");
  scanf(" %c", &digit);
  cls
}

void ListarDisciplinas(cadastro2 dis[], cadastro reg[2][qt],int *contadordisciplinas) {
  cls 
  char digit;

  if (*contadordisciplinas == 0) {
    printf("Sem disciplinas cadastradas\n");
  } else {
    for (int i = 0; i < *contadordisciplinas; i++) {
      if (dis[i].matriprof != 0) {
        printf("Nome da disciplina:\t%s\n", dis[i].nome);
        printf("Codigo da disciplina:\t%d\n", dis[i].codigo);
        printf("Semestre da disciplina:\t%dº semestre\n", dis[i].semestre);
        printf("Vagas disponiveis: %d\n", dis[i].vagas - dis[i].contadoraluno);
        printf("Professor da disciplina:\t");
        for (int j = 0; j < qt; j++) {
          if (reg[1][j].matri == dis[i].matriprof) {
            printf("%s\n", reg[1][j].nome);
            break;
          }
        }
        printf("----------------------\n");
      }
    }
  }

  printf("Digite alguma coisa para continuar:\n");
  scanf(" %c", &digit);
  cls
}

void listarumadisciplina(cadastro2 dis[], cadastro reg[2][qt]){
  cls
  char digit;
  int posicao;
  int materia_encontrado = 0;
  printf("Digite o codigo da disciplina:\n");
  scanf(" %d", &posicao);
  
  for(int i = 0; i < materias; i++)
    if(dis[i].codigo == posicao){
      posicao = i;
      materia_encontrado = 1;
      break;
    }

  if(!materia_encontrado){
    printf("Materia não encontrada!\n");
  }else{

    printf("Nome da disciplina:\t%s\n", dis[posicao].nome);
    printf("Codigo da disciplina:\t%d\n", dis[posicao].codigo);
    printf("Semestre da disciplina:\t%dº semestre\n", dis[posicao].semestre);
    printf("Vagas disponiveis: %d\n", dis[posicao].vagas - dis[posicao].contadoraluno);
    printf("Professor da disciplina:\t");
    for (int j = 0; j < qt; j++) {
      if (reg[1][j].matri == dis[posicao].matriprof) {
        printf("%s\n", reg[1][j].nome);
        break;
      }
    }
    printf("----------------------\n");

    // Verifica e imprime os alunos cadastrados
    if (dis[posicao].contadoraluno == 0) {
      printf("Não tem alunos cadastrados\n");
    } else {
      printf("Alunos cadastrados:\n");
      for (int k = 0; k < dis[posicao].contadoraluno; k++) {
        int aluno_encontrado =
            0; // Variável para verificar se o aluno está cadastrado
        for (int l = 0; l < qt; l++) 
          if (reg[0][l].matri == dis[posicao].matrialuno[k]) {
            printf("%s\n", reg[0][l].nome);
            aluno_encontrado = 1;
            break;
          }

        if (!aluno_encontrado) {
          printf("Nenhum aluno cadastrado\n");
        }
      }
    }
  }
  printf("Digite alguma coisa para continuar:\n");
  scanf(" %c", &digit);
  cls
}

void listarpessoaporsexo(cadastro reg[2][qt], int cad){
  cls
 
  int pessoa_encontrado = 0;
  int sexo;
  char digit;

  cad--;
  printf("Digite o sexo:\n1:Masculino\n2:Feminino\n3:Outro\n\n");
  scanf(" %d", &sexo);
  for(int i = 0; i < qt; i++){
    if(reg[cad][i].sexo == sexo && reg[cad][i].sexo != 0){
      printf("Numero de matricula:\t%ld\n", reg[cad][i].matri);
      printf("Nome:\t%s\n", reg[cad][i].nome);
      printf("Sexo:\t");
      if (reg[cad][i].sexo == 1)
        printf("Masculino\n");
      else if (reg[cad][i].sexo == 2)
        printf("Feminino\n");
      else if (reg[cad][i].sexo == 3)
        printf("Outro\n");

      printf("Data:\t%02d/%02d/%d\n", reg[cad][i].data[0],
             reg[cad][i].data[1], reg[cad][i].data[2]);

      printf("Cpf:\t%s\n", reg[cad][i].cpf);
      if(cad == 0)
        printf("Quantidade de materias:\t %d\n", reg[cad][i].contadordisciplinas);
      printf("----------------------\n");
      pessoa_encontrado = 1;
    }
  }
  if(!pessoa_encontrado){
    printf("Ninguem com esse sexo encontrado\n");
  }

  printf("Digite alguma coisa para continuar:\n");
  scanf(" %c", &digit);
  cls
}
  
void ListarAlunopoucadisciplina(cadastro2 dis[], cadastro reg[2][qt]){
char digit;
  cls
  printf("Lista de alunos:\n");
  int aluno_encontrado = 0;
  for(int i = 0; i < qt; i++){
    if(reg[0][i].contadordisciplinas < 3 && reg[0][i].contadordisciplinas != 0){
        printf("Numero de matricula:\t%ld\n", reg[0][i].matri);
        printf("Nome:\t%s\n", reg[0][i].nome);
        printf("Sexo:\t");
        if (reg[0][i].sexo == 1)
          printf("Masculino\n");
        else if (reg[0][i].sexo == 2)
          printf("Feminino\n");
        else if (reg[0][i].sexo == 3)
          printf("Outro\n");

        printf("Data:\t%02d/%02d/%d\n", reg[0][i].data[0],
               reg[0][i].data[1], reg[0][i].data[2]);

        printf("Cpf:\t%s\n", reg[0][i].cpf);
        printf("Quantidade de materias:\t %d\n", reg[0][i].contadordisciplinas);
        printf("----------------------\n");
        aluno_encontrado = 1;
      }
    }
  if(!aluno_encontrado){
    printf("Nenhum aluno\n");
  }
  printf("Digite alguma coisa para continuar:\n");
  scanf(" %c", &digit);
  cls
}

void listarPorNascimento(cadastro reg[2][qt], int cad, int AnoAtual){
  cls
  cad--;
  int ano;
  int mes;
  int dia;
  char digit;

  int pessoa_encontrada = 0;
  
  for (ano = AnoMinimo; ano <= AnoAtual; ano++)
    for (mes = 1; mes <= 12; mes++)
      for (dia = 1; dia <= 31; dia++)
        for(int i = 0; i < qt; i++){
          if(reg[cad][i].data[0] == dia && reg[cad][i].data[1] == mes && reg[cad][i].data[2] == ano){
            printf("Numero de matricula:\t%ld\n", reg[cad][i].matri);
            printf("Nome:\t%s\n", reg[cad][i].nome);
            printf("Sexo:\t");
            if (reg[cad][i].sexo == 1)
              printf("Masculino\n");
            else if (reg[cad][i].sexo == 2)
              printf("Feminino\n");
            else if (reg[cad][i].sexo == 3)
              printf("Outro\n");
            printf("Data:\t%02d/%02d/%d\n", reg[cad][i].data[0],
                   reg[cad][i].data[1], reg[cad][i].data[2]);
            printf("Cpf:\t%s\n", reg[cad][i].cpf);
            if(cad == 0)
              printf("Quantidade de materias:\t %d\n", reg[0][i].contadordisciplinas);
            printf("----------------------\n");
            pessoa_encontrada = 1;
          }
        }
      
  if(!pessoa_encontrada){
    printf("Nenhum Pessoa Encontrada\n");
  }
  printf("Digite alguma coisa para continuar:\n");
  scanf(" %c", &digit);
  cls
}

void listarAniversariantes(cadastro reg[2][qt], int contadoraluno, int contadorprofessor){
  cls
  int mes;
  int dia;
  char digit;

  printf("Digite o mes para pesquisar os aniversariantes:\n");
  scanf(" %d", &mes);

  if (mes < 1 || mes > 12) {
      printf("Mes invalido. Digite um numero de mes valido (1 a 12).\n");
      printf("Digite alguma coisa para continuar:\n");
      scanf(" %c", &digit);
     return;
  }
  
  if(contadoraluno != 0){
    printf("Lista de alunos fazendo aniversario:\n\n");
           for (dia = 1; dia <= 31; dia++)
            for(int i = 0; i < qt; i++){
              if(reg[0][i].data[0] == dia && reg[0][i].data[1] == mes){
                printf("Numero de matricula:\t%ld\n", reg[0][i].matri);
                printf("Nome:\t%s\n", reg[0][i].nome);
                printf("Sexo:\t");
                if (reg[0][i].sexo == 1)
                  printf("Masculino\n");
                else if (reg[0][i].sexo == 2)
                  printf("Feminino\n");
                else if (reg[0][i].sexo == 3)
                  printf("Outro\n");
                printf("Data:\t%02d/%02d/%d\n", reg[0][i].data[0],
                       reg[0][i].data[1], reg[0][i].data[2]);
                printf("Cpf:\t%s\n", reg[0][i].cpf);
                printf("Quantidade de materias:\t %d\n", reg[0][i].contadordisciplinas);
                printf("----------------------\n");
          }
        }
        printf("\n");
}else
    printf("Nenhum aluno faz aniversario nesse mes\n");
  
  if(contadorprofessor != 0){
    printf("Lista de professores fazendo aniversario:\n\n");
      for (dia = 1; dia <= 31; dia++)
        for(int i = 0; i < qt; i++){
          if(reg[1][i].data[0] == dia && reg[1][i].data[1] == mes){
            printf("Numero de matricula:\t%ld\n", reg[1][i].matri);
            printf("Nome:\t%s\n", reg[1][i].nome);
            printf("Sexo:\t");
            if (reg[1][i].sexo == 1)
              printf("Masculino\n");
            else if (reg[1][i].sexo == 2)
              printf("Feminino\n");
            else if (reg[1][i].sexo == 3)
              printf("Outro\n");
            printf("Data:\t%02d/%02d/%d\n", reg[1][i].data[0],
                   reg[1][i].data[1], reg[1][i].data[2]);
            printf("Cpf:\t%s\n", reg[1][i].cpf);
            printf("----------------------\n");
      }
    }
      
  }else
    printf("Nenhum Professor faz aniversario nesse mes\n");
    
  printf("Digite alguma coisa para continuar:\n");
  scanf(" %c", &digit);
  cls
}

void listarPorNome(cadastro reg[2][qt], int cad, int contadoraluno, int contadorprofessor){
  cls
  cad--;
  char digit;

  cadastro aux[2][qt];
  int pessoa_encontrada = 0;

  memcpy(&aux, &reg, sizeof(cadastro));

  for (int i = 0; i < qt - 1; i++) {
      for (int j = i + 1; j < qt; j++) {
          if (strcmp(aux[cad][i].nome, aux[cad][j].nome) > 0) {
              cadastro temp = aux[cad][i];
              aux[cad][i] = aux[cad][j];
              aux[cad][j] = temp;
          }
      }
  }

  cad++;

  listarAlunoProf(reg, cad, &contadoraluno, &contadorprofessor);
}

void listardis40(cadastro2 dis[],cadastro reg[2][qt], int *contadordisciplinas){
  cls
  char digit;

  if (*contadordisciplinas == 0) {
    printf("Sem disciplinas cadastradas\n");
  } else {
  for(int i = 0; i < materias; i++){
    if(dis[i].vagas > 40){
        printf("Nome da disciplina:\t%s\n", dis[i].nome);
        printf("Codigo da disciplina:\t%d\n", dis[i].codigo);
        printf("Semestre da disciplina:\t%dº semestre\n", dis[i].semestre);
        printf("Vagas disponiveis: %d\n", dis[i].vagas - dis[i].contadoraluno);
        printf("Professor da disciplina:\t");
        for (int j = 0; j < qt; j++) {
          if (reg[1][j].matri == dis[i].matriprof) {
            printf("%s\n", reg[1][j].nome);
            break;
          }
        }
        printf("----------------------\n");
      }
    }

  }
  printf("Digite alguma coisa para continuar:\n");
  scanf(" %c", &digit);
  cls
}

void buscarpornome(cadastro reg[2][qt], int contadoraluno, int contadorprofessor){
  cls
  char buscador[TAM];
  char *palavra, digit;
  int tamanho;
  int aluno_encontrado = 0;
  int professor_encontrado = 0;
  if((contadoraluno == 0) && (contadorprofessor == 0)){
    printf("Nenhuma pessoa cadastrada ainda\n");
  }else{
    printf("Digite pelo menos 3 letras para buscar o nome:\n");
    scanf(" %[^\n]s", &buscador[0]);
    tamanho = strlen(buscador);
    if(tamanho < 3){
      printf("Valor menor do que necessario!");
    }else{
      printf("Aluno com essas letras:\n");
      for(int i = 0; i < contadoraluno; i++){
        palavra = strstr(reg[0][i].nome, buscador);
        if(palavra){
          printf("Numero de matricula:\t%ld\n", reg[0][i].matri);
          printf("Nome:\t%s\n", reg[0][i].nome);
          printf("Sexo:\t");
          if (reg[0][i].sexo == 1)
            printf("Masculino\n");
          else if (reg[0][i].sexo == 2)
            printf("Feminino\n");
          else if (reg[0][i].sexo == 3)
            printf("Outro\n");
          printf("Data:\t%02d/%02d/%d\n", reg[0][i].data[0],
                 reg[0][i].data[1], reg[0][i].data[2]);
          printf("Cpf:\t%s\n", reg[0][i].cpf);
          printf("Quantidade de materias:\t %d\n", reg[0][i].contadordisciplinas);
          printf("----------------------\n");
          aluno_encontrado = 1;
        }
      }
      if(!aluno_encontrado)
        printf("Nenhum aluno com essas letras encontrado!\n\n");
      
      printf("Professor com essas letras:\n");
      for(int j = 0; j < contadorprofessor;j++){
        palavra = strstr(reg[1][j].nome, buscador);
        if(palavra){
          printf("Numero de matricula:\t%ld\n", reg[1][j].matri);
          printf("Nome:\t%s\n", reg[1][j].nome);
          printf("Sexo:\t");
          if (reg[1][j].sexo == 1)
            printf("Masculino\n");
          else if (reg[1][j].sexo == 2)
            printf("Feminino\n");
          else if (reg[1][j].sexo == 3)
            printf("Outro\n");
          printf("Data:\t%02d/%02d/%d\n", reg[1][j].data[0],
                 reg[1][j].data[1], reg[1][j].data[2]);
          printf("Cpf:\t%s\n", reg[1][j].cpf);
          printf("----------------------\n");
          professor_encontrado = 1;
        }
      }
      if(!professor_encontrado)
        printf("Nenhum professor com essas letras encontrado!\n");
    }
    
  }

  printf("Digite alguma coisa para continuar:\n");
    scanf(" %c", &digit);
  cls
}

// void buscarpornome2(cadastro reg[2][qt], int contadoraluno, int contadorprofessor){
//   cls
//   char buscador[TAM];
//     char *palavra, digit;
//     int tamanho;
//     int aluno_encontrado = 0;
//     int professor_encontrado = 0;
//     if((contadoraluno == 0) && (contadorprofessor == 0)){
//       printf("Nenhuma pessoa cadastrada ainda\n");
//     }else{

//       cadastro aux[2][qt];

//       memcpy(&aux, &reg, sizeof(cadastro));

//       for (int i = 0; i < qt - 1; i++)
        
      
//       for (int cad = 0; cad < 2; cad++)
//         for (int i = 0; i < qt - 1; i++) //para a struct
//           for (int j = i + 1; j < TAM - 1; j++)//para o nome
//             if (aux[cad][i].nome[j] < "A" && aux[cad][i].nome[j] > "Z")
//               aux[cad][i].nome[j] = aux[cad][i].nome[j] + 32;

//       printf("Digite pelo menos 3 letras para buscar o nome:\n");
//       scanf(" %[^\n]s", &buscador[0]);
//       tamanho = strlen(buscador);
//       if(tamanho < 3){
//         printf("Valor menor do que necessario!");
//       }else{
//         printf("Aluno com essas letras:\n");
//         for(int i = 0; i < contadoraluno; i++){
//           palavra = strstr(reg[0][i].nome, buscador);
//           if(palavra){
//             printf("Numero de matricula:\t%ld\n", reg[0][i].matri);
//             printf("Nome:\t%s\n", reg[0][i].nome);
//             printf("Sexo:\t");
//             if (reg[0][i].sexo == 1)
//               printf("Masculino\n");
//             else if (reg[0][i].sexo == 2)
//               printf("Feminino\n");
//             else if (reg[0][i].sexo == 3)
//               printf("Outro\n");
//             printf("Data:\t%02d/%02d/%d\n", reg[0][i].data[0],
//                    reg[0][i].data[1], reg[0][i].data[2]);
//             printf("Cpf:\t%s\n", reg[0][i].cpf);
//             printf("Quantidade de materias:\t %d\n", reg[0][i].contadordisciplinas);
//             printf("----------------------\n");
//             aluno_encontrado = 1;
//           }
//         }
//         if(!aluno_encontrado)
//           printf("Nenhum aluno com essas letras encontrado!\n\n");

//         printf("Professor com essas letras:\n");
//         for(int j = 0; j < contadorprofessor;j++){
//           palavra = strstr(reg[1][j].nome, buscador);
//           if(palavra){
//             printf("Numero de matricula:\t%ld\n", reg[1][j].matri);
//             printf("Nome:\t%s\n", reg[1][j].nome);
//             printf("Sexo:\t");
//             if (reg[1][j].sexo == 1)
//               printf("Masculino\n");
//             else if (reg[1][j].sexo == 2)
//               printf("Feminino\n");
//             else if (reg[1][j].sexo == 3)
//               printf("Outro\n");
//             printf("Data:\t%02d/%02d/%d\n", reg[1][j].data[0],
//                    reg[1][j].data[1], reg[1][j].data[2]);
//             printf("Cpf:\t%s\n", reg[1][j].cpf);
//             printf("----------------------\n");
//             professor_encontrado = 1;
//           }
//         }
//         if(!professor_encontrado)
//           printf("Nenhum professor com essas letras encontrado!\n");
//       }

//     }

//     printf("Digite alguma coisa para continuar:\n");
//       scanf(" %c", &digit);
//     cls
// }
// fim das funções

int main(){
    cadastro reg[2][qt];
    cadastro2 dis[materias];
    int opcao = 0, sair = 0;
    int sairmenucad, sairmenueditar, sairmenulista, sairmenulistaaluno, sairmenulistaprof, sairmenulistadisciplina;
    int cad;
    int contadoraluno = 0;
    int contadorprofessor = 0;
    int contadordisciplinas = 0;
    long int buscamatricula = 0;
    
    time_t rawtime;
    struct tm *info;
    int AnoAtual;

    // Obtém o tempo atual
    time(&rawtime);

    // Obtém os componentes de data local
    info = localtime(&rawtime);

    // Obtém o ano atual
    AnoAtual = info->tm_year + 1900;

    
    // Zerar matricula de aluno e professor
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < qt; j++){
        reg[i][j].matri = 0;
        dis[i].matriprof = 0;
        reg[i][j].sexo = 0;
      }
    }

    // Menu incial
    printf("************************************\n");
    printf("** Bem vindo(a) ao Menu da escola **\n");
    printf("************************************\n");
    printf("      Por Tuvo, Lara e Julio\n");
    printf("************************************\n");
    printf("\t0- Comecar programa\n");
    printf("\t1- Sair do programa\n");
    printf("************************************\n");
    scanf(" %d", &opcao);
    if (opcao != 0)
      sair = 1;
    cls 
    while (!sair) {
      
      printf("Selecione a opcao:\n");
      printf("1:Cadastro\n");
      printf("2:Listas\n");
      printf("3:Sair\n\n");
      scanf(" %d", &opcao);
      
      switch (opcao) {
      // inicio do switch menu principal
      case 1:
        // Cadastro em geral
        
        cls 
        sairmenucad = 0;
        while(!sairmenucad){
        menucadastro(&cad);
        switch (cad) {
          // CAD é usado no lugar do reg[0] ou reg[1], no case 1 e case 2,
          // assim, automaticamente levando pro aluno ou professor. inicio
          // switch cadastro
        case 1:
          cadastrarPessoa(reg, cad, &contadoraluno, AnoAtual);
          break;

        case 2:
          cadastrarPessoa(reg, cad, &contadorprofessor, AnoAtual);
          break;

        case 3:
          cadastrarDisciplina(dis, &contadordisciplinas, reg,contadorprofessor);
          break;
        case 4:
          //inicio case 4 cadastro
          cls
          sairmenueditar = 0;
          while(!sairmenueditar){
          menuEditar(&cad);
          switch (cad) {
          case 1:
            menuEditarAluno(&opcao);
            switch (opcao) {
            case 1:
              atualizarPessoaPorMatricula(cad, reg, &contadoraluno, AnoAtual);
              break;

            case 2:
              excluirPessoaPorMatricula(cad, reg, &contadoraluno, buscamatricula, &contadordisciplinas,dis);
              break;
            default: cls printf("Menu não encontrado\n");
            }
          break;
            
          case 2:
            menuEditarProf(&opcao);
            switch (opcao) {
            case 1:
              atualizarPessoaPorMatricula(cad, reg, &contadorprofessor,AnoAtual);
              break;

            case 2:
              excluirPessoaPorMatricula(cad, reg, &contadorprofessor, buscamatricula, &contadordisciplinas, dis);
              break;
            default: cls printf("Menu não encontrado\n");
            }
          break;
          case 3:
            menuEditarDis(&opcao);
            switch (opcao) {
            case 1:
              atualizarDisciplina(dis, &contadordisciplinas, reg);
              break;
            case 2:
              excluirDisciplina(dis, &contadordisciplinas);
              break;
            default: cls printf("Menu indisponivel\n");
            }
          break;
          case 4:
              adicionarAlunoDaDisciplina(reg , dis);
          break;
          case 5:
              excluirAlunoDaDisciplina(reg, dis);
          break;
          case 6: sairmenueditar = 1; cls
          break;
          default: cls printf("Menu indisponivel\n");
          }//fim case 4 gigante
        } //while saireditar
          
          break;

          case 5: sairmenucad = 1; cls
          break;

          default: cls printf("Menu indisponivel\n");
          
        }// fim switch cadastro
      } // fim do while saircad
        break;
        //fim case 1; switch principal
      case 2:
        // Listas em geral
        cls
        sairmenulista = 0;
        while(!sairmenulista){
        menulista(&cad);
        // inicio do switch lista
        switch (cad) {
        case 1:

          cls
          sairmenulistaaluno = 0;
          while(!sairmenulistaaluno){
          menualuno(&opcao);
          switch (opcao) {
            case 1:
              cls listarAlunoProf(reg, cad, &contadoraluno, &contadorprofessor);
              break;
            case 2:
                listarpessoaporsexo(reg, cad);
              break;
            case 3:
                listarPorNome(reg, cad, contadoraluno, contadorprofessor);
              break;
            case 4:
              listarPorNascimento(reg, cad, AnoAtual);
              break;
            case 5:
                ListarAlunopoucadisciplina(dis, reg);
              break;
            case 6: sairmenulistaaluno = 1; cls
              break;
            default: cls printf("Menu indisponivel\n");
          }//fim switchmenualuno
        }//fim while sairlistaaluno
          break;
          
        case 2:
          cls
          sairmenulistaprof = 0;
          while(!sairmenulistaprof){
          menuprof(&opcao);

          switch (opcao) {

            case 1:
              cls listarAlunoProf(reg, cad, &contadoraluno, &contadorprofessor);
              break;
            case 2:
                listarpessoaporsexo(reg, cad);
              break;
            case 3: 
                listarPorNome(reg, cad, contadoraluno, contadorprofessor);
              break;
            case 4:
                listarPorNascimento(reg, cad, AnoAtual);
              break;
            case 5: sairmenulistaprof = 1; cls
              break;
            default: cls printf("Menu indisponivel\n");
          }// fim switch menulistaprof
        }//fim while sairlistaprof
          break;

        case 3:
          cls
          sairmenulistadisciplina = 0;
          while(!sairmenulistadisciplina){
          menudisciplina(&opcao);
          switch (opcao) {
            case 1:
              ListarDisciplinas(dis, reg, &contadordisciplinas);
              break;
            case 2: listarumadisciplina(dis, reg);
              break;
            case 3: listardis40(dis, reg, &contadordisciplinas);
              break;
            case 4: sairmenulistadisciplina = 1; cls
              break;
            default: cls printf("Menu indisponivel\n");
          }//fim do switch
        }//fim do while
          break;
        
          
        case 4:
            listarAniversariantes(reg,contadoraluno, contadorprofessor);
          break;
          
        case 5:
            buscarpornome(reg, contadoraluno, contadorprofessor);
          break;
          
        case 6: sairmenulista = 1; cls
          break;
          
        default: cls printf("Menu indisponivel\n");
         
        } // fim do switch menu lista
      } //fim do while menu lista
        break;

      case 3:
        sair = 1;
        break;
      default: cls printf("Menu indisponivel\n");
        // fim switch menu principal
      }

      // fim do while
    }
    // fim do codigo
    return 0;
  }
