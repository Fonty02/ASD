#include "alberoBinario_pt.h"
#ifndef REALIZZAZIONI_ISOBATO_H
#define REALIZZAZIONI_ISOBATO_H
template <class T>
class isobato
{
public:
    bool isIsobato(alberoBinario_pt<T>& BT);
private:
    void checkIsobato(alberoBinario_pt<T>& BT, typename alberoBinario_pt<T>::nodo n, bool& isobato, int altezza);
};

/*
 * La funzione restituisce true se l'albero è isobato, false altrimeti
 * Un albero è isobato quando tutti i cammi dalla radice alle foglie hanno la stessa lunghezza
 */
template<class T>
bool isobato<T>::isIsobato(alberoBinario_pt<T> &BT) {
    if (!BT.alberoBinVuoto())
    {
        bool isobato=true;
        //richiamo una funzione per verificare che l'albero sia isobato
        checkIsobato(BT,BT.radice(),isobato,BT.altezza_nodo(BT,BT.radice()));
        return isobato;
    }
    //per definizione se l'albero è vuoto allora è anche isobato
    else return true;
}

//La funzione verifica se l'albero è isobato
template <class T>
void isobato<T>::checkIsobato(alberoBinario_pt<T> &BT, typename alberoBinario_pt<T>::nodo n, bool &isobato,int altezza) {
    //se l'albero è isobato continuo, altrimenti esco dalla funzione
   if (isobato) {
       if (BT.sinistroVuoto(n) && BT.destroVuoto(n)) {
           //se la profondità di una foglia è diversa dall'altezza dell'albero allora l'albero non è isobato
           if (BT.profondita_nodo(BT, n) != altezza) isobato = false;
       }
       else
       {
           //richiamo la funzione di verifica sui figli di n (se esistono)
           if (!BT.sinistroVuoto(n)) checkIsobato(BT,BT.figlioSinistro(n),isobato,altezza);
           if (!BT.destroVuoto(n)) checkIsobato(BT,BT.figlioDestro(n),isobato,altezza);
       }
   }
}
#endif //REALIZZAZIONI_ISOBATO_H
