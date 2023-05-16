#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TABLES 10
#define MAX_CUSTOMERS_PER_TABLE 4

typedef struct reservation
{
    char name[50];
    int tableNumber;
    int numberOfCustomers;
    struct Reservation *next;
}Reservation;

typedef struct
{
    struct Reservation *reservationList;
} ReservationSystem;

void initializeReservationSystem(ReservationSystem *system)
{
    system->reservationList = NULL;
}

int checkAvailability(Reservation *reservationList, int tableNumber)
{
    Reservation *current = reservationList;
    while (current != NULL)
    {
        if (current->tableNumber == tableNumber)
        {
            return 0; // mesa não disponível
        }
        current = current->next;
    }
    return 1; // mesa disponível
}

void makeReservation(ReservationSystem *system)
{
    int tableAvailable = 0;
    int i;
    for (i = 1; i <= MAX_TABLES; i++)
    {
        if (checkAvailability(system->reservationList, i))
        {
            tableAvailable = 1;
            break;
        }
    }
    if (!tableAvailable)
    {
        printf("\nDesculpe, nao ha mesas disponiveis.\n");
        return;
    }

     Reservation *newReservation = ( Reservation *)malloc(sizeof(  Reservation));
    printf("\nNome do cliente: ");
    scanf("%s", newReservation->name);
    printf("Numero de pessoas: ");
    scanf("%d", &(newReservation->numberOfCustomers));

    printf("\nMesas disponíveis:\n");
    for (i = 1; i <= MAX_TABLES; i++)
    {
        if (checkAvailability(system->reservationList, i))
        {
            printf("%d\n", i);
        }
    }
    printf("Selecione uma mesa: ");
    scanf("%d", &(newReservation->tableNumber));

    newReservation->next = NULL;

    if (system->reservationList == NULL)
    {
        system->reservationList = newReservation;
    }
    else
    {
        Reservation *current = system->reservationList;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newReservation;
    }

    printf("\nReserva feita com sucesso!\n");
}

void displayReservations(Reservation *reservationList)
{
    printf("\nReservas:\n");
    int i = 1;
    Reservation *current = reservationList;
    while (current != NULL)
    {
        printf("%d. %s - Mesa %d (%d pessoas)\n", i, current->name, current->tableNumber, current->numberOfCustomers);
        current = current->next;
        i++;
    }
}

void saveReservationsToFile(ReservationSystem *system, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }

    Reservation *current = system->reservationList;
    while (current != NULL)
    {
        fprintf(file, "%s;%d;%d\n", current->name, current->tableNumber, current->numberOfCustomers);
        current = current->next;
    }

    fclose(file);
    printf("\nReservas salvas no arquivo com sucesso!\n");
}

void loadReservationsFromFile(ReservationSystem *system, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n");
        return;
    }

    // Limpa a lista de reservas existente
    Reservation *current = system->reservationList;
    while (current != NULL)
    {
    Reservation *next = current->next;
        free(current);
        current = next;
    }
    system->reservationList = NULL;

    // Lê as reservas do arquivo e adiciona à lista
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        Reservation *newReservation = ( Reservation *)malloc(sizeof( Reservation));

        char *token = strtok(line, ";");
        strcpy(newReservation->name, token);

        token = strtok(NULL, ";");
        newReservation->tableNumber = atoi(token);

        token = strtok(NULL, "\n");
        newReservation->numberOfCustomers = atoi(token);

        newReservation->next = NULL;

        if (system->reservationList == NULL)
        {
            system->reservationList = newReservation;
        }
        else
        {
            current = system->reservationList;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newReservation;
        }
    }

    fclose(file);
    printf("\nReservas carregadas do arquivo com sucesso!\n");
}

void cancelReservation(ReservationSystem *system)
{
    printf("\nDigite o nome do cliente para cancelar a reserva: ");
    char cancelName[50];
    scanf("%s", cancelName);

     Reservation *current = system->reservationList;
     Reservation *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->name, cancelName) == 0)
        {
            if (prev == NULL)
            {
                system->reservationList = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            printf("\nReserva cancelada com sucesso!\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("\nReserva nao encontrada para o cliente especificado.\n");
}

void freeReservationList(Reservation *reservationList)
{
    Reservation *current = reservationList;
    while (current != NULL)
    {
        Reservation *next = current->next;
        free(current);
        current = next;
    }
}

void freeReservationSystem(ReservationSystem *system)
{
    freeReservationList(system->reservationList);
    system->reservationList = NULL;
}

int main()
{
    ReservationSystem system;
    initializeReservationSystem(&system);

    // Carregar as reservas do arquivo
    loadReservationsFromFile(&system, "reservas.txt");

    int choice;
    do
    {
        printf("\n===== Sistema de Reservas do Restaurante =====\n");
        printf("1. Verificar disponibilidade de mesa\n");
        printf("2. Fazer uma reserva\n");
        printf("3. Ver reservas\n");
        printf("4. Cancelar uma reserva\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao:\n\n\n ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // Verificar
            printf("\nNumero da mesa: ");
            int tableNumber;
            scanf("%d", &tableNumber);
            if (checkAvailability(system.reservationList, tableNumber))
            {
                printf("\nMesa %d esta disponivel.\n", tableNumber);
            }
            else
            {
                printf("\nMesa %d não esta disponivel.\n", tableNumber);
            }
            break;
        case 2:
            // Fazer uma reserva
            makeReservation(&system);
            saveReservationsToFile(&system, "reservas.txt");
            break;
        case 3:
            // Ver reservas
            displayReservations(system.reservationList);
            break;
        case 4:
            // Cancelar uma reserva
            cancelReservation(&system);
            saveReservationsToFile(&system, "reservas.txt");
            break;
        case 5:
            // Sair
            printf("\nSaindo do programa.\n");
            break;
        default:
            printf("\nOpcao invalida. Tente novamente.\n");
            break;
        }
    } while (choice != 5);

    // Salvar as reservas no arquivo antes de encerrar o programa
    saveReservationsToFile(&system, "reservas.txt");

    // Libera a memória alocada para as reservas
    freeReservationSystem(&system);

    return 0;
}