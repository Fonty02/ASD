#ifndef REALIZZAZIONI_HISTO_H
#define REALIZZAZIONI_HISTO_H

#include <iostream>
#include <string>
#include "hashtableAperto.h"

#define DEFAULTSIZE 10

using namespace std;

class histo {
public:
    histo();
    void add(int v);
    void remove(int v);
    int mode();
    double mean();
    void print();
    friend ostream &operator<<(ostream &os, const histo &h);
private:
    open_hash_table<int, int> hist;
};
histo::histo() : hist(DEFAULTSIZE) {}
void histo::add(int v) {
    if (!hist.ricerca(v)) {
        mypair<int, int> coppia(v, 1);
        hist.inserisci(coppia);
    } else {
        hist.modifica(v, hist.recupera(v), hist.recupera(v) + 1);
    }
}

void histo::remove(int v) {
    if (hist.ricerca(v)) {
        if (hist.recupera(v) >= 2) {
            hist.modifica(v, hist.recupera(v), hist.recupera(v) - 1);
        } else {
            hist.cancella(v);
        }
    }
}

int histo::mode() {
    int max = 0;
    int bestkey;
    List_vector<int> keys = hist.keys();
    List_vector<int>::posizione p = keys.primoLista();
    while (!keys.fineLista(p)) {
        int key = keys.leggiLista(p);
        if (hist.recupera(key) > max) {
            max = hist.recupera(key);
            bestkey = key;
        }
        p = keys.succLista(p);
    }
    return bestkey;
}

double histo::mean() {
    List_vector<int> keys = hist.keys();
    List_vector<int>::posizione p = keys.primoLista();
    double result = 0;
    while (!keys.fineLista(p)) {
        result += keys.leggiLista(p);
        p = keys.succLista(p);
    }
    return (double) result / keys.lunghezza();
}

void histo::print() {
    List_vector<int> keys = hist.keys();
    List_vector<int>::posizione p = keys.primoLista();
    while (!keys.fineLista(p)) {
        int key = keys.leggiLista(p);
        if (key) {
            cout << key << " ";
        }
        string value(hist.recupera(key), '*');
        cout << value << endl;
        p = keys.succLista(p);
    }
}

#endif //REALIZZAZIONI_HISTO_H
