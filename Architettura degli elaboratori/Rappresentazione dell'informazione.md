# Rappresentazione dell'informazione
Le informazioni all'interno del computer devono essere **rappresentate** secondo delle convenzioni comuni, per fare questo dobbiamo prima distinguere:
- **simbolo** che rappresenta l'informazione
- **valore** che corrisponde al significato dell'informazione

Quindi per **codificare** l'informazione avremmo bisogno di un alfabeto di simboli <u>finito</u>, nel caso del computer useremo i simboli $\{0,1 \}$ , i quali sono associati a segnali elettrici differenti.

>[!INFO]
>Una **codifica** fornisce corrispondenza tra **sequenze** di simboli ed i **dati**.


Con un alfabeto di $N$ simboli e sequenze di lunghezza $k$, avrò: $N^{k}$ combinazioni.

Esistono 2 tipi generali di codifiche:
- **Non numeriche**: effettuate in maniera semi arbitraria, dato che basta fissare uno standard comune come  il <u>codice ASCII</u>
- **Numeriche**: devono essere più accurate in quanto devono avvenire delle operazioni con la rappresentazione in uso

>[!example]
>$1011101_2 = 2^0 \cdot 1 + 2^1 \cdot 0 + 2^2 \cdot 1 + 2^3 \cdot 1 + 2^4 \cdot 1 + 2^5 \cdot 0 + 2^6 \cdot 1 = 1+4+8+16+64=93$ 
>$140_5 = 5^0 \cdot 0 + 5^1 \cdot 4 + 5^2 \cdot 1 = 0+20+25 = 45$