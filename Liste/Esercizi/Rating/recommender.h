#ifndef REALIZZAZIONI_RECOMMDER_H
#define REALIZZAZIONI_RECOMMDER_H
#include "rating.h"
#include "List_vector.h"
class reccomender{
public:
    //inserisci nella listan ratings un nuovo rating <user,item,rating>
    void insert(string user, string item, int giudizio);
    //restituisce la media dei rating dell'utente user
    double meanUser(string user);
    //restituisce la media del rating per il prodotto item
    double meanItem(string item);
    //restituisce la lista dei prodotto votati dall'utente user
    List_vector<string> rated(string user);
    //restituisce la lista dei prodotti votati sia da user1 che da user2
    List_vector<string> common(string user1, string user2);

    //usando il metodo common, calcola quanti prodotti sono stati votati allo stesso modo sia da user 1 che da user 2
    int commonEqual(string user1, string user2);
    reccomender()=default;


private:
    List_vector<rating> ratings;;
};

void reccomender::insert(string user, string item, int giudizio) {
    if(giudizio>=1 && giudizio<=5) {
        rating r(user, item, giudizio);
        List_vector<rating>::posizione p = ratings.primoLista();
        bool inserimento = true;
        //un utente non puo votare due volte lo stesso prodotto
        while (!ratings.fineLista(p) && inserimento) {
            rating r2 = ratings.leggiLista(p);
            if ((r2.prodotto.compare(item) == 0) && (r2.utente.compare(user) == 0)) inserimento = false;
            else p = ratings.succLista(p);
        }
        if (inserimento) ratings.inserisciCoda(r);
    }
}

double reccomender::meanUser(string user) {
    int i=0;
    int somma=0;
    List_vector<rating>::posizione p=ratings.primoLista();
    while (!ratings.fineLista(p))
    {
        if (ratings.leggiLista(p).utente.compare(user)==0) {
            somma += ratings.leggiLista(p).giudizio;
            i++;
        }
        p=ratings.succLista(p);
    }
    if (i==0) return 0;
    else return (double) somma/i;
}

double reccomender::meanItem(string item) {
    int i=0;
    int somma=0;
    List_vector<rating>::posizione p=ratings.primoLista();
    while (!ratings.fineLista(p))
    {
        if (ratings.leggiLista(p).prodotto.compare(item)==0) {
            somma += ratings.leggiLista(p).giudizio;
            i++;
        }
        p=ratings.succLista(p);
    }
    if (i==0) return 0;
    else return (double) somma/i;
}

List_vector<string> reccomender::rated(string user) {
    List_vector<string> list;
    List_vector<rating>::posizione p=ratings.primoLista();
    while (!ratings.fineLista(p))
    {
        if (ratings.leggiLista(p).utente.compare(user)==0) {
            list.inserisciCoda(ratings.leggiLista(p).prodotto);
        }
        p=ratings.succLista(p);
    }
    return list;
}

List_vector<string> reccomender::common(string user1, string user2) {
    List_vector<string> list1= rated(user1);
    List_vector<string> list2= rated(user2);
    List_vector<string> commonList;
    List_vector<string>::posizione p=list1.primoLista();
    while (!list1.fineLista(p))
    {
        string prodotto=list1.leggiLista(p);
        if (list2.ricercaElemento(prodotto))
        {
            commonList.inserisciCoda(prodotto);
        }
        p=list1.succLista(p);
    }
    return commonList;
}



int reccomender::commonEqual(string user1, string user2) {
    int u1 = 0;
    int u2 = -1;
    int counter = 0;
    List_vector<string> commonRated = common(user1, user2);
    List_vector<rating>::posizione p = ratings.primoLista();
    List_vector<string>::posizione p2 = commonRated.primoLista();
    while (!commonRated.fineLista(p2)) {
        u1 = -1;
        u2 = 0;
        p = ratings.primoLista();
        while (!ratings.fineLista(p)) {
            if (ratings.leggiLista(p).utente == user1 && ratings.leggiLista(p).prodotto == commonRated.leggiLista(p2)) {
                u1 = ratings.leggiLista(p).giudizio;
            } else if (ratings.leggiLista(p).utente == user2 && ratings.leggiLista(p).prodotto == commonRated.leggiLista(p2)) {
                u2 = ratings.leggiLista(p).giudizio;
            }
            if (u1 == u2) {
                counter++;
                break;
            }
            p = ratings.succLista(p);
        }
        p2 = commonRated.succLista(p2);
    }
    return counter;
}

#endif //REALIZZAZIONI_RECOMMDER_H
