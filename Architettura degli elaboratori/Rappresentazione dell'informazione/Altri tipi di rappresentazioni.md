# Rappresentazione dell'informazione alfanumerica
Utilizzando l'ASCII abbiamo una corrispondenza tra simbolo e valore binario, l'ascii però non basta per coprire tutti i caratteri utilizzati nelle lingue slave o le lettere accentate italiane, per questo sono nate delle estensioni come **Latin-1** per lingue come l'italiano e **Latin-2** per le lingue slave.

## Cenni sull'architettura RISC
MIPS e ARM sono simili ad altre architetture RISC (Reduced Instruction Set Computer) in quanto ammettono operazioni elementari come: **add, sub, mult, div**.
>[!Tip]
>Vediamo la seguente istruzione assembly:
>$$add\quad $9,\space $17,\space $18$$
>Assegnamo alla variabile **$9** il risultato della somma tra le variabili **$17** e **$18**.

- Ogni gruppo di byte nella memoria è organizzato in una **word**, essa stabilisce quale è il numero massimo rappresentabile.

## Codici per scoprire gli errori
Indichiamo con la **distanza di Hamming** il numero di bit che differenziano tra la codifiche corretta e la codifica effettivamente letta:

Avendo $010$ come codifica corretta e $100$ come codifica letta (errata) potremmo dire che la distanza di Hamming:
$$H(C,C')=2$$
In quanto la codifica letta possiede due bit alterati rispetto alla codifica corretta.
È quindi possibile definire <u>codifiche che scoprono e correggono errori</u>.

## Parità
Questa codifica è in grado di scoprire gli errori di lettura solo quando il numero di bit alterati è dispari.

Per farla funzionare aggiungiamo un bit $0$ alla fine della codifica se il numero di bit con valore $1$ di quest'ultima è **pari**, altrimenti aggiungiamo un bit $1$ se è **dispari**.
Quindi la codifica 001 diventerà 001**1**, mentre 011 diventerà 011**0**
>[!Example]
>È facile capire quindi che la seguente codifica è sbagliata dato che il bit di parità non corrisponde alla codifica rappresentata:
>1. In memoria ho 011**0**
>2. Leggo 001**0** (!)
>3. Capisco che è sbagliato perchè il bit di parità corrisponde a quello di una codifica pari, mentre quella letta è dispari.

