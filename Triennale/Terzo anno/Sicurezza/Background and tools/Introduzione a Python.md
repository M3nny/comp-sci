Python è molto usato nel campo della cybersecurity, perchè semplice da scrivere e può implementare librerie scritte in altri linguaggi più performanti.

### Stringhe
Le stringhe in Python sono **immutabili**, hanno indici da $0$ a $n-1$, e da $-1$ a $-n$.
**Formattazione**:
```python
"{0} {1}".format("hello", "world")
"{a} {b}".format(a="hello", b="world")
"int: {n:d}; hex: {n:x}; oct: {n:o}; bin: {n:b}".format(n=42)
```

**Slicing**:
```python
s = "hello"
s[0] # h
s[1:3] # el
s[0:4:2] # hl
s[::-1] # olleh
```

### Liste
Le liste in Python sono **mutabili** e possono contenere vari tipi di dato, anche su di esse valgono le stesse operazioni di slicing delle stringhe.

```python
l = [1, 2, 3]
m = ["a", "b", "c"]

l + m = [1, 2, 3, "a", "b", "c"]
l[1:] # [2, 3]
m[1:3] # ["b", "c"]
```

È possibile creare liste tramite cicli:
```python
# [(0, 1), (0, 3), (2, 1), (2, 3)]
[(x,y) for x in range(4) if x%2==0 for y in range(4) if y%2==1]

# [0, 4, 16, 36, 64]
[x*x for x in [y for y in range(10) if y%2==0]]
```
### Programmazione funzionale
È possibile ottenere l'iteratore di un oggetto con: `iter(iterable)`, per farlo avanzare si usa `next(iter)`.

- `filter(f, iterable)`: ritorna un iteratore tale per cui `f(item)` è `True`
- `map(f, iterable)`: ritorna un iteratore di elementi trasformati da `f(item)`

### Set, tuple e dizionari
**Set**: elementi unici senza ordinamento
- `in`: controllo della presenza (e.g. `1 in {1,2,3}`)
- `|`: unione (e.g. `{1,2,3}|{4} => {1,2,3,4}`)
- `&`: intersezione (e.g. `{1,2,3}&{3,4} => {3}`)

**Tuple**: sequenze immutabili
- Packing: `x = (1,2,3)` oppure `x = 1,2,3`
- Unpacking: `y, z, w = x`
- Singleton: `x = (1,)`
- Vuoto: `x=()`

**Dizionari**:
- `in`: controllo della presenza (e.g. `"a" in {"a": 2, "b": 5}`)
- Aggiunta: `d["z" = 6]`
- Cancellazione: `del d["z" = 6]`
- Chiavi: `d.keys()`
- Valori: `d.values()`
- Chiave-valore: `d.items()`
