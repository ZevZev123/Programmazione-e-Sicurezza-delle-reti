---
tags:
  - Soluzioni
---
### [[2026/Web/web-webservices.pdf#page=26&selection=2,0,2,9&color=note|Esercizio]]
[[2026/Web/web/javascript-load.html|Pagina]] HTML che ricarica periodicamente il sito dell'ANSA
```html
<!DOCTYPE html>
<html>
	<body>
		<iframe id="area" height="2000" width="1000"></iframe>
		<script>
			function displayHello() {
			document.getElementById("area").src = "https://www.ansa.it/sito/notizie/topnews/index.shtml";
			}
			displayHello;
			setInterval(displayHello, 5000);
		</script>
	</body>
</html>
```
### [[2026/Web/web-webservices.pdf#page=29&selection=2,0,2,22&color=note|Un semplice web server]]
Se provo ad avviare [[2026/Web/web/serverHTTP.c|serverHTTP]] su due terminali diversi il secondo non si avvia perché il server è TCP e, come detto nei capitoli precedenti la porta è già occupata dal primo server.
Quando faccio `http://127.0.0.1:8000/` sul browser mi compare la pagina bianca con scritto `Hello World, this is a very simple HTML document.`.
Sul terminale invece esce questo:
```
Accept-Encoding: gzip, deflate, br, zstd
Connection: keep-alive
Referer: http://localhost:8000/
Sec-Fetch-Dest: image
Sec-Fetch-Mode: no-cors
Sec-Fetch-Site: same-origin
Priority: u=6

[SERVER] sessione HTTP completata
```
Se invece imposto l'URL `http://localhost:8000/` il risultato non cambia.
### [[2026/Web/web-webservices.pdf#page=31&selection=2,0,2,9&color=note|Esercizio]]
Quando apro [[2026/Web/web/form-get.html|form-get.html]] vedo la pagina html in locale.
NB: L'indirizzo è il path del file e non un URL
<p style="text-align:center;"><code>file:///home/.../web/form-get.html</code></p>
All'invio del form viene aperta una pagina nuova con URL:
<p style="text-align:center;"><code>http://localhost:8000/action?fname=David&lname=Zahariev</code></p>
ovvero la pagina localhost che viene caricata da [[2026/Web/web/serverHTTP.c|serverHTTP]] con attributi `fname` e `lname` impostati a `David Zahariev`.
Seguendo il flusso TCP di Wireshark vediamo:
<p style="text-align:center;"><img src="Img/wireshark-01.png" alt="wireshark-01.png" width="600"/></p>
In formato testuale:

```
GET /action?fname=David&lname=Zahariev HTTP/1.1
Host: localhost:8000
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:149.0) Gecko/20100101 Firefox/149.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: it,en-US;q=0.9,en;q=0.8
Accept-Encoding: gzip, deflate, br, zstd
Connection: keep-alive
Upgrade-Insecure-Requests: 1
Sec-Fetch-Dest: document
Sec-Fetch-Mode: navigate
Sec-Fetch-Site: cross-site
Sec-Fetch-User: ?1
Priority: u=0, i
```
### [[2026/Web/web-webservices.pdf#page=34&selection=2,0,2,9&color=note|Esercizio]]
Nel caso di [[2026/Web/web/form-post.html|form-post.html]] la visione dell'utente non cambia da form-get.html.
Quello che vede Wireshark è:
<p style="text-align:center;"><img src="Img/wireshark-02.png" alt="wireshark-02.png" width="600"/></p>
In formato testuale:

```
POST /action HTTP/1.1
Host: localhost:8000
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:149.0) Gecko/20100101 Firefox/149.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: it,en-US;q=0.9,en;q=0.8
Accept-Encoding: gzip, deflate, br, zstd
Content-Type: application/x-www-form-urlencoded
Content-Length: 26
Origin: null
Connection: keep-alive
Upgrade-Insecure-Requests: 1
Sec-Fetch-Dest: document
Sec-Fetch-Mode: navigate
Sec-Fetch-Site: cross-site
Sec-Fetch-User: ?1
Idempotency-Key: "17835255686423549233"
Priority: u=0, i

fname=David&lname=Zahariev
```
### [[2026/Web/web-webservices.pdf#page=36&selection=2,0,2,9&color=note|Esercizio]]
Modifiche fatte a [[2026/Web/web/serverHTTP.c|serverHTTP.c]]. Il suo funzionamento è: nell'URL cerca e invia con protocollo HTTP il nome del file che viene dopo `/`. Esempio: `localhost:8000/css.html`, il server restituisce la pagina `css.html` caricandola nel browser.
Se provo a chiedere le pagine form-get.html e form-post.html vengono restituite tranquillamente.