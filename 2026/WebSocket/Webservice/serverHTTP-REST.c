#include "network.h"

float calcolaSomma(float, float);
void numeriPrimi(int min, int max, FILE *connfd);

int main(){
    socketif_t sockfd;
    FILE* connfd;
    int res, i, port = 8000;
    long length=0;
    char request[MTU], url[MTU], method[10], c;
    
    sockfd = createTCPServer(port);
    if (sockfd < 0){
        printf("[SERVER] Errore: %i\n", sockfd);
        return -1;
    }

    printf("Il server e' avviato sul seguente URL:\n");
    printf("http://127.0.0.1:%d\n", port);
    fflush(stdout);
    
    while(true) {
        connfd = acceptConnectionFD(sockfd);
        
        fgets(request, sizeof(request), connfd);
        strcpy(method,strtok(request, " "));
        strcpy(url,strtok(NULL, " "));
        while(request[0]!='\r') {
            fgets(request, sizeof(request), connfd);
            if(strstr(request, "Content-Length:")!=NULL)  {
                length = atol(request+15);
            }
        }
        
        if(strcmp(method, "POST")==0)  {
            for(i=0; i<length; i++)  {
                c = fgetc(connfd);
            }
        }
        
        if (strstr(url, "calcola-somma") != NULL || strstr(url, "numeri-primi") != NULL) {
            char *function, *op1, *op2, *val1_str, *val2_str;

            function = strtok(url, "?&");
            op1 = strtok(NULL, "?&");
            op2 = strtok(NULL, "?&");
            strtok(op1,"=");
            val1_str = strtok(NULL,"=");
            strtok(op2,"=");
            val2_str = strtok(NULL,"=");

            if (strstr(function, "calcola-somma")) {
                printf("Chiamata a funzione sommatrice\n");
                float somma = calcolaSomma(atof(val1_str), atof(val2_str));

                fprintf(connfd, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n");
                fprintf(connfd, "{\r\n  \"somma\": %f\r\n}\r\n", somma);
            }
            else if (strstr(function, "numeri-primi")) {
                printf("Chiamata a funzione numero primo\n");
                numeriPrimi(atoi(val1_str), atoi(val2_str), connfd);
            }
        }
        else {
            // stampa in connfd con visualizzazione più semplice e scalabile
            fprintf(connfd, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n"
                            "{\r\n"
                            "  \"URL_accettati\": [\r\n"
                            "    \"localhost:8000/calcola-somma?param1=num1&param2=num2\",\r\n"
                            "    \"localhost:8000/numeri-primi?min=num1&max=num2\"\r\n"
                            "  ]\r\n"
                            "}\r\n");
        }
        
        fclose(connfd);
                
        printf("[SERVER] sessione HTTP completata\n\n");
    }
    
    closeConnection(sockfd);
    return 0;
}

float calcolaSomma(float val1, float val2) {
   return (val1 + val2);
}

void numeriPrimi(int min, int max, FILE *connfd) {
    int flag, first = 1;

    // Invia l'header HTTP e l'inizio della struttura JSON
    fprintf(connfd, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n");
    fprintf(connfd, "{\r\n    \"numeri-primi\": [");

    for (int i = min; i <= max; i++) {
        if (i == 1 || i == 0)
            continue;
 
        // Controllo se il numero è primo
        flag = 1;
        for (int j = 2; j <= i / 2; ++j) {
            if (i % j == 0) {
                flag = 0;
                break;
            }
        }

        if (flag == 1) {
            if (!first) {
                // Aggiungi la virgola prima del numero (se non è il primo)
                fprintf(connfd, ", ");
            }
            fprintf(connfd, "%d", i); // Invia il numero primo
            first = 0;
        }
    }

    fprintf(connfd, "]\r\n}\r\n");
}