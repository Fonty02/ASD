
#ifndef REALIZZAZIONI_MINMAXARRAY_H
#define REALIZZAZIONI_MINMAXARRAY_H
#include <algorithm>
using namespace std;
typedef struct
{
    int max;
    int min;
} maxmin;


maxmin massimominimo(int v[], int n, int i, int f)
{
    maxmin m;
    if (n==1) {
        m.max = v[i];
        m.min = v[i];
        return m;
    }
    if (n==2)
    {
        m.max=max(v[i],v[f]);
        m.min=min(v[i],v[f]);
        return m;
    }
    maxmin destra;
    maxmin sinistra;
    sinistra=massimominimo(v,n/2,i,i+n/2-1);
    destra= massimominimo(v,n-n/2,i+n/2,f);
    m.min=min(destra.min,sinistra.min);
    m.max=max(destra.max,sinistra.max);
    return m;

}
#endif //REALIZZAZIONI_MINMAXARRAY_H



