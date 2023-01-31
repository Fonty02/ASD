//
// Created by fonta on 04/01/2023.
//

#ifndef REALIZZAZIONI_INDICEELEMENTO_H
#define REALIZZAZIONI_INDICEELEMENTO_H
#include <iostream>
bool indiceElemento(int v[],int n,int inizio,int fine)
{
    if (n==1)
    {
        return v[inizio]==inizio;
    }
    if (n==2)
    {
        return (v[inizio]==inizio || v[fine]==fine);
    }
    //controllo se esiste nella metà di sinistra
    bool esiste= indiceElemento(v,n/2,inizio,inizio+n/2-1);
    //controllo nelle metà di destra se non l ho gia trovato se non esiste
    if (!esiste)
    {
        esiste= indiceElemento(v,n-n/2,inizio+n/2,fine);
    }
    return esiste;

}
#endif //REALIZZAZIONI_INDICEELEMENTO_H
