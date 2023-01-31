#ifndef REALIZZAZIONI_SOMMAMEDIALIVELLI_H
#define REALIZZAZIONI_SOMMAMEDIALIVELLI_H
#include "alberoBinario_pt.h"
template <class T>
class sum_mean_bin
{
public:
    List_vector<double> mediaLivello(alberoBinario_pt<T>&);
private:
    void sommaLivello(alberoBinario_pt<T>&,typename alberoBinario_pt<T>::nodo ,int,T[]);
    void numNodiInLiv(alberoBinario_pt<T>&,typename alberoBinario_pt<T>::nodo, int, int&);
};


//CALCOLA LA MEDIA DEI VALORI PRESENTI IN OGNI LIVELLO
template<class T>
List_vector<double> sum_mean_bin<T>::mediaLivello(alberoBinario_pt<T> & BT) {
    List_vector<double> l;
    if (!BT.alberoBinVuoto()) {
        int dim = BT.altezza_nodo(BT, BT.radice())+1 ;
        T v[dim];
        for (int i = 0; i < dim; i++) {
            v[i] = 0;
        }
        this->sommaLivello(BT, BT.radice(), 0, v);

        for (int i = 0; i < dim; i++) {
            int c = 0;
            numNodiInLiv(BT, BT.radice(), i, c);
            l.inserisciCoda((double) v[i] / c);
        }
    }
    return l;
}


//Somma i valori di tutti i nodi di ogni livello
template <class T>
void sum_mean_bin<T>::sommaLivello(alberoBinario_pt<T> & BT, typename alberoBinario_pt<T>::nodo n, int liv, T * v)  {
    v[liv]+=BT.leggiNodo(n);
    if (!BT.sinistroVuoto(n)) sommaLivello(BT,BT.figlioSinistro(n),liv+1,v);
    if (!BT.destroVuoto(n)) sommaLivello(BT,BT.figlioDestro(n),liv+1,v);
}

//CALCOLA IL NUMERO AL LIVELLO liv
template<class T>
void sum_mean_bin<T>::numNodiInLiv(alberoBinario_pt<T> & BT, typename alberoBinario_pt<T>::nodo n, int liv , int & counter) {
    if (!BT.sinistroVuoto(n)) numNodiInLiv(BT,BT.figlioSinistro(n),liv,counter);
    if (!BT.destroVuoto(n)) numNodiInLiv(BT,BT.figlioSinistro(n),liv,counter);
    if (BT.profondita_nodo(BT,n)==liv) counter++;

}
#endif //REALIZZAZIONI_SOMMAMEDIALIVELLI_H
