#ifndef REALIZZAZIONI_DUPLICATI_H
#define REALIZZAZIONI_DUPLICATI_H
#include <iostream>
bool duplicati(int v[], int n, int inizio, int fine)
{
    if (n<=2)
        return v[inizio]==v[inizio+1];
    else {
        int mid=n/2-1;
        return (duplicati(v, n/2,inizio, mid) || duplicati(v,n-n/2,mid+1, fine)) ;
    }
    }
#endif //REALIZZAZIONI_DUPLICATI_H
