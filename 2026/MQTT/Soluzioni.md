---
tags:
  - Soluzioni
---
Info [[Extra#PUB/SUB|PUB/SUB]]
### [[2026/MQTT/Pub-sub.pdf#page=22&selection=50,0,50,19&color=note|Esercizi su pub/sub]]
Comando per far partire il subscriber:
<p style="text-align:center;"><code>❯ mosquitto_sub <span style="color: #d19a66;">-h</span> e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud <span style="color: #d19a66;">-p</span> 8883 <span style="color: #d19a66;">-u</span> univr-studenti <span style="color: #d19a66;">-P</span> MQTT-esercitazione2026 -t temperatura</code></p>
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
