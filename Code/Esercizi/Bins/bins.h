#ifndef REALIZZAZIONI_BINS_H
#define REALIZZAZIONI_BINS_H
#include "codav.h"
#include <iostream>
class bins
{
public:
    void insert(int k);
    void deleteFromList (int c);
    double mean(int c);
    int freq(int c);
private:
    codav<int> bin[3];
};

void bins::insert(int k) {
        if (k>=1 && k<=3) bin[0].incoda(k);
        if (k>=4 && k<=6) bin[1].incoda(k);
        if (k>=7 && k<=9) bin[2].incoda(k);
}

void bins::deleteFromList(int c) {
    if (c>=0 && c<=2)
        bin[c].fuoriCoda();
}

int bins::freq(int c) {
    if (c>=0 && c<=2)
        return bin[c].lunghezza();
    else return 0;
}


double bins::mean(int c) {
    double media=0;
    if (c>=0 && c<=2) {
        int num = bin[c].lunghezza();
        if (num > 0) {
            int somma = 0;
            //CREO UN VETTORE DOVE SALVO GLI ELEMENTI IN MODO DA RIPRISTINARE IN SEGUITO LA CODA
            int v[num];
            int i = 0;
            while (!bin[c].codaVuota()) {
                somma += bin[c].leggiCoda();
                v[i] = bin[c].leggiCoda();
                bin[c].fuoriCoda();
                i++;
            }
            media = (double) somma / num;
            for (int i=0;i<num;i++)
            {
                bin[c].incoda(v[i]);
            }
        }
    }
    return media;
}

#endif //REALIZZAZIONI_BINS_H
