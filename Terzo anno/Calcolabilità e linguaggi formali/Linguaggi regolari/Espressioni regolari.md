Le **espressioni regolari (regex)** costituiscono un altro formalismo più compatto per descrivere linguaggi regolari, ad esempio:
$$\underbrace{(0\cup 1)}_\text{1.}\underbrace{\circ}_\text{2.}\underbrace{0^*}_\text{3.}$$
1. Scelta tra $0$ ed $1$
2. Concatenazione
3. Un numero arbitrario di $0$ consecutivi (anche nessuno volendo)

| Stanno nel regex | Non stanno nel regex |
| ---------------- | -------------------- |
| $0,1,00,100,...$ | $01,101,...$         |

Dato un alfabeto $\Sigma=\{a,b\}$, la notazione $\Sigma^*$ è definita come:
$$\Sigma^*\stackrel{\Delta}{=}(a\cup b)^*$$

Sia $\Sigma$ un alfabeto, l'insieme delle regex definite su $\Sigma$ è definito come segue:
1. Se $a\in\Sigma$, $a$ è una regex
2. $\epsilon$ è una regex
3. $\emptyset$ è una regex
4. Se $R_1$ e $R_2$ sono regex, allora $R_1\cup R_2$, $R_1\circ R_2$, $R_1^*$, $R_2^*$ sono regex

**Convenzioni**:
- L'operatore di concatenazione $\circ$ solitamente si elide, ovvero $R_1R_2=R_1\circ R_2$
- L'**ordine delle operazioni** è: $*\rightarrow\circ\rightarrow\cup$

Sia $R$ una regex, definiamo il suo linguaggio $L(R)$ come segue:
1. Se $R=a$, allora $L(R)=\{a\}$
2. Se $R=\epsilon$, allora $L(R)=\{\epsilon\}$
3. Se $R=\emptyset$, allora $L(R)=\emptyset$
4. Se $R=R_1\cup R_2$, allora $L(R)=L(R_1)\cup L(R_2)$
5. Se $R=R_1\circ R_2$, allora $L(R)=L(R_1)\circ L(R_2)$
6. Se $R=(R_1)^*$, allora $L(R)=(L(R))^*$
>Nota che le operazioni avvengono su operandi di tipo diverso, il simbolo $\cup$ nel primo caso indica una scelta, nel secondo caso l'unione insiemistica.

>[!Example]
>Si ipotizzi $\Sigma=\{0,1\}$.
>
>- $L(0^*10^*)=$ stringhe binarie con un solo $1$
>- $L(\Sigma^*1\Sigma^*)=$ stringhe binarie con almeno un $1$
>- $L(\Sigma^*\Sigma^*)=L(\{0\cup 1\}\circ \{0\cup 1\})^*=\{00,01,10,11\}^*=$ stringhe binarie di lunghezza pari (anche vuota)
>- $L(1^*\emptyset)=L(1^*)\circ L(\emptyset)=\emptyset$
>- $L(\emptyset^*)=(L(\emptyset))^*=\emptyset^*=\{\epsilon\}$

## Regolarità tramite regex
**Teorema**: un linguaggio $A$ è regolare sse esiste una regex $R$ tale che $L(R)=A$.

### Da regex a NFA
**Lemma**: sia $R$ una regex, allora $L(R)$ è regolare.
**Dimostrazione ($\Rightarrow$)**: per induzione sulla _struttura_ (numero di operatori) di $R$:
1. Sia $R=a$ per qualche $a$, allora $L(R)=a$
	dimostro che è regolare tramite l'NFA: $\rightarrow\bigcirc\stackrel{a}{\rightarrow}\circledcirc$
2. Sia $R=\epsilon$, allora $L(R)=\{\epsilon\}$
	dimostro che è regolare tramite l'NFA: $\rightarrow\circledcirc$
3. Sia $R=\emptyset$, allora $L(R)=\emptyset$
	dimostro che è regolare tramite l'NFA: $\rightarrow\bigcirc$
4. Sia $R=R_1\cup R_2$, allora $L(R)=L(R_1)\cup L(R_2)$, per ipotesi induttiva $L(R_1)$ e $L(R_2)$ sono regolari, concludo che $L(R)=L(R_1)\cup L(R_2)$ è regolare perchè i linguaggi regolari sono chiusi rispetto all'unione.
>Dimostrazione uguale per concatenazione $\circ$ e star $*$.

Ad esempio convertiamo $(ab\cup a)^*$ in un NFA equivalente:
![[Regex to NFA.svg]]

Per prima cosa abbiamo creato un NFA per riconoscere la stringa $ab$, poi un NFA per riconoscere la stringa $A$, li abbiamo uniti per scegliere quello opportuno ($\cup$) grazie allo stato <span style="color:blue">blu</span>, poi abbiamo aggiunto un ulteriore stato <span style="color:red">rosso</span> per rendere possibile l'operazione [[Automi a stati finiti non deterministici#Chiusura rispetto a star|star]].

### Da GNFA a regex
**Lemma**: se $A$ è regolare, allora esiste una regex $R$ tale che $L(R)=A$.
**Dimostrazione ($\Leftarrow$)**:

L'idea è la seguente: se $A$ è regolare, allora esiste un DFA $D$ tale che $L(D)=A$.

Introduciamo il concetto di **GNFA**, ovvero **Generalized-NFA**, esso rappresenta un NFA i cui archi sono etichettati con delle regexp, quindi non viene consumato un carattere alla volta (può succedere volendo), ma vengono consumati blocchi di caratteri.
![[GNFA regex.svg]]

Utilizziamo GNFA che rispettano i seguenti vincoli:
- Hanno un solo stato iniziale ed un solo stato accettante (diverso da quello iniziale)
- Lo stato iniziale ha archi in uscita verso tutti gli altri e nessun arco in entrata
- Lo stato accettante ha archi in entrata da tutti gli altri e nessun arco in uscita
- Il resto del grafo è [[Tipologie#Grafo completo|completamente connesso]]

Ad esempio consideriamo la seguente trasformazione di un GNFA:
![[GNFA to regex.png|600]]

L'**eliminazione di uno stato** $q_{rip}$ (_non iniziale e non accettante_) avviene creando una regex che comprende la parte di linguaggio interpretata da esso:
![[Cancellazione stato per regex.svg|700]]
>L'eliminazione degli stati va ripetuta fino ad avere $K=2$ stati ed una singola regex $R$ rappresentante il GNFA di partenza.