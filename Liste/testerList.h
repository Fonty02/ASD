#ifndef REALIZZAZIONI_TESTERLIST_H
#define REALIZZAZIONI_TESTERLIST_H
#include "Linked_list.h"
#include <iostream>

using namespace std;


int main2(){
    Linked_list<int> list1, list2;
    Linked_list<int>::posizione iter;

    int x;
   iter=list1.primoLista();
    x = 1;
    list1.insLista(x, iter);
    x = 2;
    list1.insLista(x, iter);
    x = 3;
    list1.insLista(x, iter);
    x = 4;
    list1.insLista(x, iter);
    cout << "list1=" ; cout << list1;


}
#endif //REALIZZAZIONI_TESTERLIST_H
