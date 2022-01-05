/*
* Aluno: Bruno Costa dos Passos
* Matrícula: 120.060.010
*
* */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Palavra{
    char letras[50]; // Caracteres que formam a palavra.
    int qtdOcorrencias; // Quantidade de ocorrências no arquivo.
    int *linhas; // Vetor dinâmico.
};

struct Lista{

    struct Palavra palavra;
    struct Lista *prox;

};

// Função usada para quando não existir a palavra na lista.

struct Lista *CriaPalavra(char *p, int linha){

    struct Lista *novo = malloc(sizeof(struct Lista));

    strcpy(novo->palavra.letras, p);
    novo->palavra.qtdOcorrencias = 1; 
    novo->palavra.linhas = calloc(1, sizeof(int));
    novo->palavra.linhas[0] = linha;
    novo->prox = NULL;

    return novo;
}

// Função usada para quando for necessário acessar a palavra que já está na lista.

struct Lista *BuscaPalavra(struct Lista *l, char *p){

    struct Lista *aux = l;

    while(aux != NULL && strcmp(aux->palavra.letras, p) != 0)
        aux = aux->prox;

    return aux; 
    
}

// Função usada para quando for necessário saber se a lista já possui ou não determinada palavra.

int quantidade_palavras(struct Lista *l, char *p){

    struct Lista *aux = BuscaPalavra(l, p);

    if(aux == NULL)
        return 0;
    else
        return aux->palavra.qtdOcorrencias;

}

// Função usada para inserir uma palavra na lista, atualizando seus valores.

struct Lista *Insere(struct Lista *l, char *p, int linha){


    if(quantidade_palavras(l, p) == 0){
        struct Lista *no = CriaPalavra(p, linha);

        if(l == NULL){
            return no;
        }else if (strcmp(p, l->palavra.letras) < 0){
            no->prox = l;
            return no;
        }
        else{

            struct Lista *aux = l;
            while(aux->prox && strcmp(p, aux->prox->palavra.letras) > 0)
                aux = aux->prox;

            no->prox = aux->prox;
            aux->prox = no;

            return l;
        }
    }else{

        struct Lista *aux = BuscaPalavra(l, p);

        aux->palavra.linhas[aux->palavra.qtdOcorrencias] = linha;
        aux->palavra.qtdOcorrencias++;
        aux->palavra.linhas = (int*)realloc(aux->palavra.linhas, aux->palavra.qtdOcorrencias);

        return l;

    }
}

// Função para destruir a lista alocada.
struct Lista *DestroiLista(struct Lista *l){

    struct Lista *aux = l->prox;
    
    while(aux != NULL){

        free(l->palavra.linhas);
        free(l);
        l = aux;
        aux = aux->prox;
    }

    return NULL;

}


// Função que escreve no arquivo.
void EscreverPalavra(FILE *arq, struct Palavra p){

    int tam = strlen(p.letras) + 1;
    fwrite(&tam, sizeof(int), 1, arq);
    fwrite(p.letras, sizeof(char), tam, arq);
    fwrite(&p.qtdOcorrencias, sizeof(int), 1, arq);
    fwrite(p.linhas, sizeof(int), p.qtdOcorrencias, arq);

}

// Função que percorre toda a lista para escrever no arquivo.
void escreveLista(struct Lista *l, int qtd) {

  FILE *arq = fopen("indice.dat", "wb");

  if (arq != NULL) {

    fwrite(&qtd, sizeof(int), 1, arq);

    while (l != NULL) {
      EscreverPalavra(arq, l->palavra);
      l = l->prox;
    }
      fclose(arq);

  }else{
    printf("Erro ao tentar abrir o arquivo.\n");
  }

}

// Função principal que cria um indice para um arquivo de texto.
void criarIndice(){

    char nome_arquivo[20];
    printf("Digite o nome do arquivo texto:\n");
    scanf("%s", nome_arquivo);

    FILE *arq = fopen(nome_arquivo, "r");

    char buffer[1024];
    char *palavra;
    char *delimitadores = " \",.;:[]{}()|-\n";
    int num_linhas, num_palavras = 0;

    if(arq != NULL){

        struct Lista *lista = NULL;

        while(fgets(buffer, sizeof(buffer), arq) != NULL){
            palavra = strtok(buffer, delimitadores);

            while(palavra != NULL){

                lista = Insere(lista, palavra, num_linhas);

                num_palavras++;
                palavra = strtok(NULL, delimitadores);
            }
            num_linhas++;
        }

        escreveLista(lista, num_palavras);
        DestroiLista(lista);
        fclose(arq);
    }else{
        printf("Arquivo não aberto.\n");
    }

}

// Função auxiliar que mostra as linhas em que a palavra aparece.
void mostraLinhas(struct Lista *cont){

    for(int i = 0; i < cont->palavra.qtdOcorrencias; i++)
        printf("[%d] ", cont->palavra.linhas[i]);
    
    printf("\n");

}

// Função que mostra o registro e suas informações.
void mostraRegistro(struct Lista *lista){

    struct Lista *aux = lista;
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    
    while(aux != NULL){

        printf("Numero de caracteres: %d\n", (int)strlen(aux->palavra.letras) + 1);
        printf("Palavra: %s\n", aux->palavra.letras);
        printf("Ocorrências: %d\n", aux->palavra.qtdOcorrencias);
        printf("Linhas: ");
        mostraLinhas(aux);
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

        aux = aux->prox;
    }
}

// Função que lê o arquivo indice.dat e retorna suas informações em um formato de lista encadeada.
struct Lista *lerPalavras(FILE *arq, struct Lista *l, int qtd_palavras){

    printf("Quantidade de palavras no arquivo: %d\n\n", qtd_palavras); 

    while(qtd_palavras != 0){
        int n_caracteres = 0;
        struct Palavra palavra;

        fread(&n_caracteres, sizeof(int), 1, arq);

        fread(palavra.letras, sizeof(char), n_caracteres, arq);
        
        fread(&palavra.qtdOcorrencias, sizeof(int), 1, arq);

        palavra.linhas = (int *)malloc(palavra.qtdOcorrencias * sizeof(int));
        fread(palavra.linhas, sizeof(int), palavra.qtdOcorrencias, arq);
        for (int i = 0; i < palavra.qtdOcorrencias; i++)
            l = Insere(l, palavra.letras, palavra.linhas[i]);
        

        free(palavra.linhas);
        qtd_palavras -= palavra.qtdOcorrencias; // Podemos fazer a interação com qtd_palavras porque o valor original não vai se alterar fora do escopo da função.
    }

    mostraRegistro(l);

    return l;
}

// Função que cria uma lista de palavras com suas informações.
struct Lista *criaLista(FILE *arq){

    struct Lista *lista = NULL;

    int qtd = 0;
    fread(&qtd, sizeof(int), 1, arq);
    lista = lerPalavras(arq, lista, qtd); // Mesmo após o primeiro fread o arquivo é passado para outra função com o cursor na posição atual.


    return lista;
}

// Função que usa de um indice existente para buscar informações a partir de palavras.

void lerIndice(){


    FILE *arq = fopen("indice.dat", "rb");
    char palavra[50];

    if(arq != NULL){

        struct Lista *lista = criaLista(arq), *aux = NULL;
        

        printf("Digite a palavra que deseja buscar:\n");
        scanf("%s", palavra);

        aux = BuscaPalavra(lista, palavra);

        if(aux == NULL){
            printf("Palavra não encontrada.\n");
        }else{
            printf("\nQuantidade de vezes que \"%s\" aparece: %d\n", palavra, aux->palavra.qtdOcorrencias);
            printf("Linhas: ");
            mostraLinhas(aux);

            printf("\n");
        }

        DestroiLista(lista);
        fclose(arq);
    }else{
        printf("Arquivo não aberto.\n");
    }


}

// Função do menu principal.
void menu(){

    int opcao = 0;

    while(opcao != 3){

        printf("[1] - Criar índice\n");
        printf("[2] - Utilizar índice\n");
        printf("[3] - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            
            case 1:
                criarIndice();
                break;

            case 2:
                lerIndice();
                break;

            default:
                break;
        }

    }

}

int main(){
    
    menu();
    return 0;
}
