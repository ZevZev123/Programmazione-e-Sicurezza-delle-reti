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
<p style="text-align:center;"><img src="Img/Es01.04.png" alt="es01.04.png" width="600"/></p>
7. Gli indirizzi ip di sorgente e destinazione sono:
Sorgente: 157.27.252.223
Destinatario: 127.27.252.255 (broadcast)

8. Il livello trasporto usato è l'UDP.
Wireshark lo sa perché viene specificato nella sezione Protocol dell'header IP.

9. Le porte di sorgente e destinazione a livello trasporto sono:
Sorgente: 631
Destinazione: 631
<p style="text-align:center;"><img src="Img/Es01.05.png" alt="es01.05.png" width="600"/></p>

Si trovano nell'header di livello trasporto nella sezione Source Port e Destination Port

10. Filtrare solo i pacchetti [[Extra/Extra#ARP|ARP]]: <code>arp</code> .
11. Dopo aver applicato il filtro i pacchetti visualizzati sono 173 / 272, ovvero il 63.6%

12. Filtrare i pacchetti che hanno come MAC destinatario: 00:01:e6:57:4b:e0 .
Il filtro utilizzato è <code>eth.dst == 00:01:e6:57:4b:e0</code> .
13. Con il filtro applicato rimane solo un pacchetto 1 / 272, ovvero il 0.4%

14. Filtrare i pacchetti che hanno come MAC destinatario l'indirizzo broadcast.
Il filtro utilizzato è <code>eth.dst == ff:ff:ff:ff:ff:ff</code> .
15. Dopo aver applicato il filtro i pacchetti visualizzati sono 228 / 272, ovvero il 83.8%.
Sono tanti perché durante l'analisi della rete stava avvenendo una mappatura degli host. Motivo concentro potenziale è che lo switch non aveva ancora memorizzato gli host e quindi invia tutti i messaggi verso tutti finché non conosce tutti gli host connessi a lui.

### [[2026/wireshark-analisi-rete/analisi-rete.pdf#page=14&selection=43,0,43,11&color=note|Esercizio 2]]

1. 