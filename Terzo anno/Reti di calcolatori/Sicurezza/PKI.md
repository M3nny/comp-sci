Una **chiave** è rappresentata da un file contenente una **stringa casuale**, durante la generazione di una chiave non è possibile decidere il suo contenuto, per questa ragione il file contiene alcuni **meta-dati** che comprendono: nome, email e altre informazioni.

Tuttavia questo ancora <u>non garantisce che la chiave sia stata creata da chi dice di averla creata</u>.

Esistono vari metodi per associare una chiave ad una entità.

### Fingerprint
Un metodo _informale_ è quello di pubblicare la propria chiave pubblica su un proprio profilo social, quando Bob riceverà la chiave pubblica di Alice guarderà il suo profilo social per vedere se combacia, questa tecnica tuttavia non scala bene.

### Key servers
Esistono server che permettono l'upload della propria chiave pubblica assieme ad altre informazioni (e.g. email), tuttavia non sono responsabili dell'associazione tra chiave ed utente, servono solo per avere un posto di riferimento per molte chiavi pubbliche (una specie di motore di ricerca).

### Web of Trust (WoT)
Un WoT è un social network di contatti attraverso il quale i partecipanti si certificano a vicenda.
Se Alice e Bob si fidano di Carl ciò vuol dire due cose:
- Possiedono la sua chiave pubblica
- Si fidano che Carl non si comporti male, quindi se lui certifica qualcosa Alice e Bob credono che sia vero

Carl può fare da intermediario e dire a Bob che la chiave pubblica di Alice appartiene effettivamente a lei.
1. Alice e Carl si trovano per scambiarsi le _fingerprint_ lo stesso per Bob e Carl
2. Carl cripta la chiave pubblica di Alice assieme al suo nome con la sua chiave privata
3. Tutte le persone che hanno la chiave pubblica di Carl possono decriptare tale firma digitale e vedere che la chiave pubblica di Alice appartiene ad una persona che si chiama Alice
4. Se si fidano di Carl anche loro si fideranno dell'autenticità di Alice

In questo modo possono formarsi delle **catene di fiducia**:
![[Trust chain.png]]

La cosa importante è che viene creato un **grafo orientato tra le persone**, finchè esiste un cammino di fiducia tra Alice e Bob essi possono comunicare in modo sicuro perchè qualcuno certifica la loro autenticità.

La WoT sebbene sia un metodo informale introduce concetti come la firma delle chiavi, delegazione della fiducia ed il concetto di fiducia asimmetrica.

## Public Key Infrastructure
Una PKI è un'infrastruttura in cui esiste un'entità che è **fidata da tutti**, tutti hanno la chiave pubblica di tale entità.
In gergo tecnico essa è una **Certification Authority (CA)**.

Alice può chiedere alla CA di firmare la sua chiave, quando Bob riceverà la chiave pubblica di Alice controllerà se è stata firmata dalla CA, se ciò è vero allora Bob si fiderà dell'autenticità di Alice.
Una chiave firmata è detta **certificato**.

#### Ottenere un certificato
Il processo per ottenere un certificato è il seguente:
1. Alice genera una coppia di chiavi
2. Alice crea un **Certificate Signing Request (CSR)** il quale è un file contenente $pub\_A$ e informazioni riguardanti Alice
3. Il CSR è firmato (l'hash del doumento) con $priv\_A$ (viene scritta la funzione di hashing usata)
4. Alice manda il CSR alla CA
5. La CA controlla l'identità (Alice dovrà mostrare dei documenti)
6. La CA ritorna un certificato valido, ovvero il CSR con la firma digitale della CA aggiunta

Questo processo è eseguito una volta per periodo di validità, inoltre una volta che il certificato è consegnato, la CA non è più un bottleneck.

#### Verificare un certificato
Quando Bob riceve un certificato valido da Alice firmato da una CA:
1. Controlla che il nome riportato nel certificato è quello di Alice
2. Controlla se il certificato è ancora valido
3. Controlla se il certificato è emanato da una CA di cui lui si fida
4. Decripta la firma digitale con la chiave pubblica della CA e ottiene un digest $D$ del certificato
5. Computa un hash del certificato $D'$ (esclusa la firma) e controlla se $D=D'$
6. Se dovesse essere vero allora Bob ora si fida della chiave pubblica di Alice

#### Albero di CA
Le CA possono firmarsi i certificati a vicenda creando così una **web of trust**, la **root CA** firma il suo stesso certificato.
![[Certificate chain.png]]

Quando Bob visita `www.alice.com`, il webserver di Alice deve fornire tutta la catena di certificati fino ad una root CA, Bob avendo la firma della root CA controllerà tutta la catena di certificati fino a `www.alice.com`.
>La fiducia anche in questo caso è asimmetrica, il webserver non sa nulla del browser, esso si potrà identificare con un nome utente e password.

#### Certificate Revocation List
Se per qualche motivo dovesse succedere qualcosa alla chiave privata della CA, essa dovrà **ritirare i certificati** emanati.
Una CA espone anche una **Certificate Revocation List (CRL)** che contiene tutti i certificati revocati.

### Organizzazione di una CA
Organizzare una CA è complesso (possono essere anche interne ad aziende), prendiamo come caso di studio [let's encrypt](https://letsencrypt.org/it/certificates/), è una CA che utilizza due root, e quindi due alberi distinti, il primo firma i certificati con [[Crittografia a chiave pubblica#RSA|RSA]], mentre il secondo utilizza le [curve ellittiche](https://blog.cloudflare.com/a-relatively-easy-to-understand-primer-on-elliptic-curve-cryptography/).
![[Gerarchia let's encrypt.png]]
