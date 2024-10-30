Una **macchina di Turing (MdT)** è un modello teorico di un calcolatore con memoria infinita ed utilizzabile in maniera arbitraria.

>[!Info] Memoria dei DFA e PDA
>I **DFA** possiedono memoria **finita**, mentre gli **NFA** dispongono di memoria **infinita** in forma di _stack_.

Una MdT è formata da uno **stato interno**, un **nastro infinito** ed una **testina**.

**Caratteristiche** di una MdT:
- L'input è sul nastro e può essere sia letto che scritto
- La testina può spostarsi sia a sx e sia a dx
- Memoria (nastro) infinita
- Accetta o rifiuta un input non appena entra in uno stato di accettazione o rifiuto

## Definizione di una MdT
Una MdT è una settupla $(Q,\Sigma,\Gamma,\delta,q_0,q_{accept},q_{reject})$ dove:
- $Q$: è insieme finito di stati
- $\Sigma$: è un alfabeto finito di input tale che un carattere **blank** $\sqcup\notin\Sigma$
- $\Gamma$: è un alfabeto finito per il nastro tale che $\sqcup\in\Gamma$ e $\Sigma\subseteq\Gamma$
- $q_0\in Q$: è lo stato iniziale
- $q_{accept}\in Q$: è (l'unico) stato accettante
- $q_{reject}\in Q$: è (l'unico) stato rifiutante ($q_{reject}\neq q_{accept}$)
- $\delta:Q\times\Gamma\to Q\times\Gamma\times\{L,R\}$ è la funzione di transizione

Una configurazione di una MdT <u>descrive un momento della computazione</u> tramite tre informazioni:
- Lo stato interno
- Il contenuto del nastro
- La posizione della testina

![[Configurazione MdT.svg]]
essa può essere scritta come $001q_301$.
Generalmente una configurazione ha forma $uqv$, dove $u,v\in\Gamma^*$ e $q\in Q$.

Una MdT computa passando da una configurazione a quella successiva secondo quanto definito da $\delta$, vediamo le **regole di computazione**:
- Sia $M$ nella configurazione $uaq_ibv$, e sia $\delta(q_i,b)=(q_j,c,L)$, allora la prossima configurazione sarà $uq_jacv$
- Sia $M$ nella configurazione $uaq_ibv$ e sia $\delta(q_i,b)=(q_j,c,R)$, allora la prossima configurazione sarà $uacq_jv$
- Sia $m$ nella configurazione $q_ibv$ e sia $\delta(q_i,b)=(q_j,c,L)$, allora la prossima configurazione sarà $q_jcv$
- Sia $M$ nella configurazione $q_ibv$ e sia $\delta(q_i,b)=(q_j,c,R)$, allora la prossima configurazione sarà $cq_jv$

Una MdT **accetta un input** $w$ sse esistono della configurazioni $C_1,C_2,...,C_k$ tali che:
- $C_1$ è la configurazione iniziale $q_0w$
- $C_k$ è una configurazione accettante $u_{accept}v$ per qualche $u,v\in\Gamma^*$
	(Le configurazioni accettanti possono essere più di una)
- Per ogni $i$ $C_i$ passa in $C_{i+1}$ secondo le regole di computazione date

### Linguaggio per una MdT
Un linguaggio $A$ si dice **Turing riconoscibile** sse esiste una MdT $M$ tale che $L(M)=A$.
Dato un input $w$, una MdT $M$ ha solo tre possibili comportamenti:
- $M$ accetta $w$
- $M$ rifiuta $w$
- $M$ non termina (va in loop quando eseguita su $w$)

Una macchina di Turing che non va mai in loop per nessun input si dice **decisore**.
Un linguaggio $A$ si dice **decidibile** sse esiste un _decisore_ $M$ tale che $L(M)=A$.

>[!Example]
>Creiamo una MdT per il linguaggio _non regolare_, e _non CFL_:
>$$C=\{w\#w|w\in\{0,1\}^*\}$$
>
>L'idea è quella di andare a fare il match dei simboli a sx e dx di $\#$, per prima cosa si sostituisce il primo simbolo in posizione $i$ con una $\times$, poi si controlla il simbolo a posizione $pos(\#)+i$, se combacia si marchia con una $\times$, altrimenti si rifiuta.
>
>Dopo aver sostituito i simboli con $\times$ a sx e dx di $\#$ si verifica se ci sono ancora simboli non marchiati con $\times$, in tal caso si rifiuta, altrimenti si accetta.
>![[MdT 1.png]]
>
>---
>Creiamo una MdT per il seguente linguaggio:
>$$\{0^{2^n}|n\geq 0\}$$
>
>Il linguaggio rappresenta una stringa di zeri con lunghezza pari ad una potenza di $2$.
>L'idea è quella di fare molteplici passate sul nastro, dove ogni volta vengono marchiati con $\times$ la metà degli $0$, quindi si marchia uno si ed uno no.
>Se la passata ha marchiato solo uno $0$ accetta, se ha trovato una quantità di $0$ dispari ($>1$) rifiuta, altrimenti esegue un'altra passata.

