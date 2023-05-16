
typedef struct reservation Reservation;

typedef struct ReservationSystem;

void initializeReservationSystem(ReservationSystem *system);

int checkAvailability( Reservation *reservationList, int tableNumber);

void makeReservation(ReservationSystem *system);

void displayReservations( Reservation *reservationList);

void saveReservationsToFile(ReservationSystem *system, const char *filename);

void loadReservationsFromFile(ReservationSystem *system, const char *filename);

void cancelReservation(ReservationSystem *system);

void freeReservationList( Reservation *reservationList);

void freeReservationSystem(ReservationSystem *system);

