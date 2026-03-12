# Termini tecnici
**PDU** (Protocol Data Unit) di livello *<livello ISO/OSI>*
Il PDU è composto da Header e payload

# Metodi di trasmissione
La trasmissione avviene sempre da un solo mittente<br>**UNICAST**         = 1 destinatario
**MULTICAST**    = gruppo di destinatari
**BROADCAST**   = tutti i destinatari della rete

# ARP
ARP è un protocollo di mappatura utilizzato a livello data-link (MAC) e network (IP) che serve per ottenere l'indirizzo MAC di un host partendo dal suo IP.

*Come funziona?*
Una macchina host manda un pacchetto in **broadcast** (MAC destinatario ff:ff:ff:ff:ff:ff) con i propri dati (indirizzo IP e MAC) e chiede chi ha un determinato IP.
Solo la macchina con quel determinato IP risponde inviando un pacchetto *ARP reply* in **unicast** (diretto solo al richiedente) condividendo il suo indirizzo MAC.

<p style="text-align:center;"><img src="Img/Es01.03.png" alt="es01.03.png" width="600"></p>

Destination = **MAC broadcast** (ff:ff:ff:ff:ff:ff)
Source = MAC sorgente
Type = <code>0x0806</code> identificativo protocollo ARP
Area a linee = il contenuto ARP
Padding = zeri extra per allungare il pacchetto

I pacchetti devono avere dimensione minima **64 byte**. Serve a garantire che il segnale elettrico resti sul cavo abbastanza a lungo da permettere a tutte le schede di rete di rilevare eventuali **collisioni**

**NB:** anche conoscendo l'IP, l'host manda il pacchetto di tipo broadcast anche a livello Network. L'IP viene usato solo come domanda nel payload.