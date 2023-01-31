
#include "grafoMatrice.h"
#ifndef REALIZZAZIONI_GRAPH_PATH_H
#define REALIZZAZIONI_GRAPH_PATH_H

typedef struct {
    nodoG nodo;
    bool visitato;
} nodo_visita;


class graph_path
{
public:
    /*
     * Dato l'intero sum e due nodi a e b, determina se esiste un cammino semplice
     * ovvero senza nodi ripetuti tra a e b con le seguenti proprietà:
     * 1) Parte da A e termina su B
     * 2) La somma delle etichette sui nodi nella sequenza è minore di SUM
     */
    bool sumPath(grafoMat<int,int>& g, int sum, typename grafoMat<int,int>::nodo a,typename grafoMat<int,int>::nodo b);

private:
    void bfsModificata(grafoMat<int,int>& g, int sum, typename grafoMat<int,int>::nodo a,typename grafoMat<int,int>::nodo b, bool& esiste);
    int returnPosizione(typename grafoMat<int,int>::nodo a, nodo_visita vet[]);
};


bool graph_path::sumPath(grafoMat<int, int> &g, int sum, typename grafoMat<int, int>::nodo a,typename grafoMat<int, int>::nodo b) {
    if (g.vuoto())
    {
        return false;
    }
    else
    {
        bool esiste=false;
        bfsModificata(g,sum,a,b,esiste);
        return esiste;
    }
}


void graph_path::bfsModificata(grafoMat<int, int> &g, int sum, typename grafoMat<int, int>::nodo a,typename grafoMat<int, int>::nodo b, bool &esiste) {
   //operazioni preliminari
    nodo_visita n;
    nodoG v;
   List_vector<nodoG> lista_nodi=g.list_nodi();
   List_vector<nodoG> lista_adiacenti;
   nodo_visita visitati[g.numNodi()];
   List_vector<nodoG>::posizione p=lista_nodi.primoLista();
   int somma=0;
   int i=0;
   while (i<g.numNodi())
   {

       n.nodo=lista_nodi.leggiLista(p);
       n.visitato=false;
       visitati[i]=n;
       p=lista_nodi.succLista(p);
       i++;
   }
   //VISITA
    codav<nodoG> q;
    q.incoda(a);
    nodoG currentNode;
    while (!q.codaVuota() && !esiste && somma<sum)
    {
        currentNode=q.leggiCoda();
        somma+=g.leggiEtichetta(currentNode);
        q.fuoriCoda();
        visitati[returnPosizione(currentNode,visitati)].visitato=1;
        lista_adiacenti=g.adiacenti(currentNode);
        p=lista_adiacenti.primoLista();
        while (!lista_adiacenti.fineLista(p) && !esiste && somma<sum) {

            v = lista_adiacenti.leggiLista(p);
            if (v == b) {
                somma+=g.leggiEtichetta(v);
                esiste = true;
            } else {
                if (visitati[returnPosizione(v, visitati)].visitato == 0 && !q.esiste(v)) {
                    q.incoda(v);
                }
                p = lista_adiacenti.succLista(p);
            }
        }
    }
    if (somma>=sum)
        esiste=false;

}

int graph_path::returnPosizione(typename grafoMat<int, int>::nodo a, nodo_visita vet[]) {
    bool trovato=false;
    int i=0;
    while (!trovato)
    {
        nodo_visita n=vet[i];
        if (a==n.nodo)
        {
            trovato=true;
        }
        else i++;
    }
    return i;
}
#endif //REALIZZAZIONI_GRAPH_PATH_H
