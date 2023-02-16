/*Escreva um programa que implementa uma struct Produto com os campos nome, pre¸co e tipo. O
tipo deve ser armazenado como uma union que armazena um dos tipos: ALIMENTO, BEBIDA ou
ELETRONICO. O programa deve ler os dados de um produto e imprimir os dados do produto.*/

#include<stdio.h>
#include<stdlib.h>

typedef union tipo{
   char ALIMENTO[10];
    char BEBIDA[10];
    char ELETRONICO[10];
}Tipo;

typedef struct produto{
    char nome[50];
    float preco;
    Tipo tipo
}Produto;

int main(){
    Produto produto;
    
    printf("digite o nome do produto: ");
    scanf(" %[^\n]s", produto.nome);
    printf("digite o preco do produto: ");
    scanf("%f", &produto.preco);
    printf("digite o tipo do produto: ");
    scanf(" %[^\n]s ", produto.tipo.ALIMENTO);

    printf("\nnome: %s | preco: %.2f | tipo: %s ", produto.nome, produto.preco, produto.tipo.ALIMENTO);

return 0;
}

