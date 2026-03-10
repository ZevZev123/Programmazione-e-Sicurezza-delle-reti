#include "network.h"

int main(void) {
    connection_t connection;
    
    printf("[CLIENT] Creo una connessione logica col server\n");
    connection = createTCPConnection("127.0.0.1", 35000);
    
    if (connection < 0) {
        printf("[CLIENT] Errore nella connessione al server: %i\n", connection);
        return -1;
    } else {
        int request;
        printf("Inserisci un numero intero:\n");
        do {
            scanf("%d", &request);
            TCPSend(connection, &request, sizeof(request));
        } while (request != 0);
        
        int response;
        TCPReceive(connection, &response, sizeof(response));

        printf("[CLIENT] Ho ricevuto somma %d\n", response);
        closeConnection(connection);
    }
}
