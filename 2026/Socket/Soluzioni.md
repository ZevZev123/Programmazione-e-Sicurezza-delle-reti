### [[2026/Socket/Lab-ApplicazioniReteSocket.pdf#page=32&selection=2,0,2,40&color=note|Esercizi basati su clientUDP e serverUDP]]
1. Lanciando prima [[2026/Socket/Esempi-client-server/serverUDP.c|serverUDP]] e dopo [[2026/Socket/Esempi-client-server/clientUDP.c|clientUDP]] si crea una sessione tra i due processi:
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

