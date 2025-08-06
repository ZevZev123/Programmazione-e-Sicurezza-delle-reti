#include "network.h"

int main(){
    char fileName[MTU], buffer[MTU];
    socketif_t server;
    FILE *fd, *fptr;
    
    server = createTCPServer(35000);
    if (server < 0){
        perror("createTCPServer");
        return -1;
    }
    
    printf("[SERVER] Server in attesa della connessione\n");
    fd = acceptConnectionFD(server);
    if (fd == NULL) {
        perror("acceptConnectionFD");
        return -1;
    }
    
    printf("[SERVER] In attesa del nome del file\n");
    if(fgets(fileName, sizeof(fileName), fd) == NULL){
        perror("fgets");
        fclose(fd);
        return -1;
    }
    printf("[SERVER] Nome del file ricevuto: %s\n", fileName);
    
    fileName[strcspn(fileName, "\r\n")] = '\0';

    fptr = fopen(fileName, "rb");
    if (!fptr){
        perror("Errore apertura file");
        fclose(fd);
        return -1;
    }

    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fptr)) > 0) {
        fwrite(buffer, 1, bytesRead, fd);
    }
    fflush(fd);
    
    fclose(fptr);
    fclose(fd);

    printf("[SERVER] File inviato con successo\n");
    return 0;
}

