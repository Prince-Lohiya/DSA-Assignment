#include <stdio.h>
#include "ui.h"

void addPatient(Heap *h) {
    if (isFull(h)) {
        printf("Emergency room is full. Cannot admit more patients.\n");
        return;
    }
    Patient p;
    p.id = readInt("Enter patient ID (1-99999): ", 1, 99999);
    if (findIndex(h, p.id) != -1) {
        printf("A patient with ID %d is already in the queue.\n", p.id);
        return;
    }
    readName(p.name);
    p.age = readInt("Enter age (0-120): ", 0, 120);
    printPriorityGuide();
    p.priority = readInt("Enter priority (1-5): ", 1, 5);
    insertPatient(h, p);
    printf("Patient %s admitted with priority: %s.\n", p.name, levelName[p.priority]);
}

void treatNext(Heap *h) {
    Patient p;
    if (!extractMin(h, &p)) {
        printf("No patients waiting.\n");
        return;
    }
    printf("Now treating:\n");
    printHeader();
    printPatient(p);
}

void viewNext(Heap *h) {
    Patient p;
    if (!peekMin(h, &p)) {
        printf("No patients waiting.\n");
        return;
    }
    printf("Next patient to be treated:\n");
    printHeader();
    printPatient(p);
}

void searchPatient(Heap *h) {
    if (isEmpty(h)) {
        printf("No patients waiting.\n");
        return;
    }
    int id = readInt("Enter patient ID to search: ", 1, 99999);
    int i = findIndex(h, id);
    if (i == -1) {
        printf("Patient with ID %d not found.\n", id);
        return;
    }
    printHeader();
    printPatient(h->data[i]);
}

void changePriority(Heap *h) {
    if (isEmpty(h)) {
        printf("No patients waiting.\n");
        return;
    }
    int id = readInt("Enter patient ID: ", 1, 99999);
    if (findIndex(h, id) == -1) {
        printf("Patient with ID %d not found.\n", id);
        return;
    }
    printPriorityGuide();
    int np = readInt("Enter new priority (1-5): ", 1, 5);
    updatePriority(h, id, np);
    printf("Priority updated to %s.\n", levelName[np]);
}

void dischargePatient(Heap *h) {
    if (isEmpty(h)) {
        printf("No patients waiting.\n");
        return;
    }
    int id = readInt("Enter patient ID to remove: ", 1, 99999);
    int i = findIndex(h, id);
    if (i == -1) {
        printf("Patient with ID %d not found.\n", id);
        return;
    }
    printf("Patient %s removed from the queue.\n", h->data[i].name);
    removeAt(h, i);
}

void displayQueue(Heap *h) {
    if (isEmpty(h)) {
        printf("No patients waiting.\n");
        return;
    }
    Heap copy = *h;
    Patient p;
    printf("Patients in treatment order (%d waiting):\n", h->size);
    printHeader();
    while (extractMin(&copy, &p))
        printPatient(p);
}

void displayHeapArray(Heap *h) {
    if (isEmpty(h)) {
        printf("Heap is empty.\n");
        return;
    }
    printf("Heap array (index: id/priority):\n");
    for (int i = 0; i < h->size; i++)
        printf("[%d] %d/P%d  ", i, h->data[i].id, h->data[i].priority);
    printf("\n");
}

int main(void) {
    enableAnsi();
    enableUtf8();
    clearScreen();
    printBanner();
    spinner("Loading triage engine", 15);

    Heap h;
    h.size = 0;
    int choice;
    do {
        clearScreen();
        printBanner();
        printMenu();
        choice = readInt("Enter choice: ", 1, 9);
        printf("\n");
        switch (choice) {
            case 1: addPatient(&h); break;
            case 2: treatNext(&h); break;
            case 3: viewNext(&h); break;
            case 4: searchPatient(&h); break;
            case 5: changePriority(&h); break;
            case 6: dischargePatient(&h); break;
            case 7: displayQueue(&h); break;
            case 8: displayHeapArray(&h); break;
            case 9: printf("Exiting. Stay safe.\n"); break;
        }
        if (choice != 9)
            waitForEnter();
    } while (choice != 9);
    return 0;
}