#ifndef REALIZZAZIONI_SOTTOALBERISOMMAK_H
#define REALIZZAZIONI_SOTTOALBERISOMMAK_H
#include "../AlberiBin/alberoBinario_pt.h"
class checkAlbero
{
public:
    int contaSottoalberi(const alberoBinario_pt<int>&,int);
private:
    void visitaSottoAlberi(const alberoBinario_pt<int>&,int, alberoBinario_pt<int>::nodo ,int& counter);
    int sommaSottoAlbero(const alberoBinario_pt<int>&, alberoBinario_pt<int>::nodo);

};
#endif //REALIZZAZIONI_SOTTOALBERISOMMAK_H

//La funzione restituisce il numero di sottoAlberi la cui somma di tutti i valori dei nodi presenti è pari a k
int checkAlbero::contaSottoalberi(const alberoBinario_pt<int> &B, int k) {
    int count=0;
    if (!B.alberoBinVuoto())
    {
        visitaSottoAlberi(B,k,B.radice(),count);
    }
    return count;
}

//La funzione visita un sottoAlbero e nel mentre contra il numero di sottoAlbeir la cui somma dei valori dei nodi è pari a K
void checkAlbero::visitaSottoAlberi(const alberoBinario_pt<int> &B, int k,  alberoBinario_pt<int>::nodo n,int &count) {
    //valore statico perchè ogni volta che richiamo ricorsivamente la funzione questo non deve variare
    int somma=sommaSottoAlbero(B,n);
    //se la somma del sottoalbero avente come radice n è pari a k allora incremento il contatore
    if (somma==k ) count++;
    //richiamo la funzione di visita sui figli del nodo n (se esistono)
    if(!B.sinistroVuoto(n))
    {
        visitaSottoAlberi(B,k,B.figlioSinistro(n),count);
    }
    if(!B.destroVuoto(n))
    {
        visitaSottoAlberi(B,k,B.figlioDestro(n),count);
    }
}

//La funzione restituisce la somma dei valori del sottoAlbero avente come radice il nodo n
int checkAlbero::sommaSottoAlbero(const alberoBinario_pt<int> &B,  alberoBinario_pt<int>::nodo n ) {
    if (B.destroVuoto(n) && B.sinistroVuoto(n))
        //se il nodo è foglia restituisco il valore del nodo
        return B.leggiNodo(n);
    else
    {
        int sx=0,dx=0;
        //se il nodo ha un figlio sinistro calcolo la somma dei valori del sottoAlbero sinistro
        if(!B.sinistroVuoto(n)) sx=sommaSottoAlbero(B,B.figlioSinistro(n));
        //se il nodo ha un figlio destro calcolo la somma dei valori del sottoAlbero destro
        if(!B.destroVuoto(n)) dx=sommaSottoAlbero(B,B.figlioDestro(n));
        //restituisco il valore del nodo sommato alla somma dei valori dei suoi sottoAlberi sinistro e destro
        return (B.leggiNodo(n)+sx+dx);
    }
}

