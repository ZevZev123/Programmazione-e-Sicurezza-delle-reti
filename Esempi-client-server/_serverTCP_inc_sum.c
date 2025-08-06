#include "network.h"

int main(void) {
    int request;
    socketif_t socket;
    connection_t connection;
    
    socket = createTCPServer(35000);
    if(socket < 0){
        printf("[SERVER] Errore di creazione del socket: %i\n", socket);
        return -1;
    } else {
        while (true) {
            int response = 0;
            printf("[SERVER] Sono in attesa di richieste da qualche client\n");
            connection = acceptConnection(socket);
            printf("[SERVER] Connessione instaurata\n");
            
            while (true) {
                TCPReceive(connection, &request, sizeof(request));
                
                printf("[SERVER] Ho ricevuto un messaggio: %d\n", request);
                response += request;
                printf("[SERVER] Somma attuale: %d\n", response);
                
                if (request == 0) {
                    TCPSend(connection, &response, sizeof(response));
                    closeConnection(connection);
                    break;
                }
            }
        }
    }
}

