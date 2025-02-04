Nel modello a [[HMAC#Crittografia a chiave simmetrica|chiave simmetrica]] Alice e Bob devono condividere una chiave in un canale sicuro e poi saranno in grado di comunicare in un canale non necessariamente sicuro.

Con la **crittografia a chiave pubblica** Alice e Bob possono comunicare in modo sicuro anche senza scambiarsi alcuna informazione segreta.

**Intrattabilità della fattorizzazione di numeri grandi**.
Al momento non esiste alcun algoritmo polinomiale in grado fattorizzare grandi numeri, questo vuol dire che se $m=p\cdot q$ dove $p,q$ sono **numeri primi**, e $m$ è formato da $l$ cifre, non esiste alcun algoritmo in grado di recuperare $p$ e $q$ in al più $l^k$ operazioni per qualche $k$.

**Intrattabilità del logaritmo discreto**.
Al momento non esiste alcun algoritmo polinomiale in grado di trovare un logaritmo discreto di un numero, ciò significa che dati $g,n,m$ interi e $g^a\mod_n=m$ non esiste alcun algoritmo polinomiale in grado di invertire l'esponenziazione per trovare $a$.

## Diffie-Hellman
Il protocollo Diffie-Hellman (DH) consente ad Alice e Bob di negoziare un chiave simmetrica segreta senza condividere informazioni segrete, esso è basato sulla difficoltà di calcolare un logaritmo discreto.

1. Alice sceglie un numero primo $n$, un numero casuale $a$, una [radice primitiva modulo n](https://en.wikipedia.org/wiki/Primitive_root_modulo_n) $g$
2. Bob genera un numero casuale $b$ ($a$ è $b$ sono segreti e non verranno mai inviati da Alice o Bob)
3. Alice manda $m=g^a\mod_n,g,n$ a Bob
4. Bob manda $r=g^b\mod_n$ ad Alice
5. La chiave generata è $K=g^{ab}\mod_n$

Se Eve intercettasse il traffico potrebbe venire a conoscenza di $m,g,n,r$, ma data l'intrattabilità del logaritmo discreto non potrà ottenere $a$ o $b$.

Se Eve oltre a poter intercettare il traffico potesse anche modificarlo, potrebbe far credere ad Alice di parlare con Bob e viceversa, quando in realtà stanno passando attraverso Eve.
L'algoritmo DH garantisce **confidenzialità** soltanto se usato con qualche altro strumento che garantisce l'**autenticazione**.

## RSA
I principi della crittografia a chiave pubblica, ovvero a **chiave asimmetrica** sono:
- Alice e Bob hanno due chiavi ciascuno
- Alice possiede la chiave pubblica $pub\_a$ ed una chiave privata $priv\_a$
- Bob possiede la chiave pubblica $pub\_b$ ed una chiave privata $priv\_b$

Le **chiavi private** devono rimanere **segrete**, le chiavi **pubbliche** possono essere **condivise ovunque**.

Ciò che è criptato con una chiave pubblica può solo essere decriptato con la chiave privata corrispondente.
![[Chiave asimmetrica.png]]

Il vantaggio più grande rispetto ad un modello con chiave simmetrica è che non è necessario un canale sicuro per accordarsi su una chiave condivisa.

L'algoritmo di **Rivest, Shamir, Adelmann (RSA)** è il seguente:
- Vengono scelti due numeri primi grandi $p,q$ i quali non devono mai essere rivelati
- Viene calcolato $n=pq$ e la [funzione di eulero](https://en.wikipedia.org/wiki/Euler%27s_totient_function) $\phi(n)=(p-1)(q-1)$
- Viene scelto un intero $e$ tale che $2<e<\phi(n)$ che è coprimo con $\phi(n)$
- Viene poi calcolato $d$ in modo tale che $de\mod_{\phi(n)}=1$
	ovvero $d$ ed $e$ sono inversi in modulo $\phi(n)$

La **chiave pubblica** è $(e,n)$, mentre la **chiave privata** è $d$.
>Chiave pubblica e privata vengono generate nello stesso momento, sono un risultato di un singolo algoritmo matematico.

Se Bob vuole **mandare** un messaggio $M$ ad Alice lo **cripterà** come: $$C=M^e\mod_n$$

Alice una volta **ricevuto** il messaggio da **Bob** lo decripterà come:
$$M=C^d\mod_n$$

>[!Example]
>Prendiamo $p=7$, $q=11$, $n=77$, $\phi(n)=60$.
>Scegliamo $e=13$ che è un numero primo ed è coprimo con $60$.
>Dobbiamo trovare $d$ per cui $(d\cdot13)\mod_{60}=1$, esiste un algoritmo efficiente ma per numeri piccoli basta ciclare valori interi per $d$.
>Viene fuori che $d=37$, assumiamo poi che $M=00010100$, il quale convertito in base decimale è pari a $M=20$, abbiamo quindi:
>$$C=20^{13}\mod_{77}=69\quad\leftarrow\text{Encryption}$$
>$$M=69^{37}\mod_{77}=20\quad\leftarrow\text{Decryption}$$

Le proprietà di uno schema con **chiave asimmetrica** (e.g. RSA) sono:
- È facile calcolare la coppia di chiavi pubblica e privata
- Data la chiave pubblica è facile criptare un messaggio
- Data la chiave privata è facile decriptare un messaggio criptato con la analoga chiave pubblica
- Data solo la chiave pubblica è impossibile calcolare la sua chiave privata
- Data la chiave pubblica ed il messaggio criptato da essa è impossibile derivare il messaggio originale

>Chiavi lunghe almeno $1024$ bit rendono impossibile a Eve derivare $p,q$, computare $\phi(n)$ ed invertire $de\mod_{\phi(n)}$ a causa dell'intrattabilità della fattorizzazione di numeri grandi.

### Limiti della crittografia asimmetrica
Se Eve controlla il canale può scambiare la chiave pubblica di Bob con la sua chiave pubblica, per poi decifrare il messaggio di Alice (che doveva andare a Bob) per poi inoltrarlo a Bob, discorso analogo da Bob ad Alice, in questo modo Eve può vedere tutto il traffico ed impersonare Alice e Bob.

In uno schema a **chiave simmetrica** serve un canale sicuro che garantisca: autenticità, integrità e **segretezza**, mentre in uno schema a **chiave asimmetrica** non serve un canale che garantisca **segretezza** in quanto vengono usate chiave pubbliche disponibili a tutti.

### Firma digitale
È possibile invertire l'utilizzo delle chiavi per generare una **firma digitale**, per firmare un documento Alice lo si cripterà utilizzando la propria **chiave privata**, tutte le persone che possiedono la **chiave pubblica** di Alice potranno decriptarlo correttamente per capire che effettivamente è stata Alice a criptarlo garantendo quindi **autenticità** ad un messaggio.

Quando un documento è firmato digitalmente, esso **non è ripudiabile**, ovvero Alice non potrà negare di essere l'origine di tale documento.

Se Eve controlla il canale potrà comunque controllare il traffico durante lo scambio delle chiavi pubbliche, ci si aspetta che la chiave pubblica di un ente importante sia messa in mostra in un posto sicuro ed attendibile.

| Chiave simmetrica                                          | Chive asimmetrica                                                         |
| ---------------------------------------------------------- | ------------------------------------------------------------------------- |
| **Fornisce**:<br>segretezza, integrità, autenticazione<br> | **Fornisce**:<br>segretezza, integrità, autenticazione, non ripudiabilità |
| **Necessita un canale**:<br>segreto, autenticato, integro  | **Necessità di un canale**:<br>autenticato, integro                       |

### RSA performance
La criptazione è più veloce della decriptazione.

Bisogna ricordare che $de\mod_{\phi(n)}=1$ e quindi $de=k\cdot\phi(n)+1$ per qualche $k$, e quindi $\phi(n)$ deve essere un numero grande, per cui se $e$ è piccolo $d$ deve essere grande (o il contrario).
>$d$ deve essere grande perchè deve essere un segreto e quindi difficile da indovinare, quindi $e$ volendo può essere piccolo.

Quindi il server che decripta il traffico ha bisogno di più risorse del client che le cripta.

**Modalità mista**
Normalmente quindi si evita di criptare/decriptare dati con RSA, lo si usa solo per comunicare una chiave condivisa la quale utilizzerò poi l'[[HMAC]].

**Firma degli hash**
Sempre per motivi di performance, quando si vuole firmare un documento grande, si firma solo il suo hash per fare prima.

