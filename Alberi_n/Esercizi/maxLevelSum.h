#ifndef REALIZZAZIONI_MAXLEVELSUM_H
#define REALIZZAZIONI_MAXLEVELSUM_H
#include "AlberoPt.h"
class maxLevelSum
{
public:
    int max_level(alberoPt<int>& T);
private:
    void sommaLivello(alberoPt<int>& T, alberoPt<int>::nodo n, int liv, int *v);
};
int maxLevelSum::max_level(alberoPt<int> &T) {
    if (T.alberoVuoto()) return -1;
    else
    {
        int v[T.profonditaAlbero()];
        //INIZIALIZZO L'ARRAY
        for (int i=0;i<T.profonditaAlbero();i++)
        {
            v[i]=0;
        }
        sommaLivello(T,T.radice(),0,v);
        int i=1;
        int max=v[0];
        int liv_max=0;
        while (i<T.profonditaAlbero())
        {
            if (v[i]>max)
            {
                max=v[i];
                liv_max=i;
            }
            i++;
        }
        return liv_max;
    }
}


/*
 * FUNZIONE che memorizza in un vettore le somme dei nodi in ogni livello
 */
void maxLevelSum::sommaLivello(alberoPt<int>& T, alberoPt<int>::nodo n, int liv, int *v) {
     v[liv]+= T.leggiNodo(n);
    //richiamo la funzione di somma sul fratello (stesso livello)
    if (!T.ultimoFratello(n)) sommaLivello(T,T.fratelloSuccessivo(n),liv,v);
    //richiamo la funzione di somma sul primoFiglio (il livello aumenta di 1)
    if (!T.foglia(n)) sommaLivello(T,T.primoFiglio(n),liv+1,v);
}

#endif //REALIZZAZIONI_MAXLEVELSUM_H