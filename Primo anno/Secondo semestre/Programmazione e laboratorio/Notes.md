compilo con -c se non devo produrre l'eseguibile finale

- include: .hpp
- src: .cpp
- build: .o
- tools: file .cpp importanti come main
- external: codice altrui (github)

Nei file .hpp metto le dichiarazioni delle funzioni
``` cpp
int foo(int, double);
```

Dopo ogni target devo specificare i file usati nella recipe altrimenti non sa quali sono stati cambiati
