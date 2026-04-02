---
tags:
  - Soluzioni
---
### [[2026/Socket/Lab-ApplicazioniReteSocket.pdf#page=32&selection=2,0,2,40&color=note|Esercizi basati su clientUDP e serverUDP]]
**File originali usati: [[2026/Socket/Esempi-client-server/serverUDP.c|serverUDP.c]], [[2026/Socket/Esempi-client-server/clientUDP.c|clientUDP.c]]**
1. Lanciando prima server e dopo client si crea una sessione tra i due processi:
- Il server all'avvio è in ascolto
- All'avvio del client, il processo cerca il server e si connette a lui
- Il server e il client si scambiano dei messaggi
- Quando il processo client termina, il server rimane in ascolto
Invertendo il lancio dei due processi il client cerca il server senza però trovarlo quindi termina.

2. Cambiando la porta del server a 10000 e la porta di trasmissione del client a 30000, quando vengono eseguiti non avviane nessuna comunicazione.

3. Cambiando la porta del server a 100, il processo non parte proprio perché la porta è una [[Extra#Well-known ports|Well-know port]].
Utilizzando il comando `sudo ./serverUDP` il processo server "parte".
Per permettere al condivisione tra i processi in `clientUDP` bisogna cambiare la porta dell'invio del messaggio (`UDPSend(destPort = 100)`).

4. Sostituendo `127.0.0.1` con `localhost` il funzionamento resta illeso.
Ma sostituendo `127.0.0.1` con `pippo` la condivisione non funziona.

5. ?

6. Se avvio 2 processi server su due terminali separati, il secondo cattura i pacchetti dal client mentre il primo no. Solo dopo la cessazione del secondo server il primo server inizierà a ricevere i pacchetti dal client.

7. Per fare in modo che il server riceva massimo 5 pacchetti:
```c
for (int i = 5; i > 0; i--) {
	printf("...");
	UDPReceive(...);
	UDPSend(...);
}
```
Mentre per fare in modo che il server non termini mai:
```c
while(true) {
	printf("...");
	UDPReceive(...);
	UDPSend(...);
}
```
### [[2026/Socket/Lab-ApplicazioniReteSocket.pdf#page=37&selection=2,0,2,15&color=note|Esercizi su UDP]]
**File originali usati: [[Esempi-client-server/serverUDP_inc.c|serverUDP_inc.c]], [[Esempi-client-server/clientUDP_inc.c|clientUDP_inc.c]]**
8. Modifiche per la creare una somma di n interi (fino all'inserimento di 0):
Server modificato: [[2026/Socket/client-server/serverUDP_inc.c|serverUPD_inc.c]]
```c
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
```
Client modificato: [[2026/Socket/client-server/clientUDP_inc.c|clientUPD_inc.c]]
```c
#include "network.h"

int main(void) {
	int request;
	int response;
	socketif_t socket;
	char hostAddress[MAXADDRESSLEN];
	int port;
	
	socket = createUDPInterface(20000);
	
	printf("Il programma terminera' inserendo uno 0 (zero)\n");
	while (true){
		printf("Inserisci un numero intero:\n");
		scanf("%d", &request);
		
		UDPSend(socket, &request, sizeof(request), "127.0.0.1", 35000);
		
		if (request == 0) break;
	}
	
	UDPReceive(socket, &response, sizeof(response), hostAddress, &port); 
	
	printf("[CLIENT] Ho ricevuto un messaggio da host/porta %s/%d\n", hostAddress, port);
	
	printf("[CLIENT] Contenuto: %d\n", response);
}
```

9. ?
10. Si mescolano le somme. Entrando più nei dettagli il server accetta i messaggi da entrambi i client però solo il primo a inviare il messaggio '0' riceverà risposta perché il server non è adattato per questo modo di esecuzione e non manda nessun altro risultato.
### [[2026/Socket/Lab-ApplicazioniReteSocket.pdf#page=48&selection=2,0,2,15&color=note|Esercizi su TCP]]
11. Il secondo server non funziona perché la porta è già utilizzata dal primo avvio.
12. I codici sommatore con il TCP sono [[client-server/serverTCPsum.c|serverTCPsum]] e [[client-server/clientTCPsum.c|clientTCPsum]].
13. Se avvio due client il secondo non si connette al server perché il server è scritto in modo che non accetti altre connessioni fintanto che è già connesso ad un altro client
```c
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
```
Solo una volta chiusa la connessione il server può accettare una richiesta da un nuovo client.
### [[2026/Socket/Lab-ApplicazioniReteSocket.pdf#page=53&selection=2,0,4,34&color=note|Esercizio: applicazione di trasferimento file]]
#### Dati con cui lavoriamo:
Il client chiede al server un file specificandone il nome 
Il server lo trasmette un byte alla volta
Il client lo salva in locale con lo stesso nome

> Visto che il server trasmette un byte alla volta usiamo il protocollo TCP. Un byte è troppo poco per condividere un file in un solo pacchetto e visto che ne dobbiamo inviare di più non possiamo usare UDP.
> (Supposizione senza prova) Se stacchiamo il cavo di rete durante la condivisione di un file grosso e lo riattacchiamo la condivisione viene interrotta ma non finita, infatti dopo aver riattaccato il cavo di rete la condivisione del file viene continuata e conclusa.

### [[2026/Socket/Lab-ApplicazioniReteSocket.pdf#page=54&selection=2,0,6,32&color=note|Temi d’esame (per ognuno ragionare sulla scelta del protocollo di livello trasporto)]]

*Implementare un servizio di calcolo remoto: il client spedisce al server in un unico messaggio due numeri interi e il tipo di operatore (somma, sottrazione, moltiplicazione, divisione) e il server, dopo aver svolto il calcolo, restituisce il risultato al client che così termina la sua esecuzione*
> In questo caso il protocollo perfetto da utilizzare è UDP, un singolo messaggio da client e dal server.

*Implementare un servizio di calcolo remoto: il client spedisce al server in 3 distinti messaggi due numeri interi e il tipo di operatore (somma, sottrazione, moltiplicazione, divisione) e il server, dopo aver svolto il calcolo, restituisce il risultato al client che così termina la sua esecuzione.*
> In questo caso utilizziamo il TCP visto che sono che la condivisione è "spaccata" in più pacchetti.

*Implementare un servizio di telepass: quando l'auto si avvicina al casello il terminale in esso presente spedisce al server il numero di targa; il server tiene traccia in una struttura dati del numero di passaggi per ogni targa e restituisce al client tale numero.*
> In questo caso utilizziamo il protocollo UDP perché la velocità è un punto critico, un auto non può aspettare i tempi di sincronizzazione TCP.

*Implementare una semplice versione di terminale remoto. Il client si connette ad un server di cui si conosce IP e porta e chiede all’utente di scrivere un comando come in un normale terminale a caratteri (detto anche shell o console) di Linux. Il comando viene eseguito dal server e il relativo output viene stampato a video dal client.*
> In questo caso il protocollo migliore è il TCP, il motivo è perché così abbiamo la garanzia che nel caso il codice bash e il suo output fossero tanto grandi non ci sono problemi nella condivisione.