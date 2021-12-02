#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

    FILE *arq = fopen("exemplo.txt", "r");

    char buffer[1024] ;
    char *tk;


    while(fgets(buffer, sizeof(buffer), arq) != NULL){
        tk = strtok(buffer, " \"(\n,.-)");
        while(tk != NULL){
            printf("%s\n", tk);
            tk = strtok(NULL, " \"()\n,.-");
        }

    }

    return 0;
}
