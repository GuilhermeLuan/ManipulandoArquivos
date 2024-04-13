#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 93

typedef struct aluno {
    char nome[100];
    float nota1;
    float nota2;
    float media;
} Aluno;

void lerArquivo(char *nomeArquivo, Aluno *listaAlunos);
void determinarMedia(Aluno *listaAlunos, int tamanhoArray);

int main() {
    Aluno listaAlunos[MAX_LEN];
    int tamanhoArray = sizeof(listaAlunos) / sizeof(listaAlunos[0]);

    lerArquivo("DadosEntrada.csv", listaAlunos);
    determinarMedia(listaAlunos, tamanhoArray);

    for (int i = 0; i < tamanhoArray; ++i) {
        printf("%s\n Media: %.2f\n", listaAlunos[i].nome, listaAlunos[i].media);
    }

    return 0;
}

void determinarMedia(Aluno *listaAlunos, int tamanhoArray){
    for (int i = 0; i < tamanhoArray; ++i) {
        listaAlunos[i].media = (listaAlunos[i].nota1 + listaAlunos[i].nota2) / 2;
    }
}

void lerArquivo(char *nomeArquivo, Aluno *listaAlunos) {
    FILE *fp;
    int numeroLinha = 0;
    char linha[MAX_LEN];
    char *token;

    fp = fopen(nomeArquivo, "r");

    if (fp == NULL) {
        printf("O arquivo não pode ser aberto!");
        exit(1);
    }

    while (fgets(linha, MAX_LEN, fp) != NULL) {
        if (numeroLinha > 0) {
            token = strtok(linha, ",");
            strcpy(listaAlunos[numeroLinha - 1].nome, token);

            token = strtok(NULL, ",");
            token = strtok(NULL, ",");

            token = strtok(NULL, ",");
            listaAlunos[numeroLinha - 1].nota1 = atof(token);

            token = strtok(NULL, ",");
            listaAlunos[numeroLinha - 1].nota2 = atof(token);
        }
        numeroLinha++;
    }

    fclose(fp);
}
