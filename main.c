#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 93

typedef struct aluno {
    char nome[100];
    float nota1;
    float nota2;
    float media;
    char situacao[100];
} Aluno;

void lerArquivo(char *nomeArquivo, Aluno *listaAlunos);
void determinarMedia(Aluno *listaAlunos, int tamanhoArray);
void determinarSituacao(Aluno *listaAlunos, int tamanhoArray);
void gerarArquivo(char *nomeArquivo, Aluno *listaAlunos, int tamanhoArray);

int main() {
    Aluno listaAlunos[MAX_LEN];
    int tamanhoArray = sizeof(listaAlunos) / sizeof(listaAlunos[0]);

    lerArquivo("DadosEntrada.csv", listaAlunos);
    determinarMedia(listaAlunos, tamanhoArray);
    determinarSituacao(listaAlunos, tamanhoArray);
    gerarArquivo("SituacaoFinal.cvs", listaAlunos, tamanhoArray);


    return 0;
}

void gerarArquivo(char *nomeArquivo, Aluno *listaAlunos, int tamanhoArray){
    FILE *f;
    f = fopen(nomeArquivo, "w");

    if(f == NULL){
        printf("O arquivo não pode ser aberto!\n");
        exit(1);
    }

    for (int i = 0; i < tamanhoArray; ++i){
        fprintf(f,"%s %.2f %s", listaAlunos[i].nome, listaAlunos[i].media, listaAlunos[i].situacao);
        fprintf(f,"\n");
    }
    fclose(f);
    printf("Arquivo gerado com sucesso! - %s\n", nomeArquivo);

}

void determinarMedia(Aluno *listaAlunos, int tamanhoArray){
    for (int i = 0; i < tamanhoArray; ++i) {
        listaAlunos[i].media = (listaAlunos[i].nota1 + listaAlunos[i].nota2) / 2;
    }
    printf("Determiando media dos alunos!\n");

}

void determinarSituacao(Aluno *listaAlunos, int tamanhoArray){
    for (int i = 0; i < tamanhoArray; ++i) {
        if(listaAlunos[i].media >= 7) strcpy(listaAlunos[i].situacao, "APROVADO");
        else strcpy(listaAlunos[i].situacao, "REPROVADO");
    }
    printf("Determiando situacao dos alunos!\n");
}

//Essa função ler o arquivo
void lerArquivo(char *nomeArquivo, Aluno *listaAlunos) {
    FILE *fp;
    int numeroLinha = 0;
    char linha[MAX_LEN];
    char *token;

    fp = fopen(nomeArquivo, "r");

    if (fp == NULL) {
        printf("O arquivo não pode ser aberto!\n");
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
    printf("Lendo arquivo!\n");
    fclose(fp);
}
