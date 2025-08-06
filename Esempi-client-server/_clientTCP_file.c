#include "network.h"

int main(){
    char receive[MTU], fileName[MTU] = "testo.txt", fileOut[MTU] = "testo2.txt";
    FILE *fd, *fptr;

    fd = createTCPConnectionFD("127.0.0.1", 35000);
    if (fd == NULL) {
        perror("createTCPConnectionFD");
        return -1;
    }

    // spedisco il nome del file
    printf("[CLIENT] Inizio invio del file: %s\n", fileName);
    fprintf(fd, "%s\n", fileName);
    fflush(fd);

    fptr = fopen(fileOut, "wb");
    if (!fptr){
        perror("Errore apertura file");
        fclose(fd);
        return -1;
    }

    size_t bytesRead;
    while ((bytesRead = fread(receive, 1, sizeof(receive), fd)) > 0) {
        fwrite(receive, 1, bytesRead, fptr);
        printf("[CLIENT] Ricevuti %zu byte\n", bytesRead);
    }

    fclose(fptr);
    fclose(fd);

    printf("[CLIENT] File ricevuto con successo\n");
    return 0;
}

