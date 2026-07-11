#ifndef MAIN_H
#define MAIN_H

struct Api {
    void (*Print)(const char* str);
};

struct Overlay {
    void (*Entrypoint)(const char* str);
};

extern struct Api api;

void PrintHeader(void);

#endif
