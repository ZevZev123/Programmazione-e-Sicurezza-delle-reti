#include "network.h"
#include <stdio.h>

int share_file_content(const char*, FILE*);

int main() {
    socketif_t sockfd;
    int port = 8001;

    sockfd = createTCPServer(port);
    if (sockfd < 0) return -1;
    
    printf("Il server e' avviato sul seguente URL:\n");
    printf("http://127.0.0.1:%d\n", port);
    fflush(stdout);

    while(true) {
        FILE *connfd = acceptConnectionFD(sockfd);
        char request[MTU], path_buffer[256] = {0}, method[10] = {0};
        long length = 0;

        // Analisi riga di richiesta (METODO e PATH)
        if (fgets(request, sizeof(request), connfd)) {
            char *m_ptr = strtok(request, " ");
            if (m_ptr) strcpy(method, m_ptr);   // salva il metodo (post / get)

            char *p_ptr = strtok(NULL, " ");
            if (p_ptr) {
                if (p_ptr[0] == '/') p_ptr++;
                strcpy(path_buffer, p_ptr);     // salva il path (nome del file)
            }
        }
        
        while(fgets(request, sizeof(request), connfd) != NULL && strcmp(request, "\r\n") != 0 && strcmp(request, "\n") != 0) { // libera request HTTP
            if (strstr(request, "Content-Length:") != NULL) {
                length = atol(request + 15);        // trasforma tutto quello che c'è +15 caratteri in numero
            }
        }

        printf("[LOG] Metodo: %s | Path: %s | Lenght (POST): %ld\n", method, path_buffer, length);

        // Logica di risposta
        if (strcmp(method, "POST") == 0) {
            // Caso POST
            if (length > 0) {
                printf("lenght: %ld\n", length);
                char *post_body = malloc(length + 1);
                if (post_body) {
                    fread(post_body, 1, length, connfd);
                    post_body[length] = '\0';
                    printf("[POST DATA]: %s\n", post_body + 5); // +5 per togliere page=
                    share_file_content(post_body + 5, connfd);
                    free(post_body);
                }
            }
        } else {
            // Caso GET
            if (path_buffer[0] == '\0') {
                printf("Pagina iniziale richiesta\n");
                share_file_content("form-post-1.html", connfd);
                // carica pagina form
            } else {
                printf("Pagina richiesta con GET: %s\n", path_buffer);
                share_file_content(path_buffer, connfd);
            }
        }

        fclose(connfd);                
        printf("[SERVER] Sessione completata\n\n");
    }
    
    closeConnection(sockfd);
    return 0;
}

// Funzione per condividere il contenuto di un file carattere per carattere
int share_file_content(const char *filename, FILE *connfd) {
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        perror("Errore nell'apertura del file");
        share_file_content("error.html",connfd);
        return -1;
    }
    
    char *HTMLHeader  = "HTTP/1.1 200 OK\r\n\r\n";
    fputs(HTMLHeader, connfd);

    char c;
    while ((c = fgetc(fptr)) != EOF) {
        if (fputc(c, connfd) == EOF) {
            perror("Errore nella scrittura sul socket");
            fclose(fptr);
            return -1;
        }
    }
    
    fclose(fptr);
    return 0;
}