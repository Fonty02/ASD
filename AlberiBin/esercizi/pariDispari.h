#include "alberoBinario_pt.h"
#ifndef REALIZZAZIONI_PARIDISPARI_H
#define REALIZZAZIONI_PARIDISPARI_H
template<class T>
class pariDispari
{
public:
    bool isPariDispari(alberoBinario_pt<T>&BT);
private:
    void checkIsPariDispari(alberoBinario_pt<T>&BT, typename alberoBinario_pt<T>::nodo n, int livello, bool& pariDispari);
};

/*
 * La funzione restituisce true se l'albero è pariDispari, false altrimenti
 * Un albero è pariDispari quando tutti i nodi di livello pari hanno valore pari e tutti i nodi di livello dispari hanno valore dispari
 */
template<class T>
bool pariDispari<T>::isPariDispari(alberoBinario_pt<T> &BT) {
    if (!BT.alberoBinVuoto())
    {
        bool pariDispari=true;
        checkIsPariDispari(BT,BT.radice(),0,pariDispari);
        return pariDispari;
    }
    //se l'albero è vuoto allora non è pariDispari
    else return false;
}

template<class T>
void pariDispari<T>::checkIsPariDispari(alberoBinario_pt<T> &BT, typename alberoBinario_pt<T>::nodo n, int livello, bool &pariDispari) {
    //se l'albero non è pariDispari, esco dalla funzione
    if (pariDispari)
    {
        if (BT.leggiNodo(n)%2==0)
        {
            //se il nodo è a livello pari ma ha valore dispari l'albero non è pariDispari ed esco dalla funzione
            if (livello%2!=0) pariDispari=false;
        }
        else
        {
            //se il nodo è a livello dispari ma ha valore pari l'albero non è pariDispari ed esco dalla funzione
            if (livello%2==0) pariDispari=false;
        }
        if (pariDispari)
        {
            if (!BT.sinistroVuoto(n)) checkIsPariDispari(BT,BT.figlioSinistro(n),livello+1,pariDispari);
            if (!BT.destroVuoto(n)) checkIsPariDispari(BT,BT.figlioDestro(n),livello+1,pariDispari);

        }
    }

}
#endif //REALIZZAZIONI_PARIDISPARI_H
