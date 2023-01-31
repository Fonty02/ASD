//
// REALIZZAZIONE DI UN ALBERO N-ARIO MEDIANTE PUNTATORI
//
#include "Albero.h"
#include <stdexcept>
#include <iostream>

#ifndef REALIZZAZIONI_ALBEROPT_H
#define REALIZZAZIONI_ALBEROPT_H

template<class T>
class alberoPt;


template<class T>
class nodoT {
    friend class alberoPt<T>;

public:
    nodoT() {
        padre = nullptr;
        primofiglio = nullptr;
        fratello = nullptr;
    }

private:
    //il nodo è costituito da un label di tipo T, da un puntatore al nodo padre, un puntatore al nodo figlio e un puntatore al fratello successivo
    T valore;
    nodoT *padre;
    nodoT *primofiglio;
    nodoT *fratello;
};


template<class T>
class alberoPt : public Albero<T, nodoT<T> *> {
public:
    typedef typename Albero<T, nodoT<T> *>::tipoElem tipoElem;
    typedef typename Albero<T, nodoT<T> *>::nodo nodo;

    //costruttore
    alberoPt();

    //costruttore di copia
    alberoPt(alberoPt<T> &);

    //distruttore
    ~alberoPt();

    //void creaAlbero(); SOSTITUITO DAL COSTRUTTORE
    bool alberoVuoto() const;

    void inserisciRadice(tipoElem);

    nodo radice() const;

    nodo padre(nodo) const;

    bool foglia(nodo) const;

    nodo primoFiglio(nodo) const;

    bool ultimoFratello(nodo) const;

    nodo fratelloSuccessivo(nodo) const;

    void insFirstSubTree(nodo, Albero<tipoElem, nodoT<T> *> &);

    void insSubTree(nodo, Albero<tipoElem, nodoT<T> *> &);

    void cancSottoAlbero(nodo);

    void scriviNodo(nodo, tipoElem);

    tipoElem leggiNodo(nodo) const;

    //ritorna il numero di nodi presenti nell'albero
    int numeroNodi() const {
        return this->numNodi;
    }


    //FUNZIONI DI SERVIZIO
    void inserisciPrimoFiglio(nodo, tipoElem);
    void inserisci(nodo, tipoElem);
    void stampaAlbero() const;

private:
    //l accesso all'albero avviene mediante il puntatore alla radice
    nodoT<T> *root;
    //numero di nodi presenti nell'albero
    int numNodi;

    //funzioni di servizio per l'implementazione
    void copia(nodo, nodo);
    void stampa(nodo) const;

};

//distruttore di un albero
template <class T>
alberoPt<T>::~alberoPt() {
    if (numNodi>0) cancSottoAlbero(root);
}

//costruttore di un albero. Sostituisce il meotodo creaAlbero
//POST CONDIZIONE: T = albero vuoto (0 nodi e assenza di radice)
template<class T>
alberoPt<T>::alberoPt() {
    numNodi = 0;
    root = nullptr;
}

//costruttore di copia
template<class T>
alberoPt<T>::alberoPt(alberoPt<T> &a) {
    root = nullptr;
    root = new nodoT<T>();
    numNodi=0;
    scriviNodo(root, a.leggiNodo(a.radice()));
    //se la radice dell'albero a non è foglia richiamo il metodo per copiare il tutto il sottoalbero della radice di a nella radice dell'albero attuale
    if (!a.foglia(a.radice()))  copia(root, a.primoFiglio(a.radice()));
    numNodi++;

}

//la funzione permette di copiare copiare un albero in un altro
template<class T>
void alberoPt<T>::copia(nodo n, nodo daCopiare) {
    if (daCopiare != nullptr) {
        if (daCopiare->fratello != nullptr)
            copia(n, daCopiare->fratello);
        inserisciPrimoFiglio(n, daCopiare->valore);
        if (daCopiare->primofiglio != nullptr)
            copia(primoFiglio(n), daCopiare->primofiglio);

    }
}



/*Funzione che permette di inserire il primoFiglio di un nodo
 * INPUT: Nodo n in cui vogliamo inserire un nuovo primoFoglio
 *              Valore di tipo tipoElem da inserire nel nuovo primoFiglio di n
 * OUTPUT: Albero T in cui al nodo n è stato inserito un nuovo primoFiglio di n che ha come label il valore e
 */
template<class T>
void alberoPt<T>::inserisciPrimoFiglio(nodo n, tipoElem e) {
    nodo l = new nodoT<T>();
    l->fratello = n->primofiglio;
    n->primofiglio = l;
    l->padre = n;
    l->valore = e;
    numNodi++;
}

/*Funzione che permette di inserire il fratello successivo di un nodo
 * INPUT: Nodo n in cui vogliamo inserire un nuovo fratelloSuccessivo
 *              Valore di tipo tipoElem da inserire nel nuovo fratelloSuccessivo di n
 * OUTPUT: Albero T in cui al nodo n è stato inserito un nuovo fratelloSuccessivo di nche ha come label il valore e
 */
template <class T>
void alberoPt<T>::inserisci(alberoPt::nodo n , alberoPt::tipoElem e) {
    //la radice non puo avere fratelli
    if (n != radice()) {
        nodo l = new nodoT<T>();
        l->fratello = n->fratello;
        n->fratello = l;
        l->padre = n->padre;
        l->valore=e;
        numNodi ++;
    }
    else cout<<"LA RADICE NON PUO' AVERE FRATELLI"<<endl;
}

/*
 * La funzione verifica se l'albero è vuoto o meno
 * POST CONDIZIONE: return TRUE se l'albero è vuoto, FALSE altrimenti
 */
template<class T>
bool alberoPt<T>::alberoVuoto() const {
    return (root == nullptr);
};

/*
 * Inserimento della radice all'interno di un albero
 * PRE CONDIZIONE: L'albero è vuoto
 * POST CONDIZIONE: L'albero è formata dalla sola radice a cui viene attribuito il valore e
 */
template<class T>
void alberoPt<T>::inserisciRadice(tipoElem e) {
    //controllo se l'albero è vuoto
    if (alberoVuoto()) {
        //creo un nodo che fungerà da radice, le assegno il valore e e setto tutti i suoi puntatori a null (in quanto la radice non può avere padre e fratelli e per ora non ha figli)
        root = new nodoT<T>;
        root->valore = e;
        root->fratello = nullptr;
        root->padre = nullptr;
        root->primofiglio = nullptr;
        numNodi++;
    }

}

/*
 * Viene restituita la radice dell'albero
 * PRE CONDIZIONE: Albero diverso dall'albero vuoto
 * POST CONDIZIONE: ritorno la radice dell'albero
 */
template<class T>
typename alberoPt<T>::nodo alberoPt<T>::radice() const {
    if (!this->alberoVuoto())
        return root;
    else throw std::out_of_range("ALBERO VUOTO");
}

/*
 * Viene restituito il padre del nodo n
 * PRE CONDIZIONE: Albero non vuoto AND  n diverso dalla radice
 * POST CONDIZIONE: viene restituito il nodo del padre
 */
template<class T>
typename alberoPt<T>::nodo alberoPt<T>::padre(nodo n) const {
    if (!alberoVuoto()) {
        if (n->padre != nullptr) {
            return n->padre;
        } else throw std::out_of_range("LA RADICE NON HA PADRE");
    }
    else throw std::out_of_range("ALBERO VUOTO");
}

/*
 * Si verifica se il nodo n è una foglia dell'albero o meno
 * PRE CONDIZIONE: Albero non vuoto
 * POST CONDIZIONE: return TRUE se n non ha figli, FALSE altrimenti
 */
template<class T>
bool alberoPt<T>::foglia(nodo n) const {
    if (!alberoVuoto())
        return (n->primofiglio == nullptr);
    else throw std::out_of_range("ALBERO VUOTO");
}

/*
 * Viene restituito il primoFiglio del nodo n
 * PRE CONDIZONE: Albero non vuoto e n non è foglia
 * POST CONDIZIONE: ritorno il primo figlio di n
 */
template<class T>
typename alberoPt<T>::nodo alberoPt<T>::primoFiglio(nodo n) const {
    if (!alberoVuoto()) {
        if (n->primofiglio != nullptr) {
            return n->primofiglio;
        } else throw std::out_of_range("IL NODO E' UNA FOGLIA");
    }
    else throw std::out_of_range("ALBERO VUOTO");
}

/*
 * Si verifica se il nodo n è l'ultimo dei fratelli
 * PRE CONDIZIONE: Albero non vuoto
 * POST CONDIZIONE: return TRUE se n non ha fratelli, FALSE altrimenti
 */
template<class T>
bool alberoPt<T>::ultimoFratello(nodo n) const {
    if (!alberoVuoto())
        return (n->fratello == nullptr);
    else throw std::out_of_range("ALBERO VUOTO");
}

/*
 * Viene restituito il fratello successivo di n
 * PRE CONDIZIONE: Albero non vuoto AND n non è l'ultimo fratello
 * POST CONDIZIONE: return il fratello successivo di n
 */
template<class T>
typename alberoPt<T>::nodo alberoPt<T>::fratelloSuccessivo(nodo n) const {
    if (!alberoVuoto()) {
        if (n->fratello != nullptr) {
            return n->fratello;
        } else throw std::out_of_range("IL NODO NON HA FRATELLI SUCCESSIVI");
    }
    else throw std::out_of_range("ALBERO VUOTO");
}

/*
 * L'albero a viene inserito come primoFiglio del nodo n
 * PRE CONDIZIONE: albero non vuoto, albero a non vuoto
 * POST CONDIZIONE: L'albero di partenza viene aggiornato prendendo la radice dell'albero a e inserendola come primoFiglio del nodo n (quindi viene aggiunto tutto l'albero)
 */
template<class T>
void alberoPt<T>::insFirstSubTree(nodo n, Albero<tipoElem, nodoT<T> *> &a) {
    if (!alberoVuoto() && !a.alberoVuoto()) {
       nodoT<T>* r1=new nodoT<T>();
       //creo un nuovo nodo e vi copio il contenuto della radice di a
        scriviNodo(r1,a.leggiNodo(a.radice()));
        //se a non è foglia copio tutto il suo sottoalbero in r1
        if (!a.foglia(a.radice())) copia(r1,a.primoFiglio(a.radice()));
        //inserisco il nuovo albero come primoFiglio di n
        r1->padre = n;
        r1->fratello = n->primofiglio;
        n->primofiglio = r1;
        numNodi++;
    } else throw std::out_of_range("UNO DEI DUE ALBERI E' VUOTO, OPERAZIONE IMPOSSIBILE");
}

/*
 * L' albero a viene inserito come fratelloSuccessivo del nodo n
 * PRE CONDIZIONE: albero non vuoto, albero a non vuoto, n non è radice
 * POST CONDIZIONE: L'albero di partenza viene aggiornato prendendo la radice dell'albero a e inserendola come fratelloSuccessivo del nodo n (quindi viene aggiunto tutto l'albero)
 */
template<class T>
void alberoPt<T>::insSubTree(nodo n, Albero<tipoElem, nodoT<T> *> &a) {
    if (!alberoVuoto() && !a.alberoVuoto()) {
        if (n != root) {
            //creo un nuovo nodo e vi copio il contenuto della radice di a
            nodoT<T>* r1=new nodoT<T>();
            scriviNodo(r1,a.leggiNodo(a.radice()));
            //se a non è foglia copio tutto il suo sottoalbero in r1
            if (!a.foglia(a.radice())) copia(r1,a.primoFiglio(a.radice()));
            //inserisco il nuovo albero come fratelloSuccessivo di n
            r1->fratello = n->fratello;
            r1->padre = n->padre;
            n->fratello = r1;
            numNodi++;
        } else throw std::out_of_range("LA RADICE NON PUO AVERE FRATELLI");
    } else throw std::out_of_range("UNO DEI DUE ALBERI E' VUOTO, OPERAZIONE IMPOSSIBILE");
}

/*
 * Cancellazione dall'albero del nodo n e tutti i suoi discendenti
 * PRE CONDIZIONE: Albero non vuoto
 * POST CONDIZIONE: Dall'albero è stato eliminato il nodo n e tutti i suoi discendenti
 */
template<class T>
void alberoPt<T>::cancSottoAlbero(nodo n) {
        if (!alberoVuoto()) {
            while (n->primofiglio != nullptr) {
                //finchè n ha ancora dei figli cancello tutti gli allberi che hanno come radice il primoFiglio di n
                cancSottoAlbero(n->primofiglio);
            }
            if (n != root) {
                //se il nodo non è radice e non ha fratelli allora aggiorno l'albero
                if (n->fratello == nullptr) n->padre->primofiglio->fratello = nullptr;
                //se il nodo non è radice ed è il primoFiglio allora aggiorno l'albero
                if (n->padre->primofiglio == n) n->padre->primofiglio = n->fratello;
            }
            //Cancello il nodo
            delete n;
            numNodi--;
        }
        else throw std::out_of_range("ALBERO VUOTO");
    }

/*
 * Funzione per scrivere il valore di un nodo
 * INPUT: nodo n in cui scrivere il valore
 *              valore e da scrivere
 * OUTPUT: il nodo n con il valore e inserito
 */
template<class T>
void alberoPt<T>::scriviNodo(nodo n, tipoElem e) {
    n->valore = e;
}

/*
 * Funzione per leggere il valore di un nodo
 * INPUT: nodo n del quale leggere il valore
 * OUTPUT: il valore di n
 */
template<class T>
typename alberoPt<T>::tipoElem alberoPt<T>::leggiNodo(nodo n) const {
    return n->valore;
}

/*
 * Funzione di stampa di un albero n-ario. La visita viene effettuata in pre-ordine partendo dall radice
 */
template<class T>
void alberoPt<T>::stampaAlbero() const {
    if (root != nullptr) {
        std::cout << "[";
        stampa(root);
        std::cout << "]" << std::endl;
    } else std::cout << "ALBERO VUOTO";
}

/*
 * Visita in pre-ordine dell'albero
 */
template<class T>
void alberoPt<T>::stampa(nodo n) const {
    if (n != nullptr) std::cout << n->valore << " ";
    if (!foglia(n))
    {
        nodo c= primoFiglio(n);
        while (!ultimoFratello(c))
        {
            stampa(c);
            c= fratelloSuccessivo(c);
        }
        stampa(c);
    }
}





#endif //REALIZZAZIONI_ALBEROPT_H
