**Nginx** è un [[Web server|web server]] ad alte prestazioni multipiattaforma sviluppato con l'obiettivo di gestire più di 10000 connessioni contemporaneamente senza osservare un decadimento delle prestazioni.

Può agire da: web server, **reverse proxy**, proxy, e-mail proxy, **load balancer**.
>Negli ultimi anni il tasso di adozione è rapidamente aumentato con l'avvento delle applicazioni progettata secondo il paradigma a microservizi.

I file di **configurazione** si trovano nella directory `/etc/nginx`, tra cui il file principale `nginx.conf` il quale è composto da opzioni chiamate:
- **Direttive** se contengono un solo valore (e.g. `worker_processes 1;`)
- **Blocchi (server block o contesto)** se contengono più direttive
```
server {
 listen 80 default_server;
 server_name miosito.com www.miosito.com;
 root /var/www/miosito.com;
 index index.html;
 try_files $uri /index.html;
}
```

Nginx verrà eseguito come daemon con l'**utente nginx**, e come Apache si metterà in ascolto sulla porta 80 servendo file statici presenti all'interno di `/var/www/html`.

Il concetto di **server block (contesto)** è simile a quello del **virtual hosting** di Apache, quindi per ospitare più siti all'interno del server web gestito con nginx è sufficiente creare più _server blocks_ all'interno di `nginx.conf`.

Oppure in modo più ordinato si possono creare tanti file in `/etc/nginx/sites-available` quanti sono i siti da ospitare, usando nomi significativi e abilitandoli in `/etc/nginx/sites-enable`.

Per abilitare **ssl** è sufficiente specificare la direttiva all'interno del server block, inoltre sarà necessario specificare i file contenenti certificato e chiave privata con le direttive `ssl_certificate` e `ssl_certificate_key`.
```
erver {
	listen 80;
	listen 443 ssl;
	server_name www.miosito.com;
	ssl_certificate miosito.com.crt;
	ssl_certificate_key miosito.com.key;
	}
```

### Reverse proxy
Un [[HTTP#Server proxy|reverse proxy]] è un server web che si intrapone tra client e server effettivo, esso reindirizzerà la richiesta del client al server effettivo (fungendo da client) e poi la risposta del server farà il percorso inverso.
```
# richiesta
client -> reverse proxy -> server

# risposta
server -> reverse proxy -> client
```

Un reverse proxy trova applicazione in vari contesti, tra cui:
- Le risorse di un applicativo sono servite da più server, ma si vuole accedere a quest'ultime da un dominio comune
- Nel caso esista una pool di web server che forniscono gli stessi servizi può funzionare come load balancer per distribuire il carico fra i server
- Dotare di supporto TLS un'applicazione che ne è sprovvista

La configurazione come reverse proxy avviene semplicemente specificando una **location** con la direttiva `proxy_pass`:
```
location /my/location/ {
	proxy_pass http://www.mioappsweb.it:5001/link/;
}
```

Tramite la direttiva `proxy_set_header` si possono personalizzare gli header inviati al server, ad esempio si può prevenire una risposta compressa al client:
```
location /my/location/ {
	proxy_set_header Accept-Encoding "";
	proxy_pass http://www.example.com/link/;
}
```

### Load balancer
Il **bilanciamento del carico** di un applicativo su più istanze è una tecnica usata per:
- Ottimizzare l'utilizzo delle risorse
- Massimizzare il throughput
- Ridurre la latenza di risposta
- Garantire resilienza in caso di guasti

Le **modalità** di load balancing sono:
- **Round-robin**: le richieste vengono distribuite in sequenza ciclica
- **Least-connected**: ogni richiesta è assegnata al server con meno connessioni attive in quel momento
- **IP-hash**: viene utilizzata una funzione hash per mappare indirizzo IP del client all'identificativo del server che gestirà la richiesta

La direttiva `upstream` viene aggiunta alla configurazione già vista per un reverse proxy, per utilizzare il **round-robin**.
```
http {
	upstream myapp1 {
		server srv1.miaapp.com;
		server srv2.miaapp.com;
		server srv3.miaapp.com;
	}
	server {
		listen 80;
		location / {
			proxy_pass http(s)://miaapp.com;
		}
	}
}
```


Per attivare la modalità **least-connected** basta aggiungere la direttiva `least_conn` nel gruppo `upstream`.
```
http {
	upstream myapp1 {
		least_conn;
		server srv1.miaapp.com;
		server srv2.miaapp.com;
		server srv3.miaapp.com;
	}
	server {
		listen 80;
		location / {
			proxy_pass http(s)://miaapp.com;
		}
	}
}
```

Dato che HTTP è un protocollo **stateless**, per evitare che richieste consecutive di un client vengano mappate in un server diverso dopo il processo di load balancing, e quindi per evitare problemi di sessione (e.g. cookie) , viene utilizzato `upstream` specificando al suo interno la direttiva `ip_hash`.
```
http {
	upstream myapp1 {
		ip_hash;
		server srv1.miaapp.com;
		server srv2.miaapp.com;
		server srv3.miaapp.com;
	}
	server {
		listen 80;
		location / {
			proxy_pass http(s)://miaapp.com;
		}
	}
}
```

Volendo è anche possibile specificare dei **pesi**, tramite la direttiva `weight`, in modo da distribuire il carico in modo consono alle capacità di elaborazione dei server.

Supponiamo che il server 3 sia in grado di gestire il doppio delle richieste degli altri due, allora avremo:
```
http {
	upstream myapp1 {
		ip_hash;
		server srv1.miaapp.com;
		server srv2.miaapp.com;
		server srv3.miaapp.com weight=2;
	}
	server {
		listen 80;
		location / {
			proxy_pass http(s)://miaapp.com;
		}
	}
}
```

Se un application server non risponde correttamente alle richieste, esso verrà marcato come **non funzionante** e <u>nginx non lo selezionerà per le richieste successive</u>.

Tramite la direttiva `max_fails` (default 1), si specifica il numero di tentativi prima di considerare l'application server non funzionante, mentre con `fail_timeout` si vanno ad effettuare dei controlli periodici sui server non funzionanti.
