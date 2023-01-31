
#include <iostream>
#include <cstdlib>
#include <ctime>
#define N 1
#define min 1
#define max 15

#include "numeriConsecutivi.h"

int main() {
    int V[]={1};
    cout<<endl<<conta_coppie(V, N,0, N-1);
    cout << endl << davide(V, 0, N);
    return 0;
}