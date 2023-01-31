#include "AlberoPt.h"
#ifndef REALIZZAZIONI_CONTAPARIVISITASIMMETRICA_H
#define REALIZZAZIONI_CONTAPARIVISITASIMMETRICA_H
class contaVisita
{
public:
    int conta(alberoPt<int>& T);
private:
    void conta(alberoPt<int>&T,alberoPt<int>::nodo ,int&);
};


//La funzione restituisce il numero di nodi in cui il padre è un numero intero pari
int contaVisita::conta(alberoPt<int> &T) {
    int counter=0;
    if (!T.alberoVuoto())
    {
        conta(T,T.radice(),counter);
    }
    return counter;
}


//Viene effettuata una visita simmetrica per i=1 dell'albero n-ario visitando prima il primo figlio e poi, nell'ordine, tutti i fratelli successivi.
void contaVisita::conta(alberoPt<int> &T,alberoPt<int>::nodo n, int & counter) {
    alberoPt<int>::nodo c;
    //SE IL NODO E' PARI INCREMENTO IL COUNTER
    if (n!=T.radice())
    {
        if ((T.leggiNodo(T.padre(n))%2)==0) counter++;
    }
    if (!T.foglia(n)) {
        c = T.primoFiglio(n);
        while (!T.ultimoFratello(c))
        {
            conta(T,c,counter);
            c=T.fratelloSuccessivo(c);
        }
       conta(T,c,counter);
    }
}


#endif //REALIZZAZIONI_CONTAPARIVISITASIMMETRICA_H
