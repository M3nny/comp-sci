# Introduzione
## Architettura di Von Neumann
Formata da:
- **CPU**
- **MEMORIA**
- **PERIFERICHE I/O**
- Collegati tra loro tramite il **BUS**

## Memoria
Può essere **Volatile**(RAM, Cache) o **non volatile**(hdd, ssd)
Esistono inoltre vari tipi di memoria RAM tra cui:
- **DRAM**: dynamic RAM
- **SRAM**: static RAM

## Processore
Mette a disposizione delle istruzioni così da poterci interagire e sono chiamate
**ISA**: _Instruction Set Architecture e sono lette dalla memoria per poi modificare eventualmente i dati in memoria oppure agire sull'I/O.
Ogni ISA d'altronde è diverso di macchina in macchina, quindi ci si pone il <u>problema della portabilità binaria</u> per questo nascono linguaggi come **C** che possono essere compilati/interpretati su più macchine a patto che si disponga del traduttore opportuno.

Negli ultimi anni vediamo come la **legge di Moore** venga meno, in quanto ci stiamo avvicinando ad un punto tale per cui non siamo più in grado di restringere la quantità di transistor messi all'interno di un chip.

Le cause per l'incremento della potenza delle CPU sono le seguenti:
- miniaturizzazione e incremento velocità dei transistor
- maggior numero di transistor in una CPU
- semplificazione ISA
- miglioramento compilatori

## Video
Utilizza una piccola memoria chiamata **frame buffer** per rappresentare i colori dei pixel tramite delle sequenze di numeri binari.

## Astrazione
In informatica per astrazione si intende la **distinzione** tra le **proprietà esterne** di un'entità ed i dettagli della sua **struttura interna**, <u>permettendo così di ignorare i dettagli interni solitamente molto complessi e di usarla come una singola unità</u>.
Nonostante ciò i livelli più bassi ci rivelano più informazioni mentre quelli più alti le omettono.

## Il software di sistema
- Produce altri software
- Esegue altri software
