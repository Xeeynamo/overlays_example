#include "main.h"
#include <stdio.h>

struct Api api = {0};
static struct Overlay ovl = {0};

static void Print(const char* str) {
    puts(str);
}

void PrintHeader(void) {
    Print("Overlay example");
}

void LoadAndRunOverlay(const char* path) {
    // TODO
    ovl.Entrypoint("hello from main");
}

int main(int argc, char* argv[]) {
    api.Print = Print;
    LoadAndRunOverlay("ovl_1");
    LoadAndRunOverlay("ovl_2");
}
