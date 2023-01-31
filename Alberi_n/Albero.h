#include <vector>
#include <algorithm>
#ifndef REALIZZAZIONI_ALBERO_H
#define REALIZZAZIONI_ALBERO_H
using namespace std;
template<class I, class N>
class Albero {
public:
    typedef I tipoElem;
    typedef N nodo;

    //virtual void creaAlbero () = 0; SOSTITUITO DAL COSTRUTTORE
    virtual bool alberoVuoto () const = 0;
    virtual void inserisciRadice (tipoElem) = 0;
    virtual nodo radice () const = 0;
    virtual nodo padre (nodo) const = 0;
    virtual bool foglia (nodo) const = 0;
    virtual nodo primoFiglio (nodo) const = 0;
    virtual bool ultimoFratello (nodo) const = 0;
    virtual nodo fratelloSuccessivo (nodo) const = 0;
    virtual void insFirstSubTree (nodo, Albero<I,N> &) = 0;
    virtual void insSubTree (nodo, Albero<I,N> &) = 0;
    virtual void cancSottoAlbero (nodo) = 0;
    virtual int numeroNodi() const =0;
    virtual void scriviNodo (nodo, tipoElem) = 0;
    virtual tipoElem leggiNodo (nodo) const = 0;
    int profonditaAlbero();
    int larghezza();
private:
    int profondita(nodo);
   void larghezza(nodo,vector<int>& v, int liv);

};

//resituisce la profondità di un albero (ovvero il cammino di lunghezza massima che parte dalla radice e arriva a una foglia)
template<class I,class N>
int Albero<I, N>::profonditaAlbero() {
        if (alberoVuoto())
            return 0;
        else {
            return profondita(radice());
        }
}

template <class I, class N>
int Albero<I,N>::profondita(Albero::nodo n) {
    //se il nodo è foglia ritorno 0
    if (foglia(n)) return 0;
    //se il nodo non è foglia allora richiamo la funzione sui suoi figli e fratelli
    //inizializzo un variabile m=1. Questa indica la profondità attuale
    int m = 1;
    int c;
    nodo k = primoFiglio(n);
    while (!ultimoFratello(k)) {
        //calcolo la profondità di ogni fratello del nodo n. Se questa è maggiare della profondità attuale allora aggiorno la profondità attuale
        c = profondita(k);
        if (c > m) {
            m = c;
        }
        k = fratelloSuccessivo(k);
    }
    c = profondita(k);
    if (c > m) {
        m = c;
    }
    //ritorno la profondità attuale piu 1
    return (m + 1);
}

//Viene restituita la larghezza di un'albero n-ario (ovvero il numero massimo di nodi presenti sullo stesso livello)
template <class I,class N>
int Albero<I, N>::larghezza() {
    if (!alberoVuoto()) {
       vector<int> v;
       larghezza(radice(),v,0);
        return *max_element(v.begin(),v.end());
    }
    else return 0;
}

template <class I,class N>
void Albero<I,N>::larghezza(nodo n, vector<int> &v, int liv) {
    //se il livello è maggiore della dimensione del vettore allora inseriamo un nuovo contatore all'interno del vettore (è stato raggiungo un livello non visitato)
    if (liv >= v.size()) v.push_back(1);
    else v[liv]++;

    if (!foglia(n)) {
        nodo c = primoFiglio(n);
        int newLiv = liv + 1;
        while (!ultimoFratello(c)) {
            larghezza(c, v, newLiv);
            c = fratelloSuccessivo(c);
        }
        larghezza(c, v, newLiv);
    }
}

#endif //REALIZZAZIONI_ALBERO_H
