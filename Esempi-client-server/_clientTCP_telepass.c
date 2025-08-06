#include "network.h"

int main() {
    printf("[CLIENT] Creo una connessione logica col server\n");
    connection_t connection = createTCPConnection("127.0.0.1", 35000);
    if (connection < 0) {
        perror("[CLIENT] Errore creazione connessione");
        return -1;
    }

    char request[MTU], response[MTU];
    
    printf("[CLIENT] Inserisci le targe che passano con il telepass (exit per uscire):\n");
    
    while (true) {
        printf("> ");
        if (scanf("%s", request) != 1 || strcmp(request, "exit") == 0) break;
        

        if (TCPSend(connection, request, strlen(request) + 1) < 0) {
            perror("[CLIENT] Errore nell'invio");
            return -1;
        }

        if (TCPReceive(connection, response, sizeof(response)) < 0) {
            perror("[CLIENT] Errore nella ricezione");
            return -1;
        }

        printf("[CLIENT] La targa %s e' passata %s volta/e\n", request, response);
    }

    closeConnection(connection);
    return 0;
}