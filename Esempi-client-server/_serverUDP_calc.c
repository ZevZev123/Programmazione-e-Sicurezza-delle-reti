#include "network.h"
#include <ctype.h>

int main() {
    socketif_t socket = createUDPInterface(35000);
    char request[MTU], result[MTU];
    char hostAddress[MAXADDRESSLEN];
    int port;

    while (true) {
        int a = 0, b = 0, op = -1;
        result[0] = '\0';

        printf("[SERVER] In attesa di richieste...\n");

        UDPReceive(socket, request, MTU, hostAddress, &port);

        printf("[SERVER] Ricevuto da %s:%d -> %s\n", hostAddress, port, request);

        // Parsing: [numero1][operatore][numero2]
        int i = 0;
        while (isdigit(request[i])) {
            a = a * 10 + (request[i++] - '0');
        }

        switch (request[i++]) {
            case '+': op = 0; break;
            case '-': op = 1; break;
            case '*': op = 2; break;
            case '/': op = 3; break;
            default:
                printf("[SERVER] Operatore non valido\n");
                continue;
        }

        while (isdigit(request[i])) {
            b = b * 10 + (request[i++] - '0');
        }

        printf("[SERVER] Operazione: %d %c %d\n", a, request[i - 1], b);

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
        UDPSend(socket, result, strlen(result) + 1, hostAddress, port); // +1 per il terminatore di stringa
    }

    return 0;
}
