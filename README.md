# Sparse Matrix
> Progetto del corso 'Programmazione C++' del gennaio del 2022 (Università Milano-Bicocca)
> 
Una matrice sparsa è una matrice nella quale solo gli elementi esplicitamente inseriti sono fisicamente memorizzati. Dal punto di vista logico la matrice sparsa si deve comportare come una normale matrice: alla richiesta dell'elemento in posizione (i,j) deve essere ritornato l'elemento inserito oppure un valore di default (D). Questo valore di default è definito dall’utente e deve essere passato in fase di costruzione della matrice.

Specifiche del progetto
1. La matrice deve essere realizzata in modo tale che siano esplicitamente memorizzati solo gli elementi inseriti dall'utente (utilizzo di memoria minimale). In pratica se la dimensione logica della matrice è NxM, non bisogna memorizzare tutti gli NxM elementi ma solo quelli effettivamente inseriti dall’utente.
2. La classe deve includere il supporto agli iteratori (in sola lettura) di tipo forward per l'accesso ai soli elementi inseriti nella matrice. L’iteratore deve ritornare un oggetto element che contiene le coordinate (i,j) e il valore inserito in quella posizione. I valori in element non devono essere modificabili. Non è importante l’ordine con cui sono ritornati gli elementi.
3. L'inserimento di un valore alle coordinate (i,j) deve avvenire con un metodo set. Se l’utente inserisce esplicitamente un valore di default D, questo è inserito normalmente. Se alle coordinate (i,j) esiste già un valore, questo viene sovrascritto.
4. La lettura di un valore alle coordinate (i,j) deve avvenire tramite operator(). Se alle coordinate (i,j) non c’e’ un valore esplicito, deve essere ritornato il valore di default D.
5. Scrivete una funzione globale generica evaluate che data una matrice sparsa M e un predicato P, ritorna quanti valori in M (compresi i default) soddisfano P. Testate diversi usi della funzione anche su diversi tipi di dati custom.
