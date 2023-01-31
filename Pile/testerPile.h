#ifndef REALIZZAZIONI_TESTERPILE_H
#define REALIZZAZIONI_TESTERPILE_H
#include <iostream>
#include "pilav.h"
using namespace std;
int test()
{
    pilav<int> stack;
    pilav<int> stack2(20);
    if(stack.pilaVuota())
        std::cout << "Pila vuota!" << std::endl;
    else
        std::cout << "Pila piena!" << std::endl;
    for(int i=0; i<10; i++)
        stack.insPila(i);
    std::cout << "stack: " << stack << std::endl;
    for(int i=0; i<10; i++)
        stack2.insPila(i);
    std::cout << "stack2: " << stack2 << std::endl;
    stack.insPila(26);
    cout<<stack;
    stack.fuoriPila();
    stack.fuoriPila();
    cout<<stack;
    std::cout << "stack2.leggiPila() : " << stack2.leggiPila() << std::endl;
    pilav<int> stack3(stack2);
    stack3.fuoriPila();
    stack3.fuoriPila();
    std::cout << "stack3: " << stack3 << std::endl;
    std::cout << "stack2: " << stack2 << std::endl;

    return 0;
}
#endif //REALIZZAZIONI_TESTERPILE_H
