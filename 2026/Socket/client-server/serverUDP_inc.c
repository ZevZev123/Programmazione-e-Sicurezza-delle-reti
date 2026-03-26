#include "network.h"

int main(void) {
    int request;
    int response = 0;
    socketif_t socket;
    char hostAddress[MAXADDRESSLEN];
    int port;

    socket = createUDPInterface(35000);
    
    printf("[SERVER] Sono in attesa di richieste da qualche client\n");
    while (true){
        UDPReceive(socket, &request, sizeof(request), hostAddress, &port);
        
        printf("[SERVER] Ho ricevuto un messaggio da host/porta %s/%d\n", hostAddress, port);
        printf("[SERVER] Contenuto: %d\n", request);
        
        if (request == 0) break;

        response += request;
    }

    UDPSend(socket, &response, sizeof(response), hostAddress, port);
}

