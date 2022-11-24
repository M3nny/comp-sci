## Minimo comune multiplo
Dati due interi $a$ e $b$, il minimo fra i loro multipli comuni è detto **minimo comune multiplo** ed è denotato come **mcm(a, b)**
>mcm(1, 6) = 6
>mcm(4, 6) = 12

## Massimo comun divisore
Dati due interi $a$ e $b$, il massimo fra i loro divisori comuni è detto **massimo comun divisore** ed è denotato con **MCD(a, b)**
>MCD(1, 6) = 1
>MCD(4, 6) = 2

Euclide definisce nel seguente modo l'algoritmo per calcolare l'MCD efficientemente:
1. Dividere il maggiore dei due numeri per il minore;
2. Rimpiazzare il maggiore con il minore;
3. Rimpiazzare il minore con il resto di tale divisione;
4. Ripetere finchè il resto non diventa zero.

