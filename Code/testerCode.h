#ifndef REALIZZAZIONI_TESTERCODE_H
#define REALIZZAZIONI_TESTERCODE_H
#include "codap.h"
#include <iostream>

using namespace std;

int main(){

codap<int> C;

    C.incoda(1);
    C.incoda(2);
    C.incoda(3);
    C.incoda(4);

    cout << " " << C.leggiCoda();
    C.fuoriCoda();
    C.incoda(4);
    cout << " " << C.leggiCoda();
    C.fuoriCoda();
    cout << " " << C.leggiCoda();
    C.incoda(5);
    C.fuoriCoda();
    cout << " " << C.leggiCoda();
    C.fuoriCoda();
    cout << " " << C.leggiCoda();
    C.fuoriCoda();
}
#endif //REALIZZAZIONI_TESTERCODE_H
