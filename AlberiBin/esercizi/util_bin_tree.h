#ifndef REALIZZAZIONI_UTIL_BIN_TREE_H
#define REALIZZAZIONI_UTIL_BIN_TREE_H

#include "alberoBinario_pt.h"

class util_bin_tree {
public:

    int d3(alberoBinario_pt<int> &T, int k);
    //restituisce il numero di nodi il cui valore è pari
    int lp(alberoBinario_pt<int> &T);
    //numero di foglie il cui padre è multiplo di 5
    int l2p(alberoBinario_pt<int> &T);
    //numero foglie con valore pari
    int even_leafs(alberoBinario_pt<int> &T);
    //Modifca albero secondo il criterio
    void multipli(alberoBinario_pt<int> &T);
    //Numero foglie il cui genitore è pari
    int leafs_with_even_parent(alberoBinario_pt<int> &T);
    // Numero nodi al livello K con valore dispari
    int odd(alberoBinario_pt<int> &T, int k);
    //A ogni foglia aggiunge un figlio (sinistro in questo caso) il cui valore è la somma dei nodi presenti nel cammino che partono dalla radice e arrivano a quella foglia
    void aggiungiSommaFoglia(alberoBinario_pt<int> &T);
private:
    void d3(alberoBinario_pt<int> &T, alberoBinario_pt<int>::nodo n, int k, int liv, int &counter);
    void lp(alberoBinario_pt<int> &T, alberoBinario_pt<int>::nodo n, int &counter);
    void even_leafs(alberoBinario_pt<int> &T, alberoBinario_pt<int>::nodo n, int &counter);
    void l2p(alberoBinario_pt<int> &T, alberoBinario_pt<int>::nodo n, bool isMultiplo, int &counter);
    void leafs_with_even_parent(alberoBinario_pt<int> &T, alberoBinario_pt<int>::nodo n, bool isPari, int &counter);
    void modifica(alberoBinario_pt<int> &T, alberoBinario_pt<int>::nodo n);
    void odd(alberoBinario_pt<int> &T, alberoBinario_pt<int>::nodo n, int k, int liv, int &counter);
    void aggiungiSommaFoglia(alberoBinario_pt<int> &T, alberoBinario_pt<int>::nodo n);
};

//Funzione che ad ogni foglia aggiunge un figlio (sinistro in questo caso) il cui valore è la somma dei nodi presenti nel cammino che partono dalla radice e arrivano a quella foglia
void util_bin_tree::aggiungiSommaFoglia(alberoBinario_pt<int> &T) {
    if (!T.alberoBinVuoto()) {
        aggiungiSommaFoglia(T, T.radice());
    }
}

//Funzione di modifica dell'albero
void util_bin_tree::aggiungiSommaFoglia(alberoBinario_pt<int> &T, alberoBinario_pt<int>::nodo n) {
    //il nodo non è foglia, dunque richuamo la funzione sui figli destro e sinistro (se esistono)
    if (!T.sinistroVuoto(n) && !T.destroVuoto(n)) {
        if (!T.sinistroVuoto(n)) aggiungiSommaFoglia(T, T.figlioSinistro(n));
        if (!T.destroVuoto(n)) aggiungiSommaFoglia(T, T.figlioDestro(n));
    } else {
        //il nodo è foglia, quindi salvo il valore di n in una variabile di somma
        int somma = T.leggiNodo(n);
        alberoBinario_pt<int>::nodo padre = T.genitore(n);
        //RISALGO FINO ALLA RADICE e aggungo i valori dei nodi alla somma
        while (padre != T.radice()) {
            somma += T.leggiNodo(padre);
            padre = T.genitore(padre);
        }
        //aggiungo il valore della radice alla somma
        somma += T.leggiNodo(padre);
        //Inserisco il figlio sinistro
        T.inserisciSinistro(n, somma);
    }
}


//La funzione restituisce il numero di nodi al livello k il cui valore è divisibile per 3
int util_bin_tree::d3(alberoBinario_pt<int> &T, int k) {
    int counter = 0;
    if (!T.alberoBinVuoto()) {
        d3(T, T.radice(), k, 0, counter);
    }
    return counter;
}
//La funzione conta il numero di nodi al livello k il cui valore è divisibile per 3
void util_bin_tree::d3(alberoBinario_pt<int> &T, alberoBinario_pt<int>::nodo n, int k, int liv, int &counter) {
    if (liv == k && ((T.leggiNodo(n) % 3) == 0)) counter++;
    if (!T.sinistroVuoto(n) && k < liv) d3(T, T.figlioSinistro(n), k, liv++, counter);
    if (!T.destroVuoto(n) && k < liv) d3(T, T.figlioDestro(n), k, liv++, counter);
}


//La funzione restituisce il numero di nodi al livello k il cui valore è dispari
int util_bin_tree::odd(alberoBinario_pt<int> &T, int k) {
    int counter = 0;
    if (!T.alberoBinVuoto()) {
        odd(T, T.radice(), k, 0, counter);
    }
    return counter;
}

//La funzione conta il numero di nodi al livello k il cui valore è dispari
void util_bin_tree::odd(alberoBinario_pt<int> &T, nodoT<int> *n, int k, int liv, int &counter) {
    if (liv == k && ((T.leggiNodo(n) % 2) == 1)) counter++;
    if (!T.sinistroVuoto(n) && k < liv) d3(T, T.figlioSinistro(n), k, liv++, counter);
    if (!T.destroVuoto(n) && k < liv) d3(T, T.figlioDestro(n), k, liv++, counter);
}

//La funzione restituisce il numero di foglie il cui valori è pari
int util_bin_tree::even_leafs(alberoBinario_pt<int> &T) {
    int counter = 0;
    if (!T.alberoBinVuoto()) {
        even_leafs(T, T.radice(), counter);
    }
    return counter;
}

//La funzione conta il numero di foglie il cui valore è pari
void util_bin_tree::even_leafs(alberoBinario_pt<int> &T, nodoT<int> *n, int &counter) {
    if ((T.leggiNodo(n) % 2) == 0 && T.sinistroVuoto(n) && T.destroVuoto(n)) counter++;
    if (!T.sinistroVuoto(n)) even_leafs(T, T.figlioSinistro(n), counter);
    if (!T.destroVuoto(n)) even_leafs(T, T.figlioDestro(n), counter);
}



//La funzione restituisce il numero di foglie il cui padre ha un valore multiplo di 5
int util_bin_tree::l2p(alberoBinario_pt<int> &T) {
    int counter = 0;
    if (!T.alberoBinVuoto()) {
        bool isMultiplo = ((T.leggiNodo(T.radice()) % 5) == 0);
        if (!T.sinistroVuoto(T.radice())) l2p(T, T.figlioSinistro(T.radice()), isMultiplo, counter);
        if (!T.destroVuoto(T.radice())) l2p(T, T.figlioDestro(T.radice()), isMultiplo, counter);
    }
    return counter;
}

//La funzione conta il numero di foglie il cui padre ha un valore multiplo di 5
void util_bin_tree::l2p(alberoBinario_pt<int> &T, nodoT<int> *n, bool isMultiplo, int &counter) {
    if (isMultiplo && T.sinistroVuoto(n) && T.destroVuoto(n)) counter++;
    isMultiplo = (((T.leggiNodo(n)) % 5) == 0);
    if (!T.sinistroVuoto(n)) l2p(T, T.figlioSinistro(n), isMultiplo, counter);
    if (!T.destroVuoto(n)) l2p(T, T.figlioDestro(n), isMultiplo, counter);

}

//la funzione restituisce il numero di foglie il cui padre è un numero pari
int util_bin_tree::leafs_with_even_parent(alberoBinario_pt<int> &T) {
    int counter = 0;
    if (!T.alberoBinVuoto()) {
        bool isPari = ((T.leggiNodo(T.radice()) % 2) == 0);
        if (!T.sinistroVuoto(T.radice())) leafs_with_even_parent(T, T.figlioSinistro(T.radice()), isPari, counter);
        if (!T.destroVuoto(T.radice())) leafs_with_even_parent(T, T.figlioDestro(T.radice()), isPari, counter);
    }
    return counter;
}

//La funzione conta il numero di foglie il cui padre ha un valore pari di 5
void util_bin_tree::leafs_with_even_parent(alberoBinario_pt<int> &T, nodoT<int> *n, bool isPari, int &counter) {
    if (isPari && T.sinistroVuoto(n) && T.destroVuoto(n)) counter++;
    isPari = (((T.leggiNodo(n)) % 2) == 0);
    if (!T.sinistroVuoto(n)) l2p(T, T.figlioSinistro(n), isPari, counter);
    if (!T.destroVuoto(n)) l2p(T, T.figlioDestro(n), isPari, counter);
}

//La funzione restituisce il numero di nodi il cui valore è pari
int util_bin_tree::lp(alberoBinario_pt<int> &T) {
    int counter = 0;
    if (!T.alberoBinVuoto()) {
        lp(T, T.radice(), counter);
    }
    return counter;
}

//La funzione conta il numero di nodi con valore pari
void util_bin_tree::lp(alberoBinario_pt<int> &T, nodoT<int> *n, int &counter) {
    if ((T.leggiNodo(n) % 2) == 0) counter++;
    if (!T.sinistroVuoto(n)) lp(T, T.figlioSinistro(n), counter);
    if (!T.destroVuoto(n)) lp(T, T.figlioDestro(n), counter);
}

//La funzione modifica il contenuto dell'albero, facendo in modo che ogni nodo memorizzi il numero di nodi pari presenti nel suo sottoalbero
void util_bin_tree::multipli(alberoBinario_pt<int> &T) {
    if (!T.alberoBinVuoto()) {
        modifica(T, T.radice());
    }
}

//Funzione di modifica
void util_bin_tree::modifica(alberoBinario_pt<int> &T, nodoT<int> *n) {
    if (T.sinistroVuoto(n) && T.destroVuoto(n)) {
        if ((T.leggiNodo(n)%2)==0) T.scriviNodo(n,1);
        else T.scriviNodo(n,0);
        return;
    } else {
        int counter = 0;
        lp(T, n, counter);
        //Scrivo nel nodo il numero di nodi del suo sottoalbero con valore pari
        T.scriviNodo(n, counter);
        //richiamo la funzione sui figli destro e sinistro (se esistono)
        if (!T.sinistroVuoto(n)) modifica(T, T.figlioSinistro(n));
        if (!T.destroVuoto(n)) modifica(T, T.figlioDestro(n));
    }
}
#endif //REALIZZAZIONI_UTIL_BIN_TREE_H
