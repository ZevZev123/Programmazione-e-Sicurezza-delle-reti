[[2026/wireshark-analisi-rete/analisi-rete.pdf#page=13&selection=6,0,6,11&color=note|Esercizio 1]]
1. Il livello data-link usato è Ethernet II.
	Wireshark capisce che è Ethernet II perché la scheda di rete, quando cattura un segnale dal cavo, manda sempre anche un *modulo informativo* (creato dai driver Npcap).
	Questa informazione dice a Wireshark "Encapsulation type: Ethernet (1)", il codice 1 secondo lo standard identifica che è stata utilizzata la strada Ethernet.	
![[Es01.01.png|697]]
2. ![[Es01.02.png]]
	Destination/source = chi riceve e chi manda il messaggio
	Type = Codice che dice che il messaggio è del protocollo ARP
[[2026/wireshark-analisi-rete/analisi-rete.pdf#page=14&selection=43,0,43,11|Esercizio 2]]
