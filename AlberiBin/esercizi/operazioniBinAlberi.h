#include "alberoBinario_pt.h"
#ifndef REALIZZAZIONI_OPERAZIONIBINALBERI_H
#define REALIZZAZIONI_OPERAZIONIBINALBERI_H
template <class T>
class opB {
public:
//Dati un albero A con nodo u e un albero B con nodo v scambia i sottoalberi con radice u e v
    void mutation(alberoBinario_pt<T>& A, alberoBinario_pt<T>& B,typename alberoBinario_pt<T>::nodo u,typename alberoBinario_pt<T>::nodo v);
private:
    void copy(alberoBinario_pt<T>& BT,typename alberoBinario_pt<T>::nodo r, alberoBinario_pt<T>& BT1, typename alberoBinario_pt<T>::nodo r1);
    void remove(alberoBinario_pt<T>& BT, typename alberoBinario_pt<T>::nodo r);
};


template <class T>
void opB<T>::mutation(alberoBinario_pt<T> &A, alberoBinario_pt<T> &B, typename alberoBinario_pt<T>::nodo u, typename alberoBinario_pt<T>::nodo v)
{
    //copio i sottoalberi
    alberoBinario_pt<T> A1;
    A1.inserisciRadice(u);
    copy(A,u,A1,A1.radice());
    alberoBinario_pt<T> B1;
    B1.inserisciRadice(v);
    copy(B,v,B1,B1.radice());
    //rimuovo i figli di u e v
    remove(A,u);
    remove(B,u);
    //Inserimento
    copy(A1,A1.radice(),B,v);
    copy(B1,B1.radice(),A,u);
}

template <class T>
void opB<T>::copy(alberoBinario_pt<T> &BT, typename alberoBinario_pt<T>::nodo r, alberoBinario_pt<T> &BT1, typename alberoBinario_pt<T>::nodo r1)
{
    //copio i sottoalberi
    BT1.scriviNodo(r1,BT.leggiNodo(r));
    if (!BT.sinistroVuoto(r))
    {
        copy(BT,BT.figlioSinistro(r),BT1,BT1.figlioSinistro(r1));
    }
    if (!BT.destroVuoto(r))
    {
        cooy(BT,BT.figlioDestro(r),BT1,BT1.figlioDestro(r1));
    }
}

template <class T>
void opB<T>::remove(alberoBinario_pt<T> &BT, typename alberoBinario_pt<T>::nodo r) {
    if (!BT.sinistroVuoto(r))
        BT.cancellaSottoalbero(BT.figlioSinistro(r));
    if (!BT.destroVuoto(r))
        BT.cancellaSottoalbero(BT.figlioDestro(r));
}

#endif //REALIZZAZIONI_OPERAZIONIBINALBERI_H

