#ifndef UI_H
#define UI_H

#include "config.h"
#include "heap.h"

extern const char *levelName[];

void enableAnsi(void);
void enableUtf8(void);
void clearScreen(void);

int  readLine(char *buf, int size);
int  readInt(const char *prompt, int lo, int hi);
void readName(char *name);

void printBanner(void);
void spinner(const char *msg, int frames);
void printBadge(int priority);

void printPriorityGuide(void);
void printHeader(void);
void printPatient(Patient p);
void printMenu(void);
void waitForEnter(void);

#endif