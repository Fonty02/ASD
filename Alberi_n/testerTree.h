#include <iostream>
#include "maxLevelSum.h"
#include "sommaLivelloMaggiore.h"
#include "contaPariVisitaSimmetrica.h"
#include "util_n_tree.h"
#include "modificaAlbero.h"

int main2()
{
    alberoPt<int> Tree;
    alberoPt<int>::nodo n;
    Tree.inserisciRadice(1);
    n=Tree.radice();
    Tree.inserisciPrimoFiglio(Tree.radice(), 3);
    Tree.inserisciPrimoFiglio(Tree.radice(), 2);
    n = Tree.primoFiglio(n);
    Tree.inserisciPrimoFiglio(n, 4);
    Tree.inserisciPrimoFiglio(n, 5);
    Tree.inserisciPrimoFiglio(n, 6);
    Tree.stampaAlbero();
    maxLevelSum s;
      cout<<s.max_level(Tree)<<endl;
    cout<<Tree.larghezza()<<endl;
    sommaK livMag;
    for (int i=0;i<5;i++)
        cout<<"LIVELLO MAGGIORE DI  "<<i<<" "<<livMag.somma(Tree,i)<<endl;
    contaVisita c;
    cout<<"NUMERO NODI CON PADRE PARI "<<c.conta(Tree)<<endl;
    util_n_tree<int> ut;
    cout<<"NUMERO FOGLIE "<<ut.n_leaf(Tree)<<endl;
    for (int i=0;i<5;i++)
        cout<<"NODI AL LIVELLO  "<<i<<" "<<ut.n_level(Tree,i)<<endl;
    modifcaAlbero mod;
    mod.modifica(Tree);
    cout<<"NUOVO ALBERO "<<endl;
    Tree.stampaAlbero();
    return 0;
}


