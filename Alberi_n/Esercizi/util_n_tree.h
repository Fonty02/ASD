
#include "../AlberoPt.h"
#ifndef REALIZZAZIONI_UTIL_N_TREE_H
#define REALIZZAZIONI_UTIL_N_TREE_H
template <class T>
class util_n_tree{
public:
    typedef typename alberoPt<T>::nodo nodo;
    util_n_tree()=default;
    ~util_n_tree()=default;
    int n_leaf(alberoPt<T>&);
    int n_level(alberoPt<T>&, int k);

private:
    void n_leaf(alberoPt<T>&, nodo   ,int  &);
    void n_level(alberoPt<T>&, nodo   ,int  &, int,int);
};

//la funzione restituisce il numero di foglie presenti in un albero n-ario
template<class T>
int util_n_tree<T>::n_leaf(alberoPt<T> & A) {
    //se l'albero è vuoto esso ha 0 foglie
    if (A.alberoVuoto()) return 0;
    else
    {
        int c=0;
        //il numero viene inizializzato a 0
        n_leaf(A,A.radice(),c);
        return c;
    }
}

template <class T>
void util_n_tree<T>::n_leaf(alberoPt<T> &A , nodo n , int & c) {
    //se il nodo è foglia incremento il numero delle foglie
    if (A.foglia(n)) c++;
        if (!A.ultimoFratello(n)) {
            //se il nodo ha un fratello successivo richiamo la funzione sul fratello
            n_leaf(A,A.fratelloSuccessivo(n),c);
        }
        if (!A.foglia(n)) {
            //se il nodo non è foglia richiamo la funzione sul primo figlio del nodo
            n_leaf(A,A.primoFiglio(n),c);
    }
}


//la funzione restituisce il numero di nodi che si trovano al livello K
template <class T>
int util_n_tree<T>::n_level(alberoPt<T> &A, int k) {
    //se l'albero è vuoto oppure K è maggiore della profonditò dell'albero allora ci sono 0 foglie al livello k
    if (A.alberoVuoto() && k<=A.profonditaAlbero()) return 0;
    else
    {
        //inizializzo il numero di foglie al livello K a 0. Richiamo la funzione sulla radice, che si trova a livello 0
        int c=0;
        n_level(A,A.radice(),c,k,0);
        return c;
    }
}


template <class T>
void util_n_tree<T>::n_level(alberoPt<T> &A , nodo n, int & c,int liv,int nowLiv) {
//se il livello attuale coincide con il livello liv allora incremento il numero di nodi a livello liv
    if (nowLiv==liv) c++;
        if (!A.ultimoFratello(n)) {
            //se il nodo ha un fratello richiamo la funzione sul suo fratello (il livello attuale rimane lo stesso)
            n_level(A,A.fratelloSuccessivo(n),c,liv,nowLiv);
        }
        if (!A.foglia(n)) {
            //se il nodo ha un figlio, richiamo la funzione sul primo figlio (il livello attuale viene incrementanto di uno)
            n_level(A,A.primoFiglio(n),c,liv,nowLiv+1);
        }
}
#endif //REALIZZAZIONI_UTIL_N_TREE_H
