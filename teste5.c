#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TABLES 10
#define MAX_CUSTOMERS_PER_TABLE 4

struct Reservation {
    char name[50];
    int tableNumber;
    int numberOfCustomers;
    struct Reservation* next;
};

typedef struct {
    struct Reservation* reservationList;
} ReservationSystem;

void initializeReservationSystem(ReservationSystem* system) {
    system->reservationList = NULL;
}

int checkAvailability(struct Reservation* reservationList, int tableNumber) {
    struct Reservation* current = reservationList;
    while (current != NULL) {
        if (current->tableNumber == tableNumber) {
            return 0; // mesa não disponível
        }
        current = current->next;
    }
    return 1; // mesa disponível
}

void makeReservation(ReservationSystem* system) {
    int tableAvailable = 0;
    int i;
    for (i = 1; i <= MAX_TABLES; i++) {
        if (checkAvailability(system->reservationList, i)) {
            tableAvailable = 1;
            break;
        }
    }
    if (!tableAvailable) {
        printf("\nDesculpe, não há mesas disponíveis.\n");
        return;
    }

    struct Reservation* newReservation = (struct Reservation*)malloc(sizeof(struct Reservation));
    printf("\nNome do cliente: ");
    scanf("%s", newReservation->name);
    printf("Numero de pessoas: ");
    scanf("%d", &(newReservation->numberOfCustomers));

    printf("\nMesas disponíveis:\n");
    for (i = 1; i <= MAX_TABLES; i++) {
        if (checkAvailability(system->reservationList, i)) {
            printf("%d\n", i);
        }
    }
    printf("Selecione uma mesa: ");
    scanf("%d", &(newReservation->tableNumber));

    newReservation->next = NULL;

    if (system->reservationList == NULL) {
        system->reservationList = newReservation;
    } else {
        struct Reservation* current = system->reservationList;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newReservation;
    }

    printf("\nReserva feita com sucesso!\n");
}

void displayReservations(struct Reservation* reservationList) {
    printf("\nReservas:\n");
    int i = 1;
    struct Reservation* current = reservationList;
    while (current != NULL) {
        printf("%d. %s - Mesa %d (%d pessoas)\n", i, current->name, current->tableNumber, current->numberOfCustomers);
        current = current->next;
        i++;
    }
}

void saveReservationsToFile(ReservationSystem* system, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }

    struct Reservation* current = system->reservationList;
    while (current != NULL) {
        fprintf(file, "%s;%d;%d\n", current->name, current->tableNumber, current->numberOfCustomers);
        current = current->next;
    }

    fclose(file);
    printf("\nReservas salvas no arquivo com sucesso!\n");
}

void loadReservationsFromFile(ReservationSystem* system, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }

    // Limpa a lista de reservas existente
    struct Reservation* current = system->reservationList;
    while (current != NULL) {
        struct Reservation* next = current->next;
        free(current);
        current = next;
    }
    system->reservationList = NULL;

    // Lê as reservas do arquivo e adiciona à lista
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        struct Reservation* newReservation = (struct Reservation*)malloc(sizeof(struct Reservation));

        char* token = strtok(line, ";");
        strcpy(newReservation->name, token);

        token = strtok(NULL, ";");
        newReservation->tableNumber = atoi(token);

        token = strtok(NULL, "\n");
        newReservation->numberOfCustomers = atoi(token);

        newReservation->next = NULL;

        if (system->reservationList == NULL) {
            system->reservationList = newReservation;
        } else {
            current = system->reservationList;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newReservation;
        }
    }

    fclose(file);
    printf("\nReservas carregadas do arquivo com sucesso!\n");
}

void cancelReservation(ReservationSystem* system) {
    printf("\nDigite o nome do cliente para cancelar a reserva: ");
    char cancelName[50];
    scanf("%s", cancelName);

    struct Reservation* current = system->reservationList;
    struct Reservation* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, cancelName) == 0) {
            if (prev == NULL) {
                system->reservationList = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("\nReserva cancelada com sucesso!\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("\nReserva não encontrada para o cliente especificado.\n");
}

void freeReservationList(struct Reservation* reservationList) {
    struct Reservation* current = reservationList;
    while (current != NULL) {
        struct Reservation* next = current->next;
        free(current);
        current = next;
    }
}

void freeReservationSystem(ReservationSystem* system) {
    freeReservationList(system->reservationList);
    system->reservationList = NULL;
}

int main() {
    ReservationSystem system;
    initializeReservationSystem(&system);

    int choice;
    do {
        printf("\n===== Sistema de Reservas do Restaurante =====\n");
        printf("1. Verificar disponibilidade de mesa\n");
        printf("2. Fazer uma reserva\n");
        printf("3. Ver reservas\n");
        printf("4. Cancelar uma reserva\n");
        printf("5. Salvar reservas em arquivo\n");
        printf("6. Carregar reservas do arquivo\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao:\n\n\n ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Verificar disponibilidade de mesa
                printf("\nNumero da mesa: ");
                int tableNumber;
                scanf("%d", &tableNumber);
                if (checkAvailability(system.reservationList, tableNumber)) {
                    printf("\nMesa %d está disponível.\n", tableNumber);
                } else {
                    printf("\nMesa %d não está disponível.\n", tableNumber);
                }
                break;
            case 2:
                // Fazer uma reserva
                makeReservation(&system);
                break;
            case 3:
                // Ver reservas
                displayReservations(system.reservationList);
                break;
            case 4:
                // Cancelar uma reserva
                cancelReservation(&system);
                break;
            case 5:
                // Salvar reservas em arquivo
                saveReservationsToFile(&system, "reservas.txt");
                break;
            case 6:
                // Carregar reservas do arquivo
                loadReservationsFromFile(&system, "reservas.txt");
                break;
            case 7:
                // Sair
                printf("\nSaindo do programa.\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
                break;
        }
    } while (choice != 7);

    // Libera a memória alocada para as reservas
    freeReservationSystem(&system);

    return 0;
}