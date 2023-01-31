#ifndef REALIZZAZIONI_BST_H
#define REALIZZAZIONI_BST_H

#include "alberoBinario_pt.h"
#include <iostream>
#include <stdexcept>

using namespace std;

class BST {
public:
    bool is_bst();

    void insert(int);

    int min();

    void print();

    //costruttore
    BST(alberoBinario_pt<int> &BT) {
        T = BT;
    };


private:
    alberoBinario_pt<int> T;

    bool search(int);

    bool ricerca(int, alberoBinario_pt<int>::nodo);

    void stampa(alberoBinario_pt<int>::nodo);

    void verifica_bst(alberoBinario_pt<int>::nodo, bool &);

    int min(alberoBinario_pt<int>::nodo n);

    int conta(int k);

    void conta(int k, alberoBinario_pt<int>::nodo n, int &counter);

    bool checkSinistro(int k, alberoBinario_pt<int>::nodo n);

    bool checkDestro(int k, alberoBinario_pt<int>::nodo n);

};


//Funzione che restituisce true se l'albero è un BST, false altrimenti
bool BST::is_bst() {
    if (!T.alberoBinVuoto()) {
        bool isBst = true;
        verifica_bst(T.radice(), isBst);
        return isBst;
    }
    return true;
}

//Funzione che verifica se un albero è un BST
void BST::verifica_bst(alberoBinario_pt<int>::nodo n, bool &isBst) {
    if (isBst) {
        //Verifico se ho piu copie dello stesso nodo
        if (this->conta(T.leggiNodo(n)) > 1) isBst = false;
        //Verifico che tutti i nodi nel sottoalbero sinistro (se esiste) siano piu piccoli di n
        if (isBst)
            if (!T.sinistroVuoto(n)) {
                if (T.leggiNodo(T.figlioSinistro(n)) > T.leggiNodo(n)) isBst = false;
                if (!checkSinistro(T.leggiNodo(n), T.figlioSinistro(n))) isBst = false;
            }
        //Verifico che tutti i nodi nel sottoalbero destro (se esiste) siano piu piccoli di n
        if (isBst)
            if (!T.destroVuoto(n))
            {
                if (T.leggiNodo(T.figlioDestro(n))<T.leggiNodo(n)) isBst=false;
                if (!checkDestro(T.leggiNodo(n), T.figlioDestro(n))) isBst = false;
            }
        //Se l'albero risulta ancora essere un BST, procedoto con la visita
        if (isBst) {
            if (!T.sinistroVuoto(n)) verifica_bst(T.figlioSinistro(n), isBst);
            if (!T.destroVuoto(n)) verifica_bst(T.figlioDestro(n), isBst);
        }
    }
}

//verifico che tutti i valori siano minori di k
bool BST::checkSinistro(int k, alberoBinario_pt<int>::nodo n) {
    //se il figlio sinistro esiste ne controllo il valore
    if (!T.sinistroVuoto(n)) {
        //se maggiore di k restituisco false, altrimenti procedo con la visita
        if (T.leggiNodo(T.figlioSinistro(n)) > k) return false;
        else checkSinistro(k, T.figlioSinistro(n));
    }
    //se il figlio destro esiste ne controllo il valore
    if (!T.destroVuoto(n)) {
        //se maggiore di k restituisco false, altrimenti procedo con la visita
        if (T.leggiNodo(T.figlioDestro(n)) > k) return false;
        else checkSinistro(k, T.figlioDestro(n));
    }
    return true;
}

//verifico che tutti i valori siano maggiore di k
bool BST::checkDestro(int k, alberoBinario_pt<int>::nodo n) {
    //se il figlio sinistro esiste ne controllo il valore
    if (!T.sinistroVuoto(n)) {
        //se minore di k restituisco false, altrimenti procedo con la visita
        if (T.leggiNodo(T.figlioSinistro(n)) < k) return false;
        else checkDestro(k, T.figlioSinistro(n));
    }
    //se il figlio destro esiste ne controllo il valore
    if (!T.destroVuoto(n)) {
        //se minore di k restituisco false, altrimenti procedo con la visita
        if (T.leggiNodo(T.figlioDestro(n)) < k) return false;
        else checkDestro(k, T.figlioDestro(n));
    }
    return true;
}

//la funzione verifica quante copie di k esistono nell'albero
int BST::conta(int k) {
    //se l'albero è vuoto ho 0 copie di k
    if (T.alberoBinVuoto()) return 0;
    else {
        int counter = 0;
        conta(k, T.radice(), counter);
        return counter;
    }
}

//conto le copie di k mentre visito l'albero
void BST::conta(int k, alberoBinario_pt<int>::nodo n, int &counter) {
    if (T.leggiNodo(n) == k) counter++;
    if (!T.sinistroVuoto(n)) conta(k, T.figlioSinistro(n), counter);
    if (!T.destroVuoto(n)) conta(k, T.figlioDestro(n), counter);
}


//Funzione che restituisce il valore minimo di un bst (foglia piu a sinistra)
int BST::min() {
    if (is_bst()) {

        if (!T.alberoBinVuoto()) {
            return min(T.radice());
        } else throw out_of_range("Albero vuoto, minimo non esistente");
    } else throw out_of_range("L'albero non e' BST dunque non posso restituire il valore minimo");
}

//Funzione che restituisce il valore massimo di un BST che ha come radice il nodo n. Il valore minimo è la foglia piu a sinistra dell'albero
int BST::min(alberoBinario_pt<int>::nodo n) {
    if (T.sinistroVuoto(n)) return T.leggiNodo(n);
    else return min(T.figlioSinistro(n));
}

//La funzione ritorna TRUE se il nodo identificato dalla chiave K esiste, false ALTRIMENTI
bool BST::search(int k) {
    bool esiste = false;
    if (!T.alberoBinVuoto()) {
        esiste = ricerca(k, T.radice());
    }
    return esiste;
}

//Funzione di ricerca di un nodo
bool BST::ricerca(int k, alberoBinario_pt<int>::nodo n) {
    //se ho trovato il nodo restituisco true
    if (T.leggiNodo(n) == k) return true;
    //se la chiave che sto cercando ha un valore minore della chiave del nodo attuale AND il nodo attuale ha un figlio sinistro richiamo la funzione di ricerca sul figlio sinistro
    if (k < T.leggiNodo(n) && !T.sinistroVuoto(n)) return ricerca(k, T.figlioSinistro(n));
    //se la chiave che sto cercando ha un valore maggiore della chiave del nodo attuale AND il nodo attuale ha un figlio destro richiamo la funzione di ricerca sul figlio destro
    if (k > T.leggiNodo(n) && !T.destroVuoto(n)) return ricerca(k, T.figlioDestro(n));
    //se non ho trovato la chiave restituisco FALSE
    return false;

}

//Inserimento in un BST, rispettando le proprietà
void BST::insert(int k) {
    if (is_bst()) {
        //la chiave non deve esiste all'interno del BST
        if (!search(k)) {
            if (T.alberoBinVuoto()) {
                //CASO SEMPLICE: ALBERO VUOTO -> INSERISCO L'ELEMENTO COME RADICE
                T.inserisciRadice(k);
            } else {
                alberoBinario_pt<int>::nodo n = T.radice();
                bool continua = true;
                //VADO ALLA RICERCA DELLA POSIZIONE IN CUI INSERIRE LA CHIAVE K, tenendo conto delle proprietà di un BST
                while (continua) {
                    if (k < T.leggiNodo(n) && !T.sinistroVuoto(n)) n = T.figlioSinistro(n);
                    else if (k > T.leggiNodo(n) && !T.destroVuoto(n)) n = T.figlioDestro(n);
                    else continua = false;
                }
                //INSERISCO il valore nella posizione correta
                if (k < T.leggiNodo(n)) {
                    T.inserisciSinistro(n, k);
                } else {
                    T.inserisciDestro(n, k);
                }
            }
        }
    } else throw out_of_range("L'albero non e' BST dunque non posso inserire un valore");
}


//Stampa di un BST
void BST::print() {
    cout << "[ ";
    if (!T.alberoBinVuoto()) {
        stampa(T.radice());
    }
    cout << "]" << endl;
}

//Visita simmetrica
void BST::stampa(alberoBinario_pt<int>::nodo n) {
    if (!T.sinistroVuoto(n)) stampa(T.figlioSinistro(n));
    cout << T.leggiNodo(n) << " ";
    if (!T.destroVuoto(n)) stampa(T.figlioDestro(n));
}


#endif //REALIZZAZIONI_BST_H
