#include <stdexcept>
#include <ostream>

using namespace std;
#ifndef REALIZZAZIONI_CODAV_H
#define REALIZZAZIONI_CODAV_H

template<class T>
class codav {
public:
    typedef T tipoelem;
    //Costruttore (rimpiazza il creaCoda)
    codav();

    //Costruttore con numero elementi definito(rimpiazza il creaCoda)
    codav(int);

    //costruttore per copia (rimpiazza il creaCoda)
    codav(const codav<T> &);

    //distruttore
    ~codav();

    bool codaVuota() const;

    tipoelem leggiCoda() const;

    void fuoriCoda();

    void incoda(const tipoelem &);

    //funzioni aggiuntive
    int lunghezza() const;
    bool esiste(const tipoelem&);

    codav<T> &operator=(const codav<T> &);

    bool operator==(const codav<T> &);



    template<class T1>
    friend ostream &operator<<(ostream &, const codav<T1> &);

private:
    int lunghezzaArray;
    int testa; //testa della coda
    int coda; //coda da coda
    tipoelem *elementi; //array in cui memorizzo gli elementi della coda
//FUNZIONE DI SERVIZIO NON ACCESSIBILE AGLI UTENTI
    void cambiaDimensione(tipoelem *&, int, int);
};

/*
 * Creazione di una coda
 * POST CONDIZIONE: coda vuota
 */
template<class T>
codav<T>::codav() {
    lunghezzaArray = 10;
    elementi = new tipoelem[lunghezzaArray]; //lunghezza arbitraria
    testa = 0;
    coda = 0;
}

/*
 * Creazione di una coda
 * POST CONDIZIONE: coda vuota
 */
template<class T>
codav<T>::codav(int dim) {
    lunghezzaArray = dim;
    elementi = new tipoelem[lunghezzaArray]; //lunghezza definita dall'uente
    testa = 0;
    coda = 0;
}
//costruttore copia
template<class T>
codav<T>::codav(const codav<T> &c) {
    lunghezzaArray = c.lunghezzaArray;
    testa = c.testa;
    coda = c.coda;
    elementi = new tipoelem[lunghezzaArray];
    for (int i = testa; i < coda; i++) {
        elementi[(testa + i) % lunghezzaArray] = c.elementi[(testa + i) % lunghezzaArray];
    }
}

//distruttore
template<class T>
codav<T>::~codav() {

    delete[] elementi;
}
//restituisce il numero di elementi nella coda
template<class T>
int codav<T>::lunghezza() const {
    return coda;
}

/*
 * Verifica se la coda è vuota
 * POST CONDIZIONE: Return TRUE se la coda è vuota, FALSE altrimenti
 */
template<class T>
bool codav<T>::codaVuota() const {
    return coda == 0;
}

/*
 * Restiuisce l'elemento in testa
 * PRE CONDIZIONE: Coda non vuota
 * POST CONIDIZIONE: Restituisco l'elemento in testa
 */
template<class T>
typename codav<T>::tipoelem codav<T>::leggiCoda() const {
    if (coda > 0) {
        return elementi[testa];
    } else throw std::out_of_range("LA CODA E' VUOTA");
}

/*
 * Elimina l'elemento in testa
 * PRE CONDIZIONE: Coda non vuota
 * POST CONDIZIONE: Elimino l'elemento che si trova in testa alla coda
 */
template<class T>
void codav<T>::fuoriCoda() {
    if (coda > 0) {
        testa = (testa + 1) % lunghezzaArray;
        coda--;
    } else throw std::out_of_range("LA CODA E' VUOTA");
}

/*
 * Inserisce un elemento nella coda
 * POST CONDIZIONE: Inserisco l'elemento alla coda della coda
 */
template<class T>
void codav<T>::incoda(const tipoelem &e) {
    if (coda == lunghezzaArray) {cambiaDimensione(elementi, lunghezzaArray, lunghezzaArray * 2);
    lunghezzaArray *= 2;}
    elementi[(testa + coda) % lunghezzaArray] = e;
    coda++;
}

template<class T>
void codav<T>::cambiaDimensione(tipoelem *&e, int vecchiaDimensione, int nuovaDimensione) {
    int numero;
    (vecchiaDimensione < nuovaDimensione) ? numero = vecchiaDimensione : numero = nuovaDimensione;
    //numero=min(vecchiaDimensione, nuovaDimensione);
    tipoelem *tmp = new tipoelem[nuovaDimensione];
    for (int i = 0; i < numero; i++) {
        tmp[(testa + i) % lunghezzaArray] = elementi[(testa + i) % lunghezzaArray];
    }
    delete[] elementi;
    elementi = tmp;
    testa = 0;
}


template<class T1>
ostream &operator<<(ostream &os, const codav<T1> &c) {
    int letti = 0;
    int i = (c.testa) % c.lunghezzaArray;
    os << "[";
    while (letti < c.coda) {
        if (i == (c.testa % c.lunghezzaArray)) {
            os << c.elementi[i];
        } else os << "," << c.elementi[i];
        letti++;
        i++;
    }
    os << "]" << endl;
    return os;
}

template<class T>
bool codav<T>::operator==(const codav<T> &c) {
    if (coda != c.coda) return false;
    for (int i = 0; i < coda; i++) {
        if (elementi[i] != c.elementi[i]) return false;
    }
    return true;
}


template<class T>
codav<T> &codav<T>::operator=(const codav<T> &c) {
    if (this != &c) {
        this->~coda();
        lunghezzaArray = c.lunghezzaArray;
        testa = c.testa;
        coda = c.coda;
        elementi = new tipoelem[lunghezzaArray];
        for (int i = testa; i < coda; i++) {
            elementi[(testa + i) % lunghezzaArray] = c.elementi[(testa + i) % lunghezzaArray];
        }
    }
    return *this;
}

//Restituisce TRUE se l'elemento appartiene alla coda, FALSE altrimenti

template <class T>
bool codav<T>::esiste(const tipoelem & e) {
    if (!codaVuota())
    {
        int i=testa;
        int trov=false;
        while (i<coda && !trov)
        {
            if (elementi[(testa+i)%lunghezzaArray]==e) trov=true;
            else i++;
        }
        return trov;
    }
    else return false;
}


#endif //REALIZZAZIONI_CODAV_H
