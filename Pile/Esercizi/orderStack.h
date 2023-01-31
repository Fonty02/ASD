#ifndef REALIZZAZIONI_ORDERSTACK_H
#define REALIZZAZIONI_ORDERSTACK_H
#include "pilav.h"
#include "Ordered_list.h"
using namespace std;
class orderStack
{
public:
    //dato lo stack p restituisce un altro stack che contiene gli elementi di p ordinati dal top al bottom
    pilav<int>& sortStack(pilav<int>& p);
};


pilav<int> &orderStack::sortStack(pilav<int> &p) {
    Ordered_list<int> l;
    while (!p.pilaVuota())
    {
        l.insList(p.leggiPila());
        p.fuoriPila();
    }
    Ordered_list<int>::posizione  pos=l.ultimoLista();
    while (pos!=l.primoLista())
    {
        p.insPila(l.leggiLista(pos));
        pos=l.precLista(pos);
    }
    p.insPila(l.leggiLista(pos));
    return p;
}
#endif //REALIZZAZIONI_ORDERSTACK_H
