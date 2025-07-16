#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

// compilazione: g++ Consegna4.cpp



//////////////////////////////////////////////////
/// Min-heap
//////////////////////////////////////////////////


const int MAX_SIZE = 256; /// allocazione statica
int heap[MAX_SIZE];
int heap_size = 0; 
//funzioni per calcolare gli indici dell'array che implementa l'heap
/// uso -1 per indicare un indice non esistente
int parent_idx(int n) {
    if (n == 0)
        return -1;
    return (n - 1) / 2;
}

int child_L_idx(int n) {
    if (2 * n + 1 >= heap_size)
        return -1;
    return 2 * n + 1;
}

int child_R_idx(int n) {
    if (2 * n + 2 >= heap_size)
        return -1;
    return 2 * n + 2;
}

/// restituisce 0 se il nodo in posizione n e' un nodo interno (almeno un figlio)
/// restituisce 1 se il nodo non ha figli
int is_leaf(int n) {
    return (child_L_idx(n) == -1); // non c'e' bisogno di controllare il figlio R

    /* versione equivalente
    if (child_L_idx(n)==-1)
      return 1;
    return 0;
    */
}

void heap_insert(int elem) {
    /// inserisco il nuovo nodo con contenuto elem
    /// nell'ultima posizione dell'array
    /// ovvero continuo a completare il livello corrente

    if (details)
        printf("Inserisco elemento %d in posizione %d\n", elem, heap_size);

    if (heap_size < MAX_SIZE) {
        int i = heap_size;
        heap_size++;

        heap[i] = elem;

        while (i != 0) {                          // non sono sulla radice
            if (heap[parent_idx(i)] <= heap[i]) { /// proprieta' dell' heap e' rispettata -> esco
                if (details)
                    printf("Il genitore ha valore %d >= del nodo %d, esco\n", heap[parent_idx(i)], heap[i]);
                return;
            }

            if (details)
                printf("Il genitore ha valore %d < del nodo %d, swap\n", heap[parent_idx(i)], heap[i]);
            /// il nodo ha un genitore sicuramente <   --> swap
            int t = heap[parent_idx(i)];
            heap[parent_idx(i)] = heap[i];
            heap[i] = t;

            // tree_print_graph(0); // radice
            // n_operazione++;

            i = parent_idx(i);
        }

    } else
        printf("Heap pieno!\n");
}

void decrease_key(int indice_nodo, int key) {
    // key = nuovo valore

    if (indice_nodo < 0 || indice_nodo >= heap_size) {
        printf("Nodo non esistente\n");
        return;
    }

    if (heap[indice_nodo] < key) {
        printf("la chiave non e' piu' piccola!\n");
        return;
    }

    heap[indice_nodo] = key;

    int i = indice_nodo;
    while (i != 0) {                          // non sono sulla radice
        if (heap[parent_idx(i)] >= heap[i]) { /// proprieta' dell' heap e' rispettata -> esco
            if (details)
                printf("Il genitore ha valore %d >= del nodo %d, esco\n", heap[parent_idx(i)], heap[i]);
            return;
        }

        if (details)
            printf("Il genitore ha valore %d < del nodo %d, swap\n", heap[parent_idx(i)], heap[i]);
        /// il nodo ha un genitore sicuramente <   --> swap
        int t = heap[parent_idx(i)];
        heap[parent_idx(i)] = heap[i];
        heap[i] = t;

        tree_print_graph(0); // radice
        n_operazione++;

        i = parent_idx(i);
    }
}

int heap_remove_min() {

    if (heap_size <= 0) { /// heap vuoto!
        printf("Errore: heap vuoto\n");
        return -1;
    }

    int massimo = heap[0];

    if (details)
        printf("Massimo identificato %d\n", massimo);
    /// scambio la radice con l'ultima foglia a destra
    /// il massimo e' stato spostato in fondo --> pronto per l'eliminazione
    int t = heap[0];
    heap[0] = heap[heap_size - 1];
    heap[heap_size - 1] = t;

    // elimino il massimo (ora in fondo all'array)
    heap_size--;

    //    tree_print_graph(0);  // radice

    /// nella radice c'e' un valore piccolo (minimo?)
    int i = 0; // indice di lavoro (parto dalla root)

    while (!is_leaf(i)) { /// garantisco di fermarmi alla foglia

        if (details)
            printf("Lavoro con il nodo in posizione i = %d, valore %d\n", i, heap[i]);

        int con_chi_mi_scambio = -1;

        /// controllo il nodo i con il suo figlio L
        if (heap[i] > heap[child_L_idx(i)]) { // il nodo i e' piu' piccolo
            /// attivare uno swap (la proprieta' heap non e' rispettata)
            con_chi_mi_scambio = child_L_idx(i);
            if (details)
                printf("Figlio L e' piu' grande (valore %d)\n", heap[child_L_idx(i)]);

            if (child_R_idx(i) >= 0 && // esiste il nodo destro
                heap[child_L_idx(i)] > heap[child_R_idx(i)]) {
                con_chi_mi_scambio = child_R_idx(i);
                if (details)
                    printf("Figlio R e' ancora piu' grande (valore %d)\n", heap[child_R_idx(i)]);
            }
        } else { // il nodo e' piu' grande del figlio L

            if (child_R_idx(i) >= 0) {                // esiste il figlio R
                if (heap[i] < heap[child_R_idx(i)]) { /// attivo lo swap
                    con_chi_mi_scambio = child_R_idx(i);
                    if (details)
                        printf("Figlio R e' piu' grande del nodo (valore %d)\n", heap[child_R_idx(i)]);
                } else
                    break;
            } else
                break;
        }

        /// swap tra i e con_chi_mi_scambio
        int t = heap[i];
        heap[i] = heap[con_chi_mi_scambio];
        heap[con_chi_mi_scambio] = t;

        i = con_chi_mi_scambio;

        // tree_print_graph(0);  // radice
        // n_operazione++;
    }

    return massimo;
}






//////////////////////////////////////////////////
/// Min-heap
//////////////////////////////////////////////////