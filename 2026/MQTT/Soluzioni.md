---
tags:
  - Soluzioni
---
Info [[Extra#PUB/SUB|PUB/SUB]]
### [[2026/MQTT/Pub-sub.pdf#page=22&selection=50,0,50,19&color=note|Esercizi su pub/sub]]
Comando per far partire il subscriber:
<p style="text-align:center;"><code>❯ mosquitto_sub <span style="color: #d19a66;">-h</span> e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud <span style="color: #d19a66;">-p</span> 8883 <span style="color: #d19a66;">-u</span> univr-studenti <span style="color: #d19a66;">-P</span> MQTT-esercitazione2026 <span style="color:#d19a66">-t</span> temperatura</code></p>
Comando per far mandare il messaggio il publisher:
<p style="text-align:center;"><code>❯ mosquitto_pub <span style="color: #d19a66;">-h</span> e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud <span style="color: #d19a66;">-p</span> 8883 <span style="color: #d19a66;">-u</span> univr-studenti <span style="color: #d19a66;">-P</span> MQTT-esercitazione2026 <span style="color: #d19a66;">-t</span> temperatura -m 52</code></p>
**Leggenda:** <br><span style="color: #d19a66;">-h</span> = host a cui connettersi<br><span style="color: #d19a66;">-p</span> = porta<br><span style="color: #d19a66;">-u</span> = username<br><span style="color: #d19a66;">-P</span> = password<br><span style="color: #d19a66;">-t</span> = nome del topic<br><span style="color: #d19a66;">-m</span> = messaggio<br><span style="color: #d19a66;">-d</span> = debug

1. Se pubblico una temperatura prima di aver lanciato il subscriber il messaggio viene inviato, unica cosa è che non posso visualizzare l'arrivo.
Con l'opzione `--retain` il messaggio viene salvato nel buffer, infatti quando poi lancio il subscriber arriva il messaggio.
**NB:** per togliere il messaggio dal buffer: `-r -n` dove `-n` è il messaggio nullo
2. Visto che ho 2 sensori è corretto aprire un terminale per sensore (publisher), sommando il terminale subscriber abbiamo bisogno in totale di 3 terminali:
<p style="text-align:center;"><img src="Img/terminale-01.png" alt="terminale-01.png" width="600"/></p>
3. Per avere entrambe le temperature su un terminale solo si aggiunge questo al comando:
<p style="text-align:center;">... -t temp1 -t temp2 -v</p>
dove `temp1` e `temp2` sono le due stanze e `-v` ci permette di vedere da dove quale publisher arrivano le informazioni.
<p style="text-align:center;"><img src="Img/terminale-02.png" alt="terminale-02.png" width="600"/></p>
4. Il subscriber interessato alle temperature non riceve i valori dal publisher umidità (UR). Però con una modifica è possibile utilizzare un unico subscriber per farlo:
<p style="text-align:center;"><img src="Img/terminale-03.png" alt="terminale-03.png" width="600"/></p>
In alto a sinistra il subscriber che legge dati dai topic `temp1`, `temp2` e `UR`. Gli altri terminali sono invece i publisher e interpretano i tre sensori in questione.
5. Il livello di trasporto utilizzato per i pacchetti MQTT è il TCP. Le porte utilizzate sono la 1883 usata dal broker in ascolto, per i publisher e il subscriber ce ne sono di più: 60070, 38732, 46348, 39360 e 43278.
NB: filtrando per `mqtt` diventa più facile trovare i pacchetti di interesse.
La porta 60070 è quella usata dal subscriber, si trovano i pacchetti con questa porta tutta la durata dell'analisi della rete. La connessione è **una soltanto**.
Le altre porte sono dei publisher, ogni publisher crea una connessione TCP e si chiude una volta inviato il messaggio.
### [[2026/MQTT/Pub-sub.pdf#page=23&selection=26,0,26,19&color=note|Esercizi su pub/sub]]
Subscriber per il relatore:
<p style="text-align:center;"><code>❯ mosquitto_sub <span style="color: #d19a66;">-h</span> e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud <span style="color: #d19a66;">-p</span> 8883 <span style="color: #d19a66;">-u</span> univr-studenti <span style="color: #d19a66;">-P</span> MQTT-esercitazione2026 <span style="color:#d19a66">-t</span> univr/#</code></p>
Subscriber per la segreteria:
<p style="text-align:center;"><code>❯ mosquitto_sub <span style="color: #d19a66;">-h</span> e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud <span style="color: #d19a66;">-p</span> 8883 <span style="color: #d19a66;">-u</span> univr-studenti <span style="color: #d19a66;">-P</span> MQTT-esercitazione2026 <span style="color:#d19a66">-t</span> univr/docenti/# <span style="color:#d19a66">-t</span> univr/studenti/#</code></p>
Subscriber per i docenti:
<p style="text-align:center;"><code>❯ mosquitto_sub <span style="color: #d19a66;">-h</span> e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud <span style="color: #d19a66;">-p</span> 8883 <span style="color: #d19a66;">-u</span> univr-studenti <span style="color: #d19a66;">-P</span> MQTT-esercitazione2026 <span style="color:#d19a66">-t</span> univr/docenti/# <span style="color:#d19a66">-t</span> univr/studenti/#</code></p>
Subscriber per gli studenti:
<p style="text-align:center;"><code>❯ mosquitto_sub <span style="color: #d19a66;">-h</span> e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud <span style="color: #d19a66;">-p</span> 8883 <span style="color: #d19a66;">-u</span> univr-studenti <span style="color: #d19a66;">-P</span> MQTT-esercitazione2026 <span style="color:#d19a66">-t</span> univr/studenti/#</code></p>
L'aggiunta di univr al topic permette la scalabilità del sistema in modo che se in futuro dovesse essere aggiunto un'altra entità (o più di una) il sistema continuerà a funzionare, ovvero il rettore continuerà a leggere i messaggi di tutti.
Usando il carattere `#` diamo la possibilità di creare dei "sotto-topic" e che ogni entità universitaria della categoria giusta potrà leggerlo senza problemi.