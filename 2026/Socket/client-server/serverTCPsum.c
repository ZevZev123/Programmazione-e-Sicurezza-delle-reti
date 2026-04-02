#include "network.h"

int main(void) {
    int request, response;
    socketif_t socket;
    connection_t connection;
    
    socket = createTCPServer(35000);
    if (socket < 0){
        printf("[SERVER] Errore di creazione del socket: %i\n", socket);
    }
    else
    {
        while (true){
            response = 0;
            printf("[SERVER] Sono in attesa di richieste di connessione da qualche client\n");    
            connection = acceptConnection(socket);
            printf("[SERVER] Connessione instaurata\n");
            while (true){
                TCPReceive(connection, &request, sizeof(request));
                printf("response = %d + %d\n", response, request);
                if (request == 0) {
                    printf("Messaggio di terminazione ricevuto\n");
                    break;
                }
                response += request;
            }
            printf("Chiusura della connessione\n");
            TCPSend(connection, &response, sizeof(response));
            closeConnection(connection);
        }
    }
}

