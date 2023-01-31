#include "alberoBinario.h"
#include <stdexcept>
#ifndef REALIZZAZIONI_ALBEROBINARIO_PT_H
#define REALIZZAZIONI_ALBEROBINARIO_PT_H
template<class T>
class alberoBinario_pt;


template<class T>
class nodoT {
    friend class alberoBinario_pt<T>;

private:
    // Il nodo è costituito dal valore che esso memorizza, da un puntatore al padre (nullptr per le radici),  da un puntatore al figlioSinistro (nullptr se non esiste) e da un puntatore al figlioDestro (nullptr se non esiste)
    T valore;
    nodoT<T> *padre;
    nodoT<T>* figlio_sinistro;
    nodoT<T>* figlio_destro;
};

template<class T>
class alberoBinario_pt : public alberoBin<T, nodoT<T>*> {
public:
    //TIPO
    typedef typename alberoBin<T, nodoT<T>*>::tipoElem tipoElem;
    typedef typename alberoBin<T, nodoT<T>*>::nodo nodo;

    //COSTRUTTORE
    alberoBinario_pt();

    //COSTRUTTORE COPIA
    alberoBinario_pt(alberoBinario_pt<T> &);

    //DISTRUTTORE
    ~alberoBinario_pt();


    //OPERATORI
    // void crea(); SOSTITUITO DAL COSTRUTTORE
    bool alberoBinVuoto() const;
    nodo radice()const ;
    nodo genitore( nodo) const ; //padre
    nodo figlioSinistro( nodo) const;
    nodo figlioDestro( nodo) const ;
    bool sinistroVuoto( nodo) const;
    bool destroVuoto( nodo) const;
    void cancellaSottoalbero( nodo);
    tipoElem leggiNodo( nodo) const;
    void scriviNodo(const nodo,  tipoElem);
    void inserisciRadice( tipoElem);
    void inserisciSinistro( const nodo,  tipoElem);
    void inserisciDestro(const nodo,  tipoElem);

    //SERVIZIO

    //Restituisce il numero dei nodi dell'albero
    int getN()
    {
        return numNodi;
    }

    //Inverte l'albero
    void inverti();

    //SOVRASCRIZIONE OPERATORI
    bool operator == (const alberoBinario_pt<T>&);
    alberoBinario_pt<T>& operator = (const alberoBinario_pt<T>&);

private:
    //puntatore di accesso all'albero (nullptr se albero vuoto)
    nodoT<T>* root;
    //numero di nodi dell'albero
    int numNodi;
    //FUNZIONI DI SERVIZIO NON ACCESSIBILI ALL'UTENTE
    nodoT<T> * copiaNodo( nodoT<T> *,  nodoT<T> *);
    void cancellaNodo(nodoT<T>*);
    void cancellaSinistro(nodoT<T>*);
    void cancellaDestro(nodoT<T>*);
    bool confrontaNodi(nodoT<T>*,nodoT<T>*);
    void inverti(nodoT<T>* r);
};


// CREAZIONE DI UN ALBERO
// POST CONDIZIONE: Albero vuoto
template<class T>
alberoBinario_pt<T>::alberoBinario_pt() {
    root= nullptr;
    numNodi = 0;
}

//costruttore di copia
template<class T>
alberoBinario_pt<T>::alberoBinario_pt(alberoBinario_pt<T> &BT) {
    numNodi=0;
    root= copiaNodo(BT.root, nullptr);
    }


//la funzione permette di copiare copiare un nodo in un altro
template <class T>
nodoT<T> *alberoBinario_pt<T>::copiaNodo( nodoT<T> * daCopiare,  nodoT<T> * padre) {
    if (daCopiare== nullptr)
        return nullptr;
    nodoT<T>* nuovoNodo=new nodoT<T>;
    nuovoNodo->padre=padre;
    nuovoNodo->valore=daCopiare->valore;
    nuovoNodo->figlio_sinistro= copiaNodo(daCopiare->figlio_sinistro,daCopiare);
    nuovoNodo->figlio_destro= copiaNodo(daCopiare->figlio_destro,daCopiare);
    numNodi++;
    return nuovoNodo;
}

//La funzione permette di cancellare un nodo e tutti i suoi discendenti
template <class T>
void alberoBinario_pt<T>::cancellaNodo(nodoT<T> * daCancellare) {
    if (daCancellare!= nullptr)
    {
        cancellaNodo(daCancellare->figlio_sinistro);
        cancellaNodo(daCancellare->figlio_destro);
        delete daCancellare;
        numNodi--;
    }
}

//cancella il sottoalbero sinistro del nodo scelto
template <class T>
void alberoBinario_pt<T>::cancellaSinistro(nodoT<T> * daCancellare) {
    if (daCancellare!= nullptr)
    {
        cancellaNodo(daCancellare->figlio_sinistro);
        daCancellare->figlio_sinistro= nullptr;
    }
}

//cancella il sottoalbero destro del nodo scelto
template <class T>
void alberoBinario_pt<T>::cancellaDestro(nodoT<T> * daCancellare) {
    if (daCancellare!= nullptr)
    {
        cancellaNodo(daCancellare->figlio_destro);
        daCancellare->figlio_destro= nullptr;
    }
}

//distruttore
template<class T>
alberoBinario_pt<T>::~alberoBinario_pt() {
    if (!alberoBinVuoto())
        cancellaSottoalbero(root);
    else {
        root = nullptr;
        delete root;
    }
}

/*
 * Verifica se un'albero è vuoto o meno
 * POST CONDIZIONE: Return true se l'albero è vuoto, false altrimenti
 */
template <class T>
bool alberoBinario_pt<T>::alberoBinVuoto() const
{
    return (root== nullptr);
}
/*
 * Restituisce la radice dell' albero
 * PRE CONDIZIONE: Albero non vuoto
 * POST CONDIZIONE: Viene restituita la radice dell'albero
 */
template <class T>
typename alberoBinario_pt<T>::nodo alberoBinario_pt<T>::radice() const
{
    if (root!= nullptr)
    return root;
    else throw std::out_of_range("RADICE INESISTENTE"); //albero vuoot
}

/*
 * Restituisce il nodo padre di n
 * PRE CONDIZIONE: Albero non vuoto, n diverso dalla radice
 * POST CONDIZIONE: Viene restituito il genitore di n
 */
template <class T>
typename alberoBinario_pt<T>::nodo alberoBinario_pt<T>::genitore( nodo n)  const
{
    if (!alberoBinVuoto()) {
        if (n != root) {
            return n->padre;
        } else throw std::out_of_range("LA RADICE NON HA UN GENITORE");
    }
    else throw std::out_of_range("ALBERO VUOTO");
}

/*
 * Si restituisce il figlio dinistro di n
 * PRE CONDIZIONE: Albero non vuoto e n ha un figlio sinistro
 * POST CONDIZIONE: Viene restituito il figlio sinistro di n
 */
template <class T>
typename alberoBinario_pt<T>::nodo alberoBinario_pt<T>::figlioSinistro( nodo n) const {
    if (!alberoBinVuoto()) {
        if (n != nullptr) {
            if (!sinistroVuoto(n))
                return n->figlio_sinistro;
            else throw std::out_of_range("IL NODO NON HA UN FIGLIO SINISTRO");
        } else throw std::out_of_range("NODO NON ESISTENTE");
    }
    else throw std::out_of_range("ALBERO VUOTO");

}
/*
 * Si restituisce il figlio destro di n
 * PRE CONDIZIONE: Albero non vuoto e n ha un figlio destro
 * POST CONDIZIONE: Viene restituito il figlio destro di n
 */
template <class T>
typename alberoBinario_pt<T>::nodo alberoBinario_pt<T>::figlioDestro( nodo n) const {
    if (!alberoBinVuoto()) {
    if (n != nullptr) {
        if (!destroVuoto(n))
            return n->figlio_destro;
        else throw std::out_of_range("IL NODO NON HA UN FIGLIO DESTRO");
    } else throw std::out_of_range("NODO NON VALIDO");
}
    else throw std::out_of_range("ALBERO VUOTO");

}


/*
 * Verifica esistenza figlio sinistro
 * PRE CONDIZIONE: Albero non vuoto
 * POST CONDIZIONE: return TRUE se n non ha un figlio sinistro, FALSE altrimenti
 */
template <class T>
bool alberoBinario_pt<T>::sinistroVuoto( nodo n) const
{
    if (!alberoBinVuoto())
return (n->figlio_sinistro== nullptr);
    else throw std::out_of_range("ALBERO VUOTO");

}

/*
 * Verifica esistenza figlio destro
 * PRE CONDIZIONE: Albero non vuoto
 * POST CONDIZIONE: return TRUE se n non ha un figlio destro, FALSE altrimenti
 */
template <class T>
bool alberoBinario_pt<T>::destroVuoto( nodo n) const
{
    if (!alberoBinVuoto())
        return (n->figlio_destro== nullptr);
    else throw std::out_of_range("ALBERO VUOTO");

}

/*
 * Cancellazione del nodo n e di tutti i suoi discendenti
 * PRE CONDIZIONE: Albero non vuoto
 * POST CONDIZIONE: Viene cancellato il nodo n e tutti i suoi discendenti
 */
template <class T>
void alberoBinario_pt<T>::cancellaSottoalbero( nodo n)
{
    if (!alberoBinVuoto()) {
        if (n->padre == nullptr) {
            cancellaNodo(n);
            root = nullptr;
        } else {
            if (n->padre->figlio_sinistro == n)
                cancellaSinistro(n->padre);
            else
                cancellaDestro(n->padre);
        }
    }
    else throw std::out_of_range("ALBERO VUOTO");

}

// Restituisce il valore associato al nodo n
template <class T>
typename alberoBinario_pt<T>::tipoElem alberoBinario_pt<T>::leggiNodo( nodo n)  const
{
    return n->valore;
}

//scrive il valore nel nodo n
template <class T>
void alberoBinario_pt<T>::scriviNodo(const nodo n,  tipoElem valore)
{
    n->valore=valore;
}
/*
 * Inserisce la radice dell'albero
 * PRE CONDIZIONE: Albero vuoto
 * POST CONDIZIONE: L'albero ha solo la radice
 */
template <class T>
void alberoBinario_pt<T>::inserisciRadice( tipoElem valore)
{
    if (alberoBinVuoto())
    {
        root=new nodoT<T>;
        root->padre= nullptr;
        root->figlio_sinistro= nullptr;
        root->figlio_destro= nullptr;
        root->valore=valore;
        numNodi++;
    }
    else throw std::out_of_range("L'ALBERO HA GIA' UNA RADICE");
}

/*
 * Inserisce il figlio sinistro del nodo n
 * PRE CONDIZIONE: Albero non vuoto e n non ha figlio sinistro
 * POST CONDIZIONE: Viene aggiunto il figlioSinistro a n con valore "valore"
 */
template <class T>
void alberoBinario_pt<T>:: inserisciSinistro( nodo n ,  tipoElem valore)
{
    if (!alberoBinVuoto()) {
        if (sinistroVuoto(n)) {
            nodoT<T> *nuovoNodo = new nodoT<T>;
            nuovoNodo->valore = valore;
            nuovoNodo->padre = n;
            nuovoNodo->figlio_sinistro = nullptr;
            nuovoNodo->figlio_destro = nullptr;
            n->figlio_sinistro = nuovoNodo;
            numNodi++;
        } else throw std::out_of_range("ESISTE GIA UN FIGLIO SINISTRO");
    }
    else throw std::out_of_range("ALBERO VUOTO");
}

/*
 * Inserisce il figlio destro del nodo n
 * PRE CONDIZIONE: Albero non vuoto e n non ha figlio destro
 * POST CONDIZIONE: Viene aggiunto il figlioDestro a n con valore "valore"
 */
template <class T>
void  alberoBinario_pt<T>::inserisciDestro( nodo n ,  tipoElem valore)
{
    if (!alberoBinVuoto()) {
        if (destroVuoto(n)) {
            nodoT<T> *nuovoNodo = new nodoT<T>;
            nuovoNodo->valore = valore;
            nuovoNodo->padre = n;
            nuovoNodo->figlio_sinistro = nullptr;
            nuovoNodo->figlio_destro = nullptr;
            n->figlio_destro = nuovoNodo;
            numNodi++;
        } else throw std::out_of_range("ESISTE GIA UN FIGLIO DESTRO");
    }
    else throw std::out_of_range("ALBERO VUOTO");
}




template <class T>
bool alberoBinario_pt<T>::operator == (const alberoBinario_pt<T>& BT)
{
    if (numNodi!=BT.numNodi) return false;
    {
       return confrontaNodi(root,BT.root);

    }
}


//la funzione restituisce true se due nodi sono uguali, false altrimenti
template <class T>
bool alberoBinario_pt<T>::confrontaNodi(nodoT<T> * n1, nodoT<T> * n2) {
    bool uguali=true;
    if (n1->valore==n2->valore)
    {
        if (n1->figlio_sinistro!= nullptr && n2->figlio_sinistro != nullptr)
        {
            uguali=confrontaNodi(n1->figlio_sinistro,n2->figlio_sinistro);
        }
        else return uguali;
        if (uguali && n1->figlio_destro!= nullptr && n2->figlio_destro != nullptr)
        {
            uguali=confrontaNodi(n1->figlio_destro,n2->figlio_destro);
        }
        else return uguali;
    }
    else uguali=false;
    return uguali;
}

template<class T>
alberoBinario_pt<T>& alberoBinario_pt<T>::operator=(const alberoBinario_pt<T> &BT) {
    if (this!=&BT)
    {
        numNodi=0;
        root= copiaNodo(BT.root, nullptr);
        }
    return *this;
}

//inversione
template <class T>
void alberoBinario_pt<T>::inverti() {
    if (!alberoBinVuoto())
    {
        inverti(radice());
    }
}

template <class T>
void alberoBinario_pt<T>::inverti(nodoT<T> *r) {
    if (r->figlio_sinistro!=nullptr)
    {
        inverti(r->figlio_sinistro);
    }
    if (r->figlio_destro!=nullptr)
    {
        inverti(r->figlio_destro);
    }
    if (r->figlio_sinistro!=nullptr && r->figlio_destro!=nullptr)
    {
         nodoT<T>* tmp=r->figlio_sinistro;
        r->figlio_sinistro=r->figlio_destro;
        r->figlio_destro=tmp;
    }
}

#endif //REALIZZAZIONI_ALBEROBINARIO_PT_H
