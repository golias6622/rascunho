#include <stdio.h>
#include <string.h>

// Definir as constantes para o numero maximo de mesas e o numero maximo de clientes por mesa
#define MAX_TABLES 10
#define MAX_CUSTOMERS_PER_TABLE 4

// Estrutura para armazenar as informa��es de uma reserva
struct Reservation {
    char name[50];
    int tableNumber;
    int numberOfCustomers;
};

// Variveis globais para armazenar as reservas
struct Reservation reservations[MAX_TABLES];
int numberOfReservations = 0;

// Fun�o para exibir o menu
void displayMenu() {
    printf("\n===============================\n");
    printf("Restaurante XYZ - Sistema de Reserva\n");
    printf("===============================\n");
    printf("1. Verificar disponibilidade de mesa\n");
    printf("2. Fazer uma reserva\n");
    printf("3. Ver reservas\n");
    printf("4. Cancelar uma reserva\n");
    printf("5. Sair\n");
    printf("===============================\n");
}

// Fun��o para verificar se uma mesa esta disponivel
int checkAvailability(int tableNumber) {
    // Percorre as reservas existentes e verifica se a mesa esta ocupada
    int i;
    for ( i = 0; i < numberOfReservations; i++) {
        if (reservations[i].tableNumber == tableNumber) {
            return 0; // mesa n�o disponivel
        }
    }
    return 1; // mesa disponivel
}

// Função para fazer uma reserva
void makeReservation() {
    // Verifica se há mesas disponíveis
    int tableAvailable = 0;
    int i;
    for ( i = 1; i <= MAX_TABLES; i++) {
        if (checkAvailability(i)) {
            tableAvailable = 1;
            break;
        }
    }
    if (!tableAvailable) {
        printf("\nDesculpe, não há mesas disponíveis.\n");
        return;
    }

    // Obtém as informações do cliente
    struct Reservation newReservation;
    printf("\nNome do cliente: ");
    scanf("%s", newReservation.name);
    printf("Número de pessoas: ");
    scanf("%d", &newReservation.numberOfCustomers);

    // Verifica as mesas disponíveis e permite que o usuário selecione uma
    printf("\nMesas disponíveis:\n");
    
    for ( i = 1; i <= MAX_TABLES; i++) {
        if (checkAvailability(i)) {
            printf("%d\n", i);
        }
    }
    printf("Selecione uma mesa: ");
    scanf("%d", &newReservation.tableNumber);

    // Adiciona a reserva à lista de reservas
    reservations[numberOfReservations] = newReservation;
    numberOfReservations++;

    printf("\nReserva feita com sucesso!\n");
}

// Função para exibir as reservas
void displayReservations() {
    printf("\nReservas:\n");
    int i;
    for ( i = 0; i < numberOfReservations; i++) {
        printf("%d. %s - Mesa %d (%d pessoas)\n", i+1, reservations[i].name, reservations[i].tableNumber, reservations[i].numberOfCustomers);
    }
}

// Função para cancelar uma reserva
void cancelReservation() {
    // Exibe as reservas existentes para que o usuário selecione uma para cancelar
    displayReservations();
    if (numberOfReservations == 0) {
        printf("\nNão há reservas para cancelar.\n");}
        
         else {
    int reservationNumber;
    printf("\nSelecione o número da reserva que deseja cancelar: ");
    scanf("%d", &reservationNumber);

    // Remove a reserva selecionada da lista de reservas
    int i;
    for ( i = reservationNumber-1; i < numberOfReservations-1; i++) {
        reservations[i] = reservations[i+1];
    }
    numberOfReservations--;

    printf("\nReserva cancelada com sucesso!\n");
}
}

int main() {
int choice;
do {
displayMenu();
printf("Escolha uma opção: ");
scanf("%d", &choice);



    switch (choice) {
        case 1:
            // Verificar disponibilidade de mesa
            printf("\nNúmero da mesa: ");
            int tableNumber;
            scanf("%d", &tableNumber);
            if (checkAvailability(tableNumber)) {
                printf("\nMesa %d está disponível.\n", tableNumber);
            } else {
                printf("\nMesa %d não está disponível.\n", tableNumber);
            }
            break;
        case 2:
            // Fazer uma reserva
            makeReservation();
            break;
        case 3:
            // Ver reservas
            displayReservations();
            break;
        case 4:
            // Cancelar uma reserva
            cancelReservation();
            break;
        case 5:
            // Sair
            printf("\nObrigado por usar o Sistema de Reserva do Restaurante XYZ!\n");
            break;
        default:
            printf("\nOpção inválida. Tente novamente.\n");
            break;
    }
} while (choice != 5);

return 0;
}
