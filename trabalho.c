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

        aux->palavra.qtdOcorrencias++;
        aux->palavra.linhas = realloc(aux->palavra.linhas, aux->palavra.qtdOcorrencias - 1);
        aux->palavra.linhas[aux->palavra.qtdOcorrencias - 1] = linha;

        return l;

    }
}

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


void EscreverPalavra(FILE *arq, struct Palavra p){

    int tam = strlen(p.letras) + 1;
    fwrite(&tam, sizeof(int), 1, arq);
    fwrite(p.letras, sizeof(char), tam, arq);
    fwrite(&p.qtdOcorrencias, sizeof(int), 1, arq);
    fwrite(p.linhas, sizeof(int), p.qtdOcorrencias, arq);

}

void escrever(struct Lista *l, int qtd){

    FILE *arq = fopen("indice.dat", "wb");

    fwrite(&qtd, sizeof(int), 1, arq);

    while(l != NULL){
        EscreverPalavra(arq, l->palavra);
        l = l->prox;
    }
}

void criarIndice(){


    FILE *arq = fopen("exemplo.txt", "r");
    char buffer[1024];
    char *palavra;
    char *delimitadores = " \",.;:[]{}()|-\n";
    int num_linhas, num_palavras = 0;


    struct Lista *lista = NULL;

    while(fgets(buffer, sizeof(buffer), arq) != NULL){
        palavra = strtok(buffer, delimitadores);

        while(palavra != NULL){
            /*printf("%s\n", palavra);*/

            lista = Insere(lista, palavra, num_linhas);

            num_palavras++;
            palavra = strtok(NULL, delimitadores);
        }
        num_linhas++;
    }

    escrever(lista, num_palavras);

}


int main(){
    criarIndice();
    return 0;
}
