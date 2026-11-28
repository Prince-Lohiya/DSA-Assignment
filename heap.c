#include "heap.h"

static int arrivalCounter = 0;

static int isLess(Patient a, Patient b) {
    if (a.priority != b.priority)
        return a.priority < b.priority;
    return a.seq < b.seq;
}

static void swapPatients(Patient *a, Patient *b) {
    Patient t = *a;
    *a = *b;
    *b = t;
}

int isEmpty(Heap *h) {
    return h->size == 0;
}

int isFull(Heap *h) {
    return h->size == MAX;
}

static void heapifyUp(Heap *h, int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (isLess(h->data[i], h->data[p])) {
            swapPatients(&h->data[i], &h->data[p]);
            i = p;
        } else {
            break;
        }
    }
}

static void heapifyDown(Heap *h, int i) {
    while (1) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int s = i;
        if (l < h->size && isLess(h->data[l], h->data[s]))
            s = l;
        if (r < h->size && isLess(h->data[r], h->data[s]))
            s = r;
        if (s == i)
            break;
        swapPatients(&h->data[i], &h->data[s]);
        i = s;
    }
}

int findIndex(Heap *h, int id) {
    for (int i = 0; i < h->size; i++)
        if (h->data[i].id == id)
            return i;
    return -1;
}

int insertPatient(Heap *h, Patient p) {
    if (isFull(h))
        return 0;
    p.seq = arrivalCounter++;
    h->data[h->size] = p;
    heapifyUp(h, h->size);
    h->size++;
    return 1;
}

int extractMin(Heap *h, Patient *out) {
    if (isEmpty(h))
        return 0;
    *out = h->data[0];
    h->size--;
    if (h->size > 0) {
        h->data[0] = h->data[h->size];
        heapifyDown(h, 0);
    }
    return 1;
}

int peekMin(Heap *h, Patient *out) {
    if (isEmpty(h))
        return 0;
    *out = h->data[0];
    return 1;
}

int removeAt(Heap *h, int i) {
    if (i < 0 || i >= h->size)
        return 0;
    h->size--;
    if (i != h->size) {
        h->data[i] = h->data[h->size];
        heapifyUp(h, i);
        heapifyDown(h, i);
    }
    return 1;
}

int updatePriority(Heap *h, int id, int newPriority) {
    int i = findIndex(h, id);
    if (i == -1)
        return 0;
    h->data[i].priority = newPriority;
    heapifyUp(h, i);
    i = findIndex(h, id);
    heapifyDown(h, i);
    return 1;
}