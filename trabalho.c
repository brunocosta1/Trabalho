/*
 * Aluno: Bruno Costa dos Passos
 * Matrícula: 120.060.010
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ocorrencia {
  int arquivo;
  int qtdOcorrencias;
  int *linhas;

  struct Ocorrencia *prox;
};

struct Arquivo {
  char nomeArquivo[50];
  struct Arquivo *prox;
};

struct Indice {
  int qtdArquivos;
  struct Arquivo *arquivos;

  int qtdPalavras;
  /*struct Palavra *palavras;*/

  struct Palavra *iniciais[26];
};

struct Palavra {
  char letras[50];    // Caracteres que formam a palavra.
  int qtdOcorrencias; // Quantidade de ocorrências no arquivo.

  struct Ocorrencia *ocorrencias;
  struct Palavra *prox;
};

struct Arquivo *InsereArquivo(struct Arquivo *l, char nomeArquivo[50]) {
  struct Arquivo *aux = l;

  struct Arquivo *novo = malloc(sizeof(struct Arquivo));
  strcpy(novo->nomeArquivo, nomeArquivo);
  novo->prox = NULL;

  if (aux != NULL) {
    while (aux->prox != NULL)
      aux = aux->prox;
    aux->prox = novo;
    return l;
  } else
    return novo;
}

int ExisteArquivo(struct Arquivo *arquivos, char nomeArquivo[50]) {
  struct Arquivo *aux = arquivos;

  while (aux != NULL) {
    if (strcmp(aux->nomeArquivo, nomeArquivo) == 0)
      return 1;
    aux = aux->prox;
  }

  return 0;
}

int ExistePalavra(char *palavra, struct Palavra *lista) {
  struct Palavra *aux = lista;

  while (aux != NULL) {
    if (strcmp(aux->letras, palavra) == 0)
      return 1;
    aux = aux->prox;
  }

  return 0;
}

int existeIdArquivo(struct Palavra *palavra, int idArquivo) {
  struct Ocorrencia *aux = palavra->ocorrencias;

  while (aux != NULL) {
    if (aux->arquivo == idArquivo)
      return 1;
    aux = aux->prox;
  }

  return 0;
}

struct Palavra *BuscaPalavra(char *palavra, struct Palavra *lista) {
  struct Palavra *aux = lista;

  while (aux != NULL && strcmp(aux->letras, palavra) != 0)
    aux = aux->prox;

  return aux;
}

struct Ocorrencia *BuscaOcorrencia(struct Palavra *palavra, int idArquivo) {
  struct Ocorrencia *aux = palavra->ocorrencias;

  while (aux->prox != NULL && aux->arquivo != idArquivo)
    aux = aux->prox;

  return aux;
}

struct Ocorrencia *BuscaUltimaOcorrencia(struct Palavra *palavra) {
  struct Ocorrencia *aux = palavra->ocorrencias;

  while (aux->prox != NULL)
    aux = aux->prox;

  return aux;
}

struct Palavra *criaPalavra(char *palavra) {
  struct Palavra *novaPalavra = malloc(sizeof(struct Palavra));
  strcpy(novaPalavra->letras, palavra);
  novaPalavra->qtdOcorrencias = 1;
  novaPalavra->ocorrencias = NULL;
  novaPalavra->prox = NULL;

  return novaPalavra;
}

struct Ocorrencia *criaOcorrencia(int idArquivo, int linha) {
  struct Ocorrencia *novaOcorrencia = malloc(sizeof(struct Ocorrencia));
  novaOcorrencia->arquivo = idArquivo;
  novaOcorrencia->qtdOcorrencias = 1;
  novaOcorrencia->linhas = calloc(0, sizeof(int));
  novaOcorrencia->linhas[0] = linha;
  novaOcorrencia->prox = NULL;

  return novaOcorrencia;
}

struct Palavra *InserePalavra(char *palavra, struct Indice *indice, int linha,
                              int idArquivo, int n) {
  if (!ExistePalavra(palavra, indice->iniciais[n])) {

    indice->qtdPalavras++;

    struct Palavra *novaPalavra = criaPalavra(palavra);
    struct Ocorrencia *novaOcorrencia = criaOcorrencia(idArquivo, linha);

    novaPalavra->ocorrencias = novaOcorrencia;

    if (indice->iniciais[n] == NULL) {
      return novaPalavra;
    } else if (strcmp(palavra, indice->iniciais[n]->letras) < 0) {
      novaPalavra->prox = indice->iniciais[n];
      return novaPalavra;
    } else {
      struct Palavra *aux = indice->iniciais[n];

      while (aux->prox && strcmp(palavra, aux->prox->letras) > 0)
        aux = aux->prox;

      novaPalavra->prox = aux->prox;
      aux->prox = novaPalavra;

      return indice->iniciais[n];
    }
  } else {
    struct Palavra *palavraExistente =
        BuscaPalavra(palavra, indice->iniciais[n]);

    if (existeIdArquivo(palavraExistente, idArquivo)) {
      struct Ocorrencia *aux = BuscaOcorrencia(palavraExistente, idArquivo);

      aux->qtdOcorrencias++;
      aux->linhas =
          (int *)realloc(aux->linhas, sizeof(int) * (aux->qtdOcorrencias - 1));
      aux->linhas[aux->qtdOcorrencias - 1] = linha;

      return indice->iniciais[n];
    } else {
      palavraExistente->qtdOcorrencias++;

      struct Ocorrencia *novaOcorrencia = criaOcorrencia(idArquivo, linha);
      struct Ocorrencia *aux = BuscaUltimaOcorrencia(palavraExistente);

      aux->prox = novaOcorrencia;

      return indice->iniciais[n];
    }
  }
}

int retornaIndice(char c) {

  switch (c) {

  case 'a':
    return 0;
    break;

  case 'b':
    return 1;
    break;

  case 'c':
    return 2;
    break;

  case 'd':
    return 3;
    break;

  case 'e':
    return 4;
    break;

  case 'f':
    return 5;
    break;

  case 'g':
    return 6;
    break;

  case 'h':
    return 7;
    break;

  case 'i':
    return 8;
    break;

  case 'j':
    return 9;
    break;

  case 'k':
    return 10;
    break;

  case 'l':
    return 11;
    break;

  case 'm':
    return 12;
    break;

  case 'n':
    return 13;
    break;

  case 'o':
    return 14;
    break;

  case 'p':
    return 15;
    break;

  case 'q':
    return 16;
    break;

  case 'r':
    return 17;
    break;

  case 's':
    return 18;
    break;

  case 't':
    return 19;
    break;

  case 'u':
    return 20;
    break;

  case 'v':
    return 21;
    break;

  case 'x':
    return 22;
    break;

  case 'w':
    return 23;
    break;

  case 'y':
    return 24;
    break;

  case 'z':
    return 25;
    break;
  }

  return -1;
}

struct Indice *processaArquivo(struct Indice *indice) {
  char nomeArquivo[50];

  printf("Digite o nome do arquivo:\n");
  scanf("%s", nomeArquivo);

  if (!ExisteArquivo(indice->arquivos, nomeArquivo)) {
    FILE *arq = fopen(nomeArquivo, "r");

    if (arq != NULL) {
      indice->qtdArquivos++;
      indice->arquivos =
          InsereArquivo(indice->arquivos, nomeArquivo); // Insere no final

      char buffer[1024];
      char *palavra;
      char *delimitadores = " \",.;:[]{}()|-\n";
      int num_linhas = 0, num_palavras = 0;
      int n = 0;

      while (fscanf(arq, "%[^\n] ", buffer) != EOF) {
        palavra = strtok(buffer, delimitadores);

        while (palavra != NULL) {
          n = retornaIndice(palavra[0]);
          printf("%d\n", n);
          indice->iniciais[n] = InserePalavra(palavra, indice, num_linhas,
                                              indice->qtdArquivos, n);

          num_palavras++;
          palavra = strtok(NULL, delimitadores);
        }
        num_linhas++;
      }
      fclose(arq);
    } else {
      printf("Erro ao abrir o arquivo.\n");
    }
  } else {
    printf("Arquivo já foi processado.\n");
  }

  return indice;
}

void show(struct Indice *indice) {
  struct Arquivo *arquivo = indice->arquivos;

  printf("Nome dos arquivos:\n");
  for (int i = 0; i < indice->qtdArquivos; i++) {
    printf("%s ", arquivo->nomeArquivo);
    arquivo = arquivo->prox;
  }
  printf("\n");

  printf("\nPalavras:\n");

  for (int i = 0; i < 26; i++) {

    struct Palavra *palavra = indice->iniciais[i];

    if (palavra != NULL) {

      while (palavra != NULL) {
        struct Ocorrencia *ocorrencia = palavra->ocorrencias;

        printf("\n%s\n", palavra->letras);

        while (ocorrencia != NULL) {
          printf("Numero do arquivo: %d | Quantidade de vezes que aparece no "
                 "arquivo: %d | Linhas: ",
                 ocorrencia->arquivo, ocorrencia->qtdOcorrencias);
          for (int i = 0; i < ocorrencia->qtdOcorrencias; i++)
            printf("[%d] ", ocorrencia->linhas[i]);
          printf("\n");

          ocorrencia = ocorrencia->prox;
        }
        printf("\n");
        palavra = palavra->prox;
      }
    }
  }
}

void salvarIndice(struct Indice *indice) {
  FILE *arq = fopen("indice.dat", "wb");

  if (arq != NULL) {
    fwrite(&indice->qtdArquivos, sizeof(int), 1, arq);

    struct Arquivo *aux = indice->arquivos;

    while (aux != NULL) {
      int qtd = strlen(aux->nomeArquivo) + 1;
      fwrite(&qtd, sizeof(int), 1, arq);
      fwrite(aux->nomeArquivo, sizeof(char), qtd, arq);
      aux = aux->prox;
    }

    fwrite(&indice->qtdPalavras, sizeof(int), 1, arq);

    for (int i = 0; i < 26; i++) {
      for (struct Palavra *aux1 = indice->iniciais[i]; aux1 != NULL;
           aux1 = aux1->prox) {

        if (aux1 != NULL) {

          int qtd = strlen(aux1->letras) + 1;
          fwrite(&qtd, sizeof(int), 1, arq);
          fwrite(aux1->letras, sizeof(char), qtd, arq);
          fwrite(&aux1->qtdOcorrencias, sizeof(int), 1, arq);

          for (struct Ocorrencia *tmp = aux1->ocorrencias; tmp != NULL;
               tmp = tmp->prox) {

            fwrite(&tmp->arquivo, sizeof(int), 1, arq);
            fwrite(&tmp->qtdOcorrencias, sizeof(int), 1, arq);
            fwrite(tmp->linhas, sizeof(int), tmp->qtdOcorrencias, arq);
          }
        }
      }
    }
    fclose(arq);
  } else {
    printf("Erro ao abrir o arquivo para escrita\n");
  }
}

struct Indice *destroiIndice(struct Indice *indice) {

  int ver = 0;

  for (int i = 0; i < 26; i++) {
    if (indice->iniciais[i] != NULL)
      ver = 1;
  }

  int condicao = (indice->qtdArquivos != 0 && indice->qtdPalavras != 0 &&
                  indice->arquivos != NULL && ver);

  if (condicao) {
    for (int i = 0; i < 26; i++) {
      struct Palavra *aux1 = indice->iniciais[i];

      if (aux1 != NULL) {
        while (aux1 != NULL) {
          struct Palavra *aux4 = aux1->prox;

          struct Ocorrencia *aux2 = aux1->ocorrencias;

          while (aux2 != NULL) {
            struct Ocorrencia *aux3 = aux2->prox;

            aux2->prox = NULL;

            free(aux2->linhas);
            free(aux2);
            aux2 = aux3;
          }

          aux1->prox = NULL;
          free(aux1);

          aux1 = aux4;
        }
      }
    }
    struct Arquivo *aux5 = indice->arquivos;

    while (aux5 != NULL) {
      indice->arquivos->prox = NULL;
      free(indice->arquivos);

      indice->arquivos = aux5;
      aux5 = aux5->prox;
    }
  }

  for (int i = 0; i < 26; i++)
    indice->iniciais[i] = NULL;

  indice->arquivos = NULL;
  indice->qtdArquivos = 0;
  indice->qtdPalavras = 0;

  return indice;
}

struct Indice *lerIndice(struct Indice *indice) {
  FILE *arq = fopen("indice.dat", "rb");

  if (arq != NULL) {
    fread(&indice->qtdArquivos, sizeof(int), 1, arq);
    for (int i = 0; i < indice->qtdArquivos; i++) {
      int qtd_letras = 0;
      fread(&qtd_letras, sizeof(int), 1, arq);
      char nomeArquivo[50];
      fread(nomeArquivo, sizeof(char), qtd_letras, arq);
      indice->arquivos = InsereArquivo(indice->arquivos, nomeArquivo);
    }

    fread(&indice->qtdPalavras, sizeof(int), 1, arq);
    for (int i = 0; i < indice->qtdPalavras; i++) {
      int qtd_letras = 0;
      fread(&qtd_letras, sizeof(int), 1, arq);
      struct Palavra *palavra = malloc(sizeof(struct Palavra));
      palavra->qtdOcorrencias = 0;
      palavra->ocorrencias = NULL;
      palavra->prox = NULL;

      fread(palavra->letras, sizeof(char), qtd_letras, arq);
      fread(&palavra->qtdOcorrencias, sizeof(int), 1, arq);

      int n = retornaIndice(palavra->letras[0]);

      if (indice->iniciais[n] == NULL)
        indice->iniciais[n] = palavra;
      else {
        struct Palavra *aux = indice->iniciais[n];
        while (aux->prox != NULL)
          aux = aux->prox;
        aux->prox = palavra;
      }

      for (int j = 0; j < palavra->qtdOcorrencias; j++) {
        struct Ocorrencia *ocorrencia = malloc(sizeof(struct Ocorrencia));
        ocorrencia->prox = NULL;
        ocorrencia->linhas = NULL;
        ocorrencia->arquivo = 0;
        ocorrencia->qtdOcorrencias = 0;
        fread(&ocorrencia->arquivo, sizeof(int), 1, arq);
        fread(&ocorrencia->qtdOcorrencias, sizeof(int), 1, arq);
        ocorrencia->linhas = malloc((ocorrencia->qtdOcorrencias) * sizeof(int));
        fread(ocorrencia->linhas, sizeof(int), ocorrencia->qtdOcorrencias, arq);

        if (palavra->ocorrencias == NULL) {
          palavra->ocorrencias = ocorrencia;
        } else {
          struct Ocorrencia *tmp = palavra->ocorrencias;
          while (tmp->prox != NULL)
            tmp = tmp->prox;
          tmp->prox = ocorrencia;
        }
      }
    }
    fclose(arq);
  }

  return indice;
}

char *retornaNomeArquivo(int idArquivo, struct Arquivo *l) {

  struct Arquivo *aux = l;
  for (int i = 1; i < idArquivo; i++)
    aux = aux->prox;
  return aux->nomeArquivo;
}

void BuscaSimples(char palavra[25], struct Indice *indice) {

  int n = retornaIndice(palavra[0]);

  if (n != -1) {
    struct Palavra *l = indice->iniciais[n];

    if (!ExistePalavra(palavra, l)) {
      printf("Palavra não existe no índice\n");
      printf("%s\n", l->letras);
      printf("%d\n", n);
    } else {
      struct Palavra *aux1 = BuscaPalavra(palavra, l);
      struct Ocorrencia *aux2 = aux1->ocorrencias;

      while (aux2 != NULL) {
        printf("Arquivo: <%s>\n",
               retornaNomeArquivo(aux2->arquivo, indice->arquivos));
        printf("Linhas: ");
        for (int i = 0; i < aux2->qtdOcorrencias; i++)
          printf("[%d] ", aux2->linhas[i]);
        printf("\n");

        aux2 = aux2->prox;
      }
    }

  } else {
    printf("Entrada inválida.\n");
  }
}

int buscaTipoE(struct Palavra *palavra1, struct Palavra *palavra2, int *vet) {

  int tam = 0;
  for (struct Ocorrencia *aux1 = palavra1->ocorrencias; aux1 != NULL;
       aux1 = aux1->prox) {
    for (struct Ocorrencia *aux2 = palavra2->ocorrencias; aux2 != NULL;
         aux2 = aux2->prox) {
      if (aux1->arquivo == aux2->arquivo) {
        tam++;
        vet = realloc(vet, sizeof(int) * tam);
        vet[tam - 1] = aux1->arquivo;
      }
    }
  }

  return tam;
}

void BuscaCompostaE(char palavra1[25], char palavra2[25],
                    struct Indice *indice) {

  int n1 = retornaIndice(palavra1[0]);
  int n2 = retornaIndice(palavra2[0]);

  if (n1 != -1 && n2 != -1) {
    struct Palavra *l1 = indice->iniciais[n1];
    struct Palavra *l2 = indice->iniciais[n2];

    if (!ExistePalavra(palavra1, l1) && !ExistePalavra(palavra2, l2)) {
      printf("Alguma das duas palavras não existe no índice\n");
    } else {
      struct Palavra *aux1 = BuscaPalavra(palavra1, l1);
      struct Palavra *aux2 = BuscaPalavra(palavra2, l2);

      int *idArquivos = malloc(sizeof(int));
      int tam = buscaTipoE(aux1, aux2, idArquivos);

      printf("\nArquivos\n");
      for (int i = 0; i < tam; i++) {
        printf("Arquivo %d: <%s>\n", i,
               retornaNomeArquivo(idArquivos[i], indice->arquivos));
      }
      printf("\n");
      free(idArquivos);
    }
  } else {
    printf("Entrada inválida.\n");
  }
}

int verificaExistenciaIdArquivo(int *vet, int tam, int idArquivo) {

  for (int i = 0; i < tam; i++)
    if (vet[i] == idArquivo)
      return 1;

  return 0;
}

int buscaTipoOU(struct Palavra *palavra1, struct Palavra *palavra2, int *vet) {
  int tam = 0;

  for (struct Ocorrencia *aux1 = palavra1->ocorrencias; aux1 != NULL;
       aux1 = aux1->prox) {
    tam++;
    vet = realloc(vet, sizeof(int) * tam);
    vet[tam - 1] = aux1->arquivo;
  }

  for (struct Ocorrencia *aux2 = palavra2->ocorrencias; aux2 != NULL;
       aux2 = aux2->prox) {
    if (!verificaExistenciaIdArquivo(vet, tam, aux2->arquivo)) {
      tam++;
      vet = realloc(vet, sizeof(int) * tam);
      vet[tam - 1] = aux2->arquivo;
    }
  }

  return tam;
}

void BuscaCompostaOU(char palavra1[25], char palavra2[25],
                     struct Indice *indice) {

  int n1 = retornaIndice(palavra1[0]);
  int n2 = retornaIndice(palavra2[0]);

  if (n1 != -1 && n2 != -1) {
    struct Palavra *l1 = indice->iniciais[n1];
    struct Palavra *l2 = indice->iniciais[n2];

    if (!ExistePalavra(palavra1, l1) && !ExistePalavra(palavra2, l2)) {
      printf("Alguma das duas palavras não existe no índice\n");
    } else {

      struct Palavra *aux1 = BuscaPalavra(palavra1, l1);
      struct Palavra *aux2 = BuscaPalavra(palavra2, l2);

      int *idArquivos = malloc(sizeof(int));
      int tam = buscaTipoOU(aux1, aux2, idArquivos);

      printf("\nArquivos:\n\n");
      for (int i = 0; i < tam; i++) {
        printf("Arquivo %d: <%s>\n", i,
               retornaNomeArquivo(idArquivos[i], indice->arquivos));
      }
      printf("\n");
      free(idArquivos);
    }
  } else {
    printf("Entrada inválida.\n");
  }
}

void menuRealizaBusca(struct Indice *indice) {

  int opc = 0;
  char palavra1[25], palavra2[25];
  int opc_aux = 0;

  printf("[1] - Busca simples\n");
  printf("[2] - Busca composta\n");
  scanf("%d", &opc);

  switch (opc) {

  case 1:
    printf("Busca simples selecionada! Digite uma palavra:\n");
    scanf("%s", palavra1);
    BuscaSimples(palavra1, indice);
    break;

  case 2:
    printf(
        "Busca composta selecionada! Digite uma opção para busca composta:\n");
    printf("[1] - Operador E\n");
    printf("[2] - Operador OU\n");
    scanf("%d", &opc_aux);
    printf("Digite a primeira palavra:\n");
    scanf("%s", palavra1);
    printf("Digite a segunda palavra:\n");
    scanf("%s", palavra2);

    if (opc_aux == 1)
      BuscaCompostaE(palavra1, palavra2, indice);
    else if (opc_aux == 2)
      BuscaCompostaOU(palavra1, palavra2, indice);
    else
      printf("Opção inválida.\n");

    break;
  }
}

int main() {

  int opcao = 0;

  struct Indice *indice = malloc(sizeof(struct Indice));
  indice->qtdArquivos = 0;
  indice->qtdPalavras = 0;
  indice->arquivos = NULL;
  /*indice->palavras = NULL;*/
  for (int i = 0; i < 0; i++)
    indice->iniciais[i] = NULL;

  while (opcao != 5) {
    printf("[1] - Processar novo arquivo de texto\n");
    printf("[2] - Salvar índice atual\n");
    printf("[3] - Ler um arquivo de índice\n");
    printf("[4] - Realizar buscas usando índice atual\n");
    printf("[5] - Sair\n");
    scanf("%d", &opcao);

    switch (opcao) {

    case 1:
      indice = processaArquivo(indice);
      break;

    case 2:
      salvarIndice(indice);
      break;

    case 3:
      indice = destroiIndice(indice);
      indice = lerIndice(indice);
      break;

    case 4:
      show(indice);
      menuRealizaBusca(indice);
      break;

    case 5:
      break;

    default:
      printf("Opção inválida.\n");
      exit(1);
      break;
    }
  }
  return 0;
}
