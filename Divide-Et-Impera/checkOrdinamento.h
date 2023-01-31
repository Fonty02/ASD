//
// Created by fonta on 04/01/2023.
//

#ifndef REALIZZAZIONI_CHECKORDINAMENTO_H
#define REALIZZAZIONI_CHECKORDINAMENTO_H
bool checkOrdinato(int v[], int n, int inizio, int fine)
{
    if (n<=2)
    {
        return v[inizio]<=v[inizio+1];
    }
    bool ordinato=true;
    ordinato= checkOrdinato(v,n/2,inizio,inizio+n/2-1);
    if (ordinato)
    {
        ordinato= checkOrdinato(v,n-n/2,inizio+n/2,fine);
    }
    if (ordinato)
    {
        ordinato=(v[inizio+(n/2)-1]<=v[inizio+n/2]+1);
    }
    return ordinato;
}
#endif //REALIZZAZIONI_CHECKORDINAMENTO_H
