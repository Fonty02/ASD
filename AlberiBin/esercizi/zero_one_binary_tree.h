#include "../alberoBinario_pt.h"
#ifndef REALIZZAZIONI_ZERO_ONE_BINARY_TREE_H
#define REALIZZAZIONI_ZERO_ONE_BINARY_TREE_H
template <class T>
class zero_one_binary_tree
{
public:
    typedef typename alberoBinario_pt<T>::nodo nodo;
    zero_one_binary_tree()=default;
    ~zero_one_binary_tree()=default;
    bool is_zero_one(alberoBinario_pt<T>&);
    int zero_nodes(alberoBinario_pt<T>&);

private:
    void zero_nodes2(alberoBinario_pt<T>&, nodo   ,int  &);
    void is_zero_one2(alberoBinario_pt<T>&, nodo   ,bool  &);
};


//La funzione restituisce il numero di nodi il cui valore è zero
template <class T>
int zero_one_binary_tree<T>::zero_nodes(alberoBinario_pt<T> & BT) {
    int counter=0;
    if (!BT.alberoBinVuoto()) zero_nodes2(BT,BT.radice(),counter);
    return counter;
}

//la funzione conta il numero di nodi il cui valore è 0
template <class T>
void zero_one_binary_tree<T>::zero_nodes2(alberoBinario_pt<T> &BT, nodo n, int &counter) {
    if (BT.leggiNodo(n)==0) counter++;
    if (!BT.sinistroVuoto(n)) zero_nodes2(BT,BT.figlioSinistro(n),counter);
    if (!BT.destroVuoto(n)) zero_nodes2(BT,BT.figlioDestro(n),counter);
}


//La funzione restituisce TRUE se un albero è zero_one, false altrimenti
//Un albero è zero_one quando tutti i nodi non foglia hanno 2 figli e ogni nodo con valore 0 ha i figli con valore 1 e viceversa
template <class T>
bool zero_one_binary_tree<T>::is_zero_one(alberoBinario_pt<T> &BT) {
    if (!BT.alberoBinVuoto() && (BT.leggiNodo(BT.radice())==0))
    {
        bool verifica=true;
        is_zero_one2(BT,BT.radice(),verifica);
        return verifica;
    }
    //se l'albero è vuoto non è zero one
    else return false;
}


template<class T>
void zero_one_binary_tree<T>::is_zero_one2(alberoBinario_pt<T> &BT, nodo n , bool & verifica) {
    //se l'albero non è zero_one esco dalla funzione
    if (verifica) {
        //se sono una foglia non devo svolgere alcun controllo ed esco dalla funzione
        if (BT.destroVuoto(n) && BT.sinistroVuoto(n)) {
            return;
        } else
        {
           if (BT.sinistroVuoto(n) || BT.destroVuoto(n))
           {
               //se a un nodo non foglia manca un figlio allora l'albero non è di tipo zero_one
               verifica=false;
               return;
           }
           else
           {
               if (BT.leggiNodo(n)==0)
               {
                   //se il nodo ha valore 0 e i suoi figli non sono entrambi 1 allora l'albero non è zero_one ed esco dalla funzione
                   if (BT.leggiNodo(BT.figlioDestro(n))==0 || BT.leggiNodo(BT.figlioSinistro(n))==0)
                   {
                       verifica=false;
                       return;
                   }
               }
               else
               {
                   //se il nodo ha valore 1 e i suoi figli non sono entrambi 0 allora l'albero non è zero_one ed esco dalla funzione
                   if (BT.leggiNodo(BT.figlioDestro(n))==1 || BT.leggiNodo(BT.figlioSinistro(n))==1)
                   {
                       verifica=false;
                       return;
                   }
               }
               //richiamo la funzione di verifica sui figli nel nodo n
               this->is_zero_one2(BT,BT.figlioSinistro(n),verifica);
               this->is_zero_one2(BT,BT.figlioDestro(n),verifica);
           }
        }
    }
    return;
}

#endif //REALIZZAZIONI_ZERO_ONE_BINARY_TREE_H
