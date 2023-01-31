#include "alberoBinario.h"
#include <stdexcept>

#ifndef REALIZZAZIONI_ALBEROBINARIO_ARRAY_H
#define REALIZZAZIONI_ALBEROBINARIO_ARRAY_H

template<class T>
class alberoBinario_array;


template<class T>
class record {
    friend class alberoBinario_array<T>;

public:
    record &operator=( record<T> &r) {
        this->valore = r.valore;
        this->usato = r.usato;
        return *this;
    }

    bool operator== (record<T>&r )
    {
        return ((valore==r.valore) && (usato==r.usato));
    }

    bool operator !=(record<T>&r)
    {
        return !(this->operator==(r));
    }


private:
    //Ogni elemento dell'array è costituito dall'elemento da memorizzare e da un valore che indica se fa parte o meno dell'albero (false di default)
    T valore;
    bool usato;
};

template<class T>
class alberoBinario_array : public alberoBin<T, int> {
public:
    //TIPO
    typedef typename alberoBin<T, int>::tipoElem tipoElem;
    typedef typename alberoBin<T, int>::nodo nodo;

    //COSTRUTTORE
    alberoBinario_array();

    //COSTRUTTORE CON UN NUMERO DI NODI GIA DICHIARATO
    alberoBinario_array(int);

    //COSTRUTTORE COPIA
    alberoBinario_array(alberoBinario_array<T> &);

    //DISTRUTTORE
    ~alberoBinario_array();


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

     //SOVRASCRIZIONE OPERATORI
     bool operator == (const alberoBinario_array<T>&);
     alberoBinario_array<T>& operator = (const alberoBinario_array<T>&);

private:
    //array che contiene gli elementi
    record<T> *elementi;
    //lunghezza array
    int lunghezzaArray;
    //numero nodi
    int numNodi;
    //funzioni di servizio non accessibili all'utente
    void cambiaDimensione(record<T> *&, int, int);

};

// CREAZIONE DI UN ALBERO
// POST CONDIZIONE: Albero vuoto
template<class T>
alberoBinario_array<T>::alberoBinario_array() {
    //inizializzo l'arrya che conterrà gli elementi dell'albero con un numero di elementi arbitrario
    lunghezzaArray = 20;
    elementi = new record<T>[lunghezzaArray];
    numNodi = 0;
    for (int i = 0; i < lunghezzaArray; i++) {
        elementi[i].usato = false;
    }
}

// CREAZIONE DI UN ALBERO
// POST CONDIZIONE: Albero vuoto
template<class T>
alberoBinario_array<T>::alberoBinario_array(int dim) {
    //inizializzo l'arrya che conterrà gli elementi dell'albero con un numero di elementi scelto dall'utente

    elementi = new record<T>[dim];
    lunghezzaArray = dim;
    numNodi = 0;
    for (int i = 0; i < lunghezzaArray; i++) {
        elementi[i].usato = false;
    }
}

//costruttore di copia
template<class T>
alberoBinario_array<T>::alberoBinario_array(alberoBinario_array<T> &BT) {
    this->numNodi = BT.numNodi;
    this->lunghezzaArray = BT.lunghezzaArray;
    this->elementi = new record<T>[lunghezzaArray];
    for (int i = 0; i < lunghezzaArray; i++) {
        elementi[i] = BT.elementi[i];
    }
}

//distruttore
template<class T>
alberoBinario_array<T>::~alberoBinario_array() {
    delete[] elementi;
}

/*
 * Verifica se un'albero è vuoto o meno
 * POST CONDIZIONE: Return true se l'albero è vuoto, false altrimenti
 */
template <class T>
bool alberoBinario_array<T>::alberoBinVuoto() const
{
    if (!elementi[0].usato) return true;
    else return (numNodi==0);
}

/*
 * Restituisce la radice dell' albero
 * PRE CONDIZIONE: Albero non vuoto
 * POST CONDIZIONE: Viene restituita la radice dell'albero
 */
template <class T>
typename alberoBinario_array<T>::nodo alberoBinario_array<T>::radice() const
{
    if (numNodi!=0)
    return 1;
    else throw std::out_of_range("RADICE INESISTENTE"); //albero vuoto
}

/*
 * Restituisce il nodo padre di n
 * PRE CONDIZIONE: Albero non vuoto, n diverso dalla radice
 * POST CONDIZIONE: Viene restituito il genitore di n
 */
template <class T>
typename alberoBinario_array<T>::nodo alberoBinario_array<T>::genitore( nodo n)  const
{
    if (!alberoBinVuoto()) {
        if (n > 1) {
            //CONTROLLO SE FIGLIO SINISTRO
            if ((n % 2 == 0)) return n / 2;
            else return (n - 1) / 2;
        } else throw std::out_of_range("LA RADICE NON HA UN GENITORE");
    }
    else  throw std::out_of_range("ALBERO VUOTO");
}

/*
 * Si restituisce il figlio dinistro di n
 * PRE CONDIZIONE: Albero non vuoto e n ha un figlio sinistro
 * POST CONDIZIONE: Viene restituito il figlio sinistro di n
 */
template <class T>
typename alberoBinario_array<T>::nodo alberoBinario_array<T>::figlioSinistro( nodo n) const
{
    if (!alberoBinVuoto()) {
        if (!sinistroVuoto(n) && n > 0)
            return n * 2;
        else {
            if (n > 0) throw std::out_of_range("IL NODO NON HA UN FIGLIO SINISTRO");
            else throw std::out_of_range("NODO NON ESISTENTE");
        }
    }
    else throw std::out_of_range("ALBERO VUOTO");

}


/*
 * Si restituisce il figlio destro di n
 * PRE CONDIZIONE: Albero non vuoto e n ha un figlio destro
 * POST CONDIZIONE: Viene restituito il figlio destro di n
 */
template <class T>
typename alberoBinario_array<T>::nodo alberoBinario_array<T>::figlioDestro( nodo n) const
{
    if (!alberoBinVuoto()) {
        if (!destroVuoto(n) && n > 0) {
            return ((n * 2) + 1);
        }
        else {
            if (n > 0) throw std::out_of_range("IL NODO NON HA UN FIGLIO DESTRO");
            else throw std::out_of_range("NODO NON ESISTENTE");
        }
    }
    else throw std::out_of_range("ALBERO VUOTO");

}

/*
 * Verifica esistenza figlio sinistro
 * PRE CONDIZIONE: Albero non vuoto
 * POST CONDIZIONE: return TRUE se n non ha un figlio sinistro, FALSE altrimenti
 */
template <class T>
bool alberoBinario_array<T>::sinistroVuoto( nodo n) const
{
    if (!alberoBinVuoto()) {
        int pos = ((n * 2) - 1);
        if (pos > lunghezzaArray) {
            return true;
        }
        return !elementi[pos].usato;
    }
    else throw std::out_of_range("ALBERO VUOTO");

}

/*
 * Verifica esistenza figlio destro
 * PRE CONDIZIONE: Albero non vuoto
 * POST CONDIZIONE: return TRUE se n non ha un figlio destro, FALSE altrimenti
 */
template <class T>
bool alberoBinario_array<T>::destroVuoto( nodo n) const
{
    if (!alberoBinVuoto()) {
        int pos = (n * 2);

        if (pos > lunghezzaArray) {

            return true;
        }

        return !elementi[pos].usato;
    }
    else throw std::out_of_range("ALBERO VUOTO");

}

/*
 * Cancellazione del nodo n e di tutti i suoi discendenti
 * PRE CONDIZIONE: Albero non vuoto
 * POST CONDIZIONE: Viene cancellato il nodo n e tutti i suoi discendenti
 */
template <class T>
void alberoBinario_array<T>::cancellaSottoalbero( nodo n)
{
    if (!alberoBinVuoto()) {
        numNodi--;
        int pos = n - 1;
        elementi[pos].usato = false;
        if (!sinistroVuoto(n)) cancellaSottoalbero(figlioSinistro(n));
        if (!destroVuoto(n)) cancellaSottoalbero(figlioDestro(n));
    }
    else throw std::out_of_range("ALBERO VUOTO");
}


// Restituisce il valore associato al nodo n
template <class T>
typename alberoBinario_array<T>::tipoElem alberoBinario_array<T>::leggiNodo( nodo n)  const
{
    int pos=n-1;
    return elementi[pos].valore;
}

//scrive il valore nel nodo n
template <class T>
void alberoBinario_array<T>::scriviNodo(const nodo n,  tipoElem valore)
{
    int pos=n-1;
     elementi[pos].valore=valore;
     elementi[pos].usato=true;
}

/*
 * Inserisce la radice dell'albero
 * PRE CONDIZIONE: Albero vuoto
 * POST CONDIZIONE: L'albero ha solo la radice
 */
template <class T>
void alberoBinario_array<T>::inserisciRadice( tipoElem valore)
{
     if (alberoBinVuoto())
     {
         elementi[0].valore=valore;
         elementi[0].usato=true;
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
void alberoBinario_array<T>:: inserisciSinistro( nodo n ,  tipoElem valore)
{
    if (!alberoBinVuoto()) {
        if (sinistroVuoto(n)) {
            int pos = (n * 2) - 1;
            if (pos >= lunghezzaArray-1) {
                int nuovaDim=lunghezzaArray*2;
                cambiaDimensione(elementi, lunghezzaArray, nuovaDim);
                lunghezzaArray *= 2;
            }

            elementi[pos].valore = valore;
            elementi[pos].usato = true;
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
void  alberoBinario_array<T>::inserisciDestro( nodo n ,  tipoElem valore)
{
    if (!alberoBinVuoto()) {
        if (destroVuoto(n)) {
            int pos = (n * 2);
            if (pos >= lunghezzaArray-1) {
                int nuovaDim=lunghezzaArray*2;
                cambiaDimensione(elementi, lunghezzaArray, nuovaDim);
                lunghezzaArray *= 2;
            }

            elementi[pos].valore = valore;
            elementi[pos].usato = true;
            numNodi++;
        } else throw std::out_of_range("ESISTE GIA UN FIGLIO DESTRO");
    }
    else throw std::out_of_range("ALBERO VUOTO");
}


//Cambio dimensione dell'array e ricopio l'albero
template<class T>
void alberoBinario_array<T>::cambiaDimensione(record<T> *&elementi, int vecchiaDimensione, int nuovaDimensione) {
    record<T> * tmp=new record<T>[nuovaDimensione];
    for (int i=0;i<nuovaDimensione;i++)
    {
        tmp[i].usato=false;
    }
    for (int i=0;i<vecchiaDimensione;i++)
    {
        tmp[i].usato=elementi[i].usato;
        tmp[i].valore=elementi[i].valore;
    }
    delete [] elementi;
    elementi=tmp;

}

template <class T>
bool alberoBinario_array<T>::operator == (const alberoBinario_array<T>& BT)
{
    if (numNodi!=BT.numNodi || lunghezzaArray!=BT.lunghezzaArray) return false;
    {
        for (int i=0;i<lunghezzaArray;i++)
        {
            if (elementi[i]!=BT.elementi[i]) return false;
        }
        return true;
    }
}

template<class T>
alberoBinario_array<T>& alberoBinario_array<T>::operator=(const alberoBinario_array<T> &BT) {
if (this!=&BT)
{
    this->numNodi = BT.numNodi;
    this->lunghezzaArray = BT.lunghezzaArray;
    this->elementi = new record<T>[lunghezzaArray];
    for (int i = 0; i < lunghezzaArray; i++) {
        elementi[i] = BT.elementi[i];
    }
}
return *this;
}


#endif //REALIZZAZIONI_ALBEROBINARIO_ARRAY_H
