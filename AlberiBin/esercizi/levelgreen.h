
#ifndef REALIZZAZIONI_LEVELGREEN_H
#define REALIZZAZIONI_LEVELGREEN_H
#include "alberoBinario_pt.h"
#include <string>
using namespace std;
class green_redBin
{
public:
    int foglie_verdi(alberoBinario_pt<string>& BT);
    int level_red(alberoBinario_pt<string>& BT);
private:
    int foglie_verdi(alberoBinario_pt<string>& BT,const typename alberoBinario_pt<string>::nodo n);
    int level_red(alberoBinario_pt<string>& BT ,const typename alberoBinario_pt<string>::nodo n,int livello);
};

//La funzione restituisce il numero di foglie verdi in un albero
int green_redBin::foglie_verdi(alberoBinario_pt<string> &BT)
{
    if (BT.alberoBinVuoto()) return 0;
    else return foglie_verdi(BT,BT.radice());
}


//la funzione conta il numero di foglie il cui valore è verde
int green_redBin::foglie_verdi(alberoBinario_pt<string> & BT, const typename alberoBinario_pt<string>::nodo n)  {
    int sx=0, dx=0;
    if (BT.sinistroVuoto(n) && BT.destroVuoto(n))
    {
        //se il nodo è foglia restituisco 1 se ha come valore verde, 0 altrimenti
        return (BT.leggiNodo(n) == "verde");
    }
    else
    {
        //se il nodo non è foglia restituisco richiamo la funzione ricorsivamente sui suoi figli (se esistono)
        if (!BT.sinistroVuoto(n)) sx=foglie_verdi(BT,BT.figlioSinistro(n));
        if (!BT.destroVuoto(n)) dx=foglie_verdi(BT,BT.figlioDestro(n));
        //return del numero di foglie verdi
        return (sx+dx);
    }
}


//restituisce il numero di nodi di livello pari il cui valore è "rosso" e che hanno almeno un figlio il cui valore è "bianco";
int green_redBin::level_red(alberoBinario_pt<string> &BT)  {
    if (BT.alberoBinVuoto()) return 0;
    else return level_red(BT,BT.radice(),0);
}

//calcola il numero di nodi di livello pari il cui valore è "rosso" e che hanno almeno un figlio il cui valore è "bianco";
int green_redBin::level_red(alberoBinario_pt<string> &BT, const int n, int livello) {
    int sx=0,dx=0,c=0;
    if (BT.sinistroVuoto(n) && BT.destroVuoto(n))
        return 0;
    else
    {
        if ((livello%2)==0 && BT.leggiNodo(n)=="rosso")
        {
            if (!BT.sinistroVuoto(n) && (BT.leggiNodo(BT.figlioSinistro(n))=="bianco")) c=1;
            if (!BT.destroVuoto(n) && (BT.leggiNodo(BT.figlioDestro(n))=="bianco")) c=1;
        }
        if (!BT.sinistroVuoto(n)) sx= level_red(BT,BT.figlioSinistro(n),(livello+1));
        if (!BT.destroVuoto(n)) dx= level_red(BT,BT.figlioDestro(n),(livello+1));
        return (sx+dx+c);
    }
}
#endif //REALIZZAZIONI_LEVELGREEN_H
