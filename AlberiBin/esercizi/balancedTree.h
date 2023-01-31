
#ifndef REALIZZAZIONI_BALANCEDTREE_H
#define REALIZZAZIONI_BALANCEDTREE_H
#include "../AlberiBin/alberoBinario_pt.h"

template <class T>
class balanced_tree
{
public:

    bool isHeight_balanced(const alberoBinario_pt<T>&B);
    bool complete_nodes(const alberoBinario_pt<T>&B);
private:
void complete_nodes2(const alberoBinario_pt<T>&B, typename alberoBinario_pt<T>::nodo ,bool &);
void isHeight_balanced2(const alberoBinario_pt<T>&B, typename alberoBinario_pt<T>::nodo,bool &);
};

/*
 * Funzione per verificare se un'albero binario è bilanciato in altezza
 * return TRUE se albero vuoto oppure abs(altezza(sottoAlberoSinistro)-altezza(sottoAlberoDestro))<=1 per ogni nodo dell'albero, FALSE: altrimenti
 */
template<class T>
bool balanced_tree<T>::isHeight_balanced(const alberoBinario_pt<T> &B) {
    bool h_balanced=true;
    if (!B.alberoBinVuoto())
        isHeight_balanced2(B,B.radice(),h_balanced);
    return h_balanced;
}

/*
 * La funzione effettua un controllo per vedere se'albero è bilanciato
 */
template<class T>
void balanced_tree<T>::isHeight_balanced2(const alberoBinario_pt<T> &B, typename alberoBinario_pt<T>::nodo n, bool & h_balanced) {
    //se l'albero è bilanciato proseguo, altrimenti esco dalla funzione
    if (h_balanced) {
        if (B.sinistroVuoto(n) && B.destroVuoto(n)) {
            //se il nodo è foglia esco dalla funzione
            return;
        }
        else
        {
            //calcolo altezza del sottoalbero sinistro e destro
            int hsx=0,hdx=0;
            if (!B.sinistroVuoto(n)) hsx=B.altezza_nodo(B,B.figlioSinistro(n));
            if (!B.destroVuoto(n)) hdx=B.altezza_nodo(B,B.figlioDestro(n));
            //se 'albero è bilanciato in altezza per il nodo n, continuo a verificare se la condizione è valida per i suoi figli, altrimenti l'albero non è bilanciato ed esco dalla funzioen
            if (abs(hsx-hdx)<=1 )
            {
                if (!B.sinistroVuoto(n)) isHeight_balanced2(B,B.figlioSinistro(n),h_balanced);
                if (!B.destroVuoto(n)) isHeight_balanced2(B,B.figlioDestro(n),h_balanced);
            }
            else h_balanced=false;
        }
    }
    else return;

}




/*
 * La funzione ritorna TRUE se l'albero è completo (tutti i nodi non foglia hanno 2 figli), false altrimenti
 */
template <class T>
bool balanced_tree<T>::complete_nodes(const alberoBinario_pt<T> &B) {
    bool completo=true;
    //se l'albero è vuoto allora non è completo, altrimenti passo alla verifica
    if (!B.alberoBinVuoto())
    {
        complete_nodes2(B,B.radice(),completo);
    }
    else completo=false;
    return completo;
}


template <class T>
void balanced_tree<T>::complete_nodes2(const alberoBinario_pt<T> &B, typename alberoBinario_pt<T>::nodo n, bool & completo) {
    //se l'albero è completo continuo, altrimenti esco dalla funzione
    if (completo) {
        if (B.sinistroVuoto(n) && B.destroVuoto(n)) {
            //se il nodo è foglia esco dalla funzione
            return;
        } else {
            if (!B.sinistroVuoto(n) && !B.destroVuoto(n)) {
                //se il nodo ha entrambi i figli allora richiamo la funzione di verifica su di essi, altrimenti l'albero non è completo ed esco dalla funzione
                complete_nodes2(B, B.figlioSinistro(n), completo);
                complete_nodes2(B, B.figlioDestro(n), completo);
            } else completo = false;
        }
    }
    else return;
}


#endif //REALIZZAZIONI_BALANCEDTREE_H
