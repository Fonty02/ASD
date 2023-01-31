#ifndef REALIZZAZIONI_SUMTREE_H
#define REALIZZAZIONI_SUMTREE_H
#include "../AlberiBin/alberoBinario_pt.h"


class sumTree
{
public:
    bool isSumTree(alberoBinario_pt<int>& );

private:
    int isSumTree2(alberoBinario_pt<int>&,typename alberoBinario_pt<int>::nodo n,bool&);
};

/*
 * La funzione restitusce TRUE se un'albero è un sumTree, false altrimenti
 * Un albero è un sumTree se ogni nodo ha come valore la somma dei nodi dei suoi sottoalberi destro e sinistro (se esistono)
 */
bool sumTree::isSumTree(alberoBinario_pt<int> & bt) {
    bool sumTree=true;
    if (!bt.alberoBinVuoto())
    {
        //la funzione di verifica è ricorsiva e restituisce un intero, equivalente alla somma di un sottoalbero
       int x= isSumTree2(bt,bt.radice(),sumTree);
    }
    //se l'albero è vuoto non è sun SumTree
    else sumTree=false;
    return sumTree;
}



int sumTree::isSumTree2(alberoBinario_pt<int> & bt, typename alberoBinario_pt<int>::nodo n, bool & sumTree) {
    //se l'albero non è sumTree esco dalla funzione
    if (sumTree)
    {
        if (bt.sinistroVuoto(n) && bt.destroVuoto(n))
        {
            //se il nodo è foglia ritorno il valore del nodo
            return bt.leggiNodo(n);
        }
        else
        {
            int sx=0,dx=0;
            //salvo il valore di somma del sottoalbero sinistro di n (se esiste)
            if (!bt.sinistroVuoto(n)) sx=isSumTree2(bt,bt.figlioSinistro(n),sumTree);
            //salvo il valore di somma del sottoalbero destro di n (se esiste)
            if (!bt.destroVuoto(n)) dx=isSumTree2(bt,bt.figlioDestro(n),sumTree);
            if (bt.leggiNodo(n)==sx+dx)
            {
                //se il nodo n ha come valore la somma dei valori dei suoi sottoalberi allora restituisco il valore del sottoalbero che ha come radice n, altrimenti l'albero non è sumTree ed esco dalla funzione
                return (bt.leggiNodo(n)*2);
            }
            else sumTree=false;
        }
    }
    else return 0;
}
#endif //REALIZZAZIONI_SUMTREE_H
