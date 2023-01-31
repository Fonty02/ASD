#ifndef REALIZZAZIONI_SOTTOALBERISOMMAK_H2
#define REALIZZAZIONI_SOTTOALBERISOMMAK_H2

#include "../AlberiBin/alberoBinario_pt.h"

class checkAlbero2 {
public:
    int contaSottoalberi(const alberoBinario_pt<int> &, int);

private:
    int sommaSottoAlbero(const alberoBinario_pt<int> &, int, alberoBinario_pt<int>::nodo, int &count);

};

#endif //REALIZZAZIONI_SOTTOALBERISOMMAK_H

int checkAlbero2::contaSottoalberi(const alberoBinario_pt<int> &B, int k) {
    int count = 0;
    if (!B.alberoBinVuoto()) {
        sommaSottoAlbero(B, k, B.radice(), count);
    }
    return count;
}


int checkAlbero2::sommaSottoAlbero(const alberoBinario_pt<int> &B, int k, alberoBinario_pt<int>::nodo n, int &count) {
    if (B.destroVuoto(n) && B.sinistroVuoto(n)) {
        if (B.leggiNodo(n) == k) count++;
        return B.leggiNodo(n);
    } else {
        int sx = 0, dx = 0;
        if (!B.sinistroVuoto(n)) {
            sx = sommaSottoAlbero(B, k, B.figlioSinistro(n), count);
            if (sx + B.leggiNodo(n) == k) {
                count++;
            }
        }
        if (!B.destroVuoto(n)) {
            dx = sommaSottoAlbero(B, k, B.figlioDestro(n), count);
            if (dx + B.leggiNodo(n) == k) {
                count++;
            }
        }

        if (!B.sinistroVuoto(n) && !B.destroVuoto(n)) {
            if (sx + dx + B.leggiNodo(n) == k) {
                count++;
            }
        }
        return (B.leggiNodo(n) + sx + dx);
    }
}
