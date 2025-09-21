Compilo con **-c** se non devo produrre l'eseguibile finale.

**Ottimizzazioni**:
| Option | Optimization level                 | execution | code | memory usage | compile time |
| ------ | ---------------------------------- | --------- | ---- | ------------ | ------------ |
| -O0    | compilation time                   | +         | +    | -            | -            |
| -O1    | code size & execution time         | -         | -    | +            | +            |
| -O2    | code size & execution time         | --        |      | +            | ++           |
| -O3    | code size & execution time         | ---       |      | +            | +++          |
| -Os    | code size                          |           | --   |              | ++           |
| -Ofast | O3 with accurate math calculations | ---       |      | +            | +++          |


#### Struttura progetto
```
progetto/
|-include/
	|-file.hpp
|-src/
	|-file.cpp
|-build/
	|-file.o (generati con il flag -c)
|-tools/
	|-file.cpp importanti come il main
|-external/
	|-codice esterno (e.g. github)
```


Nei file .hpp metto le dichiarazioni delle funzioni
``` cpp
int foo(int, double);
```


#### Makefile
Viene usato per automatizzare la compilazione e segue la seguente sintassi:
```Makefile
<target>:<prerequisites>
	<recipe>
	
OPTIONS=-O3 -DNDEBUG -Wall -Wextra

all: build/theanswer

debug: OPTIONS=-O0 -g -DDEBUG -Wall -Wextra
debug: build/theanswer

build/theanswer: build/root.o build/power.o tools/main.cpp
	g++ ${OPTIONS} tools/main.cpp -o build/theanswer -I include/ build/root.o build/power.o

build/root.o: src/root.cpp include/myfunctions.hpp
	g++ ${OPTIONS} -c src/root.cpp -o build/root.o -I include/

build/power.o: src/power.cpp include/myfunctions.hpp
	g++ ${OPTIONS} -c src/power.cpp -o build/power.o -I include/

clean:
	rm -rf build/*.o build/theanswer

```

Dopo ogni target devo specificare i file usati nella recipe così da non ri-eseguire la compilazione per file che non sono stati cambiati.

