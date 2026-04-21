---
tags:
  - Soluzioni
---
### [[2026/WebSocket/web-webservices.pdf#page=18&selection=2,0,2,9&color=note|Esercizio]]
Per usare [[2026/Websocket/Webservice/serverHTTP-REST.c|serverHTTP-REST.c]] l'url da usare è strutturato in questo modo:
<p style="text-align:center;"><code>http://localhost:8000/calcola-somma?param1=<span style="color: #d19a66;">num1</span>&amp;param2=<span style="color: #d19a66;">num2</span></code></p>
dove num1 e num2 sono numeri, e possono essere positivi, negativi e decimali.
Per usare [[2026/Websocket/Webservice/clientREST-GET.c|clientREST-GET.c]] i parametri sono:
<p style="text-align:center;"><code>./clientREST-GET <span style="color: #d19a66;">tipofunzione op1 op2</span></code></p>
<code style="background: transparent; color: #d19a66;">tipofunzione</code> = al momento l'unica opzione è <code style="background: transparent; color: #98c379;">"calcola-somma"</code><br><code style="background: transparent; color: #d19a66;">op1</code> = è il valore che assumerà il primo numero (<code style="background: transparent; color: #98c379;">num1</code>)<br><code style="background: transparent; color: #d19a66;">op2</code> = è il valore che assumerà il secondo numero (<code style="background: transparent; color: #98c379;">num2</code>)<br>

La *signature* della funzione calcolaSomma() sia nel client che nel server:
- **nome** -> float
- **tipo di ritorno** -> float
- **numero e tipo di parametri** -> 2, float, float 

**DA ELABORARE**
- **Astrazione (Trasparenza):** L'obiettivo di un Web Service o di un sistema REST è fare in modo che il programmatore del client senta la funzione come se fosse **locale**. Se la firma è identica, il programmatore non deve imparare un nuovo modo di chiamare la funzione; deve solo passare gli stessi parametri che passerebbe a una funzione scritta nel suo stesso file.    
- **Protocollo di Comunicazione:** La firma definisce il "contratto". Se il Client sa che servono due interi (a e b), costruirà un pacchetto HTTP (o una URL) contenente esattamente quei due dati. Se il Server ha la stessa firma, saprà esattamente cosa cercare nel pacchetto ricevuto per poter eseguire il calcolo.
- **Coerenza dei Dati:** Se il server restituisce un `int`, il client deve aspettarsi un `int`. Se le firme fossero diverse (es. il client manda un intero ma il server aspetta un float), il sistema fallirebbe o produrrebbe risultati errati.