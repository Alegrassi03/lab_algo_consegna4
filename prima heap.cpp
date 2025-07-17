
const int MAX_SIZE = 10000;
int heap[MAX_SIZE];
int heap_pos[MAX_SIZE];    // heap_pos[v] = posizione del nodo v nel heap[]
int heap_node[MAX_SIZE];   // heap_node[i] = nodo v in heap[i]
int heap_size = 0;



/// uso -1 per indicare un indice non esistente
int parent_idx(int n) {
    if (n == 0)
        return -1;
    return (n - 1) / 2;
}


int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }

void swap_heap(int i, int j) {
    swap(heap[i], heap[j]);
    swap(heap_node[i], heap_node[j]);
    heap_pos[heap_node[i]] = i;
    heap_pos[heap_node[j]] = j;
}

void heapify_down(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if (l < heap_size && heap[l] < heap[smallest])
        smallest = l;
    if (r < heap_size && heap[r] < heap[smallest])
        smallest = r;

    if (smallest != i) {
        swap_heap(i, smallest);
        heapify_down(smallest);
    }
}

void heapify_up(int i) {
    while (i > 0 && heap[parent(i)] > heap[i]) {
        swap_heap(i, parent(i));
        i = parent(i);
    }
}

void heap_insert(int nodo, int distanza) {
    heap[heap_size] = distanza;
    heap_node[heap_size] = nodo;
    heap_pos[nodo] = heap_size;
    heapify_up(heap_size);
    heap_size++;
}

int heap_remove_min() {
    if (heap_size == 0) return -1;
    int min_nodo = heap_node[0];

    swap_heap(0, heap_size - 1);
    heap_size--;
    heapify_down(0);

    return min_nodo;
}

void decrease_key(int nodo, int nuova_distanza) {
    int i = heap_pos[nodo];
    heap[i] = nuova_distanza;
    heapify_up(i);
}


//////////////////////////////////////////////////
/// Heap
//////////////////////////////////////////////////