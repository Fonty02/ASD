#ifndef REALIZZAZIONI_BILANCIATE_H
#define REALIZZAZIONI_BILANCIATE_H

#include <stdio.h>
#include <pilapt.h>

template<class T>
class Bilanciate {
public:
    void test(string s);

private:
    pilapt<T> S;
};

template<class T>
void Bilanciate<T>::test(string s) {
    for (char c: s)
        S.insPila(c);
    int i = s.length(),j= 0;
    int tonde = 0, quadre = 0, graffe = 0;
    bool bilanciata = true;
    char c;
    while (!S.pilaVuota() && bilanciata) {
        c = S.leggiPila();
        S.fuoriPila();
        switch (c) {
            case ')':
                tonde--;
                j=i+1;
                break;
            case '(':
                tonde++;
                break;
            case ']':
                quadre--;
                j=i+1;
                break;
            case '[':
                quadre++;
                break;
            case '}':
                graffe--;
                j=i+1;
                break;
            case '{':
                graffe++;
                break;
            default:
                break;
        }
        if (tonde > 0 || quadre > 0 || graffe > 0) bilanciata = false;
       else
        {
           i--;
           j++;
        }
    }
    if (bilanciata) {
        if (tonde < 0 || quadre < 0 || graffe < 0) bilanciata = false;
    }
    if (bilanciata) cout << "La stringa " << s << " e' bilanciata" << endl;
    else {
        cout << "La stringa " << s << " non e' bilanciata ->";
        if (tonde > 0)
            cout << "PARANTESI TONDA APERTA SENZA CHIUDERE IN POSIZIONE " << i << endl;
        else if (quadre > 0)
            cout << "PARANTESI QUADRA APERTA SENZA CHIUDERE IN POSIZIONE " << i << endl;
        else if (graffe > 0)
            cout << "PARANTESI GRAFFA APERTA SENZA CHIUDERE IN POSIZIONE " << i << endl;
        else if (tonde<0)
             cout << "PARANTESI TONDA CHIUSA SENZA APRIRE IN POSIZIONE " << j << endl;
        else if (quadre<0)
            cout << "PARANTESI QUADRA CHIUSA SENZA APRIRE IN POSIZIONE " << j << endl;
        else if (graffe<0)
            cout << "PARANTESI GRAFFA CHIUSA SENZA APRIRE IN POSIZIONE " << j<< endl;
    }
}

#endif //REALIZZAZIONI_BILANCIATE_H
