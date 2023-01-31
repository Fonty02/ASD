
#include "alberoBinario_pt.h"
#ifndef REALIZZAZIONI_LIONESE_H
#define REALIZZAZIONI_LIONESE_H
template <class T>
class lionese{
public:
    bool isLionese(alberoBinario_pt<T>&BT);
private:
    void checkLionese(alberoBinario_pt<T>&BT,typename alberoBinario_pt<T>::nodo n, bool& isLionese);

};
//La funzione restituisce true se l'albero è lionese, false altrimenti
//Un albero si definisce lionese se tutti i figli destri di nodi sono pari e tutti i figli sinistri sono dispari. La radice dell’albero può contenere qualsiasi valore in quanto non è né figlio destro né sinistro
template <class T>
bool lionese<T>::isLionese(alberoBinario_pt<T> &BT) {
    if (!BT.alberoBinVuoto())
    {
        bool lionese=true;
        checkLionese(BT,BT.radice(),lionese);
        return lionese;
    }
    //se l'albero è vuoto allora non è lionese
    return false;
}

template <class T>
void lionese<T>::checkLionese(alberoBinario_pt<T> &BT, typename alberoBinario_pt<T>::nodo n, bool &isLionese) {
    if (!BT.sinistroVuoto(n) && !BT.destroVuoto(n))
    {
        // IL VALORE DELLA RADICE NON E' IMPORTANTE
        if (BT.radice()!=n)
        {
            if (!BT.sinistroVuoto(n))
            {
                //Se il figlio sinistro di n è pari allora l'albero non è lionese ed esco dalla funzione, altrimenti continuo a verificare
                if (BT.leggiNodo(BT.figlioSinistro(n))%2!=1) isLionese=false;
                else
                    checkLionese(BT,BT.figlioSinistro(n),isLionese);
            }
            if (isLionese && !BT.destroVuoto(n))
            {
                //Se il figlio destro di n è pari allora l'albero non è lionese ed esco dalla funzione, altrimenti continuo a verificare
                if (BT.leggiNodo(BT.figlioDestro(n))%2!=0) isLionese=false;
                else
                    checkLionese(BT,BT.figlioDestro(n),isLionese);
            }
        }
    }
}
#endif //REALIZZAZIONI_LIONESE_H
