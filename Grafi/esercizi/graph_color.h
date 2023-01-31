
#ifndef REALIZZAZIONI_GRAPH_COLOR_H
#define REALIZZAZIONI_GRAPH_COLOR_H
#include "grafoMatrice.h"
#include <string>
using namespace std;
typedef struct {
    nodoG nodo;
    bool visitato;
} nodo_visita;


class graph_color
{
public:
    //RESTITUISCE TRUE SE ESISTE UN PATH CHE COLLEGA n1 a n2 e tutti i nodi sono dello stesso colore, false altrimenti
    bool sameColorPath(grafoMat<string,int>&g, typename grafoMat<string,int>::nodo n1, typename grafoMat<string,int>::nodo n2);
    //restituisce true se esiste un path che collega n1 a n2 ed ogni nodo del path ha colore diverso dal precedente, folse altrimenti
    bool uniformColorPath(grafoMat<string,int>&g, typename grafoMat<string,int>::nodo n1, typename grafoMat<string,int>::nodo n2);

private:
    // FUNZIONI DI VISITA MODIFICATE  NON ACCESSIBILE ALL'UTENTE
    bool visitaSameColor(grafoMat<string,int>&g, typename grafoMat<string,int>::nodo n1, typename grafoMat<string,int>::nodo n2);
    bool visitaUniformColor(grafoMat<string,int>&g, typename grafoMat<string,int>::nodo n1, typename grafoMat<string,int>::nodo n2);
    //FUNZIONE DI SERVIZIO
    int returnPosizione(typename grafoMat<int,int>::nodo a, nodo_visita vet[]);

};

int graph_color::returnPosizione(typename grafoMat<int, int>::nodo a, nodo_visita vet[]) {
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

bool graph_color::sameColorPath(grafoMat<std::string, int> &g, typename grafoMat<string, int>::nodo n1, typename grafoMat<string, int>::nodo n2) {
    if (g.vuoto())
        return false;
    else
    {
        bool esiste=visitaSameColor(g,n1,n2);
        return esiste;
    }
}

bool graph_color::visitaSameColor(grafoMat<std::string, int> &g, typename grafoMat<string, int>::nodo n1,typename grafoMat<string, int>::nodo n2) {
    //OPERAZIONI PRELIMINARI ALLA VISITA
    nodo_visita n;
    nodoG v;
    List_vector<nodoG> lista_nodi=g.list_nodi();
    List_vector<nodoG> lista_adiacenti;
    nodo_visita visitati[g.numNodi()];
    List_vector<nodoG>::posizione p=lista_nodi.primoLista();
    int counter=0;
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
    q.incoda(n1);
    nodoG currentNode;
    while (!q.codaVuota())
    {
        currentNode=q.leggiCoda();
        if (currentNode==n2)
        {
            return true;
        }
        q.fuoriCoda();
        visitati[returnPosizione(currentNode,visitati)].visitato=true;
        lista_adiacenti=g.adiacenti(currentNode);
        p=lista_adiacenti.primoLista();
        while (!lista_adiacenti.fineLista(p))
        {
            v=lista_adiacenti.leggiLista(p);
            if (g.leggiEtichetta(n1)==g.leggiEtichetta(v) && !visitati[returnPosizione(v,visitati)].visitato) {
                if (!visitati[returnPosizione(v, visitati)].visitato && !q.esiste(v)) {
                    q.incoda(v);
                }
            }
            p=lista_adiacenti.succLista(p);
        }
    }
    return false;
}


bool graph_color::uniformColorPath(grafoMat<std::string, int> &g, typename grafoMat<string, int>::nodo n1,typename grafoMat<string, int>::nodo n2) {
    if (g.vuoto())
        return false;
    else
    {
        bool esiste=visitaUniformColor(g,n1,n2);
        return esiste;
    }
}

bool graph_color::visitaUniformColor(grafoMat<std::string, int> &g, typename grafoMat<string, int>::nodo n1,typename grafoMat<string, int>::nodo n2) {
    //OPERAZIONI PRELIMINARI ALLA VISITA
    nodo_visita n;
    nodoG v;
    List_vector<nodoG> lista_nodi=g.list_nodi();
    List_vector<nodoG> lista_adiacenti;
    nodo_visita visitati[g.numNodi()];
    List_vector<nodoG>::posizione p=lista_nodi.primoLista();
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
    q.incoda(n1);
    nodoG currentNode;
    while (!q.codaVuota())
    {
        currentNode=q.leggiCoda();
        q.fuoriCoda();
        if (currentNode==n2)
        {
            return true;
        }
        visitati[returnPosizione(currentNode,visitati)].visitato=true;
        lista_adiacenti=g.adiacenti(currentNode);
        p=lista_adiacenti.primoLista();
        while (!lista_adiacenti.fineLista(p))
        {
            v=lista_adiacenti.leggiLista(p);
            if (g.leggiEtichetta(currentNode)!=g.leggiEtichetta(v) && !visitati[returnPosizione(v,visitati)].visitato && !q.esiste(v)) {
                    q.incoda(v);
            }
            p=lista_adiacenti.succLista(p);
        }
    }
    return false;
}
#endif //REALIZZAZIONI_GRAPH_COLOR_H
