#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

#include "ui.h"

#ifdef _WIN32
void enableAnsi(void) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;
    if (GetConsoleMode(h, &mode))
        SetConsoleMode(h, mode | 0x0004);
}
void enableUtf8(void) {
    SetConsoleOutputCP(65001);
}
#else
void enableAnsi(void) {}
void enableUtf8(void) {}
#endif

void clearScreen(void) {
    printf("\033[2J\033[H");
}

const char *levelName[] = {
    "", "Critical", "Emergency", "Urgent", "Less Urgent", "Non-Urgent"
};

// Input Helpers

int readLine(char *buf, int size) {
    if (fgets(buf, size, stdin) == NULL)
        return 0;
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
    return 1;
}

int readInt(const char *prompt, int lo, int hi) {
    char buf[64];
    char *end;
    while (1) {
        printf(TEAL "%s" RESET, prompt);
        if (!readLine(buf, sizeof(buf)))
            exit(0);
        long v = strtol(buf, &end, 10);
        if (end == buf || *end != '\0') {
            printf("Invalid input. Enter a number.\n");
            continue;
        }
        if (v < lo || v > hi) {
            printf("Value must be between %d and %d.\n", lo, hi);
            continue;
        }
        return (int)v;
    }
}

void readName(char *name) {
    while (1) {
        printf(TEAL "Enter patient name: " RESET);
        if (!readLine(name, NAME_LEN))
            exit(0);
        int blank = 1;
        for (int i = 0; name[i]; i++)
            if (name[i] != ' ' && name[i] != '\t')
                blank = 0;
        if (blank) {
            printf("Name cannot be empty.\n");
            continue;
        }
        return;
    }
}

// Visual Enhancement

static void rgb(int r, int g, int b) {
    printf("\033[38;2;%d;%d;%dm", r, g, b);
}

static void gradientLine(const char *s, int r1, int g1, int b1,
                                         int r2, int g2, int b2) {
    int n = (int)strlen(s);
    for (int i = 0; i < n; i++) {
        float t = n > 1 ? (float)i / (n - 1) : 0;
        rgb(r1 + (int)((r2 - r1) * t),
            g1 + (int)((g2 - g1) * t),
            b1 + (int)((b2 - b1) * t));
        putchar(s[i]);
    }
    printf(RESET "\n");
}

void printBanner(void) {
    gradientLine(" _____ ____  ___    _    ____ _____ ", 255,  80, 120, 120,  90, 255);
    gradientLine("|_   _|  _ \\|_ _|  / \\  / ___| ____|", 240,  90, 140, 100, 110, 255);
    gradientLine("  | | | |_) || |  / _ \\| |  _|  _|  ", 225, 100, 160,  80, 130, 255);
    gradientLine("  | | |  _ < | | / ___ \\ |_| | |___ ", 210, 110, 180,  60, 150, 255);
    gradientLine("  |_| |_| \\_\\___/_/   \\_\\____|_____|", 195, 120, 200,  40, 170, 255);
    printf(GREY "  Hospital Emergency Triage  -  heap-powered priority queue\n\n" RESET);
}

void spinner(const char *msg, int frames) {
#if USE_UNICODE
    static const char *f[] = {"⠋","⠙","⠹","⠸","⠼","⠴","⠦","⠧","⠇","⠏"};
    const int n = 10;
    const char *done = "\033[32m✔\033[0m";
#else
    static const char *f[] = {"|", "/", "-", "\\"};
    const int n = 4;
    const char *done = "\033[32m+\033[0m";
#endif
    for (int i = 0; i < frames; i++) {
        printf("\r" TEAL "%s" RESET " %s", f[i % n], msg);
        fflush(stdout);
        SLEEP_MS(80);
    }
    printf("\r%s %s\n", done, msg);
}

void printBadge(int p) {
    static const char *bg[] = {
        "",
        P_RED,   
        P_ORANGE, 
        P_YELLOW,
        P_GREEN,
        P_GREY  
    };
    printf("%s %-11s " RESET, bg[p], levelName[p]);
}

void printPriorityGuide(void) {
    for (int i = 1; i <= 5; i++) {
        printf("  %d - ", i);
        printBadge(i);
        printf("\n");
    }
}

void printHeader(void) {
    printf(GREY "%-6s %-22s %-5s %-12s %-8s\n", "ID", "Name", "Age", "Priority", "Arrival");
    printf("------------------------------------------------------------\n" RESET);
}

void printPatient(Patient p) {
    printf("%-6d %-22s %-5d ", p.id, p.name, p.age);
    printBadge(p.priority);
    printf("#%-7d\n", p.seq + 1);
}

void printMenu(void) {
    printf("\n" RED "+ HOSPITAL EMERGENCY TRIAGE +" RESET "\n\n");
    printf(TEAL "1." RESET " Admit new patient\n");
    printf(TEAL "2." RESET " Treat next patient\n");
    printf(TEAL "3." RESET " View next patient\n");
    printf(TEAL "4." RESET " Search patient by ID\n");
    printf(TEAL "5." RESET " Change patient priority\n");
    printf(TEAL "6." RESET " Remove patient from queue\n");
    printf(TEAL "7." RESET " Display all waiting patients\n");
    printf(TEAL "8." RESET " Display heap array\n");
    printf(TEAL "9." RESET " Exit\n");
}

void waitForEnter(void) {
    char buf[64];
    printf("\n" GREY "Press Enter to continue..." RESET);
    readLine(buf, sizeof(buf));
}