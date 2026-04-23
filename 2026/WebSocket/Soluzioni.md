---
tags:
  - Soluzioni
---
### [[2026/WebSocket/web-webservices.pdf#page=18&selection=2,0,2,9&color=note|Esercizio]]
Per usare [[2026/Websocket/Esempi-Webservice/serverHTTP-REST.c|serverHTTP-REST.c]] l'url da usare è strutturato in questo modo:
<p style="text-align:center;"><code>http://localhost:8000/calcola-somma?param1=<span style="color: #d19a66;">num1</span>&amp;param2=<span style="color: #d19a66;">num2</span></code></p>
dove num1 e num2 sono numeri, e possono essere positivi, negativi e decimali.
Per usare [[2026/Websocket/Esempi-Webservice/clientREST-GET.c|clientREST-GET.c]] i parametri sono:
<p style="text-align:center;"><code>./clientREST-GET <span style="color: #d19a66;">tipofunzione op1 op2</span></code></p>
<code style="background: transparent; color: #d19a66;">tipofunzione</code> = al momento l'unica opzione è <code style="background: transparent; color: #98c379;">"calcola-somma"</code><br><code style="background: transparent; color: #d19a66;">op1</code> = è il valore che assumerà il primo numero (<code style="background: transparent; color: #98c379;">num1</code>)<br><code style="background: transparent; color: #d19a66;">op2</code> = è il valore che assumerà il secondo numero (<code style="background: transparent; color: #98c379;">num2</code>)<br>
Analisi con wireshark:
<p style="text-align:center;"><img src="Img/ws-01.png" alt="ws-01.png" width="600"/></p>

La *signature* della funzione calcolaSomma() sia nel client che nel server:
- **nome** -> calcolaSomma
- **tipo di ritorno** -> float
- **numero e tipo di parametri** -> 2, float, float 

Motivo principale è per la **Coerenza dei Dati** ovvero se il server restituisce un `int`, il client deve aspettarsi un `int`. Se le firme fossero diverse (es. il client manda un intero ma il server aspetta un float), il sistema fallirebbe o produrrebbe risultati errati.
Motivo aggiuntivo è che il programmatore non deve imparare un nuovo modo di chiamare la funzione. I parametri sono due ambi i casi e sono i `float` che rappresentano i numeri da sommare.
### [[2026/WebSocket/web-webservices.pdf#page=19&selection=2,0,2,11&color=note|Esercizio 2]]
Avere il server in C e il client in Java è un'opportunità di **Interoperabilità**. Dimostra che il protocollo HTTP funge da linguaggio universale, permettendo a tecnologie diverse di cooperare. Questo elimina i vincoli tecnologici e permette di scegliere il linguaggio di programmazione migliore per ogni specifico compito (C per le prestazioni, Java per la versatilità).
### [[2026/WebSocket/web-webservices.pdf#page=20&selection=2,0,2,11&color=note|Esercizio 3]]
Aggiunta opzione `numeri-primi` insieme a `calcola-somma`.
Il controllo del `url` in [[2026/WebSocket/Webservice/serverHTTP-REST.c|serverHTTP-REST.c]] è stato cambiato molto dal come era precedentemente:
```c
if (strstr(url, "calcola-somma") != NULL || strstr(url, "numeri-primi") != NULL) {
	char *function, *op1, *op2, *val1_str, *val2_str;
	
	function = strtok(url, "?&");
	op1 = strtok(NULL, "?&");
	op2 = strtok(NULL, "?&");
	strtok(op1,"=");
	val1_str = strtok(NULL,"=");
	strtok(op2,"=");
	val2_str = strtok(NULL,"=");
	
	if (strstr(function, "calcola-somma")) {
		printf("Chiamata a funzione sommatrice\n");
		float somma = calcolaSomma(atof(val1_str), atof(val2_str));
		
		fprintf(connfd, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n");
		fprintf(connfd, "{\r\n \"somma\": %f\r\n}\r\n", somma);
	}
	else if (strstr(function, "numeri-primi")) {
		printf("Chiamata a funzione numero primo\n");
		numeriPrimi(atoi(val1_str), atoi(val2_str), connfd);
	}
}
```
Viene fatto un primo controllo per essere sicuri che nell'url sia presente una funzione presente tra quelle implementate. Successivamente vengono presi i dati che dovranno essere poi invitati alla funzione richiesta. Se avessimo tenuto ben separate le condizioni dell'url `calcola-somma` e `numeri-primi` questa parte di codice si ripeteva uguale, questo è il motivo per cui è stata presa la scelta di "fonderle" insieme e controllare solo alla fine quale funzione specifica abbiamo bisogno.

La funzione <code style="background: transparent; color: #d19a66;">calcola-somma</code> non viene modificata mentre la funzione <code style="background: transparent; color: #d19a66;">numeri-primi</code> è scritta in questo modo:

```c
void numeriPrimi(int min, int max, FILE *connfd) {
	int flag, first = 1;
	
	// Invia l'header HTTP e l'inizio della struttura JSON
	fprintf(connfd, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n");
	fprintf(connfd, "{\r\n \"numeri-primi\": [");
	
	for (int i = min; i <= max; i++) {
		if (i == 1 || i == 0)
			continue;
		
		// Controllo se il numero è primo
		flag = 1;
		for (int j = 2; j <= i / 2; ++j) {
			if (i % j == 0) {
				flag = 0;
				break;
			}
		}
		
		if (flag == 1) {
			if (!first) {
				// Aggiungi la virgola prima del numero (se non è il primo)
				fprintf(connfd, ", "); 
			}
			fprintf(connfd, "%d", i); // Invia il numero primo
			first = 0;
		}
	}
	fprintf(connfd, "]\r\n}\r\n");
}
```
come si può ben vedere non c'è nessun valore di ritorno. E' stata presa questa scelta per i numeri primi sono numerosi nel caso di un range scelto ampio e salvare tutti questi numeri e troppo costoso. Per evitare questo problema viene condiviso anche <code style="color: #56b6c2;">FILE <span style="color: #f92672;">*</span>connfd</code>, per poter stampare subito i numeri primi trovati.

Modifiche fatte a [[2026/WebSocket/Webservice/ClientREST.java|ClientREST.java]]:
- Semplice controllo della funzione richiesta in <code style="background: transparent;"><span style="color: #569cd6;">class</span> <span style="color: #4ec9b0;">ClientREST</span></code>
```java
if(args.length < 3) {
	System.out.println("USAGE: java ClientREST tipofunzione op1 op2");
	}
	else if(args[0].equals("calcola-somma")) {
	service1.calcolaSomma(Float.parseFloat(args[1]), Float.parseFloat(args[2]));
	}
	else if(args[0].equals("numeri-primi")) {
	service1.numeriPrimi(Integer.parseInt(args[1]), Integer.parseInt(args[2]));
}
```

- Modifiche in <code style="background: transparent;"><span style="color: #569cd6;">class</span> <span style="color: #4ec9b0;">RESTAPI</span></code>
```java
void calcolaSomma(float val1, float val2) {
	URL u = null;
	try {
		u = URI.create("http://" + server + ":8000/calcola-somma?param1=" + val1 + "&param2=" + val2).toURL(); // per evitare il warning con java 20+
		// u = new URL("http://"+server+":8000/calcola-somma?param1="+val1+"&param2="+val2);
		System.out.println("URL aperto: " + u);
		conn(u);
	}
	catch (MalformedURLException e) {
		System.out.println("URL errato: " + u);
	}
}

void numeriPrimi(int min, int max) {
	URL u = null;
	try {
		u = URI.create("http://" + server + ":8000/numeri-primi?min=" + min + "&max=" + max).toURL(); // per evitare il warning con java 20+
		// u = new URL("http://"+server+":8000/numeri-primi?min="+min+"&max="+max);
		System.out.println("URL aperto: " + u);
		conn(u);
	}
	catch (MalformedURLException e) {
		System.out.println("URL errato: " + u);
	}
}

void conn(URL u) {
	try {
		URLConnection c = u.openConnection();
		c.connect();
		BufferedReader b = new BufferedReader(new InputStreamReader(c.getInputStream()));
		System.out.println("Lettura dei dati...");
		String s;
		while( (s = b.readLine()) != null ) {
			// legge riga per riga il messaggio di ritorno dal server
			System.out.println(s);
		}
	}
	catch (IOException e) {
		System.out.println(e.getMessage());
	}
}
```
E' stato modificato il metodo <code style="background: transparent; color: #d19a66;">calcolaSomma()</code> e aggiunti <code style="background: transparent; color: #d19a66;">numeriPrimi()</code> e <code style="background: transparent; color: #d19a66;">conn()</code>.
La modifica a <code style="background: transparent; color: #d19a66;">calcolaSomma()</code> e stata fatta per diminuire la quantità di codice ripetuto.
Le differenze tra la funzione `calcola somma` e `numeri primi` sono l'url di connessione al server e i tipi dei numeri (`float` / `int`).

Il tempo di esecuzione utilizzando il comando:
<p style="text-align:center;"><code>time java ClientREST.java numeri-primi 1 1000000</code></p>
è:
Executed in     24.49 secs                      fish        external
usr time             1.94 secs    827.00 micros      1.94 secs
sys time             0.16 secs         0.00 micros      0.16 secs
**risultato stampato a video

L'algoritmo dei numeri primi non è stato tradotto in Java. Il client java chiede al server di farlo che poi gli restituisce i risultati.

### [[2026/WebSocket/web-webservices.pdf#page=23&selection=2,0,2,16&color=note|Esercizio finale]]
