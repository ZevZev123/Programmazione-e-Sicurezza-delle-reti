#include "network.h"

int main() {
    char *HTMLDefault = "";
    char *HTMLSuccess = "HTTP/1.1 200 OK\r\n\r\n<html><body><h1>Upload Completato!</h1><a href='/'>Torna alla home</a></body></html>";
    char *HTMLError   = "HTTP/1.1 200 OK\r\n\r\n<html><body><h1>Errore</h1><p>File non trovato o errore upload.</p></body></html>";
    char *HTMLHeader  = "HTTP/1.1 200 OK\r\n\r\n";

    socketif_t sockfd;
    int port = 8001;

    sockfd = createTCPServer(port);
    if (sockfd < 0) return -1;
    
    printf("Il server e' avviato sul seguente URL:\n");
    printf("http://127.0.0.1:%d\n", port);
    fflush(stdout);

    FILE *fptr = fopen("form-post-1.html", "r");
    if (fptr) {
        fputs(HTMLHeader, HTMLDefault);
        char c;
        while(c = fgetc(fptr) != EOF) fputc(c, HTMLDefault);
        fclose(fptr);
    }

    while(true) {
        FILE *connfd = acceptConnectionFD(sockfd);
        char request[MTU], path_buffer[256] = {0}, method[10] = {0};
        long content_length = 0;

        // 1. Analisi riga di richiesta (METODO e PATH)
        if (fgets(request, sizeof(request), connfd)) {
            char *m_ptr = strtok(request, " ");
            if (m_ptr) strcpy(method, m_ptr);

            char *p_ptr = strtok(NULL, " ");
            if (p_ptr) {
                if (p_ptr[0] == '/') p_ptr++;
                strcpy(path_buffer, p_ptr);
            }
        }

        // 2. Analisi Header (cerchiamo Content-Length per il POST)
        while(fgets(request, sizeof(request), connfd) != NULL && request[0] != '\r' && request[0] != '\n') {
            if (strncasecmp(request, "Content-Length:", 15) == 0) {
                content_length = atol(request + 15);
            }
        }
        
        printf("[LOG] Metodo: %s | Path: %s | Size: %ld\n", method, path_buffer, content_length);

        // 3. LOGICA DI RISPOSTA / UPLOAD
        if (strcmp(method, "POST") == 0) {
            // Caso UPLOAD: Salviamo il file che arriva nel corpo della POST
            // Nota: in un caso reale il path_buffer sarebbe il nome del file desiderato
            if (path_buffer[0] != '\0') {
                FILE *upload_file = fopen(path_buffer, "wb"); // 'wb' per scrivere file binari
                if (upload_file) {
                    for (long i = 0; i < content_length; i++) {
                        fputc(fgetc(connfd), upload_file);
                    }
                    fclose(upload_file);
                    fputs(HTMLSuccess, connfd);
                } else {
                    fputs(HTMLError, connfd);
                }
            }
        } else {
            // Caso GET: Restituiamo il file o la home
            if (path_buffer[0] == '\0') {
                fputs(HTMLDefault, connfd);
            } else {
                FILE *fptr = fopen(path_buffer, "r");
                if (fptr) {
                    fputs(HTMLHeader, connfd);
                    int c;
                    while((c = fgetc(fptr)) != EOF) fputc(c, connfd);
                    fclose(fptr);
                } else {
                    fputs(HTMLError, connfd);
                }
            }
        }

        fclose(connfd);                
        printf("[SERVER] Sessione completata\n\n");
    }
    
    closeConnection(sockfd);
    return 0;
}