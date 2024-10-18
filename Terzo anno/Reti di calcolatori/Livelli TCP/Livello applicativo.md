Le applicazioni sono diverse tra loro quindi è difficile trovare uno standard, il **livello applicativo** quindi deve specificare la **sintassi e semantica** delle informazioni che sono richieste ed inoltrate.

Il testo generalmente è codificato usando [UTF-8](https://en.wikipedia.org/wiki/UTF-8), tuttavia è sempre richiesto specificare l'encoding.

I processori moderni utilizzano in maggior parte il sistema **little-endian**, però internet ha deciso di utilizzare **big-endian** (vedi [endianess](https://en.wikipedia.org/wiki/Endianness)), è quindi importante convertire i dati prima di riceverli e trasmetterli.

## Domain names
È più facile utilizzare un nome piuttosto che un indirizzo per identificare un host, è necessario però che qualcuno traduca il nome in un indirizzo, inizialmente ciò era fatto da un'unica entità, poi si è dovuto scalare.

Un **nome di dominio** è gerarchico, con la gerarchia che cresce da sinistra verso destra (rispetto al nome), ad esempio in `www.unive.it` il **Top Level Domain (TLD)** è `it` ed essi sono noti, mentre `unive` è affittato da un ente.

1. Il client ha bisogno di comunicare con `www.unive.it`
2. Il client in automatico contatterà il server $X$ responsabile per il dominio `.it`
3. $X$ risponderà che $Y$ è il responsabile
4. Il client allora chiederà a $Y$ chi è il responsabile per `unive.it`
5. $Y$ risponderà che $Z$ ha indirizzo $Z$
6. Il client ora potrà inoltrare i pacchetti all'indirizzo $Z$

>La profondità di una gerarchia DNS non è definita.
