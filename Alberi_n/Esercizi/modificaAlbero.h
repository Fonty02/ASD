
#ifndef REALIZZAZIONI_MODIFICAALBERO_H
#define REALIZZAZIONI_MODIFICAALBERO_H
#include "AlberoPt.h"

class modifcaAlbero
{
public:
    void modifica(alberoPt<int>&T);
private:
    int modifica(alberoPt<int>&T,alberoPt<int>::nodo n);
};

//La funzione modifica il contenuto di ogni nodo di un albero n-ario (che non sia foglia)
void modifcaAlbero::modifica(alberoPt<int> &T) {
    if (!T.alberoVuoto())
        modifica(T,T.radice());
}

//Ogni nodo assume come valore la somma dei valori dei nodi appartenenti al sottoalbero di cui esso è radice (per le foglie il valore rimane invariato)
int modifcaAlbero::modifica(alberoPt<int> &T, nodoT<int> *n) {
    if (T.foglia(n))
        //se un nodo è foglia restituisco il suo valore
        return  T.leggiNodo(n);
    else
    {
        //inizializzo una variabile di somma per memorizzare la somma dei valori dei nodi presenti nel sottoalbero di cui n è radice
    int somma=T.leggiNodo(n);
    alberoPt<int>::nodo c;
    c=T.primoFiglio(n);
    while (!T.ultimoFratello(c)) {
        //richiamo la funzione di somma su tutti i fratelli di un nodo
        somma+=modifica(T,c);
        c=T.fratelloSuccessivo(c);
    }
    somma+=modifica(T,c);
    //aggiorno il valore di un nodo
    T.scriviNodo(n,somma);
    //ritorno il valore della somma (serve per le chiamate ricorsive)
    return somma;
    }
}
#endif //REALIZZAZIONI_MODIFICAALBERO_H
