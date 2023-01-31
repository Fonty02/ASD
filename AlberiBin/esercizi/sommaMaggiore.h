#ifndef REALIZZAZIONI_SOMMAMAGGIORE_H
#define REALIZZAZIONI_SOMMAMAGGIORE_H
#include "alberoBinario_pt.h"
/*
 * /dato un albero n-ario di nodi interi ed un intero k restituisce la somma dei valori di tutte le foglie che si trovano ad una profondità maggiore di k
 */
class sommaKBin
{
public:
    int somma(alberoBinario_pt<int>& T, int k);
private:
    int effettuaSomma(alberoBinario_pt<int>&T, alberoBinario_pt<int>::nodo , int k, int liv);
};


int sommaKBin::somma(alberoBinario_pt<int> &T, int k) {
    int somma = 0;
    if (!T.alberoBinVuoto()) {
        somma = effettuaSomma(T, T.radice(), k, 0);
    }
    return somma;
}

int sommaKBin::effettuaSomma(alberoBinario_pt<int> &T, alberoBinario_pt<int>::nodo n, int k, int liv) {
    int x=0;
    if (liv>k) x=T.leggiNodo(n); //>= se k va contato
    int newLiv=liv+1;
    if (!T.destroVuoto(n)) x+= effettuaSomma(T,T.figlioDestro(n),k,newLiv);
    if (!T.sinistroVuoto(n)) x+= effettuaSomma(T,T.figlioSinistro(n),k,newLiv);
    return x;

}
#endif //REALIZZAZIONI_SOMMAMAGGIORE_H
