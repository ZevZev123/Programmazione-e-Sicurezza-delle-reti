#include "network.h"

int main() {
    socketif_t socket = createUDPInterface(20000);
    if (socket < 0) {
        perror("[CLIENT] Errore creazione socket");
        return -1;
    }

    char request[MTU], response[MTU];
    char hostAddress[MAXADDRESSLEN];
    int port;

    printf("[CLIENT] Inserisci operazione (es. 12+34): ");
    if (scanf("%s", request) != 1) {
        fprintf(stderr, "[CLIENT] Errore input\n");
        return -1;
    }

    if (UDPSend(socket, request, strlen(request) + 1, "127.0.0.1", 35000) < 0) {
        perror("[CLIENT] Errore nell'invio");
        return -1;
    }
    
    printf("[CLIENT] In attesa di risposta dal server...\n");

    if (UDPReceive(socket, response, sizeof(response), hostAddress, &port) < 0) {
        perror("[CLIENT] Errore nella ricezione");
        return -1;
    }

    printf("[CLIENT] Risposta ricevuta da %s:%d\n", hostAddress, port);
    printf("[CLIENT] Risultato: %s\n", response);

    return 0;
}
