#include "network.h"

#define MAX_PLATES 1000

typedef struct {
    char plate[20];
    int count;
} plate_entry_t;

plate_entry_t *dict = NULL;
int num_entries = 0;

int find_plate_index(char *plate) {
    for (int i = 0; i < num_entries; i++) {
        if (strcmp(dict[i].plate, plate) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    socketif_t socket = createTCPServer(35000);
    if (socket < 0) {
        perror("[SERVER] Errore creazione socket");
        return -1;
    }
    char request[MTU], result[MTU];
    connection_t connection;

    while (true) {
        printf("[SERVER] In attesa di richieste...\n");
        connection = acceptConnection(socket);
        if (connection < 0) {
            perror("[SERVER] Errore accettazione connessione");
            continue;
        }
        printf("[SERVER] Connessione accettata\n");

        while (TCPReceive(connection, request, MTU) > 0) {
            printf("[SERVER] Targa ricevuta -> %s\n", request);

            int index = find_plate_index(request);
            if (index >= 0) {
                dict[index].count++;
            } else {
                dict = realloc(dict, (num_entries + 1) * sizeof(plate_entry_t));
                strncpy(dict[num_entries].plate, request, sizeof(dict[num_entries].plate) - 1);
                dict[num_entries].plate[sizeof(dict[num_entries].plate) - 1] = '\0';
                dict[num_entries].count = 1;
                index = num_entries;
                num_entries++;
            }

            // Process the request (this is a placeholder for actual logic)
            snprintf(result, sizeof(result), "%d", dict[index].count);

            printf("[SERVER] Invio il risultato: %s\n", result);
            TCPSend(connection, result, strlen(result) + 1);
        }

        printf("[SERVER] Connessione chiusa\n");
        closeConnection(connection);
    }

    free(dict);
    return 0;
}