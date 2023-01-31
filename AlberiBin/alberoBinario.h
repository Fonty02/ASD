#include <iostream>
#include <ostream>
#include <algorithm>
using namespace std;
#ifndef REALIZZAZIONI_ALBEROBINARIO_H
#define REALIZZAZIONI_ALBEROBINARIO_H

template <class T, class N>
class alberoBin {
public:
    //TIPO
    typedef T tipoElem;
    typedef N nodo;

    //OPERATORI
    //virtual void crea()=0; SOSTITUITO DAL COSTRUTTORE
    virtual bool alberoBinVuoto() const =0;
    virtual nodo radice() const=0;
    virtual nodo genitore( nodo)  const=0; //padre
    virtual nodo figlioSinistro( nodo) const=0;
    virtual nodo figlioDestro( nodo) const=0;
    virtual bool sinistroVuoto( nodo) const=0;
    virtual bool destroVuoto( nodo) const=0;
    virtual void cancellaSottoalbero(nodo) =0;
    virtual tipoElem leggiNodo( nodo) const =0;
    virtual void scriviNodo(const nodo,  tipoElem)=0;

    virtual void inserisciRadice( tipoElem)=0;
    virtual void inserisciSinistro(const nodo,  tipoElem)=0;
    virtual void inserisciDestro(const nodo,  tipoElem)=0;

    //FUNZIONI DI SERVIZIO
    void visita( int) const;
    int profondita_nodo(alberoBin<T,N>&,nodo);
    int altezza_nodo(const alberoBin<T,N>&,nodo) const;
    //SOVRACCARICO STAMPA (usa di default la preVisita)
     template <class T1,class N1>
     friend ostream& operator<<(ostream &, alberoBin<T1,N1>&);

private:
    void stampa(nodo, std::ostream &) ;
    void preVisita( nodo) const;
    void postVisita( nodo) const;
    void visitaSimmetrica( nodo) const;
};



//Funzione di visigta di un albero, secondo il tipo di visita scelto (solo se l'albero non è vuoto)
template <class T,class N>
void alberoBin<T, N>::visita( int scelta) const {
    if (!alberoBinVuoto())
    {
        switch (scelta)
        {
            case 1:
                cout<<"[ ";
                preVisita(radice());
                cout<<"]"<<endl;
                break;
            case 2:
                cout<<"[ ";
                postVisita(radice());
                cout<<"]"<<endl;
                break;
            case 3:
                cout<<"[ ";
                visitaSimmetrica(radice());
                cout<<"]"<<endl;
                break;
            default:
                throw std::out_of_range("SCELTA NON ESISTENTE");
            }
    }
    else cout<<"ALBERO VUOTO"<<endl;

}


//Previsita di un albero
template <class T, class N>
void alberoBin<T,N>::preVisita(nodo n) const{
	cout<<leggiNodo(n)<<"  ";
	if(!sinistroVuoto(n)) preVisita(figlioSinistro(n));
    if(!destroVuoto(n)) preVisita(figlioDestro(n));
}


//PostVisita di un albero
template <class T, class N>
void alberoBin<T,N>::postVisita(nodo n) const{
    if(!sinistroVuoto(n)) postVisita(figlioSinistro(n));
    if(!destroVuoto(n)) postVisita(figlioDestro(n));
    cout<<leggiNodo(n)<<"  ";
}

//Visita simmetrica di un albero
template <class T, class N>
void alberoBin<T,N>::visitaSimmetrica(nodo n) const {
    if(!sinistroVuoto(n)) visitaSimmetrica(figlioSinistro(n));
    cout<<leggiNodo(n)<<"  ";
    if(!destroVuoto(n)) visitaSimmetrica(figlioDestro(n));
}


//SOVRACCARICO STAMPA (usa di default la preVisita)
template <class T1,class N1>
ostream& operator<<(ostream & os, alberoBin<T1,N1>& T)
{
    if (T.alberoBinVuoto())
        os<<"ALBERO VUOTO"<<endl;
    else {
        os << "[ ";
        T.stampa(T.radice(), os);
        os << "] " << endl;
    }
    return os;
}

//sovraccarico stampa di un albero
template <class T,class N>
void alberoBin<T, N>::stampa(nodo n, std::ostream & os)  {

    os<< leggiNodo(n)<<" ";
    if(!sinistroVuoto(n)) stampa(figlioSinistro(n),os);
    if(!destroVuoto(n)) stampa(figlioDestro(n),os);
}

//La funzione restiuisce la profondità di un nodo (lunghezza del cammino che parte dalla radice e arriva al nodo)
template<class T,class N>
int alberoBin<T, N>::profondita_nodo(alberoBin<T,N>& BT,nodo n) {
    if (!alberoBinVuoto())
    {
        int c=0;
            while (n!=BT.radice())
            {
                c++;
                n=BT.genitore(n);
            }
        return c;
    }
    else throw std::out_of_range("ALBERO VUOTO");
}

//La funzione restituisce l'altezza di un nodo (lunghezza del cammino più lungo che parte da quel nodo e arriva a una foglia)
template <class T,class N>
int alberoBin<T,N>::altezza_nodo(const alberoBin<T, N> &BT, nodo n) const{
    //procedo se l'albero non è vuoto
    if (!alberoBinVuoto())
    {
        if(destroVuoto(n) && sinistroVuoto(n))
            //se il nodo è foglia allora ha profondità 0 per definizione
            return 0;
        else {
                int sx = 0, dx = 0;
                if (!sinistroVuoto(n)) {
                    //calcolo altezza sottoalbero sinistro
                    sx= altezza_nodo(BT, BT.figlioSinistro(n));
                    sx++;
                }
                if (!destroVuoto(n)) {
                    //calcolo altezza destro sinistro
                    dx= altezza_nodo(BT, BT.figlioDestro(n));
                    dx++;
                }
                //l'altezza del nodo è data dall'altezza del suo sottoalbero piu alto
                return max(sx, dx);
        }
    }
    else throw std::out_of_range("ALBERO VUOTO");
}
#endif //REALIZZAZIONI_ALBEROBINARIO_H
