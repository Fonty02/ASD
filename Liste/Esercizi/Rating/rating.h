
#ifndef REALIZZAZIONI_RATING_H
#define REALIZZAZIONI_RATING_H
#include <string>
using namespace std;
class rating
{
public:
    string utente;
    string prodotto;
    int giudizio;

    rating(string utente,string prodotto, int giudizio) : utente(utente), prodotto(prodotto),
               giudizio(giudizio) {}
    rating()=default;

    ~rating() {

    }

    const string &getUtente() const {
        return utente;
    }

    void setUtente(const string &utente) {
        rating::utente = utente;
    }

    const string &getProdotto() const {
        return prodotto;
    }

    void setProdotto(const string &prodotto) {
        rating::prodotto = prodotto;
    }

    int getGiudizio() const {
        return giudizio;
    }

    void setGiudizio(int giudizio) {
        rating::giudizio = giudizio;
    }

};
#endif //REALIZZAZIONI_RATING_H
