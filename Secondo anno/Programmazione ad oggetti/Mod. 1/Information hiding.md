Dobbiamo **nascondere le informazioni** relative a come funziona una classe internamente così da creare un'**API** più pulita senza possibilità di modificare proprietà del oggetto indesiderate dall'esterno.

Per realizzare ciò usiamo l'**incapsulamento** per garantire la consistenza dello stato di un'oggetto (e.g. evitiamo che il campo benzina sia negativo).

Usiamo quindi vari **modificatori di accesso** i quali definiscono vari privilegi per leggere e modificare lo stato di un oggetto.

##### Modificatori di accesso
|           | Same class | Same package | Subclasses | Everywhere |
|:---------:|:----------:|:------------:|:----------:|:----------:|
|  **Public**   |     ✅     |      ✅      |     ✅     |     ✅     |
| **Protected** |     ✅     |      ✅      |     ✅     |     ❌     |
|  **Default**  |     ✅     |      ✅      |     ❌     |     ❌     |
|  **Private**  |     ✅     |      ❌      |     ❌     |     ❌     |

- **Public**: tutto ciò che rappresenta l'API esterna, dovrà contenere le funzionalità minime per funzionare
- **Protected**: tutto ciò che deve essere acceduto dalla stessa unità software
- **Private**: deve essere completamente nascosto all'esterno, l'implementazioni interna quindi può cambiare nel tempo

Dato che non vogliamo lasciare il controllo totale dei campi, implementiamo dei metodi **getter** e **setter** i quali ci permettono di concedere una visione read-only dei campi oppure di implementare dei controlli sulle modifiche dei campi effettuati dall'esterno.

