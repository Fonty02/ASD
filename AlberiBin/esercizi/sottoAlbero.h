#include "alberoBinario_pt.h"
#ifndef REALIZZAZIONI_SOTTOALBERO_H
#define REALIZZAZIONI_SOTTOALBERO_H
template <class T>
class subTree
{
public:
    bool isSubTree(alberoBinario_pt<T>&BT, alberoBinario_pt<T>&subBT);
private:
    void checkSubTree(alberoBinario_pt<T>&BT, alberoBinario_pt<T>&subBT,typename alberoBinario_pt<T>::nodo n,typename alberoBinario_pt<T>::nodo subR, bool& isSubTree);
};

//La funzione restituisce true se l'albero subBT è un sottoalbero dell'albero BT, false altrimenti
template <class T>
bool subTree<T>::isSubTree(alberoBinario_pt<T> &BT, alberoBinario_pt<T> &subBT) {
    if (!BT.alberoBinVuoto() && !subBT.alberoBinVuoto()) {
            bool subTree = true;
            checkSubTree(BT,subBT,BT.radice(),subBT.radice(),subTree);
            return subTree;
    }
    else return false;
}

//Funzione ricorsiva che verifica se un albero è sottoalbero di un altro
template <class T>
void subTree<T>::checkSubTree(alberoBinario_pt<T> &BT, alberoBinario_pt<T> &subBT, typename alberoBinario_pt<T>::nodo n, typename alberoBinario_pt<T>::nodo subR, bool &isSubTree) {
    if (isSubTree)
    {
        if (BT.leggiNodo(n)!=subBT.leggiNodo(subR))
        {
            isSubTree=false;
            //n e subR non hanno lo stesso valore, quindi per ora l'albero subBT non è un sottoalbero di BT
            // SE il nodo n è radice di BT richiamo la funzione di verifica sui suoi figli (se esistono)
            if (n==BT.radice()) {
                isSubTree=true;
                if (!BT.sinistroVuoto(n)) checkSubTree(BT, subBT, BT.figlioSinistro(n), subBT.radice(), isSubTree);
                if (!isSubTree && !BT.destroVuoto(n)) {
                    isSubTree=true;
                    checkSubTree(BT, subBT, BT.figlioDestro(n), subBT.radice(), isSubTree);
                }
            }
        }
        else
        {
            //se il n e subR hanno lo stesso valore allora richiamo la funzione sui figli di n (se esistono) passando come parametro i rispettivi figli (se esistono) si subBT
            if(!BT.sinistroVuoto(n) && !subBT.sinistroVuoto(subR)) checkSubTree(BT,subBT,BT.figlioSinistro(n),subBT.figlioSinistro(subR),isSubTree);
            if (!BT.destroVuoto(n) && !subBT.destroVuoto(subR) &&isSubTree) checkSubTree(BT,subBT,BT.figlioDestro(n),subBT.figlioDestro(subR),isSubTree);
        }
    }
    else
    {
        //Richiamo la funzione di verifica sui figli del nodo n (se esistono), passando come altro parametro la radice si subBT
        isSubTree=true;
        if(!BT.sinistroVuoto(n)) checkSubTree(BT,subBT,BT.figlioSinistro(n),subBT.radice(),isSubTree);
        if (!isSubTree && !BT.destroVuoto(n))
        {
            isSubTree=true;
            checkSubTree(BT,subBT,BT.figlioDestro(n),subBT.radice(),isSubTree);
        }
    }
}

#endif //REALIZZAZIONI_SOTTOALBERO_H
