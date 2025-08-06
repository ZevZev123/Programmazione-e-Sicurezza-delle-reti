#include "network.h"
#include <ctype.h>

int main() {
    socketif_t socket = createTCPServer(35000);
    if (socket < 0) {
        perror("[SERVER] Errore creazione socket");
        return -1;
    }
    connection_t connection;
    char request[MTU], result[MTU];
    char symbol[4] = {'+', '-', '*', '/'};

    while (true) {
        printf("[SERVER] In attesa di richieste...\n");
        connection = acceptConnection(socket);
        printf("[SERVER] Connessione accettata\n");
        int a = 0, b = 0, op = -1;
        result[0] = '\0';

        TCPReceive(connection, request, MTU);

        printf("[SERVER] Ricevuto contenuto -> %s\n", request);
        
        // Parsing: [numero1][operatore][numero2]
        int i = 0;
        while (isdigit(request[i])) {
            a = a * 10 + (request[i++] - '0');
        }
        
        TCPReceive(connection, request, MTU);
        
        printf("[SERVER] Ricevuto contenuto -> %s\n", request);
        
        switch (request[0]) {
            case '+': op = 0; break;
            case '-': op = 1; break;
            case '*': op = 2; break;
            case '/': op = 3; break;
            default:
            printf("[SERVER] Operatore non valido\n");
            continue;
        }
        
        TCPReceive(connection, request, MTU);
        
        printf("[SERVER] Ricevuto contenuto -> %s\n", request);
        
        i = 0;
        while (isdigit(request[i])) {
            b = b * 10 + (request[i++] - '0');
        }

        printf("[SERVER] Operazione: %d %c %d\n", a, symbol[op], b);

        // Calcolo
        switch (op) {
            case 0: snprintf(result, sizeof(result), "%d", a + b); break;
            case 1: snprintf(result, sizeof(result), "%d", a - b); break;
            case 2: snprintf(result, sizeof(result), "%d", a * b); break;
            case 3:
                if (b == 0) {
                    snprintf(result, sizeof(result), "Errore: divisione per zero");
                    printf("[SERVER] Divisione per zero!\n");
                } else {
                    snprintf(result, sizeof(result), "%d", a / b);
                }
                break;
        }

        printf("[SERVER] Invio il risultato: %s\n\n", result);
        TCPSend(connection, result, strlen(result) + 1);
        closeConnection(connection);
    }

    closeConnection(socket);
    return 0;
}
