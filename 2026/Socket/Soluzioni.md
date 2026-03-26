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
10. Si mescolano le somme