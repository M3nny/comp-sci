La difesa degli host va eseguita per ogni sistema operativo, mentre la difesa della rete attraverso **firewall** può proteggere tutti i sistemi da una gran parte di attacchi.

Un esempio di configurazione di rete potrebbero essere tre **subnet**: sensitive, trusted e untrusted, dove internet viene raggiunto solo da untrusted.

### Operazioni del firewall
- **Forward**: invio di pacchetti da una subnet ad un'altra
- **Drop**: pacchetti rifiutati da una subnet ad un'altra
- **Translate**: gli indirizzi dei pacchetti vengono _tradotti_ mentre sono consegnati

I pacchetti sono <u>accettati/rifiutati in base al loro</u>: **payload, indirizzo e porta** (sia in entrata e sia in uscita).
>Solitamente si accetta solo lo stretto necessario e quindi di default viene tutto scartato e si specifica solo cosa accettare.

La **traduzione** avviene attraverso il **Network Address Translation (NAT)** il quale è tipicamente necessario nella LAN con indirizzi IP privati.

**Source NAT**: il traffico uscente ha bisogno di un indirizzo IP pubblico sorgente
![[SNAT.png]]
`www.google.it` risponde a `157.138.7.88`, il firewall poi traduce automaticamente l'indirizzo di destinazione a `10.0.0.1`.

**Destination NAT**: il traffico entrante ha bisogno di un indirizzo IP pubblico di destinazione
![[DNAT.png]]
`10.0.0.1` risponde a `157.138.20.17`, il firewall poi traduce l'indirizzo sorgente in `157.138.7.88`.

>Il NAT è implementato trasparentemente negli [stateful firewall](https://en.wikipedia.org/wiki/Stateful_firewall)

---
## Netfilter
Netfilter è il tool standard per i firewall in Linux, consente:
- Filtraggio di pacchetti (tabella _filter_)
- NAT (tabella _nat_)
- Alterazione di pacchetti (tabella _mangle_)

Esso è configurato attraverso `iptables`, il quale utilizza tabelle per raggruppare regola in base alle azioni.

Le **catene** sono **liste di regole** che sono ispezionate sequenzialmente.
Se un pacchetto è conforme ad una regola allora esso viene processato in base al **rule target**, altrimenti viene esaminate la prossima regola nella catena, se un pacchetto non è conforme a nessuna regola allora viene attivata una **default policy**.

```bash
# -t specifica la tabella (filter di default)
# -L mostra la lista
iptables -t filter -L
Chain INPUT (policy ACCEPT)
target     prot opt source               destination

Chain FORWARD (policy ACCEPT)
target     prot opt source               destination

Chain OUTPUT (policy ACCEPT)
target     prot opt source               destination
```

È buona norma mettere la **default policy** a **DROP** e abilitare solo i pacchetti che volgiamo far passare.
Per non rimanere bloccati, prima di impostare la policy bisogna abilitare _ssh_ sia in input e sia in output:
```bash
# -A aggiunge la regola alla catena specificata
# -p tcp specifica il protocollo tcp
# -dport e -sport specificano la porta di destinazione e sorgente
# -j ACCEPT specifica il target ACCEPT
iptables -A INPUT -p tcp --dport 22 -j ACCEPT
iptables -A OUTPUT -p tcp --sport 22 -j ACCEPT
```

Ora è possibile impostare la policy DROP per ogni connessione in entrata:
```bash
iptables -P INPUT DROP
```
in questo modo qualsiasi pacchetto che non è diretto alla porta 22 (ssh) verrà scartato.

>[!Info] Come viene filtrato il traffico
>- Aggiungere _ora_ una regola che scarta i pacchetti verso la porta 22 sarebbe inutile in quanto prima troverà la regola che li accetta
>- È possibile mandare qualsiasi pacchetto in uscita, ma le risposte verranno scartate se non sono indirizzate alla porta 22

### Stateful filtering
Netfilter traccia le connessioni:
- Quando viene creata una nuova connessione i suoi pacchetti avranno stato **NEW**
- I pacchetti che appartengono alla stessa connessione hanno stato **ESTABLISHED**
- Alcuni protocolli (e.g. ftp) avviano nuove connessioni, questi pacchetti hanno stato **RELATED**
- Anche il NAT è tracciato
```bash
# sia ssh e sia i pacchetti ESTABLISHED vengono accettati
iptables -A INPUT -m state --state ESTABLISHED -j ACCEPT
```

Il DNAT è eseguito prima del routing:
```bash
# i pacchetti diretti a 157.138.7.88 vengono reindirizzati a
# 192.168.0.100:80
iptables -t nat -A PREROUTING -p tcp -d 157.138.7.88 --dport 80
-j DNAT --to-destination 192.168.0.100:80
```

### Mantenere una configurazione
Mantenere una configurazione è difficile in quanto:
- Non esiste una struttura fissa
- L'ordine è importante
- La semantica dipende dalla tabella e dalla catena
- Per scartare un pacchetto bisogna mettere tale regola prima di tutte le altre regole ACCEPT nella stessa catena