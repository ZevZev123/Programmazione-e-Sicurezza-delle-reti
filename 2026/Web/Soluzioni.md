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
form-get.html