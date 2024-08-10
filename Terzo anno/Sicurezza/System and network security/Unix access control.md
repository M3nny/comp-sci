La **protezione degli accessi** protegge le risorse del sistema da accessi non autorizzati.

### Access control policies
Dopo essersi [[Identification|identificati]], si è soggetti a delle **policy di sicurezza** che limitano le azioni che possono essere eseguite:
- **Discretionary access control (DAC)**: basata sull'identità del richiedente e sulle sue _regole di accesso_ (autorizzazioni), viene chiamata _discretionary_ perchè un'entità potrebbe abilitarne un'altra ad accedere ad alcune risorse
- **Mandatory access control (MAC)**: le _label_ di sicurezza indicano quanto è sensibile una risorsa, mentre le _autorizzazioni_ di sicurezza indicano il livello di accesso delle entità del sistema, viene chiamata _mandatory_ perchè un'entità che ha l'autorizzazione per accedere ad una risorsa potrebbe non riuscire a dare quei permessi ad un'altra entità su una determinata risorsa
- **Role-based access control (RBAC)**: basata sui _ruoli_ che gli utenti hanno nel sistema e sulle regole che determinano le autorizzazioni dei ruoli
- **Attribute-based access control (ABAC)**: basata sugli attributi dell'utente e dalle condizioni di _environment_ attuali (e.g. l'accesso ad un film potrebbe dipendere dal tipo di abbonamento)


Un **soggetto** è un'entità capace di accedere a risorse (oggetti)
- Qualsiasi utente o applicazione accede ad un oggetto tramite un _processo_
- Il processo eredita gli attributi dell'utente, tra cui i suoi diritti d'accesso

Un **oggetto** è una risorsa il cui accesso è controllato, esso è un'entità usata per contenere e/o ricevere informazioni.

### Diritti d'accesso
- **Read**: vedere le informazioni, copiarle e stamparle
- **Write**: aggiungere, modificare o cancellare informazioni in un oggetto
- **Execute**: eseguire un oggetto (e.g. programma)
- **Delete**: cancellare l'oggetto
- **Create**: creare un oggetto
- **Search**: cercare all'interno di un oggetto (e.g. tramite una query)
>Un diritto di accesso potrebbe implicarne un altro (e.g. _read_ $\rightarrow$ _search_)

---
## Controllo degli accessi
**Access matrix**: diritti di accesso per ogni _soggetto_ (riga) e _oggetto_ (colonna):

|           | README.txt  | /bin/bash            |
| --------- | ----------- | -------------------- |
| **Alice** | Read, Write | Read, Write, Execute |
| **Bob**   | Read        | Read, Execute        |

**Access Control List (ACL)**: per ogni oggetto elenca i soggetti ed i loro diritti di autorizzazione (decomposizione per colonne)
- Facile trovare quali soggetti hanno accesso ad un certo oggetto
- Difficile trovare i diritti di accesso per un certo soggetto
>e.g. `README.txt: {Alice: [Read, Write], Bob: [Read]}`

**Capabilities**: per ogni soggetto elenca gli oggetti ed i diritti di accesso ad essi (decomposizione per righe)
- Facile trovare i diritti di accesso per un determinato soggetto
- Difficile trovare quali soggetti hanno accesso ad un certo oggetto
>e.g. `Alice: {README.txt: [Read, Write], /bin/bash: [Read, Write, Execute]}`

### Unix Access Control
Il **kernel** unix ha accesso a tutto il sistema, tutti i soggetti si interfacciano con il _kernel_ per accedere agli oggetti.

L'accesso è deciso in base a **userid/groupid** dell'oggetto e allo **userid/groupid** del soggetto.
>È una forma semplificata di **ACL**.

L'utente **root** possiede userid=0 e l'accesso alle risorse è sempre garantito dal kernel.

**Creazione di un nuovo utente**:
```bash
root[~] id # display information about user and groups
uid=0(root) gid=0(root)
groups=0(root),0(root),1(bin),2(daemon),3(sys),4(adm),6(disk),10(wheel),11(floppy),20(dialout),26(tape),27(video)

root[~] adduser -D alice # creates new user alice with no password

# change alice’s password to ‘alice’
root[~] echo 'alice:alice' | chpasswd 
chpasswd: password for 'alice' changed

root[~] su - alice # switches to user alice
alice[~]$ id # display information about user and groups
uid=1000(alice) gid=1000(alice) groups=1000(alice)
```

**Creazione di un nuovo gruppo**:
```bash
root[~] addgroup student # create group student
root[~] usermod -a -G student alice # alice is in group student

root[~] id alice
uid=1000(alice) gid=1000(alice) groups=1000(alice),1001(student)

root[~] adduser -D bob; echo 'bob:bob' | chpasswd

# both alice and bob are in group student
root[~] usermod -a -G student bob 
root[~] id bob
uid=1002(bob) gid=1002(bob) groups=1002(bob),1001(student)
```

I permessi dei file sono composti da **3 triadi** che definiscono i permessi del **proprietario**, **gruppo** e degli **altri utenti**:
- **r**: il file può essere letto, il contenuto della cartella può essere visto
- **w**: il file può essere modificato, i contenuti della cartella possono essere modificati
- **x**: il file può essere eseguito, la cartella può essere attraversata
- **s**: il file è **SUID** (**SGID** se _s_ è nella triade del gruppo), implica _x_
```bash
alice[~]$ ls -al
drwxr-sr-x 2 alice alice 4096 Nov 3 17:14 .
```

**Gestire i permessi**: è possibile usare `chmod` per cambiare i permessi dei file, è possibile specificare un numero come opzione, esso viene interpretato in base $8$, ogni cifra corrisponde ai $3$ bit di permessi.
```bash
chmod 600 myfile
# rw-------
# 6 -> 110 -> rw-
# 0 -> 000 -> ---
# 0 -> 000 -> ---
```

Il proprietario ed il gruppo possono essere modificati con `chown`, gli utenti non root tuttavia possono cambiare solo il gruppo a cui appartengono, ma non chi è il proprietario.
```bash
chown alice:student myfile
# cambia il gruppo a student, ok se alice è nel gruppo stuedent
```

**SUID**: quando _s_ appare al posto di _x_ nella triade del proprietario, il programma verrà eseguito con i privilegi del proprietario.
>e.g. utility di sistema che richiede permessi root, come `/bin/su`.

>[!Attention]
>SUID è rischioso in quanto una vulnerabilità potrebbe garantire root access all'attaccante.

**SGID**: quando _s_ appare al posto di _x_ nella triade del gruppo, il programma verrà eseguito con i privilegi del gruppo.
Quando una cartella ha _SGID_ impostato, allora tutti i file o cartelle _creati_ all'interno di quella cartella saranno di proprietà dello stesso gruppo _SGID_.
SGID lascia accedere il programma ai file con i permessi ereditati dal gruppo, esempio:
```bash
root[~] cd /tmp/Challenge2/
root[/tmp/Challenge2] ./pwdChallenge
Insert password: AAAAAAAAAAAAAAA
Authenticated!

root[/tmp/Challenge2] cat pwd.txt
AAAAAAAAAAAAAAA

root[/tmp/Challenge2] ls -al
total 28
drwxr-xr-x 1 root root 4096 Nov 3 21:53 .
drwxrwxrwt 1 root root 4096 Nov 3 21:53 ..
-rw------- 1 root root 15 Nov 3 17:59 pwd.txt
-rwx------ 1 root root 13128 Mar 26 2020 pwdChallenge

root[/tmp/Challenge2] addgroup challenge
root[/tmp/Challenge2] chown root:challenge pwd*
root[/tmp/Challenge2] ls -al
total 36
drwxr-xr-x 1 root root 4096 Nov 3 21:53 .
drwxrwxrwt 1 root root 4096 Nov 3 21:53 ..
-rw------- 1 root challenge 15 Nov 3 17:59 pwd.txt
-rwx------ 1 root challenge 13128 Mar 26 2020 pwdChallenge

root[/tmp/Challenge2] chmod 2755 pwdChallenge
root[/tmp/Challenge2] chmod 640 pwd.txt
root[/tmp/Challenge2] ls -al
total 36
drwxr-xr-x 1 root root 4096 Nov 3 21:53 .
drwxrwxrwt 1 root root 4096 Nov 3 21:53 ..
-rw-r----- 1 root challenge 15 Nov 3 17:59 pwd.txt
-rwxr-sr-x 1 root challenge 13128 Mar 26 2020 pwdChallenge

root[/tmp/Challenge2] su - alice
alice[~]$ cd /tmp/Challenge2/
alice[/tmp/Challenge2]$ ./pwdChallenge
Insert password: AAAAAAAAAAAAAAA
Authenticated!

alice[/tmp/Challenge2]$ cat pwd.txt
cat: pwd.txt: Permission denied
```


Nelle cartelle condivise come `/tmp` è utile dare pieno accesso a qualsiasi utente, ciò però vuol dire che un utente può cancellare file che non sono suoi.
Quando _t_ appare al posto di _x_ nella triade degli "altri utenti" la cartella proibisce agli utenti di cancellare i file che non possiedono.
I permessi in `/tmp` solitamente hanno la seguente struttura:
```bash
drwxrwxrwt 1 root root
```

### ACL, Capabilities e privilege drop
Le **ACL** definiscono permessi differenti sulla base di utenti e gruppi, hanno una priorità superiore rispetto ai permessi Unix.

**Linux capabilities**: al posto dei permessi SUID, assegna solo le capabilities root che sono necessarie per eseguire quell'operazione amministrativa.

Si parla di **privilege drop** quando un processo inizia con privilegi elevati (e.g. root) per eseguire operazioni che richiedono tali privilegi, dopo aver completato queste operazioni il processo riduce i propri privilegi per il resto della sua esecuzione, solitamente va fatto usando `setuid()`.

`setuid()`: cambia l'id utente reale, ovvero l'identità dell'utente che ha avviato il processo, questa operazione è "one-way" ovvero una volta che l'user id è ritornato ad essere quello reale, non potrà più essere root.

```c
int show_uid() {
	printf("Effective user id is: %d\n",geteuid());
	printf("Real user id is: %d\n",getuid());
	return getuid(); // returns the real user id
}

int main () {
	int myuid;
	myuid = show_uid();
	
	printf("[-] Trying to open shadow file (need to be root)\n");
	if( open("/etc/shadow",O_RDONLY) < 0 )
		die("Failed to open shadow");
	
	printf("[-] Trying privilege drop\n");
	if ( setuid(myuid)<0 )
		die("Failed to set original uid\n");
		
	show_uid();
	
	printf("[-] Checking that shadow cannot be opened\n");
	if( open("/etc/shadow",O_RDONLY) >= 0)
		die ("I could open shadow?");
		
	printf("[-] Trying to set back uid 0 (root)\n");
	if ( setuid(0)<0 )
		die("Failed to set root uid");
		
	show_uid();
	
	printf("[-] Trying to open shadow file (need to be root)\n");
	if( open("/etc/shadow",O_RDONLY) < 0 )
		die("Failed to open shadow");
}
```

```bash
alice[/tmp]$ ls -al /tmp/privilegeDropTest
-rwsr-xr-x 1 root root 12864 Nov 3 21:10 /tmp/privilegeDropTest

alice[/tmp]$ ./privilegeDropTest
[*] Effective user id is: 0
[*] Real user id is: 1000
[-] Trying to open shadow file (need to be root)
[*] Done!
[-] Trying privilege drop
[*] Done!
[*] Effective user id is: 1000
[*] Real user id is: 1000
[-] Checking that shadow cannot be opened
[*] Done!
[-] Trying to set back uid 0 (root)
[=] ERROR: Failed to set root uid: Operation not permitted
```