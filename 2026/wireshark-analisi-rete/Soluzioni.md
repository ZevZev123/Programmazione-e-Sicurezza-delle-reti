---
tags:
  - Wireshark-analisi-rete
  - Soluzioni
---
### [[2026/wireshark-analisi-rete/analisi-rete.pdf#page=13&selection=6,0,6,11&color=note|Esercizio 1]]

1. Il livello data-link usato è Ethernet II.
Wireshark capisce che è Ethernet II perché la scheda di rete, quando cattura un segnale dal cavo, manda sempre anche un **modulo informativo** (creato dai driver Npcap).
Questa informazione dice a Wireshark "Encapsulation type: Ethernet (1)", il codice 1 secondo lo standard identifica che è stata utilizzata la strada Ethernet.	

<p style="text-align:center;"><img src="Img/Es01.01.png" alt="es01.01.png" width="600"/></p>

2. Disegno della PDU livello data-link:
<p style="text-align:center;"><img src="Img/Es01.02.png" alt="es01.02.png" width="600"/></p>

Destination/source = chi riceve e chi manda il messaggio
Type = nel pacchetto 9 contiene il codice <code>0x0800</code> che è l'identificativo del protocollo ipv4

3. Il MAC sorgente si trova nel Source dell'header ed è: 00:e0:81:24:dd:64 .
Il MAC sorgente è di tipo unicast, è impossibile che un pacchetto sia inviato in broadcast.

4. Il MAC destinatario si trova nel Destination dell'header ed è: ff:ff:ff:ff:ff:ff .
Il MAC destinatario è di tipo unicast.

5. Il protocollo di livello Network utilizzato è il IPv4 che viene specificato nella sezione Type dell'header

6. La dimensione dell'header IP è di 160bit o 20byte
<p style="text-align:center;"><img src="Img/Es01.03.png" alt="es01.03.png" width="600"/></p>
7. Gli indirizzi IP di sorgente e destinazione sono:
Sorgente: <code>157.27.252.223</code>
Destinatario: <code>127.27.252.255 (broadcast)</code>

8. Il livello trasporto usato è l'UDP.
Wireshark lo sa perché viene specificato nella sezione Protocol dell'header IP.

9. Le porte di sorgente e destinazione a livello trasporto sono:
Sorgente: 631
Destinazione: 631
<p style="text-align:center;"><img src="Img/Es01.04.png" alt="es01.04.png" width="600"/></p>

Si trovano nell'header di livello trasporto nella sezione Source Port e Destination Port

10. Filtrare solo i pacchetti [[Extra/Extra#ARP|ARP]]: <code>arp</code> .
11. Dopo aver applicato il filtro i pacchetti visualizzati sono 173 / 272, ovvero il 63.6%

12. Filtrare i pacchetti che hanno come MAC destinatario: <code>00:01:e6:57:4b:e0</code> .
Il filtro utilizzato è <code>eth.dst == 00:01:e6:57:4b:e0</code> .
13. Con il filtro applicato rimane solo un pacchetto 1 / 272, ovvero il 0.4%

14. Filtrare i pacchetti che hanno come MAC destinatario l'indirizzo broadcast.
Il filtro utilizzato è <code>eth.dst == ff:ff:ff:ff:ff:ff</code> .
15. Dopo aver applicato il filtro i pacchetti visualizzati sono 228 / 272, ovvero il 83.8%.
Sono tanti perché durante l'analisi della rete stava avvenendo una mappatura degli host. Motivo concentro potenziale è che lo switch non aveva ancora memorizzato gli host e quindi invia tutti i messaggi verso tutti finché non conosce tutti gli host connessi a lui.

### [[2026/wireshark-analisi-rete/analisi-rete.pdf#page=14&selection=43,0,43,11&color=note|Esercizio 2]]

1. Per colorare i pacchetti [[Extra#TCP|TCP]] e [[Extra#UDP|UDP]] di verde e rosso bisogna andare nel menù <code>Visualizza</code> di Wireshark, poi nel sottomenù <code>Regole di colorazione</code>. Nella nuova pagina selezionare i pacchetti <code>tcp</code> e impostare il colore verde come sfondo, per i pacchetti <code>udp</code> impostare il colore rosso.
<p style="text-align:center;"><code>Wireshark > Visualizza > Regole di colorazione</code></p>

2. Frame 1:
<table>
<tr><th>Ip sorgente</th><th>157.27.252.202</th></tr>
<tr><th>Ip destinatario</th><th>157.27.10.10</th></tr>
<tr><th>Tipo di protollo trasporto</th><th>UDP</th></tr>
<tr><th>Tipo di protollo applicazione</th><th>DNS</th></tr>
<tr><th>Payload applicazione</th><th>www.polito.it<br>Type A<br>Class IN</th></tr>
</table><br>
Frame 2:
<table>
<tr><th>Ip sorgente</th><th>157.27.10.10</th></tr>
<tr><th>Ip destinatario</th><th>157.27.252.202</th></tr>
<tr><th>Tipo di protollo trasporto</th><th>UDP</th></tr>
<tr><th>Tipo di protollo applicazione</th><th>DNS</th></tr>
<tr><th>Payload applicazione</th><th>web01.polito.it<br>type A<br>class IN<br>addr 130.192.73.1</th></tr>
</table>

Il payload del primo frame contiene la domanda del [[Extra#DNS|DNS]] (query) mentre il secondo frame contiene la risposta. Wireshark capisce che i pacchetti sono DNS perché la porta usata è la 53 (ovvero una [[Extra#Well-known ports|Well-known port]])

3. Frame 3:
<table>
<tr><th>Ip sorgente</th><th>157.27.252.202</th></tr>
<tr><th>Ip destinatario</th><th>130.192.73.1</th></tr>
</table>
Da questo pacchetto capiamo che la richiesta al DNS è andata a buon fine e ora l'host si sta interfacciando con il sito cercato precedentemente.<br>
4. Frame 6
<table>
<tr><th>Ip sorgente</th><th>157.27.252.202</th></tr>
<tr><th>Ip destinatario</th><th>130.192.73.1</th></tr>
<tr><th>Tipo di protollo trasporto</th><th>TCP</th></tr>
<tr><th>Tipo di protollo applicazione</th><th>HTTP</th></tr>
</table>
I tre pacchetti prima di questo fanno parte del [[Extra#Three way handshake|Three way handshake]] che serve instaurare una connessione [[Extra#TCP|TCP]] verso il server.
Le flag dei 3 pacchetti sono:
- <code><b>0x002 (SYN)</b></code> richiesta di connessione da parte del client
- <code><b>0x012 (SYN, ACK)</b></code> conferma di connessione dal server
- <code><b>0x010 (ACK)</b></code> conferma di connessione dal client

5. Filtro per vedere solo i pacchetti TCP (compresi HTTP): <code>tcp</code>
Dopo aver applicato il filtro vengono visualizzati 807 / 823 pacchetti, ovvero il 98.1%

6. Filtro per vedere solo i pacchetti TCP (HTTP esclusi): <code>tcp && !http</code>
Dopo aver applicato il filtro vengono visualizzati 673 / 823 pacchetti, ovvero l' 81.8%
Questi pacchetti comprendono tutti i messaggi di Three way handshake, di conferma di ricezione (ACK) e del controllo del flusso e della congestione.
Se il protocollo DNS avesse usato una connessione TCP si sarebbero aggiunti 3 pacchetti per aprire la connessione, i pacchetti di conferma per domanda e risposta e 3-4 per la chiusura della **sessione**. In questo caso usare una connessione TCP non sarebbe stato utile perché i messaggi di domanda e risposta del DNS sono molto piccoli e usare il protocollo TCP avrebbe creato latenza elevata per un carico di traffico inutile.

7. Usando il seguente comando sul terzo pacchetto
<p style="text-align:center;"><code>Tasto destro > Segui > Flusso TCP</code></p>
possiamo leggere l'intera conversazione tra il client e il server.
Nel payload troviamo in rosso le richieste GET del client e in blu le relative risposte dal server che condivide i dati della pagina web richiesta. 

### [[2026/wireshark-analisi-rete/analisi-rete.pdf#page=15&selection=0,0,0,11&color=note|Esercizio 3]]
