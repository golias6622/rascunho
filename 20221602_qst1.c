/*Escreva um programa que implementa uma struct Pessoa com os campos nome, idade e gˆenero. O
gˆenero deve ser armazenado como um enum com os valores MASCULINO e FEMININO. O programa
deve ler os dados de uma pessoa e imprimir os dados da pessoa..
*/

#include<stdio.h>   
#include<stdlib.h>

int main(){
    
    typedef enum genero{
        MASCULINO,
        FEMININO
    }Genero;

    typedef struct pessoa{
        char nome[50];
        int idade;
        Genero genero;
    }Pessoa;

    Pessoa pessoa;
    int genero = 0;

    printf("digite seu nome: ");
    scanf(" %[^\n]s", &pessoa.nome);
    printf("digite sua idade: ");
    scanf("%d", &pessoa.idade);
    printf("digite seu genero: (0 para masculino e 1 para feminino)");
    scanf("%d", &pessoa.genero);

    if (pessoa.genero == 0){
        printf("nome: %s| idade: %d | genero: masculino", pessoa.nome, pessoa.idade);
    }
    else{
        printf("nome: %s | idade %d | genero: feminino", pessoa.nome, pessoa.idade);
    }

    return 0;
}


    
