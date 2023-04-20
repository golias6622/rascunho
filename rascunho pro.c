#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct reserva {
    char nome[50];
    char telefone[20];
    char email[50];
    char data[20];
    char hora[20];
    int num_pessoas;
};

void fazer_reserva(struct reserva r) {
    // Aqui você pode adicionar a lógica para fazer a reserva, como armazenar os dados em um arquivo ou banco de dados.
    printf("Reserva feita para:\n");
    printf("Nome: %s\n", r.nome);
    printf("Telefone: %s\n", r.telefone);
    printf("E-mail: %s\n", r.email);
    printf("Data: %s\n", r.data);
    printf("Hora: %s\n", r.hora);
    printf("Número de pessoas: %d\n", r.num_pessoas);
}

int main() {
    struct reserva r;

    printf("Digite o seu nome: ");
    scanf("%s", r.nome);

    printf("Digite o seu telefone: ");
    scanf("%s", r.telefone);

    printf("Digite o seu e-mail: ");
    scanf("%s", r.email);

    printf("Digite a data da reserva (dd/mm/aaaa): ");
    scanf("%s", r.data);

    printf("Digite a hora da reserva (hh:mm): ");
    scanf("%s", r.hora);

    printf("Digite o número de pessoas: ");
    scanf("%d", &r.num_pessoas);

    fazer_reserva(r);

    return 0;
}