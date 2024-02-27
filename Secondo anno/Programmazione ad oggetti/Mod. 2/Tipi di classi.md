Oltre alle classi **top-level**, le quali sono dichiarate su un proprio file apposito, esistono classi usate per operazioni "interne".

Prendiamo come esempio la creazione dell'iteratore di `ArrayList`.
### Nested
- Ha accesso ai campi e metodi della classe enclosing
- Ha accesso al type parameter
```java
public class ArrayList<T> implements List<T> {
	public boolean size() {...}
	public T get(int i) {...}
	
	private class MyIterator implements Iterator<T> {
		private int pos = 0;
		
		@Override
		public boolean hasNext() {
			// ArrayList.this.size()
			return pos < size();
		}
		
		@Override
		public T next() {
			// ArrayList.this.get()
			return get(pos++);
		}
	}
	
	@Override
	public Iterator<T> iterator() {
		return MyIterator();
	}
}
```

È possibile chiamare le funzioni della classe enclosing senza senza dover specificare la **full qualification**: `<enclosing_class>.this.<func>()`.

### Static nested
- Non possiede il contesto della enclosing class perchè non possiede `this` nella _virtual table_
- È necessario passargli i dati su cui deve lavorare
```java
public class ArrayList<T> implements List<T> {
	public boolean size() {...}
	public T get(int i) {...}
		
	private static class StaticMyIterator<T> implements Iterator<T> {
		private int pos = 0;
		private ArrayList<T> enclosing;
		
		public StaticMyIterator(ArrayList<T> a) {
			this.enclosing = a;
		}
		
		@Override
		public boolean hasNext() {
			return pos < enclosing.size();
		}
		
		@Override
		public T next() {
			return enclosing.get(pos++);
		}
	}
	
	@Override
	public Iterator<T> iterator() {
		return StaticMyIterator<>(this);
	}
}
```

Se la static nested class fosse stata top-level, verrebbe chiamata allo stesso modo (usando il nome del file opportuno).
Farla globale però non avrebbe senso, in quanto inquinerebbe il package con una classe "inutile" in quanto usata solo allo scopo di ritornare l'iteratore.

### Anonima
- Crea direttamente un oggetto
- Porta con sè i campi definiti
- Si comporta come una normale nested class
```java
public class ArrayList<T> implements List<T> {
	public boolean size() {...}
	public T get(int i) {...}
	
	@Override
    public Iterator<T> iterator() {
	    return new Iterator<T>() { // closure
		    private int pos = 0;
		    
            @Override
            public boolean hasNext() {
                return pos < size();
            }
			
            @Override
            public T next() {
                return get(pos++);
            }
        };
    }
}
```

Aggiungere metodi non avrebbe senso perchè darebbe errore a compile time nel momento in cui si prova ad invocarli (non sono definiti in `Iterator<T>`).

