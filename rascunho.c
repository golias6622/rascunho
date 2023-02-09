#include<stdio.h>
#include<stdlib.h>

typedef struct funcionario{
    char nome[50];
    float salario;
    int id;
    char cargo[50];
}Funcionario;


void preencher(Funcionario *dados, int qnt){
    int i;
    for (i=0;i<qnt; i++){
        printf("digite o nome do %d funcionario: ", i+1);
        scanf(" %[^\n]s", dados[i].nome );
        printf("digite salario do funcionario ");
        scanf(" %f", &dados[i].salario);
        printf("digite o cargo do funcionario: ");
        scanf(" %[^\n]s", dados[i].cargo);
        printf("digite o indentificador do funcionario: ");
        scanf("%d", &dados[i].id);
    }
}

void imprime(Funcionario *imprime, int qnt){
    int i;
    for(i=0;i<qnt;i++){
        printf("\no nome do  %d funcionario: %s\n",i+1, imprime[i].nome );
        printf("os dados do %d funcionario: %s\n",i+1,imprime[i].cargo );
        printf("o cargo do %d funcionario: %f\n",i+1,imprime[i].salario );
        printf("o identificador do %d funcionario: %d\n",i+1,imprime[i].id );
    }
}

int main(){
    int qnt_funcionarios;
    printf ("informe a quantidade de funcionarios: ");
    scanf("%d", &qnt_funcionarios);
    Funcionario *dados_funcionarios=(Funcionario*)malloc(qnt_funcionarios*sizeof(Funcionario));
    preencher(dados_funcionarios, qnt_funcionarios);
    imprime(dados_funcionarios, qnt_funcionarios);


return 0;
}