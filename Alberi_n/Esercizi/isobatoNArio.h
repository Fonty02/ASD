
#include "AlberoPt.h"
#ifndef REALIZZAZIONI_ISOBATONARIO_H
#define REALIZZAZIONI_ISOBATONARIO_H
template <class T>
class isobatoN
{
public:
    bool isIsobato(alberoPt<T>& tree);
private:
    void checkIsobato(alberoPt<T>& B,typename alberoPt<T>::nodo n, bool& isobato, int altezza, int currentH);
};


//La funzione restituisce true se l'albero n-ario è isobato, false altrimenti.
//Un albero è isobato quando tutti i cammi dalla radice alle foglie hanno la stessa lunghezza
template <class T>
bool isobatoN<T>::isIsobato(alberoPt<T> &tree) {

    if(!tree.alberoVuoto())
    {
        bool isobato=true;
        //richiamo una funzione per controllare se l'albero è isobato
        checkIsobato(tree,tree.radice(),isobato,tree.profonditaAlbero()-1,0);
        return isobato;
    }
        //un albero vuoto è isobato
    else return true;
}


/*
 * La funzione riceve in input un albero, un nodo, un valore booleano passato per reference e i due interi. La variabile booleana viene subito controllata perchè se risulta essere false allora l'algoritmo non va eseguito
 * La prima variabile intera indica l'altezza delll'albero (cioè il livello della foglia piu in basso) mentre la seconda indica la profondità (lunghezza cammino radice-nodo) del nodo attuale
 */
template <class T>
void isobatoN<T>::checkIsobato(alberoPt<T> &B, typename alberoPt<T>::nodo n, bool &isobato, int altezza, int currentH) {
    if (isobato)
    {
        //se un nodo è foglia e la sua profondità non coincide con l'altezza dell'albero allora l'albero non è isobato
        if (B.foglia(n))
        {
            if (currentH!=altezza) isobato=false;
        }
        else
        {
            //richiamo la funzione sui fratelli del nodo (se presenti). In questo caso dunque la profondità rimane la stessa
            if (!B.ultimoFratello(n))
            {
                checkIsobato(B,B.fratelloSuccessivo(n),isobato,altezza,currentH);
            }
            if (!B.foglia(n))
            {
                //richiamo la funzione sul primo figlio di un nodo (in questo caso la profondità del nodo aumenta di 1)
                checkIsobato(B,B.primoFiglio(n),isobato,altezza,currentH+1);

            }
        }
    }
}
#endif //REALIZZAZIONI_ISOBATONARIO_H
