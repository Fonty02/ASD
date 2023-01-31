#ifndef REALIZZAZIONI_SOMMALIVELLOMAGGIORE_H
#define REALIZZAZIONI_SOMMALIVELLOMAGGIORE_H
#include "AlberoPt.h"
/*
 * /dato un albero n-ario di nodi interi ed un intero k restituisce la somma dei valori di tutte le foglie che si trovano ad una profondità maggiore di k
 */
class sommaK
{
public:
    int somma(alberoPt<int>& T, int k);
private:
    int effettuaSomma(alberoPt<int>&T, alberoPt<int>::nodo , int k, int liv);
};
#endif //REALIZZAZIONI_SOMMALIVELLOMAGGIORE_H

int sommaK::somma(alberoPt<int> &T, int k) {
    int somma = 0;
    if (!T.alberoVuoto()) {
        somma = effettuaSomma(T, T.radice(), k, 0);
    }
    return somma;
}

int sommaK::effettuaSomma(alberoPt<int> &T, alberoPt<int>::nodo n, int k, int liv) {
    int x=0;
    if (liv>k) x=T.leggiNodo(n); //>= se k va contato
    if (!T.foglia(n))
    {
        int newLiv=liv+1;
        alberoPt<int>::nodo c=T.primoFiglio(n);
        while (!T.ultimoFratello(c))
        {
            x+= effettuaSomma(T,c,k,newLiv);
            c=T.fratelloSuccessivo(c);
        }
        x+= effettuaSomma(T,c,k,newLiv);
    }
    return x;

}