#ifndef HEAP_H
#define HEAP_H

#include "config.h"

typedef struct {
    int id;
    char name[NAME_LEN];
    int age;
    int priority;
    int seq;
} Patient;

typedef struct {
    Patient data[MAX];
    int size;
} Heap;

int isEmpty(Heap *h);
int isFull(Heap *h);
int findIndex(Heap *h, int id);
int insertPatient(Heap *h, Patient p);
int extractMin(Heap *h, Patient *out);
int peekMin(Heap *h, Patient *out);
int removeAt(Heap *h, int i);
int updatePriority(Heap *h, int id, int newPriority);

#endif