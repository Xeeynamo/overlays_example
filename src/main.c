#include "main.h"
#include <stdio.h>

struct Api api = {0};

static void Print(const char* str) {
    puts(str);
}

void PrintHeader(void) {
    Print("Overlay example");
}

int main() {
    api.Print = Print;

    struct Overlay ovl;
    if (LoadOverlay(&ovl, "ovl_1")) {
        ovl.Entrypoint("hello from main");
    }
    if (LoadOverlay(&ovl, "ovl_2")) {
        ovl.Entrypoint("hello from main");
    }
    return 0;
}
