### [[2026/Socket/Lab-ApplicazioniReteSocket.pdf#page=32&selection=2,0,2,40&color=note|Esercizi basati su clientUDP e serverUDP]]
1. Lanciando prima [[2026/Socket/Esempi-client-server/serverUDP.c|serverUDP]] e dopo [[2026/Socket/Esempi-client-server/clientUDP.c|clientUDP]] si crea una sessione tra i due processi:
- Il server all'avvio è in ascolto
- All'avvio del client, il processo cerca il server e si connette a lui
- Il server e il client si scambiano dei messaggi
- Quando il processo client termina, il server rimane in ascolto
Invertendo il lancio dei due processi il client cerca il server senza però trovarlo quindi termina.

