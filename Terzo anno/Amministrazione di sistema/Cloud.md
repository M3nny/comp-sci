Il **cloud computing** è la distribuzione di servizi di calcolo tramite Internet.

Solitamente i provider di servizi cloud addebitano un costo per i servizi in base all'utilizzo.

Tra i **vantaggi** di questo tipo di servizi troviamo:
- **Costo**: elimina le spese associate ad acquisto di hardware e software, e la loro manutenzione
- **Velocità**: la maggior parte dei servizi viene offerta on demand, è possibile effettuare il provisioning di grandi quantità di risorse in pochi passi
- **Scalabilità globale**: possibilità di fornire la giusta quantità di risorse proprio quando è necessario
- **Produttività**: vengono eliminati i tempi di configurazione di hardware e software appositi
- **Prestazioni**: i grandi servizi di cloud vengono eseguiti su data center sparsi nel mondo, sempre aggiornati e con latenza ridotta
- **Affidabilità**: riduce i costi di backup, ripristino di emergenza e aumenta la semplicità grazie alla possibilità di eseguire il mirroring dei dati in più servizi cloud

### Tipologie di cloud
I **cloud pubblici** sono di proprietà di un provider, il quale fornisce le risorse di calcolo ed è anche colui che li gestisce.

Un **cloud privato** si riferisce alle risorse di cloud computing usate esclusivamente da una singola azienda o organizzazione, esso può essere ospitato nel data center locale oppure essere ospitato presso dei provider di terze parti, in questo caso si dice **cloud privato gestito**.
>I servizi di un cloud privato sono gestiti tramite rete privata o tramite VPN.

Un **cloud dedicato** è un cloud contenuto all'interno di un altro cloud.

I **cloud ibridi** combinano cloud privati e pubblici rendendo possibile la condivisione di dati e applicazione tra i due tipi di cloud, offrendo così una flessibilità maggiore.

### Tipologie di servizi
- **Infrastructure as a Service (IaaS)**: si affittano risorse di calcolo con pagamento in base al consumo, il provider gestisce l'infrastruttura mentre noi gestiamo software, middleware e applicazioni
- **Platform as a Service (PaaS)**: oltre a fornire risorse di calcolo come gli IaaS, forniscono anche software e middleware, è necessario gestire solo le applicazioni sviluppate
- **Software as a Service (SaaS)**: è un metodo di distribuzione di applicazioni software tramite Internet on demand, solitamente in base ad una sottoscrizione, in questo caso sono semplicemente gli utenti finali a pagare per poter usare l'applicazione, mentre gli sviluppatori si occuperanno di aggiornarla nel tempo

### Terraform
[Terraform](https://www.terraform.io/) consente di specificare l'infrastruttura di rete, interagendo con vari servizi cloud, attraverso un linguaggio ad alto livello.

Il codice ad alto livello dell'infrastruttura può essere **versionato** in modo da rendere riproducibile la creazione dell'infrastruttura.

Va a creare un **grafo delle dipendenze** tra i vari elementi dell'infrastruttura, permettendo così di avviare in parallelo la creazione di elementi indipendenti, inoltre è in grado di calcolare le differenze tra l'infrastruttura presente e una nuova versione modificata in modo da minimizzare il numero di modifiche da fare per aggiornare quella corrente.

