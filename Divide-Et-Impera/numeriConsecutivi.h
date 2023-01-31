#ifndef REALIZZAZIONI_NUMERICONSECUTIVI_H
#define REALIZZAZIONI_NUMERICONSECUTIVI_H
using namespace std;
int conta_coppie(int V[], int n, int i, int f)
{
    if (i==f)
    {
        return 0;
    }
    if (f-i==1)
        if (V[i]==V[f]-1)
            return 1;
    int medio=i+n/2;
    int contaSinistra = conta_coppie(V, n / 2, i, medio);
    int contaDestra = conta_coppie(V, n - n / 2, medio + 1, f);
    int c = 0;
    if (V[medio] == V[medio +1] -1)
    {
        c = 1;
    }
    return contaDestra + contaSinistra + c;
}

int davide(int V[], int inizio, int fine)
{
    if (fine - inizio == 0)
    {
        return 0;
    }
    if (fine - inizio == 1)
    {
        return V[inizio + 1] == V[inizio] + 1;
    }
    int centro = inizio + (fine - inizio) / 2;
    int sinistra = davide(V, inizio, centro);
    int destra = davide(V, centro, fine);
    int contatore = 0;
    if (V[centro - 1] == V[centro] + 1)
    {
        contatore = 1;
    }
    return sinistra + destra + contatore;
}

/* Data una sequenza di n numeri interi (x1, . . . , xn) diciamo che (xi
, xi+1) `e una coppia di numeri
consecutivi se xi+1 = xi + 1. Ad esempio nella sequenza (12, 13, 24, 25, 26, 35, 67) ci sono 3 coppie
di numeri consecutivi: (12, 13), (24, 25) e (25, 26). Scrivere in pseudocodice un algoritmo che utilizzi
la tecnica divide-et-impera e che calcoli quante coppie di numeri consecutivi sono contenute in una
sequenza di n numeri interi (x1, . . . , xn) ricevuta in input. */

#endif // REALIZZAZIONI_NUMERICONSECUTIVI_H
