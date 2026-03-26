#include "network.h"

int main(void) {
    socketif_t socket;
    char response[]="Sono il server: ho ricevuto correttamente il tuo messaggio!\n";
    char request[MTU];
    char hostAddress[MAXADDRESSLEN];
    int port;
    
    socket = createUDPInterface(10000);
    
    for (int i = 5; i > 0; i--) { 
    
        printf("[SERVER] Sono in attesa di massimo 5 richieste da qualche client\n");
        printf("Pacchetto %d\n",i);
        UDPReceive(socket, request, MTU, hostAddress, &port);
    
        printf("[SERVER] Ho ricevuto un messaggio da host/porta %s/%d\n", hostAddress, port);
        printf("[SERVER] Contenuto: %s\n", request);
    
        UDPSend(socket, response, strlen(response), hostAddress, port);
    }
    
}

