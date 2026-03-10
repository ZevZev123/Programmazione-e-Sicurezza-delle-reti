#include "network.h"

int main() {
    printf("[CLIENT] Creo una connessione logica col server\n");
    connection_t connection = createTCPConnection("127.0.0.1", 35000);

    char request[MTU], response[MTU];

    // [numero1]
    printf("[CLIENT] Inserisci primo numero: ");
    if (scanf("%s", request) != 1) {
        fprintf(stderr, "[CLIENT] Errore input\n");
        return -1;
    }

    if (TCPSend(connection, request, strlen(request) + 1) < 0) {
        perror("[CLIENT] Errore nell'invio");
        return -1;
    }

    // [operatore]
    printf("[CLIENT] Inserisci operazione: ");
    if (scanf("%s", request) != 1) {
        fprintf(stderr, "[CLIENT] Errore input\n");
        return -1;
    }
    
    if (TCPSend(connection, request, strlen(request) + 1) < 0) {
        perror("[CLIENT] Errore nell'invio");
        return -1;
    }

    // [numero2]
    printf("[CLIENT] Inserisci secondo numero: ");
    if (scanf("%s", request) != 1) {
        fprintf(stderr, "[CLIENT] Errore input\n");
        return -1;
    }

    if (TCPSend(connection, request, strlen(request) + 1) < 0) {
        perror("[CLIENT] Errore nell'invio");
        return -1;
    }
    
    printf("[CLIENT] Operazione inviata: %s\n", request);
    printf("[CLIENT] In attesa di risposta dal server...\n");

    if (TCPReceive(connection, response, sizeof(response)) < 0) {
        perror("[CLIENT] Errore nella ricezione");
        return -1;
    }

    printf("[CLIENT] Risultato: %s\n", response);

    return 0;
}
