#include "network.h"

int main(){
    char *HTMLDefault = "HTTP/1.1 200 OK\r\n\r\n<html><head><title>An Example Page</title></head><body><h3>Cerca nella URL un file</h3>La scelta attuale non esiste</html>\r\n";
    char *HTMLError = "HTTP/1.1 200 OK\r\n\r\n<html><body>La pagina che cerchi non esiste</body></html>";
    char *HTMLHeader = "HTTP/1.1 200 OK\r\n\r\n";

    socketif_t sockfd;
    int port = 8000;

    sockfd = createTCPServer(port);
    if (sockfd < 0) return -1;
    
    printf("Il server e' avviato sul seguente URL:\n");
    printf("http://127.0.0.1:%d\n",port);
    fflush(stdout);

    while(true) {
        FILE *connfd = acceptConnectionFD(sockfd);
        char request[MTU], path_buffer[256] = {0};
        
        // Leggi solo la prima riga e fai il parsing immediato
        if (fgets(request, sizeof(request), connfd)) {
            strtok(request, " ");          // Salta il metodo (GET/POST)
            char *p = strtok(NULL, " ");   // Prendi il path
            
            if (p) {
                if (p[0] == '/') p++;      // Salta lo slash
                strcpy(path_buffer, p);    // Salva il path prima di svuotare
           }
        }

        // Svuota il resto degli header HTTP
        while(fgets(request, sizeof(request), connfd) != NULL && request[0] != '\r' && request[0] != '\n');
        
        printf("path: %s\n", path_buffer);

        // logica di risposta
        if (path_buffer[0] == '\0') {
            fputs(HTMLDefault, connfd);
        } else {
            FILE *fptr = fopen(path_buffer, "r");
            if (fptr) {
                fputs(HTMLHeader, connfd);
                char c;
                while((c = fgetc(fptr)) != EOF) fputc(c, connfd);
                fclose(fptr);
            } else {
                fputs(HTMLError, connfd);
            }
        }

        fclose(connfd);                
        printf("\n\n[SERVER] sessione HTTP completata\n\n");
    }
    
    closeConnection(sockfd);
    return 0;
}
